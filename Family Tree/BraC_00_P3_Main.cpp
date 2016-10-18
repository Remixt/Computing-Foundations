#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <queue>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include "addressnode.h"

using namespace std;

class NameMatches
{
public:
    NameMatches(const string& firstName, const string& lastName)
        : firstName_(firstName), lastName_(lastName)
    {}

    bool operator()(const AddressNode& node)
    {

        return firstName_ == node.GetFirstName() && lastName_ == node.GetLastName();
    }

private:
    string firstName_;
    string lastName_;
};

class IDMatches
{
public:
    IDMatches(unsigned int id)
        : id_(id)
    {}

    bool operator()(const AddressNode& node)
    {
        return id_ == node.GetID();
    }

private:
    unsigned int id_;
};

void Tokenize(const string& str, char delim, vector<string>& result)
{
        istringstream stream(str);
        string field;
        while (getline(stream, field, delim))
                result.push_back(field);
}

bool CheckArgs(vector<string>& tokens, unsigned int numCommandTokens, unsigned int numArgs)
{
    if (tokens.size() < numArgs + numCommandTokens)
    {
        cout << "ERROR: TOO FEW ARGUMENTS TO COMMAND" << endl;
        return false;
    }
    return true;
}

bool CommandMatches(const string& command, const vector<string>& tokens)
{
    vector<string> commandTokens;
    Tokenize(command, ' ', commandTokens);

    if (tokens.size() < commandTokens.size() || commandTokens.empty())
        return false;

    vector<string>::const_iterator iter;
    unsigned int index = 0;
    for (iter = commandTokens.begin(); iter != commandTokens.end(); ++iter, ++index)
    {
        if (*iter != tokens[index])
            return false;
    }

    return true;
}

bool CheckID(const std::string& uid, unsigned int& result)
{
    if (uid.length() < 2 || uid.substr(0, 2) != "ID")
    {
        cout << "EXPECTED UID OF THE FORM: ID<uid>" << endl;
        return false;
    }

    unsigned int id = 0;
    stringstream stream(uid.substr(2));
    stream >> id;
    if (stream.fail())
    {
        cout << "EXPECTED NUMERICAL VALUE FOR UID" << endl;
        return false;
    }
    result = id;
    return true;
}

NodeList::iterator FindName(NodeList& nodeList, const string& firstName, const string& lastName)
{

    return find_if(nodeList.begin(), nodeList.end(), NameMatches(firstName,lastName));
}

NodeList::iterator FindID(NodeList& nodeList, unsigned int id)
{
    return find_if(nodeList.begin(), nodeList.end(), IDMatches(id));
}

void greet(){
    cout << "---------------------"<< endl;
    cout << "Commands Available:"<< endl;
    cout << "-------------------------------------------"<< endl;
    cout << "add <FName LName>"<< endl;
    cout << "add spouse <home_uid> <spouse_name>"<< endl;
    cout << "add child <home_uid> <child_name>"<< endl;
    cout << "add address1 <home_uid> <street_address"<< endl;
    cout << "add city <home_uid> <city>"<< endl;
    cout << "add state <home_uid> <state>"<< endl;
    cout << "add zip <home_uid> <zip>"<< endl;
    cout << "add date_birth <home_uid> <date_birth>"<< endl;
    cout << "add date_wedding <home_uid> <wedding_date> "<< endl;
    cout << "add date_death <home_uid> <death_date>"<< endl;
    cout << "add date_death <home_uid> <death_date>"<< endl;
    cout << "search <name>"<< endl;
    cout << "print <uid>"<< endl;
    cout << "print all"<< endl;
    cout << "file <File Name>"<< endl;
    cout << "commands"<< endl;
    cout << "quit"<< endl;
    cout << "-------------------------------------------"<< endl;
}

