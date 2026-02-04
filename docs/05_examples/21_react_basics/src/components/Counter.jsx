/*
 * Counter Component
 *
 * This component demonstrates:
 * - useState hook for managing local component state
 * - Event handlers for button clicks
 * - State updates triggering re-renders
 *
 * Each Counter component has its own independent state.
 * If you render multiple Counters, they each track their own count.
 */

import { useState } from "react";
import "./Counter.css";

function Counter() {
  // ============================================
  // STATE
  // ============================================

  // useState(0) initializes count to 0
  // count: the current value
  // setCount: function to update the value (triggers re-render)
  const [count, setCount] = useState(0);

  // ============================================
  // EVENT HANDLERS
  // ============================================

  const increment = () => {
    // setCount updates the state and triggers a re-render
    setCount(count + 1);
  };

  const decrement = () => {
    setCount(count - 1);
  };

  const reset = () => {
    setCount(0);
  };

  // ============================================
  // RENDER
  // ============================================

  return (
    <div className="counter">
      <div className="counter-display">
        <span className={count >= 0 ? "positive" : "negative"}>{count}</span>
      </div>

      <div className="counter-buttons">
        <button onClick={decrement} className="counter-btn minus">
          -
        </button>
        <button onClick={reset} className="counter-btn reset">
          Reset
        </button>
        <button onClick={increment} className="counter-btn plus">
          +
        </button>
      </div>
    </div>
  );
}

export default Counter;
