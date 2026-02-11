/*
 * Example 06: Checkerboard Pattern
 *
 * The classic checkerboard is a great example of algorithmic thinking!
 *
 * PATTERN ANALYSIS:
 * - In even rows (0, 2, 4...), even columns are black
 * - In odd rows (1, 3, 5...), odd columns are black
 *
 * ELEGANT SOLUTION:
 * If (row + column) is even → one color
 * If (row + column) is odd  → other color
 *
 * Why does this work?
 * - even + even = even
 * - odd + odd = even
 * - even + odd = odd
 * - odd + even = odd
 */

let cellSize = 50;

function setup() {
  createCanvas(600, 450);
  background(240);

  noStroke();

  // ---- Classic Black & White Checkerboard ----

  let row = 0;
  for (let y = 20; y < 220; y += cellSize) {
    let col = 0;
    for (let x = 20; x < 220; x += cellSize) {
      // The elegant solution: (row + col) % 2
      if ((row + col) % 2 == 0) {
        fill(0); // Black
      } else {
        fill(255); // White
      }

      rect(x, y, cellSize, cellSize);
      col++;
    }
    row++;
  }

  // Label
  fill(50);
  textSize(12);
  text("if ((row + col) % 2 == 0)", 20, 240);

  // ---- Colorful Checkerboard ----

  row = 0;
  for (let y = 20; y < 220; y += cellSize) {
    let col = 0;
    for (let x = 250; x < 450; x += cellSize) {
      if ((row + col) % 2 == 0) {
        fill(255, 100, 100); // Red
      } else {
        fill(100, 200, 255); // Blue
      }

      rect(x, y, cellSize, cellSize);
      col++;
    }
    row++;
  }

  fill(50);
  text("Colorful variation", 250, 240);

  // ---- Three Color Pattern ----
  // Using % 3 for three colors

  row = 0;
  for (let y = 20; y < 220; y += cellSize) {
    let col = 0;
    for (let x = 470; x < 590; x += 40) {
      let pattern = (row + col) % 3;

      if (pattern == 0) {
        fill(255, 200, 100); // Orange
      } else if (pattern == 1) {
        fill(100, 200, 100); // Green
      } else {
        fill(200, 100, 200); // Purple
      }

      rect(x, y, 38, cellSize - 2);
      col++;
    }
    row++;
  }

  fill(50);
  text("Three colors: % 3", 470, 240);

  // ---- Interactive Checkerboard (bottom) ----

  fill(50);
  textSize(14);
  text("Interactive: Move mouse to change cell size", 20, 280);
}

function draw() {
  // Clear only the bottom part
  fill(240);
  noStroke();
  rect(0, 290, width, height - 290);

  // Map mouse position to cell size (20 to 80)
  let dynamicSize = map(mouseX, 0, width, 20, 80);
  dynamicSize = constrain(dynamicSize, 20, 80); // Keep within bounds

  let row = 0;
  for (let y = 300; y < 440; y += dynamicSize) {
    let col = 0;
    for (let x = 20; x < 580; x += dynamicSize) {
      // Add some color variation based on position
      if ((row + col) % 2 == 0) {
        fill(30 + col * 10, 30 + row * 20, 100);
      } else {
        fill(255 - col * 10, 255 - row * 20, 200);
      }

      noStroke();
      rect(x, y, dynamicSize - 2, dynamicSize - 2);
      col++;
    }
    row++;
  }

  // Show current cell size
  fill(50);
  textSize(12);
  text("Cell size: " + nf(dynamicSize, 1, 1), 500, 450);
}

