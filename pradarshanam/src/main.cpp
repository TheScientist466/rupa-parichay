#include "renderer.hpp"
#include <iostream>

#include <mastishk/Layer.hpp>

int main() {
  std::cout<<"Wellcome to Rupa-parichay, A ML algorithem to detect digits";
  std::cout<<"Chose any one to proceed:\n";
  std::cout<<"1. Train the model\n"<<"2. Test the model\n"<<"3. Exit\n";
  int choice;
  std::cin>>choice;
  switch(choice){
    case 1:
      {
        trainAndSaveModel();
        break;
      }
    case 2:
      {
        Renderer renderer;
        return renderer.run();
        break;  
      }
    case 3:
      {
        exit(0);
      }
  }
  
}
