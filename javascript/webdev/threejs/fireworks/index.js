import * as THREE from 'three';
import * as BufferGeometryUtils from "three/examples/jsm/utils/BufferGeometryUtils.js";
import perlin from 'perlin-noise';
import { EffectComposer } from 'three/examples/jsm/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/examples/jsm/postprocessing/RenderPass.js';
import { UnrealBloomPass } from 'three/examples/jsm/postprocessing/UnrealBloomPass.js';
import { ShaderPass } from 'three/examples/jsm/postprocessing/ShaderPass.js';
import { CopyShader } from 'three/examples/jsm/shaders/CopyShader.js';

function randomIntFromInterval(min, max) { // min and max included
    return Math.floor(Math.random() * (max - min + 1) + min);
}

// Vertex Shader
const vertexShader = `
    uniform float size;
    uniform float time;
    attribute float alpha;
    attribute vec3 customColor;
    varying float vAlpha;
    varying vec3 vColor;
    void main() {
        vAlpha = alpha;
        vColor = customColor;
        vec4 mvPosition = modelViewMatrix * vec4(position, 1.0);
        gl_PointSize = size * (300.0 / -mvPosition.z);
        gl_Position = projectionMatrix * mvPosition;
    }
`;

// Fragment Shader
const fragmentShader = `
    varying float vAlpha;
    varying vec3 vColor;

    void main() {
        float distanceToCenter = length(gl_PointCoord - vec2(0.5, 0.5));
        float alpha = 1.0 - smoothstep(0.4, 0.5, distanceToCenter);
        
        // Ensure only main particles glow brightly
        if (vAlpha > 0.6) { // Adjust threshold as needed
            alpha *= 1.0; // Increase or decrease to control intensity
            alpha = clamp(alpha, 0.0, 1.0); // Ensure alpha is within [0, 1] range
        } else {
            alpha = vAlpha; // Use original alpha for the trail particles
        }
        
        gl_FragColor = vec4(vColor, alpha);
    }
`;

// noise
const noise = perlin.generatePerlinNoise(256, 1, {
    amplitude: 155,   // Adjust amplitude for noise influence
    frequency: 0.65,   // Adjust frequency for noise detail
    persistence: 0.35 // Adjust persistence for smoothness
});

/**
 * Global utils
 */
(function() {

    var _w = window,
        _s = window.screen,
        _b = document.body,
        _d = document.documentElement;

    window.Utils = {

        // screen info
        screen: function() {
            var width  = Math.max( 0, _w.innerWidth || _d.clientWidth || _b.clientWidth || 0 );
            var height = Math.max( 0, _w.innerHeight || _d.clientHeight || _b.clientHeight || 0 );
            
            return {
                width   : width,
                height  : height,
                centerx : width / 2,
                centery : height / 2,
                ratio   : width / height,
            };
        },
        // mouse info
        mouse: function( e ) {
            var x = Math.max( 0, e.pageX || e.clientX || 0 );
            var y = Math.max( 0, e.pageY || e.clientY || 0 );
            var s = this.screen();
            
            return {
                x : x,
                y : y,
                centerx : ( x - s.centerx ),
                centery : ( y - s.centery ),
            };
        },
    };
})();

/**
 * Firework object
 */
