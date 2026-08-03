#include "PatientStack.h"
#include <iostream>
#include <cstring>

using namespace std;

//========================================
// Constructor
//========================================

PatientStack::PatientStack()
{
    top = NULL;
}

//========================================
// Destructor
//========================================

PatientStack::~PatientStack()
{
    clear();
}

//========================================
// Kiểm tra rỗng
//========================================

bool PatientStack::isEmpty()
{
    return top == NULL;
}

//========================================
// Push
//========================================

void PatientStack::push(Patient patient)
{
    StackNode *p = new StackNode;

    p->data = patient;

    p->next = top;

    top = p;
}

//========================================
// Pop
//========================================

bool PatientStack::pop(Patient &patient)
{
    if(top == NULL)
    {
        return false;
    }

    StackNode *temp = top;

    patient = temp->data;

    top = top->next;

    delete temp;

    return true;
}

//========================================
// Peek
//========================================

Patient* PatientStack::peek()
{
    if(top == NULL)
    {
        return NULL;
    }

    return &(top->data);
}

Patient* PatientStack::searchByID(const char id[])
{
    StackNode *current = top;
    while(current != NULL)
    {
        if(strcmp(current->data.getPatientID(), id) == 0)
        {
            return &(current->data);
        }
        current = current->next;
    }
    return NULL;
}

bool PatientStack::removeByID(const char id[], Patient &patient)
{
    StackNode *current = top;
    StackNode *previous = NULL;

    while(current != NULL)
    {
        if(strcmp(current->data.getPatientID(), id) == 0)
        {
            patient = current->data;
            if(previous == NULL)
            {
                top = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

//========================================
// Display
//========================================

void PatientStack::display()
{
    if(top == NULL)
    {
        cout<<"Thung rac rong!\n";
        return;
    }

    StackNode *current = top;

    cout<<"\n===== THUNG RAC =====\n\n";

    while(current != NULL)
    {
        current->data.output();

        cout<<"-------------------------\n";

        current = current->next;
    }
}

//========================================
// Count
//========================================

int PatientStack::count()
{
    int dem = 0;

    StackNode *current = top;

    while(current != NULL)
    {
        dem++;

        current = current->next;
    }

    return dem;
}

//========================================
// Clear
//========================================

void PatientStack::clear()
{
    while(top != NULL)
    {
        StackNode *temp = top;

        top = top->next;

        delete temp;
    }
}
