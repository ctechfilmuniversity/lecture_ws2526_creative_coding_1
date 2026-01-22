---
layout: default
title:  Script 07 - Three.js
parent: Scripts
nav_order: 6
---

# Creative Coding I: Design & Communication

Jonathan Ho \| jonathan.g.ho@filmuniversitaet.de
Prof. Dr. Lena Gieseke \| l.gieseke@filmuniversitaet.de \| Film University Babelsberg KONRAD WOLF

---

# Script 06 - Three.js

The first version of this script was written by:
  
Anna Eschenbacher \| anna.eschenbacher@filmuniversitaet.de \| Film University Babelsberg KONRAD WOLF

By now, the script has been heavily updated by Lena.  



---

* [Creative Coding I: Design \& Communication](#creative-coding-i-design--communication)
* [Script 06 - Three.js](#script-06---threejs)
    * [*What Are The Spatial Properties Of The Virtual Space We Use?*](#what-are-the-spatial-properties-of-the-virtual-space-we-use)
    * [*How Do Analog And Virtual Spatial Spaces Relate To Each Other?*](#how-do-analog-and-virtual-spatial-spaces-relate-to-each-other)
    * [*What Makes Analog Space Unique?*](#what-makes-analog-space-unique)
    * [Threejs](#threejs)
        * [WebGL](#webgl)
        * [Alternatives](#alternatives)
    * [Example Projects](#example-projects)
        * [Collections](#collections)
    * [Installation](#installation)
        * [Online Library Files](#online-library-files)
        * [Local Installation](#local-installation)
    * [Basic Scene](#basic-scene)
        * [The THREE Object](#the-three-object)
        * [THREE Classes](#three-classes)
        * [JavaScript Objects](#javascript-objects)
        * [Scene](#scene)
        * [Camera](#camera)
        * [Renderer](#renderer)
    * [Coordinate System](#coordinate-system)
    * [Creating 3D Elements](#creating-3d-elements)
        * [Material](#material)
        * [Mesh](#mesh)
    * [Colors](#colors)
    * [Lighting](#lighting)
    * [The Render Loop](#the-render-loop)
    * [Orbit Control](#orbit-control)
    * [A Bit Prettier](#a-bit-prettier)
    * [Further Resources](#further-resources)
        * [three.js documentation](#threejs-documentation)
        * [three.js examples](#threejs-examples)
    * [References](#references)

---

Let's start easy: ***What is space***?


![dalle_space_01](./img/space/dalle_space_01.jpg)  Dall-E: *Space Virtual*


Check the [Merriam-Webster dictionary for *space*](https://www.merriam-webster.com/dictionary/space).  

<!-- Or ask ChatGPT:  

"Space" can refer to different concepts depending on the context. Here are a few possible interpretations:

* Outer Space
    * This is the vast, seemingly infinite expanse that exists beyond Earth's atmosphere. It is where stars, planets, galaxies, and other celestial bodies are located. Space is characterized by a near-vacuum environment, microgravity, and extreme conditions.
* Physical Space
    * In a broader sense, "space" can also refer to the three-dimensional expanse in which all physical objects exist. It is the container in which everything in the universe is located and can be measured in terms of length, width, and height.
* Cosmos
    * Space is often used synonymously with the term "cosmos," representing the entirety of the universe, including all matter, energy, planets, stars, galaxies, and the voids between them.
* Space as a Concept
    * In a more abstract sense, "space" can also refer to an interval or gap between objects, or a conceptual framework. For example, the space between two buildings, or the conceptual space in an art piece or a design.

On a side note: *Is ChatGPT's answer good?* -->

## *What Are The Spatial Properties Of The Virtual Space We Use?*  

![dalle_space_virtual_01](./img/space/dalle_space_virtual_01.jpg)  Dall-E: *Space Virtual*


<!-- ChatGPT's answer:

The term "virtual space" typically refers to the digital or simulated environments created for various purposes, such as computer games, virtual reality (VR) experiences, simulations, or digital design. In these contexts, virtual space exhibits several spatial properties:
* **Dimensionality**: Virtual spaces can exist in two, three, or even higher dimensions. Most commonly, virtual environments aim to replicate three-dimensional space to provide a more immersive experience.
* **Scale**: Virtual spaces can simulate various scales, from microscopic to cosmic. For example, a virtual environment might represent the interior of a building, an entire city, or an imaginary world.
* **Interactivity**: Users often have the ability to interact with objects and elements within virtual space. This can include manipulation of virtual objects, navigation through the environment, and engagement with other users (in the case of social virtual spaces).
* **Perspective**: Virtual space can be experienced from different perspectives. In virtual reality, for instance, users can look around in all directions and interact with the environment based on their head and body movements.
* **Physics**: Virtual spaces often simulate some aspects of physics, including gravity, collision detection, and object behavior. This contributes to a more realistic and immersive experience.
* **Navigation**: Users can navigate through virtual space using various means, such as walking, flying, teleporting, or using controllers. The navigation mechanisms depend on the type of virtual environment and the technology used (e.g., VR headsets, computer screens).
* **Immersiveness**: The goal of many virtual spaces is to create a sense of immersion, making users feel like they are present in the simulated environment. This is achieved through realistic graphics, sound, and interactive elements.
* **Connectivity**: Virtual spaces can be connected, allowing users to move seamlessly between different environments. This is common in virtual worlds, games, and collaborative virtual environments.

The spatial properties of virtual space are continually evolving as technology advances, enabling more realistic and immersive digital experiences. Virtual reality, augmented reality, and mixed reality technologies are at the forefront of these developments. -->


## *How Do Analog And Virtual Spatial Spaces Relate To Each Other?*  

![dalle_connection_analog_virtual_space_01](./img/space/dalle_connection_analog_virtual_space_01.jpg)  Dall-E: *Space Virtual*


<!-- ChatGPT's answer:

Analog and virtual spatial spaces are distinct concepts, but they can be related in various ways, especially when considering the representation and interaction with physical and digital environments. Here are some ways in which analog and virtual spatial spaces relate to each other:

* Representation of Physical Space:
    * Analog Space: Refers to the physical space we experience in the real world. It includes the three-dimensional environment around us, encompassing everything from our immediate surroundings to vast landscapes.
    * Virtual Space: A digital representation of space created through computer technology. Virtual spaces can aim to simulate and replicate aspects of analog space, providing a digital counterpart.
* Simulation and Modeling:
    * Analog Space: Represents the actual, tangible world with real physical objects and natural laws governing their behavior.
    * Virtual Space: Involves the creation of a simulated or modeled environment. Virtual spaces often attempt to emulate the properties of analog space, including visual appearance, physics, and interactivity.
* Interaction and Engagement:
    * Analog Space: Involves direct, physical interaction with the environment. Our interactions in the real world are governed by the laws of physics and the properties of tangible objects.
    * Virtual Space: Provides opportunities for interaction through digital interfaces. Users can manipulate virtual objects, navigate through environments, and engage with the digital space using input devices or even through immersive technologies like virtual reality.
* Extension of Reality:
    * Analog Space: The physical world we inhabit and perceive through our senses.
    * Virtual Space: Extends the possibilities of reality by introducing elements that may not exist in the physical world. This could include fantastical landscapes, fictional scenarios, or simulations of environments that are difficult to access in reality.
* Spatial Design and Architecture:
    * Analog Space: The field of physical architecture and spatial design involves creating structures and environments in the real world.
    * Virtual Space: Architects and designers use virtual spaces to visualize and plan structures before they are built. Virtual environments allow for experimentation with designs and concepts.
* Communication and Collaboration:
    * Analog Space: Involves face-to-face communication and collaboration in physical settings.
    * Virtual Space: Facilitates online communication, collaboration, and social interaction. Virtual spaces, including virtual worlds and meeting platforms, allow people to connect in a digital environment.

While analog and virtual spatial spaces have their unique characteristics, the relationship between them is often complementary. Virtual spaces can draw inspiration from, simulate, or enhance aspects of analog space, providing new opportunities for exploration, creativity, and interaction. Additionally, technologies like augmented reality seek to blend analog and virtual elements, creating mixed or augmented spatial experiences. -->


## *What Makes Analog Space Unique?*


---

## Threejs

Three.js is an **open-source library** and **API** using WebGL. It is used to create and display animated 3D graphics in a web browser. It simplifies the creation of WebGL tools and environments. [[2]](https://github.com/mrdoob/three.js/) This means, there is a whole library of simplified functions for geometries, materials, lighting, audio, etc. Alternatively, you could write everything in WebGL, but that is a bit more complicated as you can see in the example below.

### WebGL

WebGL is a JavaScript API for rendering interactive 2D and 3D graphics. It is executed on a computer's GPU. It consists of control code written in JavaScript and shader code which is written in OpenGL ES Shading Language (GLSL ES), a language similar to C or C++. [[1]](https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API)

Here is an example for WebGL code:

```js
<!doctype html>

<html>

  <body>

 	<canvas width="500" height="500"></canvas>

  <script>

    var canvas,
        gl,
        vertices,
        vertexBuffer,
        vertexShader,
        fragmentShader,
        shaderProgram;

    init();
    setupBuffers();
    createVertexShader();
    createFragmentShader();
    createShaderProgram();
    assignShadersToBuffers();
    draw();

    function init()
    {
      canvas = document.getElementsByTagName('canvas')[0];
      gl = canvas.getContext('webgl');
      vertices = [0, 1, 1, -1, -1, -1];
    }

    function setupBuffers()
    {
      vertexBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
      gl.bindBuffer(gl.ARRAY_BUFFER, null);
    }

    function createVertexShader()
    {
      var vertexShaderCode =
      'attribute vec2 coordinates;' +
      'void main(void) {' +
      ' gl_Position = vec4(coordinates, 0, 1.2);' +
      '}';

      vertexShader = gl.createShader(gl.VERTEX_SHADER);
      gl.shaderSource(vertexShader, vertexShaderCode);
      gl.compileShader(vertexShader);
    }

    function createFragmentShader()
    {
      var fragementShaderCode = 'void main(void) {' +
      'gl_FragColor = vec4(1, 0, 0, 1);' +
      '}';

      fragmentShader = gl.createShader(gl.FRAGMENT_SHADER);
      gl.shaderSource(fragmentShader, fragementShaderCode);
      gl.compileShader(fragmentShader);
    }

    function createShaderProgram()
    {
      shaderProgram = gl.createProgram();

      gl.attachShader(shaderProgram, vertexShader);
      gl.attachShader(shaderProgram, fragmentShader);
      gl.linkProgram(shaderProgram);
      gl.useProgram(shaderProgram);
    }

    function assignShadersToBuffers()
    {
      var numberOfComponentsPerVertexAttribute = 2,
          normalizeValues = false,
          numberOfBytesBetweenElements=0,
          offset=0,
          coordinates;

      gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);

      coordinates = gl.getAttribLocation(shaderProgram, "coordinates");

      gl.vertexAttribPointer(coordinates, numberOfComponentsPerVertexAttribute, gl.FLOAT, normalizeValues, numberOfBytesBetweenElements, offset);
      gl.enableVertexAttribArray(coordinates);
    }

    function draw()
    {
      var drawMode = gl.TRIANGLES,
          first=0,
          count=3;

      gl.clearColor(0.7, 0.7, 0.7, 1);
      gl.clear(gl.COLOR_BUFFER_BIT);
      gl.drawArrays(drawMode, first, count);
    }


  </script>

  </body>
</html>
```

This code will produce the following image: <br><img src="./img/space/webGL.png" width="400">

As you can see it it's quite **a lot** of code for a simple red triangle. In WebGL you do all setup steps manually.  

This is where Three.js comes in to simplify the creation of 3D graphics with WebGL.

### Alternatives

There are a few alternatives to Three.js. The most popular one for 3D content might be [babylon.js](https://www.babylonjs.com/). Of course [p5.js](https://p5js.org/) is also an alternative, but mostly used for 2D graphics.

A bablyon.js video promo:

<video height="480" controls="controls">
<source src="../02_scripts/img/space/babylon_01.mp4" type="video/mp4">
</video>

The master thesis project [Somewhere.gl](https://somewhere.gl/index.html) is also created with bablyon.js:

[![somewhere_01](./img/space/somewhere_01.png)](https://somewhere.gl/index.html)

## Example Projects

To get a first idea of what Three.js can do, let's have a look at some example projects:

- [bruno](https://bruno-simon.com/) <br><img src="./img/space/bruno_01.png" width="400">

- [cat](https://codepen.io/Yakudoo/pen/oXJYxy) <br><img src="./img/space/cat.png" width="400">

- [instancing](https://threejs.org/examples/#webgl_buffergeometry_instancing) <br><img src="https://hacks.mozilla.org/files/2017/01/instanced-rendering.jpg" width="400">

- [underwater journeys](https://www.bluemarinefoundation.com/the-sea-we-breathe/) <br><img src="https://assets.awwwards.com/awards/sites_of_the_day/2021/11/bluemarinefoundation-1.jpg" width="400">

- [HELIOS](http://unseen-music.com/yume/)
  <br><img src="./img/space/helios_01.png" width="400">

- [POLA](https://www.pola.co.jp/wecaremore/mothersday/)
  <br><img src="https://assets.awwwards.com/awards/sites_of_the_day/2022/06/pola-co-1.jpg" width="400">

- [Swiss army man](https://swissarmyman.com/)
  <br><img src="https://www.neatorama.com/images/posts/44/91/91044/1466524657-0.jpg" width="400">

- [NASA voyager's grand tour](https://eyes.nasa.gov/apps/solar-system/#/story/voyager_grand_tour)
  <br><img src="https://i.ytimg.com/vi/QRTfKYOfPLg/maxresdefault.jpg" width="400">

- [Design the next iPhone](https://neal.fun/design-the-next-iphone/)
  <br><img src="https://neal.fun/share-cards/design-the-next-iphone.png" width="400">

- [Design the next iPhone](https://fungui.resn.co.nz/)
  <br><img src="https://webgl.souhonzan.org/i/entry/2000/2309_001.jpg" width="400">

- [VR Dust](https://vrdust.org.uk/)
  <br><img src="https://vrdust.org.uk/wp-content/uploads/2017/01/dust_5.jpg" width="400">

- [Chartongne-Taillet Winery](https://chartogne-taillet.com/en)
 <br><img src="../02_scripts/img/space/chartonge_01.png" width="400">

- [My room in 3d](https://my-room-in-3d.vercel.app/)
 <br><img src="../02_scripts/img/space/myroom_01.png" width="400">

- [Reactive Sphere](https://organic-sphere.vercel.app/)
 <br><img src="../02_scripts/img/space/sphere_01.png" width="400">

- [Woodkid Robot](https://experiment-woodkid-volcano-robot.vercel.app/)
 <br><img src="../02_scripts/img/space/robot_01.png" width="400">


- [Annas first term project](https://shapedbymotion.herokuapp.com/)  
   <br><img src="../02_scripts/img/space/anna_03.png" width="400">

- [noise blob](https://codepen.io/vcomics/pen/ZwNgvX?editors=1010)
- [deprogrammed](http://www.deprogrammed.org/)
- [Thump Thump](http://www.larsberg.net/#/thumpThump)
- [real time short film](http://www.dilladimension.com/)
- [band website](https://www.aquarium.ru/en)
- [prior](https://prior.co.jp/discover/en/emotion)
- [infinit world](https://infinite-world.vercel.app/)

### Collections

- [three.js examples](https://threejs.org/examples/#webgl_animation_keyframes)
- [featured projects on the three.js](https://threejs.org/)
- [awarded Three.js projects](https://www.awwwards.com/websites/three-js/?ads=1&page=1)

## Installation

**Note for Class 2526: We install three.js and npm locally. I recommend installing Node by using nvm on MacOS and using Chocolatey on Windows we'll be using Node 24 LTS for this class.**

As with all libraries, we can access local or online versions of the library. For a proper local installation there are steps involved, we don't know yet. We will have a look at that next week.

For getting the coding started, we will simply work with links to online library files. If you already have three.js installed locally and running with vite, this section can be skipped. See the example project below for a vite project with three.js. This section below is an alternative way to get started with three.js using the live server extension for VSCode.

### Online Library Files

To make an import from three.js online library files, we will use a slightly more sophisticated script call:

```html
    <script type="importmap">
        {
            "imports": {
                "three": "https://unpkg.com/three@0.158.0/build/three.module.js"
            }
        }
    </script>
```

We need the above code due to the way the three.js library is constructed. Roughly speaking, the library is broken into different *modules*, which make it easier to maintain the code-base. The three.js library exports (meaning, *gives to us*) the module `three`. The script type [`importmap`](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/script/type/importmap#import_map_json_representation) allows to specify, which module(s) to import.  The imported library module will replace the text when the module URL is resolved.

Keep in mind, that modules only work with the HTTP(s) protocol. A web-page opened via the file:// protocol cannot use import / export.

Out of the box, three.js includes the fundamentals of a 3D engine. Other three.js components — such as controls, loaders, and post-processing effects — are part of the addons/ directory. [[7]](https://threejs.org/docs/#manual/en/introduction/Installation)

```html
<script type="importmap">
  {
    "imports": {
      "three": "https://unpkg.com/three@0.158.0/build/three.module.js",
      "three/addons/": "https://unpkg.com/three@0.158.0/examples/jsm/"
    }
  }
</script>
```

In total, we have in `index.html` for now:

```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Hello three.js!</title>

    <link rel="stylesheet" type="text/css" href="../css/style.css" />

    <script type="importmap">
        {
            "imports": {
                "three": "https://unpkg.com/three@0.158.0/build/three.module.js"
            }
        }
    </script>
  </head>

  <body>
    <canvas id="canvasThree"></canvas>
    <script type="module" src="./scene.js"></script>
  </body>
</html>
```

The three.js scene will be implemented in `scene.js` (often also called `main.js`). Please note, that the script type for a three.js scene must be set to `module`. If you do not specify the type as module, you will get an error, most likely. The type `module` causes the loaded source code to be treated as a JavaScript module, which is needed for three.js to work.

To define the canvas element (here with the id `canvasThree`), in which three.js is going to be rendered is not strictly necessary (similar to p5, where we didn't specify it), but I find it a well-structured setup.

For our first scene, we are going to make our scene fill the whole browser window. Hence, we only need basic css, such as

```css
body {
  margin: 0;
}
```

For such minimal code, we could also just add the code within a script tag within our `.html` file directly:


```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Hello three.js!</title>

    <style>
        body { margin: 0; }
    </style>

    <script type="importmap">
        {
            "imports": {
                "three": "https://unpkg.com/three@0.158.0/build/three.module.js"
            }
        }
    </script>
  </head>

  <body>
    <canvas id="canvasThree"></canvas>
    <script type="module" src="./scene.js"></script>
  </body>
</html>
```


To run this project we will use the same extensions as you did before - [live server](https://marketplace.visualstudio.com/items?itemName=ritwickdey.LiveServer) for VSCode. 

### Local Installation

We will come back to this. To install three.js locally and run it with vite, you can install it using the following steps:
1. Install Node.js and npm. I recommend installing Node by using nvm on MacOS and using Chocolatey on Windows. We'll be using Node 24 LTS for this class. For more information on how to install Node, see the [Node.js website](https://nodejs.org/en/download/).
2. Create a new project folder
3. Initialize the project with `npm init -y`
4. Install three.js and vite with `npm install three vite`
5. Add a script to package.json to run the project with npm run dev
Example package.json:
```json
{
  "name": "threejs-basics",
  "version": "1.0.0",
  "description": "Basic three.js scene setup example",
  "type": "module",
  "scripts": {
    "dev": "vite",
    "build": "vite build"
  },
  "dependencies": {
    "three": "^0.169.0"
  },
  "devDependencies": {
    "vite": "^5.4.0"
  }
}
```
6. Run the project with `npm run dev`
7. Open the project in the browser at http://localhost:5173


## Basic Scene

Now the fun part begins - let's get started with our first three.js scene, which we will implement in th `scene.js` file. 

To display something with three.js, such as the beautiful cube below, we need at the very least three components: 

1. a scene, 
2. a camera and 
3. a renderer.

The code below creates a basic scene, displaying a cube. Worry not, in the following script, I will explain each component.

```js
import * as THREE from 'three';

// SCENE
const scene = new THREE.Scene();

// CAMERA
const fov = 70;
const aspect = window.innerWidth / window.innerHeight;
const near = 0.1;
const far = 10;
const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);
camera.position.z = 1;

// RENDERER
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({canvas, antialias: true});
renderer.setSize( window.innerWidth, window.innerHeight);

// GEOMETRY
const geometry = new THREE.BoxGeometry(0.5, 0.5, 0.5);
const material = new THREE.MeshNormalMaterial();
const cube = new THREE.Mesh( geometry, material );

cube.rotation.x = 100;
cube.rotation.y = 180;
scene.add(cube);

renderer.render(scene, camera);
```

![cube_01](./img/space/cube_01.png)


### The THREE Object 

As above for the library loading already mentioned, three.js is a well-structured library, separated into different modules (and classes, see the section below). Such a setup requires us to specify for our JavaScript file, what to import from which module.

The following line indicates to import everything (`*`) from the library's module `three` (the same value as in the `"imports"` call in `index.html`) and save it in an object, which is called `THREE` (in theory, you could change this name, but `THREE` is a convention):

```js
import * as THREE from 'three';
```

In the following code we can now work with the object `THREE` and access its properties, functions, and classes with the `.`-notation, e.g., `THREE.Scene();`. 

### THREE Classes

In the three.js library many components are encapsulated into classes, e.g., there is a [`Scene`](https://threejs.org/docs/#api/en/scenes/Scene) class, a [`PerspectiveCamera`](https://threejs.org/docs/#api/en/cameras/PerspectiveCamera) class, a [`BoxGeometry`](https://threejs.org/docs/#api/en/geometries/BoxGeometry) and so on.

Don't forget: To access these classes, we always have to use the `THREE` object, which we have imported in the previous step.

The short story for working with three.js is that you have to **create instances from the given classes** in order to work with that component and to, e.g., use that component's functionalities. To create an instance of a class, we have to use the keyword **`new`**. The following code creates an instance of the [`PerspectiveCamera`](https://threejs.org/docs/#api/en/cameras/PerspectiveCamera) class (let's ignore its arguments for now) and we have to access that class through the `THREE` object:

```js
const camera = new THREE.PerspectiveCamera();
```
Once we have created an instance of the [`PerspectiveCamera`](https://threejs.org/docs/#api/en/cameras/PerspectiveCamera) class, we can work with that object:

```js
camera.position.z = 1;
```

The slightly longer explanation is that a class is a common data structure in many programming languages (also see [Script 04 - Javascript - Classes](./cc1_ws2324_04_javascript_script.md#classes)). It let's programmers define their own templates for "a type of object" (conceptually this can be anything) and define which properties and function that object should have. For example, if I am working on a game about cats, I might want to have a data structure for cats, meaning a template for the properties and functions of a cat. Once I have that template -which in computer science lingo is the class- I can derive instances from that template/class, and all instances have certain cat properties and functions.

```js
// The template
class Cat
{
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }
    makeSound() { console.log('meow') }
    getName() { console.log('My name is', this.name) }
}

// The instance
let ernie = new Cat('Ernie', 3);
ernie.makeSound();  // -> meow
```

### JavaScript Objects

When working with three.js, we often have to use objects as data structure (also see [Script 04 - Javascript - Classes](./cc1_ws2324_04_javascript_script.md#objects)). An object let's you group values into a single value, similar to an array but objects use key-value pairs.

You define an object as:

```js
let object_name = {
   key1: value1,
   key2: value2
}
```

```js
let user = {        // an object
  name: "Sully",    // the key "name" stores the value "Sully"
  age: 30           // the key "age" stores the value 30
};
```

The above is usually written more compactly as:

```js
let user = { name: 'Sully', age: 30 };
```

To access a property, we can use:  

`obj.property`  
  
e.g.,

`user.name;`

Which might be confusing, an which might happen, when working with three.js: When defining an object, there is a short-cut for the case that key and value are the same.

Let's say we have a variable `name` that we want to save in a key called `name`:

```js
let name = 'Sully';
let age_sully = 30;

let user = { name: name, age: age_sully };
```

The expresseion `name: name,` within an object can be shortend to just `name`:

```js
let name = 'Sully';
let age_sully = 30;

let user = { name, age: age_sully };
```

For example, when creating an instance of three.js's [WebGLRenderer](https://threejs.org/docs/?q=WebGLRenderer#api/en/renderers/WebGLRenderer) class, it takes as an argument an object. That object has, among other keys, the key `canvas`. The long version of the object as argument would be

```js
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({canvas: canvas, antialias: true});
```

But as we have the same name for object key and variable to pass, the code is usually written as:

```js
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({canvas, antialias: true});
```

In the following case, we can not shorten the code, as our variable is called `myCanvas` and not `canvas`:


```js
const myCanvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({canvas: myCanvas, antialias: true});
```


### Scene

```js
const scene = new THREE.Scene();
```

Three.js uses the concept of a *scene*. You can think of a scene as the object, which holds everything together, which belongs to a scene, such as geometry and lights, and which is then given to the renderer (together with a camera).

Under the hood, a `Scene` object defines the root of a [scenegrap](https://threejs.org/manual/#en/scenegraph). A scene graph in a 3D engine is a hierarchy of nodes in a tree-like structure, where each node represents a local space:

![scenegraph_01](./img/space/scenegraph_01.png)


### Camera

There are a few different camera types in three.js. We will use a [PerspectiveCamera](https://threejs.org/manual/#en/cameras) since its projection mode is designed to mimic the way the human eye sees. 

```js
const fov = 70;
const aspect = window.innerWidth / window.innerHeight;
const near = 0.1;
const far = 10;
const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);
```

As shown above, we can create an instance of the [`PerspectiveCamera`](https://threejs.org/docs/#api/en/cameras/PerspectiveCamera) class with the following arguments:

**PerspectiveCamera( fov : Number, aspect : Number, near : Number, far : Number )**

1. fov — Camera frustum vertical field of view.
2. aspect — Camera frustum aspect ratio.
3. near — Camera frustum near plane.
4. far — Camera frustum far plane.

The first attribute is the **field of view**. FOV is the extent of the scene that is seen on the display at any given moment. The value is in degrees.

For example, this image shows different field of views taken from the same camera position (with real cameras, this is done with changing the focal length of the lens used):

![fov_01](./img/space/fov_01.jpg) [[shotkit]](https://shotkit.com/field-of-view/)
  
The second one is the **aspect ratio**. You almost always want to use the width of the element divided by the height, otherwise you'll get a distorted image.  
  
The next two attributes are the **near and far clipping plane**. What that means, is that objects further away from the camera than the value of **far** won't be rendered. Same applies to objects closer than the **near** value. This is mainly used for better performance.  

By defining these attributes, we constrain the rendered area to the *view frustum*, which is the space between the green and red planes in this image:

![frustum_01](./img/space/frustum_01.jpg)

[[5]](https://pbs.twimg.com/media/Di2Z3InU8AAd3bm.jpg)

### Renderer

Next up is the **renderer**. We will use the [WebGLRenderer](https://threejs.org/docs/?q=WebGLRenderer#api/en/renderers/WebGLRenderer). Three.js comes with a few other renderers, often used as fallbacks for users with older browsers or for those who don't have WebGL support for some reason.  

```js
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({canvas, antialias: true});
```

In the first line we are accessing with plain, old JavaScript the element in the DOM with the id `canvasThree`. This is the canvas element to which we want to render to. This canvas we pass as argument when creating an instance from the [WebGLRenderer](https://threejs.org/docs/?q=WebGLRenderer#api/en/renderers/WebGLRenderer) class.

We also need to **set a size** for the renderer. You can understand this as the "image size", we are rendering to. It is best to use the width and height of the area we want to fill - in this case, the width and height of the browser window.

```js
renderer.setSize( window.innerWidth, window.innerHeight);
```

To actually see a rendering, we have to activate the rendering (probably somewhere at the end of our file, once the scene is put together), with a scene and a camera:

```js
renderer.render(scene, camera);
```

Now we have a **scene**, a **camera**, and **renderer** and with that a fully functioning rendering pipeline. Let's put something into our scene.

## Coordinate System

Before we add any geometry, we have to take a quick look at the coordinate system. We need to clarify the coordinate system of every new environment that we use, as these differ from environment to environment. 
As we are now in 3D, next to x, and y we have to consider a third dimension, namely z. As default, the camera is looking down the -z axis:

![coordinates_01](./img/space/coordinates_01.png)  [[6]](https://threejs.org/manual/resources/scene-down.svg)

Let's start boring and add a cube to the scene.


## Creating 3D Elements

To create a cube (fear not, there are many other shapes available in three.js), we create an instance of the [`BoxGeometry`](https://threejs.org/docs/#api/en/geometries/BoxGeometry) class with its sizes as arguments:

**BoxGeometry(width : Float, height : Float, depth : Float)**

* width — Width; that is, the length of the edges parallel to the X axis. Optional; defaults to 1.
* height — Height; that is, the length of the edges parallel to the Y axis. Optional; defaults to 1.
* depth — Depth; that is, the length of the edges parallel to the Z axis. Optional; defaults to 1.

```js
const geometry = new THREE.BoxGeometry(0.5, 0.5, 0.5);
```

The above code only defines cube geometry. However, to render that cube, we also must create a material to make it visible (the [MeshNormalMaterial](https://threejs.org/docs/?q=MeshNormalMaterial#api/en/materials/MeshNormalMaterial) material is just an example here - it takes the colors from the orientation of the surfaces)


```js
const material = new THREE.MeshNormalMaterial();
```

and add both, geometry and material, to a mesh:

 ```js
const cube = new THREE.Mesh( geometry, material );
```

That is just how three.js wants it. Live with it. Hence, in total we have for creating a geometry, or in three.js lingo a *mesh*:

```js
const geometry = new THREE.BoxGeometry(0.5, 0.5, 0.5);
const material = new THREE.MeshNormalMaterial();
const cube = new THREE.Mesh( geometry, material );
```

### Material

Three.js comes with [several materials](https://threejs.org/manual/#en/materials). All materials can be filled with certain attributes to change the look. This can be color, roughness, as well as a texture. Here, e.g., are all attributes listed for the oldy but goody [MeshPhongMaterial](https://threejs.org/docs/#api/en/materials/MeshPhongMaterial). A Phong material mimics how real-world surfaces reflect light in a very limited but still useful fashion.

### Mesh

A mesh is an object that takes a **geometry**, and applies a **material** to it. 

![meshgeomat](./img/space/meshgeomat.png)


Then, we add the mesh to our **scene** with `scene.add()`

```js
scene.add(cube);
```

By default, when we call scene.add(), the object will be added to the coordinates (0,0,0). This is why we moved the camera back a bit earlier.



---
Our basic scene is now completed. 

Be aware that certain materials only appear, if you have a light in the scene. You can imagine the MeshNormalMaterial material is "self-illuminating", meaning it doesn't need a light to be visible. For the Phong material this is different. Let's change the material to the standard material:


```js
import * as THREE from 'three';


// SCENE
const scene = new THREE.Scene();

// CAMERA
const fov = 70;
const aspect = window.innerWidth / window.innerHeight;
const near = 0.1;
const far = 10;
const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);
camera.position.z = 1;

// RENDERER
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setSize( window.innerWidth, window.innerHeight);

// GEOMETRY
const geometry = new THREE.BoxGeometry( 0.5, 0.5, 0.5 );
const material = new THREE.MeshStandardMaterial({ color: 0x50ffc0 });

const cube = new THREE.Mesh( geometry, material );
cube.rotation.x = 100;
cube.rotation.y = 180;
scene.add(cube);

renderer.render(scene, camera);
```

Notice, how [MeshStandardMaterial](https://threejs.org/docs/#api/en/materials/MeshStandardMaterial) takes as argument an object with the key-value pair color - value.

## Colors

The standard method of specifying color in three.js is with a hexadecimal triplet in the format of `0x...`. There is also the [color class](https://threejs.org/docs/#api/en/math/Color.set) in three.js, which gives you many different options to work with color.

The above scene renders as follows:

![](img/space/black.png)

That is because the standard material reacts to light and to make it visible we need to add lights to the scene to be reflected.


## Lighting

There are a few different [lights](https://threejs.org/examples/?q=light#webgl_lights_hemisphere) like ambient light, directional light, point light, spot light. First, will use an white ambient light to illuminate the whole scene.

```js
// LIGHTING
// AMBIENT
const lightColor = 0xffffff;
const lightIntensity = 0.8;
const ambientLight = new THREE.AmbientLight(lightColor, lightIntensity);
scene.add(ambientLight);
```

Btw. in real life you would code it like this, no need to extra variables if you do not want to re-use those values:

```js
// LIGHTING
// AMBIENT
const ambientLight = new THREE.AmbientLight(0xffffff, 1);
scene.add(ambientLight);
```


Now our scene looks as follows:

![ambient_01](./img/space/ambient_01.png)


Also not too exciting. An ambient light simply makes the whole scene evenly brighter.

Let's also add a point light:

```js
// POINTLIGHT
const pointLight = new THREE.PointLight(0xffffff, 0.5);
pointLight.position.set(1, 2, 1);
scene.add(pointLight);
```

Decrease the intensity of the ambient light to have a reasonable sum of the two light intensities (e.g., 0.1 for ambient and 0.8 for the point light).

For a point light the  `pointLightHelper` is very useful. It is a frame around the light so we can see where it is positioned in our space. Sometimes this is extremely helpful when designing a scene. You might need to adjust your camera or zoom out to see the helper.

```js
const sphereSize = 1;
const pointLightHelper = new THREE.PointLightHelper(pointLight, sphereSize);
// add the point light helper to the scene
scene.add(pointLightHelper);
```

Now we actually can see the shape in 3D:

![cube_02](./img/space/cube_02.png)

Stunning 🤩

Wouldn't it be nice though, if we could navigate in the scene? For enabling any type of interaction or also, e.g., animation we are still a fundamental property missing in our scene: a render loop. As of now, we are rendering the scene exactly once. But we need a functionality such as the `draw` function in p5, which is called multiple times per second.

## The Render Loop

We can easily create a render loop similar to the `draw()`-loop in p5.js. For that we are using JavaScript's [`requestAnimationFrame`](https://developer.mozilla.org/en-US/docs/Web/API/window/requestAnimationFrame) function, which requests the browser to refresh its window. 

<!-- The frequency of calls to the callback function will generally match the display refresh rate. The most common refresh rate is 60hz, (60 cycles/frames per second), though 75hz, 120hz, and 144hz are also widely used. [[8]](https://developer.mozilla.org/en-US/docs/Web/API/window/requestAnimationFrame) You can also control the refresh rate but there is no need for us to do so. -->

This is the typical function to for creating an animation in a browser. `requestAnimationFrame` refreshes the current window and takes as argument another function that should be called from `requestAnimationFrame`. Such a function as an argument is a *callback* function.

```js
requestAnimationFrame(callback)
```

In this case the callback function is the function to call when it's time to update our animation or better our scene for the next repaint.


```js
function animate() {
    
    ...
}

requestAnimationFrame(animate);
```


*Wait, what? A function takes another function as argument??* Welcome to JavaScript, my friends! 

These type of functions are called higher order functions and they are part of the *functional programming* paradigm. With that they are not JavaScript specific but to my knowledge most prominently used in JavaScript. At a different time you will hear everything about those functions. For now, just accept the fact that functions are just objects that can be passed as argument to functions.

The above does not create a loop yet. We request a window refresh exactly once. But the callback function could be the function that also calls `requestAnimationFrame(animate);` - and with that we have our loop!


```js
// RENDER LOOP
function animate() {
    
    ...
    requestAnimationFrame(animate);
}

animate();
```

As we want to re-render our scene with each refresh window call, we add the rendering to this animation function:

```js
// RENDER LOOP
function animate() {
    
    renderer.render(scene, camera);
    requestAnimationFrame(animate);
}

animate();
```

This function is typically called animate even though in the above example it is more of a render function. We could also call it `draw` if our hearts are still with p5. Eventually, we will add animation behavior to the function that is why I introduce the name `animate` here already.

Now, that we have a render loop, we can also add interaction. Let's start with simple scene navigation.



## Orbit Control

[OrbitControls](https://threejs.org/docs/index.html#examples/en/controls/OrbitControls) enable a simple navigation setting that allows us to move around a target.

The Orbit Control functionality is not part of the main library but we need to load an additional module for it. three.js calls these *Addons*. Once again, for knowing [how to install an addon](https://threejs.org/docs/#manual/en/introduction/Installation) you must look into the installation guide of the library that you are using. There is no *just knowing it*.

```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Hello three.js!</title>

    <link rel="stylesheet" type="text/css" href="../css/style.css" />

    <script type="importmap">
        {
            "imports": {
                "three": "https://unpkg.com/three@0.158.0/build/three.module.js",
                "three/addons/": "https://unpkg.com/three@0.158.0/examples/jsm/"
            }
        }
    </script>
  </head>

  <body>
    <canvas id="canvasThree"></canvas>
    <script type="module" src="./scene.js"></script>
  </body>
</html>
```

The OrbitControls addon must also be imported explicitly in our JavaScript file. The export from the OrbitControls.js file is a *named export* and we can use that name to import exactly what we need:

```js
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
```

How should you know this? Well, read the three.js documentation, where it is explained to us how to import the class `OrbitControls`.
  
You could also save the import in an object in the same manner as we have done it with the three module:

```js
import * as ORBIT from 'three/addons/controls/OrbitControls.js';
```

With the code above, you would need to add `ORBIT.` to the orbit specific commands in the following.

In general, I recommend to go with the installation, and import recommendation from the official documentation unless you have a good reason (and the knowledge) to do it differently.

Now, we can add those controls to the scene with

**OrbitControls( object : Camera, domElement : HTMLDOMElement )**

* object: (required) The camera to be controlled. The camera must not be a child of another object, unless that object is the scene itself.
* domElement: The HTML element used for event listeners (*where to detect user input?*). 

This looks in our scene as followsL

```js
// CONTROLS FOR NAVIGATION
const controls = new OrbitControls(camera, canvas);
```
Remember, in `canvas` we have saved the value of `document.querySelector("#canvasThree");`. As we might not have saved the canvas element explicitly in a variable, we could also more generically use:


```js
// CONTROLS FOR NAVIGATION
const controls = new OrbitControls(camera, renderer.domElement);
```

For simple navigation this might already be enough. But Orbit Controls has properties such as [enableDamping](https://threejs.org/docs/index.html#examples/en/controls/OrbitControls.enableDamping) and [autoRotate](https://threejs.org/docs/index.html#examples/en/controls/OrbitControls.autoRotate), which need to be updated, which can be done within our render loop with `controls.update();`. Keep in mind that also after any manual changes to the camera's transform, `controls.update();` would need to be called.


```js
// RENDER LOOP
function animate() {
    
    controls.update();
    renderer.render(scene, camera);
    requestAnimationFrame(animate);
}

animate();
```

## A Bit Prettier

With the above knowledge, you should be able to look up in the documentation and understand the following scene.

```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Hello three.js!</title>

    <style>
        body { margin: 0; }
    </style>

    <!-- Three.js -->
    <script type="importmap">
        {
            "imports": {
                "three": "https://unpkg.com/three@0.158.0/build/three.module.js",
                "three/addons/": "https://unpkg.com/three@0.158.0/examples/jsm/"
            }
        }
    </script>

  </head>

  <body>
    <canvas id="canvasThree"></canvas>
    <script type="module" src="scene.js"></script>
  </body>
</html>

```

```js
//scene.js

import * as THREE from 'three';

// We want to use the "OrbitCamera" addon provided by three.JS
// We need to import it from the folder and give the imported object (the addon) a name: "OrbitControls"
// This information is given to us by the library
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';

// SCENE
const scene = new THREE.Scene();

// A fog is implemented to give distance to the scene and smoothly transition from the bottom plane to the background color
scene.background = new THREE.Color('#ffc2c2');
scene.fog = new THREE.FogExp2(scene.background, 0.02);

// CAMERA
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 22;

// RENDERER
const canvas = document.querySelector("#canvasThree");
const renderer = new THREE.WebGLRenderer({ canvas, alpha: true, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);


// We want light to cast a shadow, so we have to enable a shadowMap with certain properties in the render pipeline
renderer.shadowMap.enabled = true;
renderer.shadowMap.type = THREE.PCFSoftShadowMap;

document.body.appendChild(renderer.domElement);


// CONTROLS FOR NAVIGATION
// Here the camera is given to OrbitControls
const controls = new OrbitControls(camera, renderer.domElement);

// LIGHTING
// AMBIENT
const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);

// POINT LIGHT
const pointLight = new THREE.PointLight(0xfff4c9, 50);
pointLight.position.set(0, 4, 2);

// Enabling shadows for the pointlight
// Max and Min Distances are needed for the renderer
pointLight.castShadow = true;
pointLight.shadow.mapSize.width = 1024;
pointLight.shadow.mapSize.height = 1024;
pointLight.shadow.camera.near = 1;
pointLight.shadow.camera.far = 600;

// The radius is the "smoothness" of the light's shadow
pointLight.shadow.radius = 10;
scene.add(pointLight);


// A pointLightHelper draws a bounding box around the light to show us its position in the scene
const pointLightHelper = new THREE.PointLightHelper(pointLight, 1);
scene.add(pointLightHelper);

// GEOMETRY
// PLANE
const planeGeometry = new THREE.PlaneGeometry(300, 300);
const planeMaterial = new THREE.MeshStandardMaterial({ color: '#b3005a' });
const planeMesh = new THREE.Mesh(planeGeometry, planeMaterial);
planeMesh.rotation.x = -Math.PI / 2;
planeMesh.position.y = -10;
// Enable shadows on the plane
planeMesh.receiveShadow = true;
scene.add(planeMesh);

// ICOSAHEDRON
const icosaGeo = new THREE.IcosahedronGeometry(2.4, 0); //radius, detail
const icosaMat = new THREE.MeshStandardMaterial({ color: 0xff0080});
const icosa = new THREE.Mesh(icosaGeo, icosaMat);
// Make the icosa cast shadows
icosa.castShadow = true;
scene.add(icosa);

// ICOSAHEDRON 2
const icosaWireGeo = new THREE.IcosahedronGeometry(3.0, 0); //radius, detail
const icosaWireMat = new THREE.MeshStandardMaterial({ color: 0xffab00, wireframe: true });
const icosaWire = new THREE.Mesh(icosaWireGeo, icosaWireMat);
scene.add(icosaWire);

// CUBECIRCLE
const nCubes = 6;
const radius = 10;
const cubeSize = 5;
let angle = 0;
const step = (2 * Math.PI) / nCubes;
for(let i = 0; i < nCubes; i++) {
    const x = radius * Math.cos(angle);
    const z = radius * Math.sin(angle);
    const y = -10;
    const cubeGeometry = new THREE.BoxGeometry(cubeSize, cubeSize, cubeSize);
    const cubeMaterial = new THREE.MeshStandardMaterial({ color: 0xff8000, roughness:0.3, metalness: 0.5});
    const cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
    
    // Make the cube cast shadows
    cube.receiveShadow = true;
    // Enable shadows on the cube
    cube.castShadow = true;
    cube.position.set(x,y,z);
    cube.lookAt(0,0,0);
    scene.add(cube);
    angle += step;
}

// ANIMATE/RENDER like draw() in p5
function animate() {
    requestAnimationFrame(animate);

    // Offset the elements over time

    icosa.rotation.x += 0.004;
    icosa.rotation.y += 0.007;
    icosaWire.rotation.x += 0.008;
    icosaWire.rotation.z += 0.005;


    const t = Date.now() / 3000;
    // move light in circle around center
    // change light height with sine curve
    const r = 3.0;
    const lx = r * Math.cos(t);
    const lz = r * Math.sin(t);
    pointLight.position.set(lx, pointLight.position.y, lz);

    renderer.render(scene, camera);
}

animate();
```

![scene_advanced](./img/space/scene_advanced.png)



## Further Resources

### [three.js documentation](https://threejs.org/docs/)

The official documentation is of course a good place to start looking for help. I consider the documentation well-made.

### [three.js examples](https://threejs.org/examples/)

The three.js example site is a great start when wondering how to add further functionality. If you find an example you would like adapt in some way in your project, you can take a look at the [three.js GitHub](https://github.com/mrdoob/three.js/) via the button on the bottom right of the scene. When you want to re-implement something from an example, make sure that you have made the same imports for the needed addons and such.



---

## References

[[1] WebGL definition](https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API)  
[[2] Github Three.js](https://github.com/mrdoob/three.js/)  
[[3] Scene Graph](https://miro.medium.com/max/701/1*Bkk14XZa94WTue7F7DrhCA.png)  
[[4] FOV Image](https://cammy-marketing.s3.amazonaws.com/2017/01/1485185693/field-of-view-camera-smartphone-security-camera.png)  
[[5] Clipping Plane](https://pbs.twimg.com/media/Di2Z3InU8AAd3bm.jpg)  
[[6] Coordinate System](https://threejs.org/manual/resources/scene-down.svg)  
[[7] three.js - Installation](https://threejs.org/docs/#manual/en/introduction/Installation)  
[[8] mdn web docs - Window: requestAnimationFrame() method](https://developer.mozilla.org/en-US/docs/Web/API/window/requestAnimationFrame)

---

The End

💻 💫 🔺
