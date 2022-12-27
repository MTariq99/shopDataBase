#include <iostream>
#include <fstream>
#define SIZE 100
using namespace std;

class Registration
{
    string userName, password;

public:
    Registration() {}
    Registration(string un, string pw)
    {
        userName = un;
        password = pw;
    }
    void signUp();
    void logIn();
};
void Registration::signUp()
{
    cout << "Enter User Name : ";
    cin >> userName;
    cout << "Enter password : ";
    cin >> password;

    ofstream sign_up;
    sign_up.open("Sign_up.txt", ios::out | ios::app);
    if (!sign_up.good())
    {
        cout << "FILE COULD NOT OPEN\n";
        return;
    }

    sign_up << userName << endl;
    sign_up << password << endl;
    sign_up.close();
}
void Registration::logIn()
{
    int ts = 0;
    string un, pw;
    cout << "Enter User Name : ";
    cin >> userName;
    cout << "Enter password : ";
    cin >> password;
    ifstream login;
    login.open("Sign_up.txt", ios::in);
    if (!login.good())
    {
        cout << "COULD NOT READ FILE\n";
        return;
    }
    while (login)
    {
        login >> un;
        login >> pw;
       // if (un == userName && pw == password | userName == "admin" && password == "admin")
       // {
       //     cout << "LOGGEDIN\n";
       //     return;
       // }
    }
}





class category
{
    string name;
    unsigned int id, quantity;
    float price;

public:
    category() : name(""), id(0), quantity(0), price(0.0) {}                                               // default constructor
    category(string n, unsigned int i, unsigned int q, float p) : name(n), id(i), quantity(q), price(p) {} // parameterized constructor
    static category* sh[];
    static int count;
    virtual void setInfo();
    virtual void dispInfo() const;
    static void add();
    static void display();
    static void write();
    static void read();
};
category* category::sh[SIZE];
int category::count;
void category::setInfo()
{
    cout << "Enter the product ID : ";
    cin >> id;
    cout << "Enter product name : ";
    cin >> name;
    cout << "Enter price Quantity of the product : ";
    cin >> quantity;
    cout << "Enter the product Price : ";
    cin >> price;
}
void category::dispInfo() const
{
    cout << "PRODUCT ID : " << id << "\n";
    cout << "PRODUCT NAME : " << name << "\n";
    cout << "PRODUCT QUANTITY : " << quantity << "\n";
    cout << "PRODUCT PRICE : " << price << "\n";
}
class product : public category
{
    string categoryName;

public:
    product() : categoryName("") {} // default constructor
    product(string cn, string n, unsigned int i, unsigned int q, float p) : category(n, i, q, p) { categoryName = cn; }
    void setInfo();
    void dispInfo() const;
};
void product::setInfo()
{
    cout << "Enter category Name : ";
    cin >> categoryName;
    category::setInfo();
}
void product::dispInfo() const
{
    cout << "PRODUCT NAME : " << categoryName << "\n";
    category::dispInfo();
}


void category::add()
{
    cout << "\n----------------------------------------------------------\n";
    cout << "|                1. TO ADD PRODUCT CATEGORY                 |\n";
    cout << "\n----------------------------------------------------------\n";
     sh[count] = new product;
    sh[count++]->setInfo();
}
void category::display()
{
    for (int i = 0; i < count; i++)
    {
        cout << i + 1;
        sh[i]->dispInfo();
        cout << endl;
    }
}

void category::write()
{
    cout << " Writing  " << count << " categories.\n";
    ofstream oufile; // open ofstream in binary
    oufile.open("categoryDataBase.DAT", ios::trunc | ios::binary);
    if (!oufile)
    {
        cout << "\nCant open file\n";
        return;
    }
    for (int j = 0; j < count; j++) // for every category object
    {                               // get its type
        oufile.write((char*)(sh[j]), sizeof(product));
        if (!oufile)
        {
            cout << "\nCant write to file\n";
            return;
        }
    }
}

