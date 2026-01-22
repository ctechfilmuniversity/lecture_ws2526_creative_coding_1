---
layout: default
title: Script 04 - Program Flow
parent: Scripts
nav_order: 4
---

# Creative Coding For Beginners
  
Prof. Dr. Lena Gieseke \| l.gieseke@filmuniversitaet.de  
  

# Script 04 - Program Flow and Interaction

* [Creative Coding For Beginners](#creative-coding-for-beginners)
* [Script 04 - Program Flow and Interaction](#script-04---program-flow-and-interaction)
    * [Topics](#topics)
    * [Learning Objectives](#learning-objectives)
    * [Program Flow](#program-flow)
        * [Curly Brackets `{}`](#curly-brackets-)
        * [Semicolons](#semicolons)
        * [Code Readability](#code-readability)
    * [Functions](#functions)
        * [Function Definition](#function-definition)
        * [Function Call](#function-call)
    * [System Loop](#system-loop)
    * [Interaction](#interaction)
        * [Mouse Interaction](#mouse-interaction)
            * [The `random` Function](#the-random-function)
            * [Careful](#careful)
            * [Mouse Position](#mouse-position)
        * [Keyboard Interaction](#keyboard-interaction)
    * [The Final Sketch](#the-final-sketch)
    * [Summary](#summary)

---

<!-- TODO: better image? -->

![ch02_01](img/04/ch02_01.png)


## Topics

* Flow of a program
    * Functions
    * User interaction
    * `if`-condition


## Learning Objectives

With this session you learn different ways to modify the execution flow of a program.  
Specifically you


* understand the basics of how code is structured and executed,
* understand what function definition and function call are,
* understand the difference between a function call and a code block,
* know the importance of code readability, and
* with that understand how you can control the flow of a program.


## Program Flow

You can understand the flow of a program as the order in which commands and function calls are executed. It is crucially important to understand early on that the order in which you write and organize the code in the code file has little to do with the order in which commands are actually executed. This order depends on constructs such as functions, if- and while-statements.

### Curly Brackets `{}`

The most important component for understanding program flow are `{}`. The brackets create one block of code. Code inside of the `{}` is executed line by line. 


`{}` are attached to different types of program flow entities, such as functions, conditionals and loops. These entities have a "title line" indicating, what is defined in the following code block, followed by the `{}` for the actual code.

```js
function draw(){ // "title line" + open bracket 

    // Code block 
    // Do something
}
```

Get in the habit of directly after writing the opening `{`, to also write the closing `}`. There is NEVER the case that you have only one of the brackets. They are BFFs and always, always appear together. Hence, write them together and then fill in the code inside of the brackets in the next step.

When trying to understand the flow of a program, look for the brackets first. They give you an understanding of the different code blocks.

### Semicolons

JavaScript is quite flexible about semicolons. It usually gives no errors when you misplace them. However, you should get in the habit of using them correctly, as it helps to visually structure the code. Also, other programming languages are very strict about the correct placement of semicolons and if you ever want to switch to a different language you should know how to place them.

There is NEVER a `;` directly after an opened parenthesis or bracket.  

`{;` -> DOES NOT EXIST EVER!

After `}` there is also no `;`. This is confusing, I know, because you are closing the code block. But also after code blocks, there are no `;`. 

You can remember it as 

* *Whenever you define a block of code with {} there is no following `;`* 
* *Whenever you call or execute something there is a following `;`*

We will get to know more cases where you need to use the `;`, e.g., when defining variables. 

Look at the following example and understand where there are semicolons and where not:

```js
function setup() {
    createCanvas(250, 250);
    background(255); //short-cut for white
}


function draw() {
    fill(0,0,255);
    stroke(255, 0, 0);
    strokeWeight(10);
    ellipse(125, 125, 100, 100);
}
```

The same example with in line comments as explanations:

```js

function setup() { // "title line" and open brackets, no semicolon

    createCanvas(250, 250);             //function call with semicolon
    background(255);                    //function call with semicolon
} //end of code block with a closing bracket, hence there is no semicolon


function draw() { // "title line" and open brackets, no semicolon
    fill(0,0,255);                  //function call with semicolon
    stroke(255, 0, 0);              //function call with semicolon
    strokeWeight(10);               //function call with semicolon
    ellipse(125, 125, 100, 100);    //function call with semicolon
} //end of code block with a closing bracket, hence there is no semicolon
```

### Code Readability

You should have gotten an idea now that the structure of code is crucial. To better understand what is going on, the visible structure of code must always represent its functional structure. 

Hence, there are many rules on how to layout your code. The most basic ones are:

* One line per function call.
* Opening curly brackets come after the title line.
* Closing curly brackets get their own line.
* Indent the content between two brackets.


```js
// codeReadability

// Not acceptable,
//...but the code still works:
function setup()
{
createCanvas(400, 400); background(255); } //short-cut for white

function 

draw(){fill(0,                   0,255);
  stroke(255,0,0);strokeWeight(10);
                 ellipse(125, 125, 100, 100);
}

// Also not acceptable,
//...but the code still works:
function setup() {createCanvas(400, 400); background(255); }function draw() {fill(0,0,255);stroke(255, 0 , 0);strokeWeight(10);ellipse(125, 125, 100, 100);}
```

*On a Side Note:* In the p5 editor, `Edit -> Tidy Code` will auto-indent the code, meaning, structure the code properly for you.

## Functions

So far, we have used many different function calls for drawing.

This is the call to the function `line`:

```js
line(10, 10, 50, 50);
```

This means we are calling the function `line`, to be executed, which is the task of drawing a line from the point 10, 10 to the point 50, 50.

But where is it defined how the line is actually drawn, meaning the coloring of the pixels?

Well somewhere inside the p5 library. `line()` is a pre-defined function, which we don't have to make from scratch but that we can simply use. Similar to if we were baking a pizza and we are using a can of pre-made tomato sauce. `line` is the tomate sauce. We can just use it and do not need to worry about how it is defined.

But somewhere [inside the p5 library](https://github.com/processing/p5.js/blob/main/src/core/shape/2d_primitives.js) there must be defined what should actually happen if the function `line()` is called. This is called a function definition.


### Function Definition

To define a function you need the keyword `function` followed by a `functionname` (given or of your choice), followed by `()`, followed by `{...}`. What a function does is enclosed in the curly brackets.

```js
function functionname(){

    // Code that is executed when we call the function
}
```

Functions define functionality blocks with fixed responsibilities or tasks.  

Working with functions consists of two parts: the definition of that function and calling that function to execute it.

With our current knowledge we could define a `line()` function as follow:

```js
// functionDefinition

function theBestLineEverDrawn(x1, y1, x2, y2) {
    beginShape();
    vertex(x1, y1);
    vertex(x2, y2);
    endShape();
}
```

Later on, we will frequently write functions from scratch. Don't worry about writing you own functions for now. Here we are talking about it in order to understand the flow of a program.

### Function Call

To execute what is inside of a function, you have to call it. You call a function with its `functionname`, followed by `()`, optional arguments inside of those parenthese, followed by a `;` as last element. We know this already.


```js
// functionDefinition

function theBestLineEverDrawn(x1, y1, x2, y2) {
    beginShape();
    vertex(x1, y1);
    vertex(x2, y2);
    endShape();
}

…

theBestLineEverDrawn(10, 10, 20, 20); // Calling the function somewhere in the code
```


## System Loop

The code we have learned to use as base structure is actually two function definitions, namely the definition of the function `setup()` and of the function `draw()`:


```javascript
function setup() {

    ...

}

function draw() {

    ...
}
```

By filling these functions with code, we are defining what happens when the commands are called, hence, we define their **functionality**.

But when are we actually calling these commands? Well, in this specific case p5 takes care of calling these commands for us. 



## Interaction

```js
// colorCircle - Step 1

function setup() {
    createCanvas(250, 250);
    background (255);
    fill(255, 0, 0);
    noStroke();
}

function draw() {
    ellipse(125, 125, 100, 100);
}
```

As the `draw()` function is continuously called, we can make changes to it over time.

Such changes could be based on **user interaction**


### Mouse Interaction

p5 gives a function definition, with which we can defined what should happen if the mouse is pressed:

```js
function mousePressed() {

    // Define what should happen
}
```

p5 calls this function for us whenever the mouse is pressed. This is the same principle as when p5 calls the function `setup()` for us when the program is started.

Now we want to do the following:

*If the mouse was pressed, change the color of the circle*

```js
// colorCircle - Step 2

function setup() {
    createCanvas(250, 250);
    background (255);
    fill(255, 0, 0);
    noStroke();
}

function draw() {
    ellipse(125, 125, 100, 100);
}

// Called if the mouse was pressed
function mousePressed() {

    // Set the fill color to
    // randomly chosen values
    fill(random(255), random(255), random(255));
}
```


#### The `random` Function

The random function generates a random number 😁.

```js
random(-50, 50);
```

When we call this function, it *returns* a value, the random number. Yes, functions can return data. We will come back to this. 

```js
fill(random(255), random(255), random(255));
```

Above, we are directly piping the return value of the random function as argument into the `fill(r, g, b)` function call. Functions can be nested. As of now, this should remain an exception for us!

Back to the functionality of `random()`:

* The function is given to us by p5, hence it is defined somewhere in the p5 library.
* Each time the `random()` function is called, it returns an unexpected value within the specified range.
    * `random(-5, 5)` returns values between -5 and 5 (starting at zero, and up to, but not including, 5)
* If only one argument is passed to the function, it will return a float between zero and the value of argument 
    * `random(5)` returns values between 0 and 5 (starting at zero, and up to, but not including, 5)

* https://p5js.org/reference/#/p5/random


#### Careful

*Why does the following not work?*

```js
// colorCircleProblem

function setup() {
    createCanvas(250, 250);
    background (255);
}

function draw() {
    fill(255, 0, 0);
    noStroke();
    ellipse(125, 125, 100, 100);
}

// Called if the mouse was pressed
function mousePressed() {

    // Set the fill color to
    // randomly chosen values
    fill(random(255), random(255), random(255));
}
```


#### Mouse Position

We can also use the current mouse position as input. This is not done with a function but with two values, so called **variables** provided by p5. This specific type of variable is called *system variable*. System variable are the variables that are given from the system in contrast to the variables that you are going to define yourself. We will come back to this.

```js
mouseX
mouseY
```

We still need to learn all about variables. This is not the time. For now you can just remember that "inside" of `mouseX` we can access the current mouse position in x at all times, and in `mouseY` the current mouse position in y.


```js
// colorCircleMove
// (the rest of the code remains the same)

function draw() {
    ellipse(mouseX, mouseY, 50, 50);
}
```

### Keyboard Interaction

Similar to the mouse pressed function, we can define what should happen if a key is pressed:

```js
function keyPressed() {

    ...
}
```

Again, p5 calls this function for us whenever a key is pressed.


```js
// Color Circle Key Input
// (the rest of the code remains the same)

function keyPressed() {

    background (255);
}
```

## The Final Sketch

With all of the above, we have now in total:


```js
function setup() {
  createCanvas(250, 250);
  background(255);
  noStroke();
  
  // The circle is in the beginning white
  // (this is also the default and we
  // don't really need this line)
  fill(255);
}

function draw() {
  ellipse(mouseX, mouseY, 100, 100);
}

// Called if the mouse was pressed
function mousePressed() {

  // Set the fill color to
  // randomly chosen values
  fill(random(255), random(255), random(255));
}

// Called when any key is pressed
function keyPressed() {

  // Fill the background with white
  background(255);
}
```

## Summary

* `{}` define blocks of code.
    * There is no `;` after such a code block.
* Functions 
    * Are defined with within `{}`
    * Need to be called in order for the code to execute.
    * Function calls are followed by a `;`
* A proper layout of the code is important.
    * How the code looks like should represents its functionality.
* We can structure the program flow with user input
    * `mousePressed()`
    * `mouseX`, `mouseY`
    * `keyPressed()`
    * `key`


Use the [reference](https://p5js.org/reference/) 🚒


---

The End  
  
⛵️  🎢  🎡 
