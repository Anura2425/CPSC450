#include "shortestPath.h"

std::vector<Matrix> load_matrices(const std::string& filename){

    std::ifstream file(filename);
    std::vector<Matrix> matrices;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open test file" << std::endl;
        return matrices;
    }

    std::string line;
    while (std::getline(file, line)){
        if(line.empty() || line == "~") continue;
        if(line == "END") break;

        // n is the size of the matrix (first number in the test files above the actual matrices)
        int n = std::stoi(line);
        Matrix matrix (n, std::vector<int>(n,0));

        // read in n rows
        for(int i = 0; i < n; ++i){
            if(std::getline(file,line)){
                std::stringstream ss(line);
                for (int j = 0; j < n; ++j){
                    ss >> matrix[i][j];
                }
            }
        }
        matrices.push_back(matrix);
    }
    file.close();
    return matrices;
}

std::vector<Graph> load_graphs(const std::string& filename){
    std::ifstream file(filename);
    std::vector<Graph> graphs;

    if (!file.is_open()){
        std::cerr << "Error: could not open test file";
        return graphs;
    }

    std::string line;
    while (std::getline(file, line)){
        if(line.empty() || line == "~") continue;
        if(line == "END") break;

        int n = std::stoi(line);
        Graph graph(n);

        for(int i = 0; i < n; ++i){
            if (std::getline(file,line)){
                std::stringstream ss(line);
                for (int j = 0; j < n; ++j){
                    int weight;
                    ss >> weight;
                    if (weight!=0){
                        graph[i].push_back({j,weight});
                    }
                }
            }
        }
        graphs.push_back(graph);
    }
    file.close();
    return graphs;
}

int output_list(const std::vector<int>& dep_list, const std::string& outfile){
    std::ostream* out = &std::cout;
    std::ofstream file_out;

    if(!outfile.empty()){
        file_out.open(outfile, std::ios::app);
        if(file_out.is_open()){
            out = &file_out;
        }
    }

    for(size_t i = 0; i < dep_list.size(); ++i){
        *out << dep_list[i];
        if (i + 1 < dep_list.size()){
            *out << ",";
        }
    }
    *out << "\n";
    return 0;
}

std::vector<int> shortest_path(const Graph& graph, int start_node){
    int n = graph.size();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    using Element = std::pair<int, int>;
    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> pq;
    
    dist[start_node] = 0;
    pq.push({0, start_node});
    while(!pq.empty()){
        auto [d,u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]){
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight< dist[v]){
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
