name: inverse
layout: true
class: center, middle, inverse

---

# Creative Coding I

### Jonathan Ho | jonathangho@filmuniversitaet.de

#### Film University Babelsberg KONRAD WOLF

---

layout:false

## Today

--

Higher Order Functions

--

- Callback Functions

--

- Notation

--

- Asynchronism

--

<br/>

three.js

- Homework

--

- Gui Controls

--

- Loading models

???

- Environment map
- https://threejs-journey.com/lessons/realistic-render#

Today we're diving into some fundamental JavaScript concepts that are essential for modern web development.

Higher Order Functions might sound intimidating, but they're actually a pattern you've already been using! Every time you've attached an event listener or used `requestAnimationFrame`, you've been working with higher order functions.

Understanding these concepts will:

- Make you more comfortable reading other people's code (you'll see arrow functions everywhere)
- Help you understand how asynchronous operations work (crucial for loading 3D models, images, data)
- Enable you to write cleaner, more professional JavaScript

The three.js portion builds directly on these concepts - loading models requires callbacks, and GUI controls use higher order functions extensively.

---

## Higher Order Functions

With this chapter you will

--

- understand and be be able to work with JavaScript functions
  _ higher order functions
  _ modern (> ECMAScript 2015) syntax \* asynchronous functionality
  --
- and with that **practice your algorithmic thinking**!

???
**ECMAScript 2015** (also called ES6) was a major update to JavaScript that introduced many modern features including arrow functions, classes, and promises. When you see "ES6" or "ECMAScript 2015" mentioned, it refers to this version.

Why does this matter for creative coding?

