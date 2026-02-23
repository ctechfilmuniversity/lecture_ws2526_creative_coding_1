import './style.css';
import * as THREE from 'three';
import { initPhysics, stepPhysics } from './physics';
import { createDie } from './diceGeometries';
import type { Die, DiceType } from './diceGeometries';
import { setupUI, showResult } from './ui';
import * as C from 'cannon-es';
import { DynamicAsciiEffect } from './asciiEffect';

let scene: THREE.Scene;
let camera: THREE.PerspectiveCamera;
let renderer: THREE.WebGLRenderer;
let effect: DynamicAsciiEffect;
let activeDie: Die | null = null;

const timer = new THREE.Timer();
timer.connect(document);

init();

function init() {
  scene = new THREE.Scene();
  scene.background = new THREE.Color(0x111111);

  camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 100);
  camera.position.set(0, 20, 0);
  camera.up.set(0, 0, -1);
  camera.lookAt(0, 0, 0);

  const ambientLight = new THREE.AmbientLight(0xffffff, 10);
  scene.add(ambientLight);

  const dirLight = new THREE.DirectionalLight(0xffffff, 10);
  dirLight.position.set(0, 20, -10);
  dirLight.castShadow = true;
  dirLight.shadow.mapSize.width = 2048;
  dirLight.shadow.mapSize.height = 2048;
  scene.add(dirLight);

  const planeGeometry = new THREE.PlaneGeometry(100, 100);
  const planeMaterial = new THREE.ShadowMaterial({ opacity: 0.6 });
  const planeMesh = new THREE.Mesh(planeGeometry, planeMaterial);
  planeMesh.rotation.x = -Math.PI / 2;
  planeMesh.receiveShadow = true;
  scene.add(planeMesh);

  renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.shadowMap.enabled = true;
  document.body.appendChild(renderer.domElement);

  //limited ascii chars for less visual noise
  effect = new DynamicAsciiEffect(renderer, ' .:-=+*#%@', { charSize: 6 });

  window.addEventListener('resize', onWindowResize);

  initPhysics();
  setupUI({ onRoll: rollDice });

  requestAnimationFrame(animate);
}
//Widow resizer
function onWindowResize() {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
  effect.setSize(window.innerWidth, window.innerHeight);
}

function rollDice(type: DiceType) {
  if (activeDie) {
    scene.remove(activeDie.mesh);
    if (activeDie.body.world) {
      activeDie.body.world.removeBody(activeDie.body);
    }
    activeDie = null;
  }

  const die = createDie(type);
  die.body.position.set(0, 5, 4);
  die.body.quaternion.setFromEuler(
    Math.random() * Math.PI,
    Math.random() * Math.PI,
    Math.random() * Math.PI
  );
  die.mesh.position.copy(die.body.position as unknown as THREE.Vector3);
  scene.add(die.mesh);
  activeDie = die;
  showResult(null);

  const force = new C.Vec3(
    (Math.random() - 0.5) * 8,
    -2,
    -8 - Math.random() * 6
  );
  die.body.applyImpulse(force, die.body.position);

  die.body.angularVelocity.set(
    Math.random() * 20 - 10,
    Math.random() * 20 - 10,
    Math.random() * 20 - 10
  );
}

function animate(timestamp: number) {
  requestAnimationFrame(animate);
  
  timer.update(timestamp);
  const dt = timer.getDelta();
  
  stepPhysics(dt);

  if (activeDie) {
    activeDie.mesh.position.set(
      activeDie.body.position.x,
      activeDie.body.position.y,
      activeDie.body.position.z
    );
    activeDie.mesh.quaternion.set(
      activeDie.body.quaternion.x,
      activeDie.body.quaternion.y,
      activeDie.body.quaternion.z,
      activeDie.body.quaternion.w
    );

    const speed = activeDie.getSpeed();
    if (speed <= 0.1) {
      const result = activeDie.computeResult();
      showResult(result);
    }
  }

  effect.render(scene, camera);
}