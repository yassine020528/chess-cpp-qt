# chess-cpp-qt

A desktop chess application built with C++, Qt Widgets, and Visual Studio.

The app renders an interactive 8x8 board, loads SVG pieces from the repository assets folder, and supports click-to-move gameplay (select source square, then destination square).

## Tech Stack

- C++
- Qt 6 Widgets (Core, Gui, Widgets)
- Visual Studio solution/project files (.sln / .vcxproj)

## Repository Layout

```text
chess-cpp-qt/
|- README.md
|- .gitignore
|- assets/
|  |- Chess_*.svg
|- Game/
   |- Chess.sln
   |- Chess/
      |- main.cpp
      |- ChessWindow.cpp / ChessWindow.h
      |- ChessView.cpp / ChessView.h
      |- ChessBoard.cpp / ChessBoard.h
      |- ChessAlgorithm.cpp / ChessAlgorithm.h
      |- ChessGame.cpp / ChessGame.h
      |- Chess.ui
      |- Chess.qrc
      |- Chess.vcxproj
      |- Chess.vcxproj.filters
```

## Architecture Overview

### main.cpp

Creates QApplication, instantiates ChessWindow, and enters the event loop.

### ChessWindow

Main UI controller that:

- creates ChessView and ChessGame
- starts a new game
- wires click handling to move execution
- loads piece icons from ../../assets/*.svg
- highlights the currently selected square

### ChessBoard

Board data model that:

- stores board state in an 8x8 grid
- exposes read/write square access
- applies moves
- supports FEN placement loading

### ChessView

Custom QWidget responsible for:

- drawing board cells and labels
- drawing piece icons
- translating mouse clicks to board coordinates
- drawing selection highlights

### ChessAlgorithm

Base logic class that provides:

- board lifecycle/setup
- current player state
- game result state
- virtual move API

### ChessGame

Concrete chess rules implementation that currently includes:

- turn enforcement (white/dark alternating)
- movement validation for pawns, kings, queens, rooks, bishops, and knights
- path blocking checks for sliding pieces
- prevention of moves that leave the moving side king in check
- check warnings via message boxes

## Gameplay Status

Implemented in the current code:

- standard initial position
- click-to-move interaction
- legal movement checks for all standard piece types
- king-in-check detection used to reject illegal moves

Current limitations:

- game over is currently based on king capture, not full checkmate/stalemate resolution
- no castling
- no en passant
- no pawn promotion
- no automated tests in this repository

## Build Requirements (Windows)

- Visual Studio 2022 with Desktop development with C++
- MSVC v143 toolset
- Windows SDK
- Qt installation compatible with the configured kits
- Qt Visual Studio Tools (QtMsBuild integration)

## Qt Kit Configuration Note

The project file currently references different Qt kits by configuration:

- Debug|x64: 6.11.0_msvc2022_64
- Release|x64: 6.5.0_msvc2019_64

If either kit is missing on your machine, update the Qt project settings in Visual Studio or install matching kits.

## Build And Run

1. Open Game/Chess.sln in Visual Studio.
2. Ensure QtMsBuild is installed and the Qt kits above resolve correctly.
3. Select x64 and either Debug or Release.
4. Build and run the Chess project.

## Assets

Piece icons are loaded from assets/*.svg using relative paths from the executable working directory. Keep the assets folder in this repository layout so icons load correctly at runtime.
