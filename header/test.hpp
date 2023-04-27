#ifndef _TEST_FLAG_HPP
#define _TEST_FLAG_HPP

#include "Command.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
class TestFlag : public Command{
private:
  string t;
public:
  TestFlag(string s)
  {
    t = s;
  }
  void setFileName(string s)
  {
  }
  bool execute(){
    const char* command = new char[t.length()+1];
    string flag;
    bool flagFound = false;
    int i = 0;
    while( i < t.size() && flagFound == false)
      {
	if (t.at(i) == '-')
	  {
	    flagFound = true;
	    flag = flag + t.at(i) +t.at(i+1);
	    t = t.substr(i+3);
	    // cout << t << endl;
	  }
	i++;
      }
   
    if ( flag == "")
      {
	flag = "-e";
      }
   
    string commandtemp;
    for (int i = 0; i < t.size();i++)
      {
	if( t.at(i) != ' ')
	  {
	    commandtemp = commandtemp + t.at(i);
	  }
      }
    command = commandtemp.c_str();

    // cout << "flag = " << flag << endl;
    struct stat sb;
    if (flag == "-e")
      {
	if(stat(command,&sb) == 0)
	  {
	    cout << "(True)" << endl;
	    return true;
	  }
      }
    else if (flag == "-f")
      {
	if(stat(command,&sb) == 0 && S_ISREG(sb.st_mode))
	  {
	    cout << "(True)" << endl;
	    return true;
	  }
      }
    else if (flag == "-d")
      {
	if(stat(command,&sb) == 0 && S_ISDIR(sb.st_mode))
          {
            cout << "(True)" << endl;
            return true;
          }
      }


  

  cout << "(False)" << endl;
    return false;
  };
};
#endif
