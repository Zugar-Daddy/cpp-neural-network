#include "Tester.h"

int main(){
    Loader loader;
    loader.LoadTrainFile();

    DenseLayer layer1(784, 128);
    DenseLayer layer2(128, 10);

    Trainer::Train(loader, layer1, layer2, 60000);

    Tester tester;
    tester.Test(layer1, layer2);

    return 0;
}