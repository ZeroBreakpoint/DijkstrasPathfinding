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

    // Initialises the window with specified dimensions and title
    InitWindow(screenWidth, screenHeight, "DijkstrasSearch Pathfinding - Bradley Robertson");
    SetTargetFPS(120); // Cap the frame rate to 120 FPS

    // Define a simple ASCII map where '0' is walkable and '1' is a wall
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

    // Create and initialise the node map using the ASCII layout
    NodeMap nodeMap;
    nodeMap.Initialise(asciiMap, 50); // 50 pixels per cell

    // Set the initial start and end nodes
    Node* startNode = nodeMap.GetNode(1, 1);
    Node* endNode = nodeMap.GetNode(10, 2);

    // Create the pathfinding agent and place it at the start node
    PathAgent agent;
    agent.SetNode(startNode);
    agent.SetSpeed(64); // Agent movement speed in pixels per second

    // Request the A* path from start to end node
    std::vector<Node*> nodeMapPath = nodeMap.DijkstrasSearch(startNode, endNode);
    agent.GoToNode(endNode, nodeMap);

    float time = (float)GetTime();
    float deltaTime;
    Color lineColour = WHITE; // Colour used to draw the path line

    // Main application loop - runs until the user closes the window
    while (!WindowShouldClose())
    {
        // Calculate how much time has passed since last frame
        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;

        // Update agent movement along the path
        agent.Update(deltaTime);

        // Start drawing
        BeginDrawing();
        ClearBackground(BLACK); // Clear screen to black

        // Draw the grid, path and the agent
        nodeMap.Draw();
        nodeMap.DrawPath(nodeMapPath, lineColour);
        agent.Draw();

        // Left mouse click: choose a new start node
        if (IsMouseButtonPressed(0))
        {
            Vector2 mousePos = GetMousePosition();
            startNode = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            if (startNode && endNode) {
                nodeMapPath = nodeMap.DijkstrasSearch(startNode, endNode);
                agent.SetNode(startNode);
                agent.GoToNode(endNode, nodeMap);
            }
        }

        // Right mouse click: choose a new end node
        if (IsMouseButtonPressed(1))
        {
            Vector2 mousePos = GetMousePosition();
            endNode = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            if (startNode && endNode) {
                nodeMapPath = nodeMap.DijkstrasSearch(startNode, endNode);
                agent.GoToNode(endNode, nodeMap);
            }
        }

        EndDrawing();
    }

    // Cleanup and close the application
    CloseWindow();
    return 0;
}
