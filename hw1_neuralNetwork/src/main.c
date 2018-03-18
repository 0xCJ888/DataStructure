#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "NN.h"


int main(){
    /* open and read file */
    int i = 0;
    Data data[INPUT_NUMBER];
    FILE * pFile;
    pFile = fopen ("input.txt","r");
    if (pFile == NULL){
        printf("Files DOES NOT EXISTS!");
    }
    while(fscanf(pFile,"%d %d %d", &data[i].inputs[0], &data[i].inputs[1], &data[i].result)!=EOF)
        i++;

    /* init */
    Neuron intermediateNeurons[NEURON_SIZE];
    for (int i = 0; i < NEURON_SIZE; i++)
        initNeuron(&intermediateNeurons[i]);

    Neuron outputNeuron;
    initNeuron(&outputNeuron);

    int count = 0;
    double output;
    double outputErr = 0;
    double err;
    for (int t = 0; t < INPUT_NUMBER; t++){
        printf("\n%d XOR %d ", data[count].inputs[0], data[count].inputs[1]);
        do{
            /* FEEDFORWARD  */
            for (int i = 0; i < NEURON_SIZE; i++){
            // Feed the intermediate_layer
                Neuron *l = &intermediateNeurons[i];
                for (int j = 0; j < NEURON_SIZE; j++)
                    l->inputs[j] = data[count].inputs[j];

            // Feed the output layer
            outputNeuron.inputs[i] = forward(l);
            }

            // Determine the output of the neural network
            output = forward(&outputNeuron);
            /* END FEEDFORWARD */

            /* BACKWARD */
            // Determine the error between what we found and the expected result
            outputErr = SIGMOID_DERIV(output) * (data[count].result - output);

            // Update output neuron
            backward(&outputNeuron, outputErr);

            // Update the neurons in the intermediate layer
            for (int i = 0; i < NEURON_SIZE; i++){
                err = SIGMOID_DERIV(outputNeuron.inputs[i]) * outputErr * outputNeuron.weights[i];
                backward(&intermediateNeurons[i], err);
            }
            /* END BACKWARD */
        }while(fabs(outputErr) > 0.001);
        printf("= %d(%d) %f(ERR:%f)", output > 0.5, data[count].result, output, outputErr);
        count++;
    }
    getchar();
    return 0;
}