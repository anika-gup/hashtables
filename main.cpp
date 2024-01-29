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
void DELETE(int &size, Node* &node, Node** &current);
void REHASH(int &size, Node** &current, Node* node);

/*
To do list
 - add funct:
  - print
   - delete
    - quit
    ??? create the array//hash table that will store everything
int size var represents size of has table

first figure out how to have a file with list of names/create the random students

then make the hash formula put it in
--if place is already taken, put it in a linked list (does linked list need to be sorted by order again? (maybe extra funct for putting in linked list)
if linked list is full, have ANOTHER funct that makes the array doubled in size and reput everything in!
 */



int main() {
  //creating example node:
  Student* exStudent = new Student();
  exStudent->setID(123);
  Node* exNode = new Node(exStudent);
  cout << exNode->getStudent()->getID() << endl;
  cout << "RUNNING" << endl;
  int quit = 0;
  int size = 100;
  int numberOfStudents = 0;
  Node** current = new Node*[size];
  
  
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
      // NOW--GENERATE RANDOM GPA AND SET ALL VALUES TO A NODE OR STUDENT AND SEND TO ADD FUNCTION OR REHASH FUNCTION OR WHATEVER 
     if (numberOfStudents!=0) {// finding the right index...
	for (int b=0; b<numberOfStudents; b++) {
	  fin  >> firstname;
	  lin >> lastname;
	}
      }

      srand(time(0));
      for (int a = 1; a<inputNumOfStudents+1 ; a++) {
	Student* s = new Student();
	int ID = numberOfStudents + a;
	fin >> firstname;
	lin >> lastname;
	float GPA = static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(4.0-0.1));
	cout << "name: " << firstname << " " << lastname;
	cout << "  ID: " << ID << " GPA: " << GPA << endl;
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
    }
    else if (strcmp(input, "DELETE")==0) {
      // delete funct
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
  int index = ID % size;
  cout << "index: " << index << endl;
  if (current[index]==NULL) {
    // first value 
    current[index] = node;
  }
  else if (current[index]->getNext()==NULL) {
      // second value
    current[index]->setNext(node);
  }
  else if (current[index]->getNext()->getNext()==NULL) {
    // third value
    current[index]->getNext()->setNext(node);
  }
  else {
    // is full, time to rehash!
    size = size*2;
    REHASH(size, current, node);
  }
  current[index] = node;
 
}
void PRINT(int &size, Node** &current) {
  // iterate through every value (like in rehash funct) and print it out! don't forget linked lists
}
void DELETE(int &size, Node* &node, Node** &current) {
  //basically use the hash functoin and reverse it based on student's ID and then delete the student. (will have to figure out what to do if the student was in a linked list!)
}
void REHASH (int &size,  Node** &current, Node* node) {
  // basically for every single value (idk how to iterate thru every value but) for loop thru every value in a COPY of current and call the ADD funct for every single student again, except size = size*2 
  cout << "reached rehashing function" << endl;
  size  = size*2;
  Node** newcurrent = new Node*[size];
  for (int it=0; it<(size/2); it++) {
    if (current[it]!=NULL) {
      ADD(size, current[it], newcurrent);
      while (current[it]->getNext()!=NULL) {

      }
    }
  }
}
