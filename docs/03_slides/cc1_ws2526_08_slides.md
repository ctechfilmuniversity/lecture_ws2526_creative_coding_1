name: inverse
layout: true
class: center, middle, inverse

---

# Creative Coding I

### Jonathan Ho | jonathangho@filmuniversitaet.de

#### Film University Babelsberg KONRAD WOLF

---

layout:false

## Today

.left-even[

]

---

## Today

.left-even[

- Routing
  ]

---

## Today

.left-even[

- Routing
- React
  _ Properties
  _ Hooks
  ]

---

## Today

.left-even[

- Routing
- React
  - Properties
  - Hooks
- React Three Fiber \* Drei
  ]

---

## Today

.left-even[

- Routing
- React
  - Properties
  - Hooks
- React Three Fiber
  - Drei
- Usefulness
  ]

---

## Today

.left-even[

- Routing
- React
  - Properties
  - Hooks
- React Three Fiber
  - Drei
- Usefulness \* Portfolio
  ]

--

.right-even[

- Wrap Up 🥳
  ]

---

.header[React]

[.center[<img src="../02_scripts/img/react/portfolio_01.png" alt="portfolio_01" style="width:65%;">]](https://cc1-ws2425-crappy-portfolio.vercel.app/)

---

.header[React]

## Recap

--
React Framework

--

- Modular UIs
- Efficiently manageable and performant

--

Components

--

- Fundamental building blocks of a react application
- Independent and reusable code pieces
- Responsible for visual appearances and interaction

---

.header[React]

## Recap

JSX

--

- Is a syntax extension for JavaScript used in React
- Looks like HTML
- For writing UI components
- You can embed JavaScript expressions inside {}

--

Installation

--

- `npm create vite@latest` → React, JavaScript

---

template:inverse

### React

# Routing

---

.header[React]

## Routing

Routing is the process of determining which content to display based on the URL in a web application.

--

> This can be understood as page navigation.

--

Ideally navigation happens without needing a full page reload!

.footnote[[ChatGPT 4o: What is routing?]]

---

.header[React]

## Routing

- Library: e.g., `npm install react-router-dom`

--

- Framework: e.g., [Next.js](https://nextjs.org/), [Gatsby](https://www.gatsbyjs.com/)

???

react-router-dom: Handles client-side routing for Single Page Applications (SPAs) in React.

Next.js: A full-fledged React framework with server-side rendering (SSR), static site generation (SSG), and API routes.

Choose react-router-dom if:

- You’re building a simple SPA.
- You only need client-side rendering (CSR).
- SEO is not a major concern.

Choose Next.js if:

- You need better SEO (SSR/SSG).
- You want faster performance with pre-rendering.
- You need backend functionality inside the same project.

---

.header[React]

## Routing

- Library: e.g., `npm install react-router-dom`

- Framework: e.g., [Next.js](https://nextjs.org/), [Gatsby](https://www.gatsbyjs.com/)

<br />

Approach:

--

1. Define the routes for the application

-- 2. Enclose the `App` in a router object

-- 3. Set links

???
.todo[TODO: Show, run example]

- 03_routing

---

.header[React | Routing | Defining the Routes]

```js
//main.jsx
```

---

.header[React | Routing | Defining the Routes]

```js
//main.jsx
import { RouterProvider, createBrowserRouter } from "react-router-dom";
```

---

.header[React | Routing | Defining the Routes]

```js
...
const router = createBrowserRouter([
    {
        path: '/',
        element: <App />,
        children: [
            {
                path: '/',
                element: <Home />,
            },{
                path: '/about',
                element: <About />,
            },{
                path: '/projects',
                element: <Projects />,
            }
        ]
    }
]);
```

---

.header[React | Routing | Defining the Routes]

```js
...

createRoot(document.getElementById('root')).render(

    <RouterProvider router={router}>
        <App />
    </RouterProvider>
);
```

---

.header[React | Routing | Defining the Routes]

```js
//Navigation.jsx
```

---

.header[React | Routing | Defining the Routes]

```js
//Navigation.jsx
import { Link } from "react-router-dom";

const Navigation = () => {
  return (
    <nav>
      <ul>
        <li>
          <Link to="/">Home</Link>
        </li>
        <li>
          <Link to="/about">About</Link>
        </li>
        <li>
          <Link to="/projects">Projects</Link>
        </li>
        <li>
          <Link to="/contact">Contact</Link>
        </li>
      </ul>
    </nav>
  );
};
export default Navigation;
```

---

.header[React | Routing | Defining the Routes]

```js
//App.jsx
```

---

.header[React | Routing | Defining the Routes]

```js
//App.jsx
import { Outlet } from "react-router-dom";

...

const App = () => {
    return (
        <>
            <Navigation />
            <Outlet /> {/* Renders child routes here */}
        </>
    );
};

export default App;
```

???
The <Outlet /> component is used in React Router to render child routes inside a parent route. It acts as a placeholder where nested route components will be displayed.

When using nested routes, <Outlet /> tells React Router where to render the child component inside the parent.
Without <Outlet />, child routes wouldn’t appear inside their parent.

---

.header[React]

## Routing

In summary, routing is the process of determining which UI component to display based on the URL.

--

`react-router-dom` is a library that enables client-side routing in React, allowing navigation without full page reloads.

--

- Declarative routing

--

- Navigation with `<Link>`

--

- Nested routes with `<Outlet />`

--

- Supports dynamic routing (`/projects/:id`)

--

- Supports browser history

---

.header[React]

## Properties

--

- Arguments passed into React components
- Passed to components via HTML attributes

---

.header[React | Properties]

Add an attribute of your choice to the `HeroText` element:

```jsx
// Header.jsx
import "./Header.css";
import HeroText from "./HeroText.js";
import HeroImage from "./HeroImage.js";

export default function Header() {
  return (

        <HeroText name="Justus" /> {/* Property name with value Justus */}
        <HeroImage />
  );
}

```

---

.header[React]

Use the `name` attribute in the component with a function argument:

```jsx
// HeroText.jsx

function HeroText(props) {
  return <h2>Hi {props.name}, I am a Hero Text!</h2>;
}
```

.footnote[[[w3schools]](https://www.w3schools.com/react/default.asp)]

---

.header[React]

```jsx
// Header.jsx
import HeroText from "./HeroText.js";

export default function Header() {
  return (

        <HeroText name="Justus" />
        <HeroImage />

  );
}
```

```jsx
// HeroText.jsx

function HeroText(props) {
  return <h2>Hi {props.name}, I am a Hero Text!</h2>;
}
```

---

template:inverse

### React

# Hooks

---

.header[React]

## Hooks

Hooks are special functions that let you “hook into” React’s built-in features inside functional components.

--

- `useState`: Lets a component remember values (a state) between re-draws.

???

- The current frame number in an animation

- Whether a light is on or off

- The volume level of a sound

- The position of a slider

--

- `useEffect`: Runs code when something changes, runs side effects (e.g., fetching data).

???

useState: E.g. a counter, or a light-mode/dark-mode toggle button.
useEffect Runs after every render, but can be controlled when to run:

- A speed tracker
- Like an alarm clock that goes off when it’s time to wake up.

--

- `useRef`: Keeps a reference to something

???

- A rear-view mirror (references: useRef)
- Like a bookmark in a book—you can jump to that place later.

--

- `useContext`: Shares values between components

???

- Like a WiFi signal that multiple devices (components) can use.

.footnote[[ChatGPT 4o: What are React hooks?]]

???

- Car: component

--

> Different hooks trigger page re-renderings differently.

???

- useState triggers a re-render.
- With useRef, values persist across renders but do not cause extra renders.

---

.header[React]

## `useState` Hook

--
`useState` allows components to have state, i.e., data that can change and trigger re-renders.

--

1. Declare a state variable and set an initial value

2. Provide a function to update the state (which triggers a re-render)

---

.header[React]

## `useState` Hook

```jsx
import React, { useState } from "react";

export default function Counter() {
  // Declare state variable,
  // its update function and
  // a initial value
  const [count, setCount] = useState(0);

  return (
    <div>
      <p>Count: {count}</p>
      <button onClick={() => setCount(count + 1)}>Increase</button>
    </div>
  );
}
```

???

Explanation

- const [count, setCount] = useState(0);
  - count → State variable (initially 0).
  - setCount → Function to update count.
  - useState(0) → Initializes count with 0.
- Clicking the button calls setCount(count + 1), updating count and re-rendering the component.

---

.header[React]

## `useRef` Hook

--

`useRef` creates a mutable reference that does not trigger re-renders when updated.

--

- Accessing and modifying DOM elements
- Storing values that persist across renders without causing re-renders

---

.header[React]

## `useRef` Hook

```jsx
import React, { useRef } from "react";

export default function InputFocus() {
  const inputRef = useRef(null); // Create a reference

  const handleClick = () => {
    inputRef.current.focus(); // Directly focus the input field
  };

  return (
    <div>
      <input ref={inputRef} type="text" />
      <button onClick={handleClick}> Focus Input</button>
    </div>
  );
}
```

???

- inputRef.current refers to the actual `<input>` DOM element.
- Clicking the button directly focuses the input using .focus().

```jsx
import React, { useRef, useState } from "react";

function Counter() {
  const countRef = useRef(0); // Mutable reference
  const [renderCount, setRenderCount] = useState(0);

  const increase = () => {
    countRef.current += 1; // Updates value but does NOT trigger re-render
    console.log("Ref Value:", countRef.current);
  };

  return (
    <div>
      <p>Component rendered: {renderCount} times</p>
      <button onClick={() => setRenderCount(renderCount + 1)}>Re-render</button>
      <button onClick={increase}>Increase Ref Count</button>
    </div>
  );
}
export default Counter;
```

countRef.current stores a value that persists across renders but does not trigger re-renders when updated.

Key Points

- Does not trigger re-renders when updated.
- Used for accessing/manipulating DOM elements.
- Great for persisting values between renders (like timers, previous values).

---

.header[React]

## `useEffect` Hook

`useEffect` is used to perform side effects in components, such as:

- Fetching data
- Managing timers

By default, it runs after the component renders but it can be controlled when to run:

--

```
useEffect(() => {
    console.log("Component re-rendered!"); // Runs after every render
});
```

---

.header[React]

## `useEffect` Hook

`useEffect` is used to perform side effects in components, such as:

- Fetching data
- Managing timers

By default, it runs after the component renders but it can be controlled when to run:

```
useEffect(() => {
    console.log("Component re-rendered!"); // Runs after every render
}, []);
```

---

.header[React]

## `useEffect` Hook

`useEffect` is used to perform side effects in components, such as:

- Fetching data
- Managing timers

By default, it runs after the component renders but it can be controlled when to run:

```
useEffect(() => {
    console.log("Component re-rendered!"); // Runs after every render
}, [stateX]);
```

---

.header[React]

## `useEffect` Hook

```jsx
import React, { useState, useEffect } from "react";

export default function Counter() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    console.log("Component re-rendered!"); // Runs after every render
  });

  return (
    <div>
      <p>Count: {count}</p>
      <button onClick={() => setCount(count + 1)}>Increase</button>
    </div>
  );
}
```

useEffect(() => { ... }) runs after every render (default behavior).

---

.header[React | `useEffect` Hook]

## Controlling `useEffect` Runs

`useEffect` takes a dependency array to control execution.

<br />

#### 1. Run After Each Re-rendering

```js
useEffect(() => {
  console.log("Component re-rendered!");
}); // NO dependency array → Runs after each update
```

Useful for running code that depends on any state change.

---

.header[React | `useEffect` Hook]

## Controlling `useEffect` Runs

`useEffect` takes a dependency array to control execution.

<br />
  
####  2. Run Only Once (On Mount)  
```js
useEffect(() => {
    console.log("Component mounted!");
}, []); // Empty dependency array → Runs only once
```
Useful for fetching data or setting up event listeners.

---

.header[React | `useEffect` Hook]

## Controlling `useEffect` Runs

`useEffect` takes a dependency array to control execution.

<br />

#### 3. Run When a State Changes

```js
useEffect(() => {
  console.log(`Count changed: ${count}`);
}, [count]); // Runs only when `count` changes
```

Runs only when `count` updates.

---

.header[React | `useEffect` Hook]

## Controlling `useEffect` Runs

`useEffect` takes a dependency array to control execution.

<br />
  
#### 4. Cleanup Effect (Before Unmount)  
```js
useEffect(() => {
    const intervalID = setInterval(() => {
        console.log("Timer running...");
    }, 1000);

    return () => clearInterval(intervalID); // Cleanup when unmounted

}, []);

````

Calls the return function once.

???

Built-in JavaScript functions:
* setInterval starts a repeating function every X milliseconds and returns an interval ID (a number).
* clearInterval(intervalID) stops the interval when it’s no longer needed.

Cleans up when the component unmounts (useful for removing listeners/timers).

Key Points
* Runs after renders but can be controlled with dependencies.
* Used for fetching data, event listeners, timers, etc.
* Supports cleanup to prevent memory leaks.




---
.header[React]

## Hooks

In summary, React Hooks are functions that let you use state and lifecycle features within components.

--

* Manage states
* Handle side effects and processes
* Create references without causing re-renders


???
Key Rules of Hooks
* Only call hooks at the top level (not inside loops, conditions, or nested functions)
* Only call hooks in React functions (functional components or custom hooks)

.todo[TODO: Show Portfolio]


---
template:inverse

# React Three Fiber


---
.header[React]

## React Three Fiber (R3F)

--
* React 3D library for rendering with Three.js

> R3F wraps its own code around Three.js and manages Three.js.


???

A React renderer is a library that allows React to render content to a specific platform beyond the standard DOM. React itself provides the Reconciler, which determines how components should update, but the actual rendering is handled by a renderer.



---
.header[React]

## React Three Fiber

```js
const scene = new THREE.Scene();
const geometry = new THREE.BoxGeometry(1, 1, 1);
const material = new THREE.MeshStandardMaterial({ color: "blue" });
const cube = new THREE.Mesh(geometry, material);
scene.add(cube);
````

--

```html
<canvas>
  <mesh>
    <boxGeometry args="{[1," 1, 1]} />
    <meshStandardMaterial color="blue" />
  </mesh>
</canvas>
```

---

.header[React]

## React Three Fiber

- `<mesh>`  
  → `new THREE.Mesh()`
- `<boxGeometry />`  
  → `new THREE.BoxGeometry()`
- `<meshStandardMaterial color="blue" />`  
  → `new THREE.MeshStandardMaterial({ color: "blue" })`

---

.header[React | React Three Fiber]

```js
// RotatingCube.jsx
import { Canvas } from "@react-three/fiber";
import { useFrame } from "@react-three/fiber";
import { useRef } from "react";

function RotatingCube() {
  const meshRef = useRef();

  useFrame(() => {
    meshRef.current.rotation.x += 0.01;
    meshRef.current.rotation.y += 0.01;
  });

  return (
    <mesh ref={meshRef}>
      <boxGeometry args={[1, 1, 1]} />
      <meshStandardMaterial color="blue" />
    </mesh>
  );
}
```

???

- `<Canvas>` → The main 3D scene container (like `<canvas>` in HTML).
- `<mesh>` → A 3D object (in this case, a cube).
- `<boxGeometry>` → Defines the shape of the cube.
- `<meshStandardMaterial>` → Gives the cube color and lighting properties.
- useFrame() → Runs on every frame (used to rotate the cube).

---

.header[React | React Three Fiber]

```js
// App.jsx
import { Canvas } from "@react-three/fiber";
import RotatingCube from "./RotatingCube.jsx";

function App() {
  return (
    <Canvas>
      <ambientLight />
      <RotatingCube />
    </Canvas>
  );
}
export default App;
```

???

- Reacts to State & Props → Easily make 3D objects interactive.
- Leverages React’s Ecosystem → Works with hooks, context, and effects.
- Optimized for Performance → Uses declarative components instead of imperative Three.js code.

---

## React Three Fiber

```
npm install three @react-three/fiber
```

--

- Use JSX to define 3D scenes instead of Three.js code

--

- Treat 3D objects as reusable React components

--

- Use React state and hooks for managing 3D elements

???

- `useState`, `useEffect`, `useRef`

--

- Additional useful hooks, e.g. `useFrame` (for animations) and `useThree` (for scene access)

---

## React Three Fiber

Examples:

- [Bruno Simon's Portfolio ⬀](https://bruno-simon.com/)
- [Examples ⬀](https://r3f.docs.pmnd.rs/getting-started/examples)
- [Organic Sphere ⬀](https://organic-sphere.vercel.app/), [code ⬀](https://github.com/brunosimon/organic-sphere/tree/master)
- [Particle System ⬀](https://three-js-tsl-particles-system.vercel.app/), [code ⬀](https://github.com/brunosimon/three.js-tsl-particles-system)
- [Attractors ⬀](https://threejs.org/examples/webgpu_tsl_compute_attractors_particles.html)

Documentation:

- [r3f.netlify.app](https://r3f.netlify.app/)
- [r3f.docs.pmnd.rs](https://r3f.docs.pmnd.rs/getting-started/introduction)

???

- [OLD: React three fiber journey ⬀](https://journey.pmnd.rs/)

---

.header[React Three Fiber]

## Drei Library

[Drei](https://drei.docs.pmnd.rs/getting-started/introduction) provides ready-to-use components for working with 3D scenes, physics, lighting, and interactions.

--

> Drei is a library for the React Three Fiber library...

---

.header[React Three Fiber]

## Drei Library

```js
import { Canvas } from "@react-three/fiber";
import { OrbitControls, Text } from "@react-three/drei";

function Scene() {
  return (
    <Canvas>
      <OrbitControls />
      <Text position={[0, 1, 0]} fontSize={0.5}>
        Hello Drei!
      </Text>
    </Canvas>
  );
}
export default Scene;
```

---

.header[React Three Fiber]

## Drei Library

[Examples ⬀](https://drei.docs.pmnd.rs/getting-started/introduction)

---

.header[React]

## React Three Fiber & Drei

In summary, R3F is a React renderer for Three.js, allowing you to build 3D scenes using React components.

--

- Uses JSX for creating and managing 3D objects.
- Integrates smoothly with React’s state and lifecycle.
- Handles animations, physics, and interactivity efficiently.

--

Drei is a utility library that extends R3F with pre-built components.

---

template:inverse

# Usefulness

???

- What is the definition of usefulness?
- What does it mean to do something useful?

---

## Portfolio

> You should have a personal website.

--

- [Top 100 Most Creative and Unique Portfolio Websites of 2025 ⬀](https://muz.li/blog/top-100-most-creative-and-unique-portfolio-websites-of-2025/)

--

Keep in mind:

--

- Always offer easy navigation as alternative

--
_ Have people in mind that need to look at 100 portfolios in 30 minutes
--
_ I personally like categories and tags
--

- Describe your projects: what did you do, which tools did you used, etc.

---

.center[<img src="../02_scripts/img/software/sloth.png" alt="sloth" style="width:100%;">]

???

https://www.ted.com/talks/lucy_cooke_sloths_the_strange_life_of_the_world_s_slowest_mammal#t-278839

- [sloths](https://www.ted.com/talks/lucy_cooke_sloths_the_strange_life_of_the_world_s_slowest_mammal#t-278839),
- [Simone Giertz's work](https://www.ted.com/talks/simone_giertz_why_you_should_make_useless_things#t-697827)
- https://www.simonegiertz.com/
- https://www.youtube.com/c/simonegiertz
- [Make Everything Ok Button](http://make-everything-ok.com/)
- Vi: https://www.youtube.com/watch?v=ott_0kDkCyg

---

<img src="../02_scripts/img/software/sloth.png" alt="sloth" style="width:80%;">

--

- What else should we consider as _useful_?

--

- What do we commonly judge out of context?

[make everything ok button ⬀](https://make-everything-ok.com/)

---

template:inverse

# Wrap Up

???

.todo[TODO: Go to Syllabus]  
https://ctechfilmuniversity.github.io/lecture_ws2425_creative_coding_1/

---

.header[Creative Coding I]

## Learning Objectives

With this course, you

--

- advance your ability to write code,

--

- advance your ability to conceptualize and design,

--

- acquire fundamental knowledge of web technologies,

--

- use software development in a creative context, and

--

- implement specific design goals.

---

template:inverse

# Creative Coding I ✔️

--

### Well, almost...

---

## Final Project

--

The final project is an individually chosen project.

???
.task[COMMENT:]

You can do whatever you want but your project must make use of text-based programming. It can also be an experiment, work in progress, or a learning path. Ideally it should be something online, but this is not a hard requirement. You don't need to submit a project plan beforehand. However, it might help to discuss your plan with me in advance. The project should not take longer than ~24h.

--

- It must be text-based programming

--
_ Ideally it should be something online, but this is not a hard requirement
--
_ It can be an experiment, part of another project, work in progress, or a learning path

--

- The official work period: Feb. 1st - Feb. 28th

--

- The time dedicated to the final project: ~40h

--

- Deadline: **February, 28th**.

???
.task[COMMENT:]

- The deadline for the final project is strict and for a late submission, I reduce **15% of the total points**.
- If you are sick within the official work period, you can get a deadline extension based on a doctor's note ("Attest").

---

## Final Project

You need to submit

- a description
- the source code
- a link to the build / online deployment or such, and
- at least one representative image.

--

Submit your code in your assignment folder as assignment `05` or add a link there to where to find the code.

---

template: inverse

## And Now What?

# 🤔

---

# _Keep on Coding!_ 💃🏻🕺

--

- Algorithmic thinking

--

- Build systems and software

--

- Draw diagrams

---

template:inverse

## The End

# 🐥 🦋 🦉
