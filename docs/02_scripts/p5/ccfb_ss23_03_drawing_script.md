---
layout: default
title: Script 03 - Drawing
parent: Scripts
nav_order: 3
---

# Creative Coding For Beginners
  
Prof. Dr. Lena Gieseke \| l.gieseke@filmuniversitaet.de  
  

# Script 03 - Drawing

* [Creative Coding For Beginners](#creative-coding-for-beginners)
* [Script 03 - Drawing](#script-03---drawing)
    * [Function Calls](#function-calls)
        * [Hello World II](#hello-world-ii)
    * [System Loop](#system-loop)
    * [Drawing](#drawing)
        * [Create Canvas](#create-canvas)
        * [Pixel](#pixel)
        * [Coordinate (x,y)](#coordinate-xy)
        * [Drawing Function Calls](#drawing-function-calls)
            * [Line](#line)
            * [Triangle](#triangle)
            * [Rectangle](#rectangle)
            * [Ellipse](#ellipse)
            * [Quad](#quad)
            * [Arc](#arc)
            * [Polygon](#polygon)
        * [Colors](#colors)
            * [RGB](#rgb)
            * [Alpha](#alpha)
            * [Color Commands](#color-commands)
            * [Color Function Calls - Example](#color-function-calls---example)
    * [Comments](#comments)
    * [Getting Help 🚒](#getting-help-)
    * [References](#references)
* [The End](#the-end)
* [👩🏽‍💻 👨🏻‍🎨](#-)

---

Now, you are learning how to draw these friendly fellas:

![drawing_01](img/03/drawing_01.png)

## Function Calls

Hello World!

<script type="text/p5" data-p5-version="1.6.0" data-height="400" data-preview-width="360" >
function setup() {

    createCanvas(300, 300);
}

function draw() {

    point(100, 200);
}
</script>

The above statement calls the function point and executes it. You can understand a function call as giving a certain command.

```js
Dear p5, please draw a point at the location (10, 50)!
```

What the function exactly executes is defined inside of p5. A sketch is a list of function calls put together.


Function calls consist of three parts

1. The `name` of the function to call
    * Usually the name describes the overall task
    * **Draw a point!**
2. `( )`  
    * In the parenthese you can give input data for the task
    * Here, we have the two arguments `(10, 50)` which indicate the location
    * **At location 10, 50**
3. The semicolon indicates the end of the command
    * Semicolons are optional in p5 and JavaScript. I recommend to place them (they are essential in many other programming languages).  


```js
functionname(argument1, argument2, argument3, ...);
functionname();
```

### Hello World II

```js
print("Hello World!");
```

With `print` you can send text to the console:

![ch01_09](img/03/ch01_09.png)

This is useful to set checkpoints in your program and to print the values of variables. We will come back to this.


[[07]](http://michaelkipp.de/processing/01%20zeichnen.html)

Why is there a counter counting up in the console when printing?

## System Loop

In p5 a sketch **must** include the following base structure:

```javascript

function setup() {

    [HERE YOU WRITE YOUR CODE]
}


function draw() {

    [HERE YOU WRITE YOUR CODE]
}
```

`setup()`

* What stands in the {} is executed once when the program is started.

`draw()`

* What stands in the {} is executed as soon as setup() is done.
* The code in the {} is executed again and again until the window is closed or the execution stopped.
* By default 60 frames are displayed in a second.

You have to accept the structure as given from the p5 gods for now. You must not change it and use it exactly as is, with all words and parenthesis.

## Drawing

### Create Canvas

For being able to display something, you have to create a canvas. You must do that inside of the {} of `setup()`:

```javascript
function setup() {

    createCanvas(100, 100);

}

function draw() {

}
```

* The values change the size of the canvas.
* You can use the variables `windowWidth` and `windowHeight` for automatically detecting the current size of the display window.


### Pixel

The canvas is a grid of small rectangles that combined make up the image. These rectangles are called pixel (picture element). To create an image you have to assign a color to each pixel

![ch01_10](img/03/ch01_10.png)

Thankfully, p5 give us many convenient drawing functions so that we don't have to color each pixel individually.

[[07]](http://michaelkipp.de/processing/01%20zeichnen.html)

### Coordinate (x,y)

![ch01_12](img/03/ch01_12.png)

Where to is following ellipse drawn?

```js
function setup() {

    createCanvas(500, 500);
}

function draw() {

    ellipse(100, 400, 20, 20);
}
```

### Drawing Function Calls

A typical drawing function call (aka *command*) could look for example as follows:

![ch01_13](img/03/ch01_13.png)

**The order of the parameters is fixed and must be followed!**

#### Line

```js
line(x1, y1, x2, y2);
```

Arguments:

* Start `(x1, y1)`
* End `(x2, y2)`

![ch01_14](img/03/ch01_14.png)

#### Triangle

```js
triangle(x1, y1, x2, y2, x3, y3)
```

Arguments:

1. corner `(x1, y1)`
2. corner `(x2, y2)`
3. corner `(x3, y3)`

![ch01_15](img/03/ch01_15.png)


#### Rectangle

```js
rect(x1, y1, breite, hoehe)
```

Arguments:

* Top, left corner `(x1, y1)`
* width
* height

![ch01_16](img/03/ch01_16.png)


#### Ellipse

```js
ellipse(x, y, diameterWidth, diameterHeight);
```

Arguments:

* Center point `(x, y)`
* diameterWidth
* diameterHeight

![ch01_17](img/03/ch01_17.png)


#### Quad

```js
quad(x1, y1, x2, y2, x3, y3, x4, y4)
```

Arguments:

1. corner `(x1, y1)`
2. corner `(x2, y2)`
3. corner `(x3, y3)`
4. corner `(x4, y4)`

![ch01_18](img/03/ch01_18.png)

#### Arc 

🤓

![rainbow_01](img/03/rainbow_01.png)

Drawing arcs is an example for needing a tiny bit of mathematical understanding.

```js
arc(x, y, width, height, alpha, beta);
```

Arguments:

* Center `(x1, y1)`
* `width`
* `height`
* Angle where to start `alpha`
* Angle where to end `beta`
    * Angles are in radians
    * 360° are 2π

![ch01_21](img/03/ch01_21.png)

Angles are measured in reference to a line starting at the center, running to the right, clock-wise.

![ch01_23](img/03/ch01_23.png)

![ch01_25](img/03/ch01_25.png)


![ch01_24](img/03/ch01_24.png)




##### Degrees vs. Radians 🤓

Radians are alternate units used to measure angles. Just as it sounds, a radian is based on the radius of a circle. One radian (abbreviated rad) is the angle created by bending the radius length around the arc of a circle. Because a radian is based on an actual part of the circle rather than an arbitrary division, it is a much more natural unit of angle measure and often used for creating graphics. [[2]](https://www.ck12.org/book/CK-12-Trigonometry-Concepts/section/2.1)


![ch01_22](img/03/ch01_22.png)

You don't really have to understand what radians are. You just need to know how to use command with radians.


##### Examples

Radians are often expressed in relationship to [`PI`](https://en.wikipedia.org/wiki/Pi) (which is the very special number 3.14159265359...). `360°` are `2PI`, hence, e.g., `30°` are `PI/6`.

```js
arc(4, 5, 5, 7, PI/6, 2*PI - PI/6);
```

p5 is so nice and provides you with the function `radians()`, which converts degrees in radians for you:

```js
arc(4, 5, 5, 7, radians(30), radians(330));
```



[[1]](http://michaelkipp.de/processing/01%20zeichnen.html)


#### Polygon

* A number of given vertices are connected with a line

![ch01_26](img/03/ch01_26.png)

* `beginShape` tells Processing that we are giving vertices for a polygon now
* Corners are added with the `vertex` command
* `endShape` ends the definition
    * `CLOSE` tells Processing to close the shape
    * If not given the last and first vertices of the poly are not connected

![ch01_27](img/03/ch01_27.png)


### Colors

#### RGB

By default Processing uses RGBA-color space with

* red, green, blue, alpha
* 0 … 255
* 0 = no color
* 255 = full saturation

Gray has the same value in all three channels.

![ch01_19](img/03/ch01_19.jpg)  
[[tutsplus]](http://cdn.tutsplus.com/active/uploads/legacy/tuts/076_rgbShift/Tutorial/1.jpg)


#### Alpha

Alpha describes the transparency of the, e.g., filling:

* 0 … 255
* 0 = fully transparent
* 255 = fully opaque

![ch01_20](img/03/ch01_20.png)


#### Color Commands

Setting the background color:

```js
background(r, g, b);
```

Changing attributes of the drawing commands:

```js
fill(r, g, b);
stroke(r, g, b);
strokeWeight(w);
```

These commands function as “turn on”-button and are valid until overwritten or deactivated.

```js
noFill(); 
noStroke();
```



#### Color Function Calls - Example

```js
// colorCommands.js

function setup() {
    createCanvas(500, 500);
    
    // Background color of the canvas
    background(0, 0, 0);
}

function draw() {
    
    // Rectangle left
    fill(0, 0, 255); 
    noStroke();
    rect(50, 50, 150, 200);
    
    // Ellipse
    fill(255, 0, 0);
    stroke(255, 255, 255);
    strokeWeight(10);
    ellipse(250, 250, 150, 200);
    
    // Rectangle right
    fill(255,168,233);
    strokeWeight(20);
    rect(300, 290, 150, 200);
}
```


## Comments

Comments are text, which p5 will ignore when executing your script file. Comments are crucially important for making code more understandable. They are furthermore used for documentation and code testing.

Inline comment:

```js
x = x + 1;  //add border
```

Single line comment:

```js
//fill(r, g, b);
//stroke(r, g, b);
//strokeWeight(w); 
```

Multiline comment:

```js
/* The following computes
…
…
*/
```

## Getting Help 🚒

How is one supposed to know this?

Look it up in the reference: https://p5js.org/reference/

The reference is like a dictionary of the programming language. Learning to work with the reference is as important as learning the programming syntax. I recommend to bookmark this page as you will come back to is many, many times.


## References

[[1] M. Kipp: Vorlesungsskript Grundlagen der Programmierung - 1 Zeichnen, Hochschule Augsburg](http://michaelkipp.de/processing/01%20zeichnen.html)  
[[2] CK-12 Foundation: Trigonometry Concepts - 2.1 Radian Measure](https://www.ck12.org/book/CK-12-Trigonometry-Concepts/section/2.1)

---

# The End  
# 👩🏽‍💻 👨🏻‍🎨 