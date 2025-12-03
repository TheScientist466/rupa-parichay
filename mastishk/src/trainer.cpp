#include <iostream>
#include "mastishk/Layer.hpp"

int main(){
    int number;
    unsigned numberOfNodesInEachLayer;
    //input section for how much hidden layer. and number of nodes in each layer respecively
    std::cout<<"\n enter how much hidden layer do you want:\t";
    std::cin>>number;
    Layer* Layers = new Layer(number+2);
    while (number>=1){
        std::cout<<"\n enter how much nodes you need in this layer:\t";
        std::cin>>numberOfNodesInEachLayer;
        Layers[number] = Layer(numberOfNodesInEachLayer);
        number--;
    }
    //adding first and last layer
    Layers[0]=Layer(28*28);
    Layers[number+1] = Layer(10);
    
    
}