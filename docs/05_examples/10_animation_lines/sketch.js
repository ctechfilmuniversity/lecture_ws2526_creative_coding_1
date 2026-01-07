/*
 * Example 10: Animation with Lines
 *
 * This example demonstrates algorithmic thinking through animation.
 * Based on the slides' "Lines" example. You can see other examples in the slides.
 *
 * ALGORITHM BREAKDOWN:
 * 1. Start with random positions for line endpoints
 * 2. Each frame, draw a line
 * 3. Move endpoints in their current direction
 * 4. Add small random variation to movement
 * 5. When hitting a border, reverse direction
 * 6. Slowly change color over time
 *
 * Click to restart with new random starting positions!
 */

// Line endpoint positions
let x1, y1; // Start point
let x2, y2; // End point

// Movement directions (1 or -1)
let dirX1 = 1;
let dirY1 = 1;
let dirX2 = 1;
let dirY2 = 1;

// Movement speed
let speed = 2;

// Color variables
let hue = 0;
let saturation = 80;

function setup() {
  createCanvas(600, 500);
  colorMode(HSB, 360, 100, 100, 100);
  background(0, 0, 10);

  // Initialize with random positions
  resetPositions();
}

function resetPositions() {
  // Random starting positions
  x1 = random(50, width - 50);
  y1 = random(50, height - 50);
  x2 = random(50, width - 50);
  y2 = random(50, height - 50);

  // Random starting directions
  dirX1 = random() > 0.5 ? 1 : -1;
  dirY1 = random() > 0.5 ? 1 : -1;
  dirX2 = random() > 0.5 ? 1 : -1;
  dirY2 = random() > 0.5 ? 1 : -1;

  // Random starting hue
  hue = random(360);
}

function draw() {
  // Semi-transparent background for trail effect
  // Comment this out for no fading, or adjust alpha for different effects
  // background(0, 0, 10, 5);

  // ---- Draw the line ----

  stroke(hue, saturation, 90, 80);
  strokeWeight(1);
  line(x1, y1, x2, y2);

  // ---- Move endpoints ----

  // Base movement
  x1 += dirX1 * speed;
  y1 += dirY1 * speed;
  x2 += dirX2 * speed * 0.8; // Slightly slower for variation
  y2 += dirY2 * speed * 1.2; // Slightly faster for variation

  // Add small random variation
  x1 += random(-1, 1);
  y1 += random(-1, 1);
  x2 += random(-1, 1);
  y2 += random(-1, 1);

  // ---- Check boundaries and reverse direction ----

  // Point 1
  if (x1 <= 0 || x1 >= width) {
    dirX1 *= -1;
    x1 = constrain(x1, 0, width);
  }
  if (y1 <= 0 || y1 >= height) {
    dirY1 *= -1;
    y1 = constrain(y1, 0, height);
  }

  // Point 2
  if (x2 <= 0 || x2 >= width) {
    dirX2 *= -1;
    x2 = constrain(x2, 0, width);
  }
  if (y2 <= 0 || y2 >= height) {
    dirY2 *= -1;
    y2 = constrain(y2, 0, height);
  }

  // ---- Update color ----

  hue += 0.5; // Slowly shift through colors
  if (hue > 360) hue = 0;

  // ---- Draw info ----

  // Background for text
  noStroke();
  fill(0, 0, 10);
  rect(0, height - 30, width, 30);

  // Text info
  fill(0, 0, 80);
  textSize(12);
  text(
    "Point 1: (" +
      nf(x1, 1, 0) +
      ", " +
      nf(y1, 1, 0) +
      ")  " +
      "Point 2: (" +
      nf(x2, 1, 0) +
      ", " +
      nf(y2, 1, 0) +
      ")  " +
      "Hue: " +
      nf(hue, 1, 0) +
      "  |  Click to restart",
    10,
    height - 10
  );
}

function mousePressed() {
  // Clear and restart
  background(0, 0, 10);
  resetPositions();
}

/*
 * ALGORITHMIC THINKING - The Sub-Problems:
 *
 * 1. LINE DRAWING
 *    Each frame, draw a line with start (x1,y1) and end (x2,y2)
 *
 * 2. MOVEMENT
 *    Each endpoint moves in a direction (dirX, dirY)
 *    Position += direction * speed
 *
 * 3. VARIATION
 *    Add small random offset to make movement organic
 *
 * 4. BOUNDARY COLLISION
 *    If position < 0 or position > canvas size:
 *      Reverse direction (multiply by -1)
 *
 * 5. COLOR TRANSITION
 *    Increment hue each frame (using HSB color mode)
 *    Reset to 0 when reaching 360
 *
 * CHALLENGES:
 * 1. Make the background fade slowly (hint: draw semi-transparent rect)
 * 2. Add multiple lines with different colors
 * 3. Make lines respond to mouse position
 * 4. Add circles at the endpoints
 */
