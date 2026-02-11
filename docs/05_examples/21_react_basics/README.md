# Example 21: React Basics

This example demonstrates the fundamental concepts of React: components, props, and the useState hook.

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

## Concepts

### Components

- **App.jsx**: The main component that composes other components
- **Header.jsx**: A simple component receiving props
- **Counter.jsx**: A component with its own local state
- **ColorCard.jsx**: A reusable component rendered multiple times

### JSX

- HTML-like syntax in JavaScript
- Embedding JavaScript expressions with `{}`
- Conditional class names
- Inline styles with camelCase properties

### Props

- Passing data from parent to child components
- Destructuring props in function parameters
- Using props for both content and styling

### useState Hook

- Creating reactive state variables
- Updating state with setter functions
- State changes trigger component re-renders

## File Structure

```
21_react_basics/
├── index.html          # HTML entry point
├── package.json        # Dependencies
├── vite.config.js      # Vite configuration
└── src/
    ├── main.jsx        # React entry point
    ├── index.css       # Global styles
    ├── App.jsx         # Main App component
    ├── App.css         # App styles
    └── components/
        ├── Header.jsx      # Header component
        ├── Header.css
        ├── Counter.jsx     # Counter with useState
        ├── Counter.css
        ├── ColorCard.jsx   # Reusable card component
        └── ColorCard.css
```

## Try It Out

- Type in the name input to see the header update in real-time
- Click the theme toggle to switch between light and dark mode
- Use the counter buttons to increment, decrement, or reset
- Hover over the color cards to see the animations

## Key Takeaways

1. **Components are functions** that return JSX (HTML-like syntax)
2. **Props flow downward** from parent to child components
3. **useState** creates state that persists across re-renders
4. **State updates trigger re-renders** of the component and its children
5. **Each component can have its own state** (Counter has independent count)
