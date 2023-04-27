#ifndef _SEMI_HPP
#define _SEMI_HPP

#include "Command.hpp"

using namespace std;
class Semi : public Command{
        public:
  void setFileName(string s)
  {

  }
                bool execute(){
		  bool fix = false;
		  if (this->leftChild  != NULL)
		    {
		      if( this->leftChild->execute() == true)
			{
			  fix = true;;
			}
		    }
		  if (this->rightChild  != NULL)
		    {
		      this->rightChild->execute();
		    }
		    return true;
		};
};
#endif
