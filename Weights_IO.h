#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "Layers.h"

enum Read_Write_Mode{
    Read,
    Write
};

class weightIO {

    static bool WriteWeights(const std::string& file, const std::vector<std::vector<double>>& mat){
        std::ofstream outFile(file);
    
        if (!outFile.is_open()){
            std::cerr << "Error: File can't be written: " << file << '\n';
            return false;
        }

        int row = mat.size();
        int col = mat[0].size();

        outFile << row << '\n' << col << '\n';

        for (auto it : mat){
            for (auto val: it) {
                outFile << val << '\n';
            }
        }

        outFile.close();
        return true;
    }

    static bool ReadWeights(const std::string& file, std::vector<std::vector<double>>& mat){
        std::ifstream inFile(file);

        if (!inFile.is_open()){
            std::cerr << "Error: File didn't open: " << file << '\n';
            return false;
        }

        int rows, cols;
        inFile >> rows >> cols;

        mat.resize(rows, std::vector<double>(cols));
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(!(inFile >> mat[i][j])){
                    std::cerr << "Error: File can't be read: " << file << '\n';
                    return false;
                }
            }
        }
        
        inFile.close();
        return true;
    }

public:
    weightIO() = delete;
    weightIO operator=(weightIO&) = delete;

    static void IO_Layer(std::vector<DenseLayer>& layers, Read_Write_Mode mode){
        if(mode == Read_Write_Mode::Read){
            for(int i = 0; i < layers.size(); i++){
                ReadWeights("layer" + std::to_string(i + 1), layers[i].weights.matrix);    
                ReadWeights("biases" + std::to_string(i + 1), layers[i].biases.matrix);    
            }
        }
        else{
            for(int i = 0; i < layers.size(); i++){
                WriteWeights("layer" + std::to_string(i + 1), layers[i].weights.matrix);    
                WriteWeights("biases" + std::to_string(i + 1), layers[i].biases.matrix);    
            }
        }
    }
};