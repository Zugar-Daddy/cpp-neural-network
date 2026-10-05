#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>

static std::string train_images_digits = "/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/train-images-idx3-ubyte";
static std::string train_labels_digits = "/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/train-labels-idx1-ubyte";
static std::string test_images_digits = "/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/t10k-images-idx3-ubyte";
static std::string test_labels_digits = "/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/t10k-labels-idx1-ubyte";

static std::string train_images_letters = "/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/emnist-letters-train-images-idx3-ubyte";
static std::string train_labels_letters = "/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/emnist-letters-train-labels-idx1-ubyte";
static std::string test_images_letters = "/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/emnist-letters-test-images-idx3-ubyte";
static std::string test_labels_letters = "/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/emnist-letters-test-labels-idx1-ubyte";

class Loader{
    
public:
    char magic_number[4], num_images[4], rows[4], cols[4];
    char* images = nullptr;
    double* normalized_images = nullptr;
    int image_dim; long total_pixels;

    uint32_t total_images, row_count, col_count, test_images;

    char magic[4], num[4];
    char* label_exact = nullptr;

    void change_endian(char* bigEndian, int size){
        char* end = bigEndian + size - 1;
        for(int i = 0; i < size / 2; i++){
            std::swap(*(bigEndian + i), *(end - i));
        }
    }

    void Debug(){
        std::cout << "Magic: "  << *reinterpret_cast<uint32_t*>(magic_number) << "\n";
        std::cout << "Images: " << total_images << "\n";
        std::cout << "Rows: "   << row_count << "\n";
        std::cout << "Cols: "   << col_count << "\n";
        std::cout << '\n';    
        std::cout << "Magic: "  << *reinterpret_cast<uint32_t*>(magic) << "\n";
        std::cout << "Images: " << *reinterpret_cast<uint32_t*>(num) << "\n";
        
        int c = 0;
        for(int j = 500; j < 515; j++){
            std::cout << '\n' << (int)(unsigned char)label_exact[j] << '\n' << '\n';
            for(int i = 0; i < image_dim; i++){
                if(normalized_images[(image_dim * j) + i] > 128/255.0) std::cout << '#';
                else std::cout << '_';
                c++;
                if(c == col_count){
                    c = 0;
                    std::cout << '\n';
                }
            }
        }
    }


    void NormalizePixels(bool letters = false){
        if(letters){
            for(int i = 0; i < total_images; i++){
                int offset = i * image_dim;

                for(int r = 0; r < row_count; r++){
                    for(int c = 0; c < col_count; c++){
                        // Transpose mapping: swap r and c for the source index
                        int raw_idx = offset + (c * 28 + r);
                        int target_idx = offset + (r * 28 + c);

                        normalized_images[target_idx] = (double) ((unsigned char)images[raw_idx]) / 255.0;
                    }
                }
            }
        }
        else{
            for(int i = 0; i < total_pixels; i++){
                normalized_images[i] = (double) ((unsigned char)images[i]) / 255.0;
            }
        }
        // std::cout << "Pixels Normalized Successfully\n";
    }
    
    int LoadDataSet(const std::string& image_path, const std::string& label_path, bool letters = false){
        std::ifstream image_file(image_path, std::ios::binary);
        std::ifstream labels_file(label_path, std::ios::binary);

        if(!image_file.is_open()) {
            std::cerr << "Error: images file unavailable\n";
            return 1;
        }
        if(!labels_file.is_open()) {
            std::cerr << "Error: labels file unavailable\n";
            return 1;
        }

        // Images
        // first 16 bytes is header
        // 0-3 magic number, 4-7 number of images, 8-11 rows, 12-15 cols
        image_file.read(magic_number, 4);
        change_endian(magic_number, 4);

        image_file.read(num_images, 4);
        change_endian(num_images, 4);
        total_images = *reinterpret_cast<uint32_t*>(num_images);
        
        image_file.read(rows, 4);
        change_endian(rows, 4);
        row_count = *reinterpret_cast<uint32_t*>(rows);

        image_file.read(cols, 4);
        change_endian(cols, 4);
        col_count = *reinterpret_cast<uint32_t*>(cols);

        image_dim = row_count * col_count;
        total_pixels = image_dim * total_images;

        images = new char[total_pixels];
        image_file.read(images, total_pixels);


        // Labels header
        label_exact = new char[total_images]; 

        labels_file.read(magic, 4);
        change_endian(magic, 4);
        labels_file.read(num, 4);    
        change_endian(num, 4);
        labels_file.read(label_exact, total_images);    

        normalized_images = new double[total_pixels];
        NormalizePixels(letters);

        // Debug();
        // closing files
        image_file.close(); labels_file.close();
        return 0;
    }

    ~Loader(){
        delete[] images; 
        delete[] normalized_images;        
        delete[] label_exact;
    }

};