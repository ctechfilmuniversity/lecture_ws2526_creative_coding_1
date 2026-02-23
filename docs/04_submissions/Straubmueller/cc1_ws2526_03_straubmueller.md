---
layout: default
title: Homework
nav_exclude: true
---


# Creative Coding I

Jonathan Ho \| jonathan.g.ho@filmuniversitaet.de
Prof. Dr. Lena Gieseke \| l.gieseke@filmuniversitaet.de  \| Film University Babelsberg KONRAD WOLF
  


# Session 03 - Space (10 points)

Please complete this session by January 28th. Completing the session should take < 5h.  


* [Creative Coding I](#creative-coding-i)
* [Session 03 - Space (10 points)](#session-03---space-10-points)
    * [Local Installation](#local-installation)
        * [Task 03.01 - Your First Scene](#task-0301---your-first-scene)
    * [three.js](#threejs)
        * [Task 03.02 - Local Project Setup](#task-0302---local-project-setup)
        * [Task 03.03 - Your First Scene](#task-0303---your-first-scene)
    * [Learnings](#learnings)


In this session we are dealing with the topic of _space_ and what types of virtual spaces we are working with. In terms of tech, this session introduces you to the JavaScript library [`Threejs`](https://threejs.org/), which is a good choice if you want to build 3D scenes in a browser.

## Local Installation

### Task 03.01 - Your First Scene

* [Install node, nvm and npm](https://nodejs.org/en/download)
* Verify a correct installation with executing `node -v` and `npm -v` in the terminal

*Submission:* -

## three.js

### Task 03.02 - Local Project Setup

Task 03.02 should be developed with a proper local installation. For that you can follow these steps in a terminal:

* Create a project folder
    * Either manually or in the terminal with `mkdir foldername`
* With the terminal navigate into the folder you just created and execute:
    * `npm init -y`
    * `npm install three vite`
* In `package.json` add line `"dev": "vite",` by changing the `"scripts": {...}` entry to:

```
  "scripts": {
    "dev": "vite",
    "test": "echo \"Error: no test specified\" && exit 1"
  },
```
* Create a `index.html` and a `scene.js`
* Add to `index.html`:

```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Hello three.js!</title>
    <style>
        body { margin: 0; }
    </style>
  </head>

  <body>
    <canvas id="canvasThree"></canvas>
    <script type="module" src="scene.js"></script> 
  </body>
</html>
```
* Complete `Task 03.03` in `scene.js`

### Task 03.03 - Your First Scene

Build a three dimensional, geometric scene. With geometric I mean that the scene should focus on abstract geometry - also think *sculptural*. Remember: exceptional creativity often emerges out of constraints and refrainment 😎. You could (but don't have to) find inspiration in the following art work. 


![mondrian_01](img/mondrian_01.png)  
[[Composition A, Piet Mondriaan, 1923]](https://www.wikiart.org/de/piet-mondrian/composition-a-1923) 

![kandinsky_02](img/kandinsky_02.jpg)  
[[Several Circles, Wassily Kandinsky, 1926]](https://en.wikipedia.org/wiki/File:Vassily_Kandinsky,_1926_-_Several_Circles,_Gugg_0910_25.jpg)

![balazova_01](img/balazova_01.jpg)  
[[Hadia geometria 36 – Alphabet 1, Mária Balážová, 1956]](https://www.1stdibs.com/art/prints-works-on-paper/abstract-prints-works-on-paper/yaacov-agam-thanksgiving/id-a_13123922/) 

![waldheims_01](img/waldheims_01.jpg)  
[[ Drawing #220, Zanis Waldheims, 1969]](https://post.moma.org/zanis-waldheims/) 

![agam_01](img/agam_01.png)  
[[Thanksgiving, Yaacov Agam, 1980]](https://www.1stdibs.com/art/prints-works-on-paper/abstract-prints-works-on-paper/yaacov-agam-thanksgiving/id-a_13123922/) 


![lewitt_01](img/lewitt_01.png)  
[[Wall Drawing #564, Sol LeWitt, 1988]](https://www.nytimes.com/2013/09/06/arts/design/sol-lewitt.html) 

![molnar_01](img/molnar_01.jpg)  
[[Dürer, Pair Impair A, Vera Molnar, 2021]](https://www.apollonia-art-exchanges.com/en/vera-molnar/) 


<br >

> How to translate the above 2D concepts and aesthetics into 3D space?  
  
> How to give the above abstractions an 3D embodiment?  
  
> How to merge 2D and 3D?
   
> How about using time as an creative tool? Could there be movement?

<br >

![abstractions_10](img/abstractions_10.jpg)  
[[The Moving Moment When I Went To The Universe, Yayoi Kusama, 2018]](https://ocula.com/art-galleries/victoria-miro-gallery/exhibitions/yayoi-kusama/)  

---

For this task there is no need to go beyond the three.js basic elements that we have discussed in class. The scene should be navigable with (e.g., a simple orbit control but feel free to do something different) but other than that the scene should not include any interactions.

*Note:* If you have previous experience with three.js and consider yourself a proficent programmer, I expect you to still challenge yourself technically with this exercise as well as completing a polished result.
  

*Submission*: ![submission03-Image ](./img/260126_CC1_Task%2003-03.png)

- [Click here for the video](https://owncloud.gwdg.de/index.php/s/AqZgOTwcpIk0UKi)
- [Click here for the source files](./cc1_ws2425_03_straubmueller)





## Learnings

Please summarize your personal learnings. What was challenging for you in this session? How did you challenge yourself?

*Submission*: 

#### What I learned
- How to build a modular geometry system instead of placing objects manually

- How to use loops and functions to generate procedural compositions
- How to use Groups to organize multiple meshes as one unit
- How to create depth fog and different lighting
- How to control the camera look (distortion)
- How to add OrbitControls 
- How to animate motion by using the render loop
- How color works in Three.js (0xRRGGBB)


#### What I struggled with

First, I wanted to test a different concept, in which I lined up glass panes and placed them in front of a sphere to break up the silhouette of the sphere in the panes. I tried to make the glass look more realistic with a gradient PNG, which looked absolutely terrible. I also wanted to apply a noise texture to the sphere, which didn't look good either. After many attempts, I finally decided to pursue a different concept, as even after several hours, the results were disappointing. (Sadly, that is the only work-in-progress image I took. I, of course, tried to place the panes in front of the sphere)

![submission03-Image ](./img/260126_CC1_Session03_Task%2003-03_WIP-01.png)


Also:

- White screen → JavaScript crashed before rendering
- Shapes repeating identically → cloning results instead of regenerating with logic
- Layout breaking when rotating → rotating coordinate systems vs rotating objects
- Multiple groups appearing → loop ranges creating extra instances

#### How I challenged myself

I found it particularly difficult to use and understand the cloning and tiling system and to work with light and materials without making the scene look flat, which is the reason why I worked with an HDR and fog.

---

Write and link all task results in a copy of this file. Submit your copy as `cc1_ws2526_XX_lastname.md` in your assignments' folder.

Please add the following header at the beginning of your Markdown file:

```md
---
layout: default
title: Homework
nav_exclude: true
---
```

---


**Happy Three Dimensioning!**