- **Higher order functions**: Enable patterns like "do this when X happens" (essential for interactivity)
- **Modern syntax**: Makes code shorter and more readable (you'll see this in tutorials and documentation)
- **Asynchronous functionality**: Allows loading resources (images, 3D models, sounds) without freezing your application

Think of it this way: If basic programming is like learning individual words, higher order functions are like learning grammar patterns that let you express more complex ideas efficiently.

---

template:inverse

# Callback Functions

Higher Order Functions  
Asynchronism  
Homework  
Gui Controls  
Loading Models

---

.header[Higher Order Functions]

## Callback Functions

--

```js
// RENDER LOOP
function renderLoop() {
  renderer.render(scene, camera);

  requestAnimationFrame(renderLoop);
}

renderLoop();
```

JavaScript's [`requestAnimationFrame`](https://developer.mozilla.org/en-US/docs/Web/API/window/requestAnimationFrame) function requests a refresh from the browser window.

???
You've already been using callback functions! Look at the `requestAnimationFrame(renderLoop)` line - we're passing the function `renderLoop` as an argument to another function.

**What's happening here:**

1. `renderLoop()` is called once to start everything
2. Inside, after rendering, it asks the browser: "Hey, call `renderLoop` again when you're ready to draw the next frame"
3. This creates our animation loop

The key insight: We're not calling `renderLoop()` with parentheses inside `requestAnimationFrame`. We're passing the function itself as a value, like handing someone a recipe card rather than the cooked meal.

**Analogy**: Imagine giving a friend your phone number (the callback) so they can call you back when they have news. You don't call yourself - you give them the means to reach you later.

---

.header[Higher Order Functions]

## Callback Functions

--
Give functions as argument the next function that should be executed.  
<br >

Such a function as argument is called a _callback_ function.

???

--

<br >

```js
function myCallbackFunc() {
  //...
}

myFunc(arg1, arg2, myCallbackFunc);
```

???

For example: An action is started, and when it finishes, the callback function is called _with the result_ from the action.

---

.header[Higher Order Functions]

## Callback Functions

```js
//https://editor.p5js.org/legie/sketches/Gy0G4ZHLq

function setup() {
  background(240);

  let canvas = createCanvas(512, 512);
  canvas.doubleClicked(changeColor);
}

function changeColor() {
  background(random(255), random(255), random(255));
}
```

???
Here's a practical p5.js example of callbacks in action.

**Breaking it down:**

- `canvas.doubleClicked(changeColor)` says: "When someone double-clicks this canvas, call the `changeColor` function"
- Notice we write `changeColor` without parentheses - we're passing the function itself, not executing it
- p5.js stores this callback and waits. When a double-click happens, it calls `changeColor()` for us

**Why not just write the code directly?** Because we don't know WHEN the user will double-click. The callback pattern lets us define WHAT should happen, and let the system handle WHEN.

This is event-driven programming: instead of constantly checking "Did they click? Did they click?", we say "Call me when they click."

---

.header[Higher Order Functions]

## Callback Functions

Callback functions enable the creation of **dependencies** and **follow-up functionality** if a certain event happened.

--
<br />
Example p5.js:

[`loadImage(path, [successCallback], [failureCallback])`](https://p5js.org/reference/p5/loadImage/)

???
.todo[TODO: Go to reference]

**The loadImage function signature explained:**

- `path`: Where to find the image (required)
- `successCallback`: Function to call when loading succeeds (optional)
- `failureCallback`: Function to call if loading fails (optional)

**Square brackets `[ ]`** in documentation mean "optional parameter."

**Example usage:**

```js
loadImage(
  "cat.jpg",
  (img) => {
    image(img, 0, 0);
  }, // Success: display the image
  (err) => {
    console.log("Failed to load!");
  }, // Failure: show error
);
```

**Why two callbacks?** Because loading can either succeed OR fail, and we might want different behavior for each case. This is a common pattern called "error-first callbacks" or having separate success/failure handlers.

**Analogy**: It's like ordering food delivery with instructions: "When it arrives, put it on the table (success). If there's a problem, call me (failure)."

---

.header[Higher Order Functions]

## Callback Functions

The callback functionality and the option to pass a function as an argument is based on the principle of _higher order functions_.

---

template:inverse

Callback Functions ✓

# Higher Order Functions

Asynchronism  
Homework  
Gui Controls  
Loading Models

???

- What are higher order functions?
- Higher-order functions allow us to abstract over _actions_, not just _values_. They come in several forms. For example, we can have functions that create new functions.
- We have already used higher order function by adding a function as callback to an event listeners.

---

## Higher Order Functions

In mathematics and computer science, a higher-order function is a function that does at least one of the following:

--

- It takes one or more functions as arguments

--

- It returns a function as its result

--

Functions are regular objects in JavaScript and they can be handled almost the same as objects.

???

This means that functions operate on other functions, either by taking them as arguments or by returning them.

Higher-order functions allow us to abstract over _actions_, not just _values_. They come in several forms. For example, we can have functions that create new functions.

We have already used higher order function by adding a function as callback to an event listeners.

[[Wikipedia: Higher-order function]](https://en.wikipedia.org/wiki/Higher-order_function)

**The key concept: Functions as "first-class citizens"**

In JavaScript, functions are treated like any other value:

- You can store them in variables: `const greet = function() { ... }`
- You can put them in arrays: `[func1, func2, func3]`
- You can pass them as arguments: `doSomething(myFunc)`
- You can return them from other functions: `return function() { ... }`

**Analogy**: Think of functions as recipes. Higher-order functions are like a "meta-recipe" - a recipe that takes other recipes as ingredients, or produces new recipes as output.

For example, a "make it spicy" function could take any food recipe and return a spicier version of it. That's a higher-order function!

**Why this matters for creative coding:**

- Event handling: `canvas.mousePressed(handleClick)` - passing a function
- Animation loops: `requestAnimationFrame(animate)` - passing a function
- Array transformations: `colors.map(brighten)` - passing a function

---

## Higher Order Functions

Three exemplary higher-order functions, taking another function as argument, are `map`, `filter`, and `reduce` for working with arrays.

???

Each programming language supporting programming in the functional style supports at least the three functions map, filter, and reduce. The names of the three functions have variations in the different programming languages.

**The "Big Three" of functional programming:**

These three functions are incredibly powerful and you'll see them constantly in modern JavaScript:

1. **`map`**: Transform each item → "Apply this operation to every element"
2. **`filter`**: Keep only matching items → "Keep only elements that pass this test"
3. **`reduce`**: Combine all items into one → "Accumulate all elements into a single result"

**Why learn these?**

- They replace many `for` loops with cleaner, more readable code
- They're used extensively in frameworks like React
- They encourage thinking about data transformations (very useful for creative coding)

**Creative coding applications:**

- `map`: Transform an array of positions into an array of scaled positions
- `filter`: Keep only particles that are still visible
- `reduce`: Calculate the total brightness of all pixels

---

.header[Higher Order Functions]

## `map`

`map` applies a function to each element of its list.

--

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map(getLength);

function getLength(item) {
  return item.length;
}
console.log(lengths);
```

--

```
// 5,7,6
``

https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/map

???
**How `map` works, step by step:**

1. Start with array: `["Bilbo", "Gandalf", "Nazgul"]`
2. For each item, call `getLength(item)`:
   - `getLength("Bilbo")` → returns 5
   - `getLength("Gandalf")` → returns 7
   - `getLength("Nazgul")` → returns 6
3. Collect all return values into a new array: `[5, 7, 6]`

**Key points:**

- `map` ALWAYS returns a new array of the same length
- The original array is unchanged (non-destructive)
- Each element is transformed by your function

**Analogy**: `map` is like a factory assembly line. Each item goes in, gets processed by your function, and comes out transformed. Three items in → three transformed items out.

**Creative coding example:**

```js
// Double all x-positions
let positions = [10, 20, 30];
let doubled = positions.map((x) => x * 2); // [20, 40, 60]
```

---

.header[Higher Order Functions]

## `filter`

`filter` removes all elements of a list not satisfying a condition.

--

```js
let numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10].filter(evenNumbers);

function evenNumbers(num) {
  if (num % 2 === 0) return true;
  else false;
}

console.log("Array:", numbers);
```

--

```js
// Array: [ 2, 4, 6, 8, 10 ]
```

https://www.greatfrontend.com/questions/quiz/what-is-the-difference-between-double-equal-and-triple-equal

???
**How `filter` works:**

1. Start with array: `[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]`
2. For each item, call `evenNumbers(item)`:
   - `evenNumbers(1)` → returns `false` → excluded
   - `evenNumbers(2)` → returns `true` → included
   - `evenNumbers(3)` → returns `false` → excluded
   - ... and so on
3. Keep only items where the function returned `true`: `[2, 4, 6, 8, 10]`

**Key points:**

- `filter` returns a new array that may be shorter (or same length, or empty)
- Your function must return `true` (keep) or `false` (discard)
- Original array is unchanged

**Analogy**: `filter` is like a bouncer at a club. Each item tries to get in, your function decides "yes" or "no", and only the approved ones make it into the new array.

**Creative coding example:**

```js
// Keep only visible particles (alpha > 0)
let particles = [{ alpha: 0 }, { alpha: 0.5 }, { alpha: 1 }];
let visible = particles.filter((p) => p.alpha > 0);
// Result: [{alpha: 0.5}, {alpha: 1}]
```

---

.header[Higher Order Functions]

## `reduce`

`reduce` successively applies a binary operation to pairs of the list and therefore reduces the list to a value.

--

<br />
`array.reduce(function(total, currentValue, currentIndex, arr), initialValue)`

???
**Understanding reduce's parameters:**

- `total` (also called "accumulator"): The running result being built up
- `currentValue`: The current array element being processed
- `currentIndex`: (optional) Position in the array
- `arr`: (optional) The original array
- `initialValue`: Starting value for `total` (often 0 for sums, [] for arrays, {} for objects)

`reduce` is the most powerful but also most confusing of the three. Take your time with this one!

---

.header[Higher Order Functions]

## `reduce`

`array.reduce(function(total, currentValue))`

--

```js
let sum = [15.6, 2.3, 1.1, 4.7].reduce(getSum, 0);

function getSum(total, num) {
  return total + Math.round(num);
}
console.log(sum);
```

???

- `reduce` successively applies a binary operation to pairs of the list and therefore reduces the list to a value.

**How reduce works, step by step:**

Starting with `total = 0` (our initial value):

1. `getSum(0, 15.6)` → `0 + 16` → returns `16` (this becomes the new total)
2. `getSum(16, 2.3)` → `16 + 2` → returns `18`
3. `getSum(18, 1.1)` → `18 + 1` → returns `19`
4. `getSum(19, 4.7)` → `19 + 5` → returns `24`

Final result: `24`

**Analogy**: `reduce` is like a snowball rolling downhill. It starts small (initial value), and each element adds to it, until you have one final result.

Or think of it as "folding" a list: you take the first two elements, combine them, take that result and the next element, combine them, and so on until you have one value.

**Creative coding example:**

```js
// Calculate total distance traveled
let segments = [10, 25, 15, 30];
let totalDistance = segments.reduce((sum, d) => sum + d, 0); // 80
```

--

```
// 24
```

---

.center[<img src="../02_scripts/img/javascript/mapfilterreduce.jpg" alt="mapfilterreduce" style="width:80%;">.imgref[[[Modernes Cpp]](https://www.modernescpp.com/index.php/higher-order-functions)]]

???
**Visual summary of the "Big Three":**

- **map** (top): Same number of vegetables go in and out, but each is transformed (sliced/diced)
- **filter** (middle): Only items passing the test make it through (green vegetables only)
- **reduce** (bottom): All items are combined into a single result (soup!)

This diagram perfectly captures the essence:

- `map`: Transform each → same quantity, different form
- `filter`: Select some → fewer items, same form
- `reduce`: Combine all → one result

**Chaining them together** is where things get powerful:

```js
let result = numbers
  .filter((n) => n > 0) // Keep positives
  .map((n) => n * 2) // Double them
  .reduce((a, b) => a + b); // Sum them
```

---

## Higher Order Functions

JavaScript offers two ways to write the code for higher order functions more compactly:

--

- **_Anonymous_** functions

--

- **_Arrow_** functions

-- \* The modern and preferred way

???
You've seen the full function syntax:

```js
function doSomething(x) {
  return x * 2;
}
```

But when passing functions as arguments, we often don't need to give them names. That's where anonymous and arrow functions come in - they're just shorter ways to write the same thing.

Think of it like signing a document: sometimes you write your full legal name (named function), sometimes you just initial it (anonymous function), and sometimes you use a quick symbol (arrow function). Same purpose, different formality levels.

---

template:inverse

### Higher Order Functions

# Anonymous Functions

???

TASK: Does anyone know what these are?

- anonymous functions are functions that are dynamically declared at runtime.

**Anonymous** literally means "without a name." In most languages, functions have names. But in JavaScript, you can create functions that exist without being named - they're just values that happen to be functions.

---

.header[Higher Order Functions]

## Anonymous Functions

They are called _anonymous_ functions because they aren’t given a name in the same way as normal functions.

--

```js
function() {
    // Function Body
}
```

--

_An anonymous function is a function without a name._

--

Hence, anonymous functions are

--

- directly placed, where they are needed, or

--

- stored in a variable.

???
**Why use anonymous functions?**

1. **One-time use**: If you only need a function once, why give it a name?
2. **Locality**: The code that uses the function is right where you need it
3. **Less pollution**: You don't create unnecessary named functions floating around

**The tradeoff:**

- Named functions can be reused and are easier to debug (error messages show the name)
- Anonymous functions are concise but can be harder to trace in error logs

**Analogy**: Named functions are like contacts in your phone (saved for reuse). Anonymous functions are like typing a number directly (quick, one-time use).

---

.header[Higher Order Functions | Anonymous Functions]

## Separate Function Definition

```js
function setup() {
  let canvas = createCanvas(512, 512);
  canvas.doubleClicked(changeColor);

  background(240);
}

function changeColor() {
  background(random(255), random(255), random(255));
}
```

???
**The "traditional" approach** - named function as callback:

Here, `changeColor` is a named function defined separately. We pass its name (without parentheses!) to `doubleClicked`.

**Pros of this approach:**

- Clear, readable
- Function can be reused elsewhere
- Easy to debug (errors will say "in changeColor")

**Cons:**

- Function might be far away from where it's used
- If only used once, the name is extra noise

This is perfectly fine code! But we can make it more compact...

---

.header[Higher Order Functions | Anonymous Functions]

## Directly Placed

```js
function setup() {
  let canvas = createCanvas(512, 512);

  // The callback as anonymous function
  canvas.doubleClicked(function () {
    background(random(255), random(255), random(255));
  });

  background(240);
}
```

--

The value of the first argument of the `.doubleClicked()` event is a function without a name.

???

- The above makes use of the principle of higher order functions.

**The anonymous function approach** - function defined right where it's used:

Instead of creating `changeColor` separately and passing its name, we define the function right inside the parentheses of `doubleClicked()`.

**Reading this code:**

```js
canvas.doubleClicked(   // When double-clicked, call...
    function() {        // ...this unnamed function that...
        background(...) // ...changes the background
    }
);
```

**Pros:**

- Code is all in one place - you can see exactly what happens without jumping around
- No extra function name to think about

**Cons:**

- Can get messy if the function is long
- Can't reuse this function elsewhere (it has no name to call!)

**Key insight**: `function() { ... }` is a VALUE. Just like `5` is a number value, `function() { ... }` is a function value. We're passing that value as an argument.

---

.header[Higher Order Functions | Anonymous Functions]

## Directly Placed

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map(getLength);

function getLength(item) {
  return item.length;
}

console.log(lengths); // 5,7,6
```

--

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map(function (item) {
  return item.length;
});

console.log(lengths); // 5,7,6
```

---

.header[Higher Order Functions | Anonymous Functions]

## Stored In a Variable

Anonymous function can also be stored in and invoked (called) using a variable name.

```js
const greatMath = function (a, b) {
  return a * b;
};

let result = greatMath(4, 3);

console.log(result);
```

--

This is also called a _function expression_.

--

Function expressions stored in variables do not need function names. They are always invoked using the variable name.

???

- What is the difference between a functions declaration and a function expression?
- https://stackoverflow.com/questions/1013385/what-is-the-difference-between-a-function-expression-vs-declaration-in-javascrip
  - Function declarations load before any code is executed.
  - Function expressions load only when the interpreter reaches that line of code.

**Function expression = storing a function in a variable**

The function itself has no name (it's anonymous), but the VARIABLE has a name. We call it using the variable name.

**Two ways to define functions:**

1. **Function Declaration** (has a name):

```js
function multiply(a, b) {
  return a * b;
}
```

2. **Function Expression** (stored in variable):

```js
const multiply = function (a, b) {
  return a * b;
};
```

Both create functions that work the same way when called!

**Analogy**: Think of a function as a recipe card.

- Function declaration: The card has a title printed on it ("Chocolate Cake Recipe")
- Function expression: A blank card that you store in a labeled folder ("multiply")

Either way, you can follow the recipe. The difference is how you find/reference it.

---

.header[Higher Order Functions]

## Function Expressions

The subtle difference between a functions declaration and a function expression is _when_ a function is created by the JavaScript engine:

--

- A function expression is created when the execution reaches it and is usable only from that moment on.

--

- A function declaration can be called earlier than it is defined.

???

For example, a global Function Declaration is visible in the whole script, no matter where it is.

That’s due to internal algorithms. When JavaScript prepares to run the script, it first looks for global Function Declarations in it and creates the functions. We can think of it as an “initialization stage”.

And after all Function Declarations are processed, the code is executed. So it has access to these functions.

---

.header[Higher Order Functions]

## Function Expressions

For example, this works:

```js
//Function Declaration

sayHi("Hans"); // Hello, Hans

function sayHi(name) {
  console.log("Hello " + name);
}
```

--

The function declaration `sayHi` is created when JavaScript is preparing to start the script and is visible everywhere in it.

---

.header[Higher Order Functions]

## Function Expressions

If it were a function expression, then it wouldn’t work:

```js
//Function Expression

sayHi("Hans"); // error!

const sayHi = function (name) {
  console.log("Hello " + name);
};
```

---

.header[Higher Order Functions]

## Anonymous Functions

All this is possible because functions in Javascript are just a special type of object.

--

<br >

This means they can be used in the same way as any other object.

--

- Stored in variables
- Passed to other functions
- Be returned from functions

.footnote[[[javaScript.info]](../02_scripts/https6//www.w3schools.com/js/js_function_definition.asp)]

???

- text
  They can be stored in variables, passed to other functions as parameters or be returned from a function using the return statement. Functions are always objects, no matter how they are created.

---

template: inverse

### Higher Order Functions

# Arrow Functions

--

## _(this is only different syntax)_

???

Arrow functions were added in 2015, mostly to make it possible to write function expressions more compactly.

[[javaScript.info]](../02_scripts/https6//www.w3schools.com/js/js_function_definition.asp) [[Eloquent JavaScript]](../02_scripts/https6//eloquentjavascript.net/03_functions.html)

**The most important thing to know**: Arrow functions are just a shorter way to write the same thing!

When you see `=>` in JavaScript, don't panic - it's just a compact function. The arrow `=>` replaces the word `function`.

**Why arrows?**

- Less typing
- Looks cleaner, especially for short callbacks
- Modern JavaScript standard (you'll see this everywhere in tutorials, documentation, libraries)

**Evolution of the same function:**

```js
// Traditional named function
function double(x) {
  return x * 2;
}

// Anonymous function expression
const double = function (x) {
  return x * 2;
};

// Arrow function
const double = (x) => {
  return x * 2;
};

// Compact arrow function
const double = (x) => x * 2;
```

All four do exactly the same thing!

---

.header[Higher Order Functions]

## Arrow Functions

Arrow functions allow an even shorter syntax for writing function expressions (starting with ECMAScript 2015).

???

- In certain cases you don't need the function keyword, the return keyword, nor the curly brackets.

--

```js
// ES5
const myFunction = function (param1, param2) {
  // do something
};
```

--

```js
// ECMAScript 2015
const myFunction = (param1, param2) => {
  // do something
};
```

---

.header[Higher Order Functions]

## Arrow Functions

```js
const myFunction = (param1, param2) => {
  // do something
};
```

An arrow comes after the list of parameters and is followed by the function’s body. It expresses something like

--

> This input (the parameters) produces this result (the body).

--

`this input => this result`

???
**Reading arrow functions:**

Think of `=>` as saying "produces" or "results in":

`(param1, param2) => { ... }`

Read as: "param1 and param2 **produce** this result"

**The anatomy:**

```
(parameters) => { function body }
     ↓              ↓
   INPUT          OUTPUT
```

**Analogy**: The arrow is like an assembly line conveyor belt. Things go in on the left, get processed, and come out on the right.

`ingredients => meal`
`numbers => sum`
`event => response`

---

.header[Higher Order Functions]

## Arrow Functions

If there are no parameters, the `()` just stay empty:

--

```js
// ES5
const myFunction = function () {

    // do something
}

--

// ECMAScript 2015
const myFunction = () => {

    // do something
}
```

---

.header[Higher Order Functions]

## Arrow Functions

With this, we can make the anonymous function for changing the canvas color in a p5 sketch even more compact:

```js
// ES5 Anonymous syntax
canvas.doubleClicked(function () {
  background(random(255), random(255), random(255));
});
```

--

```js
// ECMAScript 2015 Arrow syntax
canvas.doubleClicked(() => background(random(255), random(255), random(255)));
```

---

.header[Higher Order Functions]

## Arrow Functions

```js
function setup() {
  let canvas = createCanvas(512, 512);

  // The callback as arrow function
  canvas.doubleClicked(() => background(random(255), random(255), random(255)));

  background(240);
}
```

---

.header[Higher Order Functions]

## Arrow Functions

If there is only one parameter, we can omit the `()`.

```js
// ES5
const myFunction = function (param1) {
  // do something
};

// ECMAScript 2015
const myFunction = (param1) => {
  // do something
};
```

---

.header[Higher Order Functions ]

## Arrow Functions

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map(getLength);

function getLength(item) {
  return item.length;
}

console.log(lengths); // 5,7,6
```

--

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map(function (item) {
  return item.length;
});

console.log(lengths); // 5,7,6
```

---

.header[Higher Order Functions ]

## Arrow Functions

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map(getLength);

function getLength(item) {
  return item.length;
}

console.log(lengths); // 5,7,6
```

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map((item) => {
  return item.length;
});

console.log(lengths); // 5,7,6
```

---

.header[Higher Order Functions]

## Arrow Functions

Also, when there is only one line of code, you can omit the return and the {}.

```js
// ES5
const result = function (x, y) {
  return x * y;
};

// ECMAScript 2015
const result = (x, y) => x * y;
```

---

.header[Higher Order Functions]

## Arrow Functions

Once again, when there is only one parameter, you can also omit the parentheses around the parameter list.

```js
// ES5
const result = function (x) {
  return x * x;
};

// ECMAScript 2015
const result = (x) => x * x;
```

---

.header[Higher Order Functions ]

## Arrow Functions

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map(getLength);

function getLength(item) {
  return item.length;
}

console.log(lengths); // 5,7,6
```

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map((item) => item.length);

console.log(lengths); // 5,7,6
```

???
**The complete transformation:**

From 8 lines of code:

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map(getLength);
function getLength(item) {
  return item.length;
}
```

To 1 line:

```js
let lengths = ["Bilbo", "Gandalf", "Nazgul"].map((item) => item.length);
```

Both do exactly the same thing! The arrow function version is just more compact.

**Reading the compact version:**

- `.map(...)` = "apply this to each item"
- `item =>` = "for each item..."
- `item.length` = "...return its length"

This compact style is what you'll see most often in modern JavaScript code, especially in tutorials and documentation.

---

.header[Higher Order Functions]

## Arrow Functions

For now you can remember that functions, anonymous functions, function expression and arrow functions do the same thing.

--

  <br >
They do have slight differences but nothing we need to be bothered about at this point.

???

When Is The Arrow Function Helpful?

Arrow functions do not have their own this. They are not well suited for defining object methods.

Arrow functions are not hoisted. They must be defined before they are used.

Using `const` is safer than using `let`, because a function expression is always constant value.

You can only omit the return keyword and the curly brackets if the function is a _single statement_. Because of this, it might be a good habit to always keep them:

---

.header[Higher Order Functions]

## Arrow Functions

No matter what your programming level is, you **must understand higher order functions**, meaning that functions can be input and return arguments.

--

<br >

With that we can build functionality chains with callbacks in order to enable asynchron execution.

--

<br >

The best syntax for higher order functions is the **arrow syntax**.

???
**Summary so far:**

1. **Higher order functions** = functions that take/return other functions
2. **Callbacks** = functions passed as arguments, called later
3. **Anonymous functions** = functions without names
4. **Arrow functions** = compact syntax using `=>`

These concepts are interconnected:

- Callbacks are a USE of higher order functions
- Anonymous/arrow functions are SYNTAX OPTIONS for writing callbacks

**Why this matters**: The three.js code you'll write uses all of these! Loading models, handling events, animation loops - they all rely on callbacks and higher order functions.

---

template:inverse

Callback Functions ✓  
Higher Order Functions ✓

# Asynchronism

Homework  
Gui Controls  
Loading Models

???

- What does it mean?
  - Occurring at different times
  - Allowing the client to continue during processing
  - Having many actions occurring at a time, in any order, without waiting for each other.
- Do you have examples for asynchronity in every day life?
  - Recorded communication
  - Personal plans alla "when I have done this, I will..."
  - Promises
  - Thinking in general?
- How does the digital transformation re-shape time for us?
- Which role does asynchronism play in regard to web development?

**Asynchronism** is one of the most important concepts in web development!

The web is inherently asynchronous:

- Files take time to download
- Users interact unpredictably
- Servers respond at varying speeds

Without asynchronous programming, your application would freeze every time it waited for something.

**Real-world analogy**:

- **Synchronous**: Standing in line at a bank, waiting for each person ahead of you
- **Asynchronous**: Taking a number at the deli counter and continuing to shop while waiting

---

## Asynchronism

Do you have examples for asynchronity in every day life?

--

- Recorded communication e.g. voice messages

- Personal plans e.g. "when I have done this, I will..."
- Promises e.g. "I will call you back when I have finished my work"

--

### How does the digital transformation re-shape time for us?

--

### Which role does asynchronism play in regard to web development?

---

.header[Asynchronism]

## Synchronism

--

In a _synchronous_ programming model, things happen one at a time.

--
<br >

A **single thread** of control:

```
1 thread ->   |<---A---->||<----B---------->||<------C----->|
```

.footnote[[[Eloquent Javascript]](https://eloquentjavascript.net/11_async.html), [[stackoverflow]](https://stackoverflow.com/questions/748175/asynchronous-vs-synchronous-execution-what-is-the-difference)]

???

Tasks are executed sequentially, one after the other. In this model:

- A task must complete before the next one starts.
- The program “waits” for each operation to finish before moving forward.
- This is straightforward to understand but can lead to inefficiency if tasks involve waiting (e.g., I/O operations) since the CPU remains idle during those waiting periods.

When you call a function that performs a long-running action, it returns only when the action has finished and it can return the result. This stops your program for the time the action takes.

Synchronous or Synchronized means "connected", or "dependent" in some way.

--

> You are in a queue to get a movie ticket. You cannot get one until everybody in front of you gets one, and the same applies to the people queued behind you.

???

https://stackoverflow.com/questions/748175/asynchronous-vs-synchronous-execution-what-is-the-difference

**Synchronous = blocking**

When you call a synchronous function, your program WAITS until that function completes before moving on.

**Example in code:**

```js
console.log("Starting"); // 1. This runs
let result = heavyCalculation(); // 2. WAIT here until done...
console.log("Finished"); // 3. Only then this runs
```

**Problem**: If `heavyCalculation()` takes 5 seconds, your entire program (and UI) freezes for 5 seconds!

**The movie ticket analogy is perfect:**

- You can't do anything else while waiting in line
- Everyone waits sequentially
- If someone takes forever, everyone behind is stuck

---

.header[Asynchronism]

## Synchronism

In a _synchronous_ programming model, things happen one at a time.

<br />

Threads can be **parallel**:

```
thread A -> |<---A---->|
                        \
thread B ------------>   ->|<----B---------->|
                                              \
thread C ---------------------------------->   ->|<------C----->|
```

???
Parallel threads involve running multiple tasks simultaneously on different CPU cores or processors. Here’s how they relate:

- A thread is the smallest unit of a program that can execute independently.
- Parallelism leverages multiple threads to perform tasks at the same time, speeding up execution for CPU-bound or large workloads.

In a synchronous model, even if threads exist, they often wait for one another because execution order is linear. Conversely, an asynchronous model or a multi-threaded parallel approach can allow different tasks to run independently, using the system’s resources more efficiently.

---

## Asynchronism

An _asynchronous_ model allows multiple things to happen at the same time.

???

An asynchronous programming model allows tasks to execute independently without blocking the flow of the program. In this model:

- Tasks that take time (e.g., file I/O, network requests) don’t stop the execution of other tasks.
- Instead of waiting, the program moves on to the next task while the original task runs in the background.
- When the background task is completed, it signals the program (using callbacks, promises, or events) to handle the result.

This model improves efficiency, especially for applications with many I/O operations, as it avoids wasting time waiting for tasks to complete. Unlike synchronous programming, where tasks are executed one after another, asynchronous programming enables concurrency, allowing the system to manage multiple operations at the same time.

Asynchronous means they are totally independent and neither one must consider the other in any way, either in the initiation or in execution.

**Another way to describe the difference is that waiting for actions to finish is **implicit** in the synchronous model, while it is **explicit**, under our control, in the asynchronous one.**

--
<br >

**Async threads** of control:

```
         A-Start ------------------------------------------ A-End
           | B-Start -----------------------------------------|--- B-End
           |    |      C-Start ------------------- C-End      |      |
           |    |       |                           |         |      |
           V    V       V                           V         V      V
1 thread->|<-A-|<--B---|<-C-|-A-|-C-|--A--|-B-|--C-->|---A---->|--B-->|
```

.footnote[[[Eloquent Javascript]](https://eloquentjavascript.net/11_async.html), [[stackoverflow]](https://stackoverflow.com/questions/748175/asynchronous-vs-synchronous-execution-what-is-the-difference)]

---

## Asynchronism

An _asynchronous_ model allows multiple things to happen at the same time.

> You are in a restaurant with many other people. You order your food. Other people can also order their food, they don't have to wait for your food to be cooked and served to you before they can order. In the kitchen restaurant workers are continuously cooking, serving, and taking orders. People will get their food served as soon as it is cooked.

.footnote[[[Eloquent Javascript]](https://eloquentjavascript.net/11_async.html), [[stackoverflow]](https://stackoverflow.com/questions/748175/asynchronous-vs-synchronous-execution-what-is-the-difference)]

???

An asynchronous programming model allows tasks to execute independently without blocking the flow of the program. In this model:

- Tasks that take time (e.g., file I/O, network requests) don’t stop the execution of other tasks.
- Instead of waiting, the program moves on to the next task while the original task runs in the background.
- When the background task is completed, it signals the program (using callbacks, promises, or events) to handle the result.

This model improves efficiency, especially for applications with many I/O operations, as it avoids wasting time waiting for tasks to complete. Unlike synchronous programming, where tasks are executed one after another, asynchronous programming enables concurrency, allowing the system to manage multiple operations at the same time.

Asynchronous means they are totally independent and neither one must consider the other in any way, either in the initiation or in execution.

**Another way to describe the difference is that waiting for actions to finish is **implicit** in the synchronous model, while it is **explicit**, under our control, in the asynchronous one.**

---

## Asynchronism

Example image loading in p5:

- [The preload function ⬀](https://editor.p5js.org/legie/sketches/nP0QN8GKy)
- [A custom callback function ⬀](https://editor.p5js.org/legie/sketches/OL1uYHlfF)

???
**Why p5.js has a `preload()` function:**

Loading images takes time (network requests). If you try to use an image before it's loaded, you get errors or empty results.

**Two solutions p5.js offers:**

1. **`preload()`**: p5.js automatically waits for everything in `preload()` to finish before running `setup()`. Simple but inflexible.

2. **Callbacks**: Use the callback parameter of `loadImage()` to specify what happens WHEN the image is ready. More control but requires understanding async.

**Example comparison:**

```js
// Using preload (synchronous-feeling)
function preload() {
  img = loadImage("cat.jpg"); // p5 waits here
}

// Using callback (explicitly asynchronous)
function setup() {
  loadImage("cat.jpg", (img) => {
    image(img, 0, 0); // Only runs when image is ready
  });
}
```

This is directly relevant to three.js, where loading 3D models follows the same async pattern!

---

.header[Asynchronism]

## Callback Functions

A callback function in JavaScript can be either synchronous or asynchronous, depending on how and when it is invoked.

---

.header[Asynchronism]

## Callback Functions

A synchronous callback is executed immediately during the execution of the function it is passed to:

--

```js
function printing(str) {
  console.log(str);
}

function greet(name, callback) {
  callback(name); // Callback executed immediately
}

greet("Hello Alice", printing);
// Output: Hello Alice!
```

---

.header[Asynchronism]

## Callback Functions

An asynchronous callback is executed later, after the main function has completed, often in response to an event or after some delay:

```js
function printing(str) {
  console.log(str);
}

setTimeout(printing, 500, "Time is up!!");
// -> printing is called after 500 milliseconds
```

???
The key is when the callback is executed in the program’s flow.

The `setTimeout` function, available both in Node.js and in browsers, waits a given number of milliseconds (a second is a thousand milliseconds) and then calls a function.
.todo[TODO: Go to] https://developer.mozilla.org/en-US/docs/Web/API/setTimeout

**What makes `setTimeout` asynchronous:**

The code AFTER `setTimeout` runs immediately - it doesn't wait!

```js
console.log("1 - Start");
setTimeout(() => console.log("2 - Delayed"), 500);
console.log("3 - End");

// Output:
// 1 - Start
// 3 - End
// (500ms later) 2 - Delayed
```

Notice: "3 - End" prints BEFORE "2 - Delayed" even though it comes after in the code!

**The `setTimeout` signature:**
`setTimeout(callback, delay, ...args)`

- `callback`: Function to call later
- `delay`: Milliseconds to wait (1000 = 1 second)
- `...args`: Optional arguments to pass to the callback

**Analogy**: `setTimeout` is like setting a kitchen timer. You set it and continue cooking other things. When it goes off, you handle the timer (the callback runs).

---

.header[Asynchronism]

## Callback Functions

> Callbacks are the veins of a web application. They enable a balanced, non-blocking flow of asynchronous control going back and forth between parts of the application.

.footnote[[[Fred Schott]](../02_scripts/http:6/fredkschott.com/post/2014/03/understanding-error-first-callbacks-in-node-js/)]

---

## Asynchronism

We just saw the tip of the iceberg!

<br />
The most relevant asynchron functionality syntax:

- Promises
- then..catch
- Async / Await

--

For proper web development you would need to understand the above concepts.

???

You must **understand promises** but not necessarily write them from scratch yourself.

---

template:inverse

Callback Functions ✓  
Higher Order Functions ✓  
Asynchronism ✓

# Homework

Gui Controls  
Loading Models

---

template:inverse

Callback Functions ✓  
Higher Order Functions ✓  
Asynchronism ✓  
Homework ✓

# Gui Controls

Loading Models

---

template:inverse

# GUIs

???
**GUI = Graphical User Interface**

In creative coding, GUIs let us tweak parameters in real-time without changing code. This is incredibly valuable for:

- Fine-tuning visual parameters (colors, sizes, speeds)
- Debugging (seeing values as they change)
- Letting non-coders interact with your work
- Creating demo/presentation modes

---

## GUIs

While you can create your own debug UI using HTML / CSS / JS, there are already multiple libraries:

.footnote[[[three.js Journey]](https://threejs-journey.com/lessons/debug-ui#introduction)]

.left-even[

- [lil-gui](https://lil-gui.georgealways.com/)
- [dat.GUI](https://github.com/dataarts/dat.gui)
- [control-panel](https://github.com/freeman-lab/control-panel)
- [ControlKit](https://github.com/automat/controlkit.js)
- [Uil](https://github.com/lo-th/uil)
- [Tweakpane](https://cocopon.github.io/tweakpane/)
- [Guify](https://github.com/colejd/guify)
- [Oui](https://github.com/wearekuva/oui)
  ]

--
.right-even[

- Not three.js specific
- Possibly _debug UIs_
  ]

???

- https://bruno-simon.com/#debug

**Why use a library instead of building your own?**

- Saves massive amounts of time
- Professional-looking controls out of the box
- Handles all the complex UI interactions
- Consistent, well-tested behavior

**"Debug UI"** refers to interfaces meant for development/testing, not for end users. You'd typically hide these in a final release.

**lil-gui is our choice** because:

- It's the most commonly used with three.js
- Simple API
- Lightweight
- Well documented

---

.header[GUIs]

## `lil-gui`

--

- Mostly used with three.js

--

- Replacement for dat.GUI

--

- [Various of features and styles](https://lil-gui.georgealways.com/examples/kitchen-sink/)
  - Numbers and Sliders
  - Dropdowns
  - Color
  - Text
  - Checkbox
  - Select
  - Button

???

- https://threejs.org/examples/#webgl_animation_skinning_morph
- https://filters.pixijs.download/main/demo/index.html
  - Range —for numbers with minimum and maximum value
  - Color —for colors with various formats
  - Text —for simple texts
  - Checkbox —for booleans (true or false)
  - Select —for a choice from a list of values
  - Button —to trigger functions

---

.header[GUIs]

## `lil-gui`

???

- What do we do to install it?

**Standard npm workflow:**

1. Install the package
2. Import into your JavaScript
3. Create an instance
4. Add controls

This is the same pattern for almost any JavaScript library!

--

Install with npm:

`npm install lil-gui`

--

<br />
Import the module:

```js
import { GUI } from "lil-gui";
```

--

Create an instance:

```js
const gui = new GUI();
```

---

.header[GUIs]

## `lil-gui`

> ...an interface for changing the properties of any JavaScript object at runtime.

---

.header[GUIs | `lil-gui`]

## Adding Controllers

We always need to **modify an object's property**:

<br />
`gui.add(object, property)`

--

```
gui.add(mesh.position, 'y')
```

--

> lil-gui will choose an appropriate controller based on the property's data type.

.footnote[[[lil-gui]](https://lil-gui.georgealways.com/#Guide#Numbers-and-Sliders)]

???
**The key concept**: lil-gui modifies EXISTING properties on objects.

`gui.add(object, 'property')` means:

- Look at `object`
- Find its property called `'property'` (as a string!)
- Create a controller that modifies that property

**Why a string?** Because we need to tell lil-gui the NAME of the property to modify. `mesh.position.y` gets the VALUE, but `'y'` is the NAME.

**Example breakdown:**

```js
gui.add(mesh.position, 'y')
       └─ the object   └─ property name (string)
```

This creates a controller that directly modifies `mesh.position.y` when you drag the slider!

---

.header[GUIs | `lil-gui`]

## Adding Controllers

```
gui.add(mesh.position, 'y')
```

--
.center[<img src="../02_scripts/img/space/gui_01.png" alt="gui_01" style="width:50%;"> ]

???
lil-gui automatically detected that `mesh.position.y` is a number, so it created a number input field.

The value updates in real-time as you type or drag!

---

.header[GUIs | `lil-gui`]

## Adding Controllers

You can specify the minimum value, the maximum value, the precision and give a name:

```
gui.add(mesh.position, 'y', -1, 1, 0.001, 'Elevation');
```

--
.center[<img src="../02_scripts/img/space/gui_02.png" alt="gui_02" style="width:50%;"> ]

.footnote[[[three.js Journey]](https://threejs-journey.com/lessons/debug-ui#introduction)]

---

.header[GUIs | `lil-gui`]

## Adding Controllers

Alternatively, you can spell out and chain the parameter properties:

```
gui.add(mesh.position, 'y').min(- 10).max(10).step(0.01).name('Elevation');
```

.footnote[[[three.js Journey]](https://threejs-journey.com/lessons/debug-ui#introduction)]

--

```
gui
    .add(mesh.position, 'y')
    .min(-1)
    .max(1)
    .step(0.001)
    .name('Elevation');
```

???

[https://lil-gui.georgealways.com/#Guide#Numbers-and-Sliders](https://lil-gui.georgealways.com/#Guide#Numbers-and-Sliders)

**Method chaining** is a common pattern in JavaScript where methods return the object they belong to, allowing you to call multiple methods in sequence.

```js
gui
  .add(mesh.position, "y") // Returns the controller
  .min(-1) // Also returns the controller
  .max(1) // Also returns the controller
  .step(0.001) // Also returns the controller
  .name("Elevation"); // Final configuration
```

Each method modifies the controller and returns it, so you can keep adding more configuration.

**Why use this pattern?**

- More readable (clear what each parameter means)
- Easier to modify later
- Self-documenting code

---

.header[GUIs | `lil-gui` | Adding Controllers]

## Property Types

```
gui.add(material, 'wireframe')
```

--

**lil-gui will choose an appropriate controller based on the property's data type.**

.footnote[[[lil-gui Documentation]](https://lil-gui.georgealways.com/#Guide)]

--

<br >

Since 'wireframe' is a boolean, a checkbox is created:

.center[<img src="../02_scripts/img/space/gui_03.png" alt="gui_03" style="width:45%;"> ]

---

.header[GUIs | `lil-gui` | Adding Controllers]

## Property Types

```
gui.add( obj, 'boolean property' );      // checkbox
gui.add( obj, 'string property' );       // text field
gui.add( obj, 'number property' );       // number field
gui.add( obj, 'function property' );     // button
```

---

.header[GUIs | `lil-gui`]

## Non-Property Controls

--

```js
let myValue = 24;
gui.add(myValue, ?);
```

--

For adjusting your own variable, wrap them in a JavaScript object:

--

```js
const myObject = { myValue: 24 };
gui.add(myObject, "myValue");
```

--

.center[<img src="../02_scripts/img/space/gui_04.png" alt="gui_04" style="width:40%;"> ]

???
**The problem**: lil-gui needs an object and a property name. A standalone variable like `let myValue = 24` isn't a property on any object.

**The solution**: Create an object to hold your values!

```js
// Instead of:
let speed = 5; // Can't use with lil-gui directly
let rotation = 0.01; // Can't use with lil-gui directly

// Do this:
const params = {
  speed: 5,
  rotation: 0.01,
};

gui.add(params, "speed").min(0).max(10);
gui.add(params, "rotation").min(0).max(1);

// In your render loop:
mesh.rotation.y += params.rotation; // Use params.rotation, not rotation
```

This pattern (using a `params` or `settings` object) is extremely common in creative coding!

---

.header[GUIs | `lil-gui`]

## Non-Property Controls

Create one common GUI-object, e.g.:

```js
const guiParameter;
```

--
Add values to it:

```js
guiParameter.newKey = 5;
```

--

```js
guiParameter.spinRotation = 100;
```

---

.header[GUIs | `lil-gui` | Non-Property Controls]

## Functions

By default, if we pass a function as property, a button is created.

--

```
function spin() {
    cube.rotation.x += 100;
    cube.rotation.y += 180;
}
```

--

```
const guiParameter = {rotate: spin};
gui.add(guiParameter, 'rotate');
```

---

.header[GUIs | `lil-gui`]

## Change Events

--
You can further control what should happen upon a GUI change

--

- Define a function that should be called every time a controller is changed
- Pass that function to the controller's `onChange` method
- `onChange` passes the new GUI value to your function

--

.footnote[[[lil-gui Documentation]](https://lil-gui.georgealways.com/#Guide)]

???

- So long as it originates from that controller and not from code elsewhere

**`onChange` is a callback!** Here's where higher order functions come back:

- `onChange` is a method that takes a function as an argument
- That function is called whenever the value changes
- The new value is passed to your callback

This is the same pattern we learned earlier, now applied to GUIs!

---

.header[GUIs | `lil-gui`]

## Change Events

```js
const myObject = { myValue: 24 };

gui
  .add(myObject, "myValue")
  .onChange((myValueChange) => console.log(myObject.myValue));
```

???
**Breaking this down:**

- `.onChange(...)` takes a callback function
- `myValueChange => ...` is an arrow function that receives the new value
- The callback runs every time the slider/input changes

**Why use `onChange`?** Sometimes changing one value should trigger other updates:

- Changing a "master brightness" should adjust all lights
- Changing a color should regenerate textures
- Changing a seed should regenerate procedural content

---

.header[GUIs | `lil-gui` | Change Events]

## Different Notation

```js
const guiParams = { elevate: 3 };

gui
  .add(guiParams, "elevate")
  .min(-10)
  .max(10)
  .step(0.1)
  .onChange((value) => {
    mesh1.position.y = value;
    mesh2.position.y = value;
  });
```

???
**Practical example**: One slider controls multiple meshes!

When you drag the "elevate" slider:

1. lil-gui updates `guiParams.elevate`
2. `onChange` callback fires with the new value
3. Both `mesh1` and `mesh2` move to that Y position

**The arrow function receives `value`** which is the new slider value. You can name this parameter whatever you want (`value`, `v`, `newY`, etc.).

---

.header[Higher Order Functions | three.js]

## Window Resizing

--

```
window.addEventListener('resize', () =>  {

    renderer.setSize(window.innerWidth, window.innerHeight);

    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
});
```

???

- .updateProjectionMatrix () : undefined

Updates the camera projection matrix. Must be called after any change of parameters.

**Putting it all together: Higher order functions in three.js!**

This code uses an arrow function as a callback for the browser's 'resize' event.

**Breaking it down:**

1. `window.addEventListener('resize', ...)` - Listen for window resize events
2. `() => { ... }` - Arrow function callback (no parameters needed)
3. Inside the callback:
   - Update renderer size to match new window dimensions
   - Update camera aspect ratio (width/height)
   - Tell three.js to recalculate the camera's projection

**Why `updateProjectionMatrix()`?**
The camera internally stores calculations based on its aspect ratio. When you change the aspect ratio, you must tell three.js to recalculate, otherwise the image will be stretched/squished.

**This is a real-world example of:**

- Event listeners (higher order functions)
- Arrow function syntax
- Callbacks responding to async events (window resizing happens unpredictably)

---

template:inverse

Callback Functions ✓  
Higher Order Functions ✓  
Asynchronism ✓  
Homework ✓  
Gui Controls ✓

# Loading Models

???

Three.js lets you create many primitive geometries, but when it comes to more complex shapes, we better use a dedicated 3D software.

- OBJ
- FBX
- STL
- PLY
- COLLADA
- 3DS
- GLTF

Through times, many 3D model formats have been used. Each one responded to a problem, such as what data is embedded in the model, the weight, its compression, compatibility, copyrights, etc.

That is why, today, we have access to hundreds of model formats: https://en.wikipedia.org/wiki/List_of_file_formats#3D_graphics.

Some formats are dedicated to one software. Some are known to be very light but sometimes lack specific data. Some are known to have almost all data you could need in them but are heavy. Some formats are open source, some formats are not, some are binary, some are ASCII, and it goes on and on.

If you need precise data and can't find the adequate format supported by your software, you can even create your own quite easily.

We won't cover all of these formats. It would be boring, and we don't need to because one format is becoming a standard and should cover most of your needs.

---

.header[Loading Models]

## glTF

--

- Graphics Library Transmission Format

--

- Khronos Group (OpenGL, WebGL, Vulkan, etc.)

--

- Standard for real-time

--

- Supported by most environments
- Many exporters

--

- [glTF Sample Models](https://github.com/KhronosGroup/glTF-Sample-Assets)

???

GLTF stands for GL Transmission Format. It's made by the Khronos Group (the guys behind OpenGL, WebGL, Vulkan, Collada and with many members like AMD / ATI, Nvidia, Apple, id Software, Google, Nintendo, etc.)

GLTF has become very popular these past few years.

It supports very different sets of data. You can obviously have data like the geometries and the materials but you can also have data like cameras, lights, scene graph, animations, skeletons, morphing and even multiple scene.

It also supports various file formats like json, binary, embed textures.

- Blender by the Blender Foundation
- Substance Painter by Allegorithmic
- Modo by Foundry
- Toolbag by Marmoset
- Houdini by SideFX
- Cinema 4D by MAXON
- COLLADA2GLTF by the Khronos Group
- FBX2GLTF by Facebook
- OBJ2GLTF by Analytical Graphics Inc
- …and many more

GLTF has become the standard when it comes to real-time. And because it's becoming a standard, most 3D softwares, game engines, and libraries support it. That means that you can easily have a similar result in different environments.

That doesn't mean that you have to use GLTF in all cases. If you merely need a geometry, you better use another format like OBJ, FBX, STL, or PLY. You should test different formats on every project to see if you have all the data you need, if the file isn't too heavy, how long it takes to uncompress the information if it's compressed, etc.
Find a model

First, we need a model. As we said earlier, we will learn how to create our own model in a 3D software later, but for now, let's use a pre-made one.

The GLTF team also provides various models from a simple triangle to realistic models and things like animations, morphings, clearcoat materials, etc.

You can find them in this repository: https://github.com/KhronosGroup/glTF-Sample-Assets

If you want to test those models, you'll have to download or clone the whole repository and take the files you need. But we will start with a simple duck that you can already find in the /static/models/ folder in the starter.
GLTF formats

--

Documentation:

> Where possible, we recommend using glTF.

???

Where possible, we recommend using glTF (GL Transmission Format). Both .GLB and .GLTF versions of the format are well supported. Because glTF is focused on runtime asset delivery, it is compact to transmit and fast to load. Features include meshes, materials, textures, skins, skeletons, morph targets, animations, lights, and cameras.

Public-domain glTF files are available on sites like Sketchfab, or various tools include glTF export:

https://threejs.org/docs/index.html#manual/en/introduction/Loading-3D-models

---

.header[Loading Models]

## GLTF Formats

???
While GLTF is a format itself, it can have different file formats too. It's a little complex but for good reasons.

If you open the /static/models/Duck/ folder, you'll see 4 different folders. Each one contains the duck but in different GLTF formats:

--

- glTF
- glTF-Binary
- glTF-Draco
- glTF-Embedded

???

You can even find other formats, but those 4 are the most important and cover what we need to learn.

Be careful; your OS might hide the extension of some of these files. Refer to the file names from your code editor that should show the extension.

**glTF**

This format is kind of the default format. The Duck.gltf file is a JSON that you can open in your editor. It contains various information like cameras, lights, scenes, materials, objects transformations, but neither the geometries nor the textures. The Duck0.bin file is a binary that you can't read like this. It usually contains data like the geometries and all information associated with the vertices like UV coordinates, normals, vertex colors, etc. The DuckCM.png is simply the texture of the duck.

When we load this format, we only load the Duck.gltf that contains references to the other files that will then be loaded automatically.

**glTF-Binary**

This format is composed of only one file. It contains all the data we talked about in the glTF default format. That is a binary file, and you can't just open it in your code editor to see what's inside.

This format can be a little lighter and more comfortable to load because there is only one file, but you won't be able to easily alter its data. For example, if you want to resize or compress the textures, you just can't because it's inside that binary file, merge with the rest.

**glTF-Draco**

This format is like the glTF default format, but the buffer data (typically the geometry) is compressed using the Draco algorithm. If you compare the .bin file size, you'll see that it's much lighter.

While there is a separate folder for this format, you can apply the Draco compression to the other formats.

Let's put this one on the side, and we will talk more about it later.

**glTF-Embedded**

This format is like the glTF-Binary format because it's only one file, but this file is actually a JSON that you can open in your editor.

The only benefit of this format is to have only one easily editable file.

--

Beyond performance, choosing the right format is a matter of how you want to handle the assets.

--

- Make changes: glTF-default
- One file per model, no modifications: glTF-Binary

???

If you want to be able to alter the textures or the coordinates of the lights after exporting, you better go for the glTF-default. It also presents the advantage of loading the different files separately, resulting in a load speed improvement.

If you want only one file per model and don't care about modifying the assets, you better go for glTF-Binary.

In both cases, you must decide if you want to use the Draco compression or not, but we will cover this part later.
Setup

The starter is composed of one empty plane.

Because GLTF is a standard, it clearly supports lights. Usually, when you import a GLTF into your Three.js project, you'll end up with Meshes that have MeshStandardMaterial and, as you probably remember, if you don't have lights in your scene, you won't see much of those materials.

There is already an AmbientLight and a DirectionalLight in the starter.

Load the model in Three.js

---

.header[Loading Models]

## GLTF Loader

```js
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader.js";
```

???
To load GLTF files in Three.js, we must use the GLTFLoader. This class isn't available by default in the THREE variable. We need to import it from the examples/ folder located in the three dependency:

then we can instantiate it like we did for the TextureLoader:

**Connection to Higher Order Functions:**

This is where everything we learned comes together! The GLTFLoader uses:

- **Callbacks** (the function you pass to `.load()`)
- **Asynchronous execution** (loading files takes time, doesn't block)
- **Arrow functions** (commonly used for the callbacks)

Loading a 3D model is asynchronous - you can't know how long it will take. So you provide a callback that runs WHEN the model is ready.

--

```js
const gltfLoader = new GLTFLoader();
```

???

And if we need it, we can also use a LoadingManager as we did in the Textures lesson.

To load models, great news, it's almost as easy as loading a texture. We call the load(...) method and use the right parameters:

    The path to the file
    The success callback function
    The progress callback function
    The error callback function

gltfLoader.load(
'/models/Duck/glTF/Duck.gltf',
(gltf) =>
{
console.log('success')
console.log(gltf)
},
(progress) =>
{
console.log('progress')
console.log(progress)
},
(error) =>
{
console.log('error')
console.log(error)
}
)

You should see the progress and the success function being called. If the file couldn't be loaded, the error functions might be called. Check the path, and don't forget that we must not add the /static part.

Let's pretend we know what we are doing and remove the progress and error callback:

--

```js
gltfLoader.load("/models/Duck/glTF/Duck.gltf", (gltf) => {
  console.log(gltf);
});
```

???
If you look at the object logged in the console, you'll find a lot of elements. The most important part is the scene property because we have only one scene in the exported model.

This scene contains everything we need. But it also includes more. Always start by studying what is available in it and watch the scale property of the different Groups, Object3D, and Mesh.

We get something like this:

---

.header[Loading Models | GLTF]

## Adding The Model

```
THREE.Group: scene
└───Array: children
    └───THREE.Object3D
        └───Array: children
            ├───THREE.PerspectiveCamera
            └───THREE.Mesh
```

???

The Mesh should be our duck. We don't really care about the PerspectiveCamera. Both the camera and the duck seem to be in the first and only Object3D in the scene's children array. Even worst, that Object3D has a scale set to a minimal value.

As you can see, it's a little complex even to get our duck, and it's where most beginners get lost.

All we want is to get our duck in the scene. We have multiples ways of doing it:

- Add the whole scene in our scene. We can do that because even if its name is scene, it's in fact a Group.
- Add the children of the scene to our scene and ignore the unused PerspectiveCamera.
- Filter the children before adding to the scene to remove the unwanted objects like the PerspectiveCamera.
- Add only the Mesh but end up with a duck that could be wrongly scaled, positioned or rotated.
- Open the file in a 3D software and remove the PerspectiveCamera then export it again.

Because our model structure is simple, we will add the Object3D to our scene, and ignore the unused PerspectiveCamera inside. In future lessons, we will add the whole scene as one object:

--

```js
gltfLoader.load("/models/Duck/glTF/Duck.gltf", (gltf) => {
  scene.add(gltf.scene.children[0]);
});
```

???

You should see the duck.

You can try with other formats, but not the Draco that won't work yet:

gltfLoader.load(
'/models/Duck/glTF/Duck.gltf', // Default glTF

// Or
gltfLoader.load(
'/models/Duck/glTF-Binary/Duck.glb', // glTF-Binary

// Or
gltfLoader.load(
'/models/Duck/glTF-Embedded/Duck.gltf', // glTF-Embedded

Another model named FlightHelmet (also taken from the glTF model samples) is available in the /static/models/ folder. This model comes in only one format, which is the default glTF.

Try to load this model:

---

.header[Loading Models | GLTF | Adding The Model]

## Multiple Model Parts

--

We have to iterate over and add all parts:

--

```
while(gltf.scene.children.length) {

    scene.add(gltf.scene.children[0]);
}
```

???

Instead of a beautiful helmet, we only get a few parts.

The problem is that we added only the first child of the loaded scene to our scene.

There are multiple solutions to this problem. The first solution is to take the first children of the loaded scene and add it to our scene until there is none left:

We now get the whole helmet.

Another solution would be to duplicate the children array in order to have an unaltered independent array. To do that, we can use the spread operator ... and put the result in a brand new array []:

--

```
const children = [...gltf.scene.children]
for(const child of children) {
    scene.add(child);
}
```

???

The JavaScript spread operator (...) expands an iterable (like an array) into more elements.

This is a native JavaScript technique to duplicate an array without touching the original one.

Finally, one good and simple solution we mentioned earlier is to add the scene property:

--

```
scene.add(gltf.scene);
```

???
Our helmet is too small, and we could just increase the scale, but instead, we'll get back to our Duck and try the Draco compressed version.

---

.header[Loading Models | GLTF | Adding The Model]

## Multiple Model Parts

_How to adjust the scale?_

--

```js
gltf.scene.scale.set(3, 3, 3);
scene.add(gltf.scene);
```

---

.header[Loading Models | GLTF]

## Animation

glTF also supports animations!

--

```js
gltfLoader.load("/models/Fox/glTF/Fox.gltf", (gltf) => {
  gltf.scene.scale.set(3, 3, 3);
  scene.add(gltf.scene);
});
```

???

As we said earlier, glTF also supports animations. And Three.js can handle those animations.

**What gets embedded in a glTF file:**

- Geometry (the 3D shape)
- Materials (colors, textures, properties)
- Animations (keyframes, skeletal rigs)
- Scene hierarchy (how objects relate to each other)

This is why glTF is so powerful - it's not just a shape, it's a complete 3D scene!
Load an animated model

First, we need an animated model. We can use the fox located in /static/models/Fox/ folder (also taken from the glTF model samples).

Change the path to load that fox:

gltfLoader.load(
'/models/Fox/glTF/Fox.gltf',

We have a problem; the fox is way too big. If you can't see it, look above or zoom out.

Before handling the animation, let's fix the scale. If you look at the composition of the imported scene, the fox is composed of one Object3D, itself made of a Bone and a SkinnedMesh. We won't explain what those are, but the idea is that we shouldn't simply scale the Object3D. Even if it would work in this case, it would probably not work with more complex models.

What we can do here, is scale the loaded scene and add it directly to our scene:

gltfLoader.load(
'/models/Fox/glTF/Fox.gltf',
(gltf) =>
{
gltf.scene.scale.set(0.025, 0.025, 0.025)
scene.add(gltf.scene)
}
)

--

There is an `animations` property, containing multiple `AnimationClip` objects.

---

.header[Loading Models | GLTF | Animation]

## AnimationMixer

Create one `AnimationMixer` for each object that needs to be animated:

???

If you look at the loaded gltf object, you can see a property named animations containing multiple AnimationClip.

These AnimationClip cannot be used easily. We first need to create an AnimationMixer. An AnimationMixer is like a player associated with an object that can contain one or many AnimationClips. The idea is to create one for each object that needs to be animated.

Inside the success function, create a mixer and send the gltf.scene as parameter:

--

```js
gltfLoader.load("/models/Fox/glTF/Fox.gltf", (gltf) => {
  // console.log(gltf);
  gltf.scene.scale.set(0.025, 0.025, 0.025);
  scene.add(gltf.scene);

  const mixer = new THREE.AnimationMixer(gltf.scene);
  const action = mixer.clipAction(gltf.animations[0]);
  action.play();
});
```

???
const mixer = new THREE.AnimationMixer(gltf.scene)

We can now add the AnimationClips to the mixer with the clipAction(...) method. Let's start with the first animation:

const action = mixer.clipAction(gltf.animations[0])

This method returns a AnimationAction, and we can finally call the play() method on it:

action.play()

Regrettably, still no animation.

To play the animation, we must tell the mixer to update itself at each frame. The problem is that our mixer variable has been declared in the load callback function, and we don't have access to it in the tick function. To fix that, we can declare the mixer variable with a null value outside of the load callback function and update it when the model is loaded:

---

.header[Loading Models | GLTF | Animation]

## AnimationMixer

We must update the AnimationMixer object in our render loop and for that change its scope:

--

```js
let mixer = null;
gltfLoader.load("/models/Fox/glTF/Fox.gltf", (gltf) => {
  gltf.scene.scale.set(0.025, 0.025, 0.025);
  scene.add(gltf.scene);

  mixer = new THREE.AnimationMixer(gltf.scene);
  const action = mixer.clipAction(gltf.animations[0]);
  action.play();
});
```

???
And finally, we can update the mixer in the tick function with the already calculated deltaTime.

**Why `let mixer = null` outside the callback?**

This is a common pattern when working with async loading:

1. We need to use `mixer` in our render loop
2. But `mixer` is created inside the async callback
3. Variables created inside a callback aren't accessible outside

**The solution:**

- Declare `mixer` OUTSIDE the callback (in the outer scope)
- Set it to `null` initially (model not loaded yet)
- Assign the real mixer INSIDE the callback (when model loads)
- Check `if(mixer)` in render loop (only update if loaded)

**Analogy**: It's like reserving a parking spot (`let mixer = null`) before your friend arrives with their car. When they arrive (callback runs), they park in the reserved spot (`mixer = new AnimationMixer(...)`).

But before updating it, we must test if the mixer variable is different from null. This way, we update the mixer if the model is loaded, meaning that the animation is not ready:

---

.header[Loading Models | GLTF | Animation]

## AnimationMixer

```js
const renderLoop = () => {
  const elapsedTime = clock.getElapsedTime();
  const deltaTime = elapsedTime - previousTime;
  previousTime = elapsedTime;

  // AnimationMixer
  if (mixer) {
    mixer.update(deltaTime);
  }
};
```

???

The animation should be running. You can test the other animations by changing the value in the clipAction(...) method.

const action = mixer.clipAction(gltf.animations[2])

Three.js posses its own online editor. You can find it here: https://threejs.org/editor/

It's like a 3D software but online and with fewer features. You can create primitives, lights, materials, etc.

And because you can import models, it's a good way to test if your model is working fine. Though be careful; you can only test models composed of one file. You can try with the glTF-Binary or the glTF-Embedded duck.

Drag and drop the model into the editor.

You should see a black duck because there is no light. Add an AmbientLight and a DirectionalLight from the Add menu to see it more clearly.

Finally, you can export your scene in various formats that you can re-use in your code but we are getting out of the scope.

That's it for the moment but we're going to use loaded models multiple time in the following lessons.

https://github.com/mrdoob/three.js/blob/master/examples/webgl_lights_hemisphere.html

https://threejs.org/docs/index.html#manual/en/introduction/Animation-system

---

.header[Loading Models | GLTF]

## Draco Compression

???

Let's get back to our duck but this time, we are going to use the Draco version:

gltfLoader.load(
'/models/Duck/glTF-Draco/Duck.gltf',

Sadly, we don't get any duck. If you look at the logs, you should see a warning looking like this No DRACOLoader instance provided. We need to provide a DRACOLoader instance to our GLTFLoader so it can load compressed files.

As we saw when browsing the files, the Draco version can be much lighter than the default version. Compression is applied to the buffer data (typically the geometry). It doesn't matter if you are using the default glTF, the binary glTF or the embedded glTF.

It's not even exclusive to glTF, and you can use it with other formats. But both glTF and Draco got popular simultaneously, so the implementation went faster with glTF exporters.

Google develops the algorithm under the open-source Apache License:

    Website: https://google.github.io/draco/
    Git repository: https://github.com/google/draco

--

Add the DRACOLoader:

```
import { DRACOLoader } from 'three/examples/jsm/loaders/DRACOLoader.js';
```

???
Three.js already supports Draco. We must start by importing the DRACOLoader:

--

Instantiate the loader (before the gltfLoader) and set its path:

```
const dracoLoader = new DRACOLoader();
dracoLoader.setDecoderPath('/draco/');
```

???
The decoder is available in native JavaScript but also Web Assembly (wasm), and it can run in a worker (another thread as we saw at the end of the Physics lesson). Those two features significantly improve performances, but they imply having a wholly separated code.

Three.js already provided this seperated code. To find it, we must browse into the Three.js dependency and copy the Draco decoder folder into our /static/ folder.

This Draco folder is located in /node_modules/three/examples/jsm/libs/. Take the whole /draco/ folder and copy it into your /static/ folder. We can now provide the path to this folder to our dracoLoader:
dracoLoader.setDecoderPath('/draco/')

Finally, we can provide the DRACOLoader instance to the GLTFLoader instance with the setDRACOLoader(...) method:

--

- **Copy `/node_modules/three/examples/jsm/libs/draco/` to `/static/draco/`**

---

.header[Loading Models | GLTF]

## Draco Compression

Lastly, add the dracoLoader instance to the GLTF Loader:

```
gltfLoader.setDRACOLoader(dracoLoader);
```

???

- https://threejs.org/docs/index.html?q=loader#examples/en/loaders/DRACOLoader

Your duck should be back but this time it's a Draco compressed version.

You can still load not compressed glTF file with the GLTFLoader and the Draco decoder is only loaded when needed.
When to use the Draco compression

While you might think that the Draco compression is a win-win situation, it is not. Yes, the geometries are lighter, but first, you have to load the DRACOLoader class and the decoder. Secondly, it takes time and resources for your computer to decode a compressed file that can result in a short freeze at the start of the experience, even if we are using a worker and Web Assembly code.

You'll have to adapt and decide what the best solution is. If you only have one model with a 100kB geometry, you probably don't need Draco. But if you have many MB of models to load and don't care about some freezes at the start of the experience, you might need the Draco compression.
Animations

---

template: inverse

## The End

# 💪🏼 🗓 🔎

???

- Show tasks
