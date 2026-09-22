#pragma once

#include <cfloat>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>
#include <algorithm>

class Matrix{

    int row, col = 0;

public:

    // matrix [row][col]
    std::vector<std::vector<double>> matrix;
    
    int getRow() {return row;}
    int getCol() {return col;}

    Matrix(){row = 0; col = 0;}

    Matrix(int r, int c, std::vector<std::vector<double>> mat = {}){
        this->row = r;
        this->col = c;

        if(r == 0 || c == 0) return;

        if(mat.empty()){
            matrix.resize(row, std::vector<double>(col, 0.0));
        }
        else{
            matrix = mat;
        }
        
    }

    static Matrix Multiply(const Matrix& m1, const Matrix& m2, bool elementWise = false){
        int row1 = m1.row, col1 = m1.col, row2 = m2.row, col2 = m2.col;

        if(!elementWise){
            if(col1 != row2){
                throw std::invalid_argument("Invalid Multiplication");
            }
            
            Matrix result(row1, col2);
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
                throw std::invalid_argument("Invalid Multiplication");
            }

            Matrix result(row1, col1);
            for(int i = 0; i < col1; i++){
                for(int j = 0; j < row1; j++){
                    result.matrix[i][j] = m1.matrix[i][j] * m2.matrix[i][j];
                }
            }

            return result;
        }
    }

    static Matrix Multiply(double c, const Matrix& m){
        Matrix result(m.row, m.col);

        for(int i = 0; i < m.row; i++){
            for(int j = 0; j < m.col; j++){
                result.matrix[i][j] = m.matrix[i][j] * c;
            }
        }

        return result;
    }

    static Matrix Add(const Matrix& m1, const Matrix& m2){
        int n1 = m1.row, n2 = m1.col, mm1 = m2.row, mm2 = m2.col;

        if(n1 != mm1 || n2 != mm2){
            throw std::invalid_argument("Invalid Multiplication");
        }
        
        Matrix result(m1.row, m1.col);

        for(int i = 0; i < n1; i++){
            for(int j = 0; j < n2; j++){
                result.matrix[i][j] = (m1.matrix[i][j] + m2.matrix[i][j]);
            }
        }

        return result;
    }

    static Matrix Sub(const Matrix& m1, const Matrix& m2){
        int n1 = m1.row, n2 = m1.col, mm1 = m2.row, mm2 = m2.col;

        if(n1 != mm1 || n2 != mm2){
            throw std::invalid_argument("Invalid Subtraction");
        }
        
        Matrix result(m1.row, m1.col);

        for(int i = 0; i < n1; i++){
            for(int j = 0; j < n2; j++){
                result.matrix[i][j] = (m1.matrix[i][j] - m2.matrix[i][j]);
            }
        }

        return result;
    }

    static Matrix Transpose(const Matrix& m){
        Matrix result(m.col, m.row);

        for(int i = 0; i < m.col; i++){
            for(int j = 0; j < m.row; j++){
                result.matrix[i][j] = m.matrix[j][i];
            }
        }
        
        return result;
    }

    static Matrix Apply_ReLU(const Matrix& m){
        Matrix result(m.row, m.col);
        for(int i = 0; i < m.row; i++){
            for(int j = 0; j < m.col; j++){
                result.matrix[i][j] = std::max(0.0, m.matrix[i][j]);
            }
        }
        return result;
    }



    static Matrix Apply_SoftMax(const Matrix& m){

        int r = m.row, c = m.col;
        Matrix result(r, c);

        // ez/(summation ez) = e(z - M)/(summation e(z - M))

        // finding M
        double maxi = -DBL_MAX;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                maxi = std::max(m.matrix[i][j], maxi);                
            }
        }

        // now storing everything in result as exp(z - M) and keeping track of their sum as well
        double sum = 0;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                double val = std::exp(m.matrix[i][j] - maxi);
                result.matrix[i][j] = val;
                sum += val;
            }
        }

        // dividing everything
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                result.matrix[i][j] /= sum;
            }
        }


        return result;
    }
};