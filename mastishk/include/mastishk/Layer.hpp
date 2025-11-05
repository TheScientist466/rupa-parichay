#pragma once

#include <stdint.h>

class Layer {
public:
    Layer(unsigned int n_nodes);
    ~Layer();
    
    float operator[](unsigned int index);

    void connectPrevious(Layer* prev);
    void calculateActivations();
    void randomizeWeightsBiases(uint64_t seed);

private:
    unsigned int m_nodes;

    float* m_activations;
    float* m_biases;

    bool m_connectedPrevious;
    Layer* m_previousLayer;
    float* m_weights;
};
