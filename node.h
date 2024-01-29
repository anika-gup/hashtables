#ifndef NODE_H
#define NODE_H

#include "student.h"
#include <iostream>
using namespace std;
class Node {
public:
    Node(Student* s);
    ~Node();

    void setStudent(Student* s);
    void setNext(Node* n);

    Student* getStudent();
    Node* getNext();

private:
    Student* student;
    Node* next;
};

#endif // NODE_H

