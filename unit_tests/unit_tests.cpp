#ifndef UNIT_TESTS
#define UNIT_TESTS
#include "gtest/gtest.h"
#include "../header/Command.hpp"
#include "../header/Node.hpp"
#include "../header/and.hpp"
#include "../header/or.hpp"
#include "../header/semi.hpp"
#include "../header/test.hpp"
#include "../header/inrd.hpp"
#include "../header/outrd.hpp"
#include "../header/twooutrd.hpp"
#include "../header/pipe.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


TEST(SingleCommand, EchoTest)
{
	vector<string> v;
        v.push_back("echo");
	v.push_back("this is a test");
        Command *e = new Node(v);
        EXPECT_EQ(true,e->execute());

  
}

TEST(SingleCommand2, LsTest)
{
	vector<string> v;
        v.push_back("ls");
        Command *e = new Node(v);
        EXPECT_EQ(true,e->execute());

  
}


TEST(And, AndTest){
	vector<string> v;
	vector<string> m;
	v.push_back("echo");
	v.push_back("hello");
	Command *a = new And;
	Command *l = new Node(v);
	m.push_back("echo");
	m.push_back("bye");
	Command *r = new Node(m);
	a->leftChild = l;
	a->rightChild = r;
	EXPECT_EQ(true, a->execute());
	
}

TEST(And2, AndLSEcho){
        vector<string> v;
        vector<string> m;
        v.push_back("ls");
        Command *a = new And;
        Command *l = new Node(v);
        m.push_back("echo");
        m.push_back("cool");
        Command *r = new Node(m);
        a->leftChild = l;
        a->rightChild = r;
        EXPECT_EQ(true, a->execute());

}

TEST(Or, OrTest){
        vector<string> v;
        vector<string> m;
        v.push_back("hey");
        Command *a = new Or;
        Command *l = new Node(v);
        m.push_back("ls");
        Command *r = new Node(m);
        a->leftChild = l;
        a->rightChild = r;
        EXPECT_EQ(true, a->execute());

}

TEST(Or2, OrTest2){
        vector<string> v;
        vector<string> m;
        v.push_back("bad");
        Command *a = new Or;
        Command *l = new Node(v);
        m.push_back("ls");
        Command *r = new Node(m);
        a->leftChild = l;
        a->rightChild = r;
        EXPECT_EQ(true, a->execute());

}

TEST(Semi, SemiTest){
        vector<string> v;
        vector<string> m;
        v.push_back("echo");
	v.push_back("\"hows it going\"");
	v.push_back(";");
        Command *a = new Semi;
        Command *l = new Node(v);
        m.push_back("ls");
        Command *r = new Node(m);
        a->leftChild = l;
        a->rightChild = r;
        EXPECT_EQ(true, a->execute());

} 

TEST(Parentheses, ParentTest){
        vector<string> v;
        vector<string> m;
	v.push_back("(");
        v.push_back("echo");
	v.push_back("parentheses");
	v.push_back(")");
        Command *a = new And;
        Command *l = new Node(v);
        m.push_back("ls");
        Command *r = new Node(m);
        a->leftChild = l;
        a->rightChild = r;
        EXPECT_EQ(false, a->execute());

} 

TEST(Parentheses2, ParentTest2){
        vector<string> v;
        vector<string> m;
	v.push_back("(");
        v.push_back("echo");
	v.push_back("parentheses");
	v.push_back("echo");
	v.push_back("works");
	v.push_back(")");
        Command *a = new Or;
        Command *l = new Node(v);
        m.push_back("ls");
        Command *r = new Node(m);
        a->leftChild = l;
        a->rightChild = r;
        EXPECT_EQ(a->execute(), a->execute());

} 

TEST(LiteralTest, LitTest){
        vector<string> v;
        v.push_back("test");
	v.push_back("-e");
	v.push_back(" ../src");
        Command *a = new Node(v);
        
        EXPECT_EQ(false, a->execute());

} 

TEST(LiteralTest2, LitTest2){
        vector<string> v;
        v.push_back("test");
	v.push_back("-f");
	v.push_back(" header/Command.hpp");
        Command *a = new Node(v);
        
        EXPECT_EQ(true, a->execute());

}