int main(void)
{
    greet();
    list<AddressNode> exampleList;

    char delim = ' ';
    istream* input = &cin;
    bool inFile = false;
    while(true)
    {
        if (!inFile)
            cout << "cmd> ";

        string line;
        getline(*input, line);
        if (input->bad())
        {
            cout << "ERROR GETTING INPUT, TRYING AGAIN..." << endl;
            input->clear();
            continue;
        }

        if (input->eof())
        {
            inFile = false;
            input = &cin;
            delim = ' ';
            continue;
        }

        if (line.size() == 0)
            continue;

        vector<string> tokens;
        Tokenize(line, delim, tokens);

        string command = tokens[0];
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "quit")
{
            cout << "Have a good day and a pleasant tomorrow! Good-bye."<< endl;
            break;
}
        if (CommandMatches("add name", tokens))
        {
            if (!CheckArgs(tokens, 2, 2))
                continue;

            NodeList::iterator iter;
            if ((iter = FindName(exampleList, tokens[2], tokens[3])) != exampleList.end())
            {
                cout << "ALREADY IN LIST: ";
                iter->PrintBasic();
                continue;
            }

            exampleList.push_back(AddressNodeFactory::Make(tokens[2], tokens[3]));

            cout << "ADDED: ";
            exampleList.back().PrintBasic();
        }
        else if (CommandMatches("add city", tokens))
        {
            if (!CheckArgs(tokens, 2, 2))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            string city = tokens[3];
            for (unsigned int i = 4; i < tokens.size(); i++)
            {
                city += " " + tokens[i];
            }

            iter->SetCity(city);
            cout << "ADDED CITY: " << tokens[3] <<" UID: " << setfill('0') << setw(3) << id << endl;
        }
        else if (CommandMatches("add state", tokens))
        {
            if (!CheckArgs(tokens, 2, 2))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            string state = tokens[3];
            for (unsigned int i = 4; i < tokens.size(); i++)
            {
                state += " " + tokens[i];
            }

            iter->SetState(state);
            cout << "ADDED STATE: " << tokens[3] <<" UID: " << setfill('0') << setw(3) << id << endl;
        }
        else if (CommandMatches("add zip", tokens))
        {
            if (!CheckArgs(tokens, 2, 2))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            iter->SetZip(tokens[3]);
            cout << "ADDED ZIP: " << tokens[3] <<" UID: " << setfill('0') << setw(3) << id << endl;
        }
        else if (CommandMatches("add date_birth", tokens))
        {
            if (!CheckArgs(tokens, 2, 2))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            iter->SetDateOfBirth(tokens[3]);
            cout << "ADDED BIRTHDAY: " << tokens[3] <<" UID: " << setfill('0') << setw(3) << id << endl;
        }
        else if (CommandMatches("add date_wedding", tokens))
        {
            if (!CheckArgs(tokens, 2, 2))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            iter->SetDateOfWedding(tokens[3]);
            cout << "Added Wedding-day: " << tokens[3] <<" UID: " << setfill('0') << setw(3) << id << endl;
        }

        else if (CommandMatches("add date_death", tokens))
        {
            if (!CheckArgs(tokens, 2, 2))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            iter->SetDateOfDeath(tokens[3]);
            cout << "ADDED DATE of DEATH: " << tokens[3] <<" UID: " << setfill('0') << setw(3) << id << endl;
        }
        else if (CommandMatches("add child", tokens))
        {
            if (!CheckArgs(tokens, 2, 3))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            if ((iter = FindName(exampleList, tokens[3], tokens[4])) == exampleList.end())
            {
                exampleList.push_back(AddressNodeFactory::Make(tokens[3], tokens[4]));
                cout << "ADDED: ";
                exampleList.back().PrintBasic();
                iter->AddChild(exampleList.back());
                continue;
            }
            cout << "ALREADY IN LIST: ";
            iter->PrintBasic();

            iter->AddChild(*iter);
        }
        else if (CommandMatches("add spouse", tokens))
        {
            if (!CheckArgs(tokens, 2, 3))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            if ((iter = FindName(exampleList, tokens[3], tokens[4])) == exampleList.end())
            {
                exampleList.push_back(AddressNodeFactory::Make(tokens[3], tokens[4]));
                cout << "ADDED SPOUSE: ";
                exampleList.back().PrintBasic();
                iter->SetSpouse(exampleList.back());
                continue;
            }

            cout << "ALREADY IN LIST: ";
            iter->PrintBasic();

            iter->SetSpouse(*iter);
        }
        else if (CommandMatches("add address1", tokens))
        {
            if (!CheckArgs(tokens, 2, 2))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[2], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "ID NOT FOUND: " << id << endl;
                continue;
            }

            iter->SetAddress(tokens[3]);
        }
        else if (CommandMatches("search", tokens))
        {
            if (!CheckArgs(tokens, 1, 2))
                continue;
            NodeList::iterator iter;

            cout << tokens[1] << " " << tokens[2] << endl;

            if ((iter = FindName(exampleList, tokens[1], tokens[2])) != exampleList.end())
            {
                cout << "FOUND: ";
                iter->PrintBasic();

            }
            else
            {
             cout << "NOT FOUND: " << tokens[1] <<  " " << tokens[2] << endl;

            }
        }
        else if (CommandMatches("commands", tokens))
        {
          #ifdef __WIN32
            system("cls");
          #else
            system("clear");
          #endif
          greet();
        }
        else if (CommandMatches("print all", tokens))
        {
            if (!CheckArgs(tokens, 2, 0))
                continue;


            if(exampleList.empty()){
                cout <<"There is nothing in the list"<< endl;
            }

            exampleList.sort();
            NodeList:: iterator iter;
            for (iter = exampleList.begin(); iter!= exampleList.end(); ++iter)
            {
                iter -> PrintFormal();
            }
        }
        else if (CommandMatches("print", tokens))
        {
            if (!CheckArgs(tokens, 0, 1))
                continue;

            unsigned int id = 0;
            if (!CheckID(tokens[1], id))
                continue;

            NodeList::iterator iter;
            if ((iter = FindID(exampleList, id)) == exampleList.end())
            {
                cout << "Id not found" <<  endl;

            }
            iter->PrintFull();

        }


        else if (CommandMatches("file", tokens))
        {
            if (!CheckArgs(tokens, 1, 1))
                continue;

            if (inFile)
            {
                cout << "ERROR: CANNOT USE FILE COMMAND IN A FILE" << endl;
                continue;
            }

            string fileName = tokens[1];
            for (unsigned int i = 2; i < tokens.size(); i++)
            {
                fileName += " " + tokens[i];
            }

            fstream* file = new fstream(fileName.c_str());
            if (!file->is_open())
            {
                cout << "ERROR: CANNOT OPEN FILE: " << fileName << endl;
                delete file;
                continue;
            }

            inFile = true;
            input = file;
            delim = ',';
        }
        else
        {
            cout << "ERROR: COMMAND NOT FOUND: " << tokens[0] << endl;
        }
    }


    return 0;
}
