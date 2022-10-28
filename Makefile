CC = g++
CCFLAGS = -std=c++11

run: clean NeuralNetwork
	@./NeuralNetwork

NeuralNetwork: matrix.o nn.o main.o
	$(CC) $(CCFLAGS) main.o Matrix.o NeuralNetwork.o -o NeuralNetwork

matrix.o: Matrix.cpp Matrix.hpp
	$(CC) $(CCFLAGS) Matrix.cpp -c

nn.o: NeuralNetwork.cpp NeuralNetwork.hpp
	$(CC) $(CCFLAGS) NeuralNetwork.cpp -c

main.o: main.cpp Perceptron.hpp training.hpp
	$(CC) $(CCFLAGS) main.cpp -c

clean:
	@rm -f *.o NeuralNetwork