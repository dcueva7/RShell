#ifndef INRD_HPP
#define INRD_HPP

#include "Command.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>

using namespace std;

class InRD : public Command{
public:
  string file;

  void setFileName(string f)
  {
    file = f;
    //  cout <<"INPUTTTTTTTTTTTTTTTTt FILE NAME" << endl;
    //cout << file << endl;
  }
  bool execute(){
    //cout << "started the input redirection execution" << endl;
     string fileNameTemp = "";
    for ( int i = 0; i < file.size(); i++)
      {
	if(file.at(i) == ' ')
	  {
	    // cout << "WHAT THE FUCKKKKKKKKKKKK" << endl;
	  }
	else
	  {
	    fileNameTemp = fileNameTemp + file.at(i);
	  }

      }
    file = fileNameTemp;
    int savein = dup(0);
    FILE* fileTemp = fopen(file.c_str(), "a+");
    int fd = fileno(fileTemp);
    //int savein = dup(0);
    //cout << "savein = " << savein << endl;
    //cout << "int fd = " << fd << endl;

    
    if(fd < 0){
      perror("error");
      return false;
    }
    
    close(0);
    dup2(fd,0);
    //cout << "just made dup2() " << endl;
    bool check = leftChild->execute();
    close(0);
    dup2(savein,0); //restore normal in
    //fclose(fileTemp);
    return check;
  }

};
#endif

