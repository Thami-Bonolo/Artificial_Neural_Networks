#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Matrix.hpp"
#include <vector>
#include <math.h>
#include <string>

using namespace MLPBON002;
class NeuralNetwork{
    private:
        const int numOfIn, numOfHidden, numOfOut;
        Matrix *InputsWeight;
        Matrix *HiddenWeights;
        Matrix *BiasH;
        Matrix *BiasO;
        Matrix HiddenResults;
        Matrix *Output;
        double learningRate = 0.1;
        double Target = 0.0;
    public:
        NeuralNetwork(int, int, int);
        Matrix feedForward(std::vector<double>);
        Matrix activation(Matrix);
        Matrix convertToMatrix(std::vector<double>);
        void train(std::vector<double> input, double target);
        Matrix sigmoidDer(Matrix); //derivative of the sigmoid
        /*
         * Adding these functions so I can modify the values
         * and answer the questions in the assigment.
         */
        void setW_IH(int row, int col, double val); //Input/Hidden layer weights
        void setW_HO(int row, int col, double val); //Hidden/Output layer weights
        void setBiasH(int row, int col, double val); // Hidden layer Bias
        void setBiasO(int row, int col, double val); // Output layer Bias
        void showHiddenRes();
        std::string getHiddenRes();
        void showOutput();
        double getOutputValue();
        double getMSE();
};
#endif