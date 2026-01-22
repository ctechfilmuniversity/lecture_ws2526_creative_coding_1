---
layout: default
title: Script 05 - Color Systems
parent: Scripts
nav_order: 5
---

# Creative Coding For Beginners
  
Prof. Dr. Lena Gieseke \| l.gieseke@filmuniversitaet.de  
  


# Script 05 - Color Systems

![colorsystem_01](img/05/colorsystem_01.jpg)  
[[programmingdesignsystems]](https://programmingdesignsystems.com/color/a-short-history-of-color-theory/index.html) *Goethe's color circle with magenta, yellow, and blue primary colors.*
  
![colorsystem_02](img/05/colorsystem_02.jpg)  
[[programmingdesignsystems]](https://programmingdesignsystems.com/color/a-short-history-of-color-theory/index.html) *Philipp Otto Runge's color sphere.*
  
![colorsystem_03](img/05/colorsystem_03.jpg)  
[[programmingdesignsystems]](https://programmingdesignsystems.com/color/a-short-history-of-color-theory/index.html) *Michel Eugène Chevreul's color sphere.*
  
![colorsystem_04](img/05/colorsystem_04.jpg)  
[[programmingdesignsystems]](https://programmingdesignsystems.com/color/a-short-history-of-color-theory/index.html) *Visualization of Albert Henry Munsell's color tree from the 1943 renotation.*



## Nicer Colors

The r, g, b color system is notoriously difficult to control visually. Just try to come up in your head with the needed r, g, b numbers for a nice dark yellow-green.

Thankfully, there are several **color systems** which are easier for humans to work with. p5 offers RGB and HSB.

### Color Systems

A color system is a numeric systems to represent color. There are many, many systems, optimized for specific use cases such as printing.

All of these systems are pretty much just different descriptions for the same color. The color space is the set of colors that a specific color system is able to describe.

In p5 we have access to two color systems:

* RGBA (default)
* HSB


#### RGB

* Additive color model
* Often one Byte (8 Bit) for each color
    * 0..255
* 16,7 Mio. (256 * 256 * 256 = 16 777 216) different colors describable

![ch03_09](img/05/ch03_09.png)
[medialooks](https://old.medialooks.com/mplatform/docs/CK%20Advanced.html)

![ch03_10](img/05/ch03_10.png)


#### HSB

HSB gives usually better control over the color and offers a more aesthetic color gradient. The color system's parameter are based on human perception.

* Hue
    * Position on color spectrum 0°..360°
* Saturation
    * “Amount of color”
    * Ratio color and grey, 0%..100%
* Brightness
    * Ratio color and black, 0%..100%
* 3,6 Mio. (360 * 101 * 101 = 3 672 360) different colors describable


![ch03_11](img/05/ch03_11.png)

![ch03_12](img/05/ch03_12.png)

![ch03_13](img/05/ch03_13.png)


In p5 you can set the color system to HSB with:

```js

//https://p5js.org/reference/#/p5/colorMode

colorMode(HSB);

// This sets the channel ranges to
// H: 0..360
// S: 0..100
// B: 0..100
```

That command should be placed before all other commands working with color, such as `background()` and `fill()`.  
  
Also, you can define the value range for all OR each channel:

```js
//https://p5js.org/reference/#/p5/colorMode

colorMode(HSB);
// This sets the channel ranges to the default values of
// H: 0..360
// S: 0..100
// B: 0..100
```

vs.
  
```js
colorMode(HSB, 100);
// H: 0..100
// S: 0..100
// B: 0..100
```

vs.
  
```js
colorMode(HSB, 123, 456, 10000);
// H: 0..123
// S: 0..456
// B: 0..10000
```

Notice, how the same function can be called with different arguments!

By using the HSB color system instead of RGB, we can iterate through the hue channel and with that we only change the color. We keep the brightness and saturation as it. Hence, we are getting nicer, fully bright and saturated colors.

```js
function setup() {
    createCanvas(500, 500);

    // Setting the color mode
    // to HSB
    colorMode(HSB);

    // Then we also need to
    // adjust the background values
    // to the hsb system
    background(0, 0, 100);
    noStroke();
}

function draw() {

    ellipse(mouseX, mouseY, 100, 100);
}

function mousePressed(){

    // Here we randomize only the hue
    // and keep saturation and brightness constant
    fill(random(360), 100, 100);
}
```


*On a side note:*  

Another benefit of the hue channel is that the hue spectrum has at both ends the same color (0 = 359 = red):

![](img/04/colorlines_06.png)

This is for loops through the hue spectrum very convenient. We will come back to this.


## Summary

* In p5 there are two color systems available
    * RGBA
    * HSB
* We activate a color system with `colorMode(HSB);`
    * We can adjust the value range for each channel (if need be)
        * `colorMode(RGB, 100);`
        * `colorMode(HSB, 100, 1000, 10000);`

Use the [reference](https://p5js.org/reference/) 🚒


## References

[[1] C. Reas, B. Fry (2014): Interactivity. Processing: A Programming Handbook for Visual Designers and Artists. MIT Press.](https://www.processing.org/tutorials/interactivity/)  
[[2] MDN web docs - JavaScript data types and data structures](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Data_structures)  
[[3] Programiz - JavaScript Data Types](https://www.programiz.com/javascript/data-types)  


---

The End

📦 🐱 🎨