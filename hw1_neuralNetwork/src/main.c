#include "NN.h"

int main(){
    int i = 0;
    int count = 0;
    double output;
    double outputErr;
    double err;

    /* open and read file */
    Data data[INPUT_NUMBER];
    FILE * pFile;
    pFile = fopen ("input.txt","r");
    if (pFile == NULL){
        printf("Files DOES NOT EXISTS!");
    }
    while(fscanf(pFile,"%d %d %d", &data[i].inputs[0], &data[i].inputs[1], &data[i].result)!=EOF)
        i++;
    
    /* init weight and bias (random) */
    Neuron intermediateLayers[NEURON_SIZE];
    for (int i = 0; i < NEURON_SIZE; i++)
        initNeuron(&intermediateLayers[i]);
    Neuron outputLayers;
    initNeuron(&outputLayers);
    
    for (int t = 0; t < INPUT_NUMBER; t++){
        printf("\n %d) %d XOR %d ", count+1, data[count].inputs[0], data[count].inputs[1]);
        
        do{
            /* forward */
            for (int i = 0; i < NEURON_SIZE; i++){
                Neuron *l = &intermediateLayers[i];
                for (int j = 0; j < NEURON_SIZE; j++){
                    l->inputs[j] = data[count].inputs[j];
                }
                outputLayers.inputs[i] = forward(l);
            }
            output = forward(&outputLayers);

            /* backward */
            outputErr = SIGMOID_DERIV(output) * (data[count].result - output);
            backward(&outputLayers, outputErr);
            for (int i = 0; i < NEURON_SIZE; i++){
                err = SIGMOID_DERIV(outputLayers.inputs[i]) * outputErr * outputLayers.weights[i];
                backward(&intermediateLayers[i], err);
            }

        }while(outputErr > 0.001 || outputErr < -0.001);
        printf("= %d(except value) %f(real value) => ERR:%f", data[count].result, output, outputErr);
        count++;
    }
    
    getchar();
    return 0;
}