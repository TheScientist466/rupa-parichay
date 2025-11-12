#include "mastishk/Layer.hpp"
#include <iostream>
#include "mastishk/math.hpp"
#include <random>

Layer::Layer(unsigned int n_nodes) : 
    m_nodes(n_nodes),
    m_connectedPrevious(false),
    m_previousLayer(nullptr) 
{
    m_activations = new float[m_nodes];
    m_biases = new float[m_nodes];
    m_weights = nullptr; // Weights will be allocated when connecting to previous layer
}

Layer::~Layer() {
    delete[] m_activations;
    delete[] m_biases;
    if(m_connectedPrevious)
        delete[] m_weights;
}

void Layer::connectPrevious(Layer* prev) {
    m_previousLayer = prev;
    m_connectedPrevious = true;
    size_t totalSize = m_nodes * m_previousLayer->m_nodes;
    float* m_weights = new float[totalSize];
}

void Layer::randomizeWeightsBiases(uint64_t seed) { 
    size_t totalSize = m_nodes*m_previousLayer->m_nodes;
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0); 
    for(size_t i = 0; i < totalSize; i++) {
        m_weights[i] = (float)distribution(generator);
    }
    for(size_t i = 0; i < m_nodes; i++) {
        m_biases[i] = (float)distribution(generator);
    }
}

void Layer::calculateActivations(){
    Matrix<float> currAcctivations = { .rows = m_nodes, .cols = 1, .data = m_activations };
    Matrix<float> weight = {.rows = m_nodes, .cols =  m_previousLayer->m_nodes, .data = m_weights};
    Matrix<float> previousActivations = {.rows = m_previousLayer->m_nodes, .cols = 1, .data = m_previousLayer->m_activations};
    Matrix<float> biases = {.rows = m_previousLayer->m_nodes, .cols = 1, .data = m_previousLayer->m_activations};
    Matrix<float> product = multiplyMatrix(weight, previousActivations);
    currAcctivations = addMatrix(product, biases);
    delete[] product.data;
    
}
float& Layer::operator[](size_t index) {
    return m_activations[index];
}