(function() {
    // constructor
    var Firework = function(scene) {
        this.scene = scene;
        this.done = false;
        this.dest = [];
        this.colors = [];
        this.geometry = null;
        this.points = null;
        this.trailGeometry = null;
        this.trailPoints = null;
        this.trailPositions = [];
        this.material = new THREE.ShaderMaterial({
            uniforms: {
                color: { value: new THREE.Color(0xffffff) },
                size: { value: randomIntFromInterval(16, 36) },
                time: { value: 0.0 }
            },
            vertexShader: vertexShader,
            fragmentShader: fragmentShader,
            transparent: true,
            depthTest: false,
            vertexColors: true
        });
        this.launch();
        this.startTime = Date.now(); // Track start time for fading effect
        this.lifespan = randomIntFromInterval(3000, 5000); // Lifespan of each firework in milliseconds (5 seconds)
        var s = Utils.screen();
        this.exploded = false; // Flag to track if firework has exploded
    };

    // prototype
    Firework.prototype = {
        constructor: Firework,

        // reset
        reset: function() {
            this.scene.remove(this.points);
            this.scene.remove(this.trailPoints);
            this.dest = [];
            this.colors = [];
            this.geometry = null;
            this.points = null;
            this.trailGeometry = null;
            this.trailPoints = null;
            this.trailPositions = [];
            this.exploded = false; // Reset exploded state
        },

        // launch
        launch: function() {
            var s = Utils.screen();
            var x = Math.floor(Math.random() * (s.width * 2)) - s.width;
            var y = Math.floor(Math.random() * 701) + 100;
            var z = Math.floor(Math.random() * -2001) - 1000;

            var from = new THREE.Vector3(x, -800, z);
            var to = new THREE.Vector3(x, y, z);

            var color = new THREE.Color();
            color.setHSL((Math.random() * 0.9) + 0.1, 1, 0.8);
            this.colors.push(color);

            this.geometry = new THREE.BufferGeometry();
            this.points = new THREE.Points(this.geometry, this.material);

            const positions = new Float32Array(3);
            const colors = new Float32Array(3);
            const alphas = new Float32Array(1);

            positions[0] = from.x;
            positions[1] = from.y;
            positions[2] = from.z;
            colors[0] = color.r;
            colors[1] = color.g;
            colors[2] = color.b;
            alphas[0] = 1.0;

            this.geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
            this.geometry.setAttribute('customColor', new THREE.BufferAttribute(colors, 3));
            this.geometry.setAttribute('alpha', new THREE.BufferAttribute(alphas, 1));

            this.dest.push(to);
            this.scene.add(this.points);

            // Shorten the delay before explosion
            setTimeout(() => {
                this.explode(new THREE.Vector3(positions[0], positions[1], positions[2]));
            }, randomIntFromInterval(750, 1750)); // Reduce this delay as needed
        },


        // explode
        explode: function(vector) {
            if (this.exploded) return; // Ensure explosion only happens once
            this.exploded = true;

            this.scene.remove(this.points);
            this.dest = [];
            this.colors = [];
            this.geometry = new THREE.BufferGeometry();
            this.points = new THREE.Points(this.geometry, this.material);

            const numParticles = randomIntFromInterval(1000, 6900); // Number of particles for the explosion

            const positions = new Float32Array(numParticles * 3);
            const colors = new Float32Array(numParticles * 3);
            const alphas = new Float32Array(numParticles);

            var color = new THREE.Color(); // Generate a single color for the entire explosion
            const minHue = 0.1; // Minimum hue (red)
            const maxHue = 0.6; // Maximum hue (yellow-green)
            const randomHue = Math.random() * (maxHue - minHue) + minHue;
            color.setHSL(randomHue, 1, 0.75); // Example: random hue, full saturation, 75% lightness;

            for (var i = 0; i < numParticles; i++) {
                // Generate points on the surface of a sphere
                var phi = Math.random() * Math.PI * 2; // azimuthal angle
                var theta = Math.random() * Math.PI; // polar angle

                var x = Math.sin(theta) * Math.cos(phi);
                var y = Math.sin(theta) * Math.sin(phi);
                var z = Math.cos(theta);
                var radius = randomIntFromInterval(35, 75);
                var f = 10; //this is just a constant dont change
                var noiseValue = noise[i % 256] * 50; // Adjust scaling factor as needed

                positions[i * 3] = x * radius + vector.x + noiseValue; //radius variable just adjusts the size lol
                positions[i * 3 + 1] = y * radius + vector.y + noiseValue; //thats why its in the code for the particles moving so the circles will all be similar probably
                positions[i * 3 + 2] = z * radius + vector.z + noiseValue;

                // Assign color and alpha
                colors[i * 3] = color.r;
                colors[i * 3 + 1] = color.g;
                colors[i * 3 + 2] = color.b;
                alphas[i] = 1.0;

                this.dest.push(new THREE.Vector3(x * (radius*f) + vector.x, y * (radius*f) + vector.y, z * (radius*f) + vector.z)); // Set the destination for each particle
                this.trailPositions.push([new THREE.Vector3(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2])]);
            }

            this.geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
            this.geometry.setAttribute('customColor', new THREE.BufferAttribute(colors, 3));
            this.geometry.setAttribute('alpha', new THREE.BufferAttribute(alphas, 1));

            this.scene.add(this.points);

            // Create trail geometry
            this.trailGeometry = new THREE.BufferGeometry();
            this.trailPoints = new THREE.Points(this.trailGeometry, this.material);
            const trailPositions = new Float32Array(numParticles * 3 * 10); // Trail length of 10
            const trailColors = new Float32Array(numParticles * 3 * 10);
            const trailAlphas = new Float32Array(numParticles * 10);

            for (let i = 0; i < numParticles * 10; i++) {
                trailAlphas[i] = 10000; // change to make trails more visible from start
            }

            this.trailGeometry.setAttribute('position', new THREE.BufferAttribute(trailPositions, 3));
            this.trailGeometry.setAttribute('customColor', new THREE.BufferAttribute(trailColors, 3));
            this.trailGeometry.setAttribute('alpha', new THREE.BufferAttribute(trailAlphas, 1));

            this.scene.add(this.trailPoints);
        },


        // update
        update: function() {
            // only if objects exist
            if (this.points && this.geometry) {
                var positions = this.geometry.attributes.position.array;
                var total = positions.length / 3;

                // If not exploded, continue launching up
                if (!this.exploded) {
                    for (var i = 0; i < total; i++) {
                        positions[i * 3] += (this.dest[i].x - positions[i * 3]) / 20;
                        positions[i * 3 + 1] += (this.dest[i].y - positions[i * 3 + 1]) / 20;
                        positions[i * 3 + 2] += (this.dest[i].z - positions[i * 3 + 2]) / 20;

                        // Check if firework has reached destination
                        if (Math.abs(positions[i * 3] - this.dest[i].x) < 1 &&
                            Math.abs(positions[i * 3 + 1] - this.dest[i].y) < 1 &&
                            Math.abs(positions[i * 3 + 2] - this.dest[i].z) < 1) {
                            this.explode(new THREE.Vector3(positions[0], positions[1], positions[2]));
                            return;
                        }
                    }
                } else {
                    // Handle explosion effect
                    var elapsedTime = Date.now() - this.startTime;
                    var progress = 1 - (elapsedTime / this.lifespan);

                    for (var i = 0; i < total; i++) {
                        positions[i * 3] += (this.dest[i].x - positions[i * 3]) / 40;
                        positions[i * 3 + 1] += (this.dest[i].y - positions[i * 3 + 1]) / 40;
                        positions[i * 3 + 2] += (this.dest[i].z - positions[i * 3 + 2]) / 40;
                        this.geometry.attributes.alpha.array[i] = Math.max(0, progress);

                        // Update trail positions
                        let trail = this.trailPositions[i];
                        trail.unshift(new THREE.Vector3(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]));
                        if (trail.length > 10) trail.pop(); // Maintain trail length of 10

                        // Update trail geometry
                        for (let j = 0; j < trail.length; j++) {
                            this.trailGeometry.attributes.position.array[(i * 10 + j) * 3] = trail[j].x;
                            this.trailGeometry.attributes.position.array[(i * 10 + j) * 3 + 1] = trail[j].y;
                            this.trailGeometry.attributes.position.array[(i * 10 + j) * 3 + 2] = trail[j].z;

                            // Set the trail color to a lighter shade of the original color
                            this.trailGeometry.attributes.customColor.array[(i * 10 + j) * 3] = this.geometry.attributes.customColor.array[i * 3] * 1.1;
                            this.trailGeometry.attributes.customColor.array[(i * 10 + j) * 3 + 1] = this.geometry.attributes.customColor.array[i * 3 + 1] * 1.1;
                            this.trailGeometry.attributes.customColor.array[(i * 10 + j) * 3 + 2] = this.geometry.attributes.customColor.array[i * 3 + 2] * 1.1;

                            this.trailGeometry.attributes.alpha.array[i * 10 + j] = Math.max(0, progress - j * Math.random() / 20); // Change to make the trails progress faster. (the num after Math.random) making num higher will make it disappear slower.
                        }
                    }
                    this.geometry.attributes.alpha.needsUpdate = true;
                    this.trailGeometry.attributes.position.needsUpdate = true;
                    this.trailGeometry.attributes.customColor.needsUpdate = true;
                    this.trailGeometry.attributes.alpha.needsUpdate = true;
                }

                this.geometry.attributes.position.needsUpdate = true;

                // Remove, reset, and stop animating
                if (this.material.uniforms.size.value <= 0) {
                    this.reset();
                    this.done = true;
                    return;
                }
            }
        },
    };

    // export
    window.Firework = Firework;
})();

