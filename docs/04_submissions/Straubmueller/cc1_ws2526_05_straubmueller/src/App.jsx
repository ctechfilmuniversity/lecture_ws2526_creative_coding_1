/*CREDITS --------------------------
- All the furniture is downloaded via BlenderKit. Thanks to everyone who provided the models. Cat and Walls/Floor are modeled by me.
- Big thanks to the Epic Agency for heavily inspiring me with their super cute project Moments of Happiness—Cat. https://moments.epic.net/#cat
- My final thanks go to Nugget, the cat and pain in the a** who inspired, supported, and slowed me down in this project. 
*/

import React, { useEffect, useRef, useState } from "react";
import { Canvas, useFrame, useThree } from "@react-three/fiber";
import { useGLTF } from "@react-three/drei";
import * as THREE from "three";


//CAT ----------------------------

function Cat({ onAngryTrigger }) {
  const { camera, mouse } = useThree();
  const { scene } = useGLTF("/Cat.glb");

  const groupRef = useRef();
  const squashDuration = useRef(0);
  const hasTriggered = useRef(false);

  const browsRef = useRef(null);
  const eyeLRefs = useRef([]);
  const eyeRRefs = useRef([]);
  const pupilLRef = useRef(null);
  const pupilRRef = useRef(null);

  const pupilLBase = useRef(new THREE.Vector3());
  const pupilRBase = useRef(new THREE.Vector3());

  useEffect(() => {
    camera.lookAt(0, 0.3, 0);
  }, [camera]);

  useEffect(() => {
    eyeLRefs.current = [];
    eyeRRefs.current = [];

    scene.traverse((child) => {
      if (!child.isMesh) return;

      child.castShadow = false;
      child.receiveShadow = false;

      if (child.material?.map) {
        child.material = new THREE.MeshBasicMaterial({
          map: child.material.map,
        });
        child.material.toneMapped = false;
      }

      if (child.name === "Brows") browsRef.current = child;
      if (child.name.startsWith("EyesYellow_l"))
        eyeLRefs.current.push(child);
      if (child.name.startsWith("EyesYellow_r"))
        eyeRRefs.current.push(child);

      if (child.name === "Pupil_l") {
        pupilLRef.current = child;
        pupilLBase.current.copy(child.position);
      }

      if (child.name === "Pupil_r") {
        pupilRRef.current = child;
        pupilRBase.current.copy(child.position);
      }
    });
  }, [scene]);

  useFrame((state, delta) => {
    if (!groupRef.current) return;

    const vector = new THREE.Vector3(mouse.x, mouse.y, 0.5);
    vector.unproject(camera);
    const dir = vector.sub(camera.position).normalize();
    const distance = -camera.position.z / dir.z;

    const worldMouse = camera.position
      .clone()
      .add(dir.multiplyScalar(distance));

    const catPosition = new THREE.Vector3();
    groupRef.current.getWorldPosition(catPosition);
    catPosition.y += 0.17;

    const dist = worldMouse.distanceTo(catPosition);

    const radius = 0.7;
    let proximity = 1 - dist / radius;
    proximity = THREE.MathUtils.clamp(proximity, 0, 1);
    proximity *= proximity;

    const faceProximity = THREE.MathUtils.clamp(proximity * 2.4, 0, 1);
    const bodyProximity = THREE.MathUtils.clamp(
      (proximity - 0.2) * 1.1,
      0,
      1
    );

   // ANGRY TRIGGER ----------------------------

    const threshold = 0.6;

    if (bodyProximity > threshold) {
      squashDuration.current += delta;

      if (squashDuration.current > 3 && !hasTriggered.current) {
        hasTriggered.current = true;
        onAngryTrigger?.();
      }
    } else {
      squashDuration.current = 0;
      hasTriggered.current = false;
    }

    // SCALE -----------------------------

    const maxSquash = 0.7;
    const horizontalSpread = 0.4;

    const targetScaleY = 1 - bodyProximity * maxSquash;
    const targetScaleX = 1 + bodyProximity * horizontalSpread;
    const targetScaleZ = 1 + bodyProximity * horizontalSpread;

    groupRef.current.scale.lerp(
      new THREE.Vector3(targetScaleX, targetScaleY, targetScaleZ),
      0.08
    );

    // MORPH ----------------------------

    const morphIntensity = faceProximity;

    if (browsRef.current) {
      const index =
        browsRef.current.morphTargetDictionary?.["Brows_down"];
      if (index !== undefined) {
        browsRef.current.morphTargetInfluences[index] =
          THREE.MathUtils.lerp(
            browsRef.current.morphTargetInfluences[index],
            morphIntensity,
            0.3
          );
      }
    }

    // LEFT EYE -------------------------
eyeLRefs.current.forEach((mesh) => {
  const index =
    mesh.morphTargetDictionary?.["EyesYellow_l_down"];
  if (index !== undefined) {
    mesh.morphTargetInfluences[index] =
      THREE.MathUtils.lerp(
        mesh.morphTargetInfluences[index],
        morphIntensity,
        0.4
      );
  }
});

// RIGHT EYE -----------------------------
eyeRRefs.current.forEach((mesh) => {
  const index =
    mesh.morphTargetDictionary?.["EyesYellow_r_down"];
  if (index !== undefined) {
    mesh.morphTargetInfluences[index] =
      THREE.MathUtils.lerp(
        mesh.morphTargetInfluences[index],
        morphIntensity,
        0.4
      );
  }
});

    // PUPILS ---------------------------------

    const maxOffset = 0.003;
    const offsetHorizontal = -mouse.x * maxOffset;
    const offsetVertical = mouse.y * maxOffset;

    if (pupilLRef.current) {
      pupilLRef.current.position.z =
        pupilLBase.current.z + offsetHorizontal;
      pupilLRef.current.position.y =
        pupilLBase.current.y + offsetVertical;
    }

    if (pupilRRef.current) {
      pupilRRef.current.position.z =
        pupilRBase.current.z + offsetHorizontal;
      pupilRRef.current.position.y =
        pupilRBase.current.y + offsetVertical;
    }

    // PUPIL - scale ------------------------------

    const scaleValue = THREE.MathUtils.lerp(1, 0.65, faceProximity);

    if (pupilLRef.current) {
      pupilLRef.current.scale.setScalar(scaleValue);
    }

    if (pupilRRef.current) {
      pupilRRef.current.scale.setScalar(scaleValue);
    }
  });

  return (
    <group ref={groupRef} rotation={[0, -Math.PI / 2, 0]}>
      <primitive object={scene} />
    </group>
  );

  
}

  // ENVIRONMENT MODEL ----------------------------

