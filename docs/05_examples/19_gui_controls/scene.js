/*
 * Example 19: GUI Controls with lil-gui
 *
 * This example demonstrates using lil-gui to create interactive debug interfaces
 * for tweaking three.js scene parameters in real-time.
 *
 * Key concepts covered:
 * - Installing and importing lil-gui
 * - Creating GUI controllers for object properties
 * - Using params object pattern for custom variables
 * - onChange callbacks for custom behavior
 * - Different controller types (slider, color, checkbox, button)
 */

import * as THREE from "three";
import { OrbitControls } from "three/addons/controls/OrbitControls.js";
import { GUI } from "lil-gui";

// ============================================
// SCENE SETUP
// ============================================
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x222222);

const camera = new THREE.PerspectiveCamera(
  75,
  window.innerWidth / window.innerHeight,
  0.1,
  100
);
camera.position.z = 5;

const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);

// ============================================
// LIGHTS
// ============================================
const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8);
directionalLight.position.set(2, 2, 2);
scene.add(directionalLight);

// ============================================
// GEOMETRY
// ============================================
const geometry = new THREE.BoxGeometry(1, 1, 1);
const material = new THREE.MeshStandardMaterial({ color: 0x50ffc0 });
const cube = new THREE.Mesh(geometry, material);
scene.add(cube);

// ============================================
// GUI SETUP
// ============================================
const gui = new GUI();
gui.title("Scene Controls");

// ---- Example 1: Controlling Object Properties ----
// We can directly control properties of three.js objects
gui.add(cube.position, "x").min(-3).max(3).step(0.1).name("Position X");
gui.add(cube.position, "y").min(-3).max(3).step(0.1).name("Position Y");
gui.add(cube.position, "z").min(-3).max(3).step(0.1).name("Position Z");

gui.add(cube.rotation, "x").min(0).max(Math.PI * 2).step(0.01).name("Rotation X");
gui.add(cube.rotation, "y").min(0).max(Math.PI * 2).step(0.01).name("Rotation Y");

// ---- Example 2: Material Properties ----
// Material properties are detected automatically
gui.add(material, "wireframe").name("Wireframe");

// ---- Example 3: Using Params Object Pattern ----
// For custom variables, wrap them in an object
const params = {
  cubeSize: 1,
  color: "#50ffc0",
  speed: 0.01,
  reset: () => {
    cube.position.set(0, 0, 0);
    cube.rotation.set(0, 0, 0);
    params.cubeSize = 1;
    params.color = "#50ffc0";
    cube.scale.set(1, 1, 1);
    material.color.setHex(0x50ffc0);
    gui.updateDisplay(); // Refresh GUI to show updated values
  }
};

gui.add(params, "cubeSize").min(0.5).max(2).step(0.1).name("Cube Size")
  .onChange((value) => {
    // onChange callback: runs when slider changes
    cube.scale.set(value, value, value);
  });

gui.addColor(params, "color").name("Cube Color")
  .onChange((value) => {
    // Color picker automatically detects color type
    material.color.setHex(value.replace("#", "0x"));
  });

gui.add(params, "speed").min(0).max(0.05).step(0.001).name("Rotation Speed");

// Button: Functions automatically become buttons
gui.add(params, "reset").name("Reset Scene");

// ---- Example 4: Nested Folders ----
// Organize controls into folders
const lightFolder = gui.addFolder("Lights");
lightFolder.add(ambientLight, "intensity").min(0).max(2).step(0.1);
lightFolder.add(directionalLight, "intensity").min(0).max(2).step(0.1);
lightFolder.add(directionalLight.position, "x").min(-5).max(5).step(0.1);
lightFolder.add(directionalLight.position, "y").min(-5).max(5).step(0.1);
lightFolder.add(directionalLight.position, "z").min(-5).max(5).step(0.1);

// ============================================
// CONTROLS
// ============================================
const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;

// ============================================
// WINDOW RESIZE
// ============================================
window.addEventListener("resize", () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

// ============================================
// ANIMATION LOOP
// ============================================
function animate() {
  requestAnimationFrame(animate);

  // Rotate cube based on GUI speed parameter
  cube.rotation.y += params.speed;

  controls.update();
  renderer.render(scene, camera);
}

animate();

/*
 * KEY INSIGHTS:
 * 
 * 1. gui.add(object, 'property')
 *    - Directly modifies object properties
 *    - Automatically detects type (number, boolean, etc.)
 * 
 * 2. Params Object Pattern
 *    - Wrap custom variables in an object
 *    - Allows GUI to track and modify them
 *    - Common pattern in creative coding
 * 
 * 3. onChange Callbacks
 *    - Runs when GUI value changes
 *    - Perfect for triggering side effects
 *    - Uses arrow function syntax
 * 
 * 4. Controller Types
 *    - Numbers → Slider
 *    - Booleans → Checkbox
 *    - Colors → Color picker
 *    - Functions → Button
 * 
 * 5. Method Chaining
 *    - .min().max().step().name().onChange()
 *    - Each method returns the controller
 *    - Allows fluent configuration
 */
