#pragma once
#include <cstddef>
#include <stdint.h>

class Layer {
public:
    Layer(unsigned int n_nodes);
    ~Layer();
    void connectPrevious(Layer* prev);       
    void calculateActivations(float*firstLayerInput);
    void randomizeWeightsBiases(uint64_t seed);
    float* producingTheActivation();//takes out the value of activation function.
    bool ifPreviousLayer();
    size_t numberOfNodes();
    friend void trainAndSaveModel();
    friend float *ValueOfNetWorkCalculater(Layer *currentLayer, float *input);
private:
    size_t m_nodes;
    float* m_biases;
    float* m_activations;
    bool m_connectedPrevious;
    Layer* m_previousLayer;
    float* m_weights;

    float (*activationFunc)(float x);
    
};

