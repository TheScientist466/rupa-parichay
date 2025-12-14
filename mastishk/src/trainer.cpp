#include "mastishk/Layer.hpp"
#include <fstream>
#include <iostream>
float cost(float* value, float* labled){
  float total = 0;
  for(int i = 0;i<10;i++){
    total+= (value[i]-labled[i])*(value[i]-labled[i]);
  }
  return total/10.0f;
}
float* ValueOfNetWorkCalculater(Layer* currentLayer, float* input){
  if ( currentLayer->ifPreviousLayer() == false){
    currentLayer->calculateActivations(input);
    return input;
  }
  
  ValueOfNetWorkCalculater(currentLayer->GenaratingPrevious(), input);
  currentLayer->calculateActivations(nullptr);
  return currentLayer->producingTheActivation();
}

int trainAndSaveModel() {
  //
  // Defining the Network
  //
  int number;
  unsigned numberOfNodesInEachLayer;
  int seed = 19;
  std::cout << "\n enter how much hidden layer do you want:\t";
  std::cin >> number;
  // adding first layer
  Layer first(28*28);
  Layer *LayersCommonPointer = &first;

  while (number >= 1) {
    std::cout << "\n enter how much nodes you need in this layer:\t";
    std::cin >> numberOfNodesInEachLayer;
    Layer *L = new Layer(numberOfNodesInEachLayer);  // allocate on heap
    L->connectPrevious(LayersCommonPointer);
    LayersCommonPointer = L;
    L->randomizeWeightsBiases(seed);
    number--;
  }

  Layer *last = new Layer(10);  // allocate on heap
  last->connectPrevious(LayersCommonPointer);
  last->randomizeWeightsBiases(seed);
  LayersCommonPointer = last;







  // training section comes here:-----------------------------------------------------------------------------<start>

  // opening the binary file
  std::ifstream imagefile("../../dataSetsForTraining/train-images.idx3-ubyte", std::ios::binary);
  // opening the lable file
  std::ifstream lablefile("../../dataSetsForTraining/train-labels.idx1-ubyte", std::ios::binary);
  // input section for how much hidden layer. and number of nodes in each layer

  // Skip IDX3 header (16 bytes for images)
  // Read image data
  char header[16];
  imagefile.read(header, 16);

  //reading the labels
  char headerIgnore[8];
  lablefile.read(headerIgnore, 8);


  unsigned char imageData[784]; // 28*28 pixels
  int label;
  while(imagefile.read(reinterpret_cast<char*>(imageData), 784) && lablefile.read(reinterpret_cast<char*>(label), 1)) {
    // DATA preparation part..................................................................................<start>
    // Convert to float and normalize
    float input[784];
    for(int i = 0; i < 784; i++) {
      input[i] = imageData[i] / 255.0f;
    }
    //label creation
    float arrayOflabel[10];
    for(int i = 0 ;i<10;i++){
      if (i == label){
        arrayOflabel[i] = 1.00f;
      }
      else{
        arrayOflabel[i] = 0.00f;
      }
    }
    // DATA preparatoin part ..................................................................................<end>


    // Looping for the weights and biases of a layer.......................................................................<star>
    Layer* LayerCommonPointerBackup = LayersCommonPointer;
    while(LayerCommonPointerBackup->m_connectedPrevious){
      Layer*Previous = LayerCommonPointerBackup->m_previousLayer;
      //code for weights correction ---------------------------------->
      float* weightMatrix = LayerCommonPointerBackup->m_weights;
      for(int i=0; i<(LayerCommonPointerBackup->m_nodes*Previous->m_nodes);i++){
        float Current, lower, upper;
        while(!(Current<=lower && Current<=upper)){
        
        float* OutputOfTheNetwork = ValueOfNetWorkCalculater(LayerCommonPointerBackup, input);
        //compairission with cost function
        Current = cost(OutputOfTheNetwork, arrayOflabel);
        // decreasing the weight
        weightMatrix[i] -=0.01f;
        OutputOfTheNetwork = ValueOfNetWorkCalculater(LayerCommonPointerBackup, input);
        lower = cost(OutputOfTheNetwork, arrayOflabel);
        weightMatrix[i] +=0.01f;
        // increaseing the weight
        weightMatrix[i] +=0.01f;
        OutputOfTheNetwork = ValueOfNetWorkCalculater(LayerCommonPointerBackup, input);
        upper = cost(OutputOfTheNetwork, arrayOflabel);
        weightMatrix[i] +=0.01f;
        if(Current<upper && Current>lower){
          weightMatrix[i]-=0.01f;
        }
        else if (Current>upper && Current<lower)
        {
          weightMatrix[i]+=0.01f;
        }
        else{
          weightMatrix[i]+=0.01f;
        }
        }
      }
      //code for biases correction ---------------------------------->
      float* biasMatrix = LayerCommonPointerBackup->m_biases;
      for(int i = 0; i<(LayerCommonPointerBackup->m_nodes);i++){
        float Current, lower, upper;
        while(!(Current<=lower && Current<=upper)){
        
        float* OutputOfTheNetwork = ValueOfNetWorkCalculater(LayerCommonPointerBackup, input);
        //compairission with cost function
        Current = cost(OutputOfTheNetwork, arrayOflabel);
        // decreasing the weight
        biasMatrix[i] -=0.01f;
        OutputOfTheNetwork = ValueOfNetWorkCalculater(LayerCommonPointerBackup, input);
        lower = cost(OutputOfTheNetwork, arrayOflabel);
        biasMatrix[i] +=0.01f;
        // increaseing the weight
        biasMatrix[i] +=0.01f;
        OutputOfTheNetwork = ValueOfNetWorkCalculater(LayerCommonPointerBackup, input);
        upper = cost(OutputOfTheNetwork, arrayOflabel);
        biasMatrix[i] +=0.01f;
        if(Current<upper && Current>lower){
          biasMatrix[i]-=0.01f;
        }
        else if (Current>upper && Current<lower)
        {
          biasMatrix[i]+=0.01f;
        }
        else{
          biasMatrix[i]+=0.01f;
        }
        }
      }
    
      LayerCommonPointerBackup = LayerCommonPointerBackup->m_previousLayer;
    }

    
  }

  
}