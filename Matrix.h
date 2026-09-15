#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;

class Matrix{

    int row, col = 0;

public:

    // matrix [row][col]
    vector<vector<double>> matrix;
    
    int getRow() {return row;}
    int getCol() {return col;}

    Matrix(){row = 0; col = 0;}

    Matrix(int r, int c, bool input, vector<vector<double>> mat = {}){
        this->row = r;
        this->col = c;

        if(r == 0 || c == 0) return;

        if(input){
            matrix.resize(row, vector<double>(col));
            for(int i = 0; i < col; i++){
                for(int j = 0; j < row; j++){
                    std::cin >> matrix[i][j];
                }
            }
        }
        else{
            if(mat.empty()){
                matrix.resize(row, vector<double>(col, 0.0));
            }
            else{
                this->matrix = mat;
            }
        }
    }

    static Matrix Multiply(Matrix& m1, Matrix& m2, bool elementWise = false){
        int row1 = m1.row, col1 = m1.col, row2 = m2.row, col2 = m2.col;

        if(!elementWise){
            if(col1 != row2){
                throw invalid_argument("Invalid Multiplication");
            }
            
            Matrix result(row1, col2, false);
            for(int i = 0; i < row1; i++){
                for(int j = 0; j < col2; j++){
                    double sum = 0.0;
                    for(int k = 0; k < col1; k++){
                        sum += m1.matrix[i][k] * m2.matrix[k][j];
                    }
                    result.matrix[i][j] = sum;
                }
            }

            return result;
        }
        else{
            if (row1 != row2 || col1 != col2){
                throw invalid_argument("Invalid Multiplication");
            }

            Matrix result(row1, col1, false);
            for(int i = 0; i < col1; i++){
                for(int j = 0; j < row1; j++){
                    result.matrix[i][j] = m1.matrix[i][j] * m2.matrix[i][j];
                }
            }

            return result;
        }
    }

    static Matrix Multiply(double c, Matrix& m){
        Matrix result(m.row, m.col, false);

        for(int i = 0; i < m.row; i++){
            for(int j = 0; j < m.col; j++){
                result.matrix[i][j] = m.matrix[i][j] * c;
            }
        }

        return result;
    }

    static Matrix Add(Matrix& m1, Matrix& m2){
        int n1 = m1.row, n2 = m1.col, mm1 = m2.row, mm2 = m2.col;

        if(n1 != mm1 || n2 != mm2){
            throw invalid_argument("Invalid Multiplication");
        }
        
        Matrix result(m1.row, m1.col, false);

        for(int i = 0; i < n1; i++){
            for(int j = 0; j < n2; j++){
                result.matrix[i][j] = (m1.matrix[i][j] + m2.matrix[i][j]);
            }
        }

        return result;
    }

    static Matrix Sub(Matrix& m1, Matrix& m2){
        int n1 = m1.row, n2 = m1.col, mm1 = m2.row, mm2 = m2.col;

        if(n1 != mm1 || n2 != mm2){
            throw invalid_argument("Invalid Multiplication");
        }
        
        Matrix result(m1.row, m1.col, false);

        for(int i = 0; i < n1; i++){
            for(int j = 0; j < n2; j++){
                result.matrix[i][j] = (m1.matrix[i][j] - m2.matrix[i][j]);
            }
        }

        return result;
    }

    static Matrix Transpose(Matrix& m){
        Matrix result(m.col, m.row, false);

        for(int i = 0; i < m.row; i++){
            for(int j = 0; j < m.col; j++){
                result.matrix[i][j] = m.matrix[j][i];
            }
        }
        
        return result;
    }
    
};