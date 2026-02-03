/*
 * Example 22: React Three Fiber
 *
 * This example demonstrates how to create 3D scenes using React Three Fiber (R3F).
 * R3F is a React renderer for Three.js that allows you to build 3D scenes
 * using familiar React patterns like components, props, and hooks.
 *
 * Key Concepts:
 * - Canvas: The container for the 3D scene (replaces WebGLRenderer setup)
 * - mesh: A 3D object combining geometry and material
 * - useFrame: A hook that runs on every frame (like requestAnimationFrame)
 * - useRef: Used to get direct access to Three.js objects
 * - Drei: A helper library with pre-built components (OrbitControls, Text, etc.)
 */

import { useState } from "react";
import { Canvas } from "@react-three/fiber";
import { OrbitControls, Text, Environment } from "@react-three/drei";
import RotatingBox from "./components/RotatingBox.jsx";
import FloatingSphere from "./components/FloatingSphere.jsx";
import "./App.css";

function App() {
  // State for controlling the scene from React UI
  const [boxColor, setBoxColor] = useState("#ff6b6b");
  const [sphereColor, setSphereColor] = useState("#4ecdc4");
  const [rotationSpeed, setRotationSpeed] = useState(0.01);

  return (
    <div className="app">
      {/* 
        Control Panel - Regular React UI 
        This demonstrates how R3F integrates with standard React components
      */}
      <div className="controls">
        <h2>React Three Fiber</h2>

        <div className="control-group">
          <label>Box Color</label>
          <input
            type="color"
            value={boxColor}
            onChange={(e) => setBoxColor(e.target.value)}
          />
        </div>

        <div className="control-group">
          <label>Sphere Color</label>
          <input
            type="color"
            value={sphereColor}
            onChange={(e) => setSphereColor(e.target.value)}
          />
        </div>

        <div className="control-group">
          <label>Rotation Speed: {rotationSpeed.toFixed(3)}</label>
          <input
            type="range"
            min="0"
            max="0.05"
            step="0.001"
            value={rotationSpeed}
            onChange={(e) => setRotationSpeed(parseFloat(e.target.value))}
          />
        </div>

        <p className="hint">Drag to orbit • Scroll to zoom</p>
      </div>

      {/* 
        Canvas - The 3D Scene Container
        
        The Canvas component:
        - Creates a WebGL renderer
        - Sets up a scene and camera
        - Handles resize automatically
        - Provides context for all child components
      */}
      <Canvas camera={{ position: [3, 3, 3], fov: 50 }}>
        {/* 
          Lighting
          In R3F, lights are just components like any other
        */}
        <ambientLight intensity={0.5} />
        <directionalLight position={[5, 5, 5]} intensity={1} />

        {/* 
          3D Objects as Components
          Props are passed just like regular React components
        */}
        <RotatingBox
          position={[-1.5, 0, 0]}
          color={boxColor}
          speed={rotationSpeed}
        />

        <FloatingSphere position={[1.5, 0, 0]} color={sphereColor} />

        {/* 
          Text Component from Drei
          Drei provides many useful pre-built components
        */}
        <Text
          position={[0, -2, 0]}
          fontSize={0.3}
          color="#333"
          anchorX="center"
          anchorY="middle"
        >
          Creative Coding I
        </Text>

        {/* 
          OrbitControls from Drei
          Allows camera rotation, panning, and zooming
        */}
        <OrbitControls
          enableDamping
          dampingFactor={0.05}
          minDistance={2}
          maxDistance={10}
        />

        {/* 
          Environment from Drei
          Adds environment lighting/reflections
        */}
        <Environment preset="city" />
      </Canvas>
    </div>
  );
}

export default App;
