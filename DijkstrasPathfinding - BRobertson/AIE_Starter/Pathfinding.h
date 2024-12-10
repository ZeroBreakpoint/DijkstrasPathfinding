#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <raylib.h>
#include <cfloat>

namespace AIForGames
{
    struct Node;

    struct Edge {
        Node* target;
        float cost;
        Edge() : target(nullptr), cost(0) {}
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
    };

    struct Node {
        glm::vec2 position;
        std::vector<Edge> connections;
        float gScore;
        Node* previous;
        Node() : position(0.0f, 0.0f), gScore(FLT_MAX), previous(nullptr) {}
        Node(float x, float y) : position(x, y), gScore(FLT_MAX), previous(nullptr) {}
        void ConnectTo(Node* other, float cost);
    };
}
