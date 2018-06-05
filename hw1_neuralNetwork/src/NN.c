#include "NN.h"

void initNeuron(Neuron *n){
    for(int i = 0; i < NEURON_SIZE; i++)
        n->weights[i] = RAND;
    n->bias = RAND;
}

double forward(Neuron *n){
    double result = 0;

    for(int i = 0; i < NEURON_SIZE; i++)
        result += n->inputs[i] * n->weights[i];
    result += n->bias;

    return SIGMOID(result);
}

void backward(Neuron *n, double error){
    for(int i = 0; i < NEURON_SIZE; i++)
        n->weights[i] += error * n->inputs[i];
    n->bias += error;
}