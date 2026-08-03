#include "PatientLinkedList.h"
#include <iostream>
#include <cstring>

using namespace std;

//========================================
// Constructor
//========================================

PatientLinkedList::PatientLinkedList()
{
    head = NULL;
    tail = NULL;
}

//========================================
// Destructor
//========================================

PatientLinkedList::~PatientLinkedList()
{
    clear();
}

//========================================
// Kiểm tra danh sách rỗng
//========================================

bool PatientLinkedList::isEmpty()
{
    return (head == NULL);
}

//========================================
// Thêm bệnh nhân vào đầu danh sách
//========================================

void PatientLinkedList::addFirst(Patient patient)
{
    PatientNode *p = new PatientNode;

    p->data = patient;
    p->next = head;

    head = p;

    if(tail == NULL)
    {
        tail = p;
    }
}

//========================================
// Thêm bệnh nhân vào cuối danh sách
//========================================

void PatientLinkedList::addLast(Patient patient)
{
    PatientNode *p = new PatientNode;

    p->data = patient;
    p->next = NULL;

    if(head == NULL)
    {
        head = p;
        tail = p;
    }
    else
    {
        tail->next = p;
        tail = p;
    }
}

//========================================
// Hiển thị danh sách bệnh nhân
//========================================

void PatientLinkedList::display()
{
    if(head == NULL)
    {
        cout << "\nDanh sach benh nhan rong!\n";
        return;
    }

    PatientNode *current = head;

    while(current != NULL)
    {
        current->data.output();

        cout << endl;

        current = current->next;
    }
}

//========================================
// Đếm số lượng bệnh nhân
//========================================

int PatientLinkedList::count()
{
    int dem = 0;

    PatientNode *current = head;

    while(current != NULL)
    {
        dem++;

        current = current->next;
    }

    return dem;
}

//========================================
// Tìm theo mã bệnh nhân
//========================================

PatientNode* PatientLinkedList::searchByID(char id[])
{
    PatientNode *current = head;

    while(current != NULL)
    {
        if(strcmp(current->data.getPatientID(), id) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

//========================================
// Tìm theo CCCD
//========================================

PatientNode* PatientLinkedList::searchByCCCD(char cccd[])
{
    PatientNode *current = head;

    while(current != NULL)
    {
        if(strcmp(current->data.getCitizenID(), cccd) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

//========================================
// Tìm theo họ tên
//========================================

PatientNode* PatientLinkedList::searchByName(char name[])
{
    PatientNode *current = head;

    while(current != NULL)
    {
        if(strcmp(current->data.getFullName(), name) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

//========================================
// Xóa bệnh nhân theo mã
//========================================

bool PatientLinkedList::deletePatient(char id[])
{
    if(head == NULL)
    {
        return false;
    }

    PatientNode *current = head;
    PatientNode *previous = NULL;

    while(current != NULL)
    {
        if(strcmp(current->data.getPatientID(), id) == 0)
        {
            // Xóa node đầu
            if(previous == NULL)
            {
                head = current->next;

                if(current == tail)
                {
                    tail = NULL;
                }
            }
            else
            {
                previous->next = current->next;

                if(current == tail)
                {
                    tail = previous;
                }
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
// Xóa toàn bộ danh sách
//========================================

void PatientLinkedList::clear()
{
    PatientNode *current = head;

    while(current != NULL)
    {
        PatientNode *temp = current;

        current = current->next;

        delete temp;
    }

    head = NULL;
    tail = NULL;
}