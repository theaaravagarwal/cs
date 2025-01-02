let scene, camera, renderer, pointCount = Math.round(Math.random() * 100) + 100;
let lineColor = Math.random() * 0xffffff;
let pointColor = Math.random() * 0xffffff;
// let lineColor = 0xffffff;
// let pointColor = 0xffffff;
console.log(pointCount);
let isTyping = false;
let isDeleting = false;
let positions = [];
let motivationalQuotes = [];
let pointOpacities = [];
let velocities = [];
const maxDistance = Math.round(Math.random() * 3) + 0.5;
console.log(maxDistance);
let quotes = 'https://gist.githubusercontent.com/JakubPetriska/060958fd744ca34f099e947cd080b540/raw/963b5a9355f04741239407320ac973a6096cd7b6/quotes.csv'; // From https://gist.github.com/JakubPetriska

// Load quotes from a csv file found on Github
async function loadQuotes() {
    const response = await fetch(quotes);
    const text = await response.text();
    const lines = text.split('\n').slice(1); // Skip the first line since its not a quote
    motivationalQuotes = lines.map(line => {
        const [author, quote] = line.split('","').map(part => part.replace(/"/g, '').trim());
        const validAuthor = author ? author : "Anon"; // Just looks so much cleaner than a blank space tbh
        return { author: validAuthor, quote };
    }).filter(quote => quote.author && quote.quote);
}

function init() {
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.z = 5;
    renderer = new THREE.WebGLRenderer({ antialias: true, alpha: true });
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.body.appendChild(renderer.domElement);
    createPoints();
    document.getElementById('generate').addEventListener('click', generateQuote);
    const buttons = document.querySelectorAll('button');
    buttons.forEach(button => {
        button.style.opacity = 0;
        setTimeout(() => {
            button.style.opacity = 1;
        }, 500);
    });
    animate();
}

function createPoints() {
    positions = [];
    pointOpacities = [];
    velocities = [];
    for (let i = 0; i < pointCount; i++) {
        const x = (Math.random() * 2 - 1) * (window.innerWidth / 100); //positions
        const y = (Math.random() * 2 - 1) * (window.innerHeight / 100);
        positions.push(x, y, 0); //adds positions to list of positions to keep track of them for changes like movement
        pointOpacities.push(Math.random()); //point opacities will be 1 always
        const angle = Math.random() * Math.PI * 2; //random angle for movement
        const speed = (Math.random() - 0.5) * 0.02; //random speed
        velocities.push(Math.cos(angle) * speed); //speed for movement
        velocities.push(Math.sin(angle) * speed);
        const geometry = new THREE.CircleGeometry(0.02, 32);
        const material = new THREE.MeshBasicMaterial({ color: pointColor });
        const circle = new THREE.Mesh(geometry, material);
        circle.position.set(x, y, 0);
        scene.add(circle);
    }
}

function generateQuote() {
    if (motivationalQuotes.length === 0 || isTyping || isDeleting) {
        console.error("Please wait a bit before doing this.");
        return;
    }
    const randomIndex = Math.floor(Math.random() * motivationalQuotes.length);
    const quoteElement = document.getElementById('quote');
    const { author, quote } = motivationalQuotes[randomIndex];
    deleteQuote(() => {
        quoteElement.style.opacity = 1;
        typeQuote(quote, author);
    });
}

function deleteQuote(callback) {
    const quoteElement = document.getElementById('quote');
    const fullText = quoteElement.innerHTML;
    const words = fullText.split(' ');
    let index = words.length;
    isDeleting = true;
    function deleteNextWord() {
        if (index > 0) {
            index--;
            quoteElement.innerHTML = words.slice(0, index).join(' ') + ' |';
            setTimeout(deleteNextWord, 175);
        } else {
            quoteElement.innerHTML = '';
            isDeleting = false;
            callback();
        }
    }
    deleteNextWord();
}

function typeQuote(quote, author) {
    isTyping = true;
    const quoteElement = document.getElementById('quote');
    const fullText = `<strong>${quote}</strong><br><em>~ ${author}</em>`;
    let index = 0;
    const caret = document.createElement('span');
    caret.textContent = '|';
    caret.style.animation = 'blink 0.7s step-end infinite';
    quoteElement.appendChild(caret);
    function typeNextCharacter() {
        if (index < fullText.length) {
            quoteElement.innerHTML = fullText.substring(0, index + 1) + caret.outerHTML;
            index++;
            const randomDelay = (Math.random() * 50) + 50;
            setTimeout(typeNextCharacter, randomDelay);
        } else {
            caret.remove();
            isTyping = false;
        }
    }
    typeNextCharacter();
}

function animate() {
    requestAnimationFrame(animate);
    const circles = scene.children.filter(child => child instanceof THREE.Mesh);
    for (let i = 0; i < circles.length; i++) {
        const circle = circles[i];
        circle.position.x += velocities[i * 2];
        circle.position.y += velocities[i * 2 + 1];
        if (Math.abs(circle.position.x) > window.innerWidth / 200 || Math.abs(circle.position.y) > window.innerHeight / 200) {
            circle.position.x = (Math.random() * 2 - 1) * (window.innerWidth / 100);
            circle.position.y = (Math.random() * 2 - 1) * (window.innerHeight / 100);
        }
    }
    const lineMaterial = new THREE.LineBasicMaterial({ color: lineColor });
    const linePositions = [];
    for (let i = 0; i < circles.length; i++) {
        const circle1 = circles[i];
        const x1 = circle1.position.x;
        const y1 = circle1.position.y;

        for (let j = 0; j < circles.length; j++) {
            if (i !== j) {
                const circle2 = circles[j];
                const x2 = circle2.position.x;
                const y2 = circle2.position.y;
                const distance = Math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2);
                if (distance < maxDistance) {
                    linePositions.push(x1, y1, 0);
                    linePositions.push(x2, y2, 0);
                }
            }
        }
    }
    if (linePositions.length > 0) {
        const lineGeometry = new THREE.BufferGeometry();
        lineGeometry.setAttribute('position', new THREE.Float32BufferAttribute(linePositions, 3));
        const linesSegment = new THREE.LineSegments(lineGeometry, lineMaterial);
        scene.add(linesSegment);
        setTimeout(() => {
            scene.remove(linesSegment);
        }, 0);
    }
    renderer.render(scene, camera);
}

window.addEventListener('resize', () => {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
});

loadQuotes().then(init);

window.onload = function() {
    const h1 = document.querySelector('h1');
    h1.classList.add('visible');
};

document.getElementById('generate').addEventListener('click', function() {
    const h1 = document.querySelector('h1');
    h1.classList.remove('visible');
    setTimeout(() => {
        h1.classList.add('visible');
    }, 100);
});