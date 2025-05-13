#pragma once
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "raylib.h"
#include "Pathfinding.h"
#include "NodeMap.h"
#include <cfloat>

class PathAgent
{
private:
    glm::vec2 m_position{ 0.0f, 0.0f };      // Current position of the agent in the world
    int m_currentIndex{ 0 };                // Index of the node currently being travelled to
    AIForGames::Node* m_currentNode{ nullptr }; // Node the agent currently occupies
    float m_speed{ 0.0f };                  // Movement speed of the agent

public:
    std::vector<AIForGames::Node*> m_path;  // List of nodes forming the current path

    void Update(float deltaTime);           // Moves the agent along the current path
    void GoToNode(AIForGames::Node* node, NodeMap& nodeMap); // Calculates path to a target node
    void Draw();                            // Renders the agent visually
    void SetNode(AIForGames::Node* node);   // Places agent at a specific node
    void SetSpeed(float speed);             // Sets how fast the agent moves
};


