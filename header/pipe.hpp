#ifndef PIPE_HPP
#define PIPE_HPP

#include "Command.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<fcntl.h> 

using namespace std;

class Pipe : public Command{
public:
  string file;

  void setFileName(string f)
  {
    file = f;
    // cout <<"PIPEEEEEEEEEEEE FILE FILE NAME";
    // cout << file << endl;

  }
  bool execute(){
    // cout << "started the PIPE" << endl;
    int p[2];
    p[0] = 0;
    p[1] = 0;
    //cout << p[0] << endl;
    //cout << p[1] << endl;
    return true; 
    if (pipe(p) == -1)
      {
	cout << "the pipe failed" << endl;
      }
    //cout << "this is pipe " << pipe(p) << endl;
  cout << "hello" << endl;
    //return true;
    // cout << "reated teh pipe" << endl;
    

    for(int i = 0; i < file.size(); i++)
      {
	if( file.at(i) == ' ')
	  {
	    //cout << "PIPE SPACE IN FILE" << endl;
	  }
      }
    char* filechar = (char*)file.c_str();
    vector<string> t;
    char* delim = " ";
    char* tok = strtok(filechar,delim);
    while(tok != NULL){
      t.push_back(tok);
      tok = strtok(NULL, delim);
    }
    char *in[t.size()+1];
    
    for(int i = 0; i < t.size(); i++){
      //cout << "t.at(i) = " << t.at(i) << endl;
      in[i] = (char*)(t.at(i).c_str());
    }
    in[t.size()] = NULL;
    cout << "made it before the dups" << endl;
    
    
    int out = dup(1);
    int indup = dup(0);
    //cout << "out dup = " << out << endl;
    //cout << "in dup = " << indup << endl;
      if ( indup < 0 )
	{
	  perror("error opeinging input");
	  return false;
	}
      if( out < 0)
	{
	  perror("error opening output");
	  return false;
	}
      cout << "before the dup2" << endl;
      if(dup2(p[1],1) == -1)
	{
	  perror("dup2 doesnt work");
	  return false;
	}
      //cout << "inDup2 = " << endl;
      
      if( dup2(p[0],0) == -1)
	{
	  perror("dup2 doesn't work");
	  return false;
	}
      
      
       cout << "before the leftexecute" << endl;
      bool check = leftChild->execute();
      //cout << "after check of pipe" << endl;
      close(p[1]);
	    if (check == false)
	      {
		return false;
	      }

    return true;
  }

};
#endif

