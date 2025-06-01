#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "../include/NeuralNetwork.h"

std::vector<double>* read_numbers_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file.\n";
        return nullptr;
    }

    auto* numbers = new std::vector<double>();
    numbers->reserve(6052);  // Allocate space for 6052 elements (you only need 6051 but you never know, do you)

    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        double num;
        while (ss >> num) {
            numbers->push_back(num);
        }
    }

    file.close();
    return numbers;
}

void train_A(const std::string& filename, const std::string& export_filename, NeuralNetwork& n, const int& epochs){
    std::vector<double>* data = read_numbers_from_file(filename);
    const int data_size = static_cast<int>(data->size());
    std::cout << "Before training:\n";
    n.print_weights_and_biases();

    // Train for a few epochs
    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int k = 0; k < 10; k++) {
            for (int pos = 0; pos + 5 < data_size; pos += 10) {  // Prevent out-of-bounds access
                int index = pos + k;
                if (index + 5 < data_size) {
                    std::vector<double> training(5);
                    training[0] = (*data)[index]/10;      // Dereferencing pointer correctly
                    training[1] = (*data)[index + 1]/10;
                    training[2] = (*data)[index + 2]/10;
                    training[3] = (*data)[index + 3]/10;
                    training[4] = (*data)[index + 4]/10;

                    int label = static_cast<int>((*data)[index + 5]) - 1;
                    if (label >= 0 && label < 10) {
                        std::vector<double> exp(10, 0);
                        exp[label] = 1;
                        n.learn(training, exp);
                    }
                }
            }
        }
        if(epoch%100==0) std::cout << epoch << " epochs completed." << std::endl;
    }

    std::cout << "\nAfter training:\n";
    n.print_weights_and_biases();
	n.export_network(export_filename);
    // Cleanup allocated memory
    delete data;
}
void test_A(const std::string& filename, NeuralNetwork& n){
    std::vector<double>* data = read_numbers_from_file(filename);
    const int data_size = static_cast<int>(data->size());

    int success =0;
    int fail = 0;
    int all = 0;

    for(int k = 0; k < data_size-5; k++ ){
        std::vector<double> temp(5);
        for(int i = 0; i < 5; i++ ){
            temp[i] = (*data)[k+i];
        }
        if(n.run(temp)==(*data)[k+5]) success++;
        else fail++;
        all++;
    }
    std::cout << "Accuracy: " << static_cast<double>(success)/static_cast<double>(all)*100.0 << "%\n";
    std::cout << success << " " << fail << '\n';
    // Cleanup allocated memory
    delete data;
}


void train_B(const std::string& filename, const std::string& export_filename, NeuralNetwork& n, const int& epochs){
    //read file
    std::vector<std::vector<double>> data;
    std::vector<std::vector<double>> exp;
    data.reserve(1000);
    exp.reserve(1000);

    std::ifstream file(filename);
    if (!file) {
        throw std::invalid_argument("Matrix sizes must match for addition");
    }

    std::string line;
    int index_1 = 0;
    while (std::getline(file, line)) {
        data.push_back(std::vector<double>(64));
        exp.push_back(std::vector<double>(4,0));
        std::stringstream ss(line);
        double num;
        int index_2 = 0;
        while (ss >> num) {
            if(index_2 == 64){
                exp[index_1][num] = 1;
            }
            else{
                data[index_1][index_2] = num/255;
                index_2++;
            }
        }
        index_1++;
    }

    file.close();

    std::cout << "Before training:\n";
    n.print_weights_and_biases();

    // Train for a few epochs
    for (int epoch = 0; epoch < epochs; epoch++) {
        //data handling goes here
        for (int k = 0; k < static_cast<int>(data.size()); k++)
            n.learn(data[k],exp[k]);
        if(epoch%100==0) std::cout << epoch << " epochs completed." << std::endl;
    }

    std::cout << "\nAfter training:\n";
    n.print_weights_and_biases();
	n.export_network(export_filename);
}

void test_B(const std::string& filename, NeuralNetwork& n){
    //read file
    std::vector<std::vector<double>> data;
    std::vector<int> exp;
    data.reserve(1000);
    exp.reserve(1000);

    std::ifstream file(filename);
    if (!file) {
        throw std::invalid_argument("Error: could not open file\n");
    }

    std::string line;
    int index_1 = 0;
    while (std::getline(file, line)) {
        data.push_back(std::vector<double>(64));
        std::stringstream ss(line);
        double num;
        int index_2 = 0;
        while (ss >> num) {
            if(index_2 == 64){
                exp[index_1] = num;
                break;
            }
            else{
                data[index_1][index_2] = num;
                index_2++;
            }
        }
        index_1++;
    }

    file.close();

    int success =0;
    int fail = 0;
    int all = 0;
    for (int k = 0; k < static_cast<int>(data.size()); k++){
        all++;
        //std::cout << n.run(data[k]) << '\t' << exp[k] << '\n';
        if(n.run(data[k])==exp[k]) success++;
        else fail++;
    }
    std::cout << "Accuracy: " << static_cast<double>(success)/static_cast<double>(all)*100.0 << "%\n";
    std::cout << success << " " << fail << '\n';
}
void testNetwork(){
    NeuralNetwork net({2,4,2}, 0.1, {"0","1"}, "wadawd", {ReLU,SIGMOID});

    std::vector<std::vector<double>> xor_inputs = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };
    std::vector<std::vector<double>> xor_outputs = {
        {1,0},
        {0,1},
        {0,1},
        {1,0}
    };
    for(int epoch = 0; epoch < 500000; epoch++){
        for (int i = 0; i < 4; i++) {
            net.learn(xor_inputs[i],xor_outputs[i]);
            int prediction = net.run(xor_inputs[i]);
            int expected = (xor_inputs[i][0] != xor_inputs[i][1]) ? 1 : 0;
            std::cout << xor_inputs[i][0] << " XOR " << xor_inputs[i][1]
                      << " = " << prediction << " (Expected: " << expected << ")\n";
        }
    }
    net.print_weights_and_biases();

    for(int i = 0; i < 4; i++){
        std::cout << net.run(xor_inputs[i]) << ' ';
    }



}


int main() {
	//std::string path = "project_b_training.txt";
    std::string path = "training_data_raw.txt";
    std::string e_path = "A.txt";
    //std::string title = "Project B - final test";
    //const double learning_rate = 0.06;
    //const int epochs = 6000;

    //std::vector<int> size = {64, 32, 10, 4};  // for project A
    //std::vector<std::string> op = {"kör", "X", "háromszög", "smiley"};
    //std::vector<std::string> op = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    //std::vector<int> act_funct = {SIGMOID, SIGMOID};

    //NeuralNetwork net(size, learning_rate, op, title, act_funct);

    //train_B(path,e_path,net,epochs);

    NeuralNetwork Ignac(e_path);

    std::cout << "Testing...\n";

    test_A(path,Ignac);
    int o;
    std::cin >> o;

    //train_B(path,e_path,net,epochs);
}



    //std::vector<int> size = {64, 32, 4}; // for project B
    //std::vector<std::string> op = {"kör", "X", "háromszög", "smiley"};