// Stage setup
(function() {
    var screen = Utils.screen(),
        renderer = null,
        camera = null,
        scene = null,
        composer = null, // Add composer for post-processing
        bloomComposer = null, // Separate composer for bloom
        finalComposer = null, // Final composer to combine scenes
        to = { px: 0, py: 0, pz: 500 },
        fireworks = [];

    try {
        renderer = new THREE.WebGLRenderer( { alpha: true, antialias: true } );
        camera = new THREE.PerspectiveCamera( 60, screen.ratio, 0.1, 20000 );
        scene = new THREE.Scene();
    }
    catch( e ) {
        alert( "THREE.JS Error: " + e.toString() );
        return;
    }

    // Set up post-processing
    composer = new EffectComposer(renderer);
    const renderPass = new RenderPass(scene, camera);
    composer.addPass(renderPass);

    bloomComposer = new EffectComposer(renderer);
    bloomComposer.renderToScreen = false;
    const bloomPass = new UnrealBloomPass(
        new THREE.Vector2(screen.width, screen.height),
        0.5, // Bloom strength
        0.6, // Bloom radius
        0.75 // Bloom threshold
    );
    bloomComposer.addPass(renderPass);
    bloomComposer.addPass(bloomPass);

    finalComposer = new EffectComposer(renderer);
    const finalPass = new ShaderPass(CopyShader);
    finalPass.renderToScreen = true;
    finalComposer.addPass(renderPass);
    finalComposer.addPass(bloomPass);
    finalComposer.addPass(finalPass);

    // Ground mesh
    // var groundGeometry = new THREE.PlaneGeometry(10000, 10000);
    // var groundMaterial = new THREE.MeshBasicMaterial({ color: 0x555555 });
    // var groundMesh = new THREE.Mesh(groundGeometry, groundMaterial);
    // groundMesh.rotation.x = -Math.PI / 2; // Rotsate to lie flat on the ground
    // scene.add(groundMesh);

    // on screen resize
    function onResize( e ) {
        var s = Utils.screen();
        renderer.setSize( s.width, s.height );
        camera.aspect = s.ratio;
        camera.updateProjectionMatrix();
        composer.setSize(s.width, s.height); // Update composer size on resize
        bloomComposer.setSize(s.width, s.height);
        finalComposer.setSize(s.width, s.height);
    };

    // on mouse move and scroll wheel
    function onMouse(e) {
        var mouse = Utils.mouse(e);
        to.px = (mouse.centerx * 0.95);
        to.py = -(mouse.centery * 0.95);

        // Handle scroll wheel zoom
        var delta = 0;
        if (e.type === 'wheel') {
            delta = e.deltaY > 0 ? 1 : -1; // Modern browsers
        } else if (e.type === 'DOMMouseScroll') {
            delta = e.detail > 0 ? 1 : -1; // Firefox
        }
        to.pz += delta * 250; // Adjust the zoom speed as needed
    };

    // on click/tap
    function onPress( e ) {
        fireworks.push( new Firework( scene ) );
    };

    // setup stage
    function setup() {
        camera.position.set( 0, 0, 0 );
        camera.rotation.set( 0, 0, 0 );

        renderer.setPixelRatio( window.devicePixelRatio );
        renderer.setClearColor( 0x000000, 1);
        renderer.sortObjects = true;
        renderer.domElement.style["display"]  = "block";
        renderer.domElement.style["position"] = "fixed";
        renderer.domElement.style["width"]    = "100%";
        renderer.domElement.style["height"]   = "100%";
        renderer.domElement.style["z-index"]  = "-1";

        // Setup event listeners
        window.addEventListener("resize", onResize, false);
        window.addEventListener("mousemove", onMouse, false);
        window.addEventListener("mousedown", onPress, false);
        window.addEventListener("touchstart", onPress, false);
        window.addEventListener("wheel", onMouse, false); // For modern browsers
        window.addEventListener("DOMMouseScroll", onMouse, false); // For Firefox

        document.body.appendChild( renderer.domElement );
    };

    // animation loop
    function draw() {
        requestAnimationFrame( draw );

        // add fireworks
        if( randomIntFromInterval(0, 1000) === 0 ) {
            fireworks.push( new Firework( scene ) );
        }
        // update fireworks
        for( var i = 0; i < fireworks.length; i++ ) {
            if( fireworks[ i ].done ) {                fireworks.splice( i, 1 );
                continue;
            }
            fireworks[ i ].update();
        }

        // lerp camera position
        camera.position.x += ( to.px - camera.position.x ) / 50;
        camera.position.y += ( to.py - camera.position.y ) / 50;
        camera.position.z += ( to.pz - camera.position.z ) / 50;

        // render with post-processing
        composer.render();
        bloomComposer.render();
        finalComposer.render();
    };

    // run
    onResize();
    setup();
    draw();
})();