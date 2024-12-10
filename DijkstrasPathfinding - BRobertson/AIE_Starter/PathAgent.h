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
    glm::vec2 m_position{ 0.0f, 0.0f };
    int m_currentIndex{ 0 };
    AIForGames::Node* m_currentNode{ nullptr };
    float m_speed{ 0.0f };

public:
    std::vector<AIForGames::Node*> m_path;
    void Update(float deltaTime);
    void GoToNode(AIForGames::Node* node, NodeMap& nodeMap);
    void Draw();
    void SetNode(AIForGames::Node* node);
    void SetSpeed(float speed);
 };

