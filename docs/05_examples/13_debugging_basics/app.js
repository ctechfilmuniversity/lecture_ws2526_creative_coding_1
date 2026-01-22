/*
 * Example 13: Debugging Basics in JavaScript (VSCode + Node.js)
 *
 * This example contains an intentional logical bug and some console.log()
 * statements so that you can practice:
 * - Setting breakpoints
 * - Stepping through code
 * - Inspecting variables
 * - Understanding call stacks
 */

// A simple data set to work with
const numbers = [1, 2, 3, 4, 5];

/**
 * Intentionally buggy function:
 * - It tries to sum all numbers in the array
 * - There is an off-by-one error in the loop condition
 *
 * Exercise:
 * - Set a breakpoint on the first line inside the function
 * - Step through and watch how i and total change
 * - Inspect arr[i] when i is equal to arr.length
 */
function sumArray(arr) {
  console.log("sumArray() called with:", arr);

  let total = 0;

  // BUG: should be i < arr.length, not i <= arr.length
  for (let i = 0; i <= arr.length; i++) {
    console.log("Loop iteration, i =", i, "current value =", arr[i]);
    total += arr[i];
  }

  console.log("Total at end of sumArray():", total);
  return total;
}

/**
 * Main function that runs when the script executes
 */
function main() {
  console.log("=== Debugging Example ===");
  console.log("Numbers to sum:", numbers);

  // Expected sum: 1 + 2 + 3 + 4 + 5 = 15
  const sum = sumArray(numbers);

  // When the bug is present, this will show "Sum is: NaN"
  console.log(`\nResult: Sum is ${sum}`);
  console.log("Expected: Sum is 15");

  if (isNaN(sum)) {
    console.log("\n❌ Bug detected! The sum is NaN.");
    console.log("Use the debugger to find out why.");
  } else if (sum === 15) {
    console.log("\n✅ Correct! The sum is 15.");
  } else {
    console.log(`\n⚠️  Unexpected result: ${sum}`);
  }
}

// Run the main function
main();
