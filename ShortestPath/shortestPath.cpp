#include "shortestPath.h"

using Edge = std::pair<int, int>;
using Graph = std::vector<std::vector<Edge>>;

std::vector<int> load_matrix(std::string filename){

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open test file" << std::endl;
        return;
    }

    char ch;
    std::vector<std::vector<int>> temp_matrix;
    while(!file.eof()){

        if(ch == '~'){
            // new test matrix (return and clear the last)
            temp_matrix.clear();
        } else if(std::isdigit(static_cast<unsigned char>(ch))){
            
        }
    }

    file.close();

    std::vector<int> adj_matrix = {0, 1, 2}; // dummy
    return adj_matrix;
}


int output_list(std::vector<int> dep_list, std::string outfile){
    for (int i = 0; i < dep_list.size(); ++i){
        std::cout << dep_list.at(i);
        if (i == dep_list.size() - 1){
            std::cout << "\n";
            break;
        }
        std::cout << ", ";
    }
    return 0;
}

std::vector<int> solve(){
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // min heap for node process order (stores edge weights)

    return {123};
}
