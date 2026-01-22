---
layout: default
title: Scripts p5
nav_exclude: true
---


# Script 11 - Sound

* [Script 11 - Sound](#script-11---sound)
    * [Learning Objectives](#learning-objectives)
    * [Sound](#sound)
        * [Loading And Playing A Sound File](#loading-and-playing-a-sound-file)
    * [PlayMode](#playmode)
    * [Adding A Sound Effect](#adding-a-sound-effect)
    * [Summary](#summary)

---

## Learning Objectives

With this script you know how to work with sound files.


## Sound

To make our game quite annoying... aehm I mean more interesting, let's add sound effects. For that we are using the [sound library](https://p5js.org/reference/#/libraries/p5.sound). This library is actually developed by the p5 team and is therefore also [documented on the p5 website](https://p5js.org/reference/#/libraries/p5.sound). As you can see in the documentation, there is a lot of functionality provided to work with sound with examples given for:

* Load/Play Sound
* Preload SoundFile
* soundFormats
* Play Mode
* Pan Sound
* Sound Effect
* Playback Rate
* Measuring Amplitude
* Noise Drum Envelope
* Note Envelope
* Oscillator Frequency
* Mic Input
* Frequency Spectrum
* Mic Threshold
* Filter LowPass
* Filter BandPass
* Delay
* Reverb
* Convolution Reverb
* Record Save Audio
* Frequency Modulation
* Amplitude Modulation

For our game, we are only looking into some basics such as starting and stopping a file.

Do not forget to [include the library in your sketch](itc_ws2021_10_libraries_script.md#using-libraries-in-openprocessing). Forgetting to add a library to the sketch is a common error.

Working with sound files follows pretty much the same logic as working with images. You have to:

* add the sound files as asset to your sketch
* load the sound file in your code
* save it in a variable, and 
* then work with that variable.

### Loading And Playing A Sound File

The most basic functions for working with a [sound variable](https://p5js.org/reference/#/p5.SoundFile) are:

* start()
* stop()
* pause()

These functions "belong" to a sound object, hence you have to attach them to them by a dot:

```js
let sound = loadSound(...);

sound.start();
sound.stop();
```

The following example loads a .mp3 and plays it when we press the mouse (assuming that you have the blues_string.mp3 as asset added to your sketch).

```js
// 09.01 Playing Sound 
// https://www.openprocessing.org/sketch/1064943
// Source: https://p5js.org/examples/sound-load-and-play-sound.html


// A sound file object
let jinggle;

function preload() {
    jinggle = loadSound('blues_string.mp3');
}

function setup() {
    createCanvas(720, 200);
    background(255, 0, 0);
}

function mousePressed() {

    // .isPlaying() returns a boolean
    if (jinggle.isPlaying()) {

        jinggle.stop();
        // jinggle.pause();
        background(255, 0, 0);

    } else {

        jinggle.play();
        background(0, 255, 0);
    }
}
```

## PlayMode

p5.SoundFile has two play modes: `restart` and `sustain`. Play Mode determines what happens to a p5.SoundFile if it is triggered while in the middle of playback. In `sustain` mode, playback will continue simultaneous to the new playback. In `restart` mode, `play()` will stop playback and start over. Sustain is the default mode.


```js
// 09.02 PlayMode 
// https://www.openprocessing.org/sketch/1064952

// A sound file object
let jinggle;

function preload() {
    jinggle = loadSound('blues_string.mp3');
}

function setup() {
    createCanvas(720, 200);
    
    jinggle.playMode('restart');
    // jinggle.playMode('sustain');
}

function mousePressed() {
    
    background(random(255));
    jinggle.play();
}
```

As said before, there are many, many more given functions to work with sound. For example, you can also record sound with p5.

## Adding A Sound Effect

Now, we want to add a sound effect to our game whenever our player collected a point. For that we need to load the sound file and play it upon player-coin collision. As the sound somewhat "belongs" to a coin, we add the code to the coin tab. You can find various free sound effects on the internet, for example [here](https://mixkit.co/free-sound-effects/video-game/).

```js
// Jumping Game Step 5 - Sound 
// https://openprocessing.org/sketch/1064940#
// coin

// Sound Variable
let soundCollected;

function loadCoin() {

    ...

    // Loading the sound file, saving it in soundCollected
    soundCollected = loadSound('coin_collected.wav');
    soundCollected.playMode('restart');
}

function animateCoin() {

    ...

    // Check for collision between coin and player:
    // They collide if the distance between their positions is equal or less
    // than both of their "radiuses" (half their size)
    if (dist(coinX, coinY, playerX, playerY) <= playerSize / 2 + coinSize / 2) {
        coinCollected = true;

        // Playing the sound effect
        soundCollected.play();
    }

    ...
}
```

Of course, you can also add a song to the world, which continuously plays in loop. I add this to the background tab, as to me it feels like "background music" but you could also structure your game differently, e.g. adding the sound to mySketch. For looping a sound, you can simply call `soundBackground.loop();`. We can also reduce the file's volume a bit with [`setVolume()`](https://p5js.org/reference/#/p5.SoundFile/setVolume).

```js
// Jumping Game Step 5 - Sound 
// https://openprocessing.org/sketch/1064940#
// background


// Sound Variable
let soundBackground;


function loadBackground() {

    ...

    // Loading the soundfile
    soundBackground = loadSound('theme_loop.wav');
}

function initBackground() {

    ...
    
    soundBackground.play();
    
    // Repeating the sound file
    soundBackground.loop();
    
    // Reducing the volume with 
    // a value between 0 (no sound) to 1 (full volume)
    soundBackground.setVolume(0.1);
}

...

```


## Summary

[p5.sound](https://p5js.org/reference/#/libraries/p5.sound)


Loading a sound file:

```js 
let song;

function preload() {
    song = loadSound('song.mp3');
}
```

```js
song.playMode('restart');
song.setVolume(0.1);
song.play();

...

song.stop();
```

Use the [reference](https://p5js.org/reference/) 🚒

---

The End

🎹 🥁 🎧