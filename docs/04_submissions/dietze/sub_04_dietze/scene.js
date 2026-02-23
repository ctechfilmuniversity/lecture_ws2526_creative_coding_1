import * as THREE from 'three';
import GUI from 'lil-gui';

const canvas = document.querySelector('#canvasThree');
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true, alpha: true });
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));

const scene = new THREE.Scene();

const canvasBg = document.createElement('canvas');
canvasBg.width = 2;
canvasBg.height = 512;
const context = canvasBg.getContext('2d');
const gradient = context.createLinearGradient(0, 0, 0, 512);
gradient.addColorStop(0, '#0a0514');
gradient.addColorStop(0.5, '#5e175c');
gradient.addColorStop(1, '#11192b');
context.fillStyle = gradient;
context.fillRect(0, 0, 2, 512);
const bgTexture = new THREE.CanvasTexture(canvasBg);
bgTexture.colorSpace = THREE.SRGBColorSpace;
scene.background = bgTexture;

scene.fog = new THREE.FogExp2(0x11192b, 0.02);

const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 100);
camera.position.set(0, 2, 20);

const ambientLight = new THREE.AmbientLight(0xffffff, 0.4);
scene.add(ambientLight);

const directionalLight1 = new THREE.DirectionalLight(0x00ffff, 2.0);
directionalLight1.position.set(10, 15, 10);
scene.add(directionalLight1);

const directionalLight2 = new THREE.DirectionalLight(0xff007f, 3.0);
directionalLight2.position.set(-10, -10, -10);
scene.add(directionalLight2);

const pointLight = new THREE.PointLight(0xffaa00, 3.0, 30);
pointLight.position.set(0, 5, -5);
scene.add(pointLight);

const cloudGroup = new THREE.Group();

const cloudMaterial = new THREE.MeshPhysicalMaterial({
  color: 0xffffff,
  transmission: 1.0,
  opacity: 1.0,
  metalness: 0.1,
  roughness: 0.02,
  ior: 1.5,
  thickness: 2.5,
  specularIntensity: 1.0,
  clearcoat: 1.0,
  clearcoatRoughness: 0.02,
  dispersion: 3.0,
  iridescence: 1.0,
  iridescenceIOR: 1.3
});

const sphere1 = new THREE.Mesh(new THREE.SphereGeometry(2.5, 64, 64), cloudMaterial);
const sphere2 = new THREE.Mesh(new THREE.SphereGeometry(1.8, 64, 64), cloudMaterial);
sphere2.position.set(-2.5, -0.5, 0.5);
const sphere3 = new THREE.Mesh(new THREE.SphereGeometry(2.0, 64, 64), cloudMaterial);
sphere3.position.set(2.5, -0.2, -0.5);
const sphere4 = new THREE.Mesh(new THREE.SphereGeometry(1.5, 64, 64), cloudMaterial);
sphere4.position.set(0, 1.5, 0.8);
const sphere5 = new THREE.Mesh(new THREE.SphereGeometry(1.2, 64, 64), cloudMaterial);
sphere5.position.set(-1.5, 1.2, -0.8);

cloudGroup.add(sphere1, sphere2, sphere3, sphere4, sphere5);
cloudGroup.position.set(0, 8, 0);
scene.add(cloudGroup);

const groundGeo = new THREE.PlaneGeometry(150, 150);
const groundMat = new THREE.MeshStandardMaterial({ 
  color: 0x11192b, 
  roughness: 0.1, 
  metalness: 0.8 
});
const ground = new THREE.Mesh(groundGeo, groundMat);
ground.rotation.x = -Math.PI / 2;
ground.position.y = -10;
scene.add(ground);

const maxParticles = 25000;
const particlesGeo = new THREE.BufferGeometry();
const positions = new Float32Array(maxParticles * 3);
const velocities = new Float32Array(maxParticles);

for (let i = 0; i < maxParticles; i++) {
  positions[i * 3] = (Math.random() - 0.5) * 20;
  positions[i * 3 + 1] = 8 + (Math.random() - 0.5) * 15;
  positions[i * 3 + 2] = (Math.random() - 0.5) * 10;
  velocities[i] = 0.5 + Math.random();
}

particlesGeo.setAttribute('position', new THREE.BufferAttribute(positions, 3));
particlesGeo.setAttribute('velocity', new THREE.BufferAttribute(velocities, 1));

const particlesMat = new THREE.PointsMaterial({
  size: 0.08,
  color: 0x88ccff,
  transparent: true,
  opacity: 0.8,
  blending: THREE.AdditiveBlending,
  depthWrite: false
});

const particleSystem = new THREE.Points(particlesGeo, particlesMat);
particleSystem.geometry.setDrawRange(0, 8000);
scene.add(particleSystem);

const gui = new GUI();
const guiParams = {
  size: 0.08,
  color: 0x88ccff,
  speed: 0.05,
  count: 8000
};

gui.add(guiParams, 'size', 0.01, 0.3).name('Particle Size').onChange((value) => {
  particlesMat.size = value;
});

gui.addColor(guiParams, 'color').name('Particle Color').onChange((value) => {
  particlesMat.color.setHex(value);
});

gui.add(guiParams, 'speed', 0.01, 0.3).name('Falling Speed');

gui.add(guiParams, 'count', 100, maxParticles, 100).name('Particle Count').onChange((value) => {
  particleSystem.geometry.setDrawRange(0, value);
});

let targetX = 0;
const windowHalfX = window.innerWidth / 2;

document.addEventListener('mousemove', (event) => {
  const normalizedX = (event.clientX - windowHalfX) / windowHalfX;
  targetX = normalizedX * 15;
});

window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

function animate() {
  requestAnimationFrame(animate);

  cloudGroup.position.x += (targetX - cloudGroup.position.x) * 0.05;
  cloudGroup.position.y = 8 + Math.sin(Date.now() * 0.002) * 0.3;
  cloudGroup.rotation.y += 0.002;
  cloudGroup.rotation.z = Math.sin(Date.now() * 0.001) * 0.05;

  const posAttribute = particlesGeo.attributes.position;
  const velAttribute = particlesGeo.attributes.velocity;
  const currentDrawRange = particleSystem.geometry.drawRange.count;

  for (let i = 0; i < currentDrawRange; i++) {
    let y = posAttribute.getY(i);
    const vel = velAttribute.getX(i);

    if (y > -9.9) {
      y -= guiParams.speed * vel;
    } else {
      if (Math.random() < 0.02) {
        y = cloudGroup.position.y + (Math.random() - 0.5) * 2;
        posAttribute.setX(i, cloudGroup.position.x + (Math.random() - 0.5) * 6);
        posAttribute.setZ(i, (Math.random() - 0.5) * 6);
      }
    }

    posAttribute.setY(i, y);
  }

  posAttribute.needsUpdate = true;

  renderer.render(scene, camera);
}

animate();