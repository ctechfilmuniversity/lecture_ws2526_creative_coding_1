/*
 * Example 04: Grid Pattern (Nested Loops)
 *
 * To create a 2D grid, we use nested loops:
 * - The outer loop controls rows (y positions)
 * - The inner loop controls columns (x positions)
 *
 * For each row, the inner loop draws all columns.
 * This creates a complete grid!
 */

let cellSize = 50;

function setup() {
  createCanvas(600, 400);
  background(30, 30, 40);

  // ---- Basic Grid ----

  stroke(255);
  strokeWeight(1);
  fill(100, 150, 200);

  // Outer loop: rows (y direction)
  for (let y = 0; y < height; y += cellSize) {
    // Inner loop: columns (x direction)
    for (let x = 0; x < width; x += cellSize) {
      // Draw a rectangle at each grid position
      rect(x, y, cellSize, cellSize);

      // Label each cell with it's inner loop and outer loop index
      // textSize(12);
      // fill(255);
      // textAlign(CENTER, CENTER);
      // text(
      //   x / cellSize + ", " + y / cellSize,
      //   x + cellSize / 2,
      //   y + cellSize / 2
      // );
      // fill(100, 150, 200);
    }
  }
}

function draw() {
  // This version redraws each frame
  // Try uncommenting the lines below for interactive grid!
  // background(30, 30, 40);
  // stroke(255);
  // strokeWeight(1);
  // for (let y = 0; y < height; y += cellSize) {
  //   for (let x = 0; x < width; x += cellSize) {
  //     // Calculate distance from mouse to each cell center
  //     let centerX = x + cellSize / 2;
  //     let centerY = y + cellSize / 2;
  //     let d = dist(mouseX, mouseY, centerX, centerY);
  //     // Use distance to affect color
  //     let brightness = map(d, 0, 300, 255, 50);
  //     fill(brightness, brightness * 0.6, brightness * 0.8);
  //     rect(x, y, cellSize, cellSize);
  //   }
  // }
}

/*
 * Understanding Nested Loops:
 *
 * When cellSize = 50 and canvas is 600x400:
 *
 * y = 0:   Draw cells at x = 0, 50, 100, 150... 550 (row 0)
 * y = 50:  Draw cells at x = 0, 50, 100, 150... 550 (row 1)
 * y = 100: Draw cells at x = 0, 50, 100, 150... 550 (row 2)
 * ... and so on for all rows
 *
 * Total cells: (600/50) × (400/50) = 12 × 8 = 96 cells
 *
 * CHALLENGE:
 * 1. Change cellSize to see different grid densities
 * 2. Uncomment the code in draw() to see mouse interaction
 * 3. Try drawing circles instead of rectangles
 */
