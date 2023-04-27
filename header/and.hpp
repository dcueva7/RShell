#ifndef AND_HPP
#define AND_HPP

#include "Command.hpp"

using namespace std;

class And : public Command{
		
	public:
  void setFileName(string s)
  {
  }
		bool  execute(){
		  // cout << "started the and" << endl;
			
		  // cout << this->leftChild->execute() << endl;
			  if(this->leftChild->execute() == true){
			    //perror ("error");
			    if (this->rightChild->execute() == true)
			      {
				//cout << "THIS CAN BE EXECUTED" << endl;
				return true;
			      }
			    else
			      {
				//cout << "this cant be executed" << endl;
				return false;
			      }
			  }
			  else
			    {
			      //cout << "this cannt be executed" << endl;
			      return false;
			    }
			  /*	cout << "left child failed to execute" << endl;
					r
				}
			}
			if(this->rightChild->execute() == -1){
			       
			  cout << "the right child procces failed " << endl;     
			  return -1;
			}
			return 1;*/
			
		}
}; 

#endif
