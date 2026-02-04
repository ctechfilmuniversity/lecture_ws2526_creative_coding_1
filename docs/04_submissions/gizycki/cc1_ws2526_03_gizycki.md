---
layout: default
title: Homework
nav_exclude: true
---

# Session 03 - Space (10 points)
> Bonita von Gizycki | bonita.gizycki@filmuniversitaet.de |
> Film University Babelsberg KONRAD WOLF


## Task 03.03 - First Three.js Scene



🔗 **Live Demo:**  [Dispersion Bubbles](https://boxnixta.github.io/threejs-kusama-scene-CC1-03.03/)

✏️ **CodePen:**  [Everything at one place](https://codepen.io/box-nixta/pen/zxBaPOv)

💻 **Source Code:**  [here](https://github.com/Boxnixta/threejs-kusama-scene-CC1-03.03.git).

📼 **Visual Result:** the live version shows more detail and the interaction of course

 <p align="center">
  <img src="gif/LowRes-0303.gif" alt="Bubbles in a Room" width="60%">
  <br>
  <p align="center">
  <img src="img/03-bubbles1.png" width="32%">
  <img src="img/03-bubbles2.png" width="32%">
</p>
  <em>Klick and scroll do move freely through the scene and enjoy the glass bubbles.</em>
</p>

Description: This scene is an homage to the work of Yayoi Kusama. It combines abstract geometry with physically based materials (PBR) to create an immersive, sculptural environment.

## Technical Highlights:

Procedural Environment: The space consists of an inverted sphere with a procedurally generated canvas texture that utilizes digital noise and dithering.

Advanced Materiality: MeshPhysicalMaterial is used to simulate glass with dispersion (refraction) and frosted effects.

Post-Processing: An EffectComposer with UnrealBloomPass is implemented to give the emissive elements a physical glow.

Mathematical Alignment: The dots (cylinders) were precisely positioned on the curved surface of the spheres using normal vectors and quaternions.

<p align="center">
  <img src="img/03-dispersion.png" width="32%">

</p>


## Learnings & Challenges

* **Technical Focus:** My focus was on simulating realistic glass. I worked extensively with **dispersion**, **IOR (refractive index)**, and **frosted materials** to give the spheres physical depth.

* **Effects:** By using `UnrealBloomPass` in post-processing, the inner points glow through the glass, giving the scene a sculptural lighting effect.

* **AI Collaboration:** I used AI to understand all the complex mathematical concepts (such as the alignment of the cylinders using quaternions). Through iterative debugging, I learned how to build the Three.js render stack modularly and fix errors in the build process. There were often moments when I had difficulty finding small errors in the code, and AI was very helpful in these situations as well.


### How to run locally
1. Clone the repository.
2. Run `npm install`.
3. Run `npm run dev`.