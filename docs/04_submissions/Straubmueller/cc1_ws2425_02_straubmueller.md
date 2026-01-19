---
layout: default
title: Homework
nav_exclude: true
---

# Creative Coding I

Prof. Dr. Lena Gieseke \| l.gieseke@filmuniversitaet.de \| Film University Babelsberg KONRAD WOLF

# Session 02 - Instruction (10 points)

Please complete this session by January 21st. Since we did not cover local server setup yet, you can stop after the Completing the session should take < 5h.

In this session we are going to think about the topic of _instructions_ and what the different forms in which instructions can be given. In terms of tech this session is about continuing programming with p5 and getting some coding done!

- [Creative Coding I](#creative-coding-i)
- [Session 02 - Instruction (10 points)](#session-02---instruction-10-points) \* [Tools and Environments](#tools-and-environments)
  - [Instructions](#instructions)
    - [Task 02.01 - _Coding_](#task-0201---coding)
    - [Task 02.02 - _Coding_](#task-0202---coding)
    - [Task 02.03 - _Algorithmic Thinking_](#task-0203---algorithmic-thinking)
    - [Task 02.04 - _Creative Instructions_](#task-0204---creative-instructions)
  - [The Web](#the-web)
    - [Task 02.05 - _Working With a Local Server_](#task-0205---working-with-a-local-server)
  - [Learnings](#learnings)

### Tools and Environments

Are there any languages, tools or environments for creative coding that you know of, that you can recommend, and which are not included in the script? _If not, you can skip this question._

_Submission_: 

- FFglitch

## Instructions

Submit a text-based program and its result for each of the following instruction. Try to include into the programming some algorithmic thinking, meaning a structured approach.

_Note_: You are free to choose any programming language, environment, library, etc. for this task, but it must be text-based programming. If you are a beginner, I highly recommend that you stick with p5.

_Submission_: Submit a link to your online sketch within the p5 editor, and link in your markdown submission file at least one result image or video of your work. If you do not use the online editor, submit all source files and resources that I need to run your sketch.

### Task 02.01 - _Coding_

> Circles!

_Submission_:
-  https://editor.p5js.org/an0malie_/sketches/iCmEcrRRt
- [Click here for the video](https://owncloud.gwdg.de/index.php/s/0XAaCcFy4vcuF2I)
- .\img\Task 02.01 - Coding_Circles

### Task 02.02 - _Coding_

> Happiness.

_Submission_:

The goal of my project was to convert an image that evokes happiness in me into ASCII artwork. Initially, I wanted to use characters that represent emotive symbols, such as hearts or smiling faces. However, after several attempts with different character sizes and images, I realized that the symbols were too uniform, resulting in insufficient contrast to make the image clearly recognizable. For this reason, I decided to use normal characters instead. The original images of Nugget the cat and the results can be found in the “img” folder.

-  https://editor.p5js.org/an0malie_/sketches/fgDM4_BNt
- .\img\Task 02.01 - Coding_Happiness...

<!-- > When I see you, it makes me happy. -->

### Task 02.03 - _Algorithmic Thinking_

Briefly reflect on how you implemented your creative idea. Did you apply algorithmic thinking and if so, how?

_Submission_: 

#### Circles
- The visual elements  are created through mathematical rules
- A loop generates multiple lines, based on a single rule
- Time based transformation -> variables evolve over time

#### Happiness
Input → Process → Output structure

- Input: a raster image
- Process: pixel analysis, brightness calculation, value mapping
- Output: a text-based visual representation

Brightness values are mapped to a fixed character set. Consistent rules determine the visual outcome. Loops go through every pixel, applying the same logic repeatedly.


### Task 02.04 - _Creative Instructions_

Write instructions that are in themselves a creative output.

_Hint:_ This is not about instructions for a creative output but about thinking about the instructions themselves and how to shape them creatively.

_Submission_: 

#### Load image

- Preload the uploaded image and make the pixel accessible

#### Reduce image

- Give the image a width and height resolution and resize the image to reduce the overall pixel

#### Process each pixel

- Read the x and y position of every pixel once the algorithm is executed

#### Calculate brightness 

- Read the RGB value of every pixel and compute the brightness value for each. The output should be an integer

#### Map brightness to character

- Map each brightness value to one specific ASCII character of a given set

#### Position character
- When a character is drawn, it must appear at the calculated grid position


#### Render grid

- Render the processed pixel as a text-based character as a visible image


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

_Submission_: 

- Deepened understanding of mapping functions and connecting multiple parameters
- Strengthened understanding of what belongs in draw(), in particular how the line “tail” is created -> controlled not by the object itself but by the background
- Everything that is to be looped also belongs in the loop function

- Stronger understanding of how pixels are processed and how their values can be used for other purposes.
- Uploading and the preload function within the online editor

My personal challenge was to test new styles, try out animated functions, and not shy away from mathematical functions. Processing pixels and their values also introduced me to new workflows that first had to be understood.


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
