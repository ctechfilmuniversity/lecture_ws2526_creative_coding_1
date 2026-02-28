import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader.js";
import { FontLoader } from "three/examples/jsm/loaders/FontLoader.js";
import { TextGeometry } from "three/examples/jsm/geometries/TextGeometry.js";
import gsap from "gsap";


// SCENE & CAMERA

const scene = new THREE.Scene();
scene.background = new THREE.Color(0x202020);

const camera = new THREE.PerspectiveCamera(70, window.innerWidth/window.innerHeight, 0.1, 100);
camera.position.set(0,2,8);

// RENDERER

const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, antialias:true });
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setPixelRatio(Math.min(window.devicePixelRatio,2));
renderer.shadowMap.enabled = true;


// CONTROLS

const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;
controls.dampingFactor = 0.05;


// LIGHTS

const ambientLight = new THREE.AmbientLight(0xffffff,1.2);
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xffffff,2.5);
directionalLight.position.set(5,5,5);
directionalLight.castShadow = true;
scene.add(directionalLight);


// TorusKnot 

const knotMaterial = new THREE.MeshPhysicalMaterial({
  color:0xffffff,
  metalness:0,
  roughness:0.05,
  transmission:1,
  transparent:true,
  ior:1.5,
  thickness:0.5,
  clearcoat:1,
  clearcoatRoughness:0
});
const knotGeometry = new THREE.TorusKnotGeometry(3,0.15,100,16);
const knot = new THREE.Mesh(knotGeometry,knotMaterial);
knot.castShadow = true;
scene.add(knot);


// GLTF Loader

const gltfLoader = new GLTFLoader();

// Flower02
const flowerGroup02 = new THREE.Group();
scene.add(flowerGroup02);
gltfLoader.load("Blume02/blume02.glb", gltf=>{
  const model = gltf.scene;
  model.scale.set(1,1,1);
  model.position.set(0,0,0);
  model.traverse(c=>{if(c.isMesh){c.castShadow=true;c.receiveShadow=true;}});
  flowerGroup02.add(model);
});

// Flower1
const flowerGroup1 = new THREE.Group();
scene.add(flowerGroup1);

const flowerData = [
  { pos:new THREE.Vector3(-5,0,0), rot:new THREE.Euler(0,0,0) },
  { pos:new THREE.Vector3(-8,0,1), rot:new THREE.Euler(0,Math.PI/4,0) },
  { pos:new THREE.Vector3(3,0,-1), rot:new THREE.Euler(0,Math.PI/2,0) },
  { pos:new THREE.Vector3(1,0,1), rot:new THREE.Euler(0,Math.PI/3,0) },
  { pos:new THREE.Vector3(4,2,-2), rot:new THREE.Euler(0,-Math.PI/4,0) },
  { pos:new THREE.Vector3(-1,-2,4), rot:new THREE.Euler(0,-Math.PI/4,0) },
  { pos:new THREE.Vector3(-2,0,-3), rot:new THREE.Euler(0,-Math.PI/4,0) },
  { pos:new THREE.Vector3(2,0,3), rot:new THREE.Euler(0,-Math.PI/4,0) },
  { pos:new THREE.Vector3(3,-3,1), rot:new THREE.Euler(0,-Math.PI/4,0) },
  { pos:new THREE.Vector3(-5,-2,1), rot:new THREE.Euler(0,-Math.PI/4,0) },
  { pos:new THREE.Vector3(1,0,1), rot:new THREE.Euler(0,-Math.PI/4,0) }
];

gltfLoader.load("Blume_object/Blume_fuer_three_js.glb", gltf=>{
  const model = gltf.scene;
  flowerData.forEach(({pos,rot})=>{
    const clone = model.clone();
    clone.scale.set(0.5,0.5,0.5);
    clone.position.copy(pos);
    clone.rotation.copy(rot);
    clone.traverse(c=>{if(c.isMesh){c.castShadow=true;c.receiveShadow=true;}});
    flowerGroup1.add(clone);
  });
});


// Particle-System

const particleCount = 2000;
const particlesGeometry = new THREE.BufferGeometry();
const positions = [];
for(let i=0;i<particleCount;i++){
  const r = THREE.MathUtils.randFloat(2,10);
  const angle = THREE.MathUtils.randFloat(0,Math.PI*2);
  const y = THREE.MathUtils.randFloat(-0.3,0.3);
  positions.push(
    flowerGroup02.position.x + Math.cos(angle)*r,
    flowerGroup02.position.y + y,
    flowerGroup02.position.z + Math.sin(angle)*r
  );
}
particlesGeometry.setAttribute("position",new THREE.Float32BufferAttribute(positions,3));

