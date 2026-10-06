#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>
#include <functional>
#include <cctype>
#include <string>

using Matrix = std::vector<std::vector<int>>;
using Edge = std::pair<int, int>;              // {neighbor_node, weight}
using Graph = std::vector<std::vector<Edge>>;  // adj list

// loads all adjacency matrices from the file
std::vector<Matrix> load_matrix(const std::string& filename);

// converts directly to Adjacency List graphs
std::vector<Graph> load_graphs(const std::string& filename);

// output helper for testanswers 
int output_list(const std::vector<int>& dep_list, const std::string& outfile);

// solves shortest path for a graph starting at source node 0
std::vector<int> shortest_path(const Graph& graph, int start_node = 0);