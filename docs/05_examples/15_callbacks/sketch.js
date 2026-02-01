/*
 * Example 15: Callback Functions
 *
 * This sketch demonstrates callback functions - functions passed as arguments
 * to other functions, which are then called at a later time.
 *
 * Key concepts covered:
 * - Named callback functions
 * - Anonymous callback functions
 * - Event callbacks (mousePressed, doubleClicked)
 * - requestAnimationFrame pattern (similar to p5's draw loop)
 */

let bgColor = 240;
let circleX = 300;
let circleY = 200;
let circleSize = 50;

function setup() {
  createCanvas(600, 400);
  background(bgColor);
  
  // ---- Example 1: Named Callback Function ----
  // We define a function with a name, then pass that name to mousePressed
  // Notice: we pass 'changeBackground' WITHOUT parentheses
  // We're passing the function itself, not calling it
  
  // Named function approach
  mousePressed(changeBackground);
  
  // ---- Example 2: Anonymous Callback Function ----
  // We can also define the function directly where it's needed
  // This is called an "anonymous" function because it has no name
  
  doubleClicked(function() {
    // Reset circle position
    circleX = random(100, width - 100);
    circleY = random(100, height - 100);
    circleSize = random(30, 80);
  });
  
  // ---- Example 3: Arrow Function Callback (modern syntax) ----
  // Arrow functions are a shorter way to write anonymous functions
  // This does the same thing as Example 2, but more compact
  
  // Uncomment to try:
  // doubleClicked(() => {
  //   circleX = random(100, width - 100);
  //   circleY = random(100, height - 100);
  //   circleSize = random(30, 80);
  // });
}

function draw() {
  // Clear with current background color
  background(bgColor);
  
  // Draw a circle that follows the mouse
  fill(255, 100, 100);
  noStroke();
  circle(mouseX, mouseY, circleSize);
  
  // Draw a fixed circle
  fill(100, 200, 255, 150);
  circle(circleX, circleY, circleSize);
  
  // Instructions
  fill(50);
  textSize(14);
  textAlign(LEFT);
  text("Click: Change background color", 10, 20);
  text("Double-click: Move blue circle", 10, 40);
}

// ---- Named Callback Function ----
// This function is defined separately and given a name
// It's called whenever the mouse is pressed
function changeBackground() {
  // Generate random background color
  bgColor = color(
    random(200, 255),
    random(200, 255),
    random(200, 255)
  );
  
  // Print to console to see when it's called
  console.log("Background changed! Color:", bgColor);
}

/*
 * KEY INSIGHTS:
 * 
 * 1. Callbacks are functions passed as arguments
 *    - mousePressed(changeBackground) passes the function, doesn't call it
 *    - p5.js stores this function and calls it when the mouse is pressed
 * 
 * 2. Named vs Anonymous
 *    - Named: function changeBackground() { ... }
 *    - Anonymous: function() { ... } or () => { ... }
 *    - Both work the same way!
 * 
 * 3. When are callbacks executed?
 *    - NOT immediately when you write the code
 *    - Later, when the event happens (mouse click, double-click, etc.)
 *    - This is "asynchronous" - the timing is controlled by the system
 */
