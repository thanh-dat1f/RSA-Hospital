#include "PatientLinkedList.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

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

PatientNode* PatientLinkedList::searchByID(const char id[])
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

PatientNode* PatientLinkedList::searchByCCCD(const char cccd[])
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

static void replaceAll(string &value, const string &from, const string &to)
{
    size_t position = 0;
    while((position = value.find(from, position)) != string::npos)
    {
        value.replace(position, from.size(), to);
        position += to.size();
    }
}

static string normalizeName(const char value[])
{
    string result = value == NULL ? "" : value;
    for(size_t i = 0; i < result.size(); ++i)
    {
        const unsigned char c = static_cast<unsigned char>(result[i]);
        if(c >= 'A' && c <= 'Z')
        {
            result[i] = static_cast<char>(c - 'A' + 'a');
        }
    }

    static const char *vietnameseCasePairs[][2] =
    {
        {"À", "à"}, {"Á", "á"}, {"Ả", "ả"}, {"Ã", "ã"}, {"Ạ", "ạ"},
        {"Ă", "ă"}, {"Ằ", "ằ"}, {"Ắ", "ắ"}, {"Ẳ", "ẳ"}, {"Ẵ", "ẵ"}, {"Ặ", "ặ"},
        {"Â", "â"}, {"Ầ", "ầ"}, {"Ấ", "ấ"}, {"Ẩ", "ẩ"}, {"Ẫ", "ẫ"}, {"Ậ", "ậ"},
        {"Đ", "đ"},
        {"È", "è"}, {"É", "é"}, {"Ẻ", "ẻ"}, {"Ẽ", "ẽ"}, {"Ẹ", "ẹ"},
        {"Ê", "ê"}, {"Ề", "ề"}, {"Ế", "ế"}, {"Ể", "ể"}, {"Ễ", "ễ"}, {"Ệ", "ệ"},
        {"Ì", "ì"}, {"Í", "í"}, {"Ỉ", "ỉ"}, {"Ĩ", "ĩ"}, {"Ị", "ị"},
        {"Ò", "ò"}, {"Ó", "ó"}, {"Ỏ", "ỏ"}, {"Õ", "õ"}, {"Ọ", "ọ"},
        {"Ô", "ô"}, {"Ồ", "ồ"}, {"Ố", "ố"}, {"Ổ", "ổ"}, {"Ỗ", "ỗ"}, {"Ộ", "ộ"},
        {"Ơ", "ơ"}, {"Ờ", "ờ"}, {"Ớ", "ớ"}, {"Ở", "ở"}, {"Ỡ", "ỡ"}, {"Ợ", "ợ"},
        {"Ù", "ù"}, {"Ú", "ú"}, {"Ủ", "ủ"}, {"Ũ", "ũ"}, {"Ụ", "ụ"},
        {"Ư", "ư"}, {"Ừ", "ừ"}, {"Ứ", "ứ"}, {"Ử", "ử"}, {"Ữ", "ữ"}, {"Ự", "ự"},
        {"Ỳ", "ỳ"}, {"Ý", "ý"}, {"Ỷ", "ỷ"}, {"Ỹ", "ỹ"}, {"Ỵ", "ỵ"}
    };

    for(const auto &pair : vietnameseCasePairs)
    {
        replaceAll(result, pair[0], pair[1]);
    }

    return result;
}

vector<PatientNode*> PatientLinkedList::searchAllByName(const char name[])
{
    vector<PatientNode*> exactMatches;
    vector<PatientNode*> partialMatches;

    if(name == NULL || strlen(name) == 0)
    {
        return exactMatches;
    }

    const string keyword = normalizeName(name);
    PatientNode *current = head;

    while(current != NULL)
    {
        const string fullName = normalizeName(current->data.getFullName());
        if(fullName == keyword)
        {
            exactMatches.push_back(current);
        }
        else if(fullName.find(keyword) != string::npos)
        {
            partialMatches.push_back(current);
        }

        current = current->next;
    }

    return exactMatches.empty() ? partialMatches : exactMatches;
}

PatientNode* PatientLinkedList::searchByName(const char name[])
{
    vector<PatientNode*> matches = searchAllByName(name);
    return matches.empty() ? NULL : matches.front();
}

//========================================
// Xóa bệnh nhân theo mã
//========================================

bool PatientLinkedList::deletePatient(const char id[])
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
