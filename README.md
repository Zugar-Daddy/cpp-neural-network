# cpp-neural-network

Loader.h -> Loads the ubyte files using std::ifstream and opens them in binary mode
            The files are in bigEndian Format and we have to change them inorder for the stuff inside to make sense, Endian simply means the bytes of that chunk have been reversed, (the files were originally meant to be read from behind but modern pc's read it from front or vice versa). That's what change_endian functions is doing.
            Vector of size 60000*784 can't be initialized that's why using dynamic memory.
            DeleteAllDynamic() is for clearing all that dynamically allocated memory
            Pixels are being normalized by NormalizePixels()

Matrix.h -> Defines basic matrix operations, multiply, add, subtract, transpose
            Matrix format mat[row][col]. All operations have been defined using this only

Layers.h -> Initialises layers, and their respective weights and biases using out_features and in_features
            shape of weights is (out_features x in_features) and shape of biases is (out_features x 1)
            
            Weights have been randomized using He's algorithm because I was told so by the internet that this is important. I have used mt19937, again, because I was told so.

Trainer.h-> Heavy math, the code is well documented. I've also added backprop.png in the folder for reference.
            First Layer (784 x 128) Uses ReLU activation
            Middle Layer (128 x 10) Uses SoftMax and determines probability (basically tells what digit the model thinks is the right answer)


Tester.h -> Uses loader.LoadTestFile() and then does forward pass and calculates overall accuracy.

Main.cpp -> Runs Everything

side note:
I use the codeforces template of having input.txt and output.txt workflow. But for running this, you need to run the program with optimsed flag which is "g++ -std=c++17 -O3 -march=native -ffast-math Main.cpp" for performing matrix calculations.
