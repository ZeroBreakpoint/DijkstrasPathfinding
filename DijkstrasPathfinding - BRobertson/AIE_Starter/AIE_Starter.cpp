#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"
#include "Pathfinding.h"
#include "NodeMap.h"
#include "PathAgent.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>

using namespace AIForGames;

int main(int argc, char* argv[])
{
    int screenWidth = 800;
    int screenHeight = 450;
    
    //Initialise the application window with the above dimensions
    InitWindow(screenWidth, screenHeight, "Artificial Intelligence For Games - Assessment 2 - Bradley Robertson");

    SetTargetFPS(60);

    // ASCII Art Map
    std::vector<std::string> asciiMap = {
        "000000000000",
        "010111011100",
        "010101110110",
        "011100000010",
        "010111111110",
        "010000001000",
        "011111111110",
        "000000000000"
    };

    // Instantiate NodeMap and Initialize
    NodeMap nodeMap;
    nodeMap.Initialise(asciiMap, 50);

    // Get start and end nodes
    Node* startNode = nodeMap.GetNode(1, 1);
    Node* endNode = nodeMap.GetNode(10, 2);

    // Instantiate PathAgent and set its initial position
    PathAgent agent;
    agent.SetNode(startNode);
    agent.SetSpeed(64);

    // Perform Dijkstra's search
    std::vector<Node*> nodeMapPath = nodeMap.DijkstrasSearch(startNode, endNode);

    // Set the agent's path
    agent.GoToNode(endNode, nodeMap);

    float time = (float)GetTime();
    float deltaTime;
    Color lineColor = WHITE;

    // Main application loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Calculate deltaTime
        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;

        // Update agent
        agent.Update(deltaTime);

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the map and the paths
        nodeMap.Draw();
        nodeMap.DrawPath(nodeMapPath, lineColor);
        agent.Draw();  // Draw the agent as a yellow circle

        // Handle mouse input for setting start and end nodes
        if (IsMouseButtonPressed(0))  // Left click to set start node
        {
            Vector2 mousePos = GetMousePosition();
            startNode = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            if (startNode != nullptr && endNode != nullptr) {
                nodeMapPath = nodeMap.DijkstrasSearch(startNode, endNode);
                agent.SetNode(startNode); // Update agent's position to the new start node
                agent.GoToNode(endNode, nodeMap); // Set the agent's path to the end node
            }
        }

        if (IsMouseButtonPressed(1))  // Right click to set end node
        {
            Vector2 mousePos = GetMousePosition();
            endNode = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            if (startNode != nullptr && endNode != nullptr) {
                nodeMapPath = nodeMap.DijkstrasSearch(startNode, endNode);
                agent.GoToNode(endNode, nodeMap); // Update agent's path to the new end node
            }
        }

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}