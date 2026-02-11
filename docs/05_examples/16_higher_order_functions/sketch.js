/*
 * Example 16: Higher Order Functions (map, filter, reduce)
 *
 * This sketch demonstrates the three most important higher order functions
 * for working with arrays in JavaScript.
 *
 * Key concepts covered:
 * - map(): Transform each element → same length, different values
 * - filter(): Keep only matching elements → shorter array
 * - reduce(): Combine all elements → single value
 */

let numbers = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100];
let positions = [];
let filteredPositions = [];
let sum = 0;

function setup() {
  createCanvas(800, 600);
  background(240);
  
  // ---- Example 1: map() - Transform each element ----
  // map() applies a function to each element and returns a new array
  // Original array: [10, 20, 30, ...]
  // Result: [100, 200, 300, ...] (each multiplied by 10)
  
  // Using a named function
  let multiplied = numbers.map(multiplyByTen);
  
  // Using an anonymous function
  let doubled = numbers.map(function(num) {
    return num * 2;
  });
  
  // Using an arrow function (modern syntax)
  let positionsX = numbers.map(num => num * 5);
  
  // Create positions array for visualization
  positions = numbers.map((num, index) => {
    return {
      x: 100 + index * 60,
      y: 200,
      size: num / 2,
      value: num
    };
  });
  
  // ---- Example 2: filter() - Keep only matching elements ----
  // filter() keeps only elements where the function returns true
  // Original: [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
  // Result: [20, 40, 60, 80, 100] (only even numbers)
  
  let evenNumbers = numbers.filter(isEven);
  
  // Using arrow function
  let largeNumbers = numbers.filter(num => num > 50);
  
  // Filter positions to show only large circles
  filteredPositions = positions.filter(pos => pos.value > 50);
  
  // ---- Example 3: reduce() - Combine all elements ----
  // reduce() combines all elements into a single value
  // Original: [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
  // Result: 550 (sum of all numbers)
  
  // Using a named function
  sum = numbers.reduce(addNumbers, 0);
  
  // Using arrow function
  let product = numbers.reduce((total, num) => total * num, 1);
  
  console.log("Original numbers:", numbers);
  console.log("Even numbers:", evenNumbers);
  console.log("Sum:", sum);
  console.log("Product:", product);
}

function draw() {
  background(240);
  
  // Draw title
  fill(50);
  textSize(24);
  textAlign(CENTER);
  text("Higher Order Functions", width / 2, 40);
  
  // ---- Visualize map() ----
  textSize(16);
  textAlign(LEFT);
  fill(100, 150, 255);
  text("map(): Transform each element", 20, 100);
  
  // Draw all circles (transformed positions)
  positions.forEach((pos, index) => {
    fill(100, 150, 255, 150);
    noStroke();
    circle(pos.x, pos.y, pos.size);
    
    // Label
    fill(50);
    textSize(10);
    textAlign(CENTER);
    text(pos.value, pos.x, pos.y + 30);
  });
  
  // ---- Visualize filter() ----
  fill(255, 150, 100);
  textAlign(LEFT);
  textSize(16);
  text("filter(): Keep only values > 50", 20, 350);
  
  // Draw only filtered circles
  filteredPositions.forEach((pos) => {
    fill(255, 150, 100, 200);
    noStroke();
    circle(pos.x, pos.y + 150, pos.size);
    
    // Label
    fill(50);
    textSize(10);
    textAlign(CENTER);
    text(pos.value, pos.x, pos.y + 180);
  });
  
  // ---- Visualize reduce() ----
  fill(150, 255, 100);
  textAlign(LEFT);
  textSize(16);
  text("reduce(): Sum of all values = " + sum, 20, 550);
  
  // Draw sum visualization
  fill(150, 255, 100, 150);
  rect(20, 560, sum / 2, 20);
}

// ---- Helper Functions for map, filter, reduce ----

// For map()
function multiplyByTen(num) {
  return num * 10;
}

// For filter()
function isEven(num) {
  return num % 2 === 0;  // Returns true if number is even
}

// For reduce()
function addNumbers(total, num) {
  return total + num;  // Accumulate sum
}

/*
 * KEY INSIGHTS:
 * 
 * 1. map() - Transform each element
 *    - Input: [10, 20, 30]
 *    - Function: multiply by 2
 *    - Output: [20, 40, 60]
 *    - Same length, different values
 * 
 * 2. filter() - Keep only matching elements
 *    - Input: [10, 20, 30, 40, 50]
 *    - Function: keep if > 30
 *    - Output: [40, 50]
 *    - Shorter array, same form
 * 
 * 3. reduce() - Combine all elements
 *    - Input: [10, 20, 30]
 *    - Function: add together
 *    - Output: 60
 *    - Single value
 * 
 * All three take a function as an argument - that's why they're
 * called "higher order functions"!
 */
