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
        if (un == userName && pw == password | userName == "admin" && password == "admin")
        {
            cout << "LOGGEDIN\n";
            return;
        }
    }
}
enum cType
{
   p
};
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
    virtual cType get_category();
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

/*class outfitCategory : public category
{
    string categoryName;

public:
    outfitCategory() : categoryName("") {} // default constructor
    outfitCategory(string cn, string n, unsigned int i, unsigned int q, float p) : category(n, i, q, p) { categoryName = cn; }
    void setInfo();
    void dispInfo() const;
};
void outfitCategory::setInfo()
{
    cout << "Enter category Name : ";
    cin >> categoryName;
    category::setInfo();
}
void outfitCategory::dispInfo() const
{
    cout << "CATEGORY NAME : " << categoryName << "\n";
    category::dispInfo();
}

class groceryCategory : public category
{
    string categoryName;

public:
    groceryCategory() : categoryName("") {}                                                                                 // default constructor
    groceryCategory(string cn, string n, unsigned int i, unsigned int q, float p) : category(n, i, q, p) { categoryName = cn; } // paremeterized constructor
    void setInfo();
    void dispInfo() const;
};
void groceryCategory::setInfo()
{
    cout << "Enter category Name : ";
    cin >> categoryName;
    category::setInfo();
}
void groceryCategory::dispInfo() const
{
    cout << "CATEGORY NAME : " << categoryName << "\n";
    category::dispInfo();
}*/

cType category::get_category()
{
 if (typeid(*this) == typeid(product))
    {
        return p;
    }
    else
    {
        cerr << "BAD CATEGORY TYPE\n";
    }
    return p;
}

void category::add()
{
    int option;
    cout << "\n----------------------------------------------------------\n";
    cout << "|                1. TO ADD PRODUCT CATEGORY                 |\n";
    cout << "\n----------------------------------------------------------\n";
    cout << "Enter an Option : ";
    cin >> option;
    switch (option)
    {
    case 1:
        sh[count] = new product;
        break;
    case 2:
      //  sh[count] = new product;
        break;
    case 3:
       // sh[count] = new outfitCategory;
        break;
    default:
        cout << "INVALID OPTION\n";
        break;
    }
    sh[count++]->setInfo();
}
void category::display()
{
    for (int i = 0; i < count; i++)
    {
        cout << i + 1;
        switch (sh[i]->get_category())
        {
        case p:
            cout << " : -----------PRODUCT CATEGORY-----------------\n";
            break;
        default:
            cerr << "BAD CATEGORY TYPE \n";
            break;
        }
        sh[i]->dispInfo();
        cout << endl;
    }
}

void category::write()
{
    int size;
    cout << " Writing  " << count << " categories.\n";
    ofstream oufile; // open ofstream in binary
    cType ct;        // type of each category object
    oufile.open("categoryDataBase.DAT", ios::trunc | ios::binary);
    if (!oufile)
    {
        cout << "\nCant open file\n";
        return;
    }
    for (int j = 0; j < count; j++) // for every category object
    {                               // get its type
        ct = sh[j]->get_category();
        // write type to file
        oufile.write((char*)&ct, sizeof(ct));
        switch (ct) // find its size
        {
        case p:
            size = sizeof(product);
            break;
        } // write Categories object to file
        oufile.write((char*)(sh[j]), size);
        if (!oufile)
        {
            cout << "\nCant write to file\n";
            return;
        }
    }
}

void category::read()
{
    int size=0;        // size of person object
    cType ct = p;    // type of person
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
        infile.read((char*)&ct, sizeof(ct));
        if (infile.eof()) // quit loop on eof
            break;
        if (!infile) // error reading type
        {
            cout << "\nCant read type from file\n";
            return;
        }
        switch (ct)
        {       // make new person
        case p:
            sh[count] = new product;
            size = sizeof(product);
            break;
        default:
            cout << "\nUnknown type in file\n";
            return;
        } // read data from file into it
        infile.read((char*)sh[count], size);
        if (!infile) // error but not eof
        {
            cout << "\nCant read data from file\n";
            return;
        }
        count++; // count categories
    }            // end while
    cout << " Reading " << count << " employees\n";
}

int main()
{

    Registration registr;
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
            category::add();
            break;
        case 4:
            category::write();
            break;
        case 5:
            category::read();
            break;
        case 6:
            category::display();
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
