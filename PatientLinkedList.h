#ifndef PATIENTLINKEDLIST_H
#define PATIENTLINKEDLIST_H

#include "../models/Patient.h"

struct PatientNode
{
    Patient data;
    PatientNode *next;
};

class PatientLinkedList
{
private:

    PatientNode *head;
    PatientNode *tail;

public:

    // Constructor
    PatientLinkedList();

    // Destructor
    ~PatientLinkedList();

    //--------------------------
    // Các thao tác cơ bản
    //--------------------------

    bool isEmpty();

    void addLast(Patient patient);

    void addFirst(Patient patient);

    void display();

    int count();

    PatientNode* searchByID(char id[]);

    PatientNode* searchByCCCD(char cccd[]);

    PatientNode* searchByName(char name[]);

    bool deletePatient(char id[]);

    void clear();
};

#endif