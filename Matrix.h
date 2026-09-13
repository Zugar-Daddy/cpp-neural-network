#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Matrix{
    int row, col = 0;

    // each vector is a column
    vector<vector<double>> matrix;

    Matrix(int r, int c, bool input, vector<vector<double>> mat = {}){
        this->row = r;
        this->col = c;

        if(r == 0 && c == 0) return;

        if(input){
            for(int i = 0; i < col; i++){
                this->matrix.push_back({});
                for(int j = 0; j < row; j++){
                    std::cin >> matrix[i][j];
                }
            }
        }
        else{
            this->matrix = mat;
        }
    }

    static Matrix Multiply(Matrix& m1, Matrix& m2, bool elementWise = false){
        int row1 = m1.row, col1 = m1.col, row2 = m2.row, col2 = m2.col;
        vector<vector<double>> mat;

        if(!elementWise){
            if(col1 != row2){
                cout << "Invalid Multiplication" << '\n';
                return Matrix(0, 0, false);
            }
            

            for(int i = 0; i < col2; i++){
                mat.push_back({});
                double sum = 0;
                for(int j = 0; j < row1; j++){
                    sum += m1.matrix[i][j] * m2.matrix[j][i];
                }
                mat[i].push_back(sum);
            }

            return Matrix(col1, col1, false, mat);
        }
        else{
            if (row1 != row2 || col1 != col2){
                cout << "Invalid Multiplication" << '\n';
                return Matrix(0, 0, false);
            }

            for(int i = 0; i < col1; i++){
                mat.push_back({});
                for(int j = 0; j < row1; j++){
                    mat[i][j] = m1.matrix[i][j] * m2.matrix[i][j];
                }
            }

            return Matrix(row1, col1, false, mat);
        }
    }

    static Matrix Multiply(double c, Matrix& m){
        vector<vector<double>> mat;

        for(int i = 0; i < m.row; i++){
            mat.push_back({});
            for(int j = 0; j < m.col; j++){
                mat[i].push_back(m.matrix[i][j] * c);
            }
        }

        return Matrix(m.row, m.col, false, mat);
    }

    static Matrix Add(Matrix& m1, Matrix& m2){
        int n1 = m1.row, n2 = m1.col, mm1 = m2.row, mm2 = m2.col;

        if(n1 != mm1 || n2 != mm2){
            cout << "Invalid Matrix Addition" << '\n';
            return Matrix(0, 0, false);
        }
        
        vector<vector<double>> mat;

        for(int i = 0; i < n1; i++){
            mat.push_back({});
            for(int j = 0; j < n2; j++){
                mat[i].push_back(m1.matrix[i][j] + m2.matrix[i][j]);
            }
        }

        return Matrix(n1, n2, false, mat);
    }

    static Matrix Sub(Matrix& m1, Matrix& m2){
        int n1 = m1.row, n2 = m1.col, mm1 = m2.row, mm2 = m2.col;

        if(n1 != mm1 || n2 != mm2){
            cout << "Invalid Matrix Addition" << '\n';
            return Matrix(0, 0, false);
        }
        
        vector<vector<double>> mat;

        for(int i = 0; i < n1; i++){
            mat.push_back({});
            for(int j = 0; j < n2; j++){
                mat[i].push_back(m1.matrix[i][j] - m2.matrix[i][j]);
            }
        }

        return Matrix(n1, n2, false, mat);
    }

    static Matrix Transpose(Matrix& m){
        vector<vector<double>> mat = m.matrix;
        for(auto it: mat){
            reverse(it.begin(), it.end());
        }
        reverse(mat.begin(), mat.end());

        return Matrix(m.row, m.col, false, mat);
    }
    
};