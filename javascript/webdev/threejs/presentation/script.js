import * as THREE from 'three';
import { UnrealBloomPass } from 'three/examples/jsm/postprocessing/UnrealBloomPass.js';
import { EffectComposer } from 'three/examples/jsm/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/examples/jsm/postprocessing/RenderPass.js';
import { FontLoader } from 'three/examples/jsm/loaders/FontLoader.js';
import { TextGeometry } from 'three/examples/jsm/geometries/TextGeometry.js';

const params = {
    starCount: 48000,
    starSize: 2.5,
    starTwinkleSpeed: 0.7,
    starBloomIntensity: 3.25,
    starBloomRadius: 0.75,
    starBloomThreshold: 0.3,

    cameraDistance: 1300,
    minStarDistance: 750,
    maxStarDistance: 975,
    rotationSpeed: 0.000015,
    degreeOffset: 15,

    cometCount: 10,
    cometSpeed: (Math.random() * 2) + 0.75,
    cometLength: (Math.random() * 150) + 75,
    cometTrailOpacity: 0.7,
    cometSpawnInterval: 100,
    cometHeadSize: 12.5,
    cometTrailSize: 7.5,
    cometSPawnChance: 1,

    cometBloomIntensity: 9.5,  // Added bloom control
    cometBloomRadius: 3.5,     // Added bloom radius
    cometBloomThreshold: 0.1,  // Added bloom threshold

    cometHeadPolygonSides: 8,  // Number of sides for comet head (random-sided polygon)

    cometTrailColors: [
        new THREE.Color(0x4444ff),
        new THREE.Color(0x8844ff),
        new THREE.Color(0x4488ff)
    ],

    cometHeadColor: new THREE.Color(0xaaaaaa),

    starColors: [
        new THREE.Color(0xffffff),
        new THREE.Color(0xfffaf4),
        new THREE.Color(0xf4faff),
        new THREE.Color(0xfff4fa)
    ],
    slideCount: 5,
    currentSlide: 0,
    thankYouText: {
        parts: [
            { text: "Thank", color: new THREE.Color(0x5271ff) }, //not highlighted
            { text: "You", color: new THREE.Color(0x5271ff) }, //highlighted word
            { text: "for Listening", color: new THREE.Color(0x5271ff) } //not highlighted
        ],
        wordSpacing: 50,
        size: 90,
        height: 20,
        curveSegments: 12,
        bevelEnabled: false,
        bevelThickness: 3,
        bevelSize: 1.5,
        bevelSegments: 6,
        glowColor: new THREE.Color(0x99aaff),
        glowStrength: 0.4,
        glowSpread: 0.6,
        animationDuration: 500,
        displayDuration: 1000000,
        fadeOutDuration: 500,
        startScale: 0.8,
        endScale: 1.0,
        enablePulse: true,
        pulseSpeed: 0.002,
        pulseMin: 0.8,
        pulseMax: 1.1
    }
};

let scene, camera, renderer, composer;
let starField, comets = [];

let cometInterval = null;

const fontLoader = new FontLoader();
let cachedFont = null;

fontLoader.load(
    'https://threejs.org/examples/fonts/droid/droid_serif_bold.typeface.json',  // font path
    function(font) {
        console.log('Font preloaded successfully');
        cachedFont = font;
    },
    function(xhr) {
        console.log('Font loading progress:', (xhr.loaded / xhr.total * 100) + '%');
    },
    function(error) {
        console.error('Font loading error:', error);
    }
);

function init() {
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 0.1, 2000);
    camera.position.z = params.cameraDistance;
    renderer = new THREE.WebGLRenderer({ antialias: true, powerPreference: "high-performance" });
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setClearColor(0x000000);
    renderer.toneMapping = THREE.NoToneMapping;
    document.getElementById("container").appendChild(renderer.domElement);
    setupPostProcessing();
    createStarfield();
    animate();
    const slides = document.querySelectorAll('.slide');
    slides.forEach((slide, index) => {
        slide.style.display = index === 0 ? 'block' : 'none';
    });
}

function setupPostProcessing() {
    composer = new EffectComposer(renderer);
    const renderPass = new RenderPass(scene, camera);
    composer.addPass(renderPass);
    
    const bloomPass = new UnrealBloomPass(
        new THREE.Vector2(window.innerWidth, window.innerHeight),
        params.starBloomIntensity,
        params.starBloomRadius,
        params.starBloomThreshold
    );
    
    composer.addPass(bloomPass);
}

