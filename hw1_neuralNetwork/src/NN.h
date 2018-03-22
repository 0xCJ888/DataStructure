#ifndef __NN_H__
#define __NN_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NEURON_SIZE 2 
#define DATA_SIZE 4

#define SIGMOID(x)       ( 1. / (1. + exp(-x)) )
#define SIGMOID_DERIV(x) ( x * (1. - x) )
#define RAND       ( (double)rand()/(double)RAND_MAX )

typedef struct{
  double inputs[2];
  double result;
} DataDouble;

typedef struct{
  int inputs[2];
  int result;
} Data;
typedef struct{
  double inputs[NEURON_SIZE];
  double weights[NEURON_SIZE]; 
  double bias;
} Neuron;

void initNeuron(Neuron *n);
double forward(Neuron *n);
void backward(Neuron *n, double error);

#endif