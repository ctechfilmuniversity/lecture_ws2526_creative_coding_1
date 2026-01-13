/*
 * Example 11: 3D Basics in p5.js
 *
 * p5.js can render 3D graphics using WEBGL mode :)
 *
 * KEY DIFFERENCES FROM 2D:
 * - Use createCanvas(w, h, WEBGL) for 3D
 * - Origin (0,0,0) is at CENTER of canvas (not top-left!)
 * - Z-axis: positive comes toward you, negative goes away
 *
 * 3D PRIMITIVES:
 * - box(width, height, depth)
 * - sphere(radius)
 * - cylinder(radius, height)
 * - cone(radius, height)
 * - torus(ring radius, tube radius)
 * - plane(width, height)
 *
 * TRANSFORMATIONS:
 * - translate(x, y, z) - move the origin
 * - rotateX(), rotateY(), rotateZ() - rotate around axes
 * - scale() - change size
 * - push() / pop() - save/restore transformation state
 */

let angle = 0;

function setup() {
  createCanvas(700, 500, WEBGL); // Enable 3D mode
}

function draw() {
  background(30);

  // Add lights for 3D effect
  ambientLight(60);
  directionalLight(255, 255, 255, 0, 0, -1);
  pointLight(255, 200, 200, 200, -200, 200);

  // ---- Central rotating cube ----

  push(); // Save transformation state

  // Rotate based on angle (animation)
  rotateX(angle * 0.5);
  rotateY(angle);

  // Set material color
  fill(100, 150, 255);
  stroke(255);
  strokeWeight(1);

  // Draw a box (cube)
  box(100);

  pop(); // Restore transformation state

  // ---- Orbiting sphere ----

  push();

  // Orbit around center
  rotateY(angle * 2);
  translate(200, 0, 0); // Move out from center

  fill(255, 100, 150);
  noStroke();
  sphere(30);

  pop();

  // ---- Row of shapes at the back ----

  push();
  translate(0, 0, -200); // Move backward in Z

  // Cylinder
  push();
  translate(-200, 100, 0);
  rotateX(PI / 2); // Rotate to stand upright
  fill(100, 255, 150);
  cylinder(40, 100);
  pop();

  // Cone
  push();
  translate(-50, 100, 0);
  rotateX(PI); // Point upward
  fill(255, 200, 100);
  cone(50, 100);
  pop();

  // Torus (donut)
  push();
  translate(100, 100, 0);
  rotateX(angle);
  fill(200, 100, 255);
  torus(40, 15);
  pop();

  // Plane
  push();
  translate(230, 100, 0);
  rotateY(angle);
  fill(255, 255, 100);
  plane(80, 80);
  pop();

  pop();

  // ---- Floor grid ----

  push();
  translate(0, 150, 0);
  rotateX(PI / 2);

  stroke(100);
  strokeWeight(1);
  noFill();

  // Draw grid lines
  for (let i = -300; i <= 300; i += 50) {
    line(i, -300, i, 300);
    line(-300, i, 300, i);
  }

  pop();

  // ---- UI Text (2D overlay) ----
  // Switch to 2D for text
  push();

  // Reset transformations for 2D text
  translate(-width / 2, -height / 2, 0); // Move to top-left corner

  fill(255);
  noStroke();
  textSize(14);
  text("3D Basics in p5.js - Drag mouse to rotate view", 20, 30);
  text("Primitives: box, sphere, cylinder, cone, torus, plane", 20, 50);

  pop();

  // Update animation angle
  angle += 0.01;

  // Enable mouse-based camera rotation
  orbitControl();
}

/*
 * UNDERSTANDING THE 3D COORDINATE SYSTEM:
 *
 *        +Y (up)
 *         |
 *         |
 *         |_______ +X (right)
 *        /
 *       /
 *      +Z (toward you)
 *
 * In WEBGL mode:
 * - Origin (0,0,0) is at CENTER of canvas
 * - X increases to the right
 * - Y increases DOWNWARD (same as 2D)
 * - Z increases toward the viewer
 *
 * TRANSFORMATIONS:
 * - Transformations are CUMULATIVE
 * - Use push()/pop() to isolate transformations
 * - Order matters! translate then rotate ≠ rotate then translate
 *
 * CHALLENGES:
 * 1. Add more shapes and arrange them
 * 2. Make shapes orbit around each other
 * 3. Change colors based on position
 * 4. Create a simple solar system
 */
