#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student {
 public:
  Student();
  void setID(int iid);
  int getID();
  void setFName(char* firstName);
  char* getFName();
  void setLName(char* lastName);
  char* getLName();
  void setGPA(float GPA);
  float getGPA();
 protected:
  int id;
  char fName[15];
  char lName[15];
  float gpa;
  
} ;
#endif
