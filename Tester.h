#include "Loader.h"
#include "Layers.h"

class Tester{
public:

    void Test(std::vector<DenseLayer>& layers){
        Loader loader;
        loader.LoadDataSet(test_images_digits, test_labels_digits);
        // loader.LoadDataSet(test_images_letters, test_labels_letters);

        int correct = 0;
        int total = loader.total_images;

        for (int start = 0; start < total; start++) {

            // making image
            std::vector<std::vector<double>> img;    
            for(int i = start * loader.image_dim; i < start * loader.image_dim + loader.image_dim; i++){
                img.push_back({loader.normalized_images[i]});
            }
            Matrix imgM(loader.image_dim, 1, img);

            // forward pass
            int n = layers.size();
            Matrix a = layers[0].forward(imgM, ACTIVATION_FUNCTION::ReLU);
            for(int i = 0; i < n - 1; i++){
                a = layers[i].forward(imgM, ACTIVATION_FUNCTION::ReLU);
            }
            Matrix a_n = layers[n - 1].forward(a, ACTIVATION_FUNCTION::SoftMax);

            // max prediction wins
            double maxi = -1.0;
            int predicted_idx = 0;
            for(int i = 0; i < 10; i++){
                if(maxi < a_n.matrix[i][0]){
                    predicted_idx = i;
                    maxi = a_n.matrix[i][0];
                }
            }

            int actual_label = (int)(unsigned char)loader.label_exact[start];
            if (predicted_idx == actual_label) {
                correct++;
            }
        }

        std::cout << "Overall Accuracy: " << (double)correct / total * 100.0 << "%" << std::endl;
    }
};