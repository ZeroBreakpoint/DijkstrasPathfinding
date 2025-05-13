#include "Pathfinding.h"

// Connect this node to another with a specified cost (used to build the graph)
void AIForGames::Node::ConnectTo(Node* other, float cost)
{
    connections.push_back(Edge(other, cost));
}
