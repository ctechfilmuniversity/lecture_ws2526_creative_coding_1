import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import { GUI } from 'three/addons/libs/lil-gui.module.min.js';
import { RGBELoader } from 'three/addons/loaders/RGBELoader.js';



// Thanks to these generous folks for sharing free 3D models.
// Monkey - ChaosBlend https://www.cgtrader.com/designers/chaosblend?utm_source=credit&utm_source=credit_item_page
// Coconut tree - PANDORA-Land https://www.cgtrader.com/free-3d-models/plant/conifer/4-different-tree-coconut-palm-tree-on-beach
// Banana - WolFsamii   https://www.cgtrader.com/free-3d-models/scanned/various/banana-a0e9f2de-0622-477c-99a7-789f20e3fede


// SCENE
const scene = new THREE.Scene();
				scene.fog = new THREE.Fog( 0x90CDFF, -5, 250 );

const rgbeLoader = new RGBELoader();
rgbeLoader.load('/qwantani_sunset_puresky_2k.hdr', (texture) => {
  texture.mapping = THREE.EquirectangularReflectionMapping;

  scene.background = texture;    // visible background
  scene.environment = texture;   // lighting + reflections
});


//LIGHTING
const hemiLight = new THREE.HemisphereLight( 0xFFF4C5, 0x444444, 3 );
				hemiLight.position.set( 0, 100, 0 );
				scene.add( hemiLight );

				const dirLight = new THREE.DirectionalLight( 0xffffff, 1);
				dirLight.position.set( 0, 200, 100 );

				dirLight.castShadow = true;

				dirLight.shadow.mapSize.width = 2048;
				dirLight.shadow.mapSize.height = 2048;

				dirLight.shadow.camera.near = 1;
				dirLight.shadow.camera.far = 300;
				

				dirLight.shadow.camera.top = 80;
				dirLight.shadow.camera.bottom = - 80;
				dirLight.shadow.camera.left = - 80;
				dirLight.shadow.camera.right = 80;

				dirLight.shadow.bias = -0.001;
				scene.add( dirLight )



// CAMERA
const fov = 60;
const aspect = window.innerWidth / window.innerHeight;
const near = 0.1;
const far = 1000;
const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);
camera.position.set(-5, 6, 40);


// RENDERER
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({canvas, antialias: true});
renderer.setSize( window.innerWidth, window.innerHeight);

renderer.shadowMap.enabled = true;
renderer.shadowMap.type = THREE.PCFSoftShadowMap; 

//ORBIT CONTROL
const controls = new OrbitControls(camera, renderer.domElement);
controls.target.set(-3, 10, 0);
controls.update();

// GEOMETRY 

	// Banana Scene
const gltfLoader = new GLTFLoader();
gltfLoader.load('/models/model_monkey_banana_Scene.glb', (gltf) => {
  const bananaScene = gltf.scene;
  bananaScene.scale.set(5, 5, 5);

  bananaScene.traverse((child) => {
    if (child.isMesh) {
      child.castShadow = true;
      child.receiveShadow = true;
    }
});

  scene.add(bananaScene);

});

	// Banana
let mixer;
gltfLoader.load('/models/model_monkey_banana.glb', (gltf) => {
  const banana = gltf.scene;
  banana.scale.set(5, 5, 5);

  banana.traverse((child) => {
    if (child.isMesh) {
      child.castShadow = true;
      child.receiveShadow = true;
    }
});
  scene.add(banana);

  mixer = new THREE.AnimationMixer(banana);
  const clips = gltf.animations;
  const clip = THREE.AnimationClip.findByName(clips, 'Banana_Schwanken_Y');
  const action = mixer.clipAction(clip);
  action.play();

});

	// Floor Plane (Water)
const mesh = new THREE.Mesh( new THREE.PlaneGeometry( 700, 700 ), 
new THREE.MeshPhongMaterial( { color: 0x90CDFF, depthWrite: false } ) );
mesh.rotation.x = - Math.PI / 2;
mesh.receiveShadow = true;
mesh.position.y = -0.01;
scene.add( mesh );


//GUI - ANIMATION
const params = {
  animationSpeed: 1  
};
const gui = new GUI();
gui.add(params, 'animationSpeed', 0, 20).step(0.1).name('He loves to jiggle fast!');



const clock = new THREE.Clock();
function animate() {
  requestAnimationFrame(animate);

  const delta = clock.getDelta();
  if (mixer) mixer.update(delta * params.animationSpeed);

  controls.update();
  renderer.render(scene, camera);
}
animate();
