/*
 * FloatingSphere Component
 *
 * This component demonstrates:
 * - Using useFrame with state.clock for time-based animation
 * - Creating smooth floating motion with sine functions
 * - Different geometry (sphere) and material properties
 * - Accessing Three.js state through useFrame
 */

import { useRef } from "react";
import { useFrame } from "@react-three/fiber";

function FloatingSphere({ position = [0, 0, 0], color = "#4ecdc4" }) {
  const meshRef = useRef();

  // Store the initial Y position
  const initialY = position[1];

  useFrame((state) => {
    if (meshRef.current) {
      // state.clock.elapsedTime gives us the total time since start
      // Using Math.sin creates a smooth oscillating motion
      const time = state.clock.elapsedTime;

      // Float up and down
      meshRef.current.position.y = initialY + Math.sin(time * 2) * 0.3;

      // Gentle rotation
      meshRef.current.rotation.y = time * 0.5;

      // Subtle scale pulsing
      const scale = 1 + Math.sin(time * 3) * 0.05;
      meshRef.current.scale.set(scale, scale, scale);
    }
  });

  return (
    <mesh ref={meshRef} position={position}>
      {/* 
        sphereGeometry creates a sphere
        args: [radius, widthSegments, heightSegments]
        More segments = smoother sphere
      */}
      <sphereGeometry args={[0.7, 32, 32]} />

      {/* 
        Using different material properties for a glossy look
      */}
      <meshStandardMaterial color={color} metalness={0.8} roughness={0.1} />
    </mesh>
  );
}

export default FloatingSphere;
