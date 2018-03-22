#include "NN.h"

int main(){
    int i = 0;
    int count = 0;
    double output;
    double outputErr;
    double err;
    double ERR = 1;

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

    while(ERR > 0.001 || ERR < -0.001){
        for (int t = 0; t < INPUT_NUMBER; t++){
            if(count == 4) count = 0;
            
            /* forward */
            for (int i = 0; i < NEURON_SIZE; i++){
                Neuron *l = &intermediateLayers[i];
                for (int j = 0; j < NEURON_SIZE; j++){
                    l->inputs[j] = data[count].inputs[j];
                }
                outputLayers.inputs[i] = forward(l);
            }
            output = forward(&outputLayers);
            ERR = data[count].result - output;

            /* backward */
            outputErr = SIGMOID_DERIV(output) * (data[count].result - output);
            backward(&outputLayers, outputErr);
            for (int i = 0; i < NEURON_SIZE; i++){
                err = SIGMOID_DERIV(outputLayers.inputs[i]) * outputErr * outputLayers.weights[i];
                backward(&intermediateLayers[i], err);
            }

            count++;
        }
    }

    /* display */
    count = 0;
    for (int t = 0; t < INPUT_NUMBER; t++){
        if(count == 4) count = 0;
        printf("\n %d) %d XOR %d ", count+1, data[count].inputs[0], data[count].inputs[1]);

        for (int i = 0; i < NEURON_SIZE; i++){
            Neuron *l = &intermediateLayers[i];
            for (int j = 0; j < NEURON_SIZE; j++){
                l->inputs[j] = data[count].inputs[j];
            }
            outputLayers.inputs[i] = forward(l);
        }
        output = forward(&outputLayers);
        ERR = output - data[count].result;
        
        printf("= %f(real output) , %d(except output) , ERR = %f", output, data[count].result, ERR);
        count++;
    }
    
    getchar();
    return 0;
}