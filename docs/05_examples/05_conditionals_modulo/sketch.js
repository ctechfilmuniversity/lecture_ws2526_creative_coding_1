/*
 * Example 05: Conditionals & The Modulo Operator
 *
 * Conditionals (if statements) let your code make decisions.
 * The modulo operator (%) returns the remainder of a division.
 *
 * MODULO EXPLAINED:
 * 7 % 3 = 1  (7 divided by 3 is 2 with remainder 1)
 * 8 % 2 = 0  (8 divided by 2 is 4 with remainder 0)
 * 5 % 5 = 0  (5 divided by 5 is 1 with remainder 0)
 *
 * Key use: Checking if a number is even or odd:
 * number % 2 == 0 → number is EVEN
 * number % 2 != 0 → number is ODD
 */

let cellSize = 50;

function setup() {
  createCanvas(600, 500);
  background(240);

  // ---- Example 1: Diagonal Pattern ----
  // Fill only cells where x position equals y position

  drawLabel(20, 20, "Diagonal: if (x == y)");

  stroke(100);
  strokeWeight(1);

  let row = 0;
  for (let y = 40; y < 200; y += 30) {
    let col = 0;
    for (let x = 20; x < 300; x += 30) {
      // Conditional: check if we're on the diagonal
      if (row == col) {
        fill(255, 100, 100); // Red for diagonal
      } else {
        fill(255); // White otherwise
      }

      rect(x, y, 28, 28);
      col++;
    }
    row++;
  }

  // ---- Example 2: Upper/Lower Triangle ----
  // Fill cells where x > y (above diagonal)

  drawLabel(320, 20, "Triangle: if (col > row)");

  row = 0;
  for (let y = 40; y < 200; y += 30) {
    let col = 0;
    for (let x = 320; x < 580; x += 30) {
      if (col > row) {
        fill(100, 100, 255); // Blue above diagonal
      } else {
        fill(255);
      }

      rect(x, y, 28, 28);
      col++;
    }
    row++;
  }

  // ---- Example 3: Even/Odd Columns with Modulo ----

  drawLabel(20, 220, "Even columns: if (col % 2 == 0)");

  row = 0;
  for (let y = 240; y < 350; y += 30) {
    let col = 0;
    for (let x = 20; x < 280; x += 30) {
      // Check if column number is even
      if (col % 2 == 0) {
        fill(100, 200, 100); // Green for even columns
      } else {
        fill(255);
      }

      rect(x, y, 28, 28);
      col++;
    }
    row++;
  }

  // ---- Example 4: Every Third Cell ----

  drawLabel(320, 220, "Every 3rd: if (col % 3 == 0)");

  row = 0;
  for (let y = 240; y < 350; y += 30) {
    let col = 0;
    for (let x = 320; x < 580; x += 30) {
      // Check if column is divisible by 3
      if (col % 3 == 0) {
        fill(255, 200, 100); // Orange every 3rd
      } else {
        fill(255);
      }

      rect(x, y, 28, 28);
      col++;
    }
    row++;
  }

  // ---- Example 5: Showing Modulo Values ----

  drawLabel(20, 380, "Modulo values: 0 % 4, 1 % 4, 2 % 4, ...");

  fill(50);
  textSize(9);
  textAlign(CENTER, CENTER);

  for (let i = 0; i < 16; i++) {
    let x = 40 + i * 35;
    let remainder = i % 4;

    // Color based on remainder
    if (remainder == 0) fill(255, 100, 100);
    else if (remainder == 1) fill(100, 255, 100);
    else if (remainder == 2) fill(100, 100, 255);
    else fill(255, 255, 100);

    stroke(100);
    rect(x - 15, 410, 30, 30);

    fill(0);
    noStroke();
    text(i + "%4=" + remainder, x, 460);
  }
}

function drawLabel(x, y, txt) {
  fill(50);
  noStroke();
  textSize(14);
  textAlign(LEFT, TOP);
  text(txt, x, y);
}
