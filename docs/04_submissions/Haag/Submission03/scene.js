/*
 * Example 13: three.js Basic Setup
 *
 * This example demonstrates the fundamental structure of a three.js scene.
 *
 * Key concepts covered:
 * - Scene: Container for all 3D objects
 * - Camera: Defines the point of view (PerspectiveCamera)
 * - Renderer: Draws the scene to the canvas (WebGLRenderer)
 * - Geometry: The shape of 3D objects (BoxGeometry)
 * - Material: The appearance of objects (MeshNormalMaterial)
 * - Mesh: Combination of geometry and material
 * - Render loop: Continuous rendering for animation
 */

import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import * as THREE from "three";
import {GUI} from "lil-gui";

const gui = new GUI();

gui.add( {message: 'Hello, lil-gui!'}, 'message');


console.log(THREE);

// ============================================
// 1. SCENE
// ============================================
// The scene is a container that holds all 3D objects, lights, etc.
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x202020);
// ============================================
// 2. CAMERA
// ============================================
// PerspectiveCamera mimics how the human eye sees
// Parameters:
//   - fov: Field of view (degrees) - how wide the camera sees
//   - aspect: Width/height ratio of the canvas
//   - near: Closest distance the camera can see
//   - far: Farthest distance the camera can see
const fov = 70;
const aspect = window.innerWidth / window.innerHeight;
const near = 0.1;
const far = 10;
const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);

// Position the camera along the Z-axis (toward/away from scene)
// By default, camera looks down the negative Z-axis
camera.position.z = 2;

// ============================================
// 3. RENDERER
// ============================================
// The renderer draws the scene to the canvas
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;
controls.dampingFactor = 0.05;

// Set the size of the renderer to match the window
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));

// ============================================
// 4. GEOMETRY
// ============================================
// Geometry defines the shape of 3D objects
// BoxGeometry creates a box/cube
// Parameters: width, height, depth
const geometry = new THREE.BoxGeometry(0.5, 0.5, 0.5);

// ============================================
// 5. MATERIAL
// ============================================
// Material defines the appearance of objects
// MeshNormalMaterial shows colors based on surface normals
// (useful for debugging - each face has a different color)
// 5. MATERIAL

const knotMaterial = new THREE.MeshPhysicalMaterial({
  color: 0xffffff,        // leicht eingefärbt geht auch, z.B. 0x88ccff
  metalness: 0,
  roughness: 0.05,        // sehr glatt
  transmission: 1,        // macht es wirklich "glasig"
  transparent: true,
  opacity: 1,
  ior: 1.5,               // Brechungsindex (Glas ~1.5)
  thickness: 0.5,         // wie dick das Material ist
  clearcoat: 1,
  clearcoatRoughness: 0
});

// ============================================
// 6. MESH – Würfel
const cubeGeometry = new THREE.BoxGeometry(0.5, 0.5, 0.5);
const cubeMaterial = new THREE.MeshStandardMaterial({
  color: 0x0077ff,
  roughness: 0.5,
  metalness: 0.2,
});
const cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
cube.rotation.x = 0.1;
cube.rotation.y = 0.1;
cube.castShadow = true;
cube.position.x = -2; // leicht nach links verschoben
scene.add(cube);

// ============================================
// BODEN
// ============================================
const floorGeometry = new THREE.PlaneGeometry(5, 5);
const floorMaterial = new THREE.MeshStandardMaterial({
  color: 0x808080,
  roughness: 0.2,
  metalness: 0.0,
});

const floor = new THREE.Mesh(floorGeometry, floorMaterial);

// Plane standardmäßig senkrecht → wir legen sie flach
floor.rotation.x = -Math.PI / 2;

// Etwas unter die Objekte schieben
floor.position.y = -0.25;

// Schatten empfangen
floor.receiveShadow = true;

scene.add(floor);

// 6. MESH – TorusKnot
const knotGeometry = new THREE.TorusKnotGeometry(0.3, 0.1, 100, 16);

const knot = new THREE.Mesh(knotGeometry, knotMaterial);
knot.castShadow = true;
knot.position.x = 1; // leicht nach rechts verschoben
scene.add(knot);

// 7. LIGHTS
const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xffffff, 1);
directionalLight.position.set(2, 2, 2);
scene.add(directionalLight);

// Shadow Setup (erst nach Licht und Mesh)
renderer.shadowMap.enabled = true;
cube.castShadow = true;
directionalLight.castShadow = true;

// ============================================
// 8. RENDER LOOP
// ============================================
// For animation and continuous updates, we need a render loop
// This is similar to the draw() function in p5.js
function animate() {
  // Update the cube rotation for animation
  cube.rotation.x += 0.01;
  cube.rotation.y += 0.01;

  // Render the scene from the camera's perspective
  renderer.render(scene, camera);

  // Request the next frame (creates a loop)
  requestAnimationFrame(animate);
}

// Start the animation loop
animate();

// ============================================
// 9. HANDLE WINDOW RESIZE
// ============================================
// Update camera and renderer when window is resized
function onWindowResize() {
  // Update camera aspect ratio
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  controls.update();

  // Update renderer size
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
}

window.addEventListener("resize", onWindowResize);