function createStarfield() {
    const geometry = new THREE.BufferGeometry();
    const vertices = [];
    const colors = [];
    const twinkleOffsets = [];

    for (let i = 0; i < params.starCount; i++) {
        const r = Math.random() * (params.maxStarDistance - params.minStarDistance) + params.minStarDistance;
        const theta = 2 * Math.PI * Math.random();
        const phi = Math.acos(2 * Math.random() - 1);
        
        const x = r * Math.sin(phi) * Math.cos(theta);
        const y = r * Math.sin(phi) * Math.sin(theta);
        const z = r * Math.cos(phi);
        
        vertices.push(x, y, z);

        const color = params.starColors[Math.floor(Math.random() * params.starColors.length)];
        colors.push(color.r, color.g, color.b);

        twinkleOffsets.push(Math.random() * Math.PI * 2);
    }

    geometry.setAttribute('position', new THREE.Float32BufferAttribute(vertices, 3));
    geometry.setAttribute('color', new THREE.Float32BufferAttribute(colors, 3));
    geometry.setAttribute('twinkleOffset', new THREE.Float32BufferAttribute(twinkleOffsets, 1));

    const material = createStarMaterial();
    starField = new THREE.Points(geometry, material);
    scene.add(starField);
}

function createStarMaterial() {
    return new THREE.ShaderMaterial({
        uniforms: {
            time: { value: 0 }
        },
        vertexShader: `
            attribute float twinkleOffset;
            uniform float time;
            varying vec3 vColor;
            varying float vAlpha;

            void main() {
                vColor = color * 2.0;
                float twinkle = sin(time * 0.5 + twinkleOffset) * 0.5 + 0.5;
                twinkle = pow(twinkle, 1.5);
                vAlpha = twinkle;
                vec4 mvPosition = modelViewMatrix * vec4(position, 1.0);
                gl_PointSize = ${params.starSize} * (900.0 / length(mvPosition.xyz)) * (0.5 + 0.5 * twinkle);
                gl_Position = projectionMatrix * mvPosition;
            }
        `,
        fragmentShader: `
            varying vec3 vColor;
            varying float vAlpha;

            void main() {
                float d = length(gl_PointCoord - vec2(0.5));
                if (d > 0.5) discard;
                
                float strength = 1.0 - (d * 2.0);
                strength = pow(strength, 1.5);
                
                vec3 brightColor = vColor + vec3(0.8, 0.8, 0.8) * vAlpha;
                vec3 finalColor = mix(vColor, brightColor, vAlpha) * 1.5;
                
                gl_FragColor = vec4(finalColor, strength * vAlpha);
            }
        `,
        blending: THREE.AdditiveBlending,
        depthWrite: false,
        transparent: true,
        vertexColors: true
    });
}

