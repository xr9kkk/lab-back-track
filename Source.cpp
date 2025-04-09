#include <iostream>
#include <fstream>
#include <vector>
#include <string>



void dfs(int v, const std::vector<std::vector<int>>& adjacency_matrix, std::vector<bool>& visited) {
    visited[v] = true;

    for (int i = 0; i < adjacency_matrix.size(); ++i) {
        if (adjacency_matrix[v][i] == 1 && !visited[i]) {
            dfs(i, adjacency_matrix, visited);
        }
    }
}


bool is_connected(const std::vector<std::vector<int>>& adjacency_matrix) {
    int n = adjacency_matrix.size();
    std::vector<bool> visited(n, false);

    dfs(0, adjacency_matrix, visited);

    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}
  

std::vector<std::vector<int>> load_adjacency_matrix(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> matrix;
    std::string line;

    while (getline(file, line)) {
        std::vector<int> row;
        int num;
        size_t pos = 0;
        while (pos < line.length()) {
            if (isdigit(line[pos])) {
                num = line[pos] - '0';
                row.push_back(num);
            }
            ++pos;
        }
        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

int main() {
    setlocale(LC_ALL, "ru");
    std::string filename = "graph.txt";
    std::vector<std::vector<int>> adjacency_matrix = load_adjacency_matrix(filename);

    if (adjacency_matrix.empty()) {
        std::cout << "Ошибка: матрица не загружена.\n";
        return 1;
    }

    if (is_connected(adjacency_matrix)) {
        std::cout << "Граф связный.\n";
    }
    else {
        std::cout << "Граф не связный.\n";
    }

    return 0;
}
