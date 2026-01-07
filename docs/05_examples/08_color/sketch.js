/*
 * Example 08: Working with Color
 *
 * p5.js supports different color modes:
 *
 * RGB (Red, Green, Blue) - Default
 * - Each value: 0-255
 * - fill(255, 0, 0) = pure red
 * - fill(0, 255, 0) = pure green
 * - fill(0, 0, 255) = pure blue
 *
 * HSB (Hue, Saturation, Brightness)
 * - Hue: 0-360 (color wheel)
 * - Saturation: 0-100 (gray to vivid)
 * - Brightness: 0-100 (dark to light)
 *
 * Alpha (Transparency)
 * - 4th parameter: 0 = invisible, 255 = opaque
 * - fill(255, 0, 0, 128) = semi-transparent red
 */

function setup() {
  createCanvas(650, 500);
  background(30);

  // ---- RGB Color Examples ----

  fill(255);
  textSize(14);
  text("RGB Colors (default)", 20, 25);

  noStroke();

  // Primary colors
  fill(255, 0, 0); // Red
  rect(20, 40, 60, 60);
  fill(0, 255, 0); // Green
  rect(90, 40, 60, 60);
  fill(0, 0, 255); // Blue
  rect(160, 40, 60, 60);

  // Secondary colors (mixing)
  fill(255, 255, 0); // Red + Green = Yellow
  rect(20, 110, 60, 60);
  fill(255, 0, 255); // Red + Blue = Magenta
  rect(90, 110, 60, 60);
  fill(0, 255, 255); // Green + Blue = Cyan
  rect(160, 110, 60, 60);

  // Grayscale
  for (let i = 0; i < 8; i++) {
    let gray = i * 36;
    fill(gray);
    rect(20 + i * 27, 180, 25, 30);
  }

  // ---- HSB Color Mode ----

  fill(255);
  text("HSB Colors (Hue, Saturation, Brightness)", 250, 25);

  // Switch to HSB mode
  colorMode(HSB, 360, 100, 100);

  // Hue spectrum (rainbow)
  for (let h = 0; h < 360; h += 15) {
    fill(h, 100, 100);
    rect(250 + h * 0.9, 40, 15, 40);
  }

  // Saturation gradient (vivid to gray)
  for (let s = 0; s <= 100; s += 10) {
    fill(200, s, 100); // Fixed hue (cyan), varying saturation
    rect(250 + s * 3.2, 90, 30, 40);
  }

  // Brightness gradient (dark to light)
  for (let b = 0; b <= 100; b += 10) {
    fill(30, 100, b); // Fixed hue (orange), varying brightness
    rect(250 + b * 3.2, 140, 30, 40);
  }

  // ---- Alpha (Transparency) ----

  colorMode(RGB, 255); // Back to RGB

  fill(255);
  text("Alpha (Transparency)", 20, 240);

  // Overlapping transparent circles
  fill(255, 0, 0, 150);
  circle(80, 310, 100);
  fill(0, 255, 0, 150);
  circle(130, 310, 100);
  fill(0, 0, 255, 150);
  circle(105, 360, 100);

  // Transparency gradient
  for (let a = 0; a <= 255; a += 25) {
    fill(255, 100, 100, a);
    rect(20 + a * 0.8, 420, 20, 50);
  }

  fill(255);
  text("Alpha: 0 → 255", 20, 485);

  // ---- HSB Practical Example: Color Wheel ----

  fill(255);
  text("HSB Color Wheel", 400, 240);

  colorMode(HSB, 360, 100, 100);

  let centerX = 480;
  let centerY = 350;
  let radius = 100;

  // Draw color wheel with small rectangles
  for (let angle = 0; angle < 360; angle += 5) {
    for (let r = 20; r < radius; r += 10) {
      let hue = angle;
      let saturation = map(r, 20, radius, 0, 100);
      fill(hue, saturation, 100);

      // Convert polar to cartesian coordinates
      let x = centerX + cos(radians(angle)) * r;
      let y = centerY + sin(radians(angle)) * r;
      noStroke();
      circle(x, y, 12);
    }
  }

  // Center circle (white)
  fill(0, 0, 100);
  circle(centerX, centerY, 40);

  // ---- Tip box ----
  colorMode(RGB);
  fill(50);
  rect(250, 420, 380, 70, 5);
  fill(255);
  textSize(12);
  text("TIP: Use HSB mode for easier color manipulation!", 260, 445);
  text("Changing just the hue creates harmonious color schemes.", 260, 465);
  text("colorMode(HSB, 360, 100, 100);", 260, 485);
}
