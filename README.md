# Arduino Snake Game

A classic Snake game implementation for Arduino using an 8x8 LED Matrix and two control buttons.

## 🕹️ How it Works

- **Objective**: Eat the food to grow the snake as long as possible.
- **Game Over**: If the snake's head touches its own body, the game resets.
- **Wrap-around**: Moving through a wall will make the snake appear on the opposite side.
- **Controls**:
  - **Auto-move**: The snake moves forward automatically every 400ms.
  - **Inversion**: Pressing a button corresponding to the opposite direction of movement will invert the snake (the tail becomes the head).

## 🛠️ Hardware Requirements

- **Arduino** (Uno, Nano, or similar)
- **8x8 LED Matrix** (Multiplexed)
- **2x Push Buttons** (UP and LEFT)
- Jumper wires and Breadboard

## 🔌 Pinout & Wiring

### 8x8 LED Matrix
The matrix is driven through 16 pins (8 rows and 8 columns).

| Arduino Pin | Matrix Component |
|-------------|------------------|
| 2 to 9      | ROWS 1 to 8      |
| 10 to 13    | COLUMNS 1 to 4   |
| A0 to A3    | COLUMNS 5 to 8   |

### Buttons
Buttons are connected with internal `INPUT_PULLUP`. Connect one side of the button to the Arduino pin and the other to Ground (GND).

| Arduino Pin | Function |
|-------------|----------|
| A5          | Button UP / Down |
| A4          | Button LEFT / Right |

*Note: Since there are only two buttons, they handle transitions between Vertical and Horizontal movement. Pressing the button for the current axis will invert the snake.*

## 🚀 How to Run

1. Connect the hardware according to the pinout above.
2. Open `snakeGame.ino` in the **Arduino IDE**.
3. Select your board and port.
4. Click **Upload**.
5. Enjoy the game!

---
*Created as a project demonstration.*
