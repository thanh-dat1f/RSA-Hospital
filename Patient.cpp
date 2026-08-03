#include "Patient.h"
#include "Examination.h"
#include "../utils/InputUtils.h"

using namespace std;

//==============================
// Constructor
//==============================
Patient::Patient()
{
    patientID[0] = '\0';
    fullName[0] = '\0';
    dateOfBirth[0] = '\0';
    gender = true;
    citizenID[0] = '\0';
    phone[0] = '\0';
    email[0] = '\0';
    address[0] = '\0';
    insuranceID[0] = '\0';

    history = NULL;

    // Thêm dòng này
    missedCall = 0;
}

Patient::Patient(const Patient &other)
{
    InputUtils::copyToBuffer(patientID, other.patientID);
    InputUtils::copyToBuffer(fullName, other.fullName);
    InputUtils::copyToBuffer(dateOfBirth, other.dateOfBirth);
    gender = other.gender;
    InputUtils::copyToBuffer(citizenID, other.citizenID);
    InputUtils::copyToBuffer(phone, other.phone);
    InputUtils::copyToBuffer(email, other.email);
    InputUtils::copyToBuffer(address, other.address);
    InputUtils::copyToBuffer(insuranceID, other.insuranceID);
    history = other.history == NULL ? NULL : new Examination(*other.history);
    missedCall = other.missedCall;
}

Patient& Patient::operator=(const Patient &other)
{
    if(this == &other)
    {
        return *this;
    }

    Examination *newHistory = other.history == NULL
        ? NULL : new Examination(*other.history);
    delete history;

    InputUtils::copyToBuffer(patientID, other.patientID);
    InputUtils::copyToBuffer(fullName, other.fullName);
    InputUtils::copyToBuffer(dateOfBirth, other.dateOfBirth);
    gender = other.gender;
    InputUtils::copyToBuffer(citizenID, other.citizenID);
    InputUtils::copyToBuffer(phone, other.phone);
    InputUtils::copyToBuffer(email, other.email);
    InputUtils::copyToBuffer(address, other.address);
    InputUtils::copyToBuffer(insuranceID, other.insuranceID);
    history = newHistory;
    missedCall = other.missedCall;

    return *this;
}

Patient::Patient(Patient &&other) noexcept
{
    InputUtils::copyToBuffer(patientID, other.patientID);
    InputUtils::copyToBuffer(fullName, other.fullName);
    InputUtils::copyToBuffer(dateOfBirth, other.dateOfBirth);
    gender = other.gender;
    InputUtils::copyToBuffer(citizenID, other.citizenID);
    InputUtils::copyToBuffer(phone, other.phone);
    InputUtils::copyToBuffer(email, other.email);
    InputUtils::copyToBuffer(address, other.address);
    InputUtils::copyToBuffer(insuranceID, other.insuranceID);
    history = other.history;
    missedCall = other.missedCall;
    other.history = NULL;
}

Patient& Patient::operator=(Patient &&other) noexcept
{
    if(this == &other)
    {
        return *this;
    }

    delete history;
    InputUtils::copyToBuffer(patientID, other.patientID);
    InputUtils::copyToBuffer(fullName, other.fullName);
    InputUtils::copyToBuffer(dateOfBirth, other.dateOfBirth);
    gender = other.gender;
    InputUtils::copyToBuffer(citizenID, other.citizenID);
    InputUtils::copyToBuffer(phone, other.phone);
    InputUtils::copyToBuffer(email, other.email);
    InputUtils::copyToBuffer(address, other.address);
    InputUtils::copyToBuffer(insuranceID, other.insuranceID);
    history = other.history;
    missedCall = other.missedCall;
    other.history = NULL;

    return *this;
}

//==============================
// Destructor
//==============================

Patient::~Patient()
{
    delete history;
    history = NULL;
}

//==============================
// Setter
//==============================

void Patient::setPatientID(const char id[])
{
    InputUtils::copyToBuffer(patientID, id);
}

void Patient::setFullName(const char name[])
{
    InputUtils::copyToBuffer(fullName, name);
}

void Patient::setDateOfBirth(const char dob[])
{
    InputUtils::copyToBuffer(dateOfBirth, dob);
}

void Patient::setGender(bool g)
{
    gender = g;
}

void Patient::setCitizenID(const char cccd[])
{
    InputUtils::copyToBuffer(citizenID, cccd);
}

void Patient::setPhone(const char phoneNumber[])
{
    InputUtils::copyToBuffer(phone, phoneNumber);
}

void Patient::setEmail(const char mail[])
{
    InputUtils::copyToBuffer(email, mail);
}

void Patient::setAddress(const char addr[])
{
    InputUtils::copyToBuffer(address, addr);
}

