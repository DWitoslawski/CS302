/******************************************************************************
 Name: Daniel Witoslawski
 NSHE ID: 2000889468
 Assignment 7: Create a program that can take a graph that represents a path
    through campus, and determine if that graph is traversable from a given
    start node to a given end node within a pre-determined number of weight units.
 Input: Txt files that have a start node, end node, given stamina (weight max) and
    a list nodes and edge weights.
 Output: Print out "Time to cool off!" as well as a viable path within the stamina
    weight limit if one exists. Print "This is going to be a long summer..." if
    no viable path within the stamina limit exists.
 *******************************************************************************/

#include <iostream>
#include <list>
#include <unordered_map>

struct vertexType
{
    std::string building;
    int distance;
};

/*
 * Recursive function that traverses the graph in a dfs-like manner with some adjustments.
 * If the function reaches the end node with stamina left, then the function returns true.
 * As the predecessor list passed in was a reference variable, it will be updated as the
 * list is traversed, and it will represent a final path when the end node is reached. If
 * we are not at the end node, then we will loop through all the neighbors of the current
 * node (stored in adjList). If the neighbor's stored weight value in visitedMap is less
 * than the current node's weight minus the edge weight, then we will update the neighbor
 * node with a new weight (visited) and update the predecessor map of the neighbor. Once
 * the updates have been made, we will call pathFinder recursively on the neighbor. If we
 * reach the end node, true is returned. If not, false is returned. This function will
 * recursively traverse through every node that is in the path starting from startNode.
 */
bool pathFinder(const std::string & currentNode, const std::string & endNode, int & stamina,
                std::unordered_map< std::string, std::list<vertexType> > & adjList,
                std::unordered_map<std::string, std::string> & predecessor,
                std::unordered_map<std::string, int> & visited)
{

    if (currentNode == endNode)
        return true;

    for (auto const & neighbor : adjList[currentNode])
    {
        if (visited[neighbor.building] < visited[currentNode] - neighbor.distance && visited[currentNode] - neighbor.distance > 0)
        {
            predecessor[neighbor.building] = currentNode;
            visited[neighbor.building] = visited[currentNode] - neighbor.distance;

            if (pathFinder(neighbor.building, endNode, stamina, adjList, predecessor, visited))
                return true;
        }
    }

    return false;
}

int main() {

    // Adjacency list that stores neighbor building and distance values associated with each building.
    std::unordered_map< std::string, std::list<vertexType> > adjList;

    // Predecessor map that updates to contain the best predecessor of each building node in the graph.
    std::unordered_map< std::string, std::string > predecessor;

    // Visited map that stores an int value to represent the current weight value.
    // It will be updated to hold the highest (best) weight value.
    std::unordered_map< std::string, int > visited;

    // Will store the proper path in order based on the predecessor map.
    std::list<std::string> path;

    std::string startNode, endNode, to, from;
    int stamina, distance;

    std::cin >> startNode >> endNode >> stamina;

    // Start with the max weight that we will have (stamina value). The value will
    // decrease as each edge is processed until endNode or 0 is reached.
    visited[startNode] = stamina;

    // Loop to populate the adjacency list with all neighbors of each node based on input file data.
    while (!std::cin.eof())
    {
        std::cin >> from >> to >> distance;
        adjList[from].push_back({to, distance});
    }

    // The pathFinder function will output true if a valid path to the endNode is reached with at least
    // 1 stamina. In that case, predecessor will have been updated properly as each edge was processed.
    if (pathFinder(startNode, endNode, stamina, adjList, predecessor, visited))
    {
        // Loop that will store the valid path into pathList in reverse order (from end node through
        // predecessor map until start node is reached).
        while (!endNode.empty())
        {
            path.push_back(endNode);
            endNode = predecessor[endNode];
        }
        std::cout << "Time to cool off!" << std::endl;
        std::cout << "Path: ";

        // Loop that will output then pop off the last item in the pathList (LIFO) to print a path
        // in order from start to finish.
        for( ; !path.empty(); path.pop_back())
            std::cout << " " << path.back();
    }
    else
        std::cout << "This is going to be a long summer..." << std::endl;


    return 0;
}
