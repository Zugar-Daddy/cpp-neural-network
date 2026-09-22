#pragma once

#include "Matrix.h"
#include <random>

enum ACTIVATION_FUNCTION{
    ReLU,
    SoftMax
};

class DenseLayer {
public:
    // Parameters (trainable)
    Matrix weights;  // shape: (outputs x inputs)
    Matrix biases;   // shape: (outputs x 1)

    // Gradients (computed during backward pass)
    Matrix d_weights;
    Matrix d_biases;

    // Cache (saved during forward pass for backprop)
    Matrix z;           
    Matrix a;           

    DenseLayer(int in_features, int out_features) 
        : weights(out_features, in_features),
          biases(out_features, 1)
    {
        randomizeWeightsAndBiases(in_features);    
    }

    void randomizeWeightsAndBiases(int in_features){
        std::mt19937 generator(std::random_device{}());
        std::normal_distribution<double> dist(0.0, std::sqrt(2.0 / in_features));
        
        for(auto& it: weights.matrix){
            int n = it.size();
            for(auto& itt: it){
                itt = dist(generator);
            }
        }        
    }

    Matrix forward(Matrix& inp, ACTIVATION_FUNCTION Function){
        z = Matrix::Add(Matrix::Multiply(weights, inp), biases);

        if(Function == ACTIVATION_FUNCTION::SoftMax){
            a = Matrix::Apply_SoftMax(z);
        }
        else{
            a = Matrix::Apply_ReLU(z);
        }

        return a;
    }
};