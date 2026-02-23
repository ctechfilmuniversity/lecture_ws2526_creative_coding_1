import * as THREE from 'three';

const canvas = document.querySelector('#canvasThree');
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setPixelRatio(window.devicePixelRatio);

const scene = new THREE.Scene();
scene.background = new THREE.Color(0xffffff);
scene.fog = new THREE.Fog(0xffffff, 5, 35);

const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.set(0, 0, 0);
camera.rotation.order = 'YXZ';

const ambientLight = new THREE.AmbientLight(0xffffff, 0.7);
scene.add(ambientLight);

const directionalLight1 = new THREE.DirectionalLight(0xffffff, 0.5);
directionalLight1.position.set(10, 10, 10);
scene.add(directionalLight1);

const directionalLight2 = new THREE.DirectionalLight(0xffffff, 0.3);
directionalLight2.position.set(-10, -10, -10);
scene.add(directionalLight2);

const materials = {
  white: new THREE.MeshStandardMaterial({ color: 0xf4f4f4, roughness: 0.1 }),
  red: new THREE.MeshStandardMaterial({ color: 0xd92121, roughness: 0.2 }),
  blue: new THREE.MeshStandardMaterial({ color: 0x1d3a82, roughness: 0.2 }),
  yellow: new THREE.MeshStandardMaterial({ color: 0xf2ca00, roughness: 0.2 }),
  black: new THREE.MeshStandardMaterial({ color: 0x111111, roughness: 0.6 })
};

const group1 = new THREE.Group();
const base1 = new THREE.Mesh(new THREE.BoxGeometry(4, 4, 1), materials.white);
const line1a = new THREE.Mesh(new THREE.BoxGeometry(0.3, 4.2, 1.2), materials.black);
line1a.position.set(-1, 0, 0);
const line1b = new THREE.Mesh(new THREE.BoxGeometry(4.2, 0.3, 1.2), materials.black);
line1b.position.set(0, 1, 0);
const redBox1 = new THREE.Mesh(new THREE.BoxGeometry(1.5, 1.5, 1.1), materials.red);
redBox1.position.set(1, 2, 0.05);
group1.add(base1, line1a, line1b, redBox1);
group1.position.set(0, 0, -12);
group1.lookAt(0, 0, 0);
scene.add(group1);

const group2 = new THREE.Group();
const base2 = new THREE.Mesh(new THREE.BoxGeometry(3, 5, 0.8), materials.white);
const line2 = new THREE.Mesh(new THREE.BoxGeometry(0.4, 5.2, 1), materials.black);
line2.position.set(0.5, 0, 0);
const blueBox2 = new THREE.Mesh(new THREE.BoxGeometry(1.2, 2, 0.9), materials.blue);
blueBox2.position.set(-0.8, -1, 0.05);
const yellowBox2 = new THREE.Mesh(new THREE.BoxGeometry(1, 1.5, 0.9), materials.yellow);
yellowBox2.position.set(1.1, 1.5, 0.05);
group2.add(base2, line2, blueBox2, yellowBox2);
group2.position.set(10, 4, -8);
group2.lookAt(0, 0, 0);
scene.add(group2);

const group3 = new THREE.Group();
const base3 = new THREE.Mesh(new THREE.BoxGeometry(5, 3, 1.5), materials.white);
const line3a = new THREE.Mesh(new THREE.BoxGeometry(5.2, 0.4, 1.7), materials.black);
line3a.position.set(0, -0.5, 0);
const redBox3 = new THREE.Mesh(new THREE.BoxGeometry(2, 1.2, 1.6), materials.red);
redBox3.position.set(-1.5, 1, 0.05);
group3.add(base3, line3a, redBox3);
group3.position.set(-12, -3, -5);
group3.lookAt(0, 0, 0);
scene.add(group3);

const group4 = new THREE.Group();
const base4 = new THREE.Mesh(new THREE.BoxGeometry(4, 4, 1), materials.white);
const line4 = new THREE.Mesh(new THREE.BoxGeometry(0.3, 4.2, 1.2), materials.black);
const yellowBox4 = new THREE.Mesh(new THREE.BoxGeometry(2, 2, 1.1), materials.yellow);
yellowBox4.position.set(1, 0, 0.05);
group4.add(base4, line4, yellowBox4);
group4.position.set(8, -6, 10);
group4.lookAt(0, 0, 0);
scene.add(group4);

const group5 = new THREE.Group();
const base5 = new THREE.Mesh(new THREE.BoxGeometry(3, 3, 1), materials.white);
const line5 = new THREE.Mesh(new THREE.BoxGeometry(3.2, 0.3, 1.2), materials.black);
const blueBox5 = new THREE.Mesh(new THREE.BoxGeometry(1.5, 1.5, 1.1), materials.blue);
blueBox5.position.set(0, 1, 0.05);
group5.add(base5, line5, blueBox5);
group5.position.set(-8, 6, 8);
group5.lookAt(0, 0, 0);
scene.add(group5);

let isDragging = false;
let previousMousePosition = { x: 0, y: 0 };
let rotX = 0;
let rotY = 0;

document.addEventListener('mousedown', (e) => {
  isDragging = true;
  previousMousePosition = { x: e.clientX, y: e.clientY };
});

document.addEventListener('mousemove', (e) => {
  if (isDragging) {
    const deltaX = e.clientX - previousMousePosition.x;
    const deltaY = e.clientY - previousMousePosition.y;

    rotY -= deltaX * 0.003;
    rotX -= deltaY * 0.003;

    rotX = Math.max(-Math.PI / 2, Math.min(Math.PI / 2, rotX));

    camera.rotation.set(rotX, rotY, 0);

    previousMousePosition = { x: e.clientX, y: e.clientY };
  }
});

document.addEventListener('mouseup', () => {
  isDragging = false;
});

window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

function animate() {
  requestAnimationFrame(animate);
  renderer.render(scene, camera);
}

animate();