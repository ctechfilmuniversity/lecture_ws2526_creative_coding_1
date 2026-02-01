# Creative Coding I - Examples

This folder contains hands-on examples that accompany the Creative Coding I course. The examples use both **p5.js** (a JavaScript library for creative coding) and **three.js** (a 3D graphics library).

## How to Run These Examples

### p5.js Examples (01-12, 15-18)

**Option 1: Using a Local Server (Recommended)**

1. Open the `05_examples` folder in Visual Studio Code
2. Install the "Live Server" extension if you haven't already
3. Click "Go Live" in the bottom right corner
4. Navigate to any example folder and open `index.html`

**Option 2: Direct File Opening**

For simple p5.js examples, you can double-click the `index.html` file to open it directly in your browser. This works because we're loading p5.js from a CDN.

### Node.js Examples (13)

1. Open the example folder in VSCode
2. Run with `node app.js` or use the VSCode debugger (press F5)

### Three.js Examples (14, 19, 20)

Three.js examples require npm and a development server:

1. Navigate to the example folder in your terminal
2. Run `npm install` to install dependencies
3. Run `npm run dev` to start the development server
4. Open the URL shown in the terminal (usually `http://localhost:5173`)

---

## Session 02: Instruction - Examples (p5.js)

These examples cover fundamental programming concepts:

### 01_basic_setup

**Concepts:** Canvas creation, basic shapes, fill, stroke  
The foundation of every p5.js sketch. Learn how to create a canvas and draw basic shapes.

### 02_variables

**Concepts:** Variables, built-in variables (width, height, mouseX, mouseY)  
Store and reuse values to make your code flexible.

### 03_for_loops

**Concepts:** For loop syntax, repetition, patterns  
Repeat code multiple times - essential for creating patterns!

### 04_grid_pattern

**Concepts:** Nested loops, 2D grids, row/column indexing  
Create grids by putting one loop inside another.

### 05_conditionals_modulo

**Concepts:** if/else statements, comparison operators, modulo (%)  
Make decisions in your code. The modulo operator returns the remainder of division.

### 06_checkerboard

**Concepts:** Algorithm design, pattern recognition  
The classic algorithmic thinking example! Create a checkerboard using `(row + col) % 2`.

### 07_random

**Concepts:** random() function, controlled randomness  
Add variation and unpredictability. Click to regenerate!

### 08_color

**Concepts:** RGB and HSB color modes, alpha transparency  
Master color manipulation. HSB mode makes working with colors more intuitive.

### 09_mouse_interaction

**Concepts:** Mouse variables, event functions, creating tools  
Make your sketches respond to user input. This example creates a simple drawing tool!

### 10_animation_lines

**Concepts:** The draw() loop, animation, boundary detection, state  
Based on the slides' "Lines" algorithm example. Watch how simple rules create beautiful patterns.

---

## Session 03: Space - Examples (p5.js)

These examples introduce 3D graphics in p5.js:

### 11_3d_basics

**Concepts:** WEBGL mode, 3D primitives, transformations, lighting  
Introduction to 3D in p5.js. Learn about boxes, spheres, cylinders, and how to position them.

### 12_geometric_scene

**Concepts:** 3D composition, algorithmic art, Mondrian/Kandinsky inspiration  
A complete 3D scene demonstrating how to combine everything you've learned. Press R to regenerate!

---

## Session 04: Asynchronism - Examples (p5.js)

These examples cover JavaScript functions and asynchronous programming:

### 15_callbacks

**Concepts:** Callback functions, named vs anonymous functions, event callbacks  
Understand how functions can be passed as arguments and called later when events occur.

### 16_higher_order_functions

**Concepts:** map(), filter(), reduce(), array transformations  
The three essential higher-order functions for working with arrays in JavaScript.

### 17_arrow_functions

**Concepts:** Arrow function syntax, compact function expressions  
Modern JavaScript syntax for writing concise functions: `x => x * 2`.

### 18_async_callbacks

**Concepts:** Synchronous vs asynchronous execution, setTimeout(), loadImage()  
Understand non-blocking code and how JavaScript handles operations that take time.

---

## Session 06: Three.js - Examples

These examples introduce three.js for professional 3D graphics:

### 14_threejs_basics

**Concepts:** Scene, Camera, Renderer, Geometry, Material, Mesh, Render loop  
The fundamental building blocks of every three.js application. See a rotating cube!

### 19_gui_controls

**Concepts:** lil-gui library, interactive controls, params object pattern, onChange callbacks  
Create debug interfaces to tweak scene parameters in real-time. Essential for creative development.

### 20_loading_models

**Concepts:** GLTFLoader, asynchronous model loading, animation playback  
Load external 3D models (glTF/GLB format) and display them in your scene.

---

## Session 07: Debugging - Examples (Node.js)

### 13_debugging_basics

**Concepts:** VSCode debugger, breakpoints, stepping through code, variable inspection  
Learn to use the debugger to find and fix bugs. Contains an intentional bug for practice!

---

## Progressive Learning Path

### Part 1: Programming Fundamentals (p5.js)

```
01_basic_setup → 02_variables → 03_for_loops → 04_grid_pattern
       ↓
05_conditionals_modulo → 06_checkerboard → 07_random
       ↓
08_color → 09_mouse_interaction → 10_animation_lines
```

### Part 2: 3D Graphics (p5.js)

```
11_3d_basics → 12_geometric_scene
```

### Part 3: JavaScript Functions

```
15_callbacks → 16_higher_order_functions → 17_arrow_functions → 18_async_callbacks
```

### Part 4: Three.js

```
14_threejs_basics → 19_gui_controls → 20_loading_models
```

### Part 5: Development Tools

```
13_debugging_basics
```

---

## Tips:

1. **Read the comments** - I've added comments to explain what's happening
2. **Modify values** - Play ariound with the numbers and see what happens
3. **Break things** - Comment out lines to understand their purpose - cmd / on mac, ctrl / on windows
4. **Combine ideas** - Try mixing concepts from different examples
5. **Check the console** - Press F12 in your browser to see any error messages

## Resources

### p5.js

- [p5.js Reference](https://p5js.org/reference/) - Documentation for all p5 functions
- [p5.js Examples](https://p5js.org/examples/) - Official examples
- [The Coding Train](https://thecodingtrain.com/) - Video tutorials by Daniel Shiffman
- [OpenProcessing](https://openprocessing.org/) - Community sketches for inspiration

### Three.js

- [Three.js Documentation](https://threejs.org/docs/) - Official documentation
- [Three.js Examples](https://threejs.org/examples/) - Interactive examples gallery
- [Three.js Journey](https://threejs-journey.com/) - Comprehensive course by Bruno Simon
- [Discover Three.js](https://discoverthreejs.com/) - Free online book

---

Happy Coding!