let cometCooldown = false;
function createComet() {
    const cometGeometry = new THREE.BufferGeometry();
    const positions = new Float32Array(params.cometLength * 3);  // Positions for the trail
    const colors = new Float32Array(params.cometLength * 3);     // Colors for the trail
    const sizes = new Float32Array(params.cometLength);          // Sizes for each part of the comet's trail
    const opacities = new Float32Array(params.cometLength);      // Opacities for each part of the comet's trail

    for (let i = 0; i < params.cometLength; i++) {
        const t = i / params.cometLength;
    
        // Size decreases as you move away from the head
        if (i === 0) {
            sizes[i] = params.cometHeadSize;
            opacities[i] = 1.0;
            colors[i * 3] = params.cometHeadColor.r;
            colors[i * 3 + 1] = params.cometHeadColor.g;
            colors[i * 3 + 2] = params.cometHeadColor.b;
        } else {
            sizes[i] = params.cometTrailSize * (1 - t); // Tail particles get smaller
            opacities[i] = Math.max(0, (1 - t) * params.cometTrailOpacity);  // Gradual fade
    
            const trailColor = params.cometTrailColors[
                Math.floor(Math.random() * params.cometTrailColors.length)
            ];
            colors[i * 3] = trailColor.r * (1 - t);  // Fading the trail color
            colors[i * 3 + 1] = trailColor.g * (1 - t);
            colors[i * 3 + 2] = trailColor.b * (1 - t);
        }
    
        // Add some slight randomness to the tail's spread
        const trailDistance = t * params.cometLength;
        positions[i * 3] = trailDistance;
        positions[i * 3 + 1] = (Math.random() * 2 - 1) * window.innerHeight * 0.5;
        positions[i * 3 + 2] = (Math.random() * 2 - 1) * 300;
    }    

    // Set up the geometry attributes for the comet's trail
    cometGeometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
    cometGeometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));
    cometGeometry.setAttribute('size', new THREE.BufferAttribute(sizes, 1));
    cometGeometry.setAttribute('opacity', new THREE.BufferAttribute(opacities, 1));

    // Create the comet's head (simple circle geometry)
    const headGeometry = new THREE.CircleGeometry(params.cometHeadSize, params.cometHeadPolygonSides);
    const headMaterial = new THREE.MeshBasicMaterial({
        color: params.cometHeadColor,
        emissive: params.cometHeadColor,
        transparent: true,
        opacity: 1.0,
    });

    const headMesh = new THREE.Mesh(headGeometry, headMaterial);
    headMesh.position.set(window.innerWidth, Math.random() * window.innerHeight - window.innerHeight / 2, Math.random() * 200 - 100);
    scene.add(headMesh);

    const cometMaterial = new THREE.ShaderMaterial({
        uniforms: { 
            time: { value: 0 },
            bloomIntensity: { value: params.cometBloomIntensity },
            bloomRadius: { value: params.cometBloomRadius },
            bloomThreshold: { value: params.cometBloomThreshold },
        },
        vertexShader: `
            attribute float size;
            attribute float opacity;
            varying vec3 vColor;
            varying float vOpacity;
            
            void main() {
                vColor = color * 2.0;  // Apply a brighter color for the bloom effect
                vOpacity = opacity;
                vec4 mvPosition = modelViewMatrix * vec4(position, 1.0);
                gl_PointSize = size * (800.0 / length(mvPosition.xyz));  // Adjust the size of points dynamically
                gl_Position = projectionMatrix * mvPosition;
            }
        `,
        fragmentShader: `
            varying vec3 vColor;
            varying float vOpacity;
    
            void main() {
                float d = length(gl_PointCoord - vec2(0.5));
                if (d > 0.5) discard;
    
                float strength = 1.0 - (d * 2.0);
                strength = pow(strength, 1.5);
    
                // Smooth gradient effect along the tail (fading color and opacity based on distance)
                vec3 glowColor = vColor * 2.0;  // Double the color intensity for a glowing effect
    
                // Modify glow strength based on the tail's position to simulate a fade-out
                float tailDistance = length(gl_PointCoord - vec2(0.5));
                float fadeFactor = 1.0 - (tailDistance * 2.0);
                glowColor *= fadeFactor;
    
                // Apply opacity and final glow
                gl_FragColor = vec4(glowColor, vOpacity * strength);
            }
        `,
        blending: THREE.AdditiveBlending,
        depthWrite: false,
        transparent: true,
        vertexColors: true,
        emissive: new THREE.Color(2.0, 2.0, 2.0),  // Glow from the tail
    });
    

    // Create the comet object with the trail
    const comet = new THREE.Points(cometGeometry, cometMaterial);

    // Random starting position for the comet
    const startY = (Math.random() * 2 - 1) * window.innerHeight * 0.5;
    const startZ = (Math.random() * 2 - 1) * 300;
    comet.position.set(window.innerWidth * 0.5, startY, startZ);

    // Define speed and trajectory for the comet
    const speed = params.cometSpeed * (1.2 + Math.random() * 0.8);
    const angle = ((Math.random() * (-2 * params.degreeOffset)) + params.degreeOffset) * (Math.PI / 180);
    const verticalOffset = Math.random() * 0.5 - 0.25;  // Random vertical fluctuation
    comet.velocity = new THREE.Vector3(
        -speed,                       // constant leftward speed
        0,  // slight vertical fluctuation
        0                             // no change in the z direction
    );

    // Add the comet to the scene and push it to the comets array
    scene.add(comet);
    comets.push(comet);
}

function updateComets() {
    comets = comets.filter((comet) => {
        const positions = comet.geometry.attributes.position.array;

        // Move each particle in the comet trail
        for (let i = positions.length - 3; i > 0; i -= 3) {
            positions[i] = positions[i - 3];
            positions[i + 1] = positions[i - 2];
            positions[i + 2] = positions[i - 1];
        }

        // Update the head position at the start of the trail
        positions[0] = comet.position.x;
        positions[1] = comet.position.y;
        positions[2] = comet.position.z;

        // Move the comet based on its velocity
        comet.position.add(comet.velocity);
        comet.geometry.attributes.position.needsUpdate = true;

        // Remove comet if it moves too far away from the camera
        if (comet.position.length() > 3000) {
            scene.remove(comet);
            return false;
        }
        return true;
    });
}

