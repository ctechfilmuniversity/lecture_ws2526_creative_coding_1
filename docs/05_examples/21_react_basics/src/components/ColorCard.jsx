/*
 * ColorCard Component
 *
 * This component demonstrates:
 * - Receiving multiple props
 * - Using props for both content and styling
 * - A simple, reusable component pattern
 *
 * Props:
 * - name: string - The name of the color
 * - hex: string - The hex color code (e.g., '#FF6B6B')
 */

import "./ColorCard.css";

function ColorCard({ name, hex }) {
  return (
    <div className="color-card">
      {/* 
        Inline styles in React use camelCase (backgroundColor, not background-color)
        and values are passed as strings or numbers
      */}
      <div className="color-swatch" style={{ backgroundColor: hex }} />
      <div className="color-info">
        <span className="color-name">{name}</span>
        <span className="color-hex">{hex}</span>
      </div>
    </div>
  );
}

export default ColorCard;
