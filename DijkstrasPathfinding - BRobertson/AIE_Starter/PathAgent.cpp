#include "NodeMap.h"
#include "PathAgent.h"
#include "raylib.h"
#include <algorithm>
#include <cfloat>
#include <iostream>

using namespace AIForGames;

void PathAgent::SetNode(AIForGames::Node* node)
{
    if (node == nullptr) {
        std::cerr << "Error: Attempted to set a null node." << std::endl;
        return;
    }

    m_currentNode = node;
    m_position = node->position;
}

void PathAgent::SetSpeed(float speed)
{
    m_speed = speed;
}



	void PathAgent::Update(float deltaTime)
    {
        if (m_path.empty()) return; // If path is empty, return

        Node* nextNode = m_path[m_currentIndex];
        if (nextNode == nullptr) {
            std::cerr << "Error: Next node in the path is null." << std::endl;
            return;
        }

        glm::vec2 direction = nextNode->position - m_position;
        float distance = glm::length(direction);

        // Normalise the direction vector (unit vector)
        glm::vec2 unitDirection = glm::normalize(direction);

        // Subtract the distance covered this frame
        distance -= m_speed * deltaTime;

        if (distance > 0) {
            // If still moving towards the target node
            m_position += unitDirection * m_speed * deltaTime;
        }
        else {
            // Agent has overshot or reached the node
            m_currentIndex++;

            if (m_currentIndex >= m_path.size()) {
                // Agent has reached the end of the path, snap to the final node and clear the path
                m_position = nextNode->position;
                m_path.clear();
            }
            else {
                // Move to the next node in the path
                m_position = nextNode->position;

                // Get the next target node
                Node* newNextNode = m_path[m_currentIndex];
                if (newNextNode == nullptr) {
                    std::cerr << "Error: New next node is null." << std::endl;
                    return;
                }

                // Calculate how far the Agent has overshot the node (invert the distance)
                float overshootDistance = -distance;

                // Calculate the new direction vector to the new next node
                glm::vec2 newDirection = newNextNode->position - nextNode->position;
                glm::vec2 newUnitDirection = glm::normalize(newDirection);

                // Move along this vector by the overshoot distance
                m_position += newUnitDirection * overshootDistance;
            }
        }
    }

	void PathAgent::GoToNode(AIForGames::Node* node, NodeMap& nodeMap)
    {
        if (node == nullptr) {
            std::cerr << "Error: Destination node is null." << std::endl;
            return;
        }

        m_path = nodeMap.DijkstrasSearch(m_currentNode, node);
        if (m_path.empty()) {
            std::cerr << "Error: Path is empty. Check if start and end nodes are properly connected." << std::endl;
            return;
        }
        m_currentIndex = 0;
    }

	void PathAgent::Draw()
	{   //Draw Agent - set size and color to yellow
        DrawCircle((int)m_position.x, (int)m_position.y, 8, { 255, 255, 0, 255 });
	}
