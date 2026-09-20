#include "Layers.h"
#include "Loader.h"
#include "Matrix.h"

void PrintMatrix(std::vector<std::vector<double>> mat){
    for(auto it: mat){
        for(auto itt: it){
            std::cout << itt << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main(){
    Loader loader;
    loader.LoadFile();

    DenseLayer layer1(784, 128);
    DenseLayer layer2(128, 10);

    std::vector<std::vector<double>> img;

    for(int i = 0; i < 784; i++){
        img.push_back({loader.normalized_images[i]});
    }

    Matrix img_1(784, 1, img);
    Matrix lbl_img_1(10, 1);
    lbl_img_1.matrix[(int)(unsigned char) loader.label_exact[0]][0] = 1;
    std::cout << "image is: " << (int)(unsigned char) loader.label_exact[0] << '\n';

    // First pass
    Matrix a1 = layer1.forward(img_1, ACTIVATION_FUNCTION::ReLU);
    Matrix a2 = layer2.forward(a1, ACTIVATION_FUNCTION::SoftMax);

    PrintMatrix(a2.matrix);







    // Since we're using softmax, we're pairing it with "Categorical Cross-Entropy"
    // Cost is (-Summation(yk ln(ak[i])))
    
    // The derivative of Cost wrt z[L] = a[L] - y
    Matrix dz2 = Matrix::Sub(a2, lbl_img_1);

    // anything wiht d, means "derivative of the Cost function wrt this variable"

    // The Chain rule we learnt in the video had three terms
    // dellC/ dellW = (dellC / dell a[L]) * (dell a[L] / dell z[L]) * (dell z[L] / dell w[L])    
    // this can be denoted as "dW"
    
    // also, the derivative of z[L] wrt weights = a[L - 1]
    // Dell C/ Dell z[L] = a[L] - y

    // The gradient of a weight is
    // dell C / dell W [of layer 2] = error * Transpose(incoming activation)
    // *****************This just means dW[L] = dz[L] * a[L - 1]************************

    // dz is (10 x 1), and the incoming activation for previous layer a[1]T is (1 x 128). Now dW is (10 x 128)
    Matrix a1T = Matrix::Transpose(a1);
    Matrix dW2 = Matrix::Multiply(dz2, a1T);

    // well that's because (Dell Z / Dell B) is 1
    Matrix db2 = dz2;


    // Now we push the blame back futher
    // z[2] = W[2] * a[2] + b[2]
    // (Dell z[2] / Dell a[1]) = W[2]

    // now da[1] = Transpose(W[2]) * dz[2]    
    // layer2 had 128 in features and 10 out features, then weights is (10 x 128)
    Matrix dW2T = Matrix::Transpose(layer2.weights); 
    Matrix da1 = Matrix::Multiply(dW2T, dz2); // (128 x 10) * (10 x 1) = (128 x 1)

    // Now dz[1] = da[1] * ReLU'(z[1]), where ReLU'(z) = {1 if z > 0, 0 if z <= 0}
    // In layers, a = ReLU(z). That's what this main is storing
    // z -> a we go with ReLU, dz <- da we come with ReLU
    // now this da1 which has come, we check for each element if it's creator z was positive or not, we'll only keep this value if it's from a positive z

    // now we check the z's, basically doing ReLU'(z)
    Matrix dz1 = da1; // (128 x 1)
    for(int i = 0; i < 128; i++){
        if(layer1.z.matrix[i][0] <= 0) dz1.matrix[i][0] = 0;
    }

    // (1 x 784)
    Matrix a0T = Matrix::Transpose(img_1);
    Matrix dW1 = Matrix::Multiply(dz1, a0T); // (128 x 1) * (1 x 784)
    Matrix db1 = dz1;


    // Training
    double alpha = 0.01;
    // Layer 2
    Matrix alphaDW2 = Matrix::Multiply(alpha, dW2);
    layer2.weights = Matrix::Sub(layer2.weights, alphaDW2);
    Matrix alphaDB2 = Matrix::Multiply(alpha, db2);
    layer2.biases  = Matrix::Sub(layer2.biases,  alphaDB2);

    // Layer 1
    Matrix alphaDW1 = Matrix::Multiply(alpha, dW1);
    layer1.weights = Matrix::Sub(layer1.weights, alphaDW1);
    Matrix alphaDB1 = Matrix::Multiply(alpha, db1);
    layer1.biases  = Matrix::Sub(layer1.biases,  alphaDB1);






    // checking after applying changes
    a1 = layer1.forward(img_1, ACTIVATION_FUNCTION::ReLU);
    a2 = layer2.forward(a1, ACTIVATION_FUNCTION::SoftMax);

    PrintMatrix(a2.matrix);

    return 0;
}