/*
 * Example 12: Abstract Geometric Scene
 *
 * Inspired by geometric artists:
 * - Piet Mondrian (grids, primary colors)
 * - Wassily Kandinsky (circles, composition)
 * - Sol LeWitt (systematic, rule-based art)
 *
 * This scene demonstrates how to build an abstract 3D composition
 * using algorithmic thinking and loops.
 *
 * Drag to rotate view | Scroll to zoom
 */

let shapes = [];
let time = 0;

function setup() {
  createCanvas(800, 600, WEBGL);
  colorMode(HSB, 360, 100, 100, 100);

  generateScene();
}

function generateScene() {
  shapes = [];

  // ---- Grid of pillars (Mondrian-inspired) ----

  let gridSize = 5;
  let spacing = 80;

  for (let i = -gridSize; i <= gridSize; i++) {
    for (let j = -gridSize; j <= gridSize; j++) {
      // Skip some positions randomly for visual interest
      if (random() < 0.3) continue;

      // Vary height based on position
      let height = map(noise(i * 0.3, j * 0.3), 0, 1, 30, 200);

      // Color based on position (Mondrian primary colors)
      let col;
      let r = random();
      if (r < 0.2) col = color(0, 90, 95); // Red
      else if (r < 0.4) col = color(45, 90, 95); // Yellow
      else if (r < 0.6) col = color(220, 90, 80); // Blue
      else col = color(0, 0, 95); // White

      shapes.push({
        type: "box",
        x: i * spacing,
        y: 100 - height / 2,
        z: j * spacing,
        w: 25,
        h: height,
        d: 25,
        color: col,
        rotSpeed: random(-0.01, 0.01),
      });
    }
  }

  // ---- Floating spheres (Kandinsky-inspired) ----

  for (let i = 0; i < 25; i++) {
    let angle = random(TWO_PI);
    let radius = random(100, 350);
    let height = random(-150, -50);

    shapes.push({
      type: "sphere",
      x: cos(angle) * radius,
      y: height,
      z: sin(angle) * radius,
      size: random(10, 40),
      color: color(random(360), 70, 90, 80),
      orbitSpeed: random(0.005, 0.02),
      orbitRadius: radius,
      orbitAngle: angle,
      floatOffset: random(TWO_PI),
    });
  }

  // ---- Geometric rings (Sol LeWitt-inspired) ----

  for (let i = 0; i < 3; i++) {
    let ringRadius = 200 + i * 80;
    let numTori = 8 + i * 4;

    for (let j = 0; j < numTori; j++) {
      let angle = (TWO_PI / numTori) * j;

      shapes.push({
        type: "torus",
        x: cos(angle) * ringRadius,
        y: -180 - i * 60,
        z: sin(angle) * ringRadius,
        ringRadius: 15,
        tubeRadius: 5,
        color: color(180 + i * 60, 60, 90, 70),
        rotSpeed: 0.02 * (i + 1),
        baseAngle: angle,
      });
    }
  }
}

function draw() {
  background(0, 0, 15);

  // Lighting
  ambientLight(40);
  directionalLight(0, 0, 100, 1, 1, -1);
  pointLight(0, 0, 100, 0, -300, 0);

  // Camera orbit
  orbitControl();

  // Floor plane
  push();
  translate(0, 150, 0);
  rotateX(HALF_PI);
  noStroke();
  fill(0, 0, 20);
  plane(1000, 1000);
  pop();

  // Draw floor grid
  push();
  translate(0, 149, 0);
  rotateX(HALF_PI);
  stroke(0, 0, 30);
  strokeWeight(1);
  noFill();
  for (let i = -500; i <= 500; i += 50) {
    line(i, -500, i, 500);
    line(-500, i, 500, i);
  }
  pop();

  // Draw all shapes
  for (let shape of shapes) {
    push();

    if (shape.type === "box") {
      translate(shape.x, shape.y, shape.z);
      rotateY(time * shape.rotSpeed);

      fill(shape.color);
      stroke(0, 0, 0, 50);
      strokeWeight(0.5);
      box(shape.w, shape.h, shape.d);
    } else if (shape.type === "sphere") {
      // Orbital motion
      shape.orbitAngle += shape.orbitSpeed;
      let floatY = sin(time * 2 + shape.floatOffset) * 20;

      translate(
        cos(shape.orbitAngle) * shape.orbitRadius,
        shape.y + floatY,
        sin(shape.orbitAngle) * shape.orbitRadius
      );

      fill(shape.color);
      noStroke();
      sphere(shape.size);
    } else if (shape.type === "torus") {
      translate(shape.x, shape.y, shape.z);
      rotateY(shape.baseAngle);
      rotateX(time * shape.rotSpeed);
      rotateZ(time * shape.rotSpeed * 0.5);

      fill(shape.color);
      noStroke();
      torus(shape.ringRadius, shape.tubeRadius);
    }

    pop();
  }

  // Central structure
  push();
  translate(0, -100, 0);
  rotateY(time * 0.2);

  // Nested wireframe cubes
  stroke(0, 0, 80);
  strokeWeight(1);
  noFill();
  for (let i = 5; i > 0; i--) {
    rotateY(time * 0.1 * i);
    rotateX(time * 0.05 * i);
    box(40 * i);
  }
  pop();

  // Update time
  time += 0.02;

  // 2D overlay text
  push();
  translate(-width / 2 + 20, -height / 2 + 30, 0);
  fill(0, 0, 80);
  textSize(14);
  text(
    "Geometric Scene | Drag to rotate | Scroll to zoom | Press R to regenerate",
    0,
    0
  );
  pop();
}

function keyPressed() {
  if (key === "r" || key === "R") {
    generateScene();
  }
}

/*
 * DESIGN PRINCIPLES APPLIED:
 *
 * 1. REPETITION WITH VARIATION
 *    - Grid of pillars with varying heights
 *    - Multiple spheres with different sizes/colors
 *
 * 2. COLOR HARMONY
 *    - Limited palette inspired by Mondrian
 *    - HSB color mode for easy manipulation
 *
 * 3. HIERARCHICAL COMPOSITION
 *    - Ground plane as base
 *    - Pillars as middle ground
 *    - Floating spheres and rings above
 *
 * 4. MOVEMENT & TIME
 *    - Orbiting spheres
 *    - Rotating elements
 *    - Floating animations
 *
 * CHALLENGES:
 * 1. Add your own shape types
 * 2. Make shapes respond to mouse position
 * 3. Add sound reactivity
 * 4. Create a different artistic style (e.g., all circles)
 */
