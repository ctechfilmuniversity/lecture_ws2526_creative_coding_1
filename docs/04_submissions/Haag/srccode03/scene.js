import * as THREE from 'three';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import { Reflector } from 'three/examples/jsm/objects/Reflector.js';
import './style.css';

let scene, camera, renderer, controls;
let metaballSpheres = [];
let toruses = [];
let particles;

const clock = new THREE.Clock();
const bounds = 25;
const torusCount = 140;
const metaballCount = 110;

init();
animate();

function init() {

  scene = new THREE.Scene();
  scene.background = new THREE.Color(0x000000);

  createStudioEnvironment();
  createParticles(); 

  camera = new THREE.PerspectiveCamera(60, innerWidth / innerHeight, 0.1, 1000);
  camera.position.set(-20, 15, 220);

  renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.setSize(innerWidth, innerHeight);
  renderer.setPixelRatio(devicePixelRatio);
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  document.body.appendChild(renderer.domElement);

  controls = new OrbitControls(camera, renderer.domElement);
  controls.enableDamping = true;

  scene.add(new THREE.AmbientLight(0xffffff, 0.15));

  const dirLight = new THREE.DirectionalLight(0xffffff, 0.50);
  dirLight.position.set(0, 100, 50);
  scene.add(dirLight);

  // Spheres
  const speckledTexture = createSpeckledTexture(64, 80);

  // SPHERES und Sprenkles
  const metaballGeo = new THREE.SphereGeometry(4, 32, 32);

  for (let i = 0; i < metaballCount; i++) {

    const mat = new THREE.MeshPhysicalMaterial({
      color: 0xffffff,
      map: speckledTexture,          
      emissive: new THREE.Color().setHSL(Math.random(), 5, 0.2),
      emissiveIntensity: 0.2,
      roughness: 5,
      metalness: 1.4,
      envMapIntensity: 3
    });

    const sphere = new THREE.Mesh(metaballGeo, mat);

    sphere.position.set(
      (Math.random() - 0.5) * bounds * 2,
      50 + (Math.random() - 0.5) * 10,
      (Math.random() - 0.5) * bounds * 2
    );

    sphere.userData.velocity = new THREE.Vector3(
      (Math.random() - 0.5) * 0.25,
      (Math.random() - 0.5) * 0.25,
      (Math.random() - 0.5) * 0.25
    );

    metaballSpheres.push(sphere);
    scene.add(sphere);
  }

  // Donutzz
  const torusGeo = new THREE.TorusGeometry(2, 0.5, 16, 32);

  for (let i = 0; i < torusCount; i++) {

    const torusMat = new THREE.MeshPhysicalMaterial({
      color: new THREE.Color().setHSL(Math.random(), 0.6, 0.55),
      roughness: 0.35,
      metalness: 0.25,
      envMapIntensity: 1.5
    });

    const torus = new THREE.Mesh(torusGeo, torusMat);

    torus.position.set(
      (Math.random() - 0.5) * bounds * 2,
      (Math.random() - 0.5) * bounds * 2 + 10,
      (Math.random() - 0.5) * bounds * 2
    );

    torus.userData.velocity = new THREE.Vector3(
      (Math.random() - 0.5) * 0.1,
      (Math.random() - 0.5) * 0.1,
      (Math.random() - 0.5) * 0.1
    );

    toruses.push(torus);
    scene.add(torus);
  }

  // Reflector mit Helfelein
  const glassMirror = new Reflector(
    new THREE.PlaneGeometry(900, 900),
    {
      clipBias: 0.003,
      textureWidth: innerWidth * devicePixelRatio * 0.4,
      textureHeight: innerHeight * devicePixelRatio * 0.4,
      color: 0x777777
    }
  );

  glassMirror.rotation.x = -Math.PI / 2;
  glassMirror.position.y = -20;
  scene.add(glassMirror);

  // Glasiges 
  const frostedGlass = new THREE.Mesh(
    new THREE.PlaneGeometry(900, 900),
    new THREE.MeshPhysicalMaterial({
      color: 0xffffff,
      transparent: true,
      opacity: 0.25,
      roughness: 1,
      transmission: 0.7,
      thickness: 2,
      envMapIntensity: 2,
      clearcoat: 1,
      clearcoatRoughness: 1
    })
  );

  frostedGlass.rotation.x = -Math.PI / 2;
  frostedGlass.position.y = -19.9;
  scene.add(frostedGlass);

  const floorHelper = new THREE.Mesh(
    new THREE.PlaneGeometry(900, 900),
    new THREE.MeshBasicMaterial({ color: 0x050505 })
  );

  floorHelper.rotation.x = -Math.PI / 2;
  floorHelper.position.y = -22;
  scene.add(floorHelper);

  window.addEventListener('resize', onResize);
}

