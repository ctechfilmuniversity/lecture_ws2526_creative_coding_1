# Example 13: three.js Basic Setup

This example demonstrates the fundamental structure of a three.js scene.

## Setup Instructions

### Prerequisites

- Node.js installed (with npm)
- Verify installation: `node -v` and `npm -v`

### Installation Steps

1. **Navigate to this directory:**

   ```bash
   cd 13_threejs_basics
   ```

2. **Install dependencies:**

   ```bash
   npm install
   ```

   This will install:

   - `three` - The three.js 3D graphics library
   - `vite` - Development server and build tool

3. **Start the development server:**

   ```bash
   npm run dev
   ```

4. **Open your browser:**

   - The terminal will show a local URL (usually `http://localhost:5173`)
   - Open this URL in your browser
   - You should see a rotating cube!

5. **Stop the server:**
   - Press `CTRL+C` in the terminal

## Key Concepts

### 1. Scene

The scene is a container that holds all 3D objects, lights, and other elements.

```js
const scene = new THREE.Scene();
```

### 2. Camera

The camera defines the point of view. We use `PerspectiveCamera` which mimics human vision.

```js
const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);
camera.position.z = 1;
```

### 3. Renderer

The renderer draws the scene to the canvas using WebGL.

```js
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
```

### 4. Geometry

Geometry defines the shape of 3D objects.

```js
const geometry = new THREE.BoxGeometry(0.5, 0.5, 0.5);
```

### 5. Material

Material defines the appearance of objects.

```js
const material = new THREE.MeshNormalMaterial();
```

### 6. Mesh

A mesh combines geometry and material into a renderable object.

```js
const cube = new THREE.Mesh(geometry, material);
scene.add(cube);
```

### 7. Render Loop

For animation, we need a continuous render loop (similar to `draw()` in p5.js).

```js
function animate() {
  cube.rotation.x += 0.01;
  renderer.render(scene, camera);
  requestAnimationFrame(animate);
}
animate();
```

## Coordinate System

- **X-axis**: Left/Right (positive = right)
- **Y-axis**: Up/Down (positive = up)
- **Z-axis**: Toward/Away from camera (positive = toward camera)

## Files

- `index.html` - HTML structure with canvas element
- `scene.js` - Main three.js code
- `style.css` - Basic styling
- `package.json` - Project configuration and dependencies

## Next Steps

Try modifying the code:

- Change the cube size: `new THREE.BoxGeometry(width, height, depth)`
- Change the material: `new THREE.MeshStandardMaterial({ color: 0xff0000 })`
- Add more objects to the scene
- Experiment with camera position: `camera.position.set(x, y, z)`
