---
layout: default
title: Script 11 - Functions
parent: Scripts
nav_order: 11
---


# Script 11 - Functions

* [Script 11 - Functions](#script-11---functions)
    * [Learning Objectives](#learning-objectives)
    * [Functions](#functions)
        * [Parameters](#parameters)
        * [Return values](#return-values)
        * [Why Should We Care?](#why-should-we-care)
    * [Summary](#summary)

---


## Learning Objectives

With this script you

* understand how to structure your code more wisely, and
* know how to define your own functions.


## Functions

So far most of our code was written directly inside of `setup()` and `draw()`. But as our code will get more and more complex, we need to think about how to structure it more wisely. One important step to do so is to write our own functions to encapsulate complicated logics into single function calls.

In [session 2](https://ctechfilmuniversity.github.io/lecture_creative_coding_for_beginners/scripts/ccfb_summerschool21_04_flow_script.html#functions) you already learnt the basics of functions:

To define a function you need the keyword function followed by a `functionname` (given or of your choice), followed by `()`, followed by `{...}`. What a function does is enclosed in the curly brackets.

```
function functionname() {
    // Code that is executed when we call the function
}
```

After we defined it we can then call the function:

```
function draw() {
  functionname();
}
```

Note that what you learnt about [variable scopes](https://ctechfilmuniversity.github.io/lecture_creative_coding_for_beginners/scripts/ccfb_summerschool21_05_variables_script.html#variable-scope) also applies to functions: you can only call them at places where they are accessible from.


### Parameters

In all our examples we were calling functions which are defined inside the p5 library like this:

```
line(10, 10, 50, 50);
```

```
// Somewhere inside of the p5 library
// is the function definition 

function line(x1, y1, x2, y2) {
    beginShape();
    vertex(x1, y1);
    vertex(x2, y2);
    endShape();
}
```

And exactly like that we can also define our own functions with our input parameters:

```
function functionname(parameter1, parameter2, parameter3) {
  // Code that is executed when we call the function
}
```

When we call this function we then hand in the values or variables we want to use as `parameter1`, `parameter2` and `parameter3` as the arguments.

```
function draw() {
  let someValue = 1.5;
  functionname(100, 'whatever', someValue);
}
```

### Return values

Now we learnt how to pass values into functions. But what if we want the function to give a value back to us? Next to tasks such as "draw something" there can be tasks that result in a value with which we want to continue to work with.

The random command for example works like this:

```javascript
let value = random(10, 100); // returns a value between 10 and 100
```

To write our own functions with return values we use the keyword `return` at the end of the function definition and the value behind it will be returned when we call it:

```
function calculateSquare(x) {
  return x * x;
}

function draw() {
  let result = calculateSquare(4); // returns 16
  print(result); // prints '16' to the console
}
```

### Why Should We Care?

Why should we define our own functions instead of just writing everything into setup() and draw()? It makes our code **modular** and **reusable**. 

For example, look at the following code. Imagine you would want to repeat the flower multiple times in different locations. You could simply copy the code or try do put it into a loop.

```js
function setup() {
	createCanvas(300, 300);
	background(0, 200, 0);
	noStroke();
}

function draw() {

	let flowerX = 150;
	let flowerY = 150;
	let petalSize = 100;
	let petalDistance = petalSize / 2;

	fill(200, 0, 100);

	// upper-left petal
	circle(flowerX - petalDistance, flowerY - petalDistance, petalSize);

	// upper-right petal
	circle(flowerX + petalDistance, flowerY - petalDistance, petalSize);

	// lower-left petal
	circle(flowerX - petalDistance, flowerY + petalDistance, petalSize);

	// lower-right petal
	circle(flowerX + petalDistance, flowerY + petalDistance, petalSize);

	// center petal
	fill(255, 255, 0);
	circle(flowerX, flowerY, petalSize);
}
```

Or, for creating multiple flowers, you could define a custom function for drawing one flower:


```js
function setup() {
	createCanvas(300, 300);
	background(0, 200, 0);
	noStroke();
}

function draw() {
  drawFlower(80, 90, 75);
  drawFlower(225, 80, 45);
  drawFlower(75, 225, 55);
  drawFlower(220, 220, 65);
}

function drawFlower(flowerX, flowerY, petalSize) {
	let petalDistance = petalSize / 2;

	fill(200, 0, 100);

	// upper-left petal
	circle(flowerX - petalDistance, flowerY - petalDistance, petalSize);

	// upper-right petal
	circle(flowerX + petalDistance, flowerY - petalDistance, petalSize);

	// lower-left petal
	circle(flowerX - petalDistance, flowerY + petalDistance, petalSize);

	// lower-right petal
	circle(flowerX + petalDistance, flowerY + petalDistance, petalSize);

	// center petal
	fill(255, 255, 0);
	circle(flowerX, flowerY, petalSize);
}

```
Now that you have a drawFlower function, you can call it as many times as you want, with whatever parameters you want!

The payoff here is that you can treat the drawFlower function as a single step, even though it’s really doing a bunch of stuff when you call it. You don’t have to worry about how the flower is drawn, exactly like you didn’t have to worry about how the circle function works behind the scenes.

Source: https://happycoding.io/tutorials/p5js/creating-functions

A reasonable use of functions, keeping `setup()` and `draw()` as tidy as possible, is considered good and robust code.

![wtfm](img/functions/wtfm.jpg)





## Summary

- Functions have a name, optional parameters and an optional return value.

```
function addTen(float parameter1) 
{
	return (parameter1 + 10);
}
```

- Functions are called like all the commands we already know

```
let newValue = addTen(21);  //newValue is now 31
```

- Use them to encapsulate parts of your code, making it **modular** and **reusable**
- Use files/tabs to structure your code


Use the [reference](https://p5js.org/reference/) 🚒

---

The End

🌼 🌺 🌸