// Partikell
function createParticles() {

  const count = 3000;
  const positions = new Float32Array(count * 3);

  for (let i = 0; i < count; i++) {
    const i3 = i * 3;
    positions[i3]     = (Math.random() - 0.5) * 400;
    positions[i3 + 1] = Math.random() * 140;
    positions[i3 + 2] = (Math.random() - 0.5) * 400;
  }

  const geometry = new THREE.BufferGeometry();
  geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));

  // Kreise Adaption
  const size = 128;
  const canvas = document.createElement('canvas');
  canvas.width = size;
  canvas.height = size;

  const ctx = canvas.getContext('2d');

  const gradient = ctx.createRadialGradient(
    size / 2, size / 2, 0,
    size / 2, size / 2, size / 2
  );

  gradient.addColorStop(0, 'rgba(255,255,255,1)');
  gradient.addColorStop(0.4, 'rgba(255,255,255,0.6)');
  gradient.addColorStop(1, 'rgba(255,255,255,0)');

  ctx.fillStyle = gradient;
  ctx.fillRect(0, 0, size, size);

  const texture = new THREE.CanvasTexture(canvas);

  const material = new THREE.PointsMaterial({
    size: 0.6,                 
    map: texture,
    transparent: true,
    depthWrite: false,
    blending: THREE.AdditiveBlending,
    color: 0xffffff,
    sizeAttenuation: true
  });

  particles = new THREE.Points(geometry, material);
  scene.add(particles);
}

// Environment
function createStudioEnvironment() {

  const size = 1024;
  const canvas = document.createElement('canvas');
  canvas.width = size;
  canvas.height = size;
  const ctx = canvas.getContext('2d');

  ctx.fillStyle = '#050505';
  ctx.fillRect(0, 0, size, size);

  const topLight = ctx.createRadialGradient(size/2, size*0.15, 0, size/2, size*0.15, size*0.5);
  topLight.addColorStop(0, 'rgba(255,255,255,0.25)');
  topLight.addColorStop(1, 'rgba(255,255,255,0)');
  ctx.fillStyle = topLight;
  ctx.fillRect(0, 0, size, size);

  const texture = new THREE.CanvasTexture(canvas);
  texture.mapping = THREE.EquirectangularReflectionMapping;

  scene.environment = texture;
}

// Punkte (Funktion)
function createSpeckledTexture(size = 64, dotCount = 80) {
  const canvas = document.createElement('canvas');
  canvas.width = size;
  canvas.height = size;
  const ctx = canvas.getContext('2d');

  // Base
  ctx.fillStyle = 'white';
  ctx.fillRect(0, 0, size, size);

  // Dots
  ctx.fillStyle = 'black';
  for (let i = 0; i < dotCount; i++) {
    const x = Math.random() * size;
    const y = Math.random() * size;
    const r = Math.random() * 1.2 + 0.3;
    ctx.beginPath();
    ctx.arc(x, y, r, 0, Math.PI * 2);
    ctx.fill();
  }

  return new THREE.CanvasTexture(canvas);
}

function onResize() {
  camera.aspect = innerWidth / innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(innerWidth, innerHeight);
}

function animate() {

  requestAnimationFrame(animate);

  metaballSpheres.forEach(s => {
    s.position.add(s.userData.velocity);
  });

  toruses.forEach(t => {
    t.position.add(t.userData.velocity);
    t.rotation.x += 0.01;
    t.rotation.y += 0.01;
  });

  // Animation und finito
  if (particles) {
    particles.rotation.y += 0.0008;
  }

  controls.update();
  renderer.render(scene, camera);
}