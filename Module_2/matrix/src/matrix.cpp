#include <iostream>
#include <vector>
#include "matrix.hpp"

Matrix ReadMatrix(int n){
    if(n > 0)
    {
        Matrix m(n, std::vector<int> (n));
        for(auto& i: m)
        for(auto& j:i)
        std::cin >> j;
        return m;
    }
}

Matrix Rotate90Deg(const Matrix &m){
    int row = m.size();
    int col = m[0].size();
    Matrix r(row, std::vector<int> (col));
    for(int i = 0; i<row;i++)
    for(int j = 0; j<row;j++)
    r[i][j] = m[row-j-1][i];
    return r;
}

void Print(const Matrix &m){
    for(unsigned int i = 0; i < m.size(); i++){
        for(unsigned int j = 0; j < m[i].size(); j++){
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}