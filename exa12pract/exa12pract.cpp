// exa12pract.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <String>
#include <fstream>
#include <cstring>
#include <ctime>
using namespace std;
const int tst = 3;

//parent class
class Person
{
protected:
    char gender;
    int age;
public:
    Person();  //default constructo
    Person(Person&);   //copy constructor
    void setPerson(char, int);
    string getGender();
    int getAge();
    bool operator==(char);  //compares one persons age with another
};

//class implementation section
Person::Person()                    //defauklt constructo
{
    gender = ' ';
    age = 0;
}

Person::Person(Person& pr)          //copy constructor
{
    gender = ' ';
    age = 0;
}
void Person::setPerson(char gen, int ag)        //setter
{
    if (toupper(gen) == 'M' || toupper(gen) == 'F')
        gender = toupper(gen);
    else
        gender = 'M';

    if (ag > 0)
        age = ag;
    else
        age = 0;
}

string Person::getGender()
{
    string gn = "Female";
    if (gender == 'M')
        gn = 'M';
    return gn;
}

int Person::getAge()
{
    return age;
}

bool Person::operator==(char gn)
{
    bool test = false;
    if (toupper(gender) == toupper(gn))
        test = true;
    return test;
}
//chile class

class Student :public Person
{
private:
    string studNum;
    int marks[tst];
    float finMark;
    static float weights[tst];
    char result;
public:
    Student();
    void setStudent(string, char, int, int[]);
    string getStudNum();
    int getMarks(int);
    float getFinMark();
    char getResult();
    void calcFinMark();
    void detResult();
    Student operator+(Student&);
    bool operator > (Student&);
};
float Student::weights[] = { 0.25,0.3,0.45 };

//child class implementation section
Student::Student()
{
    studNum = " ";
    for (int i = 0; i < tst; i++)
    {
        marks[i] = 0;
    }
    finMark = .0;
    result = ' ';    
}
//setter
void Student::setStudent(string stn, char gn, int ag, int mrk[])
{
    setPerson(gn, ag);

    if (stn.size() > 0)
        studNum = stn;
    else
        studNum = "Unknown";

    for (int i = 0; i < tst; i++)
    {
        if (mrk[i] > 0)
            marks[i] = mrk[i];
        else
            marks[i] = 0;
    }
    //call calcfinmark
    calcFinMark();
}

string Student::getStudNum()
{
    return studNum;
}

int Student::getMarks(int i)
{
    return marks[i];
}

void Student::calcFinMark()
{
    float fm = 0;
    
    fm = (marks[0] * weights[0]) + (marks[1] * weights[1]) + (marks[2] * weights[2]);
    finMark = fm;
}\

float Student::getFinMark()
{
    return finMark;
}

void Student::detResult()
{
    if (getFinMark() > 50)
        result = 'P';
    else
        result = 'F';
}

char Student::getResult()
{
    detResult();
    return result;
}

//overloade operators
Student Student::operator+(Student& st)
{
    Student temp;
    temp.finMark = finMark + st.finMark;
    return temp;
}

bool Student::operator>(Student& st)
{
    bool test = false;
    if (age > st.age)
        test = true;
    return test;
}

//populate an array with data fom a csv file

void populateStudent(Student st[], int sz, string fName)
{
    int mrk[tst];
    int ag;
    string stn;
    char gn;
    string line = " ";
    int pos = 0;
    int count = 0;

    ifstream inFile(fName.c_str());

    if (!inFile)
        cout << fName << "File could not be found. \n ";
    else
    {
        while (getline(inFile, line))
        {
            //getting the student number
            pos = line.find(" , ");
            stn = line.substr(0, pos);
            line = line.erase(0, pos + 1);

            //getting the gender
            pos = line.find(" , ");
            gn = line.substr(0, pos)[0];
            line = line.erase(0, pos + 1);

            //getting the age
            pos = line.find(" , ");
            ag = atoi(line.substr(0, pos).c_str());
            line = line.erase(0, pos + 1);

            //getting the 3 marks
            for (int i = 0; i < tst; i++)
            {
                pos = line.find(" , ");
                mrk[i] = atoi(line.substr(0, pos).c_str());
                line = line.erase(0, pos + 1);
            }
            st[count].setStudent(stn, gn, ag, mrk);
            count++;
        }
    }

}

//displaying student info
void displayStud(Student st[], int sz)
{
    for (int i = 0; i < sz; i++)
    {
        cout << st[i].getStudNum() << " ";
        cout << st[i].getAge() << " " << st[i].getGender() << "\t";
        for (int x = 0; x < tst; x++)
        {
            cout << st[i].getMarks(x) << " ";
        }
        cout << st[i].getFinMark() << "\t" << st[i].getResult() << endl;
    }
    cout << endl << endl;
}

//displaying oldest student
void showOldest(Student st[], int sz)
{
    Student high = st[0];
    for (int i = 1; i < sz; i++)
    {
        if (st[i] > high)
            high = st[i];
    }
    cout << high.getStudNum() << " is the oldest student at " << high.getAge() << "years\n";
    cout << endl;
}

//function that calculates and displays the average final mark for both male and female students
void calcAvgPerGender(Student st[], int sz)
{
    Student sumMale;
    Student sumFemale;
    int count = 0;
    float  avgM=0;
    float avgF = 0;

    for (int i = 0; i < sz; i++)
    {
        if (st[i] == 'M')
        {
            sumMale = sumMale + st[i];
            count++;
        }
        else
        {
            sumFemale = sumFemale + st[i];

        }

    }
    avgM = sumMale.getFinMark() / count;
    avgF = sumFemale.getFinMark() / (sz - count);
    cout << "Male average final mark is : " << avgM << endl;
    cout << "Female average final mark is : " << avgF << endl;
}
//writes specific student data to an external file
void writeStats(Student st[], int size, string fName)
{
    ofstream outFile(fName.c_str());
    outFile << "Student Number,Final Mark, Result(P/F)\n";
    for (int x = 0; x < size; x++)
    {
        outFile << st[x].getStudNum() << "," << st[x].getFinMark() << ","
            << st[x].getResult() << endl;
    }
    cout << "All data has been written to " << fName << endl;
}

const int SIZE = 10;
int main()
{
    Student std[SIZE];

    populateStudent(std, SIZE, "studData.csv");
    displayStud(std, SIZE);
    showOldest(std, SIZE);
    calcAvgPerGender(std, SIZE);
    writeStats(std, SIZE, "studRes.csv");

    _getch();
    return 0;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
