#include <cstdint>
#include <fstream>
#include <iostream>
using namespace std;

void change_endian(char* bigEndian, int size){
    char* end = bigEndian + size - 1;
    for(int i = 0; i < size / 2; i++){
        swap(*(bigEndian + i), *(end - i));
    }
}

int main(){
    std::ifstream image_file("/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/train-images-idx3-ubyte", std::ios::binary);
    std::ifstream labels_file("/home/madhav_bhardwaj/Desktop/Career/LearningExp/CPP-Neural-Network/Datasets/train-labels-idx1-ubyte", std::ios::binary);

    if(!image_file.is_open()) {
        cerr << "Error: images file unavailable\n";
        return 1;
    }
    if(!labels_file.is_open()) {
        cerr << "Error: labels file unavailable\n";
        return 1;
    }

    // Images
    // first 16 bytes is header
    // 0-3 magic number, 4-7 number of images, 8-11 rows, 12-15 cols
    char magic_number[4]; image_file.read(magic_number, 4);
    char num_images[4]; image_file.read(num_images, 4);
    char rows[4]; image_file.read(rows, 4);
    char cols[4]; image_file.read(cols, 4);
    char* images = new char[60000*784];
    image_file.read(images, 784 * 60000);

    change_endian(magic_number, 4);
    change_endian(num_images, 4);
    change_endian(rows, 4);
    change_endian(cols, 4);

    // Labels header
    char magic[4]; labels_file.read(magic, 4);
    char num[4]; labels_file.read(num, 4);    
    char* labels = new char[60000]; 
    change_endian(magic, 4);
    change_endian(num, 4);

    labels_file.read(labels, 60000);    


    // DEBUG
    cout << "Magic: "  << *reinterpret_cast<uint32_t*>(magic_number) << "\n";
    cout << "Images: " << *reinterpret_cast<uint32_t*>(num_images) << "\n";
    cout << "Rows: "   << *reinterpret_cast<uint32_t*>(rows) << "\n";
    cout << "Cols: "   << *reinterpret_cast<uint32_t*>(cols) << "\n";
    cout << '\n';    
    cout << "Magic: "  << *reinterpret_cast<uint32_t*>(magic) << "\n";
    cout << "Images: " << *reinterpret_cast<uint32_t*>(num) << "\n";
    
    int c = 0;
    for(int j = 0; j < 5; j++){
        cout << '\n' << (int)(unsigned char)labels[j] << '\n' << '\n';
        for(int i = 0; i < 784; i++){
            if((int)(unsigned char)images[(784 * j) + i] > 128) cout << '#';
            else cout << ".";
            c++;
            if(c == 28){
                c = 0;
                cout << '\n';
            }
        }
    }


    image_file.close(); labels_file.close();
}