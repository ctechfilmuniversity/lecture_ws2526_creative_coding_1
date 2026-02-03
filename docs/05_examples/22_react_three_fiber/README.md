# Example 22: React Three Fiber

This example demonstrates how to create 3D scenes using React Three Fiber (R3F) - a React renderer for Three.js.

## Setup

1. Install dependencies:

```bash
npm install
```

2. Run the development server:

```bash
npm run dev
```

3. Open the URL shown in the terminal (usually `http://localhost:5173`)

## Concepts

### React Three Fiber Basics

- **Canvas**: The container that sets up WebGL renderer, scene, and camera
- **mesh**: 3D objects combining geometry and material
- **useFrame**: Hook that runs on every animation frame
- **useRef**: Access to underlying Three.js objects

### Three.js to R3F Translation

```javascript
// Three.js
const geometry = new THREE.BoxGeometry(1, 1, 1);
const material = new THREE.MeshStandardMaterial({ color: "blue" });
const cube = new THREE.Mesh(geometry, material);
scene.add(cube);

// React Three Fiber (equivalent)
<mesh>
  <boxGeometry args={[1, 1, 1]} />
  <meshStandardMaterial color="blue" />
</mesh>;
```

### Drei Library

Drei provides ready-to-use components:

- **OrbitControls**: Camera controls for orbiting, panning, zooming
- **Text**: 3D text rendering
- **Environment**: Environment maps for lighting/reflections

### React Integration

- State from React controls 3D scene properties
- Regular React UI alongside 3D canvas
- Props passed to 3D components like any React component

## File Structure

```
22_react_three_fiber/
├── index.html
├── package.json
├── vite.config.js
└── src/
    ├── main.jsx
    ├── index.css
    ├── App.jsx         # Main app with Canvas and controls
    ├── App.css
    └── components/
        ├── RotatingBox.jsx      # Animated rotating cube
        └── FloatingSphere.jsx   # Floating animated sphere
```

## Try It Out

- Use the color pickers to change object colors
- Adjust the rotation speed slider
- Drag to orbit the camera around the scene
- Scroll to zoom in/out

## Key Takeaways

1. **R3F uses JSX** for declarative 3D scene building
2. **Components are reusable** - create 3D objects like React components
3. **useFrame** replaces requestAnimationFrame for animations
4. **useRef** provides direct access to Three.js objects
5. **Drei** provides many useful pre-built components
6. **State integration** - React state can control 3D properties

## Resources

- [React Three Fiber Docs](https://r3f.docs.pmnd.rs/)
- [Drei Library](https://drei.docs.pmnd.rs/)
- [Three.js Docs](https://threejs.org/docs/)