void category::read()
{
    ifstream infile; // open ifstream in binary
    infile.open("categoryDataBase.DAT", ios::binary);
    if (!infile)
    {
        cout << "\nCant open file\n";
        return;
    }
    count = 0;
    while (true)
    { // read type of next employee
        if (infile.eof()) // quit loop on eof
            break;
        if (!infile) // error reading type
        {
            cout << "\nCant read type from file\n";
            return;
        }
         sh[count] = new product;
        infile.read((char*)sh[count], sizeof(product));
        count++; // count categories
    }            // end while
    cout << " Reading " << count << " employees\n";
}


class admin {
    category categ;
public:
    void viewCategory();
    void addCategory();
    void writetofile();
    void readfromfile();
    void displayallcategories();
    void searchCategory();
    void deleteCategory();

};
void admin::viewCategory() {
    categ.display();
}
void admin::addCategory() {
    categ.add();
}
void admin::writetofile() {categ.write();}
void admin::readfromfile() { categ.read(); }
void admin::displayallcategories() { categ.display(); }
void admin::searchCategory(){}
void admin::deleteCategory(){}

int main()
{

    Registration registr;
    admin admn;
    int option;
    

    do
    {
        cout << "\n--------------------- Welcome to the main Manu-----------------------\n";
        cout << "|                                                                     |\n";
        cout << "|                            1 SIGN_UP                                |\n";
        cout << "|                            2 LOGIN                                  |\n";
        cout << "|                            3 ADD CATEGORY                           |\n";
        cout << "|                            4 WRITE CATEGORY                         |\n";
        cout << "|                            5 READ CATEGORY                          |\n";
        cout << "|                            6 DISPLAY CATEGORY                       |\n";
        cout << "\n---------------------------------------------------------------------\n";
        cout << "Enter A Number in the Above Options : ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Welcome to the Registration\n";
            registr.signUp();
            break;
        case 2:
            cout << "LOGIN YOUR ACCOUNT\n";
            registr.logIn();
            break;
        case 3:
            cout << "ADDING NEW CATEGORY \n";
           // category::add();
            admn.addCategory();
            break;
        case 4:
           // category::write();
            admn.writetofile();
            break;
        case 5:
           // category::read();
            admn.readfromfile();
            break;
        case 6:
           // category::display();
            admn.displayallcategories();
            break;
        case 9:
            cout << "Program is terminated successfully\n";
            exit(0);
            break;
        default:
            cout << "INVALID OPTION\n";
            break;
        }

    } while (option != 9);

    return 0;
}

// void student::saveData(student stu[], int &ts)
// {
//     ofstream outfile;
//     outfile.open("studentsData.txt", ios::out);
//     if (!outfile.good())
//     {
//         cout << "FILE COULD NOT OPEN\n";
//         return;
//     }
//     for (int i = 0; i < ts; i++)
//     {

//         outfile << stu[i].regNumber << " ";
//         outfile << stu[i].studentName << endl;
//         outfile << stu[i].studentFatherName << endl;
//         outfile << stu[i].DOB.day << " ";
//         outfile << stu[i].DOB.month << " ";
//         outfile << stu[i].DOB.year << " ";
//         outfile << stu[i].DOA.day << " ";
//         outfile << stu[i].DOA.month << " ";
//         outfile << stu[i].DOA.year << " ";
//         outfile << stu[i].GPA;
//     }
//     outfile.close();
// }

// void student::loaddata(student stu[], int &ts)
// {
//     ifstream infile;
//     infile.open("studentsData.txt", ios::in);
//     if (!infile.good())
//     {
//         cout << "COULD NOT READ FILE\n";
//         return;
//     }
//     ts = 0;
//     while (infile)
//     {
//         infile >> stu[ts].regNumber;
//         getline(infile, stu[ts].studentName, '\n');
//         getline(infile, stu[ts].studentFatherName, '\n');
//         infile >> stu[ts].DOB.day;
//         infile >> stu[ts].DOB.month;
//         infile >> stu[ts].DOB.year;
//         infile >> stu[ts].DOA.day;
//         infile >> stu[ts].DOA.month;
//         infile >> stu[ts].DOA.year;
//         infile >> stu[ts].GPA;
//         ts++;
//     }
//     ts--;
//     infile.close();
// }
