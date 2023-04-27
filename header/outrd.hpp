#ifndef OUTRD_HPP
#define OUTRD_HPP

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

class OutRD : public Command{
public:
  string file;
  
  void setFileName(string f)
  {
    file = f;
    // cout <<"THIS IS THE FILE NAME" << endl;
    //cout << file << endl;

  }
  bool execute(){
    //cout << "started the output redirection" << endl;
    int savein = dup(1);
    FILE* fileTemp = fopen(file.c_str(), "a+");
    int fd = fileno(fileTemp);
    //int savein = dup(0);



    if(fd < 0){
      perror("error");
      return false;
    }

    close(1);
    dup2(fd,1);
    bool check = leftChild->execute();
    close(1);
    dup2(savein,1); //restore normal in
    // fclose(fileTemp);
    return check;

  } 
  
};
#endif
