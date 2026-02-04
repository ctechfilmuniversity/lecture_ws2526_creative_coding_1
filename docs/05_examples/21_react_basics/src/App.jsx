/*
 * Example 21: React Basics - App Component
 *
 * This is the main App component that demonstrates:
 * - Component composition (using other components)
 * - Passing props to child components
 * - Using useState hook for state management
 *
 * Key Concepts:
 * - Components are functions that return JSX
 * - JSX looks like HTML but is actually JavaScript
 * - Props pass data from parent to child components
 * - useState creates reactive state that triggers re-renders
 */

import { useState } from "react";
import Header from "./components/Header.jsx";
import Counter from "./components/Counter.jsx";
import ColorCard from "./components/ColorCard.jsx";
import "./App.css";

function App() {
  // ============================================
  // STATE MANAGEMENT WITH useState
  // ============================================

  // useState returns an array with two elements:
  // 1. The current state value
  // 2. A function to update the state
  const [userName, setUserName] = useState("Creative Coder");
  const [theme, setTheme] = useState("light");

  // Array of colors to display as cards
  const colors = [
    { name: "Coral", hex: "#FF6B6B" },
    { name: "Teal", hex: "#4ECDC4" },
    { name: "Purple", hex: "#9B59B6" },
    { name: "Gold", hex: "#F1C40F" },
  ];

  // ============================================
  // EVENT HANDLERS
  // ============================================

  // Handler for the name input
  const handleNameChange = (event) => {
    setUserName(event.target.value);
  };

  // Handler for theme toggle
  const toggleTheme = () => {
    setTheme(theme === "light" ? "dark" : "light");
  };

  // ============================================
  // RENDER
  // ============================================

  return (
    <div className={`app ${theme}`}>
      {/* 
        Passing props to Header component:
        - name: the current userName state
        - theme: the current theme
      */}
      <Header name={userName} theme={theme} />

      <main className="main-content">
        {/* Name Input Section */}
        <section className="section">
          <h2>Change Your Name</h2>
          <p>Type below to see props update in real-time:</p>
          <input
            type="text"
            value={userName}
            onChange={handleNameChange}
            placeholder="Enter your name"
            className="name-input"
          />
        </section>

        {/* Theme Toggle Section */}
        <section className="section">
          <h2>Theme Toggle</h2>
          <p>
            Current theme: <strong>{theme}</strong>
          </p>
          <button onClick={toggleTheme} className="theme-button">
            Switch to {theme === "light" ? "Dark" : "Light"} Mode
          </button>
        </section>

        {/* Counter Component - demonstrates useState within a component */}
        <section className="section">
          <h2>Counter Example</h2>
          <p>This component manages its own state:</p>
          <Counter />
        </section>

        {/* Color Cards - demonstrates mapping over arrays and props */}
        <section className="section">
          <h2>Color Cards</h2>
          <p>Components rendered from an array using map():</p>
          <div className="color-grid">
            {colors.map((color, index) => (
              // Each item in a list needs a unique "key" prop
              <ColorCard key={index} name={color.name} hex={color.hex} />
            ))}
          </div>
        </section>
      </main>

      <footer className="footer">
        <p>Creative Coding I - React Basics Example</p>
      </footer>
    </div>
  );
}

export default App;
