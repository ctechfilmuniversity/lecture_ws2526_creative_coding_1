/*
 * Example 03: For Loops
 *
 * For loops let you repeat code multiple times.
 * This is essential for creating patterns!
 *
 * Syntax:
 * for (initialization; condition; increment) {
 *     // code to repeat
 * }
 *
 * Example breakdown:
 * for (let i = 0; i < 10; i++) {
 *     let i = 0      → start at 0
 *     i < 10         → continue while i is less than 10
 *     i++            → add 1 to i each time (i = i + 1)
 * }
 */

function setup() {
  createCanvas(600, 500);
  background(240);

  // ---- Example 1: Simple row of circles ----

  fill(255, 100, 100);
  noStroke();

  // This loop runs 6 times (i goes: 0, 1, 2, 3, 4, 5)
  for (let i = 0; i < 6; i++) {
    // Calculate x position based on i
    let x = 50 + i * 100; // 50, 150, 250, 350, 450, 550
    circle(x, 50, 40);
  }

  // Label
  fill(50);
  textSize(12);
  text("Row of circles using: for (let i = 0; i < 6; i++)", 20, 90);

  // ---- Example 2: Column of rectangles ----

  fill(100, 200, 100);
  stroke(50);
  strokeWeight(2);

  for (let i = 0; i < 5; i++) {
    let y = 120 + i * 35; // Vertical position
    rect(20, y, 80, 25);
  }

  // Label
  fill(50);
  noStroke();
  text("Column of rectangles", 20, 310);

  // ---- Example 3: Circles with varying sizes ----

  fill(100, 150, 255);
  noStroke();

  for (let i = 0; i < 8; i++) {
    let x = 150 + i * 50;
    let size = 20 + i * 10; // Size increases with i
    circle(x, 200, size);
  }

  fill(50);
  text("Circles with increasing size", 150, 260);

  // ---- Example 4: Using the counter for colors ----

  noStroke();

  for (let i = 0; i < 10; i++) {
    // Map i (0-9) to a color value (0-255)
    let colorValue = i * 25;
    fill(colorValue, 100, 255 - colorValue);

    let x = 150 + i * 40;
    rect(x, 280, 35, 60);
  }

  fill(50);
  text("Colors changing with loop counter", 150, 360);

  // ---- Example 5: Step increment (counting by different amounts) ----

  fill(255, 200, 100);
  stroke(100);
  strokeWeight(1);

  // i += 30 means add 30 to i each loop
  for (let i = 0; i <= width; i += 30) {
    line(i, 380, i, 430);
  }

  fill(50);
  noStroke();
  text("Lines with step of 30: for (let i = 0; i <= width; i += 30)", 20, 470);

  // ---- Example 6: Countdown (decrementing) ----

  fill(200, 100, 200);
  textSize(16);
  textAlign(CENTER);

  // i-- means subtract 1 from i each loop
  let textX = 450;
  for (let i = 5; i >= 1; i--) {
    text(i, textX, 420);
    textX += 30;
  }
  text("GO!", textX, 420);

  fill(50);
  textSize(12);
  textAlign(LEFT);
  text("Countdown: for (let i = 5; i >= 1; i--)", 400, 470);
}
