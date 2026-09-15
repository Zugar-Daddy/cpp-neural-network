#include "Layers.h"
#include "Loader.h"
#include "Matrix.h"

int main(){
    Loader loader;
    loader.LoadFile();

    DenseLayer layer1(784, 128);
    DenseLayer layer2(128, 10);

    vector<vector<double>> img;

    for(int i = 0; i < 784; i++){
        img.push_back({loader.normalized_images[i]});
    }

    Matrix img_1(784, 1, img);

    Matrix a1 = layer1.forward(img_1, ACTIVATION_FUNCTION::ReLU);
    Matrix a2 = layer2.forward(a1, ACTIVATION_FUNCTION::SoftMax);

    for(auto it: a2.matrix){
        for(auto itt: it){
            cout << itt << ' ';
        }
        cout << '\n';
    }
    return 0;
}