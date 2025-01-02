#include <bits/stdc++.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FastNoiseLite.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// Configuration
const int WIDTH = 1280;  // Window width
const int HEIGHT = 720;  // Window height
const int WORLD_SIZE = 64; // Size of generated world
const int CHUNK_SIZE = 16;

struct Voxel {
    bool isActive;
    glm::vec3 color;
};

struct Chunk { 
    std::vector<glm::vec3> cubes; 
    bool isLoaded = false; 
};

// World grid for voxels
Voxel world[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];

// 2D grid of chunks
std::vector<std::vector<Chunk>> chunks;

// Initialize noise for terrain generation
FastNoiseLite noise;

// Camera properties
glm::vec3 cameraPos(0.0f, 10.0f, 20.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
float cameraSpeed = 0.05f;
float sensitivity = 0.1f;
float pitch = 0.0f;
float yaw = -90.0f;
bool firstMouse = true;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;

// Player properties
glm::vec3 playerSize = glm::vec3(0.5f, 1.8f, 0.5f); // Player dimensions (similar to Minecraft)
glm::vec3 playerVelocity;
bool isGrounded = false;
float gravity = -9.8f;
float jumpHeight = 1.5f;

// Gravity Things
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Light properties
glm::vec3 lightDir = glm::vec3(0.5f, 1.0f, 0.5f); // Simulate a higher light source
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // White light

// Terrain properties
const float TERRAIN_SCALE = 0.1f;
const int TERRAIN_HEIGHT = 10;

GLuint shaderProgram;

const char* vertexShaderSource = R"(
#version 120
attribute vec3 aPos;
attribute vec3 aColor;
varying vec3 fragColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fragColor = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 120
varying vec3 fragColor;
void main()
{
    gl_FragColor = vec4(fragColor, 1.0);
}
)";

GLuint lightingShader;

const char* lightingVertexShaderSource = R"(
#version 120

attribute vec3 aPos;   // Position attribute
attribute vec3 aColor; // Color attribute

varying vec3 FragPos;  // Position output to the fragment shader
varying vec3 VertexColor; // Color output to the fragment shader

uniform mat4 model; // Model matrix
uniform mat4 view;  // View matrix
uniform mat4 projection; // Projection matrix

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    VertexColor = aColor;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

const char* lightingFragmentShaderSource = R"(
#version 120

varying vec3 FragPos;   // Position from the vertex shader
varying vec3 VertexColor;  // Color from the vertex shader

uniform vec3 lightDir;   // Direction of the light
uniform vec3 lightColor; // Color of the light

void main() {
    vec3 norm = normalize(FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (diffuse + vec3(0.1)) * VertexColor; // Adding some ambient light
    gl_FragColor = vec4(result, 1.0);
}
)";

GLuint skyboxShader;

const char* skyboxVertexShaderSource = R"(
#version 120
attribute vec3 aPos;
uniform mat4 view;
uniform mat4 projection;
void main() {
    vec4 pos = projection * mat4(mat3(view)) * vec4(aPos, 1.0);
    gl_Position = pos.xyww;  // Set w to 1 to avoid z-fighting
})";

const char* skyboxFragmentShaderSource = R"(
#version 120
void main() {
    gl_FragColor = vec4(0.5, 0.7, 1.0, 1.0);  // Sky color gradient
})";

bool compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    std::cout << "Shader compiled successfully" << std::endl;
    return true;
}

