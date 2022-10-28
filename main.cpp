#include "Perceptron.hpp"
#include "training.hpp"
#include "NeuralNetwork.hpp"

#include <string>
#include <iostream>
#include <fstream>

using namespace MLPBON002;
int main(void){
    int part;
    std::cout << "Part 1 or 2: " << std::endl;
    std::cin >> part;
    if(part==1){ //XOR algorithm
        //Here we train the algorithm using examples in training.hpp.
        /*
         * I know the structure/connection of the XOR. Therefore I'll only train the NAND,
         * OR and AND(Which is just the inverse of NAND)
         */
        Perceptron NAND(2);
        Perceptron OR(2);
        std::vector<double> input;
        int NANDOut, OROut, NANDGuess, ORGuess;
        //Train the algorithm
        input.push_back(0);
        input.push_back(0); 
        for(int i = 0; i < 8; i++){
            input[0] = (NAN1[i][0]);
            input[1] = (NAN1[i][1]);
            NANDOut = NAN1[i][2]; OROut = O[i][2];
            NANDGuess = NAND.guess(input);
            ORGuess = OR.guess(input);

            while(NANDGuess != NANDOut || ORGuess != OROut){
                NAND.train(input, NANDOut); NANDGuess = NAND.guess(input);
                OR.train(input, OROut); ORGuess = OR.guess(input);
            }
        }
        /*
         * At this point the algorithm has trained and it is
         * ready to take in user inputs.
         */
        int userInput1 = 0, userInput2 = 0, results = 0, u1, u2;
        Perceptron AND(NAND);
        AND.invert(); //Inverting the NAND to get the AND
        std::vector<double> final = {0, 0};
        while(userInput1 != -2 && userInput2 != -2){
            std::cout <<"Enter input 1(or -2 to exit): " << std::endl;
            std::cin >> userInput1;
            u1 = userInput1;
            if(userInput1 == 0){
                userInput1 = -1;
            }
            if(userInput1 == -2){
                break;
            }
            std::cout <<"Enter input 2(or -2 to exit): " << std::endl;
            std::cin >> userInput2;
            u2 = userInput2;
            if(userInput2 == 0){
                userInput2 = -1;
            }
            input[0] = userInput1;
            input[1] = userInput2;
            final[0] = NAND.guess(input);
            if(final[0] == 0){
                final[0] = -1;
            }
            final[1] = OR.guess(input);
            if(final[1] == 0){
                final[1] = -1;
            }
            results = AND.guess(final);
            if(results == -1){results = 0;}
            std::cout << "The output for XOR inputs: "<< u1 <<" "<< u2 <<" is "<<results<< std::endl;
        }
    }else if(part==2){
        /*
         * This is the part where we train the algorithm.
         * except for this assignment we don't really have to worry
         * about the whole network since some of the inputs where given.
         */
        std::ofstream output; //For writing to output file.
        output.open("Part_2.txt");

        NeuralNetwork nn(3,2,1);
        //We set the given weights!
        nn.setW_IH(0,0,0.1); nn.setW_IH(0,1,0.2); nn.setW_IH(0,2,0.5);
        nn.setW_IH(1,0,-0.4); nn.setW_IH(1,1,1.0); nn.setW_IH(1,2,-0.6);
        nn.setBiasH(0, 0, 0.1); nn.setBiasH(1, 0, -0.3);
        int n = 100;
        std::vector<double> trainValues = {1.30, 2.70, 0.80};
        while(nn.getOutputValue() != 0.36 && n >= 0){
            nn.train(trainValues, 0.36);
            n--;
        }
        std::cout << "With the neual network trained to give this output: " << std::endl;
        output << "With the neual network trained to give this output: " << nn.getOutputValue() << "\n";
        nn.showOutput();
        std::cout << "The outputs of the hidden layer neurons 1 and 2 are: "<<std::endl;
        output << "The outputs of the hidden layer neurons 1 and 2 are: "<< nn.getHiddenRes() << "\n\n";
        nn.showHiddenRes();
        //Write the results to file.
        std::cout << "Given the values in Question 4 the neural network output: "<<std::endl;
        nn.setW_HO(0,0, 0.8); nn.setW_HO(0, 1, 1.0);
        nn.setBiasO(0, 0, -0.3);
        nn.feedForward(trainValues);
        output << "Given the values in Question 4 the neural network output: " << nn.getOutputValue() << "\n\n";
        nn.showOutput();
        std::cout <<"And the Mean Square Error is: "<<std::endl;
        output << "And the Mean Square Error is: " << nn.getMSE() << "\n\n";
        std::cout << nn.getMSE() << std::endl;
        std::cout << "The results are also written to a text file (Part2.txt)"<<std::endl;
    }
}