function checkCometCollisions() {
    for (let i = 0; i < comets.length; i++) {
        for (let j = i + 1; j < comets.length; j++) {
            const cometA = comets[i];
            const cometB = comets[j];

            const dx = cometA.position.x - cometB.position.x;
            const dy = cometA.position.y - cometB.position.y;
            const distance = Math.sqrt(dx * dx + dy * dy);

            // Collision threshold (based on comet size)
            const collisionThreshold = params.cometHeadSize;

            if (distance <= collisionThreshold) {
                createExplosion(cometA, cometB);
                scene.remove(cometA);
                scene.remove(cometB);
                comets.splice(i, 1);
                comets.splice(j - 1, 1);  // j-1 because we removed cometA first
                break;  // exit the loop after collision is handled
            }
        }
    }
}

function createExplosion(cometA, cometB) {
    const explosionGeometry = new THREE.BufferGeometry();
    const explosionCount = 500;  // Number of particles in the explosion

    const positions = new Float32Array(explosionCount * 3);
    const colors = new Float32Array(explosionCount * 3);
    const sizes = new Float32Array(explosionCount);
    const velocities = new Float32Array(explosionCount * 3);  // Speed of each particle
    const opacities = new Float32Array(explosionCount);

    // Mix comet colors directly (50% ratio)
    const colorA = cometA.headColor || params.cometHeadColor;
    const colorB = cometB.headColor || params.cometHeadColor;

    for (let i = 0; i < explosionCount; i++) {
        // Set random position and velocity for each particle
        const angle = Math.random() * Math.PI * 2;
        const speed = Math.random() * 5 + 5;

        positions[i * 3] = cometA.position.x; // Explosion at comet position
        positions[i * 3 + 1] = cometA.position.y;
        positions[i * 3 + 2] = cometA.position.z;

        velocities[i * 3] = Math.cos(angle) * speed;
        velocities[i * 3 + 1] = Math.sin(angle) * speed;
        velocities[i * 3 + 2] = Math.random() * 2 - 1; // Random spread in Z

        // Mix comet colors directly (50% ratio)
        colors[i * 3] = (colorA.r + colorB.r) * 0.5;
        colors[i * 3 + 1] = (colorA.g + colorB.g) * 0.5;
        colors[i * 3 + 2] = (colorA.b + colorB.b) * 0.5;

        sizes[i] = Math.random() * 5 + 5;  // Random size for particles
        opacities[i] = Math.random() * 0.8 + 0.2;  // Random opacity for particles
    }

    explosionGeometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
    explosionGeometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));
    explosionGeometry.setAttribute('size', new THREE.BufferAttribute(sizes, 1));
    explosionGeometry.setAttribute('velocity', new THREE.BufferAttribute(velocities, 3));
    explosionGeometry.setAttribute('opacity', new THREE.BufferAttribute(opacities, 1));

    const explosionMaterial = new THREE.ShaderMaterial({
        uniforms: {
            time: { value: 0 },
            bloomIntensity: { value: params.cometBloomIntensity },
            bloomRadius: { value: params.cometBloomRadius },
            bloomThreshold: { value: params.cometBloomThreshold },
        },
        vertexShader: `
            attribute float size;
            attribute float opacity;
            attribute vec3 velocity;
            varying vec3 vColor;
            varying float vOpacity;

            void main() {
                vColor = color;
                vOpacity = opacity;

                // Apply velocity to each particle
                vec3 pos = position + velocity * (time * 0.1);
                gl_PointSize = size;
                gl_Position = projectionMatrix * modelViewMatrix * vec4(pos, 1.0);
            }
        `,
        fragmentShader: `
            varying vec3 vColor;
            varying float vOpacity;

            void main() {
                float d = length(gl_PointCoord - vec2(0.5));
                if (d > 0.5) discard;

                float strength = 1.0 - (d * 2.0);
                strength = pow(strength, 1.5);

                gl_FragColor = vec4(vColor, strength * vOpacity);
            }
        `,
        blending: THREE.AdditiveBlending,
        depthWrite: false,
        transparent: true,
        vertexColors: true,
    });

    const explosion = new THREE.Points(explosionGeometry, explosionMaterial);
    scene.add(explosion);

    // Animation loop to update explosion particles over time
    const explosionTime = { value: 0 };
    function updateExplosion() {
        explosionTime.value += 0.1;
        explosionMaterial.uniforms.time.value = explosionTime.value;

        // Clean up after 1 second
        if (explosionTime.value > 1.0) {
            scene.remove(explosion);
        }
    }

    setInterval(updateExplosion, 16);  // Update every 16ms (~60FPS)
}

