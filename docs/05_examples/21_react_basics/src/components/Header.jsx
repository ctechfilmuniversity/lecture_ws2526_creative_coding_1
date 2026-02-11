/*
 * Header Component
 *
 * This component demonstrates:
 * - Receiving props from a parent component
 * - Using props to render dynamic content
 * - Destructuring props in the function parameters
 *
 * Props:
 * - name: string - The user's name to display
 * - theme: string - Current theme ('light' or 'dark')
 */

import "./Header.css";

// Props can be destructured directly in the function parameters
// This is equivalent to: function Header(props) { const { name, theme } = props; ... }
function Header({ name, theme }) {
  return (
    <header className={`header ${theme}`}>
      <h1>Hello, {name}!</h1>
      <p>Welcome to React Basics</p>
    </header>
  );
}

export default Header;