let particleTexture = null;
try{ particleTexture = new THREE.TextureLoader().load("textures/circle.png"); }catch{}
const particlesMaterial = new THREE.PointsMaterial({
  color:0xffffff,
  size:0.06,
  map:particleTexture,
  transparent:true,
  blending:THREE.AdditiveBlending,
  depthWrite:false,
  alphaTest:0.001
});
const particles = new THREE.Points(particlesGeometry,particlesMaterial);
scene.add(particles);
const particleRotationSpeed = 0.01;


// 3D Text
let rotatingText = null;
const fontLoader = new FontLoader();
fontLoader.load("fonts/helvetiker_regular.typeface.json", font=>{
  const geom = new TextGeometry("Hi! Welcome to my brain.", { font, size:0.2, height:0.05, curveSegments:12 });
  const mat = new THREE.MeshStandardMaterial({ color:0xffffff });
  rotatingText = new THREE.Mesh(geom, mat);

  geom.computeBoundingBox();
  const centerX = (geom.boundingBox.max.x + geom.boundingBox.min.x)/2;
  const centerZ = (geom.boundingBox.max.z + geom.boundingBox.min.z)/2;

  rotatingText.position.set(
    knot.position.x - centerX,
    knot.position.y + 1,
    knot.position.z - centerZ
  );

  rotatingText.visible = false;
  scene.add(rotatingText);
});


// Kamera Ziele

const cameraTargets = {
  flowerGroup1:{position:new THREE.Vector3(0,2,8), lookAt:flowerGroup1.position},
  flowerGroup02:{position:new THREE.Vector3(0,2,5), lookAt:flowerGroup02.position},
  knot:{position:new THREE.Vector3(3,2,8), lookAt:knot.position},
};


// Kamera Bewegung

function moveCamera(target){
  controls.enableDamping=false;
  gsap.killTweensOf(camera.position);
  gsap.killTweensOf(controls.target);

  gsap.to(camera.position,{
    x:target.position.x,
    y:target.position.y,
    z:target.position.z,
    duration:1.5,
    ease:"power2.inOut",
    onUpdate:()=>controls.update(),
    onComplete:()=>controls.enableDamping=true
  });

  gsap.to(controls.target,{
    x:target.lookAt.x,
    y:target.lookAt.y,
    z:target.lookAt.z,
    duration:1.5,
    ease:"power2.inOut"
  });
}
// Buttons Events
document.getElementById("btnFlower1")?.addEventListener("click",()=>moveCamera(cameraTargets.flowerGroup1));
document.getElementById("btnFlower02")?.addEventListener("click",()=>moveCamera(cameraTargets.flowerGroup02));
document.getElementById("btnKnot")?.addEventListener("click",()=>moveCamera(cameraTargets.knot));

// Text Button → sichtbar + Orbit
let textOrbitRadius = 3.5;
let textOrbitAngle = 0;
document.getElementById("btnTextAnimate")?.addEventListener("click", ()=>{
  if(!rotatingText) return;
  rotatingText.visible = true;
  gsap.fromTo(rotatingText.scale, {x:0.1,y:0.1,z:0.1}, {x:1,y:1,z:1,duration:0.5,ease:"back.out(1.7)"});
});


// Animate Loop
function animate(){
  knot.rotation.x +=0.01;
  knot.rotation.y +=0.01;
  particles.rotation.y += particleRotationSpeed;

  if(rotatingText && rotatingText.visible){
    textOrbitAngle += 0.01;
    rotatingText.position.x = knot.position.x + Math.cos(textOrbitAngle)*textOrbitRadius;
    rotatingText.position.z = knot.position.z + Math.sin(textOrbitAngle)*textOrbitRadius;
    rotatingText.position.y = knot.position.y + 1;
  }

  controls.update();
  renderer.render(scene, camera);
  requestAnimationFrame(animate);
}
animate();


// Window Resize
window.addEventListener("resize", ()=>{
  camera.aspect=window.innerWidth/window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth,window.innerHeight);
  renderer.setPixelRatio(Math.min(window.devicePixelRatio,2));
});