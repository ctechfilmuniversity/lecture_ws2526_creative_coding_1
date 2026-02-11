/*
 * RotatingBox Component
 *
 * This component demonstrates:
 * - Creating a 3D mesh with geometry and material
 * - Using useRef to access the Three.js object
 * - Using useFrame for animation (runs every frame)
 * - Receiving props for customization
 *
 * In R3F, Three.js concepts map to JSX:
 * - new THREE.Mesh() → <mesh>
 * - new THREE.BoxGeometry() → <boxGeometry>
 * - new THREE.MeshStandardMaterial() → <meshStandardMaterial>
 */

import { useRef } from "react";
import { useFrame } from "@react-three/fiber";

function RotatingBox({
  position = [0, 0, 0],
  color = "#ff6b6b",
  speed = 0.01,
}) {
  // useRef gives us direct access to the Three.js mesh object
  // This is similar to how we used refs in vanilla Three.js
  const meshRef = useRef();

  // useFrame runs on every frame (like requestAnimationFrame)
  // It receives the state (containing camera, scene, etc.) and delta time
  useFrame((state, delta) => {
    if (meshRef.current) {
      // Rotate the mesh
      meshRef.current.rotation.x += speed;
      meshRef.current.rotation.y += speed * 1.5;
    }
  });

  return (
    // mesh combines geometry and material into a renderable object
    // The ref prop connects our ref to the actual Three.js object
    <mesh ref={meshRef} position={position}>
      {/* 
        boxGeometry creates a cube shape
        args corresponds to constructor arguments: [width, height, depth]
      */}
      <boxGeometry args={[1, 1, 1]} />

      {/* 
        meshStandardMaterial is a physically-based material
        It responds to lights in the scene
      */}
      <meshStandardMaterial color={color} metalness={0.3} roughness={0.4} />
    </mesh>
  );
}

export default RotatingBox;