function EnvironmentModel() {
  const { scene } = useGLTF("/Environment.glb");

  useEffect(() => {
    scene.traverse((child) => {
      if (!child.isMesh) return;

      if (child.material?.map) {
        child.material = new THREE.MeshBasicMaterial({
          map: child.material.map,
        });
        child.material.toneMapped = false;
      }
    });
  }, [scene]);

  return (
    <group rotation={[0, -Math.PI / 2, 0]}>
      <primitive object={scene} />
    </group>
  );
}

// POPUP ----------------------------------

function Popup({ type, onClose }) {
  const imageSrc =
    type === "intro"
      ? "/260223_CC1_img_Text-01.png"
      : "/260223_CC1_img_Text-02.png";

  return (
    <div style={overlayStyle}>
      <div style={popupStyle(type)}>
        <img src={imageSrc} alt="popup" style={{ width: "100%" }} />
        <button onClick={onClose} style={closeStyle}>
          ✕
        </button>
      </div>
    </div>
  );
}

const overlayStyle = {
  position: "fixed",
  inset: 0,
  background: "rgba(0,0,0,0.6)",
  display: "flex",
  justifyContent: "center",
  alignItems: "center",
  zIndex: 1000,
};

const popupStyle = (type) => ({
  position: "relative",
  width: type === "angry" ? "800px" : "600px",
  maxWidth: "90vw",
});

const closeStyle = {
  position: "absolute",
  top: "20px",
  right: "20px",
  background: "transparent",
  border: "none",
  fontSize: "32px",
  cursor: "pointer",
  color: "black",
};

//  APP (POPUP) ---------------------------

export default function App() {
  const [popup, setPopup] = useState("intro");

  return (
    <>
      <Canvas
        style={{ width: "100vw", height: "100vh" }}
        camera={{ position: [0, 0.2, 1], fov: 49 }}
        gl={{
          outputColorSpace: THREE.SRGBColorSpace,
          toneMapping: THREE.NoToneMapping,
        }}
      >
        <color attach="background" args={["#081120"]} />

        <EnvironmentModel />
        <Cat onAngryTrigger={() => setPopup("angry")} />
      </Canvas>

      {popup && (
        <Popup
          type={popup}
          onClose={() => setPopup(null)}
        />
      )}
    </>
  );
}