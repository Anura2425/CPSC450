#include "shortestPath.h"

int main(){

    // clear output files just in case since my write function appends and doesnt truncate/overwrite ever
    std::ofstream("testoutput1.txt");
    std::ofstream("testoutput2.txt");
    std::ofstream("testoutput3.txt");
    std::ofstream("testoutput4.txt");
    generate_test_file("test4.txt", 3, 100, 20, 0.3);

    //test 1
    std::vector<Graph> test1_graphs = load_graphs("test1.txt");

    for(const Graph& graph : test1_graphs){
        std::vector<int> dep_list = shortest_path(graph);
        output_list(dep_list, "testoutput1.txt");
    }

    //test 2 
    std::vector<Graph> test2_graphs = load_graphs("test2.txt");
    for(const Graph& graph : test2_graphs){
        std::vector<int> dep_list = shortest_path(graph);
        output_list(dep_list, "testoutput2.txt");
    }

    //test 3 
    std::vector<Graph> test3_graphs = load_graphs("test3.txt");
    for(const Graph& graph : test3_graphs){
        std::vector<int> dep_list = shortest_path(graph);
        output_list(dep_list, "testoutput3.txt");
    }   

    //test 4: 100x100 large graph test for fun
    std::vector<Graph> test4_graphs = load_graphs("test4.txt");
    for(const Graph& graph : test4_graphs){
        std::vector<int> dep_list = shortest_path(graph);
        output_list(dep_list, "testoutput4.txt");
    }

    return 0;
}