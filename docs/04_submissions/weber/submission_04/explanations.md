import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import { GUI } from "lil-gui";

// ===== SCENE & CAMERA =====
const scene = new THREE.Scene();
scene.background = new THREE.Color(0xBDEDFF);

const camera = new THREE.PerspectiveCamera(
  75,
  window.innerWidth / window.innerHeight,
  0.1,
  100
);
camera.position.z = 5;

// ===== RENDERER =====
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);

// ===== CUBE =====
const cubeGeometry = new THREE.BoxGeometry();
const cubeMaterial = new THREE.MeshStandardMaterial({ color: 0x50ffc0 });
const cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
scene.add(cube);

// ===== BULBS + POINT LIGHTS =====
const bulbPositions = [
  { x: -2, y: 1, z: 0 },
  { x: 0, y: 1, z: 0 },
  { x: 2, y: 1, z: 0 },
];

const bulbs = [];
const lights = [];

bulbPositions.forEach((pos, i) => {
  // Sphere
  const bulbGeo = new THREE.SphereGeometry(0.2, 16, 16);
  const bulbMat = new THREE.MeshStandardMaterial({
    color: 0xffffaa,
    emissive: 0xffffaa,
    emissiveIntensity: 1,
  });
  const bulb = new THREE.Mesh(bulbGeo, bulbMat);
  bulb.position.set(pos.x, pos.y, pos.z);
  scene.add(bulb);
  bulbs.push(bulb);

  // PointLight
  const pointLight = new THREE.PointLight(0xffffff, 1, 10);
  pointLight.position.set(pos.x, pos.y, pos.z);
  scene.add(pointLight);
  lights.push(pointLight);
});

// ===== AMBIENT & DIRECTIONAL LIGHT =====
const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xff2f00, 5);
directionalLight.position.set(2, 2, 2);
scene.add(directionalLight);

// ===== CONTROLS =====
const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;

// ===== GUI =====
const gui = new GUI();
const params = {
  light_intensity: ambientLight.intensity,
  bgLightness: 1,
};

// Ambient light slider
gui.add(params, "light_intensity").min(0).max(2).step(0.01).name("Ambient Light");

// Background brightness slider
gui.add(params, "bgLightness").min(0).max(1).step(0.01).name("Background Brightness");

// Sliders for each bulb
lights.forEach((_, i) => {
  params["bulb" + i] = 1; // initial intensity
  gui
    .add(params, "bulb" + i)
    .min(0)
    .max(5)
    .step(0.01)
    .name("Bulb " + (i + 1));
});

// ===== HANDLE WINDOW RESIZE =====
window.addEventListener("resize", () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

// ===== ANIMATE =====
function animate() {
  requestAnimationFrame(animate);

  // Rotate cube
  cube.rotation.x += 0.01;
  cube.rotation.y += 0.01;

  // Update lights
  ambientLight.intensity = params.light_intensity;

  lights.forEach((light, i) => {
    light.intensity = params["bulb" + i];
    bulbs[i].material.emissiveIntensity = params["bulb" + i]; // sphere glows like light
  });

  // Update background brightness
  const baseColor = new THREE.Color(0xBDEDFF);
  scene.background = baseColor.clone().multiplyScalar(params.bgLightness);

  controls.update();
  renderer.render(scene, camera);
}
animate();
