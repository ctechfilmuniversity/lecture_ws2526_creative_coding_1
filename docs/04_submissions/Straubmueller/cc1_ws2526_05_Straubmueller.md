---
layout: default
title: Homework
nav_exclude: true
---

# Creative Coding I

Jonathan Ho \| jonathan.g.ho@filmuniversitaet.de  
Prof. Dr. Lena Gieseke \| l.gieseke@filmuniversitaet.de \| Film University Babelsberg KONRAD WOLF

# Session 05 - Systems (55 points)

Please complete this session by February 28th. Completing the session should take < 40h.

- [Creative Coding I](#creative-coding-i)
- [Session 05 - Systems (55 points)](#session-05---systems-55-points)
  - [Task 05.01 - The Final Project](#task-0501---the-final-project)
  - [Task 05.02 - Feedback](#task-0502---feedback)
  - [Learnings](#learnings)

Our last topic is _systems_. We are done with the class and hopefully from here on you have enough coding competencies and algorithmic thinking developed that you can build more complex systems - by using code, nodes, hardware... Also, hopefully you, yourself, can further evolve with what you have learned from this class (🐛 -> 🦋).

## Task 05.01 - The Final Project

The final project is an individually chosen project.

_Maybe a portfolio page?_ 👑

_Maybe something useless?_ 😁

You can do whatever you want but your project must make use of text-based programming. It can also be an experiment, part of a larger project, work in progress, or a learning path. Ideally it should be something online, but this is not a hard requirement. You don't need to submit a project plan beforehand. However, I am open to discuss your plan with me in advance.

The time dedicated to the final project is ~40h.

The official work period for the final assignment is Feb. 1st - Feb. 28th. The deadline for the final project is February, 28th.

- The deadline for the final project is strict and for a late submission, I reduce **15% of the total points**.
- If you are sick within the official work period, you can get a deadline extension based on a doctor's note ("Attest"). You must hand in the Attest within 3 days.

As submission, I require

- a description
- the source code
- a link to the build / online deployment or such, and
- at least one representative image.

Submit your code in your assignment folder as assignment `05` or add a link there to where to find the code.

 *Submission*: 

 > Description:
 This interactive project features a reactive 3D cat character that hates to be touched. It was sculpted in Blender and animated with React Three Fiber. The cat responds dynamically to the user’s cursor: as the mouse approaches, it squashes downwards while its facial expression and pupils subtly morph to convey an angry emotion. If the user pushes the interaction for too long, the cat “reacts” by triggering a timed response that reveals an additional on-screen message.
The visual style combines baked lighting from Blender with a real-time web-based rendering workflow, resulting in a stylized and performant scene. 

 ![First concept](<img/260223_CC1_Session05_Task 05-01_firstConcept.png>)

 ![Sculpting](<img/260223_CC1_Session05_Task 05-01_modelSculpting.png>)
 
![React light tests](<img/260223_CC1_Session05_Task 05-01_reactLightTests.png>)

![Scene optimization](<img/260223_CC1_Session05_Task 05-01_sceneOptimization.png>)

![Final Submission 01](<img/260223_CC1_Session05_Task 05-01_finalSubmission-01.png>)

![Final Submission 01](<img/260223_CC1_Session05_Task 05-01_finalSubmission-02.png>)

![Final Submission 01](<img/260223_CC1_Session05_Task 05-01_finalSubmission-03.png>)

![Final Submission 01](<img/260223_CC1_Session05_Task 05-01_finalSubmission-04.png>)

- [Click here for the video/images](https://owncloud.gwdg.de/index.php/s/UFKJ6D2E8mikHPV)
- [Click here for the source file](https://owncloud.gwdg.de/index.php/s/j6T9kwDJ1EvYFOY)

- [Click here to view the project](https://do-not-touch.vercel.app/)

## Task 05.02 - Feedback

- How would you rate the difficulty of this class from 1 (far too easy) to 5 (far too difficult)? 
> 3


- How would you rate the amount of work you had to put into this class so far from 1 (no work at all) to 5 (far too much work)?
> 4

- How much did you learn in the class and expanded your skill set, from 1 (I am the same) to 5 (learned a lot)?
> 4

- How much did you enjoy working with p5, from 1 (hate it) to 5 (love it)?
> 4

- How useful do you consider p5 for you, from 1 (don't need it) to 5 (will use it all the time)?
> 2

- How much did you enjoy working with tree.js, from 1 (hate it) to 5 (love it)?
> 3

- How useful do you consider tree.js for you, from 1 (don't need it) to 5 (will use it all the time)?
> 4

- How much did you enjoy working with React, from 1 (hate it) to 5 (love it)?
> 2

- How useful do you consider React for you, from 1 (don't need it) to 5 (will use it all the time)?
> 3

- How much did you enjoy working on the exercise tasks, from 1 (hated it) to 5 (loved it)?
> 3

- What do you think about the context expansions, e.g., the brief general discussions of certain topics?
> I truly enjoyed the general discussions and the time that was taken for exploring different topics to broaden my horizon of creative coding.

- Which one was your favorite topic, which one your least favorite?
> favorite: three js -> useful for portfolio and general 3D context

> least favorite: react -> too less time to explain and understand the topic

- Was there a topic missing and if so which one?
> no

- Please feel free to add any feedback you want to give!

> - Nice, supportive, and fun atmosphere
> - No fear of asking questions
> - Help provided until everyone understood
> - Good overview of the creative coding landscape

> All in all, a great course — a big thank you to Jonathan!

## Learnings

Please summarize your personal learnings of the final project and in regard to the whole course. What was challenging for you? How did you challenge yourself?

_Submission_: 

I probably set the bar a bit too high since my idea combined 3D modeling with web interaction — overall, it turned out to be too much work. Creating the basic 3D scene took a day, which was fine, but the web interaction part became time‑consuming and caused many issues. I ended up relying on ML tools for troubleshooting, which unfortunately disrupted my learning experience of code structure and syntax.
It also took some trial and error to decide whether to rig the cat or use shape keys for animation. Initially, I planned a wider range of movements so the cat could dodge in different directions, but I soon realized that would exceed the project’s scope. In the final version, the cat only performs a simple squish animation.
Another challenging part was managing lights and materials. At first, I exported the glb file and tried lighting the scene in React. HDRs gave the best‑looking, though still unsatisfactory, results — and they made the scene lag. I eventually decided to bake the textures onto the model. Since it was my first time working with texture baking, it took a while to find the right workflow and color space setup for use in Three.js.

Things I learned:
- How to pass callbacks from child to parent
- Managing UI state with useState
- Using useRef 
- Difference between: MeshBasicMaterial & MeshStandardMaterial
- Why objects render black without lights
- How tone mapping affects appearance
- Why baking removes real-time lighting influence
- Matching Blender viewport look to Three.js renderer
- Converting mouse to world space
- Calculating proximity radius
- Squash & stretch scaling logic
- Pupil movement based on mouse position
- Pupil scaling based on morph intensity
- Creating threshold-based timed triggers 
- Creating modal popups in React

Things I struggled with
- Tone mapping mismatch between Blender and Three.js
- Why highlights disappeared after baking
- Environment light intensity not reacting
- Shadows not appearing or looking blocky
- Passing callback props correctly
- Interaction hotspot shifting when camera changed
- World space conversion confusion
- Hook-based timer for threshold trigger

---

Bye-bye

![](https://media.giphy.com/media/G5h04AkAvAHcs/giphy.gif)

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

**Happy Evolving!**
