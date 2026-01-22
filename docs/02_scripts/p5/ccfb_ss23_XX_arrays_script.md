---
layout: default
title: Scripts p5
nav_exclude: true
---

## Spritesheet Animation

Another way of bringing images to live is to use a series of still images and display them in a fast sequence. This technique was "invented" in 1872 by Eadweard Muybridge. He was commissioned to prove whether a horse lifted all four legs off the ground at once when it ran. To do so, he set up a series of cameras along a track and took pictures in quick succession as a horse ran by. This process allowed him to capture 16 pictures of the horse's run. In one of the pictures, the horse did indeed have all four legs off the ground.

![ch06_08.png](img/images/ch06_08.png)

Muybridge later repeated the experiment and placed each photo onto a device that could project the photos in rapid succession to give the illusion of the horse running, creating the first movie projector!


To rebuild Muybridge's principle of animation in p5, we first of all need an image sequence. We are going to use here Muybridge's original and divide it in separate files as frame-0.jpg, frame-1.jpg, frame-2.jpg, ..., frame-14.jpg.

Instead of loading all files separately such as

```js
// Spritesheet Animation - STEP 4
// https://openprocessing.org/sketch/1256845


let imgArray = []; // Image array

function preload() {
    // Store images in array
    imgArray.push(loadImage("frame-0.jpg"));
    imgArray.push(loadImage("frame-1.jpg"));
    imgArray.push(loadImage("frame-2.jpg"));
    imgArray.push(loadImage("frame-3.jpg"));
    ...
}
```

we can loop over all files based on their name. We can use the iterator i as a part of the images file name. Because our program doesn't know how many images we have, we define `numberImg` ourself and use it as the iteration limit in the for loop.

```js
// Spritesheet Animation - STEP 5
// https://openprocessing.org/sketch/1256845

let imgArray = []; // Image array
let numberImg = 15; // Number of images

function preload() {
    // Store images in array
    for (let i = 0; i < numberImg; i++) {
        imgArray.push(loadImage("frame-" + i + ".jpg"));
    }
}
```

We create a new variable to keep track of the image that is currently displayed. Then we can count up imgIndex, from 0 to numberImg and then back to 0.


```js
// Spritesheet Animation - STEP 7
// https://openprocessing.org/sketch/1256845

let imgArray = []; // Image array
let numberImg = 15; // Number of images
let imgIndex = 0; // Index of the image currently displayed

function preload() {
    // Store images in array
    for (let i = 0; i < numberImg; i++) {
        imgArray.push(loadImage("frame-" + i + ".jpg"));
    }
}

function setup() {
    createCanvas(600, 600);
    background(255);
}

function draw() {
    // Display the image at current index
    image(imgArray[imgIndex], 0, 0);

    // We want to iterate the image for each draw call.
    // For that, we count up imgIndex
    
    imgIndex++; // Next image

    if (imgIndex == numberImg) { // Reached last image
        imgIndex = 0 // Back to first image
    }
}
```

To change the speed of the animation we need to control how often imgIndex is increased. A simple solution would to just lower the framerate to a lower value with the frameRate() command.   

But most of the time this is not very useful, because now the whole program runs at 10 frames per second. What if we want to display something else in an other pace? We need a way to control how often imgIndex counts up.

The solution is to use the modulo operator, which returns for a division with a whole number the rest of that division, on the frameCount variable. frameCount contains the number of frames that have been displayed since the program started. So `(frameCount % 5 == 0)` is true when the current frame number is dividable by 5 without remainders, which means every 5th frame.

With that functionality we can increase `imgIndex` only every 5th frame.


```js
// Spritesheet Animation - STEP 10
// https://openprocessing.org/sketch/1256845

let imgArray = []; // Image array
let numberImg = 15; // Number of images
let imgIndex = 0; // Index of the image currently displayed

function preload() {
    // Store images in array
    for (let i = 0; i < numberImg; i++) {
        imgArray.push(loadImage("frame-" + i + ".jpg"));
    }
}

function setup() {
    createCanvas(600, 600);
    background(255);

}

function draw() {
    // Display the image at current index
    image(imgArray[imgIndex], 0, 0);

    // We want to iterate the image for each draw call.
    // For that, we count up imgIndex
    
    if (frameCount % 5 == 0) { // Every 5th frame
        imgIndex++; // Next image

        if (imgIndex == numberImg) { // Reached last image
            imgIndex = 0 // Back to first image
        }
    }
}
```

Ideally replace the modulo number with the a global variable, e.g., `animationSlowDown` to have easy access for changing the speed.

You can also follow these explanations in [this tutorial](https://openprocessing.org/sketch/1256845) in OpenProcessing.




