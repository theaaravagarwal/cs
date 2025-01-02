#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FastNoiseLite.h"

// Configuration
const int WIDTH = 800;
const int HEIGHT = 600;
const int WORLD_SIZE = 128; // Size of generated world

struct Voxel {
    bool isActive;
};

// World grid for voxels
Voxel world[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];

// Initialize noise for terrain generation
FastNoiseLite noise;

// Camera properties
glm::vec3 cameraPos(0.0f, 15.0f, 20.0f); // Initial camera position
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f); // Camera front direction
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f); // Camera up direction
float cameraSpeed = 0.2f; // Movement speed
float lastX = WIDTH / 2.0f; // Mouse starting position (X)
float lastY = HEIGHT / 2.0f; // Mouse starting position (Y)
float pitch = 0.0f; // Camera pitch
float yaw = -90.0f; // Camera yaw

// Initialize noise for terrain generation
void generateTerrain() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int z = 0; z < WORLD_SIZE; z++) {
            float height = noise.GetNoise((float)x, (float)z) * 10 + 10;  // Generate height
            for (int y = 0; y < WORLD_SIZE; y++) {
                if (y < height) {
                    world[x][y][z].isActive = true;  // Activate voxel below height
                }
            }
        }
    }
}

GLuint shaderProgram;

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 fragColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fragColor = aColor;
})";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 fragColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(fragColor, 1.0);
})";

GLuint compileShader(GLuint shaderType, const char* shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    // Error checking
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Shader Compilation Error: " << infoLog << std::endl;
    }
    return shader;
}

void initShaders() {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Error checking
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader Program Linking Error: " << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
}

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

void renderWorld() {
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                if (world[x][y][z].isActive) {
                    drawCube(x, y, z);
                }
            }
        }
    }
}

void processInput(SDL_Event& event) {
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_W]) {
        cameraPos += cameraSpeed * cameraFront; // Move forward
    }
    if (keystates[SDL_SCANCODE_S]) {
        cameraPos -= cameraSpeed * cameraFront; // Move backward
    }
    if (keystates[SDL_SCANCODE_A]) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; // Move left
    }
    if (keystates[SDL_SCANCODE_D]) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; // Move right
    }
    if (keystates[SDL_SCANCODE_SPACE]) {
        cameraPos += cameraSpeed * cameraUp; // Move up
    }
    if (keystates[SDL_SCANCODE_LSHIFT]) {
        cameraPos -= cameraSpeed * cameraUp; // Move down
    }
}

void updateCamera() {
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set OpenGL context version to 3.2 for compatibility with GLSL #version 150
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("Voxel Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cout << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW could not initialize!" << std::endl;
        return 1;
    }


    glEnable(GL_DEPTH_TEST);

    // Initialize shaders and world
    initShaders();
    setupCube();
    generateTerrain();

    // Game loop
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                return 0;
            }
            processInput(event);
        }

        glClearColor(0.5f, 0.7f, 1.0f, 1.0f); // Sky blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateCamera();
        renderWorld();

        SDL_GL_SwapWindow(window);
    }

    return 0;
}