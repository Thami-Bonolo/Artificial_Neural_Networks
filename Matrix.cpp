#include "Matrix.hpp"

#include <random> //Generating random values.

//using namespace std;
namespace MLPBON002{
    Matrix::Matrix(int row, int col): rows(row), cols(col){
        matrix = new double* [row];

        for(int i = 0; i < row; i++){
            matrix[i] = new double[col];
        }
    }

    Matrix::Matrix(const Matrix& old): rows(old.rows), cols(old.cols){
        matrix = new double* [rows];
        for(int i = 0; i < rows; i++){
            matrix[i] = new double[cols];
            for (int j = 0; j < cols; j++){
                matrix[i][j] = old.matrix[i][j];
            }
        }
    }

    Matrix::~Matrix(){
        if(matrix != NULL){
            for(int i = 0; i < rows; i++){
                delete [] matrix[i];
            }
            delete [] matrix;
        }
    }

    double Matrix::get(int row, int col){
        if(row > rows - 1 || col > cols - 1 ||
        row < 0 || col < 0){
            std::cerr << "Invalid index!";
            return 0.0;
        }
        return matrix[row][col];
    }

    void Matrix::set(int row, int col, double val){
        if(row > rows - 1 || col > cols - 1 ||
        row < 0 || col < 0){
            std::cerr << "Invalid index!";
        }else{
            matrix[row][col] = val;
        }
    }

    Matrix Matrix::transpose(){
        Matrix temp(cols, rows);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                temp.matrix[j][i] = matrix[i][j];
            }
        }
        return temp;
    }

    void Matrix::ShowGrid(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                std::cout << matrix[i][j]<< " ";
            }
            std::cout << "\n";
        }
    }
    /*
     * This method sets the entries of the matrix to values
     * between 0 and 1;
     */
    void Matrix::randomize(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                matrix[i][j] = (((double) rand()/(RAND_MAX))*2)-1;
            }
        }
    }
}