function animate(time) {
    requestAnimationFrame(animate);

    if (Math.random() < params.cometSpawnChance) {
        createComet();
    }

    if (starField && starField.material.uniforms) {
        starField.material.uniforms.time.value = time * 0.001;
        starField.rotation.y += params.rotationSpeed;
    }

    comets.forEach(comet => {
        if (comet.material.uniforms) {
            comet.material.uniforms.time.value = time * 0.001;
        }
    });

    //checkCometCollisions();
    updateComets();

    composer.render();
}

window.addEventListener('resize', onWindowResize);

function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
    composer.setSize(window.innerWidth, window.innerHeight);
}

function nextSlide() {
    const slides = document.querySelectorAll('.slide');
    if (params.currentSlide < slides.length - 1) {
        slides[params.currentSlide].style.display = 'none';
        params.currentSlide++;
        slides[params.currentSlide].style.display = 'block';
    }
}

function prevSlide() {
    const slides = document.querySelectorAll('.slide');
    if (params.currentSlide > 0) {
        slides[params.currentSlide].style.display = 'none';
        params.currentSlide--;
        slides[params.currentSlide].style.display = 'block';
    }
}

window.addEventListener('keydown', (event) => {
    if (event.key === 'Enter') {
        const container = document.getElementById("container");
        const elements = document.body.children;
        
        for (let el of elements) {
            if (el !== container) el.style.display = 'none';
        }
    }

    if (event.key === ' ') {
        if (!cometInterval) {
            cometInterval = setInterval(createComet, 200);
            createThankYouText();
        }
    }

    if (event.key === 'Escape') {
        clearInterval(cometInterval);
        cometInterval = null;
    }

    if (cometCooldown) return;
    
    switch(event.key) {
        case 'ArrowRight':
            nextSlide();
            cometCooldown = true;
            break;
        case 'ArrowLeft':
            prevSlide();
            cometCooldown = true;
            break;
    }
    setTimeout(() => {
        cometCooldown = false;
    }, 500);
});

window.addEventListener('keyup', (event) => {
    if (event.key === 'ArrowRight' || event.key === 'ArrowLeft') {
        cometCooldown = false;
    }
});

// Add this CSS to your stylesheet or add it to the head of your HTML
const style = document.createElement('style');
style.textContent = `
.thank-you-text {
    position: fixed;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    font-size: 5rem;
    color: #fff;
    text-shadow: 
        0 0 7px #fff,
        0 0 10px #fff,
        0 0 21px #fff,
        0 0 42px #5271ff,
        0 0 82px #5271ff,
        0 0 92px #5271ff,
        0 0 102px #5271ff,
        0 0 151px #5271ff;
    animation: fadeInOut 2s ease-in-out;
    pointer-events: none;
    z-index: 1000;
    font-family: Arial, sans-serif;
    text-align: center;
    opacity: 0;
}

@keyframes fadeInOut {
    0% { opacity: 0; transform: translate(-50%, -50%) scale(0.8); }
    20% { opacity: 1; transform: translate(-50%, -50%) scale(1); }
    80% { opacity: 1; transform: translate(-50%, -50%) scale(1); }
    100% { opacity: 0; transform: translate(-50%, -50%) scale(1.2); }
}
`;
document.head.appendChild(style);

