#include "Student.h"
#include <iostream>
#include <cstring>
using namespace std;

Student::Student() {
  //cout << "creating student" << endl;
}

int Student::getID() {
  //cout << "returning ID" << endl;
  return id;
}

void Student::setID(int iid) {
  id = iid;
}

void Student::setFName(char* firstName) {
  strcpy(fName, firstName);
}
char* Student::getFName() {
  return fName;
}
void Student::setLName(char* lastName) {
  strcpy(lName, lastName);
}
char* Student::getLName() {
  return lName;
}
void Student::setGPA(float GPA) {
  gpa = GPA;
}
float Student::getGPA() {
  return gpa;
}
