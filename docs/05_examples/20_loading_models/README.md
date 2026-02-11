# Example 20: Loading 3D Models (glTF)

This example demonstrates loading external 3D models using GLTFLoader in three.js.

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

- **GLTFLoader**: Loading glTF/GLB model files
- **Asynchronous Loading**: Models load in the background using callbacks
- **Model Structure**: Understanding gltf.scene hierarchy
- **Scaling**: Adjusting model size to fit your scene
- **AnimationMixer**: Playing animations from glTF files
- **Loading States**: Showing progress and handling errors

## Model Source

This example uses the Duck model from the Khronos Group glTF Sample Models:
https://github.com/KhronosGroup/glTF-Sample-Models/tree/master/2.0/Duck

## Try It Out

- The model loads asynchronously - watch the loading indicator
- Use mouse to orbit around the model
- Check the browser console (F12) to see loading progress
- If the model doesn't load, check your internet connection (model loads from CDN)

## Notes

- Models can be large - loading may take time
- Always handle errors in production code
- Consider using LoadingManager for multiple models
- For local models, place them in a `/static/models/` folder
