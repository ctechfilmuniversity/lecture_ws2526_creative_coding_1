import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import { GUI } from "lil-gui";

const scene = new THREE.Scene();
scene.background = new THREE.Color(0x07070A);

const camera = new THREE.PerspectiveCamera(75,window.innerWidth/window.innerHeight,0.1,100);
camera.position.z = 5;

const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);

const cubeGeometry = new THREE.BoxGeometry();
const glassMaterial = new THREE.MeshPhysicalMaterial({color: 0x07070A,transparent: true, opacity: 0.7,transmission: 1,clearcoat: 1,clearcoatRoughness: 0,reflectivity: 0.2,});
const cube = new THREE.Mesh(cubeGeometry, glassMaterial);
scene.add(cube);

const bulbPositions = [{ x: 3.0, y: 0, z: 0.0 },
  { x: 0.927, y: 0, z: 2.853 },
  { x: -2.427, y: 0, z: 1.763 },
  { x: -2.427, y: 0, z: -1.763 },
  { x: 0.927, y: 0, z: -2.853 },
];

const bulbs = [];
const lights = [];

bulbPositions.forEach((pos, i) => {
  const bulbGeo = new THREE.SphereGeometry(0.3, 32, 32);
  const bulbMat = new THREE.MeshStandardMaterial({color: 0xffffaa,emissive: 0xffffaa, emissiveIntensity: 2,});

  const bulb = new THREE.Mesh(bulbGeo, bulbMat);
  bulb.position.set(pos.x, pos.y, pos.z);
  scene.add(bulb);
  bulbs.push(bulb);

  const pointLight = new THREE.PointLight(0xffffaa, 3, 20, 2);
  pointLight.position.set(pos.x, pos.y, pos.z);
  scene.add(pointLight);
  lights.push(pointLight);
});

const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;

const gui = new GUI();
const params = { 
bg_lightness: 0,
};


lights.forEach((_, i) => {
  params["bulb" + i] = 0;
  gui
    .add(params, "bulb" + i)
    .min(0)
    .max(1)
    .step(0.01)
    .name("Bulb " + (i + 1));
});

window.addEventListener("resize", () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

function animate() {
  requestAnimationFrame(animate);

  cube.rotation.x += 0.01;
  cube.rotation.y += 0.01;

  lights.forEach((light, i) => {light.intensity = params["bulb" + i];bulbs[i].material.emissiveIntensity = params["bulb" + i];});

  controls.update();
  renderer.render(scene, camera);
}
animate();
