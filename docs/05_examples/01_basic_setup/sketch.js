/*
 * Example 01: Basic Setup
 *
 * This sketch demonstrates the fundamental structure of a p5.js program.
 *
 * Key concepts covered:
 * - The setup() function: runs once at the beginning
 * - The createCanvas() function: creates our drawing area
 * - Basic drawing commands: circle, rect, ellipse, line, triangle
 * - Colors with fill() and stroke()
 * - The coordinate system (0,0 is top-left)
 */

function setup() {
  // createCanvas(width, height) - creates our drawing area
  // Try changing these numbers!
  createCanvas(600, 400);

  // background(r, g, b) or background(grayscale) - fills the canvas
  background(240, 240, 245);

  // ---- Drawing basic shapes ----

  // Set fill color (the inside of shapes)
  // fill(red, green, blue) - values from 0-255
  fill(255, 100, 100); // A nice red

  // Set stroke color (the outline)
  stroke(50); // Dark gray outline
  strokeWeight(2); // Line thickness

  // Circle: circle(x, y, diameter)
  circle(100, 100, 80);

  // Rectangle: rect(x, y, width, height)
  fill(100, 200, 100); // Green
  rect(200, 60, 100, 80);

  // Ellipse: ellipse(x, y, width, height)
  fill(100, 100, 255); // Blue
  ellipse(400, 100, 120, 60);

  // Line: line(x1, y1, x2, y2)
  stroke(200, 100, 200); // Purple
  strokeWeight(4);
  line(50, 200, 550, 200);

  // Triangle: triangle(x1, y1, x2, y2, x3, y3)
  fill(255, 200, 100); // Orange
  stroke(50);
  strokeWeight(2);
  triangle(150, 350, 100, 280, 200, 280);

  // No fill - just outline
  noFill();
  stroke(0, 150, 150); // Teal
  strokeWeight(3);
  rect(300, 250, 100, 100);

  // No stroke - just fill
  fill(200, 100, 150);
  noStroke();
  circle(500, 300, 70);

  // Add some text
  fill(50);
  textSize(16);
  textAlign(CENTER);
  text("Welcome to p5.js!", width / 2, 380);
}

// Note: We don't need draw() for static images
// draw() is used for animation (runs continuously)
