# DijkstrasPathfinding (C++ with Raylib)

This stand-alone demonstration implements **Dijkstra's shortest path algorithm** using C++ and Raylib, with support for real-time interaction, agent animation and visualised paths.  Created for an AIE assessment, this project allows users to explore how Dijkstra’s algorithm calculates the shortest path between two points on a 2D grid.

---

## Features

### Fully Functional Dijkstra's Algorithm
- Calculates shortest path from a start node to an end node
- Supports dynamic node reassignment during runtime
- Backtracks using `previous` pointers to reconstruct the path

### Real-Time Visualisation
- Agent follows the calculated path smoothly
- Grid and path are rendered live using Raylib
- Nodes and connections are updated each time a new target is selected

### Controls
- **Left-click** sets the player controlled agent start node
- **Right-click** sets the player controlled agent end node
