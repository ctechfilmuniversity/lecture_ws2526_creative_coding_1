/*
 * Example 20: Loading 3D Models (glTF)
 *
 * This example demonstrates loading external 3D models using GLTFLoader.
 * Models are loaded asynchronously - we use callbacks to handle them when ready.
 *
 * Key concepts covered:
 * - GLTFLoader: Import and use the loader
 * - Asynchronous loading: Models load in the background
 * - Callbacks: Handle success, progress, and errors
 * - Model structure: Understanding gltf.scene hierarchy
 * - Scaling: Adjusting model size
 * - AnimationMixer: Playing animations from glTF files
 */

import * as THREE from "three";
import { OrbitControls } from "three/addons/controls/OrbitControls.js";
import { GLTFLoader } from "three/addons/loaders/GLTFLoader.js";

// ============================================
// SCENE SETUP
// ============================================
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x222222);

const camera = new THREE.PerspectiveCamera(
  75,
  window.innerWidth / window.innerHeight,
  0.1,
  1000
);
camera.position.set(0, 0, 5);

const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);

// ============================================
// LIGHTS
// ============================================
const ambientLight = new THREE.AmbientLight(0xffffff, 0.6);
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8);
directionalLight.position.set(5, 5, 5);
scene.add(directionalLight);

// ============================================
// CONTROLS
// ============================================
const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;

// ============================================
// LOADING MANAGER (Optional)
// ============================================
const loadingManager = new THREE.LoadingManager();
loadingManager.onLoad = () => {
  console.log("All models loaded!");
  document.getElementById("loading").style.display = "none";
};

loadingManager.onProgress = (url, loaded, total) => {
  console.log(`Loading: ${(loaded / total * 100).toFixed(0)}%`);
};

loadingManager.onError = (url) => {
  console.error("Error loading:", url);
};

// ============================================
// GLTF LOADER
// ============================================
const gltfLoader = new GLTFLoader(loadingManager);

// Variable to store animation mixer (declared outside callback)
let mixer = null;

// ============================================
// LOAD MODEL
// ============================================
// Using a free glTF model from the Khronos Group sample assets
// Duck model: https://github.com/KhronosGroup/glTF-Sample-Models/tree/master/2.0/Duck

gltfLoader.load(
  // Path to model (using a CDN-hosted version)
  "https://raw.githubusercontent.com/KhronosGroup/glTF-Sample-Models/master/2.0/Duck/glTF-Binary/Duck.glb",
  
  // Success callback - runs when model loads successfully
  (gltf) => {
    console.log("Model loaded!", gltf);
    
    // The loaded model structure:
    // gltf.scene - The root scene containing all objects
    // gltf.animations - Array of animation clips (if any)
    // gltf.cameras - Array of cameras (if any)
    // gltf.scenes - Array of scenes (if any)
    
    // Get the model (it's in gltf.scene)
    const model = gltf.scene;
    
    // Scale the model (Duck model is quite small)
    model.scale.set(2, 2, 2);
    
    // Position the model
    model.position.y = -1;
    
    // Add to scene
    scene.add(model);
    
    // ---- Handle Animations (if model has them) ----
    if (gltf.animations && gltf.animations.length > 0) {
      console.log("Model has animations:", gltf.animations.length);
      
      // Create AnimationMixer for this model
      mixer = new THREE.AnimationMixer(model);
      
      // Play the first animation
      const action = mixer.clipAction(gltf.animations[0]);
      action.play();
      
      console.log("Animation playing!");
    }
  },
  
  // Progress callback - runs while loading
  (progress) => {
    const percent = (progress.loaded / progress.total * 100).toFixed(0);
    document.getElementById("loading").textContent = `Loading model... ${percent}%`;
    console.log("Progress:", percent + "%");
  },
  
  // Error callback - runs if loading fails
  (error) => {
    console.error("Error loading model:", error);
    document.getElementById("loading").textContent = "Error loading model. Check console.";
  }
);

// ============================================
// CLOCK FOR ANIMATION
// ============================================
const clock = new THREE.Clock();

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
  
  const deltaTime = clock.getDelta();
  
  // Update animation mixer if it exists
  // (only runs if model has loaded and has animations)
  if (mixer) {
    mixer.update(deltaTime);
  }
  
  controls.update();
  renderer.render(scene, camera);
}

animate();

/*
 * KEY INSIGHTS:
 * 
 * 1. Asynchronous Loading
 *    - gltfLoader.load() returns immediately
 *    - Model loads in the background
 *    - Callbacks handle completion
 * 
 * 2. Callback Structure
 *    - Success: (gltf) => { ... }
 *    - Progress: (progress) => { ... }
 *    - Error: (error) => { ... }
 * 
 * 3. Model Structure
 *    - gltf.scene: The root object (usually what you want)
 *    - gltf.animations: Array of animation clips
 *    - May contain nested groups, meshes, cameras, lights
 * 
 * 4. Scaling Models
 *    - Models come in various sizes
 *    - Use model.scale.set(x, y, z) to adjust
 *    - Check model dimensions in console
 * 
 * 5. AnimationMixer
 *    - Must be updated in render loop
 *    - Requires deltaTime for smooth playback
 *    - Declare outside callback to access in animate()
 * 
 * 6. Scope Pattern
 *    - Declare mixer = null outside callback
 *    - Assign inside callback when model loads
 *    - Check if(mixer) before updating
 */
