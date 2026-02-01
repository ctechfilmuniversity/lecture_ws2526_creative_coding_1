/*
 * Example 18: Asynchronous Callbacks
 *
 * This sketch demonstrates asynchronous programming - when code doesn't
 * execute in the order it's written, but rather when certain events happen.
 *
 * Key concepts covered:
 * - Synchronous: Code executes line by line, waiting for each to finish
 * - Asynchronous: Code continues while waiting for slow operations
 * - setTimeout(): Execute code after a delay
 * - loadImage(): Load images without blocking
 * - Callbacks: Functions called when async operations complete
 */

let timerMessage = "Waiting...";
let timerCount = 0;
let img = null;
let loadingMessage = "Loading image...";
let imageLoaded = false;

function setup() {
  createCanvas(800, 600);
  background(240);
  
  // ---- Example 1: Synchronous Execution ----
  // This code runs immediately, line by line
  console.log("1. This runs first");
  console.log("2. This runs second");
  console.log("3. This runs third");
  
  // ---- Example 2: setTimeout() - Asynchronous Execution ----
  // setTimeout schedules code to run LATER, without blocking
  
  console.log("A. This runs immediately");
  
  setTimeout(() => {
    console.log("B. This runs after 1000ms (1 second)");
    timerMessage = "Timer fired!";
    timerCount++;
  }, 1000);
  
  console.log("C. This also runs immediately (doesn't wait for setTimeout)");
  
  // Notice: C prints before B, even though B comes first in the code!
  // This is because setTimeout is asynchronous.
  
  // ---- Example 3: Multiple setTimeout calls ----
  // They don't block each other - all run concurrently
  
  setTimeout(() => {
    timerMessage = "First timer (500ms)";
  }, 500);
  
  setTimeout(() => {
    timerMessage = "Second timer (1500ms)";
  }, 1500);
  
  setTimeout(() => {
    timerMessage = "Third timer (2500ms)";
  }, 2500);
  
  // ---- Example 4: loadImage() - Asynchronous Image Loading ----
  // Loading images takes time (network request)
  // We use a callback to handle the image when it's ready
  
  // Using a callback function
  loadImage('https://picsum.photos/400/300', (loadedImage) => {
    // This callback runs WHEN the image finishes loading
    // Not immediately when loadImage() is called!
    img = loadedImage;
    imageLoaded = true;
    loadingMessage = "Image loaded!";
    console.log("Image loaded successfully");
  });
  
  // This runs immediately, before the image is loaded
  console.log("loadImage() called, but image not ready yet");
}

function draw() {
  background(240);
  
  // Draw title
  fill(50);
  textSize(24);
  textAlign(CENTER);
  text("Asynchronous Callbacks", width / 2, 40);
  
  // ---- Display Timer Example ----
  fill(100, 150, 255);
  textSize(16);
  textAlign(LEFT);
  text("setTimeout Example:", 20, 100);
  
  fill(50);
  textSize(14);
  text("Message: " + timerMessage, 20, 130);
  text("Timer fired " + timerCount + " times", 20, 150);
  
  // Draw a visual timer
  let timerBar = map((millis() % 3000), 0, 3000, 0, width - 40);
  fill(100, 150, 255, 100);
  rect(20, 170, timerBar, 20);
  
  // ---- Display Image Loading Example ----
  fill(255, 150, 100);
  textSize(16);
  text("loadImage() Example:", 20, 250);
  
  fill(50);
  textSize(14);
  text(loadingMessage, 20, 280);
  
  // Draw image if loaded
  if (imageLoaded && img) {
    image(img, 20, 300);
    fill(50);
    text("Image loaded asynchronously!", 20, 620);
  } else {
    // Show loading indicator
    fill(200);
    rect(20, 300, 400, 300);
    fill(100);
    textAlign(CENTER);
    text("Loading...", 220, 450);
  }
  
  // ---- Explanation ----
  fill(50);
  textSize(12);
  textAlign(LEFT);
  let y = 350;
  text("Key Insight:", 450, y);
  y += 20;
  text("Asynchronous code doesn't block!", 450, y);
  y += 20;
  text("Your program continues running", 450, y);
  y += 20;
  text("while waiting for slow operations.", 450, y);
  y += 30;
  text("Check the browser console (F12)", 450, y);
  y += 20;
  text("to see the execution order!", 450, y);
}

function mousePressed() {
  // Reset timer
  timerCount = 0;
  timerMessage = "Reset - waiting for timer...";
  
  // Schedule a new timer
  setTimeout(() => {
    timerMessage = "Mouse click timer fired!";
    timerCount++;
  }, 1000);
}

/*
 * KEY INSIGHTS:
 * 
 * 1. SYNCHRONOUS (blocking):
 *    - Code runs line by line
 *    - Each line waits for the previous to finish
 *    - Simple but can freeze your program
 * 
 * 2. ASYNCHRONOUS (non-blocking):
 *    - Code continues while waiting
 *    - Callbacks run when operations complete
 *    - Essential for web development!
 * 
 * 3. setTimeout(callback, delay):
 *    - Schedules callback to run after delay
 *    - Doesn't block other code
 *    - Returns immediately
 * 
 * 4. loadImage(path, callback):
 *    - Starts loading image
 *    - Continues immediately (doesn't wait)
 *    - Calls callback when image is ready
 * 
 * REAL-WORLD ANALOGY:
 * - Synchronous: Standing in line, waiting for each person
 * - Asynchronous: Taking a number, continuing to shop, 
 *   getting notified when your number is called
 */
