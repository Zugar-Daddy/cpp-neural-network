#include "Trainer.h"

class Tester{
public:

    void Test(DenseLayer& layer1, DenseLayer& layer2){
        Loader loader;
        loader.LoadTestFile();

        int correct = 0;
        int total = 10000;

        for (int start = 0; start < total; start++) {

            // making image
            std::vector<std::vector<double>> img;    
            for(int i = start * 784; i < start * 784 + 784; i++){
                img.push_back({loader.normalized_images[i]});
            }
            Matrix imgM(784, 1, img);

            // forward pass
            Matrix a1 = layer1.forward(imgM, ACTIVATION_FUNCTION::ReLU);
            Matrix a2 = layer2.forward(a1, ACTIVATION_FUNCTION::SoftMax);

            // max prediction wins
            double maxi = -1.0;
            int predicted_idx = 0;
            for(int i = 0; i < 10; i++){
                if(maxi < a2.matrix[i][0]){
                    predicted_idx = i;
                    maxi = a2.matrix[i][0];
                }
            }

            int actual_label = (int)(unsigned char)loader.label_exact[start];
            if (predicted_idx == actual_label) {
                correct++;
            }
        }

        std::cout << "Overall Accuracy: " << (double)correct / total * 100.0 << "%" << std::endl;
        loader.DeleteAllDynamic();
    }
};