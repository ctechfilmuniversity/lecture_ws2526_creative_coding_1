---
layout: default
title: Homework
nav_exclude: true
---

# Creative Coding I

Jonathan Ho \| jonathan.g.ho@filmuniversitaet.de
Prof. Dr. Lena Gieseke \| l.gieseke@filmuniversitaet.de \| Film University Babelsberg KONRAD WOLF

# Session 04 - Asynchronism / Space Again (15 points)

Please complete this session by February 11th. Completing the session should take < 6h.

- [Creative Coding I](#creative-coding-i)
- [Session 04 - Asynchronism / Space Again (15 points)](#session-04---asynchronism--space-again-15-points)
  - [JavaScript Functions \& Asynchronism](#javascript-functions--asynchronism)
    - [Task 04.01](#task-0401)
    - [Task 04.02 - Coding Practices](#task-0402---coding-practices)
  - [Three.js](#threejs)
    - [Task 04.03 - Your Own Scene](#task-0403---your-own-scene)
  - [Learnings](#learnings)

In this session we are dealing with the topic of _asynchronism_, where we encounter it in every day life and what it means for us as humans. In terms of tech, this session introduces you to some web-specific JavaScript functionality and syntax, which we will need in the upcoming sessions.

## JavaScript Functions & Asynchronism

### Task 04.01

Re-cap the sections in the script regarding higher order functions and their different syntax formats. As a beginner you can skip the more advanced sections that we haven't covered in class:

- [Higher Order Functions](../../02_scripts/cc1_ws2526_04_javascript_script.md#higher-order-functions)
- [Anonymous Functions](../../02_scripts/cc1_ws2526_04_javascript_script.md#anonymous-functions)
- [Arrow Functions](../../02_scripts/cc1_ws2526_04_javascript_script.md#arrow-functions)
- [Asynchronism](../../02_scripts/cc1_ws2526_04_javascript_script.md#asynchronism)

At the very least make sure that you understand the underlying functionality and that you will be able to work with the syntax when given to you, e.g., from a framework.

If you are more advanced, make sure that your understand Closures, Promises and Async and Await.

_Submission:_ -

### Task 04.02 - Coding Practices

Reflect on your usage of resources and Machine Learning tools for coding.

- What have you used and how has it served you?

*Answer: I use ML tools as follows:*
1. Explaining my idea and receiving the general structure
2. Writing the code myself and trying to understand the sections and their order
3. Asking questions if I don't understand a section
4. Experimenting and modifying the code to better grasp what each section does and achieve individual results
5. Adding more functionalities

*Perplexity:* I used Perplexity as my main ML tool but quickly realized it didn't really understand my issues and couldn't help.

*Claude:* Claude enabled my concepts but often used unfamiliar libraries or languages in p5 editor, requiring me to argue for fitting results.

*ChatGPT:* Despite ChatGPT's annoying phrasing and text spacing, it worked best for coding. It understands my expectations and explains things in a way I can follow.

- Do you actually understand the code an ML tool has given to you (in case you have used any)?

*Answer:* Most of the time, I understand the general functionality but don't give enough thought to the mathematical equations, since they bring me the least joy.
- Would you be able to re-create it without any help?

*Answer:* Without ANY help, no. But I might achieve the same or a similar result with the p5/three.js documentations, user forums, and much more time.

- What can you recommend?

*Answer:* Working with ML tools might be sensible since it is also a skill and it saves time but we should always understand the code ourselves.

- How do you want to proceed?

*Answer:* I want to explore more example projects to understand their structure and code implementation, but I'll still use ML tools for bug fixing, analysis, and explanations.



## Three.js

### Task 04.03 - Your Own Scene

Create a Three.js scene up to your liking. There are no constraints for what the scene should be. The result should be polished and will be graded on concept, form / design and implementation quality.

You are required to use additional functionality that you haven't yet used last week. Check the [three.js manual](https://threejs.org/docs/index.html#manual/en/introduction/Creating-a-scene) or [the examples](https://threejs.org/examples/#webgl_animation_keyframes) for inspiration.

*Submission*: ![Submission-04](<img/260208_CC1_Session04_Task 04-03_.png>)

- [Click here for the video](https://owncloud.gwdg.de/index.php/s/8L9iz2bIcHPqsqD)
- [Click here for the source file](https://owncloud.gwdg.de/index.php/s/QsA3ovjD7L4rY3p)

## Learnings



Please summarize your personal learnings. What was challenging for you in this session? How did you challenge yourself?

_Submission_: 
#### What I learned


- HDRIs and HemisphereLights do not cast shadows, and a shadow-casting light like a DirectionalLight is required.

- Lights must explicitly have castShadow enabled, or no shadows will appear.

- Increasing light intensity does not improve shadow quality and can cause visual artifacts.

- How to load a glTF format with all its textures.

- Exporting gltf with animations and manipulating them with lil gui

- OrbitControls override camera rotation every frame

- HDRIs as backgrounds

- Animations require AnimationMixer and a Clock (delta must be defined).

#### What I struggled with

I struggled, especially at the beginning, with loading the GLTF file and figuring out how to manipulate the animation. I was also confused by the missing shadows, and it took some time to add all the correct parameters.

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

**Happy Building!**