bool initShaders() {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader Program Linking Error: " << infoLog << std::endl;
        return false;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

bool initLightingShader() {
    GLuint vertexShader, fragmentShader;
    if (!compileShader(GL_VERTEX_SHADER, lightingVertexShaderSource) ||
        !compileShader(GL_FRAGMENT_SHADER, lightingFragmentShaderSource)) {
        return false;
    }

    lightingShader = glCreateProgram();
    glAttachShader(lightingShader, vertexShader);
    glAttachShader(lightingShader, fragmentShader);
    glLinkProgram(lightingShader);

    int success;
    glGetProgramiv(lightingShader, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(lightingShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    std::cout << "Shaders linked successfully" << std::endl;
    return true;
}

bool initSkyboxShader() {
    GLuint skyboxVertexShader = compileShader(GL_VERTEX_SHADER, skyboxVertexShaderSource);
    GLuint skyboxFragmentShader = compileShader(GL_FRAGMENT_SHADER, skyboxFragmentShaderSource);

    skyboxShader = glCreateProgram();
    glAttachShader(skyboxShader, skyboxVertexShader);
    glAttachShader(skyboxShader, skyboxFragmentShader);
    glLinkProgram(skyboxShader);

    int success;
    char infoLog[512];
    glGetProgramiv(skyboxShader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(skyboxShader, 512, NULL, infoLog);
        std::cerr << "Skybox Shader Program Linking Error: " << infoLog << std::endl;
        return false;
    }

    glDeleteShader(skyboxVertexShader);
    glDeleteShader(skyboxFragmentShader);
    return true;
}

float skyboxVertices[] = {
    -50.0f,  50.0f, -50.0f,
    -50.0f, -50.0f, -50.0f,
     50.0f, -50.0f, -50.0f,
     50.0f, -50.0f, -50.0f,
     50.0f,  50.0f, -50.0f,
    -50.0f,  50.0f, -50.0f,

    -50.0f, -50.0f,  50.0f,
    -50.0f, -50.0f, -50.0f,
    -50.0f,  50.0f, -50.0f,
    -50.0f,  50.0f, -50.0f,
    -50.0f,  50.0f,  50.0f,
    -50.0f, -50.0f,  50.0f,

     50.0f, -50.0f, -50.0f,
     50.0f, -50.0f,  50.0f,
     50.0f,  50.0f,  50.0f,
     50.0f,  50.0f,  50.0f,
     50.0f,  50.0f, -50.0f,
     50.0f, -50.0f, -50.0f,

    -50.0f, -50.0f,  50.0f,
    -50.0f,  50.0f,  50.0f,
     50.0f,  50.0f,  50.0f,
     50.0f,  50.0f,  50.0f,
     50.0f, -50.0f,  50.0f,
    -50.0f, -50.0f,  50.0f,

    -50.0f,  50.0f, -50.0f,
     50.0f,  50.0f, -50.0f,
     50.0f,  50.0f,  50.0f,
     50.0f,  50.0f,  50.0f,
    -50.0f,  50.0f,  50.0f,
    -50.0f,  50.0f, -50.0f,

    -50.0f, -50.0f, -50.0f,
    -50.0f, -50.0f,  50.0f,
     50.0f, -50.0f, -50.0f,
     50.0f, -50.0f, -50.0f,
    -50.0f, -50.0f,  50.0f,
     50.0f, -50.0f,  50.0f
};

// Cube vertices and colors
float vertices[] = {
    // Positions          // Colors
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f
};

GLuint indices[] = {
    0, 1, 2, 2, 3, 0,  // Front face
    4, 5, 6, 6, 7, 4,  // Back face
    0, 1, 5, 5, 4, 0,  // Bottom face
    2, 3, 7, 7, 6, 2,  // Top face
    0, 3, 7, 7, 4, 0,  // Left face
    1, 2, 6, 6, 5, 1   // Right face
};

GLuint VAO, VBO, EBO;

void setupCube() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void drawCube(float x, float y, float z) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void drawTree(int baseX, int baseY, int baseZ) {
    // Draw trunk (brown)
    glUniform3f(glGetUniformLocation(lightingShader, "customColor"), 0.55f, 0.27f, 0.07f);
    drawCube(baseX, baseY + 1, baseZ);    // Trunk base
    drawCube(baseX, baseY + 2, baseZ);    // Trunk middle
    drawCube(baseX, baseY + 3, baseZ);    // Trunk top

    // Draw leaves (green)
    glUniform3f(glGetUniformLocation(lightingShader, "customColor"), 0.0f, 0.5f, 0.0f);
    drawCube(baseX, baseY + 4, baseZ);    // Leaves base
    drawCube(baseX + 1, baseY + 4, baseZ); // Leaves right
    drawCube(baseX - 1, baseY + 4, baseZ); // Leaves left
    drawCube(baseX, baseY + 5, baseZ);    // Leaves top
}

bool checkCollisions(glm::vec3 position, bool &grounded) {
    float playerSize = 0.3f; // Smaller size for more accurate collision detection
    grounded = false;

    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                if (world[x][y][z].isActive) {
                    glm::vec3 blockPos(x, y, z);

                    // Check bounding box collision for ground
                    bool collisionX = position.x + playerSize > blockPos.x && position.x - playerSize < blockPos.x + 1.0f;
                    bool collisionY = position.y + playerSize > blockPos.y && position.y - playerSize < blockPos.y + 1.0f;
                    bool collisionZ = position.z + playerSize > blockPos.z && position.z - playerSize < blockPos.z + 1.0f;

                    if (collisionX && collisionY && collisionZ) {
                        if (position.y > blockPos.y) {
                            grounded = true;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void generateTerrain() {
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int z = 0; z < WORLD_SIZE; z++) {
            float noiseValue = noise.GetNoise((float)x * TERRAIN_SCALE, (float)z * TERRAIN_SCALE);
            int terrainHeight = (noiseValue + 1) * 0.5 * TERRAIN_HEIGHT;
            for (int y = 0; y < terrainHeight; y++) {
                world[x][y][z].isActive = true;
                // Assign a color based on height or noise value
                world[x][y][z].color = glm::vec3(y / (float)TERRAIN_HEIGHT, noiseValue, 1.0f - noiseValue);
            }
        }
    }
}

void generateTrees() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int z = 0; z < WORLD_SIZE; z++) {
            float noiseValue = noise.GetNoise((float)x * TERRAIN_SCALE, (float)z * TERRAIN_SCALE);
            if (noiseValue > 0.5) {
                for (int y = WORLD_SIZE - 1; y >= 0; y--) {
                    if (world[x][y][z].isActive) {
                        drawTree(x, y + 1, z);
                        break;
                    }
                }
            }
        }
    }
}

void loadChunk(int chunkX, int chunkZ) {
    if (!chunks[chunkX][chunkZ].isLoaded) {
        // Generate or load your chunk here
        // For simplicity, let's assume we just add some cubes
        for (int x = 0; x < CHUNK_SIZE; x++) {
            for (int y = 0; y < CHUNK_SIZE; y++) {
                for (int z = 0; z < CHUNK_SIZE; z++) {
                    chunks[chunkX][chunkZ].cubes.push_back(glm::vec3(chunkX * CHUNK_SIZE + x, y, chunkZ * CHUNK_SIZE + z));
                }
            }
        }
        chunks[chunkX][chunkZ].isLoaded = true;
    }
}

void unloadChunk(int chunkX, int chunkZ) {
    if (chunks[chunkX][chunkZ].isLoaded) {
        chunks[chunkX][chunkZ].cubes.clear();
        chunks[chunkX][chunkZ].isLoaded = false;
    }
}

void updateChunks(glm::vec3 playerPos) {
    int currentChunkX = playerPos.x / CHUNK_SIZE;
    int currentChunkZ = playerPos.z / CHUNK_SIZE;

    // Load surrounding chunks
    for (int x = currentChunkX - 1; x <= currentChunkX + 1; x++) {
        for (int z = currentChunkZ - 1; z <= currentChunkZ + 1; z++) {
            loadChunk(x, z);
        }
    }

    // Unload faraway chunks
    // For simplicity, this example doesn't unload chunks. Add logic as needed.
}

bool IsVoxelVisible(const glm::vec3& voxelPos, const glm::mat4& view, const glm::mat4& projection) {
    // Calculate clip-space coordinates
    glm::vec4 clipPos = projection * view * glm::vec4(voxelPos, 1.0f);

    // Perform frustum culling
    if (clipPos.x < -clipPos.w || clipPos.x > clipPos.w) return false; // Left/Right
    if (clipPos.y < -clipPos.w || clipPos.y > clipPos.w) return false; // Top/Bottom
    if (clipPos.z < -clipPos.w || clipPos.z > clipPos.w) return false; // Near/Far

    return true; // Voxel is visible
}

void renderChunks(glm::mat4 view, glm::mat4 projection) {
    glUseProgram(lightingShader);
    glUniform3fv(glGetUniformLocation(lightingShader, "lightDir"), 1, glm::value_ptr(lightDir));
    glUniform3fv(glGetUniformLocation(lightingShader, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniformMatrix4fv(glGetUniformLocation(lightingShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(lightingShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);

    for (int cx = 0; cx < chunks.size(); cx++) {
        for (int cz = 0; cz < chunks[cx].size(); cz++) {
            if (chunks[cx][cz].isLoaded) {
                for (const glm::vec3& cubePos : chunks[cx][cz].cubes) {
                    glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePos);
                    glUniformMatrix4fv(glGetUniformLocation(lightingShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
                    
                    // Set color uniform
                    glm::vec3 blockColor = world[(int)cubePos.x][(int)cubePos.y][(int)cubePos.z].color;
                    glUniform3fv(glGetUniformLocation(lightingShader, "blockColor"), 1, glm::value_ptr(blockColor));
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                }
            }
        }
    }

    glBindVertexArray(0);
}

void renderWorld(const glm::mat4& view, const glm::mat4& projection) {
    glUseProgram(shaderProgram);

    // Pass view and projection matrices to the shader
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Iterate through the world grid
    for (int x = 0; x < WORLD_SIZE; ++x) {
        for (int y = 0; y < WORLD_SIZE; ++y) {
            for (int z = 0; z < WORLD_SIZE; ++z) {
                Voxel& voxel = world[x][y][z];
                
                if (!voxel.isActive) continue;

                // Calculate voxel position
                glm::vec3 voxelPos(x, y, z);
                if (!IsVoxelVisible(voxelPos, view, projection)) {
                    continue;
                }
                glm::mat4 model = glm::translate(glm::mat4(1.0f), voxelPos);
                GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                glBindVertexArray(0);
            }
        }
    }
}

// void renderWorld(glm::mat4 view, glm::mat4 projection) {
//     glUseProgram(lightingShader);

//     glUniform3fv(glGetUniformLocation(lightingShader, "lightDir"), 1, glm::value_ptr(lightDir));
//     glUniform3fv(glGetUniformLocation(lightingShader, "lightColor"), 1, glm::value_ptr(lightColor));

//     glUniformMatrix4fv(glGetUniformLocation(lightingShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
//     glUniformMatrix4fv(glGetUniformLocation(lightingShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

//     // Render a single cube at a fixed position for debugging
//     drawCube(0.0f, 0.0f, -5.0f); // Place cube in front of the camera
// }

GLuint skyboxVAO, skyboxVBO;

void setupSkybox() {
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);

    glBindVertexArray(skyboxVAO);

    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

// void renderSkybox(glm::mat4 view, glm::mat4 projection) {
//     glUseProgram(skyboxShader);

//     // Remove translation from the view matrix
//     glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));
//     glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "view"), 1, GL_FALSE, glm::value_ptr(viewNoTranslation));
//     glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

//     glDepthFunc(GL_LEQUAL); // Ensure skybox passes depth test
//     glBindVertexArray(skyboxVAO); // Use the skybox VAO
//     glDrawArrays(GL_TRIANGLES, 0, 36);
//     glBindVertexArray(0);
//     glDepthFunc(GL_LESS); // Reset depth function to default
// }

void renderSkybox() {
    // Simply clear the background to a blue color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Darker shade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void renderScene(glm::mat4 view, glm::mat4 projection) {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render skybox
    renderSkybox();

    // Render world
    renderWorld(view, projection);
}

void breakBlock() {
    glm::vec3 rayStart = cameraPos;
    glm::vec3 rayDirection = glm::normalize(cameraFront);
    float maxDistance = 5.0f; // Adjust for desired reach
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                if (world[x][y][z].isActive) {
                    glm::vec3 blockPos(x, y, z);
                    glm::vec3 difference = blockPos - rayStart;
                    float distance = glm::length(difference);
                    if (distance < maxDistance && glm::dot(rayDirection, glm::normalize(difference)) > 0.99f) {
                        world[x][y][z].isActive = false;
                        return;
                    }
                }
            }
        }
    }
}

void placeBlock() {
    glm::vec3 rayStart = cameraPos;
    glm::vec3 rayDirection = glm::normalize(cameraFront);
    float maxDistance = 5.0f; // Adjust for desired reach
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                if (!world[x][y][z].isActive) {
                    glm::vec3 blockPos(x, y, z);
                    glm::vec3 difference = blockPos - rayStart;
                    float distance = glm::length(difference);
                    if (distance < maxDistance && glm::dot(rayDirection, glm::normalize(difference)) > 0.99f) {
                        world[x][y][z].isActive = true;
                        return;
                    }
                }
            }
        }
    }
}

void processInput(const Uint8* keystates) {
    glm::vec3 direction(0.0f);
    if (keystates[SDL_SCANCODE_W]) direction += cameraFront;
    if (keystates[SDL_SCANCODE_S]) direction -= cameraFront;
    if (keystates[SDL_SCANCODE_A]) direction -= glm::normalize(glm::cross(cameraFront, cameraUp));
    if (keystates[SDL_SCANCODE_D]) direction += glm::normalize(glm::cross(cameraFront, cameraUp));

    // Handle jumping
    if (keystates[SDL_SCANCODE_SPACE] && isGrounded) {
        playerVelocity.y = sqrt(2.0f * jumpHeight * -gravity);
        isGrounded = false;
        std::cout << "Jumping with velocity: " << playerVelocity.y << std::endl;
    }

    direction.y = 0.0f; // Prevent vertical movement
    if (glm::length(direction) > 0.0f) { // Check to avoid division by zero
        direction = glm::normalize(direction);
    }

    glm::vec3 newPos = cameraPos + direction * cameraSpeed * deltaTime;

    // Apply gravity
    playerVelocity.y += gravity * deltaTime;
    newPos.y += playerVelocity.y * deltaTime;

    std::cout << "Attempting to move to position: " << newPos.x << ", " << newPos.y << ", " << newPos.z << std::endl;

    bool grounded = false;
    if (!checkCollisions(newPos, grounded)) {
        cameraPos = newPos;
        std::cout << "Moved to position: " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
    } else {
        // Adjust position if there's a collision
        cameraPos = glm::round(cameraPos);
        playerVelocity.y = 0.0f; // Reset vertical velocity if collision occurs (to simulate landing)
        isGrounded = grounded;
        std::cout << "Collision detected. Movement adjusted to: " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
    }

    // Ground check
    glm::vec3 belowPos = cameraPos;
    belowPos.y -= 0.3f; // Small buffer to detect ground
    if (checkCollisions(belowPos, grounded)) {
        isGrounded = true;
        playerVelocity.y = 0.0f; // Stop falling if on the ground
    } else {
        isGrounded = false;
    }
}

void mouseMovement(float xpos, float ypos) {
    static bool firstMouse = true;
    static float lastX = xpos;
    static float lastY = ypos;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Inverted controls
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Clamp pitch to avoid flipping the view
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void initializeCamera() {
    cameraPos = glm::vec3(WORLD_SIZE / 2, WORLD_SIZE / 2, WORLD_SIZE / 2);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    std::cout << "Camera initialized at position: " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_Window* window = SDL_CreateWindow("Voxel Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);

    if (!initShaders() || !initLightingShader()) {
        std::cerr << "Shader initialization failed" << std::endl;
        return -1;
    }

    generateTerrain();
    generateTrees();
    initializeCamera();
    setupCube();

    // Initialize chunks
    chunks.resize((WORLD_SIZE / CHUNK_SIZE) + 1, std::vector<Chunk>((WORLD_SIZE / CHUNK_SIZE) + 1));

    bool quit = false;
    SDL_Event e;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    while (!quit) {
        float currentFrame = SDL_GetTicks() / 1000.0f; // Get current time in seconds
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            if (e.type == SDL_MOUSEMOTION) mouseMovement((float)e.motion.x, (float)e.motion.y);
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) breakBlock();
                if (e.button.button == SDL_BUTTON_RIGHT) placeBlock();
            }
        }
        processInput(keystates);

        // Update chunks based on the player's position
        updateChunks(cameraPos);

        // Set clear color to a pleasant sky blue
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        // Render the visible chunks
        renderChunks(view, projection);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}