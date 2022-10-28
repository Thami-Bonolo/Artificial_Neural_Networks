#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(int in, int hi, int ou):numOfIn(in), numOfHidden(hi), numOfOut(ou){
    InputsWeight = new Matrix(numOfHidden, numOfIn);
    HiddenWeights = new Matrix(numOfOut, numOfHidden);
    BiasH = new Matrix(numOfHidden, 1);
    BiasO = new Matrix(numOfOut, 1);
    InputsWeight->randomize();
    HiddenWeights->randomize();
    BiasH->randomize();
    BiasO->randomize();
    Output = new Matrix(1,1);
}
/*
 * This function is for converting the vector to a matrix. So
 * that we can use the matrix operators defined in the matrix class.
 */
Matrix NeuralNetwork::convertToMatrix(std::vector<double> array){
    Matrix temp(array.size(),1);
    for(int i = 0; i < array.size(); i++){
        temp.set(i, 0, array[i]);
    }
    return temp;
}

void NeuralNetwork::train(std::vector<double> in, double t){
    /*
     * Here we train the algorithm to give us the desired results. (How?)
     * 1. We compute the error = Target - Guess;
     * 2. Then we tweak the weights(both Input/Hidden and Hidden/Output) in suuch a 
     *    way that we minimize the error. 
     *      Wij <- Wij + ΔWij
     *    The value in which we change the weights is ΔWij
     *  And how it is calculated is the following:
     * 
     * ΔWij = (learningRate * Error * (s(hiddenOutput) * (1 - s(hiddenOutput)))) * hiddenOut.transpose();
     * 
     * 
     * We won't be passing the inputs into the feed forward function.
     * Because I coded it in such a way that it just takes in the input and returns the output.
     * So, we re-do the whole process in this function. 
     */

    //Convert to Matrix objects
    Target = t;
    std::vector<double> temp = {t};
    Matrix target(convertToMatrix(temp));
    Matrix answer = feedForward(in);

    //Here we calculate the error
    Matrix OutputError = target - answer;

    //Hidden Layer:
    Matrix input(convertToMatrix(in));
    Matrix InputHidden((*InputsWeight)*input);
    InputHidden += (*BiasH);
    Matrix Hidden(activation(InputHidden));

    //Here I convert all the const I'll use to a Matrix!
    std::vector<double> learning = {learningRate};
    std::vector<double> o = {1};
    Matrix lr(convertToMatrix(learning));
    Matrix one(convertToMatrix(o));
    //Then, we calculate the hidden layer errors
    Matrix HiddenWeights_t((HiddenWeights->transpose()));
    Matrix HiddenErrors = HiddenWeights_t * OutputError;
    // ΔWij - for Input/Hidden
    //Matrix W_IH = (lr*(OutputError*(Hidden*(one - Hidden))))*(input.transpose());

    // ΔWij - for Hidden/Output
    //Matrix W_HO = (lr*(HiddenErrors*(answer*(one - answer))))*(Hidden.transpose());

    // I attempt to use the already defined matrices :|
    Matrix b = sigmoidDer(answer);
    Matrix c = OutputError * b;
    Matrix d = lr * c;
    Matrix Hidden_t(Hidden.transpose());
    Matrix W_HO = d * Hidden_t;

    //change all the weights by ΔWij
    *HiddenWeights += W_HO; 
}

Matrix NeuralNetwork::feedForward(std::vector<double> array){
    /*
     * In this function takes in the user input and generates the output.
     * (How?)
     * In two steps:
     * 1. Compute the weighted sum on the input matrix and the hidden layer neurons matrix.
     * Pass the results to the sigmoid activation function.
     * 2. Take the results, compute the the weighted sum on the results and the output layer matrix.
     * again, pass the results to the sigmoid activation function. then return the result.
     */
    //1
    Matrix input(convertToMatrix(array)); //Using the copy constructor!
    Matrix InputHidden((*InputsWeight)*input);
    InputHidden += (*BiasH);
    //InputHidden.ShowGrid(); std::cout << "\n";
    HiddenResults = activation(InputHidden);

    //2
    Matrix HiddenOutput((*HiddenWeights)*HiddenResults);
    HiddenOutput += (*BiasO);
    Matrix Out(activation(HiddenOutput));
    *Output = Out; //Using the assignment operator :|
    return Out; 
}

void NeuralNetwork::setW_IH(int row, int col, double val){
    InputsWeight->set(row, col, val);
}
void NeuralNetwork::setW_HO(int row, int col, double val){
    HiddenWeights->set(row, col, val);
}
void NeuralNetwork::setBiasH(int row, int col, double val){
    BiasH->set(row, col, val);
}
void NeuralNetwork::setBiasO(int row, int col, double val){
    BiasO->set(row, col, val);
}
void NeuralNetwork::showHiddenRes(){
    HiddenResults.ShowGrid();
}
std::string NeuralNetwork::getHiddenRes(){
    std::string out = "";
    for(int i = 0; i < HiddenResults.getRows(); i++){
        for(int j = 0; j < HiddenResults.getCols(); j++){
            out += std::to_string(HiddenResults.get(i,j));
            out += " ";
        }
    }
    return out;
}
void NeuralNetwork::showOutput(){
    Output->ShowGrid();
}
double NeuralNetwork::getOutputValue(){
    return Output->get(0,0); // 1x1 matrix!
}

Matrix NeuralNetwork::sigmoidDer(Matrix in){ //Derivative of the sigmoid function.
    Matrix temp(in);
    for(int i = 0; i < in.getRows(); i++){
        for(int j = 0; j < in.getCols(); j++){
            temp.set(i, j,((-1*exp(-1*in.get(i,j)))/((1-exp(-1*in.get(i,j)))*(1-exp(-1*in.get(i,j))))));
        }
    }
    return temp;
}

//This was added only for the purpose of answering Question 5.
double NeuralNetwork::getMSE(){
    return (Output->get(0,0) - Target)*(Output->get(0,0) - Target);
}

Matrix NeuralNetwork::activation(Matrix in){
    //sigmoid function
    Matrix temp(in);
    for(int i = 0; i < in.getRows(); i++){
        for(int j = 0; j < in.getCols(); j++){
            temp.set(i, j, (1/(1+exp(-1*in.get(i,j)))));
        }
    }
    return temp;
}