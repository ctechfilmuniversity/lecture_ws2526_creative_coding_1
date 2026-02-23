import * as C from 'cannon-es';
import type { Die } from './diceGeometries';

export let world: C.World;

export function initPhysics(): void {
  world = new C.World({
    gravity: new C.Vec3(0, -9.82, 0),
  });

  const ground = new C.Body({ mass: 0 });
  const plane = new C.Plane();
  ground.addShape(plane);
  ground.quaternion.setFromEuler(-Math.PI / 2, 0, 0);
  world.addBody(ground);

  // wall distances based on camera view 
  const cameraHeight = 20;
  const fov = 45; // degrees
  const vFOV = (fov * Math.PI) / 180; 
  const visibleZ = 2 * Math.tan(vFOV / 2) * cameraHeight;
  const aspect = window.innerWidth / window.innerHeight;
  const visibleX = visibleZ * aspect;

  const padding = 2; //wall distance 
  const wallDistanceX = visibleX / 2 - padding;
  const wallDistanceZ = visibleZ / 2 - padding;

  const leftWall = new C.Body({ mass: 0 });
  leftWall.addShape(new C.Plane());
  leftWall.position.set(-wallDistanceX, 0, 0);
  leftWall.quaternion.setFromEuler(0, Math.PI / 2, 0);
  world.addBody(leftWall);

  const rightWall = new C.Body({ mass: 0 });
  rightWall.addShape(new C.Plane());
  rightWall.position.set(wallDistanceX, 0, 0);
  rightWall.quaternion.setFromEuler(0, -Math.PI / 2, 0);
  world.addBody(rightWall);

  const backWall = new C.Body({ mass: 0 });
  backWall.addShape(new C.Plane());
  backWall.position.set(0, 0, -wallDistanceZ);
  world.addBody(backWall);

  const frontWall = new C.Body({ mass: 0 });
  frontWall.addShape(new C.Plane());
  frontWall.position.set(0, 0, wallDistanceZ);
  frontWall.quaternion.setFromEuler(0, Math.PI, 0);
  world.addBody(frontWall);
}

export function stepPhysics(delta: number): void {
  world.step(1 / 60, delta, 3);
}

export function addDieToWorld(die: Die): void {
  world.addBody(die.body);
}