#ifndef NODE_HPP
#define NODE_HPP

#include "Command.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include "and.hpp"
#include "or.hpp"
#include "semi.hpp"
#include "test.hpp"

using namespace std;

class Node : public Command{
	private:
		vector<string> t;
	public:
		Node(vector<string> s){
			t = s;
		}
  void setFileName(string s)
  {

  }
		 bool execute(){
			char *in[t.size()+1];
			
                        for(int i = 0; i < t.size(); i++){
                                in[i] = (char*)(t.at(i).c_str());
				//cout << "t  =  "<<( t.at(i).c_str()) << endl;
                        }
			if (t.at(0) == "exit")
			  {
			    exit(0);
			  }
			if(t.at(0) == "test")
			  {
			    string testTemp;
			    for (int i = 1; i < t.size(); i++)
			      {if(i > 1)
				  {
				    testTemp =   testTemp + " "  + t.at(i);
				  }
				else
				  {
				    testTemp = testTemp + t.at(i);
				  }
				
			      }
			    bool testResult = false;
			    // cout << testTemp << endl;
			    Command* temp = new TestFlag(testTemp);
			    testResult = temp->execute();
			    return testResult;
			  }
			
			in[t.size()] = NULL;
			int failed = 0;
			pid_t child;
			//cout << "we are about to fork" << endl;
			child = fork();
			//cout << child << endl;
			//	cout << "we just forked" << endl;
        		if(child == 0){
			  // cout << "out to test the child" << endl;
			   //cout <<  execvp(in[0],in) << endl;
			  // cout << "there should be nothing in between" << endl;
			  if (execvp(in[0],in) == -1)
			    {
			      failed = -1;
			      // cout <<"failed = " <<  failed << endl;
			       perror ("error");
			      //cout << "error because child ==  0 " << endl;
				exit(1);
			    }
        		}
        		else if(child > 0){
			  // cout << "parent started" << endl;
			   int status;
			   //cout << "about to wait until child process runs" << endl;
			   waitpid(child, &status, 0);
			   // cout << " echild process should have run now" << endl;
			 
			   if (WEXITSTATUS(status) != 0)
			     {
			       // cout <<" the process failed" << endl;
			       return false;
			     }
			   else
			     {
			       //cout << " the process worked!" << endl;
			       return true;
			     }
			   /* if( execvp(in[0],in)== -1){
				   cout << "in" << endl;
                        		perror("error");
					
						exit(1);
						cout << "exited and about to return" << endl;
						return -1;
						
                		}
        		}	
        		else{
                		while(wait(0) == -1){
                        		perror ("error");
                        		exit(1);
						return -1;
                		}	
				}*/
			}
			return false;
		 }


};

#endif
