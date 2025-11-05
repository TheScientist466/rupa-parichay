#pragma once

#include "Layer.hpp"
#include <vector>

class Network {
public:
    Network(const unsigned int* layerNumNodes, const unsigned int numLayers);

    void appendLayer(Layer* layer);

private:
    std::vector<Layer*> m_layers;
    Layer* m_outLayer; //alias for last / output layer in m_layers
};
