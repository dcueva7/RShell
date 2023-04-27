#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include "../header/Node.hpp"
#include "../header/and.hpp"
#include "../header/or.hpp"
#include "../header/semi.hpp"
#include "../header/Command.hpp"
#include "../header/paren.hpp"
#include "../header/test.hpp"
#include "../header/outrd.hpp"
#include "../header/pipe.hpp"
#include "../header/inrd.hpp"
#include "../header/twooutrd.hpp"
#include <stdio.h>

using namespace std;

Command* parse(string s){
	int i = 0;
        Command* r = NULL;
        Command* root = NULL;
        int j = 0;
        string str;
        bool hit = false;
        string temp;
        vector<string> t;
        stringstream com(s);
        if(s.at(0) != '#' && s.find("#") != string::npos){
                getline(com,temp, '#');
                s = temp;
        }
	int k = 0;
	string fun;
	string ok;
	int quote = 0;
	int parenCounter = 0;
	bool bracket = false;			 
	Command* testTemp;
	Command* redirTemp;
	string rightstr; 
	bool rexist;


       
	while(i < s.size()){
	 
          if(s.at(i) == '\"')
	    {
	      quote++;
	      
	     
	    }
	  if(s.at(i) == '[')
	    {
	      bracket = true;
	      i++;
	      string sBracket;
	      while(s.at(i) !=']')
		{
		  sBracket = sBracket + s.at(i);
		  i++;
		}
	       testTemp = new TestFlag(sBracket);
	     
	    }
	   if (s.at(i) == '(')
	    {
	      
	      int icheck = i;
	      icheck++;
	      i++;
	      string sParen;
	      while (icheck < s.size() && s.at(icheck) != ')' ||  parenCounter != 0)
		{
		  if(s.at(icheck) == ')')
		    {
		      parenCounter--;
		    }
		  if(s.at(icheck) == '(')
		    {
		      parenCounter++;
		      // cout << parenCounter << endl;
		    }
		  sParen = sParen + s.at(icheck);
		  icheck++;
		}
	      // cout << "icheck = " << icheck << "s.size() = " << s.size() << endl;
	      if(icheck >= s.size())
		{
		  perror("no closing paren");
		  exit(1);
		}
	      
	      // cout << sParen << endl;
	      Command* exParen = parse(sParen);
	      Command* getParse = new Paren;
	      
		if (r == NULL)
		  {
		    r = getParse;
		    root = getParse;
		    r->leftChild = exParen;
		    
		  }
		else
		  {
		    if (r->rightChild == NULL)
			  {
			    r->rightChild = exParen;
			    root = r;
			    r = getParse;
			    r->leftChild = root;

			  }
		  }
		//cout << sParen << endl;
		i = icheck;
		j = i;
	    }
	   if (s.at(i) == '>' && s.at(i-1)!= '>')
	     {
	       if (s.at(i+1) == '>')
		 {
		   Command* temp2;
		   if(rexist == true)
		     {
		       char* arr = new char[i-j];
		       string stemp = s.substr(j, i-j);
		       redirTemp->setFileName(stemp);
		       //rexist = false;
		       temp2 = redirTemp;
		     }
		   else{
		   rexist = true;
		   // cout << "Outputredirection with >> activated" << endl;
                   char *arr = new char[i-j];
                   string stemp = s.substr(j, i-j);
                   arr = (char*)(stemp.c_str());
                   char* delim = " ";
                   char* tok = strtok(arr,delim);
                   while(tok != NULL){
                     t.push_back(tok);
                     tok = strtok(NULL, delim);
                   }
                   for (int i = 0; i < t.size(); i++)
                     {
		       // cout << t.at(i) << endl;
                     }

                    temp2 = new Node(t);
		   }
                   Command *lol = new TwoOutRD();
                   redirTemp = lol;
		   //cout << " just made the twooutrd object" << endl;

                   if(r == NULL)
                     {
                       r = lol;
                       root = lol;
                       r->leftChild = temp2;
                     }

                   else

                     {
                       if (r->rightChild == NULL)
                         {
                           r->rightChild = temp2;
                           root = r;
                           r = lol;
                           r->leftChild = root;
                         }
		     }
                   i += 3;
		   j = i;
		 
	     }
	       else
		 {
		   //cout << "Output redirection with > activated" << endl;
		   rexist = true;
		   char *arr = new char[i-j];
		   string stemp = s.substr(j, i-j);
		   arr = (char*)(stemp.c_str());
		   char* delim = " ";
		   char* tok = strtok(arr,delim);
		   while(tok != NULL){
		     t.push_back(tok);
		     tok = strtok(NULL, delim);
		   }
		   for (int i = 0; i < t.size(); i++)
		     {
		       
		       // cout << t.at(i) << endl;
		     }
		   
		   Command* temp2 = new Node(t);
		   Command *lol = new OutRD();
		   redirTemp = lol;
		   
		   
		   if(r == NULL)
		     {
		       r = lol;
		       root = lol;
		       r->leftChild = temp2;
		     }

		   else

		     {
		       if (r->rightChild == NULL)
			 {
			   r->rightChild = temp2;
			   root = r;
			   r = lol;
			   r->leftChild = root;
			 }
			 }
		   i += 2;
		   j = i;
		 }

	     }
	   if (s.at(i) == '<')
	     {

	       //cout << "start of the input redirection" << endl;
	      
	       rexist = true;
	       char *arr = new char[i-j];
	       string stemp = s.substr(j, i-j);
	       arr = (char*)(stemp.c_str());
	       char* delim = " ";
	       char* tok = strtok(arr,delim);
	       while(tok != NULL){
		 t.push_back(tok);
		 tok = strtok(NULL, delim);
	       }
	       for (int i = 0; i < t.size(); i++)
		 {
		   //  cout << t.at(i) << endl;
		 }

	       Command* temp2 = new Node(t);
	       Command *lol = new InRD();
	       redirTemp = lol;


	       if(r == NULL)
		 {
		   r = lol;
		   root = lol;
		   r->leftChild = temp2;
		 }

	       else

		 {
		   if (r->rightChild == NULL)
		     {
		       r->rightChild = temp2;
		       root = r;
		       r = lol;
		       r->leftChild = root;
		     }
		 }
	       i += 2;
	       j = i;
	     
	     }
	   if (s.at(i) == '|' && s.at(i+1) != '|' && s.at(i+1) != '|')
	     {
	       Command* temp2;
	       if(rexist == true)
		 {
		   char* arr = new char[i-j];
		   string stemp = s.substr(j, i-j);
		   redirTemp->setFileName(stemp);
		   // rexist = false;
		   temp2 = redirTemp;
		 }
	       else
		 {
		   //cout << "pipe is going to start" << endl;
	       rexist = true;
	       char *arr = new char[i-j];
	       string stemp = s.substr(j, i-j);
	       arr = (char*)(stemp.c_str());
	       char* delim = " ";
	       char* tok = strtok(arr,delim);
	       while(tok != NULL){
		 t.push_back(tok);
		 tok = strtok(NULL, delim);
	       }
	       for (int i = 0; i < t.size(); i++)
		 {
		   // cout << t.at(i) << endl;
		 }

	       temp2 = new Node(t);
		 }
	       Command *lol = new Pipe();
	       //cout << "created a pipe" << endl;
	       redirTemp = lol;


	       if(r == NULL)
		 {
		   r = lol;
		   root = lol;
		   r->leftChild = temp2;
		 }

	       else

		 {
		   if (r->rightChild == NULL)
		     {
		       r->rightChild = temp2;
		       root = r;
		       r = lol;
		       r->leftChild = root;
		     }
		 }
	       i += 2;
	       j = i;
	     

	     }
	  
             
	   if(s.at(i) == '&' && s.at(i+1) == '&' && quote%2 == 0){
             if(rexist == true)
	       {
		 char* arr = new char[i-j];
		 string stemp = s.substr(j, i-j);
		 redirTemp->setFileName(stemp);
		 rexist = false;
	       }
	     else{
	     char *arr = new char[i-j];
	     string stemp = s.substr(j,i-j);
                        
	     arr = (char*)(stemp.c_str());
	     char* delim = " & ";
	     char* tok = strtok(arr,delim);
	     while(tok != NULL){
	       t.push_back(tok);
	       tok = strtok(NULL, delim);
	     }
	     }
	     
	     hit = true;
	     Command* temp;
	     Command* temp2 = new Node(t);
	     if(bracket  == true)
	       {
		 temp = testTemp;
		 bracket = false;
	       }
	     else
	       {
		 temp = temp2;

	       }
	     /* if(rexist == true)
	       {
		 temp = redirTemp;
		 rexist = false;
	       }
	     else
	       {
		 temp = temp2;
	       }*/
	            
	     Command *lol = new And;
	     
	     if(r == NULL)
	       {
                         
		 r = lol;
		 root = lol;
		 r->leftChild = temp;
	       }

	     else

	       {
		 if (r->rightChild == NULL)
		   {
                                
		     r->rightChild = temp;
		     root = r;
		     r = lol;
                               
		     r->leftChild = root;

		   }
	       }
	      
	     i = i+2;
                        
	     j = i;
	   }
                
	   t.clear();
              
              
                if(s.at(i) == '|' && s.at(i+1) == '|' && quote%2 == 0){
                  
		  if(rexist == true)
		    {
		      char* arr = new char[i-j];
		      string stemp = s.substr(j, i-j);
		      redirTemp->setFileName(stemp);
		      rexist = false;
		    }
		  else
		    {
		      char *arr = new char[i-j];
                  string stemp = s.substr(j,i-j);
                  

                  arr = (char*)(stemp.c_str());

                        char* delim = "| ";

 			char* tok = strtok(arr,delim);
                        while(tok != NULL){
                                t.push_back(tok);
                                tok = strtok(NULL, delim);
                        }
		    }
                        

                        hit = true;
                        
			Command * temp;
                        Command* temp2 = new Node(t);
                        if(bracket  == true)
                          {
                            temp = testTemp;
                            bracket = false;
                          }
                        else
                          {
                            temp = temp2;

                          }

                        Command *lol = new Or;

                        if(r == NULL)
                          {

                            r = lol;
                            root = lol;
                            r->leftChild = temp;
                          }

                        else

                          {
                            if (r->rightChild == NULL)
                              {

                                r->rightChild = temp;
                                root = r;
                                r = lol;

                                r->leftChild = root;

                              }
                          }

                        i = i+2;
                        j = i;
                }
                t.clear();
               
                if(s.at(i) == ';'){
                  
		  if(rexist == true)
		    {
		      char* arr = new char[i-j];
		      string stemp = s.substr(j, i-j);
		      redirTemp->setFileName(stemp);
		      rexist = false;
		    }
		  else{
                  char *arr = new char[i-j];
                  string stemp = s.substr(j,i-j);
                 

                  arr = (char*)(stemp.c_str());

                        char* delim = "; ";
                        char* tok = strtok(arr,delim);
                        while(tok != NULL){
                                t.push_back(tok);
                                tok = strtok(NULL, delim);
                        }
		  }
	 		hit = true;
                        
			Command * temp;
                        Command* temp2 = new Node(t);
                        if(bracket  == true)
                          {
                            temp = testTemp;
                            bracket = false;
                          }
                        else
                          {
                            temp = temp2;

                          }

			Command *lol = new Semi;
                       

                        if(r == NULL)
                          {

                            r = lol;
                            root = lol;
                            r->leftChild = temp;
                          }

                        else

                          {
                            if (r->rightChild == NULL)
                              {

                                r->rightChild = temp;
                                root = r;
                                r = lol;

                                r->leftChild = root;

                              }
                          }
	   
                        i++;
                        j = i;
                }
                if ( hit == false)
                  {
                    i++;
                   
                  }
                else
                  {
                    hit = false;
                  }



        }
	if (j != i)
	  {
	    if(rexist == true)
	      {
		char* arr = new char[i-j];
		string stemp = s.substr(j, i-j);
		redirTemp->setFileName(stemp);
		rexist = false;
	      }
	    else{
	      char *arr = new char[i-j];
	    string stemp = s.substr(j,i-j);


	    arr = (char*)(stemp.c_str());

	    char* delim = " ";
	    char* tok = strtok(arr,delim);
	    while(tok != NULL){
	      t.push_back(tok);
	      tok = strtok(NULL, delim);
	}
	    }
	    Command *lol = new Semi;
	    Command * temp;
	    Command* temp2 = new Node(t);
	    if(bracket  == true)
	      {
		temp = testTemp;
		bracket = false;
	      }
	    else
	      {
		temp = temp2;

	      }

	
	if(r == NULL)
	  {

	    r = lol;
	    root = lol;
	    r->leftChild = temp;
	  }

	else

	  {
	    if (r->rightChild == NULL)
	      {

		r->rightChild = temp;
		root = r;
		r = lol;

		r->leftChild = root;

	      }
	  }
	  }

        return root;

}
int main(){
  while(1){
    string str;

    cout << "$ ";
    getline(cin,str);
    if(str == "")
      {
	
      }
    else{
    Command* temp = parse(str);
    if(temp->execute() == false){
	exit(1);
    }
    }

  }
  

  
  return 1;
}
