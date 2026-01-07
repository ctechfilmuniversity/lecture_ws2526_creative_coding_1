/*
 * Example 09: Mouse Interaction
 *
 * p5.js provides several ways to interact with the mouse:
 *
 * Variables (updated every frame):
 * - mouseX, mouseY: current mouse position
 * - pmouseX, pmouseY: previous frame mouse position
 * - mouseIsPressed: true if any mouse button is pressed
 *
 * Event Functions (called when something happens):
 * - mousePressed(): called once when button pressed
 * - mouseReleased(): called once when button released
 * - mouseMoved(): called when mouse moves (button not pressed)
 * - mouseDragged(): called when mouse moves while pressed
 *
 * This sketch creates a simple drawing tool :)
 */

let brushColor;
let brushSize = 20;

function setup() {
  createCanvas(700, 500);
  background(240);

  // Initial brush color
  brushColor = color(100, 150, 255);

  drawUI();
}

function draw() {
  // Draw when mouse is pressed
  if (mouseIsPressed) {
    // Only draw in the canvas area (not UI)
    if (mouseY > 60) {
      noStroke();
      fill(brushColor);

      // Draw a circle at mouse position
      circle(mouseX, mouseY, brushSize);

      // Connect to previous position for smooth lines
      // Using lerp to interpolate between points
      let d = dist(mouseX, mouseY, pmouseX, pmouseY);
      if (d > 1) {
        for (let i = 0; i < d; i++) {
          let x = lerp(pmouseX, mouseX, i / d);
          let y = lerp(pmouseY, mouseY, i / d);
          circle(x, y, brushSize);
        }
      }
    }
  }

  // Update UI continuously for mouse position display
  drawMousePosition();
}

function drawUI() {
  // Top bar background
  fill(50);
  noStroke();
  rect(0, 0, width, 55);

  // Color palette
  let colors = [
    color(255, 100, 100), // Red
    color(255, 200, 100), // Orange
    color(255, 255, 100), // Yellow
    color(100, 255, 100), // Green
    color(100, 200, 255), // Light Blue
    color(100, 100, 255), // Blue
    color(200, 100, 255), // Purple
    color(255, 100, 200), // Pink
    color(50, 50, 50), // Black
    color(255, 255, 255), // White
  ];

  for (let i = 0; i < colors.length; i++) {
    fill(colors[i]);
    stroke(255);
    strokeWeight(2);
    rect(10 + i * 40, 10, 35, 35, 5);
  }

  // Size controls
  fill(255);
  noStroke();
  textSize(12);
  text("Size:", 430, 32);

  // Size buttons
  let sizes = [10, 20, 40, 60];
  for (let i = 0; i < sizes.length; i++) {
    fill(80);
    stroke(255);
    strokeWeight(1);
    rect(470 + i * 40, 10, 35, 35, 5);

    fill(255);
    noStroke();
    circle(487 + i * 40, 27, sizes[i] / 3);
  }

  // Clear button
  fill(200, 80, 80);
  stroke(255);
  rect(640, 10, 50, 35, 5);
  fill(255);
  noStroke();
  textAlign(CENTER, CENTER);
  text("Clear", 665, 27);
  textAlign(LEFT, TOP);

  // Current brush indicator
  fill(brushColor);
  stroke(255);
  strokeWeight(2);
  circle(620, 27, 25);
}

function drawMousePosition() {
  // Show mouse coordinates
  fill(50);
  noStroke();
  rect(0, height - 25, 150, 25);
  fill(255);
  textSize(12);
  text("x: " + mouseX + "  y: " + mouseY, 10, height - 8);
}

function mousePressed() {
  // Check if clicking on color palette
  if (mouseY < 50) {
    // Color buttons
    if (mouseX >= 10 && mouseX < 410) {
      let colorIndex = floor((mouseX - 10) / 40);
      let colors = [
        color(255, 100, 100),
        color(255, 200, 100),
        color(255, 255, 100),
        color(100, 255, 100),
        color(100, 200, 255),
        color(100, 100, 255),
        color(200, 100, 255),
        color(255, 100, 200),
        color(50, 50, 50),
        color(255, 255, 255),
      ];
      if (colorIndex < colors.length) {
        brushColor = colors[colorIndex];
        drawUI();
      }
    }

    // Size buttons
    let sizes = [10, 20, 40, 60];
    for (let i = 0; i < sizes.length; i++) {
      if (mouseX >= 470 + i * 40 && mouseX < 505 + i * 40) {
        brushSize = sizes[i];
      }
    }

    // Clear button
    if (mouseX >= 640 && mouseX < 690) {
      background(240);
      drawUI();
    }
  }
}

/*
 * CHALLENGES:
 * 1. Add more colors to the palette
 * 2. Add an eraser tool (hint: draw with background color)
 * 3. Make the brush leave a trail with fading opacity
 * 4. Add keyboard shortcuts for colors (press 'r' for red, etc.)
 */
