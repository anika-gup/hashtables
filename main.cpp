#include <iostream>
#include "Student.h"
#include "Node.h"
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

void ADD(int &size, Node* node, Node** &current) ; 
void PRINT(int &size, Node** &current);
void DELETE(int &size, int ID, Node** &current);
Node** REHASH(int &size, Node** &current, Node* node);




int main() {
  //creating example node:
  Student* exStudent = new Student();
  exStudent->setID(123);
  Node* exNode = new Node(exStudent);
  cout << exNode->getStudent()->getID() << endl;
   
  int quit = 0;
  int size = 100;
  int numberOfStudents = 0;
  Node** current = new Node*[size];
  for (int a=0; a<size; a++) {
    current[a] = NULL;
  }
  
  while (quit==0) {
    
    cout << "Choices: ADD   PRINT   DELETE   QUIT " << endl;
    char input[50];
    cin >> input;
    if (strcmp(input, "ADD")==0) {
      // credit for reading in a file: https://mathbits.com/MathBits/CompSci/Files/End.htm
      // credit for first and last name txt files: https://github.com/dominictarr/random-name/tree/master

      
      // access first name file
      ifstream fin;
      char firstname[20];
      fin.open("FirstNames.txt");
      fin >> skipws;

      // access last name file
      ifstream lin;
      char lastname[20];
      lin.open("LastNames.txt");
      lin >> skipws;
      
      int inputNumOfStudents=0;
      
      cout << "How many students would you like to add?  ";
      cin>> inputNumOfStudents ;
    
     if (numberOfStudents!=0) {// finding the right index...
	for (int b=0; b<numberOfStudents; b++) {
	  fin  >> firstname;
	  lin >> lastname;
	}
      }

      srand(time(0));
      for (int a = 0; a<inputNumOfStudents ; a++) {
	Student* s = new Student();
	int ID = numberOfStudents + a;
	fin >> firstname;
	lin >> lastname;
	float GPA = static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(4.0-0.1));
	//cout << "name: " << firstname << " " << lastname;
	//cout << "  ID: " << ID << " GPA: " << GPA << endl;
	s->setID(ID);
	s->setGPA(GPA);
	s->setFName(firstname);
	s->setLName(lastname);
	Node* n = new Node(s);
	ADD(size, n, current);
	
	
      }
      numberOfStudents = numberOfStudents + inputNumOfStudents;
    }
    else if (strcmp(input, "PRINT")==0) {
      //print funct
      PRINT(size, current);
    }
    else if (strcmp(input, "DELETE")==0) {
      // delete funct
      cout << "ID of who you wanna delete: " << endl;
      int ID;
      cin >> ID ;
      DELETE(size, ID, current);
    }
    else if (strcmp(input, "QUIT") ==0) {
      quit = 1;
    }
  }
  return 0;
}

void ADD (int &size, Node* node, Node** &current) {
  // some kind of hash function using student ID (and also inclusive of size, so that if size changes then the order gets changed too).
  // if there's something at that spot, then do a linked list thing
  //--as in, if there's something there, check if value is > than head.
  // if there are already 3 things in the linked list, call REHASH(with all variables :))
  //cout << "ADDING A STUDENT!" << endl;
  int ID = node->getStudent()->getID();
  //cout << "size: " << size << "   id: " << ID << endl;
  int index = ID % size;
  //cout << "index: " << index << endl;
 
  if (current[index]==NULL) {
    // first value
    //cout << "first val" << endl;
    current[index] = node;
    current[index]->setNext(NULL);
    //cout << current[index]->getStudent()->getFName() << endl;
  }
  else if (current[index]->getNext()==NULL) {
      // second value
    current[index]->setNext(node);
    current[index]->getNext()->setNext(NULL);
    //cout << "second val" << endl;
  }
  else if (current[index]->getNext()->getNext()==NULL) {
    // third value
    current[index]->getNext()->setNext(node);
    current[index]->getNext()->getNext()->setNext(NULL);
    //cout << "third val" << endl;
  }
  else {
    cout << "time to rehash" << endl;
    // is full, time to rehash!
    //if (size<11) {
       size = size*2;
       Node** newccurrent = REHASH(size, current, node);
       delete current;
       current = newccurrent;
       //}
  }
 
}
void PRINT(int &size, Node** &current) {
  // iterate through every value (like in rehash funct) and print it out! don't forget linked lists
  cout << "size is: " << size << endl;
  for (int a=0; a<size; a++) {
    if (current[a]!=NULL) {
      Node* c = current[a];
      cout << c->getStudent()->getFName() << " " << c->getStudent()->getLName() << " ID:" << c->getStudent()->getID() << endl;
      if (c->getNext()!=NULL) {
        c = c->getNext();
	//   cout << c->getStudent()->getID() << endl;
	  cout << c->getStudent()->getFName() << " " << c->getStudent()->getLName()\
 << " ID:" << c->getStudent()->getID() << endl;

        if (c->getNext()!=NULL) {
	  c = c->getNext();
	  //cout << c->getStudent()->getID() << endl;
	    cout << c->getStudent()->getFName() << " " << c->getStudent()->getLName()\
 << " ID:" << c->getStudent()->getID() << endl;

        }
      }
    }
  }
}
void DELETE(int &size, int ID, Node** &current) {
  //basically use the hash functoin and reverse it based on student's ID and then delete the student. (will have to figure out what to do if the student was in a linked list!)
  //int ID = node->getStudent()->getID();
  int index = ID % size;
  if (current[index]->getStudent()->getID()==ID) {
    Node* c = current[index];
    Node* n = current[index]->getNext();
    c->~Node();
    //delete c;
    current[index] = n;
  }
  else if (current[index]->getNext()->getStudent()->getID()==ID) {
    Node* p = current[index];
    Node* c = current[index]->getNext();
    Node* n = current[index]->getNext()->getNext();
    current[index]->setNext(n);
    c->~Node();
    //delete c;
  }
  else if (current[index]->getNext()->getNext()->getStudent()->getID()==ID) {
    Node* p = current[index]->getNext();
    Node* c = p->getNext();
    p->setNext(NULL);
    c->~Node();
    //delete c;
   
  }
  else {
    cout << "Sorry, ID doesn't match up with anyone in storage" << endl;
  }
}
Node** REHASH (int &size,  Node** &current, Node* node) {
  // basically for every single value (idk how to iterate thru every value but) for loop thru every value in a COPY of current and call the ADD funct for every single student again, except size = size*2 
  cout << "reached rehashing function" << endl;
  cout << "size is: " << size;
  cout << "the node that started this is: " << node->getStudent()->getID() << endl;
  Node** newcurrent = new Node*[size];
  for (int a=0; a<size; a++) {
    newcurrent[a] = NULL;
  }

  int counter = 0;
  int idplusone = node->getStudent()->getID();
  cout << "size/2: " << size/2 << "--------------------------------------------------------------------" << endl;
  for (int z=0; z<(size/2); z++) {
    if (current[z]!=NULL) {

      Node* cNode = current[z];
      if (cNode->getNext()!=NULL) {
	if (cNode->getNext()->getNext()!=NULL) {
	  ADD(size, cNode->getNext()->getNext(), newcurrent);
	}
	ADD(size, cNode->getNext(), newcurrent);
      }
      ADD(size, cNode, newcurrent);
      
    }
    
  }
  ADD(size, node, newcurrent);
  //delete current;
  //Node** current = newcurrent;
  return newcurrent;
}
