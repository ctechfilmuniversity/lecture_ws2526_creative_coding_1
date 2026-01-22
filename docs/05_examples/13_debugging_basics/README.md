# Example 13: Debugging Basics (VSCode + Node.js)

This example demonstrates how to use the **VSCode debugger** with Node.js.

It contains an intentional **logical bug** in `sumArray()` so you can:

- Set breakpoints
- Step through code
- Inspect variables and the call stack
- See the difference between expected and actual behavior

---

## Files

- `app.js` – Contains the buggy `sumArray()` function and main execution logic

---

## The Bug

In `app.js`:

```js
function sumArray(arr) {
  let total = 0;

  // BUG: should be i < arr.length, not i <= arr.length
  for (let i = 0; i <= arr.length; i++) {
    total += arr[i];
  }

  return total;
}
```

Because of `i <= arr.length`, the loop runs one step too far:

- On the last iteration, `i === arr.length`
- `arr[i]` is `undefined`
- `total += undefined` produces `NaN`

When you run the script, it will show:

> `Sum is NaN`

instead of the expected `Sum is 15`.

---

## How to Run

### Simple Execution

1. Open this folder (`13_debugging_basics`) in VSCode.
2. Run the script from the terminal:

```bash
node app.js
```

You'll see output showing the bug (NaN result).

---

## Debugging with VSCode

### Step 1: Set a Breakpoint

1. Open `app.js` in VSCode.
2. Click in the **left margin** (gutter) next to line 29 (inside the `sumArray` function) to set a red breakpoint dot.

### Step 2: Start Debugging

1. Press **F5** (or go to **Run and Debug** in the sidebar, then click the play button).
2. VSCode will ask you to create a launch configuration. Select **"Node.js"**.
3. This creates a `.vscode/launch.json` file automatically.

Alternatively, you can manually create `.vscode/launch.json`:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "type": "node",
      "request": "launch",
      "name": "Debug Debugging Example",
      "skipFiles": ["<node_internals>/**"],
      "program": "${workspaceFolder}/docs/05_examples/13_debugging_basics/app.js"
    }
  ]
}
```

### Step 3: Debug!

1. With your breakpoint set, press **F5** to start debugging.
2. Execution will **pause** at your breakpoint.
3. Now you can:

   - **Inspect variables**: Look at the VARIABLES panel on the left, or hover your mouse over variables in the code
   - **Step Over (F10)**: Execute the current line and move to the next
   - **Step Into (F11)**: Enter into function calls
   - **Continue (F5)**: Run until the next breakpoint
   - **Watch expressions**: Add variables to the WATCH panel to monitor them

4. Step through the loop and watch what happens:
   - Notice how `i` increments: 0, 1, 2, 3, 4, 5
   - When `i === 5` (which equals `arr.length`), `arr[i]` is `undefined`
   - This is when `total` becomes `NaN`

---

## Fixing the Bug

Once you understand the issue, fix it:

```js
for (let i = 0; i < arr.length; i++) {
  total += arr[i];
}
```

After saving:

1. Run the script again: `node app.js`
2. The result should now be: `Sum is 15`

Or debug it again to see it working correctly!

---

## Key Learning Points

This example demonstrates:

- **Syntax vs. logical errors**: The code runs without syntax errors, but the logic is wrong
- **How the debugger helps**: You can see what the code is _actually_ doing, not what you _think_ it's doing
- **Variable inspection**: Watch values change in real-time as you step through code
- **Call stack**: See how functions call each other

---

## Tips

- **Multiple breakpoints**: Set breakpoints at different locations to pause at various points
- **Conditional breakpoints**: Right-click a breakpoint to add a condition (e.g., only pause when `i === 5`)
- **Logpoints**: Right-click in the gutter and select "Add Logpoint" to log values without modifying code
- **Debug Console**: Use the DEBUG CONSOLE to evaluate expressions while paused
