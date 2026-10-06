#include "shortestPath.h"

int main(){

    std::vector<int> test = {0, 1, 2};
    

    std::cout << "Test 1: \n------------------------------------------------------------------------------" << std::endl;
    std::vector<std::vector<int>> test_matrices = load_matrix("test1");
    output_list(test, "testoutput1.txt");    

    return 0;
}