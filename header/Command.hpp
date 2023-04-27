#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <stdio.h>

using namespace std;
class Command{


        public:
                Command* leftChild = NULL;
                Command* rightChild = NULL;
  virtual bool execute() = 0;
  virtual void setFileName(string s) = 0;



};
#endif

