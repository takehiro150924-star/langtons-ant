# Langton's Ant

This repository contains a C++ implementation of Langton's Ant.

## Overview

Langton's Ant is a simple cellular automaton.
An ant moves on a grid according to simple rules.

Rules:

1. If the ant is on a white cell:
   - Turn right
   - Change the cell to black
   - Move forward one cell

2. If the ant is on a black cell:
   - Turn left
   - Change the cell to white
   - Move forward one cell

## Files

```text
Langtons_ant.cpp  Main C++ source code
Dockerfile        Docker environment definition
compose.yml       Docker Compose configuration
.gitignore        Files ignored by Git
```

## Build and Run on Windows

If you have g++ installed, run:

```powershell
g++ Langtons_ant.cpp -o Langtons_ant.exe
.\Langtons_ant.exe
```

## Run with Docker

If you have Docker installed, run:

```powershell
docker compose up --build
```

## Output

The program outputs a BMP image:

```text
langtons_ant_result.bmp
```

White cells represent unvisited or white cells.
Black cells represent flipped cells.
The red cell represents the final ant position.

## Purpose

This project is for understanding the basic structure of agent-based simulation:

```text
Agent observes the environment
↓
Agent changes its direction based on rules
↓
Agent updates the environment
↓
Agent moves
↓
Repeat
```

This structure is related to termite or swarm robot simulations.