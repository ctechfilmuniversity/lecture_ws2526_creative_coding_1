/*
 * Example 02: Variables
 *
 * Variables are containers that store values.
 * They make your code flexible and reusable!
 *
 * Key concepts covered:
 * - Declaring variables with 'let'
 * - Using variables for positions and sizes
 * - Built-in p5 variables: width, height, mouseX, mouseY
 * - Simple math with variables
 */

// Variables declared outside functions are "global"
// They can be accessed anywhere in your code
let circleSize = 80;
let spacing = 100;

function setup() {
  createCanvas(600, 400);
  background(30, 30, 40);

  // ---- Using variables for positioning ----

  // Define center position using built-in width/height variables
  let centerX = width / 2;
  let centerY = height / 2;

  // Draw a circle at the center
  fill(255, 150, 100);
  noStroke();
  circle(centerX, centerY, circleSize);

  // ---- Using variables for multiple shapes ----

  // Using spacing variable to position circles evenly
  fill(100, 200, 255);
  circle(centerX - spacing, centerY, circleSize);
  circle(centerX + spacing, centerY, circleSize);

  // ---- Math with variables ----

  // We can do math with variables!
  let smallSize = circleSize / 2;
  let largeSize = circleSize * 1.5;

  fill(200, 255, 150);
  circle(centerX - spacing, centerY - spacing, smallSize);
  circle(centerX, centerY - spacing, circleSize);
  circle(centerX + spacing, centerY - spacing, largeSize);

  // ---- Variables for colors ----

  let redValue = 255;
  let greenValue = 100;
  let blueValue = 150;

  fill(redValue, greenValue, blueValue);
  circle(centerX, centerY + spacing, circleSize);

  // Modify the color values
  fill(redValue - 100, greenValue + 100, blueValue);
  circle(centerX - spacing, centerY + spacing, circleSize);

  fill(redValue, greenValue, blueValue + 100);
  circle(centerX + spacing, centerY + spacing, circleSize);

  // ---- Display some info ----

  fill(255);
  textSize(14);
  textAlign(LEFT, TOP);
  text("Canvas size: " + width + " x " + height, 20, 20);
  text("Circle size: " + circleSize, 20, 40);
  text("Spacing: " + spacing, 20, 60);

  textAlign(CENTER, BOTTOM);
  text(
    "Try changing the variables at the top of the code!",
    width / 2,
    height - 20
  );
}

// Bonus: This draw function shows mouseX and mouseY variables
function draw() {
  // Draw a small rectangle showing mouse position
  fill(30, 30, 40);
  noStroke();
  rect(width - 150, 10, 140, 50);

  fill(255);
  textSize(12);
  textAlign(LEFT, TOP);
  text("mouseX: " + mouseX, width - 140, 20);
  text("mouseY: " + mouseY, width - 140, 40);
}
