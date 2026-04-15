# ProjectTestChess

A desktop chess project built with C++, Qt Widgets, and Visual Studio.

The application opens a chessboard window, renders pieces from SVG assets, and lets players move pieces by clicking a source square and then a destination square. The current codebase includes board representation, a custom Qt board view, turn handling, move validation for all the piece types, and basic game-state messaging.

## Stack

- C++
- Qt Widgets
- Visual Studio solution/project (`.sln` / `.vcxproj`)
- SVG piece assets

## Repository Layout

```text
ProjectTestChess/
|- .gitignore
|- README.md
|- Game/
|  |- Chess.sln
|  |- Chess/
|     |- main.cpp
|     |- ChessWindow.cpp / ChessWindow.h
|     |- ChessBoard.cpp / ChessBoard.h
|     |- ChessView.cpp / ChessView.h
|     |- ChessAlgorithm.cpp / ChessAlgorithm.h
|     |- ChessGame.cpp / ChessGame.h
|     |- Chess.ui
|     |- Chess.qrc
|     |- Chess.vcxproj
|     |- Chess.vcxproj.filters
|- assets/
   |- Chess_*.svg
```

## Architecture Overview

### `main.cpp`

Creates the Qt application and shows the main window.

### `ChessWindow`

Main window controller. It:

- creates the visual board (`ChessView`)
- creates the game logic object (`ChessGame`)
- starts a new game
- loads piece icons from `assets/`
- handles click-to-move interaction
- highlights the selected square

### `ChessBoard`

Stores the 8x8 board state and exposes:

- board dimensions
- square access and updates
- piece movement on the board
- FEN-based board initialization

### `ChessView`

Custom Qt widget responsible for:

- drawing the board
- drawing rank/file labels
- drawing piece icons
- converting mouse clicks into board coordinates
- rendering square highlights

### `ChessAlgorithm`

Base game-logic class. It provides:

- the board object
- game result state
- current-player state
- a generic `newGame()`
- a virtual `move(...)` API for specialized rules

### `ChessGame`

Concrete chess logic used by the app. It currently contains:

- turn validation
- move validation for pawns, kings, queens, knights, bishops, and rooks
- piece-position tracking for game-state checks
- warning dialogs for invalid moves and some check/game-over states

## Assets

All chess piece images live in [`assets`](./assets). The application loads them with relative paths from the Visual Studio project, so this folder must stay in the repository.

## Build Requirements

To open and build the solution on another machine, the repo alone is not enough. The machine also needs:

- Visual Studio 2022
- Desktop development with C++
- MSVC toolset `v143`
- a compatible Windows SDK
- Qt installed
- Qt Visual Studio Tools / `QtMsBuild`

## Open And Run

1. Clone the repository.
2. Open [`Chess.sln`](/Game/Chess.sln) in Visual Studio.
3. Make sure Visual Studio can resolve the Qt installation used by the project.
4. Build and run the `Chess` project.

## Important Portability Note

The current project file uses teh following Qt kit for Debug :

- `Debug|x64`: `6.11.0_msvc2022_64`

## Current Behavior

From the current codebase, the application supports:

- starting from the standard initial chess position
- alternating turns between white and dark pieces
- selecting a piece and moving it by clicking
- validating many standard piece movement patterns
- showing message boxes for invalid moves and some game-state warnings

## Known Limits

Based on the current implementation, this project appears to be a course/project build rather than a full tournament-complete chess engine. In particular:

- there are no automated tests in the repository
- build artifacts were previously generated in the project tree and are now ignored via `.gitignore`
- advanced rules such as castling, promotion, and en passant do not appear in the current source
- the game-state logic is custom and should be treated as educational/project logic rather than a fully verified chess rules engine
