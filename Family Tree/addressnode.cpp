#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>
#include "addressnode.h"

using namespace std;

static std::queue<int> availableIDs;

/////////////////// AddressNode /////////////////////////////////

void AddressNode::AddChild(AddressNode& child)
{
    vector<AddressNode*>::iterator iter;
    if((iter = find(children_.begin(), children_.end(), &child)) != children_.end())
        return;

    children_.push_back(&child);

    if (spouse_)
        spouse_->AddChild(child);
}

void AddressNode::PrintBasic()
{
    cout << firstName_ << " " << lastName_ << " ID" << setfill('0') << setw(3) << id_ << endl;
}

void AddressNode::PrintFormal()
{
    cout << lastName_ << " " << firstName_ << " ID" << setfill ('0') << setw(3) << id_ << endl;
}

void AddressNode::PrintFull()
{
    cout << setfill(' ') << endl;
    cout << setw(15) << "UID " << "ID" << setfill('0') << setw(3) << id_ <<  setfill(' ')<< endl;
    cout << setw(15) << "NAME:" << firstName_ << " " << lastName_ << endl;
    cout << setw(15) << "Address1:" << address_ << endl;
    cout << setw(15) << "City:" << city_<< " "  << endl;
    cout << setw(15) << "State:" << state_<< " "  << endl;
    cout << setw(15) << "Zip:" << zip_<< " "  << endl;
    cout << setw(15) << "Date_Birth:" << dob_<< " "  << endl;
    cout << setw(15) << "Date_Death:" << dod_<< " "  << endl;
    cout << setw(15) << "Date_Wedding:" << dow_<< " "  << endl;
    cout << setw(15) << "Spouse:" << (spouse_ ? spouse_->GetFirstName() : "") << " " << (spouse_ ? spouse_-> GetLastName() : "") << endl;


    for(unsigned int i = 0; i < children_.size(); i++)
    {
        cout << setw(15) << "Child: " << i << ": " << children_[i]->GetFirstName()<< " " << children_[i]->GetLastName()<<  endl;
    }
}

/////////////////// AddressFactory /////////////////////////////////

AddressNode AddressNodeFactory::Make(const string& firstName, const string& lastName)
{
    static int nextID = 1;

    int newID = 0;
    if (availableIDs.empty())
    {
        newID = nextID++;
    }
    else
    {
        newID = availableIDs.front();
        availableIDs.pop();
    }
    return AddressNode(firstName, lastName, newID);
}

void AddressNodeFactory::Recycle(const AddressNode& ex)
{
    availableIDs.push(ex.GetID());
}
