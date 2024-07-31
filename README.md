# Chess Game Project

## Overview

This project is a comprehensive chess game developed for the CS 247: Software Engineering Principles course. It incorporates standard chess functionalities, advanced features, and a user-friendly interface. The project emphasizes object-oriented programming principles to ensure a well-structured and maintainable codebase.

## Features

- **Standard Chess Rules:** Includes all standard chess moves and rules.
- **User Interface:** Supports both text and graphical displays for game interaction.
- **Advanced Moves:** Implements special moves such as En Passant, Castling, and Pawn Promotion.
- **Computer Player:** Multiple difficulty levels for computer players (Level 1 to Level 5).
- **Timed Game:** Support countdown for human vs. human game!
- **Encouragements:** You get a best friend that cheers you up for even just starting the game :D

## Design Principles

### Object-Oriented Design and Patterns
- **Encapsulation:** Data is hidden within classes and accessed via public methods.
- **Inheritance & Polymorphism:** Used extensively for chess piece classes.
- **Composition & Aggregation:** Board class composed of multiple Square objects.
- **Observer Pattern:** Used for updating the game display.
- **Template/Strategy Pattern:** Used for defining player strategies.
- **Single Responsibility Principle (SRP):** Each class has a single, clear responsibility.

### Resilience to Change
- **Rule Changes:** Encapsulated logic for each piece makes it easy to modify rules.
- **Feature Extensions:** Abstract base classes allow for easy addition of new features or player types.
- **UI Changes:** Separation of game logic and display logic ensures flexibility in UI modifications.

## Extra Credit Features

- **Memory Management:** Uses smart pointers and vectors for efficient memory management.
- **Enhanced UI:** Option to display pieces as text, letters, or images.
- **Command Line Options:** Flexible command-line options for graphics and setup.
- **Move Tracking:** Displays computer moves in algebraic notation.
- **Draw Conditions:** Implements draw condition when only two kings are left.
- **Move Count:** Tracks and displays the total move count.
- **Timer:** Adds a timer feature for tracking move duration and overall game time.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/chess-game.git
   cd chess-game
