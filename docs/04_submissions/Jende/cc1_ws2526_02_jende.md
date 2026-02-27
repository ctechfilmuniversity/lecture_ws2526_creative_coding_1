
```md
---
layout: default
title: Homework
nav_exclude: true
---
```

### Task 02.01 - _Coding_

Circles!

> Access Project Files:
> https://github.com/MariaJende/cc1_ws2526_02_jende_01
> 
>View Project:
> https://cc102jende01.vercel.app/
> 
> View Video of Project:
> https://owncloud.gwdg.de/index.php/s/qstVvOtOnH14lWe
>
> Inspired by https://medium.com/@banyapon/creating-an-engaging-rhythm-circle-with-creative-coding-in-three-js-2eeac9df1fe2 by Banyapon Poolsawas

![](https://github.com/MariaJende/LinkedFiles/blob/main/cc1_ws2526_02_jende_01.gif)

### Task 02.02 - _Coding_

Happiness.

> Access Project Files:
> https://github.com/MariaJende/cc1_ws2526_02_jende_02
> 
>View Project:
> https://mariajende.github.io/cc1_ws2526_02_jende_02/
>
> View Video of Project:
> https://owncloud.gwdg.de/index.php/s/jCIxDsnhQ3jTxzP

### Task 02.03 - _Algorithmic Thinking_

Briefly reflect on how you implemented your creative idea. Did you apply algorithmic thinking and if so, how?

_Submission_:

> I actually used alghoritmic thinking several times. Therefore I will only show one per task.
>
> **02.01_Circles**
> ```js
> const arcCount = 30;
> for (let i = 0; i < arcCount; i++)
> ```
>I created a parameter for the arc count (arc count = n, in this case n = 30) which then influences the amount of loops that generate the arcs. Therefore the arcs are not drawn directly by me, they are generated and bound by flexible values.
>  
> **02.02_Happiness**
> ```js
> const positions = new Float32Array(COUNT * 3);
> const velocities = new Float32Array(COUNT * 3);
> 
> for (let i = 0; i < COUNT * 3; i++) {
>   positions[i] = (Math.random() - 0.5) * 200;
>   velocities[i] = (Math.random() - 0.5) * 300;
> }
> ```
> I see this as algorithmic thinking because the code describes a clear process rather than fixed results.  
> Each particle is treated as an entity with a state consisting of position (x, y, z = 3 values) and velocity. Instead of assigning explicit values to those two parameters, the algorithm creates them using controlled randomness, distributing particles across space and giving them high initial velocities.  

### Task 02.04 - _Creative Instructions_

Write instructions that are in themselves a creative output.

_Hint:_ This is not about instructions for a creative output but about thinking about the instructions themselves and how to shape them creatively.

_Submission_:  
> Sit down.  
> If it’s early morning, think about yesterday; from noon onward, think about today.  
> Recall a moment when you felt joy, relaxation, and/or gratitude yesterday/today.  
> Analyse, why it made you feel one, two or all of these feelings.
> Keep those parameters in mind and repeat them tomorrow if it’s noon or later, or today if it’s early morning.  
> After 24 hours, sit down again and repeat.

## Learnings

Please summarize your personal learnings. What was challenging for you in this session? How did you challenge yourself?

_Submission_:

> My biggest learning in this session was starting to work with three.js, which I had never used before. At the beginning, I felt overwhelmed because it wasn’t as convenient as the online p5 editor.  
> However, I worked through some basic tutorials, which really helped. Trying to understand every line of code (how it influences other parts of the program, how it functions) is quite exhausting, but it obviously helped me with debugging.
