#include "Prescription.h"
#include "../utils/InputUtils.h"
#include <utility>

using namespace std;

//======================================
// Constructor
//======================================

Prescription::Prescription()
{
    medicineName[0] = '\0';
    quantity = 0;
    dosage[0] = '\0';
    instruction[0] = '\0';

    next = NULL;
}

Prescription::Prescription(const Prescription &other)
{
    InputUtils::copyToBuffer(medicineName, other.medicineName);
    quantity = other.quantity;
    InputUtils::copyToBuffer(dosage, other.dosage);
    InputUtils::copyToBuffer(instruction, other.instruction);
    next = other.next == NULL ? NULL : new Prescription(*other.next);
}

Prescription& Prescription::operator=(const Prescription &other)
{
    if(this == &other)
    {
        return *this;
    }

    Prescription *newNext = other.next == NULL ? NULL : new Prescription(*other.next);
    delete next;

    InputUtils::copyToBuffer(medicineName, other.medicineName);
    quantity = other.quantity;
    InputUtils::copyToBuffer(dosage, other.dosage);
    InputUtils::copyToBuffer(instruction, other.instruction);
    next = newNext;

    return *this;
}

Prescription::Prescription(Prescription &&other) noexcept
{
    InputUtils::copyToBuffer(medicineName, other.medicineName);
    quantity = other.quantity;
    InputUtils::copyToBuffer(dosage, other.dosage);
    InputUtils::copyToBuffer(instruction, other.instruction);
    next = other.next;
    other.next = NULL;
}

Prescription& Prescription::operator=(Prescription &&other) noexcept
{
    if(this == &other)
    {
        return *this;
    }

    delete next;
    InputUtils::copyToBuffer(medicineName, other.medicineName);
    quantity = other.quantity;
    InputUtils::copyToBuffer(dosage, other.dosage);
    InputUtils::copyToBuffer(instruction, other.instruction);
    next = other.next;
    other.next = NULL;

    return *this;
}

//======================================
// Destructor
//======================================

Prescription::~Prescription()
{
    delete next;
    next = NULL;
}

//======================================
// Setter
//======================================

void Prescription::setMedicineName(const char name[])
{
    InputUtils::copyToBuffer(medicineName, name);
}

void Prescription::setQuantity(int q)
{
    quantity = q;
}

void Prescription::setDosage(const char dose[])
{
    InputUtils::copyToBuffer(dosage, dose);
}

void Prescription::setInstruction(const char text[])
{
    InputUtils::copyToBuffer(instruction, text);
}

//======================================
// Getter
//======================================

char* Prescription::getMedicineName()
{
    return medicineName;
}

int Prescription::getQuantity()
{
    return quantity;
}

char* Prescription::getDosage()
{
    return dosage;
}

char* Prescription::getInstruction()
{
    return instruction;
}

//======================================
// Nhập thuốc
//======================================

void Prescription::input()
{
    cout << "\n=============================\n";
    cout << "NHAP THONG TIN THUOC\n";
    cout << "=============================\n";

    const string name = InputUtils::readLine("Ten thuoc: ", 49);
    const int amount = InputUtils::readInt("So luong: ", 1, 1000000);
    const string dose = InputUtils::readLine("Lieu dung: ", 49);
    const string usage = InputUtils::readLine("Huong dan su dung: ", 99);

    setMedicineName(name.c_str());
    setQuantity(amount);
    setDosage(dose.c_str());
    setInstruction(usage.c_str());
}

//======================================
// Hiển thị thuốc
//======================================

void Prescription::output() const
{
    cout << "Ten thuoc      : " << medicineName << endl;
    cout << "So luong       : " << quantity << endl;
    cout << "Lieu dung      : " << dosage << endl;
    cout << "Huong dan dung : " << instruction << endl;
}
