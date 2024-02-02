#include "node.h"
#include <iostream>
#include <cstring>
using namespace std;
Node::Node(Student* s) : student(s), next(0) {}
  //creating node, takes in a student pointer
Node::~Node() {
    // Assuming proper memory management for Student objects is handled elsewhere
  delete student;
}

void Node::setStudent(Student* s) {
    //not needed
    student = s;
}

void Node::setNext(Node* n) {
    next = n;
}

Student* Node::getStudent() {
    return student;
}

Node* Node::getNext() {
    return next;
}

