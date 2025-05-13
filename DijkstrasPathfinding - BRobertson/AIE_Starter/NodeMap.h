#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include "Pathfinding.h"
#include <raylib.h>

class NodeMap
{
    int m_width, m_height;               // Grid dimensions
    float m_cellSize;                    // Size of each grid cell in pixels
    AIForGames::Node** m_nodes;          // Flat array of node pointers

public:
    NodeMap();
    ~NodeMap();
    AIForGames::Node* GetNode(int x, int y);
    void Initialise(std::vector<std::string> asciiMap, int cellSize);
    void Draw();
    std::vector<AIForGames::Node*> DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);
    void DrawPath(const std::vector<AIForGames::Node*>& path, Color lineColour);
    AIForGames::Node* GetClosestNode(glm::vec2 worldPos);
};