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

import * as THREE from "three";

// ============================================
// 1. SCENE
// ============================================
// The scene is a container that holds all 3D objects, lights, etc.
const scene = new THREE.Scene();

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
camera.position.z = 1;

// ============================================
// 3. RENDERER
// ============================================
// The renderer draws the scene to the canvas
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });

// Set the size of the renderer to match the window
renderer.setSize(window.innerWidth, window.innerHeight);

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
const material = new THREE.MeshNormalMaterial();

// ============================================
// 6. MESH
// ============================================
// A Mesh combines geometry and material into a renderable object
const cube = new THREE.Mesh(geometry, material);

// Optional: Rotate the cube slightly to see it's 3D
cube.rotation.x = 0.1;
cube.rotation.y = 0.1;

// Add the cube to the scene
scene.add(cube);

// ============================================
// 7. RENDER LOOP
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
// 8. HANDLE WINDOW RESIZE
// ============================================
// Update camera and renderer when window is resized
function onWindowResize() {
  // Update camera aspect ratio
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();

  // Update renderer size
  renderer.setSize(window.innerWidth, window.innerHeight);
}

window.addEventListener("resize", onWindowResize);
