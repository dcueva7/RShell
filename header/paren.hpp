#ifndef PAREN_HPP
#define PAREN_HPP

#include "Command.hpp"

using namespace std;

class Paren : public Command{

public:
  void setFileName(string s)
  {

  }
  bool execute(){
    if (this->leftChild  != NULL)
      {
       
	this->leftChild->execute();
      }
    /*if (this->rightChild  != NULL)
      {
	
	this->rightChild->execute();
	}*/
    return true;


};
    
  };
#endif
