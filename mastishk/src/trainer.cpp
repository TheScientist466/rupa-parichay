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

  // training section comes here:---------------------------------------->

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
    // Pass through network
    Layer* LayerCommonPointerBackup = LayersCommonPointer;
    float* OutputOfTheNetwork = ValueOfNetWorkCalculater(LayerCommonPointerBackup, input);

    //compairission with cost function
    float DifferenceBetweenExpectationAndReality = cost(OutputOfTheNetwork, arrayOflabel);
  }

  
  

  
  

  

  
  
  
}