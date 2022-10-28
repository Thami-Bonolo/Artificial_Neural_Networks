#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <random>

namespace MLPBON002{
    class Perceptron
    {
    private:
        /* data */
        std::vector<double> weights;
        int num; //Number of inputs
        double learningRate = 0.1;
    public:
        Perceptron(int);
        ~Perceptron();
        Perceptron(const Perceptron& old); //copy constructor
        int guess(std::vector<double>);
        int Threshold(double);
        void train(std::vector<double>, int);
        void invert();
    };
    
    Perceptron::Perceptron(int numOfInputs)
    {
        /*
         * Here we create the vector wof weights!.
         * Note: I have added an extra dimension in the vector to 
         * store the BIAS value.
         * SO, we store the Bias at weights[0];
         * 
         * We should be setting the Bias value. But since this is 
         * a simple setting, I'll let it be set randomly. :)
         */
        num = numOfInputs;
        for(int i = 0; i < numOfInputs+1; i++){
            double temp = ((double)rand()/(RAND_MAX))*2;
            double w = temp - 1;
            weights.push_back(w);
        }
    }

    Perceptron::Perceptron(const Perceptron& old):num(old.num), learningRate(old.learningRate){
        /*
         * I am not sure if I can copy the vector with the assignment operator
         * So I'll just use what I know works. Manually copy everything!
         */
        for(int i = 0; i < num+1; i++){
            weights.push_back(old.weights[i]);
        }
    }

    //Activation function
    int Perceptron::Threshold(double sum){
        if(sum >= 0){
            return 1;
        }else{
            return -1;
        }
    }

    int Perceptron::guess(std::vector<double> inputs){
        double sum = weights[0];//Adding the bias first;
        for(int i = 0; i < num; i++){
            sum += (inputs[i])*weights[i+1];
        }
        int out = Threshold(sum);
        return out;
    }

    void Perceptron::train(std::vector<double> inputs, int target){
        int g = guess(inputs);
        double error = (target - g)*learningRate;
        weights[0] += error; // Code performs well with/without (this line)changing the bias.
        for(int i = 0; i < num; i++){
            weights[i+1] += error * inputs[i]; //i+1 because we avoiding the Bias.
        }
    }
    //To invert the NAND to an AND or vice versa
    void Perceptron::invert(){
        for(int i = 0; i < num+1; i++){
            weights[i] *= -1;
        }
    }
    
    Perceptron::~Perceptron()
    {
    }
    
}
#endif