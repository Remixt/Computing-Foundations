#ifndef ADDRESSNODE_H
#define ADDRESSNODE_H

#include <list>
#include <vector>
#include <algorithm>
#include <string>

class AddressNode;
typedef std::list<AddressNode> NodeList;

inline bool operator<(const AddressNode& lhs, const AddressNode& rhs);

class AddressNode
{
    friend bool operator<(const AddressNode& lhs, const AddressNode& rhs);
public:
    AddressNode(const std::string& firstName, const std::string& lastName, int id)
        : firstName_(firstName), lastName_(lastName), spouse_(NULL), id_(id)
    {}

    const std::string& GetFirstName() const { return firstName_; }
    const std::string& GetLastName() const { return lastName_; }
    const std::string& GetCity() const { return city_; }
    const std::string& GetState() const { return state_; }
    const std::string& GetZip() const{ return zip_; }
    const std::string& GetDateOfBirth() const { return dob_; }
    const std::string& GetDateOfWedding() const { return dow_; }
    const std::string& GetDateOfDeath() const { return dod_; }
    unsigned int GetID() const { return id_; }

    void SetCity(const std::string& city) { city_ = city; }
    void SetState(const std::string& state) { state_ = state; }
    void SetZip(const std::string& zip) { zip_ = zip; }
    void SetDateOfBirth(const std::string& dob) { dob_ = dob; }
    void SetDateOfWedding(const std::string& dow) { dow_ = dow; }
    void SetDateOfDeath(const std::string& dod) { dod_ = dod; }
    void SetAddress(const std::string& address) { address_ = address; }
    void SetSpouse(AddressNode& spouse) { spouse_ = &spouse; }

    void AddChild(AddressNode& child);

    void PrintBasic();
    void PrintFormal();
    void PrintFull();

private:
    std::string firstName_;
    std::string lastName_;
    std::string city_;
    std::string state_;
    std::string zip_;
    std::string dob_;
    std::string dow_;
    std::string dod_;
    std::string address_;
    std::vector<AddressNode*> children_;
    AddressNode* spouse_;
    unsigned int id_;
};

inline bool operator<(const AddressNode& lhs, const AddressNode& rhs)
{
    std::string lhsLastName(lhs.lastName_);
    std::string lhsFirstName(lhs.firstName_);
    std::transform(lhsLastName.begin(), lhsLastName.end(), lhsLastName.begin(), ::tolower);
    std::transform(lhsFirstName.begin(), lhsFirstName.end(), lhsFirstName.begin(), ::tolower);


    std::string rhsLastName(rhs.lastName_);
    std::string rhsFirstName(rhs.firstName_);
    std::transform(rhsLastName.begin(), rhsLastName.end(), rhsLastName.begin(), ::tolower);
    std::transform(rhsFirstName.begin(), rhsFirstName.end(), rhsFirstName.begin(), ::tolower);

    if (lhsLastName > rhsLastName)
        return false;
    if (lhsLastName < rhsLastName)
        return true;
    if (lhsFirstName > rhsFirstName)
        return false;

    return true;
}

class AddressNodeFactory
{
public:
    static AddressNode Make(const std::string& firstName, const std::string& lastName);
    static void Recycle(const AddressNode& node);
};

#endif // ADDRESSNODE_H
