#ifndef PATIENTLINKEDLIST_H
#define PATIENTLINKEDLIST_H

#include "../models/Patient.h"
#include <vector>

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

    PatientNode* searchByID(const char id[]);

    PatientNode* searchByCCCD(const char cccd[]);

    PatientNode* searchByName(const char name[]);

    std::vector<PatientNode*> searchAllByName(const char name[]);

    bool deletePatient(const char id[]);

    void clear();
};

#endif
