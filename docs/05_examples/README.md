# Creative Coding I - p5.js Examples

This folder contains hands-on p5.js examples that accompany Sessions 02 (Instruction) and 03 (Space) of the Creative Coding I course.

## How to Run These Examples

### Option 1: Using a Local Server (Recommended)

1. Open the `05_examples` folder in Visual Studio Code
2. Install the "Live Server" extension if you haven't already
3. Click "Go Live" in the bottom right corner
4. Navigate to any example folder and open `index.html`

### Option 2: Direct File Opening

For these simple examples, you can also just double-click the `index.html` file in any folder to open it directly in your browser. This works because we're loading p5.js from a CDN.

---

## Session 02: Instruction - Examples

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

## Session 03: Space - Examples

These examples introduce 3D graphics:

### 11_3d_basics

**Concepts:** WEBGL mode, 3D primitives, transformations, lighting  
Introduction to 3D in p5.js. Learn about boxes, spheres, cylinders, and how to position them.

### 12_geometric_scene

**Concepts:** 3D composition, algorithmic art, Mondrian/Kandinsky inspiration  
A complete 3D scene demonstrating how to combine everything you've learned. Press R to regenerate!

---

## Progressive Learning Path

For beginners, work through the examples in order:

```
01_basic_setup → 02_variables → 03_for_loops → 04_grid_pattern
       ↓
05_conditionals_modulo → 06_checkerboard → 07_random
       ↓
08_color → 09_mouse_interaction → 10_animation_lines
       ↓
11_3d_basics → 12_geometric_scene
```

## Tips for Learning

1. **Read the comments** - Each sketch is heavily commented to explain what's happening
2. **Modify values** - Change numbers and see what happens
3. **Break things** - Comment out lines to understand their purpose
4. **Combine ideas** - Try mixing concepts from different examples
5. **Check the console** - Press F12 in your browser to see any error messages

## Resources

- [p5.js Reference](https://p5js.org/reference/) - Documentation for all p5 functions
- [p5.js Examples](https://p5js.org/examples/) - Official examples
- [The Coding Train](https://thecodingtrain.com/) - Video tutorials by Daniel Shiffman
- [OpenProcessing](https://openprocessing.org/) - Community sketches for inspiration

---

Happy Coding! 🎨✨