function createThankYouText() {
    if (!cachedFont) return;

    const group = new THREE.Group();
    let currentX = 0;

    // First pass: compute total width including word spacing
    let totalWidth = 0;
    params.thankYouText.parts.forEach((part, index) => {
        const tempGeometry = new TextGeometry(part.text, {
            font: cachedFont,
            size: params.thankYouText.size,
            height: params.thankYouText.height,
            curveSegments: params.thankYouText.curveSegments,
            bevelEnabled: params.thankYouText.bevelEnabled,
            bevelThickness: params.thankYouText.bevelThickness,
            bevelSize: params.thankYouText.bevelSize,
            bevelSegments: params.thankYouText.bevelSegments
        });
        tempGeometry.computeBoundingBox();
        totalWidth += tempGeometry.boundingBox.max.x - tempGeometry.boundingBox.min.x;
        // Add word spacing between words (except after the last word)
        if (index < params.thankYouText.parts.length - 1) {
            totalWidth += params.thankYouText.wordSpacing;
        }
        tempGeometry.dispose();
    });

    // Second pass: create and position meshes
    currentX = -totalWidth / 2; // Start from half the total width to center
    params.thankYouText.parts.forEach((part, index) => {
        const textGeometry = new TextGeometry(part.text, {
            font: cachedFont,
            size: params.thankYouText.size,
            height: params.thankYouText.height,
            curveSegments: params.thankYouText.curveSegments,
            bevelEnabled: params.thankYouText.bevelEnabled,
            bevelThickness: params.thankYouText.bevelThickness,
            bevelSize: params.thankYouText.bevelSize,
            bevelSegments: params.thankYouText.bevelSegments
        });

        const textMaterial = new THREE.ShaderMaterial({
            uniforms: {
                baseColor: { value: part.color },
                glowColor: { value: params.thankYouText.glowColor },
                glowStrength: { value: params.thankYouText.glowStrength },
                glowSpread: { value: params.thankYouText.glowSpread },
                opacity: { value: 0.0 },
                time: { value: 0.0 }
            },
            vertexShader: `
                varying vec3 vNormal;
                varying vec3 vViewPosition;
                
                void main() {
                    vNormal = normalize(normalMatrix * normal);
                    vec4 mvPosition = modelViewMatrix * vec4(position, 1.0);
                    vViewPosition = -mvPosition.xyz;
                    gl_Position = projectionMatrix * mvPosition;
                }
            `,
            fragmentShader: `
                uniform vec3 baseColor;
                uniform vec3 glowColor;
                uniform float glowStrength;
                uniform float glowSpread;
                uniform float opacity;
                uniform float time;
                
                varying vec3 vNormal;
                varying vec3 vViewPosition;
                
                void main() {
                    vec3 normal = normalize(vNormal);
                    vec3 viewDir = normalize(vViewPosition);
                    
                    float fresnel = pow(1.0 - abs(dot(normal, viewDir)), glowSpread);
                    fresnel = pow(fresnel, 1.8);  // Increased power for softer glow
                    
                    // Further reduced glow intensity
                    vec3 finalColor = baseColor + (glowColor * fresnel * glowStrength * 0.6);
                    
                    // Even gentler pulse
                    float pulse = sin(time) * 0.2 + 0.8;  // Reduced pulse range
                    finalColor += glowColor * fresnel * pulse * 0.2;  // Reduced pulse contribution
                    
                    float finalOpacity = max(opacity, fresnel * opacity * 0.3);  // Reduced glow opacity
                    
                    gl_FragColor = vec4(finalColor, finalOpacity);
                }
            `,
            transparent: true,
            side: THREE.DoubleSide,
            blending: THREE.AdditiveBlending
        });

        const textMesh = new THREE.Mesh(textGeometry, textMaterial);
        textGeometry.computeBoundingBox();
        textMesh.position.x = currentX;
        currentX += textGeometry.boundingBox.max.x - textGeometry.boundingBox.min.x;
        if (index < params.thankYouText.parts.length - 1) {
            currentX += params.thankYouText.wordSpacing;
        }
        
        group.add(textMesh);
    });

    group.position.z = -500;
    scene.add(group);

    const startTime = Date.now();
    
    function animateText() {
        const now = Date.now();
        const elapsed = now - startTime;
        
        group.children.forEach(textMesh => {
            textMesh.material.uniforms.time.value = elapsed * params.thankYouText.pulseSpeed;
        });
        
        if (elapsed < params.thankYouText.animationDuration) {
            const progress = elapsed / params.thankYouText.animationDuration;
            const scale = THREE.MathUtils.lerp(
                params.thankYouText.startScale,
                params.thankYouText.endScale,
                progress
            );
            group.scale.set(scale, scale, scale);
            group.children.forEach(textMesh => {
                textMesh.material.uniforms.opacity.value = progress;
            });
        }
        
        if (elapsed > params.thankYouText.displayDuration) {
            const fadeProgress = (elapsed - params.thankYouText.displayDuration) / 
                               params.thankYouText.fadeOutDuration;
            if (fadeProgress >= 1) {
                scene.remove(group);
                group.children.forEach(textMesh => {
                    textMesh.geometry.dispose();
                    textMesh.material.dispose();
                });
                return;
            }
            group.children.forEach(textMesh => {
                textMesh.material.uniforms.opacity.value = 1 - fadeProgress;
            });
        }

        requestAnimationFrame(animateText);
    }

    animateText();
}

init();