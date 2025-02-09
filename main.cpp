#include <iostream>
#include <vector>
#include <string>
using namespace std;

void menu()
{
    cout << "1. Display Whole Family" << endl;
    cout << "2. Add Member to a Family" << endl;
    cout << "3. Remove Member from a Family" << endl;
    cout << "4. Update Data of a Family Member" << endl;
    cout << "5. EXIT" << endl;
}

class Date
{
public:
    int day;
    int month;
    int year;

    Date(int day, int month, int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    void displayDate()
    {
        cout << day << "-" << month << "-" << year;
    }

    int getYear() const
    {
        return year;
    }
};

class Member
{
public:
    int memberid;
    string name;
    string gender;
    Date *date_of_birth;
    static int id;
    friend class Family;
    Member(int id, string n, string g, Date *dob)
    {
        memberid = id;
        name = n;
        gender = g;
        date_of_birth = dob;
    }

    void displayMember()
    {
        cout << "Member Id: " << memberid << endl;
        cout << "        Name: " << name << endl;
        cout << "        Gender: " << gender << endl;
        cout << "        Date of Birth: ";
        if (date_of_birth != nullptr)
        {
            date_of_birth->displayDate();
        }
        else
        {
            cout << "Not available";
        }
        cout << endl;
        getAge();
    }

    void getAge()
    {
        cout << "        Age: ";
        if (date_of_birth != nullptr)
        {
            int current_age = 2024 - date_of_birth->getYear();
            cout << current_age << " ";
        }
        else
        {
            cout << "Not available";
        }
        cout << endl;
    }

private:
    static bool validateDate(int day, int month, int year)
    {
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
        {
            return false;
        }
        return true;
    }
    ~Member()
    {
        delete date_of_birth;
    }
};
int Member::id = 0;

class Family
{
    int familyID;
    vector<Member *> members;
    int no_of_members;
    static int id;

public:
    Family(int familyID, int m)
    {
        this->familyID = familyID;
        this->no_of_members = m;

        members.push_back(new Member(1, "Muhammad Qadeem", "Male", new Date(10, 1, 1975)));
        members.push_back(new Member(2, "Fozia Qadeem", "Female", new Date(31, 12, 1982)));
        members.push_back(new Member(3, "Ramsha Qadeem", "Female", new Date(31, 12, 1998)));
        members.push_back(new Member(4, "Rahat Qadeem", "Female", new Date(31, 8, 2003)));
        members.push_back(new Member(5, "Mariam Qadeem", "Female", new Date(20, 9, 2004)));
        members.push_back(new Member(6, "Umer Qadeem", "Male", new Date(24, 11, 2005)));
    }
    void displayWholeFamily()
    {
        cout << "Family ID: " << familyID << endl;
        cout << "No of Members in this family " << no_of_members << endl;
        for (Member *m : members)
        {
            m->displayMember();
        }
    }
    void addMember()
    {
        int id;
        string name;
        string gender;
        int date;
        int month;
        int year;

        cout << "Enter Name of New Member: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Gender: ";
        cin >> gender;
        do
        {
            cout << "Enter Id: ";
            cin >> id;
            cout << "Enter Date of Birth: ";
            cin >> date;
            cout << "Enter Month of Birth: ";
            cin >> month;
            cout << "Enter Year of Birth: ";
            cin >> year;

            if (id < 0 || !Member::validateDate(date, month, year))
            {
                cout << "Invalid ID or Date of Birth. Please enter valid values." << endl;
            }
        } while (id < 0 || date < 1 || date > 31 || month < 1 || month > 12 || year < 0);

        members.push_back(new Member(id, name, gender, new Date(date, month, year)));
        no_of_members++;
        cout << "Member Added Successfully" << endl;
    }
    void removeMember()
    {
        int id;
        cout << "Enter Id of the member to be removed: ";
        cin >> id;

        auto m = members.begin();
        while (m != members.end())
        {
            if ((*m)->memberid == id)
            {
                delete *m;
                m = members.erase(m);
                cout << "Member Removed Successfully" << endl;
                return;
            }
            m++;
        }
        cout << "Member not found wmh ID " << id << endl;
    }
    void updateDataOfMember()
    {
        int id;
        cout << "Enter the ID of the member whose data you want to update: ";
        cin >> id;

        for (Member *m : members)
        {
            if (m->memberid == id)
            {
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, m->name);
                cout << "Enter new gender: ";
                cin >> m->gender;
                cout << "Enter new Date of Birth (DD MM YYYY): ";
                cin >> m->date_of_birth->day >> m->date_of_birth->month >> m->date_of_birth->year;
                cout << "Data updated successfully for member wmh ID " << id << endl;
                return;
            }
        }
        cout << "Member not found wmh ID " << id << endl;
    }
    ~Family()
    {
        for (auto m : members)
        {
            delete m;
        }
    }
};

int Family::id = 0;

int main()
{
    int choice;
    Family obj(100, 6);

    cout << "-----------Welcome to the Qadeem Family :)-----------" << endl;
    cout << endl;

    do
    {
        menu();
        cout << "Enter Your Choice (1-5): ";
        cin >> choice;

        if (choice < 1 || choice > 5)
        {
            cout << "Invalid option. Please enter a valid choice." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            obj.displayWholeFamily();
            break;
        case 2:
            obj.addMember();
            break;
        case 3:
            obj.removeMember();
            break;
        case 4:
            obj.updateDataOfMember();
            break;
        case 5:
            cout << "Goodbye!" << endl;
            break;
        }

    } while (choice != 5);

    return 0;
}
