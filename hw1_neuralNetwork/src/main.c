#include "NN.h"

int main(){
    int i =0;
    Data data[DATA_SIZE];
    DataDouble t[DATA_SIZE];
    FILE * pFile;
    pFile = fopen ("input.txt","r");
    if (pFile == NULL){
      printf("Files DOES NOT EXISTS!");
    }
    while(fscanf(pFile,"%d %d %d", &data[i].inputs[0], &data[i].inputs[1], &data[i].result)!=EOF){
      t[i].inputs[0] =(double) data[i].inputs[0];
      t[i].inputs[1] =(double) data[i].inputs[1];
      t[i].result =(double) data[i].result;
      i++;
    }

  /* init weight and bias (random) */
  Neuron intermediateNeurons[NEURON_SIZE]; 
  for (int i = 0; i < NEURON_SIZE; i++)
    initNeuron(&intermediateNeurons[i]);
  Neuron outputNeuron;
  initNeuron(&outputNeuron);

  int count = 0;

  for (int epoch = 0; epoch < 4000; epoch++){
    if(count == 4) count = 0;

    /* forward */
    for (int i = 0; i < NEURON_SIZE; i++){
      Neuron *l = &intermediateNeurons[i];
      for (int j = 0; j < NEURON_SIZE; j++)
        l->inputs[j] = t[count].inputs[j];
      outputNeuron.inputs[i] = forward(l);
    }
    double output = forward(&outputNeuron);

    /* backward */
    double outputErr = SIGMOID_DERIV(output) * (t[count].result - output);
    backward(&outputNeuron, outputErr);
    for (int i = 0; i < NEURON_SIZE; i++){
      double err = SIGMOID_DERIV(outputNeuron.inputs[i]) * outputErr * outputNeuron.weights[i];
      backward(&intermediateNeurons[i], err);
    }
    count++;
  }
  /* display */
  for(int count = 0; count < DATA_SIZE; count++){
    for (int i = 0; i < NEURON_SIZE; i++){
      Neuron *l = &intermediateNeurons[i];
      for (int j = 0; j < NEURON_SIZE; j++)
         l->inputs[j] = t[count].inputs[j];
      outputNeuron.inputs[i] = forward(l);
    }
    double output = forward(&outputNeuron);
    printf("\n%d XOR %d = %d ", (int)t[count].inputs[0], (int)t[count].inputs[1], (int)t[count].result);
    printf("= %d(%d) %f(ERR:%f)", output > 0.5, (int)t[count].result, output, t[count].result - output);
  }
  getchar();
  return 0;
}