void Patient::setInsuranceID(const char insurance[])
{
    InputUtils::copyToBuffer(insuranceID, insurance);
}

void Patient::setHistory(Examination* exam)
{
    if(history == exam)
    {
        return;
    }

    delete history;
    history = exam;
}
//==============================
// Lưu kết quả khám
//==============================

void Patient::setExamination(Examination *exam)
{
    if(exam == NULL)
    {
        return;
    }

    Examination *tail = exam;
    while(tail->next != NULL)
    {
        tail = tail->next;
    }

    tail->next = history;
    history = exam;
}

//==============================
// Getter
//==============================

char* Patient::getPatientID()
{
    return patientID;
}

char* Patient::getFullName()
{
    return fullName;
}

char* Patient::getDateOfBirth()
{
    return dateOfBirth;
}

bool Patient::getGender()
{
    return gender;
}

char* Patient::getCitizenID()
{
    return citizenID;
}

char* Patient::getPhone()
{
    return phone;
}

char* Patient::getEmail()
{
    return email;
}

char* Patient::getAddress()
{
    return address;
}

char* Patient::getInsuranceID()
{
    return insuranceID;
}

Examination* Patient::getHistory()
{
    return history;
}
//==============================
// Lấy kết quả khám
//==============================

Examination* Patient::getExamination()
{
    return history;
}
//==============================
// Quản lý số lần vắng
//==============================

void Patient::increaseMissedCall()
{
    missedCall++;
}

void Patient::resetMissedCall()
{
    missedCall = 0;
}

int Patient::getMissedCall()
{
    return missedCall;
}

//==============================
// Nhập thông tin bệnh nhân
//==============================

void Patient::input()
{
    cout << "\n===== NHAP THONG TIN BENH NHAN =====\n";

    const string name = InputUtils::readLine("Ho va ten: ", 49);
    const string dob = InputUtils::readDate("Ngay sinh (dd/mm/yyyy): ", false);
    const int selectedGender = InputUtils::readInt("Gioi tinh (1-Nam, 0-Nu): ", 0, 1);

    string cccd;
    do
    {
        cccd = InputUtils::readLine("CCCD (12 chu so): ", 12);
        if(cccd.size() != 12 || !InputUtils::isDigits(cccd))
        {
            cout << "CCCD phai gom dung 12 chu so!\n";
        }
    }while(cccd.size() != 12 || !InputUtils::isDigits(cccd));

    string phoneNumber;
    do
    {
        phoneNumber = InputUtils::readLine("So dien thoai (10 chu so): ", 10);
        if(phoneNumber.size() != 10 || phoneNumber[0] != '0'
           || !InputUtils::isDigits(phoneNumber))
        {
            cout << "So dien thoai phai gom 10 chu so va bat dau bang 0!\n";
        }
    }while(phoneNumber.size() != 10 || phoneNumber[0] != '0'
           || !InputUtils::isDigits(phoneNumber));

    string mail;
    do
    {
        mail = InputUtils::readLine("Email: ", 49);
        if(!InputUtils::isValidEmail(mail))
        {
            cout << "Email khong hop le!\n";
        }
    }while(!InputUtils::isValidEmail(mail));

    const string patientAddress = InputUtils::readLine("Dia chi: ", 99);

    string insurance;
    do
    {
        insurance = InputUtils::readLine(
            "Ma BHYT (bo trong neu khong co): ", 19, true);
        if(!insurance.empty() && !InputUtils::isAlphaNumeric(insurance))
        {
            cout << "Ma BHYT chi duoc gom chu cai va chu so!\n";
        }
    }while(!insurance.empty() && !InputUtils::isAlphaNumeric(insurance));

    setFullName(name.c_str());
    setDateOfBirth(dob.c_str());
    setGender(selectedGender == 1);
    setCitizenID(cccd.c_str());
    setPhone(phoneNumber.c_str());
    setEmail(mail.c_str());
    setAddress(patientAddress.c_str());
    setInsuranceID(insurance.c_str());
}

//==============================
// Hiển thị
//==============================

void Patient::output()
{
    cout << "\n==============================\n";

    cout << "Ma benh nhan : " << patientID << endl;
    cout << "Ho ten       : " << fullName << endl;
    cout << "Ngay sinh    : " << dateOfBirth << endl;

    cout << "Gioi tinh    : ";

    if(gender)
        cout << "Nam" << endl;
    else
        cout << "Nu" << endl;

    cout << "CCCD         : " << citizenID << endl;
    cout << "So dien thoai: " << phone << endl;
    cout << "Email        : " << email << endl;
    cout << "Dia chi      : " << address << endl;
    cout << "BHYT         : " << insuranceID << endl;

    cout << "==============================\n";
}
