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
    m_biases = nullptr;
    m_weights = nullptr; // Weights will be allocated when connecting to previous layer
}

Layer::~Layer() {
    delete[] m_activations;
    if(m_connectedPrevious)
        delete[] m_weights;
        delete[] m_biases;
}

void Layer::connectPrevious(Layer* prev) {
    m_previousLayer = prev;
    m_connectedPrevious = true;
    size_t totalSize = m_nodes * m_previousLayer->numberOfNodes();
    m_weights = new float[totalSize];
    m_biases = new float[m_nodes];
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

void Layer::calculateActivations(float* firstlayerInput){
    
    if(firstlayerInput == nullptr){
        Matrix<float> currAcctivations = { .rows = m_nodes, .cols = 1, .data = m_activations };
        Matrix<float> weight = {.rows = m_nodes, .cols =  m_previousLayer->m_nodes, .data = m_weights};
        Matrix<float> previousActivations = {.rows = m_previousLayer->m_nodes, .cols = 1, .data = m_previousLayer->producingTheActivation()};
        Matrix<float> biases = {.rows = m_previousLayer->m_nodes, .cols = 1, .data = m_previousLayer->m_biases};
        Matrix<float> product = multiplyMatrix(weight, previousActivations);
        currAcctivations = addMatrix(product, biases);
        delete[] product.data;
    }else{
        m_activations =firstlayerInput;
    }
    
    
}
float* Layer::producingTheActivation() {
    return m_activations;
}
size_t Layer::numberOfNodes(){
    return m_nodes;
}
bool Layer::ifPreviousLayer(){
    return m_connectedPrevious;
}

