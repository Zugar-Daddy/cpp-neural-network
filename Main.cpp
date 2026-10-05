#include "Tester.h"
#include "Trainer.h"
#include "Weights_IO.h"


int main(){
    // Loader loader;
    // loader.LoadDataSet(train_images_digits, train_labels_digits);

    std::vector<DenseLayer> layers = {DenseLayer(784,128), DenseLayer(128, 10)};

    // Trainer::Train(loader, layers, 20);
    // weightIO::IO_Layer(layers, Read_Write_Mode::Write);
    

    weightIO::IO_Layer(layers, Read_Write_Mode::Read);
    Tester tester;
    tester.Test(layers);

    return 0;
}