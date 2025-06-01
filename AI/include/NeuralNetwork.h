#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <string>
#include "Matrix.h"

#define ReLU 0
#define SIGMOID 1

class NeuralNetwork {
private:
    std::vector<std::vector<double>> biases;
    double learning_rate;
    int layers;
    std::vector<int> size;
    std::vector<int> activation_function; //use ReLU or sigmoid
    std::vector<Matrix> weights;
    std::vector<std::string> output_values; //DO NOT USE SPACES
    double sigmoid(const double x) const;
    double sigmoid_derivative(const double x) const;
    double relu(const double x) const;
    double relu_derivative(const double x) const;
    double runActivationFunction(const int index, const double value) const;
    double runActivationFunctionDerivative(const int index, const double value) const;
    std::string title;

public:
    NeuralNetwork(const std::vector<int> layer_sizes, const double l_r, const std::vector<std::string> output, const std::string t,const std::vector<int> act_funct);
    NeuralNetwork(const std::string& filename);
    int run(const std::vector<double>& input) const;
    void learn(const std::vector<double> &input,const std::vector<double> &expected_output);
    //this function got forgotten
    //void learn_mini_batch(const std::vector<std::vector<double>> input,std::vector<std::vector<double>> expected_output) const;
    void export_network(const std::string& filename) const;
    void print_weights_and_biases() const;
};

#endif // NEURALNETWORK_H