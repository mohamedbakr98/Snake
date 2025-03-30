# Snake Game

![Snake Game Screenshot](screenshot.png)

A classic console-based Snake game implemented in C, featuring a menu system, score tracking, and smooth snake movement.

## Features

- 🎮 Classic Snake gameplay
- 📊 Score tracking system
- 🍎 Random fruit generation
- 🎯 Menu system with multiple options
- 🎨 Colored console interface
- 💾 Save and load game functionality

## Game Controls

- **Arrow Keys**: Control snake movement
- **Enter**: Select menu options
- **Up/Down Arrow**: Navigate menu
- **ESC**: Exit game

## Game Rules

1. Control the snake using arrow keys
2. Eat fruits to grow longer and increase your score
3. Avoid hitting the walls or the snake's own body
4. The game ends when you collide with the wall or yourself

## Building the Game

### Prerequisites

- GCC compiler
- Windows operating system (for console functionality)

### Compilation

To compile the game, run the following command in the project directory:

```bash
gcc main.c major_functions.c input.c -o snake.exe
```

### Running the Game

After compilation, run the game using:

```bash
.\snake.exe
```

## Project Structure

- `main.c`: Main game loop and initialization
- `major_functions.c`: Core game logic and menu system
- `major_functions.h`: Function declarations and shared variables
- `input.c`: Input handling and keyboard controls
- `input.h`: Input-related declarations
- `settings.h`: Game configuration and constants

## Game Settings

The game board is configured with the following dimensions:
- Width: 25 units
- Height: 25 units
- Starting position: (30, 2) on the console

## Menu Options

1. **New Game**: Start a fresh game
2. **Load Game**: Continue a previously saved game
3. **Exit**: Quit the game

## Technical Details

- The game uses Windows Console API for display and input
- Snake movement is implemented using coordinate-based system
- Collision detection is performed for walls and self-collision
- Random number generation is used for fruit placement

## Contributing

Feel free to submit issues and enhancement requests!

## License

This project is open source and available under the MIT License.
