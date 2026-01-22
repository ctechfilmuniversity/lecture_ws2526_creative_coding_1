---
layout: default
title: Script 07 - Variables
parent: Scripts
nav_order: 7
---

# Script 07 - Variables

* [Script 07 - Variables](#script-07---variables)
    * [Topics](#topics)
    * [Learning Objectives](#learning-objectives)
    * [Re-Using Values](#re-using-values)
    * [Variables](#variables)
        * [Initalization](#initalization)
        * [Variable Errors](#variable-errors)
        * [Naming Conventions](#naming-conventions)
        * [Data Types](#data-types)
        * [Data Types List](#data-types-list)
            * [String](#string)
            * [Number](#number)
            * [Boolean](#boolean)
            * [undefined](#undefined)
            * [print()](#print)
            * [Summary Data Types](#summary-data-types)
        * [Variable Scope](#variable-scope)
        * [Nesting Scopes](#nesting-scopes)
        * [Global Scope](#global-scope)
        * [Summary](#summary)
    * [Application Example Animation](#application-example-animation)
        * [Change the Color of the Circle Automatically](#change-the-color-of-the-circle-automatically)
            * [Why Does the Color Stop Changing?](#why-does-the-color-stop-changing)
        * [Change the Position of the Circle Automatically](#change-the-position-of-the-circle-automatically)
    * [Arithmetic Operators](#arithmetic-operators)
    * [Summary](#summary-1)
    * [References](#references)

---

For this topic, we are working with [cats in boxes](https://www.youtube.com/watch?v=TbiedguhyvM):

![ch03_01](img/05/ch03_01.jpg)  
[[pinimg]](https://i.pinimg.com/originals/29/e5/e8/29e5e884709323402933b3e3b73dbbb8.jpg)


## Topics

* Variables
    * Data Types
    * Scope
* Animation


## Learning Objectives


With this session you 

* understand how to work with data, and
* understand what the scope of a variable is, and
* how to animate certain properties, such as color and position.

## Re-Using Values

When [drawing colorful lines](https://editor.p5js.org/legie/sketches/vcKXqzsgQ), we decided to use the width of our window as size for the value range for our color spectrum and so we had to paste the same value multiple times at different locations:

![colorlines_next_01](img/07_variables/colorlines_next_01.png)  

This is tedious. If we want to test out different values for the window size we have to copy and paste the new value to all these places. Most likely we will forget one of the spots and create non-consistent behavior.

*How can we make this better?*

It would be great if we could define the value only once and then re-use or reference that value in the different places.

Well, variables enable us to do exactly that! Here a [quick preview](https://editor.p5js.org/legie/sketches/vcKXqzsgQ) before we get into the details about variables:

![colorlines_next_02](img/07_variables/colorlines_next_02.png)  

As you can see above, we are only defining a value for `myWidth` once (line 2) and the re-use `myWidth` multiple times. If we would want to change the value, we would only need to set in line 2 and do not need to worry about of the other locations.

## Variables

Think back to the idea of understanding coding like creating a cooking recipe. In practice, a recipe only makes sense with the actual *ingredients* to cook with. Similarly, programming really only enfolds its full potential when working with data. You can think of the various forms of data such as a mouse click, text or numbers, as being the ingredients for programming.

Data can come in various forms, such as

* Inputs such as images, video, sound files or streams
* Inputs from user interaction, ranging from a key pressed to spoken words or hand gestures
* Data defined in the program such as constant values or a data table
* Data generated during the program such as formula computations

In programming, data is saved in *variables*. 

Imagine variables as boxes in which you can put stuff and that

* boxes can be moved around,
* boxes can be empty, and
* what is inside a box can be changed.

![ch03_04](img/05/ch03_18.png)  


### Initalization

Variables must be specifically created with the `let` keyword and any name of your choosing. You use `let` exactly **once** for each variable. `let` means something like *"create this variable"*:

```js
let myWidth;
```

`myWidth` is not the best name. Usually you want to be as concise as possible with your variable names. However, here the name helps us to understand that this is a self-made name. We could have also used `hasi` (let's not do that thought...ever!) or almost anything really.

Usually you give the variable an initial value directly when creating the variable:

```js
let myWidth = 300;
```

```js
//Pseudo code

let variablename = value;
```

With the single `=` you assign a value to a variable. Do not confuse this with the comparison operator `==`; in programming `=` (value assignment) and `==` (is equal test) are completely different things!

If you do not initialize the variable when you create it, its value is *undefined* until you assign a value to it. Using a variable with a undefined value can lead to unexpected behavior and errors. Hence, get in the habit to always assign a value to a variable, when creating it.

After you created a variable and give it a value, you can work with the variable:

```js
let myDiameter = 10;

circle(50, 50, myDiameter);
print(myDiameter);
```

At all times you can change the value of a variable:

```js
myDiameter = myDiameter + 10;
```

As an [example](https://editor.p5js.org/legie/sketches/KR1qoukBx), we could increase the diameter with each mouse-click:

```js
let myDiameter = 10;

function setup() {
    createCanvas(400, 400);


    fill(0,0,255);
    noStroke();
}

function draw() {
  
    background(255);
    circle(mouseX, mouseY, myDiameter);

    print(myDiameter);
}


function mousePressed(){
  
    myDiameter = myDiameter + 1;
}
```

Notice how we are using `print` to keep track of the variable value - just for our information.

### Variable Errors

If you are trying to work with a variable that does not exists, p5 will throw an error:

```js
// Variable Error

    ...
    circle(mouseX, mouseY, myDiamete);
```

Error:

> ReferenceError: myDiamete is not defined.  
> 🌸 p5.js says: "myDiamete" is not defined in the current scope....


### Naming Conventions

Again, for programming, upper and lower case spelling matters!

```js
thisName != thisname
```

You must not use

* Umlaute, ß, or accents,
* names the p5 syntax is using, such as `let`, `function`,
* spaces and hyphen, or
* start with a number.

You should

* start with a small letter, and
* separate different words with camel case.

```js
thisNameIsAwesome
```

**Use sensible names!**

### Data Types

The computer keeps track of the *type of data* that is inside of the box. For different data types, memory is allocated differently (you don't need to worry about memory allocation though).

So, be aware that data has a *type*. E.g., the type of `myDiameter` variable in the the above example is a *number*. The value you give a variable defines the type.

JavaScript is a loosely typed programming language. That means it is loose about data types 😊. That means that you can assign and re-assign values of all types to the same variable:

```js
let myVariable = 42;        // a number
myVariable     = 'hello';   // a string
myVariable     = true;      // a boolean
```

Just keep in the back of your head that this behavior makes JavaScript quite special. In most other programming language a variable can only accept values of the same type. In other programming languages the above example will create an error, saying that you can't assign 'hello' to a variable that was previously defined to store numbers.


![ch03_06](img/05/ch03_06.png)

### Data Types List

There are in total nine data types. We only care about `String` (textual data), `Number` (well... numbers 🙃), `Boolean` (true or false). and `undefined` (no value assigned).

For somewhat advanced knowledge, which you can also ignore, here all data types:

| Data Type   | Description                                        | Example                          |
|-------------|----------------------------------------------------|----------------------------------|
| `String`    | represents textual data                            | `'hello'`, `"hello world!"` etc. |
| `Number`    | an integer or a floating-point number              | `3`, `3.234`, `3e-2` etc.        |
| `BigInt`    | an integer with arbitrary precision                | `900719925124740999n`, `1n` etc. |
| `Boolean`   | Any of two values: true or false                   | `true` and `false`               |
| `undefined` | a data type whose variable is not initialized      | `let a;`                         |
| `null`      | special keyword denoting a null value              | `let a = null;`                  |
| `Symbol`    | data type whose instances are unique and immutable | `let value = Symbol('hello');`   |
| `Object`    | key-value pairs of collection of data              | `let student = { };`             |

All data types except Object are called *primitive data types*, whereas Object is non-primitive. The non-primitive type Object can store collections of data, whereas primitive data type can only store a single data entity.

Good news, again, the only data types we care about are `String`, `Number`, `Boolean` and `undefined`.

[[3]](https://www.programiz.com/javascript/data-types)

#### String 

`String` is used to store text. In JavaScript, strings are surrounded by quotes:

* Single quotes: 'Hello'
* Double quotes: "Hello"
* (Backticks: `Hello`)

For example,

```js
//strings example
let firstName = 'Mickey';
let lastName = "Mouse";
let fullName = firstname + " " + lastname;
```

Single quotes and double quotes are practically the same and you can use either of them.

<!-- Backticks are generally used when you need to include variables or expressions into a string. This is done by wrapping variables or expressions with ${variable or expression} as shown above. -->

[[3]](https://www.programiz.com/javascript/data-types)

#### Number

`Number` represents whole numbers (called integer) and decimal numbers (called float). For example,

```js
let number1 = 3;
let number2 = 3.433;
```

[[3]](https://www.programiz.com/javascript/data-types)


#### Boolean

This data type represents a logical entity. `Boolean` represents one of two values: `true` or `false.` It is easier to think of it as a yes/no switch. For example,

```js
let classIsOngoing = true;
let nightTime = false;
```

[[3]](https://www.programiz.com/javascript/data-types)

#### undefined

The `undefined` data type represents that a value is not assigned. If a variable is declared but the value is not assigned, then the value of that variable will be undefined. For example,

```js
let name;
print(name); // returns undefined
```

*On a side note:* If you explicitly want a variable with no value, it is recommended to use `null` to assign 'unknown' or 'empty'.


[[3]](https://www.programiz.com/javascript/data-types)


#### print()

When working with a variable it is common practice while developing a program to print the value of a variable to know what is going on:

```js
let counter = 0;

// do stuff with counter

print(counter);
```


#### Summary Data Types

You can also check for the current type of a variable with the `typeof` command. It returns the type of that variable as a string.

```js
// Data Types


let wholeNumber = 10;
let floatingPointNumber = 10.25;
let truthValue = false;
let word = "Hello World";
let noValue;

print(typeof(wholeNumber));
print(typeof(floatingPointNumber));
print(typeof(truthValue));
print(typeof(word));
```


### Variable Scope

🚨 Attention: the following section is very important to understand... 🚨
  
🤓 ...but also a bit tricky!! 🤓 

Variables have a *scope*. Scope refers to the area in the code where you can access the variable, meaning *where it exists* (or sometimes I also call scope also *visibility*, in the sense of *where is the variable visible?*)

The scope of a variable is defined by where we create it (meaning where we used `let`) and our already best friends, the curly brackets:

```js
{
    // Variable only exists inside the brackets
    let myDiameter = 10;
}
```

**Variables only exist within the scope (meaning within the code block, defined by `{}`) that we created the variable in!**

Here it does not matter to what kind of code construct the curly brackets belong to. For all curly brackets scope applies in the same way.

```js
function setup() {

    // SCOPE 1
}

function draw() {

    // SCOPE 2
}
```

```js
if (name == 'ernie') {

    // SCOPE 1
} 
else {

    // SCOPE 2
}
```

What will happen in the following [example](https://editor.p5js.org/legie/sketches/yG1r_Epfe)?

```js
// Variable Scope


function setup() {

    noLoop();

    // VARIABLE CREATION
    let myVariable = 10;

    print('1. print: ' + myVariable); 

}

function draw() {

    // myVariable is out of scope here, 
    // meaning we can not access it
    print('2. print: ' + myVariable); 
}
```

### Nesting Scopes

Scopes can be nested and variables are visible from the [inside of the nested brackets](https://editor.p5js.org/legie/sketches/BGp6te8CY):

```js


function setup() {
    noLoop();
}

function draw() {

    // SCOPE 1
    let variableLevel1 = 1;

    if (variableLevel1 == 1) {
        // SCOPE 2

        // SCOPE 2 is nested in SCOPE 1
        // and we can access SCOPE 1's variables here:
        print(variableLevel1); // No error
    }
}
```

![ch03_16](img/05/ch03_16.png)

Why does [the following](https://editor.p5js.org/legie/sketches/wRFErPBr5) throw an error?

```js

function setup() {
    noLoop();
}

function draw() {

    //SCOPE 1
    let variableLevel1 = 1;

    if (variableLevel1 == 1) {
        // SCOPE 2

        // SCOPE 2 is nested in SCOPE 1
        // and can access SCOPE 1's variables
        print('1. print: ' + variableLevel1);

        let variableLevel2 = 2;
    }


    // We are back in SCOPE 1
    // variableLevel2 is out of scope here, 
    // meaning we can not access it
    print('2. print: ' + variableLevel2); 
}
```

### Global Scope

There is a **global scope**. For this imagine one pair of `{}` around everything by default.

![ch03_17](img/05/ch03_17.png)


```js

//SCOPE 0 - this variable visible everywhere!
let variableLevel0 = 1;

function setup() {
    noLoop();
}

function draw() {
    // SCOPE 1

    print('1. print: ' + variableLevel0);

    if (variableLevel0 == 1) {
        // SCOPE 2
        print('2. print: ' + variableLevel0)
    }

    print('3. print: ' + variableLevel0);
}
```

Global scope comes with many problems, e.g., it is difficult to keep track where the variable is changed in the code. 

**However, for beginners it is perfectly fine to use global variables.**

In the upcoming weeks, we will most likely very often use variables that we define before any other code. Those variable we can use anywhere in the code and we do not need to worry about their scope, as they are in global scope.

We used global scope already in our very first example:

```js
let myDiameter = 10; //variable is visible everywhere

function setup() {
    createCanvas(400, 400);


    fill(0,0,255);
    noStroke();
}

function draw() {
  
    background(255);
    circle(mouseX, mouseY, myDiameter);

    print(myDiameter);
}


function mousePressed(){
  
    myDiameter = myDiameter + 1;
}
```

### Summary

* You have to define a variable with `let` and a name of your choice.
* You should initialize a variable with a value, assigning a value with `=`.
* **Variables only exists inside of the `{}`, where they were created.**
* **If your variable behaves strangely, check its scope!**

![ch03_02](img/05/ch03_02.png)


## Application Example Animation

### Change the Color of the Circle Automatically

Idea: in each frame (meaning every time draw is called) count up a variable and use that variable for the hue channel. Hence, the color should change smoothly by increasing its value one by one.

```js
// https://editor.p5js.org/legie/sketches/uaRTbFi0H
// Animating the Color of the Circle


// Creation and initialization
// of a new variable
let hue = 0;

function setup() {
    createCanvas(250, 250); 

    colorMode(HSB);
    background(100);
    fill(hue, 100, 100);
    noStroke();
}

function draw() {

    // Using the colorRed variable
    // as value for the red channel
    fill(hue, 100, 100);
    ellipse(mouseX, mouseY, 20, 20);

    // Increasing the value
    // in each draw() call
    hue = hue + 1;
    // print(hue);
}
```


... but wait. Why does the color stop changing after a while?


#### Why Does the Color Stop Changing?

We continuously increase the value for the `hue` variable and at some point its value is above 360 (the default value range for the H channel). Hence, every value above 360 will just interpreted as 360 by p5. So when, e.g. `hue` is 500, the color looks like 360.

In order to change this "overflow", we need to check for the possible value range of a color and make sure that hue only gets values 0..360.

```js
// https://editor.p5js.org/legie/sketches/Amb0jZJIN
// Animating the Color of the Circle 

let hue = 0;

function setup() {
    createCanvas(250, 250); 

    colorMode(HSB);
    background(100);
    fill(hue, 100, 100);
    noStroke();
}

function draw() {

    // Using the colorRed variable
    // as value for the red channel
    fill(hue, 100, 100);
    ellipse(mouseX, mouseY, 20, 20);

    // Increasing the value
    // in each draw() call
    hue = hue + 1;
   //print(hue);
  
      // We check whether the value of
    // hue becomes larger than 360,
    // and if so we reset it back to zero.
    if(hue > 360){
        hue = 0;
    }
}
```

Similarly, we could animate the position of the circle.

### Change the Position of the Circle Automatically

Let's create two new variables for the position of the circle and one for its speed and use those variables for, well the position of the circle. In the same manner that we increase the hue variable, we can increase the position variable by speed:

```js
// https://editor.p5js.org/legie/sketches/OljoriSe7

let hue = 0;
let positionX = 0;
let positionY = 0;
let speed = 2;

function setup() {
    createCanvas(250, 250); 

    colorMode(HSB);
    background(100);
    fill(hue, 100, 100);
    noStroke();
}

function draw() {

    // Using the colorRed variable
    // as value for the red channel
    fill(hue, 100, 100);
    ellipse(positionX, positionY, 20, 20);

    // Increasing the position values
    positionX = positionX + speed;
    positionY = positionY + speed;

    // Increasing the value
    // in each draw() call
    hue = hue + 1; 
    // We check whether the value of
    // hue becomes larger than 360,
    // and if so we reset it back to zero.
    if(hue > 360){
        hue = 0;
    }
}
```

In the same way that the hue value becomes larger than 360, the position variable become to large for the canvas and the circle runs out of the canvas. 

We can fix this by testing for the canvas size. For making that easier, let's use the system variable `windowWidth` and `windowHeight` the set the canvas size (otherwise I recommend to also create your own variables for the windows sizes).

Also, we are going to use the `or` operator with `|`, which connects two conditions. This means that only one of the two conditions (condition 1 is `positionX > windowWidth` and condition 2 is `positionX < 0`) needs to be true for the whole statement `condition 1 or condition 2` to be true.


```js
// https://editor.p5js.org/legie/sketches/Rri_V0jph

let hue = 0;
let positionX = 0;
let positionY = 0;
let speed = 2;

function setup() {
    createCanvas(windowWidth, windowHeight); 

    colorMode(HSB);
    background(100);
    fill(hue, 100, 100);
    noStroke();
}

function draw() {

    // Using the colorRed variable
    // as value for the red channel
    fill(hue, 100, 100);
    ellipse(positionX, positionY, 20, 20);
    
    // POSITION
    // Increasing the position values
    positionX = positionX + speed;
    positionY = positionY + speed;
  
    // If the x position runs out of the canvas, 
    // reset the position to 0
    if(positionX < 0 | positionX > windowWidth) {
        positionX = 0;
    }
    
    // If the y position runs out of the canvas, 
    // reset the position to 0
    if(positionY < 0 | positionY > windowHeight) {
        positionY = 0;
    }
  
    // HUE
    // Increasing the value
    // in each draw() call
    hue = hue + 1; 
    // We check whether the value of
    // hue becomes larger than 360,
    // and if so we reset it back to zero.
    if(hue > 360){
        hue = 0;
    }
}
```

In the above example, we reset the position to 0, creating a jump of the circle to the other side of the canvas again. How could we create the effect that the circle bounces of the sides of the canvas?

A solution could be to change the direction of the movement, when we hit the border of the canvas. We can change the direction by not adding `speed` to `positionX` and `positionY` but subtracting it!

So, first, when we start the program, we want that a postion is **increased** by speed (`positionX = positionX + speed;`) until it hits `windowWidth`. Then, we want to "switch direction" and **decrease** the `positionX` value (`positionX = positionX - 1;`) until it reached zero. Once it reached zero, we want to switch direction again and count up again, and so on and so on.

For that we can re-utilize our `speed` variable, also giving it a sign, meaning making it negativ, when we want to subtract values. However, we want to be able to control positionX and positionY independently, hence we also split speed int `speedX` and `speedY`.


```js
// https://editor.p5js.org/legie/sketches/D1R-Owv47

let hue = 0;
let positionX = 0;
let positionY = 0;
let speedX = 5;
let speedY = 5;

function setup() {
    createCanvas(windowWidth, windowHeight); 

    colorMode(HSB);
    background(100);
    fill(hue, 100, 100);
    noStroke();
}

function draw() {

    // Using the colorRed variable
    // as value for the red channel
    fill(hue, 100, 100);
    ellipse(positionX, positionY, 20, 20);
    
    // POSITION
    // Increasing the position values
    positionX = positionX + speedX;
    positionY = positionY + speedY;
  
    // If the x position runs out of the canvas, 
    // reset the position to 0
    if(positionX < 0 | positionX > windowWidth) {
        speedX = speedX * -1;
    }
    
    // If the y position runs out of the canvas, 
    // reset the position to 0
    if(positionY < 0 | positionY > windowHeight) {
        speedY = speedY * -1;
    }
  
    // HUE
    // Increasing the value
    // in each draw() call
    hue = hue + 1; 
    // We check whether the value of
    // hue becomes larger than 360,
    // and if so we reset it back to zero.
    if(hue > 360){
        hue = 0;
    }
}
```


Further explanation:

```js
// Pseudo Code

let positionX = 0;
let speedX = 1;

...

positionX = positionX + speedX;

// This means as long as speedX is a positive number such as 1, we count positionX up:
// 1 = 0 + 1 
// 2 = 1 + 1
// 3 = 2 + 1
// 4 = 3 + 1
// ...

// When positionX becomes larger than windowWidth, we 
// multiply speedX by -1 so that speedX becomes equal -1

if(positionX > 255) {
    speedX = speedX * -1;
}

// 1 * -1 = -1 -> speedX is now -1

// This would work the same with any other value for speedX
// Let's say seepX is 5:
// 5 * -5 = -5 -> speedX is now -5


// Now when we count up positionX, we are actually doing a subtraction!

positionX = positionX + speedX;

// This means as long as speedX is -1, we count positionX DOWN:
// 360 + (-1) = 360 - 1 = 359
// 359 + (-1) = 358
// 358 + (-1) = 357
// ...

// Again, this would work the same with any other value for speedX
// Let's say seepX is now -5:
// 360 + (-5) = 360 - 5 = 355
// 355 + (-5) = 350
// 350 + (-5) = 345
// ...

// The if the case becomes true that positionX is smaller 0, 
// meaning running out of the canvas on the left side, we 
// multiply speed again with -1, making it positiv again:

// -1 * -1 = 1 -> speedX is now 1 again

// (negative multiplied by negative is positive again...)

```



## Arithmetic Operators

Arithmetic operators give us the option to use short-cuts for computations and to make our code a bit more concise.

| Arithmetic               | Operator |
|--------------------------|----------|
| Addition                 | `+`      |
| Subtraction              | `-`      |
| Multiplication           | `*`      |
| Division                 | `/`      |
| Increment value with one | `++`     |
| Decrement value with one | `--`     |

```js
let value = 10;

value = value + 1; //now value is 11

// This is the same as the line above
value++; //now value is 12
```

```js
let value = 10;

value++; //now value is 11
value--; //now value is 10 again
```

If you want to work with the current value of the variable often this short cut is used:


```js
let num = 12;

num = num + 20; //now value is 32

// This is the same as the line above
num +=20; //now num is 52
```

```js
let num = 10;

num +=20; //now num is 30
num *=2
```

```js
let num = 10;

num +=20; //now num is 30
num *=2; //now num is 60
```

Hence, the above code example we can shorten to:


```js
let hue = 0;
let positionX = 0;
let positionY = 0;
let speedX = 5;
let speedY = 5;

function setup() {
    createCanvas(windowWidth, windowHeight); 

    colorMode(HSB);
    background(100);
    fill(hue, 100, 100);
    noStroke();
}

function draw() {

    // Using the colorRed variable
    // as value for the red channel
    fill(hue, 100, 100);
    ellipse(positionX, positionY, 20, 20);
    
    // POSITION
    // Increasing the position values
    positionX += speedX;
    positionY += speedY;
  
    // If the x position runs out of the canvas, 
    // reset the position to 0
    if(positionX < 0 | positionX > windowWidth) {
        speedX *= -1;
    }
    
    // If the y position runs out of the canvas, 
    // reset the position to 0
    if(positionY < 0 | positionY > windowHeight) {
        speedY *=  -1;
    }
  
    // HUE
    // Increasing the value
    // in each draw() call
    hue += 1; 
    // We check whether the value of
    // hue becomes larger than 360,
    // and if so we reset it back to zero.
    if(hue > 360){
        hue = 0;
    }
}
```




---

Good job on our side! 😁 We are starting to become real programmers!!

Now, it is time for a break... 🏖️



## Summary

* We use variables to save and access data
    * `let hue = 0;`
    * Variables have a data type
    * Variables live inside `{}` and have a scope


Use the [reference](https://p5js.org/reference/) 🚒


## References

[[1] C. Reas, B. Fry (2014): Interactivity. Processing: A Programming Handbook for Visual Designers and Artists. MIT Press.](https://www.processing.org/tutorials/interactivity/)  
[[2] MDN web docs - JavaScript data types and data structures](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Data_structures)  
[[3] Programiz - JavaScript Data Types](https://www.programiz.com/javascript/data-types)  


---

The End

📦 🐱 🎨