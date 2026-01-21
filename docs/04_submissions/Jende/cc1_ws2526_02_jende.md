
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
> https://mariajende.github.io/cc1_ws2526_02_jende_01/
> >
> View Video of Project:
> https://owncloud.gwdg.de/index.php/f/3812310145
>
> Inspired by https://medium.com/@banyapon/creating-an-engaging-rhythm-circle-with-creative-coding-in-three-js-2eeac9df1fe2 by Banyapon Poolsawas

### Task 02.02 - _Coding_

Happiness.

> Access Project Files:
> https://github.com/MariaJende/cc1_ws2526_02_jende_02
> 
>View Project:
> https://mariajende.github.io/cc1_ws2526_02_jende_02/
>
> View Video of Project:
> https://owncloud.gwdg.de/index.php/f/3812242744

### Task 02.03 - _Algorithmic Thinking_

Briefly reflect on how you implemented your creative idea. Did you apply algorithmic thinking and if so, how?

_Submission_:

> I actually used alghoritmic thinking several times. Therefore I will only show one per task.
>
> **02.01_Circles**
> 
> **02.02_Happiness**
> 
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

_Submission_: Text and/or an audiovisual representation in your markdown submission file.

---

### We will get to [Script 06 - The Web](../../02_scripts/cc1_ws2425_06_web_script.md) at a later class, so you're not expected to know / do this part until after the break.

---

## The Web

### Task 02.05 - _Working With a Local Server_

Create a setup with a local webserver and be able to work with, e.g., p5, locally.

A possible setup could simply be using a local webserver with [the VSCode extension](../../02_scripts/cc1_ws2425_02_setup_script.md#webservers).

If needed, re-cap the topic by reading [Example: A Local Setup For p5.js](../../02_scripts/cc1_ws2425_02_setup_script.md#example-a-local-setup-for-p5js).

Also, it is time to getting used to doing simple steps with the terminal (😱). For that, you can work through the chapter [Terminal / Console](..//02_scripts/cc1_ws2425_02_setup_script.md#terminal--console) in the setup script.

No need to submit anything, but I expect that you are ready to work with a local webserver and the terminal from next week on.

_Submission_: -

## Learnings

Please summarize your personal learnings. What was challenging for you in this session? How did you challenge yourself?

_Submission_: Text or bullet points in your markdown submission file.

---

Write and link all task results in a copy of this file. Submit your copy as `cc1_ws2425_XX_lastname.md` in your assignments' folder.

Please add the following header at the beginning of your Markdown file:

```md
---
layout: default
title: Homework
nav_exclude: true
---
```

---

**Happy Instructing!**
