#ifndef OR_HPP
#define OR_HPP

#include "Command.hpp"
#include <stdio.h>


using namespace std;

class Or : public Command{
	public:
  void setFileName( string s)
  {
  }
		bool  execute(){
		  //cout << "started the or" << endl;
		  if(leftChild->execute() == true){
		    //cout << "error in executing left child" << endl;
			  // perror ("error");
			  //	exit(1);
		    return true;
			}
		  else if(rightChild->execute() == true){
		    return true;
		  }
		  else{
		    
		    perror ("error");
				exit(1);


			}
			/*	if(rightChild->execute() != -1){
				perror ("error");
				exit(1);
			}*/

		  return false;
		} 
  
};
#endif


