/*
 * Example 17: Arrow Functions
 *
 * This sketch demonstrates arrow function syntax - a modern, compact way
 * to write functions in JavaScript (introduced in ES6/ES2015).
 *
 * Key concepts covered:
 * - Arrow function syntax: () => { }
 * - Omitting parentheses for single parameters: x => { }
 * - Omitting return and braces for single expressions: x => x * 2
 * - Using arrow functions in callbacks
 */

let circles = [];
let colors = [];

function setup() {
  createCanvas(800, 600);
  background(240);
  
  // Generate some random circles
  for (let i = 0; i < 20; i++) {
    circles.push({
      x: random(width),
      y: random(height),
      size: random(20, 60),
      speedX: random(-2, 2),
      speedY: random(-2, 2)
    });
  }
  
  // Generate colors using arrow functions
  // ---- Example 1: Full arrow function syntax ----
  colors = Array.from({length: 20}, () => {
    return color(random(255), random(255), random(255));
  });
  
  // ---- Example 2: Compact arrow function (single expression) ----
  // When you have only one expression, you can omit {} and return
  let sizes = circles.map(circle => circle.size);
  
  // ---- Example 3: Arrow function with single parameter ----
  // When you have only one parameter, you can omit ()
  let doubledSizes = sizes.map(size => size * 2);
  
  // ---- Example 4: Arrow function with no parameters ----
  // Must use () when there are no parameters
  mousePressed(() => {
    // Reset all circles
    circles = circles.map(() => ({
      x: random(width),
      y: random(height),
      size: random(20, 60),
      speedX: random(-2, 2),
      speedY: random(-2, 2)
    }));
  });
  
  // ---- Example 5: Arrow function in filter ----
  // Keep only large circles
  let largeCircles = circles.filter(c => c.size > 40);
  
  console.log("Total circles:", circles.length);
  console.log("Large circles:", largeCircles.length);
  console.log("Average size:", sizes.reduce((a, b) => a + b, 0) / sizes.length);
}

function draw() {
  background(240, 240, 245, 50);  // Semi-transparent for trail effect
  
  // Draw title
  fill(50);
  textSize(24);
  textAlign(CENTER);
  text("Arrow Functions", width / 2, 40);
  
  // Instructions
  textSize(14);
  fill(100);
  text("Click to reset circles", width / 2, 70);
  
  // Update and draw circles using arrow functions
  circles.forEach((circle, index) => {
    // Update position
    circle.x += circle.speedX;
    circle.y += circle.speedY;
    
    // Bounce off walls
    if (circle.x < 0 || circle.x > width) circle.speedX *= -1;
    if (circle.y < 0 || circle.y > height) circle.speedY *= -1;
    
    // Draw circle
    fill(colors[index]);
    noStroke();
    circle(circle.x, circle.y, circle.size);
  });
  
  // Draw comparison of syntax styles
  drawSyntaxComparison();
}

function drawSyntaxComparison() {
  // Show syntax examples
  fill(50);
  textSize(12);
  textAlign(LEFT);
  
  let y = height - 200;
  text("Syntax Comparison:", 20, y);
  y += 20;
  
  text("Traditional: function(x) { return x * 2; }", 20, y);
  y += 20;
  
  text("Arrow (full): (x) => { return x * 2; }", 20, y);
  y += 20;
  
  text("Arrow (compact): x => x * 2", 20, y);
  y += 20;
  
  text("All three do the same thing!", 20, y);
}

/*
 * ARROW FUNCTION RULES:
 * 
 * 1. Basic syntax: (parameters) => { body }
 * 
 * 2. Single parameter: You can omit parentheses
 *    - (x) => x * 2  →  x => x * 2
 * 
 * 3. No parameters: Must use empty parentheses
 *    - () => { doSomething(); }
 * 
 * 4. Single expression: You can omit {} and return
 *    - (x) => { return x * 2; }  →  x => x * 2
 * 
 * 5. Multiple statements: Must use {} and return (if needed)
 *    - (x) => {
 *        let doubled = x * 2;
 *        return doubled + 10;
 *      }
 * 
 * WHEN TO USE ARROW FUNCTIONS:
 * - Callbacks (like in map, filter, forEach)
 * - Event handlers (mousePressed, etc.)
 * - Short, simple functions
 * 
 * WHEN NOT TO USE:
 * - Object methods (they don't have their own 'this')
 * - Functions that need to be hoisted (called before definition)
 */
