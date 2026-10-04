#include "Tester.h"
#include "WeightIO.h"

int main(){
    Loader loader;
    loader.LoadTrainFile();

    DenseLayer layer1(784, 128);
    DenseLayer layer2(128, 10);

    // Trainer::Train(loader, layer1, layer2, 20);

    weightIO::ReadWeights("layer1", layer1.weights.matrix);
    weightIO::ReadWeights("biases1", layer1.biases.matrix);
    weightIO::ReadWeights("layer2", layer2.weights.matrix);
    weightIO::ReadWeights("biases2", layer2.biases.matrix);

    Tester tester;
    tester.Test(layer1, layer2);



    // weightIO::WriteWeights("layer1", layer1.weights.matrix);
    // weightIO::WriteWeights("biases1", layer1.biases.matrix);
    // weightIO::WriteWeights("layer2", layer2.weights.matrix);
    // weightIO::WriteWeights("biases2", layer2.biases.matrix);



    return 0;
}