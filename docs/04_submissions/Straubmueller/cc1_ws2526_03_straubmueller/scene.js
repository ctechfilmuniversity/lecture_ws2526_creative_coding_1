import * as THREE from 'three';
import { RGBELoader } from 'three/examples/jsm/loaders/RGBELoader.js';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';


const scene = new THREE.Scene();

// Render -----

const canvas = document.getElementById('canvasThree');
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setClearColor(0xFFCFFA);
renderer.physicallyCorrectLights = true;
renderer.outputColorSpace = THREE.SRGBColorSpace;
renderer.toneMapping = THREE.ACESFilmicToneMapping;


//Camera -----

const camera = new THREE.PerspectiveCamera(
  160,
  window.innerWidth / window.innerHeight,
  0.1,
  300
);
camera.position.z = 1.5
const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;
controls.dampingFactor = 0.05;

//Fog -----

scene.fog = new THREE.Fog(0xFFCFFA, 0.2, 7);

// HDR Environment

new RGBELoader()
  .load('/citrus_orchard_road_puresky_2k.hdr', function (texture) {
    texture.mapping = THREE.EquirectangularReflectionMapping;
    scene.environment = texture; // lighting + reflections
    // NOT setting scene.background → HDR invisible
  });



//Geometry -----

const baseMat = new THREE.MeshStandardMaterial({
  color: 0xD74A00,
  roughness: 0.1,
  metalness: 0.2,
});

const shapes = [
  //new THREE.BoxGeometry(1, 1, 1),
  //new THREE.SphereGeometry(0.6, 48, 48),
  new THREE.OctahedronGeometry(0.7),
  new THREE.TorusGeometry(0.5, 0.2, 16, 64),
];

function placeShape(geometry, x, y, scale = 1) {
const mesh = new THREE.Mesh(geometry, baseMat);
mesh.position.set(x, y, 0);
mesh.scale.setScalar(scale);
scene.add(mesh);
}

//grid layout -----
const spacing = 1.8;

function createTile(offsetX = 0, offsetZ = 0) {
  const group = new THREE.Group();
  group.name = "tile";

  for (let row = -2; row <= 2; row++) {
    for (let col = -2; col <= 2; col++) {
      const geo = shapes[Math.floor(Math.random() * shapes.length)];
      const scale = 0.8 + Math.random() * 0.4;

      const mesh = new THREE.Mesh(geo, baseMat);
      mesh.position.set(col * spacing, row * spacing, 0);
      mesh.scale.setScalar(scale);
      mesh.rotation.y = Math.random() * Math.PI;

      if (geo.type === "TorusGeometry") {
  mesh.rotation.x = Math.PI / 2;}

      group.add(mesh);

    }
  }


  group.position.x = offsetX;
  group.position.z = offsetZ;
  scene.add(group);
}

const tileSize = spacing*7;

for (let x = 0; x <= 0; x++) {
  for (let z = 0; z <= 3; z++) {
    createTile(x * tileSize, -z * tileSize * .1);
  }
}


// Lights -----

scene.add(new THREE.HemisphereLight(0xffffff, 0xdcd6ff, 0.8));


const fill = new THREE.DirectionalLight(0xffffff, 0.3);
fill.position.set(-3, 2, 2);
scene.add(fill);

const ambient = new THREE.AmbientLight(0xffffff, 0.3);
scene.add(ambient);

// Render -----

function animate() {
  requestAnimationFrame(animate);
scene.children.forEach(child => {
    if (child.name === "tile") {
      child.children.forEach(mesh => {
        mesh.rotation.y += 0.01; // spin speed
      });
    }
  });

  controls.update();
  renderer.render(scene, camera);
}
 animate();