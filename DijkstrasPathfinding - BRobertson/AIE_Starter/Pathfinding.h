#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <raylib.h>
#include <cfloat>

namespace AIForGames
{
    struct Node;

    // Represents a connection (edge) between two nodes with an associated movement cost
    struct Edge {
        Node* target; // Target node for the connection
        float cost;   // Cost of traversing this edge
        Edge() : target(nullptr), cost(0) {}
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
    };

    // Represents a position within the navigation grid
    struct Node {
        glm::vec2 position;                  // Position in world space
        std::vector<Edge> connections;       // List of connections to neighbouring nodes
        float gScore;                        // Cost from start node to this node
        Node* previous;                      // Pointer to the previous node in the shortest path

        Node() : position(0.0f, 0.0f), gScore(FLT_MAX), previous(nullptr) {}
        Node(float x, float y) : position(x, y), gScore(FLT_MAX), previous(nullptr) {}

        void ConnectTo(Node* other, float cost); // Creates a directional connection
    };
}
