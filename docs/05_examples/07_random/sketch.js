/*
 * Example 07: Randomness
 *
 * The random() function adds unpredictability to your sketches!
 *
 * Usage:
 * - random(max)        → returns a number from 0 to max
 * - random(min, max)   → returns a number from min to max
 * - random(array)      → returns a random element from the array
 *
 * Every time random() is called, it returns a different value!
 *
 * Click anywhere to regenerate the artwork.
 */

function setup() {
  createCanvas(600, 520);
  generateArt();
}

function generateArt() {
  background(30, 30, 40);

  // ---- Section 1: Random positions ----

  fill(255, 100, 150, 200);
  noStroke();
  textAlign(LEFT, TOP);

  for (let i = 0; i < 20; i++) {
    // Random x and y positions
    let x = random(20, 280);
    let y = random(20, 220);
    circle(x, y, 30);
  }

  // Label
  fill(255);
  textSize(12);
  text("Random positions", 20, 240);

  // ---- Section 2: Random sizes ----

  fill(100, 200, 255, 200);

  for (let i = 0; i < 15; i++) {
    let x = random(320, 580);
    let y = random(20, 220);
    let size = random(10, 60); // Random size between 10 and 60
    circle(x, y, size);
  }

  fill(255);
  text("Random sizes", 320, 240);

  // ---- Section 3: Random colors ----

  for (let i = 0; i < 20; i++) {
    // Random RGB values
    let r = random(255);
    let g = random(255);
    let b = random(255);

    fill(r, g, b, 200);

    let x = random(20, 280);
    let y = random(270, 450);
    rect(x, y, 40, 40);
  }

  fill(255);
  text("Random colors", 20, 480);

  // ---- Section 4: Controlled randomness ----
  // Random within constraints for more pleasing results

  for (let i = 0; i < 25; i++) {
    // Keep colors in a nice range (pastel-ish)
    let r = random(150, 255);
    let g = random(100, 200);
    let b = random(150, 255);

    fill(r, g, b, 180);

    // Organize positions along a loose grid
    let baseX = 320 + (i % 5) * 50;
    let baseY = 270 + floor(i / 5) * 35;

    // Add small random offset
    let x = baseX + random(-10, 10);
    let y = baseY + random(-10, 10);
    let size = random(25, 45);

    circle(x, y, size);
  }

  fill(255);
  text("Controlled randomness", 320, 480);

  // Instruction
  fill(255, 200, 100);
  textSize(12);
  textAlign(CENTER, CENTER);
  text("Click anywhere to regenerate!", width / 2, height - 10);
}

function mousePressed() {
  // Regenerate the art when clicked
  generateArt();
}

/*
 * TIPS FOR USING RANDOM:
 *
 * 1. Too much randomness can look chaotic
 *    - Use constraints and controlled ranges
 *
 * 2. Use random for variation, not chaos
 *    - random(baseValue - 10, baseValue + 10) for slight variations
 *
 * 3. Combine random with structure
 *    - Use grids or patterns as a base, add random offsets
 *
 * 4. random() gives floats (decimals)
 *    - Use floor(random(10)) for integers 0-9
 */
