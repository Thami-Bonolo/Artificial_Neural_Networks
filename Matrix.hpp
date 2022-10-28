#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <iostream> //For output

namespace MLPBON002{
    /*
     * Here we implement the matrix class to use for all
     * matrix opeations we need in our NeuralNetwork program
     */
    class Matrix{
        private:
            int rows, cols;
            double **matrix;
        public:
            //Default constructor
            Matrix(void): rows(0), cols(0){
                matrix = NULL;
            }
            //Another constrctor
            Matrix(int rows, int cols);
            //Copy Constructor
            Matrix(const Matrix&);
            //Destructor
            ~Matrix();
            //Getters and Setters
            int getRows(){
                return rows;
            }
            int getCols(){
                return cols;
            }
            void randomize(); //This will randomize the entries of the matrix
            void set(int, int, double); 
            double get(int, int);

            /*
             * Here are the matrix operations.
             * I tried to add operations where the operators are used for Matrices and a constant
             * But sadly I couldn't. Now, a way that I did that is to convert the constant into a
             * 1x1 matrix then do the operations.
             */
            Matrix operator + (Matrix& B){
                /*
                 * If the dimensions of one(this) of the matrices is 1x1
                 * Then we'll be performing this between a matrix and a const!.
                 */
                if(rows == cols == 1){
                    Matrix temp(B);
                    for(int i = 0; i < B.rows; i++){
                        for(int j = 0; j < B.cols; j++){
                            temp.matrix[i][j] += matrix[0][0];
                        }
                    }
                    return temp;
                }

                if(B.cols != cols || B.rows != rows){
                    std::cerr << "The dimensions don't add up!\n";
                    return *this;
                }
                Matrix temp(*this);
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < cols; j++){
                        temp.matrix[i][j] += B.matrix[i][j];
                    }
                } return temp;
            }

            Matrix operator - (Matrix& B){
                /*
                 * If the dimensions of one(this) of the matrices is 1x1
                 * Then we'll be performing this between a matrix and a const!.
                 */
                if(rows == cols == 1){
                    Matrix temp(B);
                    for(int i = 0; i < B.rows; i++){
                        for(int j = 0; j < B.cols; j++){
                            temp.matrix[i][j] -= matrix[0][0];
                        }
                    }
                    return temp;
                }
                else if(B.cols != cols || B.rows != rows){
                    std::cerr << "The dimensions don't add up!\n";
                    return *this;
                }

                Matrix temp(*this);
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < cols; j++){
                        temp.matrix[i][j] -= B.matrix[i][j];
                    }
                } return temp;
            }

            //Assignment Operator;
            Matrix& operator=(const Matrix& A){
                if(this == &A){
                    return *this;
                }
                if(matrix != NULL){
                    for(int i = 0; i < rows; i++){
                        delete [] matrix[i];
                    }
                    delete [] matrix;
                }
                rows = A.rows; cols = A.cols;
                matrix = new double* [A.rows];
                for(int i = 0; i < A.rows; i++){
                    matrix[i] = new double [A.cols];
                    for(int j = 0; j < A.cols; j++){
                        matrix[i][j] = A.matrix[i][j];
                    }
                }
                return *this;
            }

            Matrix& operator +=(Matrix& B){
                *this = *this + B;
                return *this;
            }

            Matrix operator * (Matrix& B){
                /*
                 * If the dimensions of one(this) of the matrices is 1x1
                 * Then we'll be performing this between a matrix and a const!.
                 */
                if(rows == cols == 1){
                    Matrix temp(B);
                    for(int i = 0; i < B.rows; i++){
                        for(int j = 0; j < B.cols; j++){
                            temp.matrix[i][j] *= matrix[0][0];
                        }
                    }
                    return temp;
                }
                else if(cols != B.rows){
                    std::cerr << "The * operation cannot be done on the matrices. The dimensions do not match!\n";
                    return *this;
                }
                Matrix temp(rows, B.cols);
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < B.cols; j++){
                        for(int k = 0; k < cols; k++){
                            temp.matrix[i][j] += matrix[i][k] * B.matrix[k][j];
                        }
                    }
                }
                return temp;
            }
            //Matrix Transpose! :|
            Matrix transpose();
            //For testing purposes:
            void ShowGrid();
    };
}
#endif