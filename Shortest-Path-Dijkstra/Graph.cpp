#include "Graph.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <algorithm>

#define INFINITY 2147483647

// Assignment 4 - Dijkstra's Algorithm
// Uliana Ozerova Driver 50% / Daniel Shultz Navigator 50%
// Dijkstra's Algorithm:
// This algorithm calculates the shortest path from a source node to a destination node in an undirected weighted graph.
// shortestPath will return the total integer sum of the smallest weights for the shortest path graph traversal.

Graph::Graph(){

}

Graph::~Graph(){

}

Edge::Edge(){
    v1 = ""; 
    v2 = "";
    w = 0;
}

void Graph::addVertex(std::string label)
{
    vertex_vector.push_back(label);
}

void Graph::removeVertex(std::string label){
    for(itr = vertex_vector.begin(); itr != vertex_vector.end(); itr++){
        if(*itr == label){
            vertex_vector.erase(itr);
        
            for(itr2 = edge_vector.begin(); itr2 != edge_vector.end(); ){
                if((*itr2)->v1 == label || (*itr2)->v2 == label){
                    edge_vector.erase(itr2);
                }
                else   
                    itr2++;

            }
        }
    }
    return;
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    Edge* newEdge = new Edge(); // construct a new Edge
    newEdge->v1 = label1;
    newEdge->v2 = label2;
    newEdge->w = weight;
    edge_vector.push_back(newEdge); // add the new Edge into the edge vector
}

void Graph::removeEdge(std::string label1, std::string label2){
    for(itr2 = edge_vector.begin(); itr2 != edge_vector.end(); ){
        if((*itr2)->v1 == label1 && (*itr2)->v2 == label2){
            itr2 = edge_vector.erase(itr2);
        }
        else   
            itr2++;
    }
    return;
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){ // Dijkstra's Algorithm
    for(itr = vertex_vector.begin(); itr != vertex_vector.end(); itr++){ // set all vertices to INFINITY, as well as UNVISITED.
        minDistance[*itr] = INFINITY;
        visited[*itr] = "UNVISITED";
    }

    minDistance[startLabel] = 0; // The source vertex is a distance of 0 from itself

    typedef std::pair <size_t, std::string> path_cur;
    std::priority_queue<path_cur, std::vector<path_cur>, std::greater<path_cur>> pqPath; // Priority queue for finding the shortest distance
    pqPath.push(make_pair(0, startLabel));

    while(!pqPath.empty()){ // While the pq is not empty
        std::string stringTemp = pqPath.top().second;
        pqPath.pop(); 
        std::string neighbor;
        for(itr2 = edge_vector.begin(); itr2 != edge_vector.end(); itr2++){ // This graph is undirected, therefore both cases are required.
            if((*itr2)->v1 == stringTemp){ // Shared source vertex, therefore label2 is a neighbor
                neighbor = (*itr2)->v2;
            }
            else if((*itr2)->v2 == stringTemp){ // Shared destination vertex, therefore label1 is a neighbor
                neighbor = (*itr2)->v1;
            }
            else
                continue;
        
        size_t curWeight = (*itr2)->w;
        if((minDistance[stringTemp] + curWeight) < minDistance[neighbor]){ // Relaxation is done on neighbors
            visited[neighbor] = stringTemp; // The current vertex overwrites the "UNVISITED" inside the visited map, becoming the previous vertex.
            minDistance[neighbor] = minDistance[stringTemp] + curWeight;
            pqPath.push(make_pair(minDistance[neighbor], neighbor)); // Adds the compatible neighbor to the priority queue
        }
        }
    }
    std::string destination = endLabel; // endLabel is placed in a destination string
    path.push_back(endLabel); // The end label is added to the path
    std::map<std::string, std::string>::iterator itr4;
    for(itr4 = visited.begin(); itr4 != visited.end(); itr4++){
        if(itr4->second == "UNVISITED") // If a vertex is unvisited, continue
            continue;
        endLabel = visited[endLabel];
        if(endLabel == "UNVISITED")
            break;  
        path.push_back(endLabel); // Adds the previous vertex from the map
    }
    std::reverse(path.begin(), path.end()); // Reverses path

    return minDistance[destination]; // Returns the minimum distance of destination
}

// g++ -std=c++17 -Wall Graph.cpp PP4Test.cpp