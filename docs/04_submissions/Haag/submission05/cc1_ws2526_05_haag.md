layout: default
title: Session
nav_exclude: true
---

# Session 05 - Systems (55 points)

## Task 05.01 - The Final Project

🔗 **Website:**  [Smombies&Zombies](https://smombies-vr.vercel.app/)

💻 **Code:** Look up [here](https://github.com/haaglynnxctech2025/SmombiesVR/blob/main/index.html)

📸 
![Screenshots](https://raw.githubusercontent.com/haaglynnxctech2025/SmombiesVR/main/img/Webview.png)


*Website Design — Smombies & Zombies*

First of all I want to say, that I am still working on my portfolio website that is a much larger project than this one pager. It's still not completely finished so I didn't want to deploy it yet. Time was tight, so I used this opportunity to make this one pager really refined and also I wanted to try making a convential website, not one that uses frameworks like three.js. This was a one page web project I could see the finished result come closer, more than the refined result of my portfolio website.

I built this website as a single-page HTML/CSS/JavaScript file deployed via Vercel, directly from the GitHub repository. No framework, no build tools — just HTML with embedded styles and scripts. This was easier for me than to switch, and I liked the workflow. Next time I'd still do it differently because when I adapt and make the page longer it will probably be ore convenient. I'm not sure but i will try. I used this technique a lot where you can search for a word by hitting "ctrl+H" and then hit "replace all".

*Visual Direction*

The design follows the same aesthetic as the game its based on: a little dark but playful, underground Berlin. 
The colour palette uses three accent colours pulled directly from the game's scenes. I replaced the custom cursor for the default browser cursor — a small dot with a trailing ring, both following the mouse with different easing. This was inspired by the roundness of the street/Ubahn signs in the illustrative background image.

*Typography*

The font pairing was chosen for contrast and character. Bebas Neue is used for all display headings — it has an aggressive, blocky quality that fits the comic underground aesthetic. Space Mono is used for labels, tags, and UI text — it reads like code or a terminal, which suits the techy/digital theme. DM Sans handles body copy for readability. All three are loaded from Google Fonts.

*Layout and Interactions*

The hero section uses a full-viewport image with a CSS gradient fade to black — the image bleeds into the dark background so there is no hard edge. The title is set at a slight rotation using transform: rotate(-5deg) to give it energy and break the grid.
I wasn't sure about this decision until the end but I thought it fits the look in the end.
I wanted the "VS." to flicker like a UBahn neon light — So I used flickers using a CSS keyframe animation. And it glows in purple using layered text-shadow, mimicking a neon sign. I like this a lot but it was hard to adapt the right glow amount.

The music player in the bottom right corner is a fixed-position ambient audio toggle with animated equaliser bars.

I used Scroll-triggered reveals with IntersectionObserver — sections fade up as they enter the viewport. The battery bar in the hero I animated through a full drain cycle on loop, going from green to yellow to red, referencing the core game mechanic directly.


Audio used: [Soundtrack](https://github.com/haaglynnxctech2025/SmombiesVR/tree/main/audio)
Images used: [Images] (https://github.com/haaglynnxctech2025/SmombiesVR/tree/main/img)

## Task 05.02 - Feedback

- **How would you rate the difficulty of this class from 1 (far too easy) to 5 (far too difficult)?**  
For me it was 3.5, I was challenged a lot but the lessons were really helpful, and I liked how easy it felt to ask questions, when I didn't understand the context or anything else. So I had a lot of fun learning, and I know there is much more to learn but I feel like it was very good entry level to get more into web developement. I can't wait to explore it more in the future.

- **How would you rate the amount of work you had to put into this class so far from 1 (no work at all) to 5 (far too much work)?**  
Maybe a 4. I had a lot other stuff on my plate so it just felt hard to focus on getting deeply into understanding all the code and how it all connects. But it's also very ambitious these days for a beginner like me to understand everything when things are still changing and someone can achieve an dlearn alot also with the help of artificial intelligence. At the end of the day I feel like it's important to achieve the results you were aiming for, especially as a Designer/3D artist.

- **How much did you learn in the class and expand your skill set, from 1 (I am the same) to 5 (learned a lot)?**  
5! I didn’t know anything about three.js/P5.js or had written any code before. So it was all very new and I feel like I understand a lot more than I could have ever achieved just learning it by myself or with tutorials.

- **How much did you enjoy working with p5, from 1 (hate it) to 5 (love it)?**  
5  

- **How useful do you consider p5 for you, from 1 (don't need it) to 5 (will use it all the time)?**  
3

- **How much did you enjoy working with three.js, from 1 (hate it) to 5 (love it)?**  
5  

- **How useful do you consider three.js for you, from 1 (don't need it) to 5 (will use it all the time)?**  
4 

- **How much did you enjoy working with React, from 1 (hate it) to 5 (love it)?**  
I think I like three.js more because it feels more experimental, but I really want to get into using React more in the future. 

- **How useful do you consider React for you, from 1 (don't need it) to 5 (will use it all the time)?**  
I think it will be really useful to me in the future so 4. But it depends on if I have enough practice to actually integrate it into my workflow. 

- **How much did you enjoy working on the exercise tasks, from 1 (hated it) to 5 (loved it)?**  
4.5 

- **What do you think about the context expansions, e.g., the brief general discussions of certain topics?**  
I liked them a lot, they smoothly embedded the context on creative coding and I feel like we could have discussed even further, also about using AI and vibe coding, but then we would have hardly ever stopped LOL.

- **Which one was your favorite topic, which one your least favorite?**  
Ever part was kind of fun, but my least favorite part was probably the “” algorithmic thinking" just because I felt like at that point i didn't know enough to actually discuss this topic. My favorite part was the one on Three.js/ React and talking about different examples/ how to achieve certain designs.

- **Was there a topic missing and if so which one?**  
Maybe we could have talked more about using LLMs in creative coding tasks and what the spectrum of using them to experiment with coding could have been. 

- **Please feel free to add any feedback you want to give!**  
- I liked how it was all very free and that we could come with anything. But maybe for the last too I would have apppreciated a smal scope or some type of exapmple on what to was expected. While I tried to think of what to do for the last two tasks I lost lots of time and in the process I got stuck because I didn't know how to continue creatively. So I lost soe time on learing actual coding just because I didn't know what was possible.
- Maybe some interactive parts in class would have been more helpful than just talkng, also to find out about some things and directly reflect and ask for help. But actually that one time we did that was already very helpful!

## Learnings this Week   
- How to create buttons and links with <a> tags
- Structuring the multiple componenpts of html, css.style and java script and built the into one system but what goes into which part I struggled with the most, but here I learned th most too
- How document.addEventListener('mousemove') tracks cursor position
- How requestAnimationFrame() creates smooth animation loops
- How IntersectionObserver detects when elements enter the viewport
- How to toggle classes with classList.add() and classList.remove()
- How to control audio playback with .play() and .pause()
- How to handle Promise-based async operations (audio autoplay restrictions)
- How querySelector and getElementById select DOM elements
- How event listeners work (onclick, onmousemove)
- The embedding of the Youtube Link was a weird struggle in the end, just because the Youtube Player just wouldn't embed my video correctly. This being one of the final opertations, I got really angry with YouTube hahah.

Thank you for this class, it was a lot of fun!