TEST(LiteralTest3, LitTest3){
        vector<string> v;
        v.push_back("test");
	v.push_back("-d");
	v.push_back(" header");
        Command *a = new Node(v);
        
        EXPECT_EQ(true, a->execute());

}

TEST(LiteralTst4, LtTest4){
        vector<string> v;
        v.push_back("test");
	v.push_back("-d");
	v.push_back(" src");
        Command *a = new Node(v);
        
        EXPECT_EQ(true, a->execute());

}

TEST(LiteralTest4, LitTest4){
        vector<string> v;
        v.push_back("test");
	v.push_back("-d");
	v.push_back(" hello");
        Command *a = new Node(v);
        
        EXPECT_EQ(false, a->execute());

}

TEST(LiteralTest5, LitTest5){
        vector<string> v;
        v.push_back("test");
	v.push_back("-f");
	v.push_back(" nofile");
        Command *a = new Node(v);
        
        EXPECT_EQ(false, a->execute());

}

TEST(SyblTest, SymTest3){
        string v = "-d header";

        Command *a = new TestFlag(v);

        EXPECT_EQ(true, a->execute());

}


TEST(SymblTest, SymTest2){
        string v = "-f header/Command.hpp";

        Command *a = new TestFlag(v);

        EXPECT_EQ(true, a->execute());

}


TEST(SyblTst, SymTest3){
	string v = "-e header/test.hpp";

        Command *a = new TestFlag(v);
        
        EXPECT_EQ(true, a->execute());

}

TEST(yblTst, SymTest4){
  string v = "-e header/bla.hpp";

  Command *a = new TestFlag(v);

  EXPECT_EQ(false, a->execute());

}

TEST(SymblTest5, SymTest5){
        string v = "-f header/ok.hpp";

        Command *a = new TestFlag(v);

        EXPECT_EQ(false, a->execute());

}


TEST(inredir, inredirtest){
  vector<string> v;
  v.push_back("echo");
  v.push_back("world");
  Command *a = new Node(v);
  Command *b = new InRD();
  b->setFileName("test1");
  b->leftChild = a;
  

  EXPECT_EQ(true, b->execute());

}

TEST(inredir2, inredirtest2){
  vector<string> v;
  v.push_back("echo");
  v.push_back("sick");
  Command *a = new Node(v);
  Command *b = new InRD();
  b->setFileName("test2");
  b->leftChild = a;


  EXPECT_EQ(true, b->execute());

}

TEST(outredir, outredirtest){
  vector<string> v;
  v.push_back("echo");
  v.push_back("world");
  Command *a = new Node(v);
  Command *b = new OutRD();
  b->setFileName("test3");
  b->leftChild = a;


  EXPECT_EQ(true, b->execute());

}
TEST(outredir2, outredirtest2){
  vector<string> v;
  v.push_back("echo");
  v.push_back("cool");
  Command *a = new Node(v);
  Command *b = new OutRD();
  b->setFileName("test4");
  b->leftChild = a;


  EXPECT_EQ(true, b->execute());

}

TEST(twooutredir, twooutredirtest){
  vector<string> v;
  v.push_back("echo");
  v.push_back("dope");
  Command *a = new Node(v);
  Command *b = new TwoOutRD();
  b->setFileName("test4");
  b->leftChild = a;


  EXPECT_EQ(true, b->execute());

}
TEST(twooutredir2, twooutredirtest2){
  vector<string> v;
  v.push_back("echo");
  v.push_back("dope2");
  Command *a = new Node(v);
  Command *b = new TwoOutRD();
  b->setFileName("test5");
  b->leftChild = a;


  EXPECT_EQ(true, b->execute());

}
TEST(pipe, pipetest){
  vector<string> v;
  v.push_back("echo");
  v.push_back("dope");
  Command *a = new Node(v);
  Command *b = new Pipe();
  b->setFileName("test6");
  b->leftChild = a;


  EXPECT_EQ(true, b->execute());

}
TEST(pipe2, pipetest2){
  vector<string> v;
  v.push_back("echo");
  v.push_back("dope3");
  Command *a = new Node(v);
  Command *b = new Pipe();
  b->setFileName("test7");
  b->leftChild = a;


  EXPECT_EQ(true, b->execute());

}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
