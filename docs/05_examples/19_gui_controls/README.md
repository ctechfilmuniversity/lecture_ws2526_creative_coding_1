# Example 19: GUI Controls (lil-gui)

This example demonstrates using lil-gui to create interactive debug interfaces for three.js scenes.

## Setup

1. Install dependencies:
```bash
npm install
```

2. Run the development server:
```bash
npm run dev
```

3. Open the URL shown in the terminal (usually `http://localhost:5173`)

## Concepts Demonstrated

- **lil-gui**: A lightweight GUI library for creating debug interfaces
- **Object Properties**: Directly controlling three.js object properties
- **Params Pattern**: Wrapping custom variables in an object for GUI control
- **onChange Callbacks**: Responding to GUI changes with custom code
- **Controller Types**: Automatic detection of slider, checkbox, color picker, button

## Try It Out

- Drag sliders to move and rotate the cube
- Change the color using the color picker
- Toggle wireframe mode
- Adjust lighting parameters
- Click "Reset Scene" to restore defaults
