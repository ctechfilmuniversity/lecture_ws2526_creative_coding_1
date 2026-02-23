import * as THREE from 'three';
import * as C from 'cannon-es';
import { world } from './physics';

export const DIE_SIZE = 2.4;

export type DiceType = 'd2' | 'd4' | 'd6' | 'd8' | 'd10' | 'd12' | 'd20' | 'd100';

export interface Die {
  mesh: THREE.Mesh;
  body: any;
  getSpeed(): number;
  computeResult(): number;
}

function geometryToTrimesh(geometry: THREE.BufferGeometry): any {
  const pos = geometry.attributes.position.array as unknown as number[];
  let indices: number[] = [];
  
  if (geometry.index) {
    indices = Array.from(geometry.index.array as unknown as number[]);
  } else {
    indices = [];
    for (let i = 0; i < pos.length / 3; i++) {
      indices.push(i);
    }
  }
  
  return new C.Trimesh(pos, indices);
}

export function createDie(type: DiceType): Die {
  let geometry: THREE.BufferGeometry;
  const material = new THREE.MeshStandardMaterial({
    color: 0xff3366,
    roughness: 0.4,
    metalness: 0.8,
    flatShading: true,
  });

  switch (type) {
    case 'd2':
      geometry = new THREE.CylinderGeometry(DIE_SIZE, DIE_SIZE, 0.2 * DIE_SIZE, 32);
      break;
    case 'd4':
      geometry = new THREE.TetrahedronGeometry(DIE_SIZE);
      break;
    case 'd6':
      geometry = new THREE.BoxGeometry(DIE_SIZE, DIE_SIZE, DIE_SIZE);
      break;
    case 'd8':
      geometry = new THREE.OctahedronGeometry(DIE_SIZE);
      break;
    case 'd10': {
      geometry = new THREE.BufferGeometry();
      const H = 0.1055728;
      const vertices = new Float32Array([
        0.0, 1.0, 0.0,
        0.0, -1.0, 0.0,
        1.0, H, 0.0,
        0.309017, H, 0.951057,
        -0.809017, H, 0.587785,
        -0.809017, H, -0.587785,
        0.309017, H, -0.951057,
        0.809017, -H, 0.587785,
        -0.309017, -H, 0.951057,
        -1.0, -H, 0.0,
        -0.309017, -H, -0.951057,
        0.809017, -H, -0.587785
      ]);
      const indices = [
        0, 7, 2, 0, 3, 7,
        0, 8, 3, 0, 4, 8,
        0, 9, 4, 0, 5, 9,
        0, 10, 5, 0, 6, 10,
        0, 11, 6, 0, 2, 11,
        1, 7, 3, 1, 3, 8,
        1, 8, 4, 1, 4, 9,
        1, 9, 5, 1, 5, 10,
        1, 10, 6, 1, 6, 11,
        1, 11, 2, 1, 2, 7
      ];
      geometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3));
      geometry.setIndex(indices);
      geometry.scale(DIE_SIZE, DIE_SIZE, DIE_SIZE);
      geometry.computeVertexNormals();
      break;
    }
    case 'd12':
      geometry = new THREE.DodecahedronGeometry(DIE_SIZE);
      break;
    case 'd20':
      geometry = new THREE.IcosahedronGeometry(DIE_SIZE);
      break;
    case 'd100':
      geometry = new THREE.IcosahedronGeometry(DIE_SIZE, 3);
      break;
    default:
      geometry = new THREE.BoxGeometry(DIE_SIZE, DIE_SIZE, DIE_SIZE);
  }

  const mesh = new THREE.Mesh(geometry, material);
  mesh.castShadow = true;
  mesh.receiveShadow = true;

  const body = new C.Body({ mass: 1 });
  
  if (type === 'd6') {
    body.addShape(new C.Box(new C.Vec3(DIE_SIZE / 2, DIE_SIZE / 2, DIE_SIZE / 2)));
  } else if (type === 'd2') {
    body.addShape(new C.Cylinder(DIE_SIZE, DIE_SIZE, 0.2 * DIE_SIZE, 32));
  } else if (type === 'd100') {
    body.addShape(new C.Sphere(DIE_SIZE));
    body.angularDamping = 0.4;
    body.linearDamping = 0.1;
  } else {
    const trimesh = geometryToTrimesh(geometry);
    body.addShape(trimesh);
  }

  if (world) {
    world.addBody(body);
  }

  let finalResult: number | null = null;

  const die: Die = {
    mesh,
    body,
    getSpeed: () => {
      const v = die.body.velocity;
      return Math.sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    },
    computeResult: (): number => {
      if (finalResult === null) {
        const max = parseInt(type.replace('d', ''), 10);
        finalResult = Math.floor(Math.random() * max) + 1;
      }
      return finalResult;
    },
  };

  return die;
}