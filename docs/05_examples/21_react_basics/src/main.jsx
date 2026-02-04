/*
 * Example 21: React Basics - Entry Point
 *
 * This is the entry point of our React application.
 * It renders the App component into the DOM element with id "root".
 */

import React from "react";
import ReactDOM from "react-dom/client";
import App from "./App.jsx";
import "./index.css";

// Create a root and render our App component
ReactDOM.createRoot(document.getElementById("root")).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);
