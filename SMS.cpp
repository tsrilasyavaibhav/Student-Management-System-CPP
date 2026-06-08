#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
using namespace std;

class Student{
    int id;
    char name[50];
    float marks;

public:

    void input(){
        cout<<"\nEnter ID: ";
        cin>>id;

        cin.ignore();

        cout<<"Enter Name: ";
        cin.getline(name,50);

        cout<<"Enter Marks: ";
        cin>>marks;
    }

    void show(){
        cout<<left<<setw(10)<<id
            <<setw(25)<<name
            <<setw(10)<<marks<<endl;
    }

    int getID(){
        return id;
    }

    void update(){
        cin.ignore();

        cout<<"Enter New Name: ";
        cin.getline(name,50);

        cout<<"Enter New Marks: ";
        cin>>marks;
    }
};

void header(){
    cout<<"\n=================================================\n";
    cout<<"          STUDENT MANAGEMENT SYSTEM\n";
    cout<<"=================================================\n";
}

void addStudent(){

    Student s;

    ofstream file("students.dat",ios::binary|ios::app);

    s.input();

    file.write((char*)&s,sizeof(s));

    file.close();

    cout<<"\nStudent Added Successfully!\n";
}

void displayStudents(){

    Student s;

    ifstream file("students.dat",ios::binary);

    if(!file){
        cout<<"\nNo Records Found!\n";
        return;
    }

    cout<<"\n-------------------------------------------------\n";
    cout<<left<<setw(10)<<"ID"
        <<setw(25)<<"NAME"
        <<setw(10)<<"MARKS"<<endl;

    cout<<"-------------------------------------------------\n";

    while(file.read((char*)&s,sizeof(s))){
        s.show();
    }

    file.close();
}

void searchStudent(){

    Student s;

    int id;
    bool found=false;

    cout<<"Enter Student ID: ";
    cin>>id;

    ifstream file("students.dat",ios::binary);

    while(file.read((char*)&s,sizeof(s))){

        if(s.getID()==id){

            cout<<"\nStudent Found:\n";

            cout<<left<<setw(10)<<"ID"
                <<setw(25)<<"NAME"
                <<setw(10)<<"MARKS"<<endl;

            s.show();

            found=true;

            break;
        }
    }

    file.close();

    if(!found)
        cout<<"\nStudent Not Found!\n";
}

void updateStudent(){

    Student s;

    int id;

    bool found=false;

    cout<<"Enter Student ID to Update: ";

    cin>>id;

    fstream file("students.dat",
                 ios::binary|
                 ios::in|
                 ios::out);

    while(file.read((char*)&s,sizeof(s))){

        if(s.getID()==id){

            cout<<"\nCurrent Details:\n";

            s.show();

            cout<<"\nEnter New Details:\n";

            s.update();

            file.seekp(-sizeof(s),ios::cur);

            file.write((char*)&s,sizeof(s));

            found=true;

            cout<<"\nUpdated Successfully!\n";

            break;
        }
    }

    file.close();

    if(!found)
        cout<<"\nStudent Not Found!\n";
}

void deleteStudent(){

    Student s;

    int id;

    bool found=false;

    cout<<"Enter Student ID to Delete: ";

    cin>>id;

    ifstream file("students.dat",ios::binary);

    ofstream temp("temp.dat",ios::binary);

    while(file.read((char*)&s,sizeof(s))){

        if(s.getID()!=id){

            temp.write((char*)&s,sizeof(s));

        }else{

            found=true;

        }
    }

    file.close();

    temp.close();

    remove("students.dat");

    rename("temp.dat","students.dat");

    if(found)

        cout<<"\nDeleted Successfully!\n";

    else

        cout<<"\nStudent Not Found!\n";
}

int main(){

    int choice;

    do{

        header();

        cout<<"\n1. Add Student";
        cout<<"\n2. Display Students";
        cout<<"\n3. Search Student";
        cout<<"\n4. Update Student";
        cout<<"\n5. Delete Student";
        cout<<"\n6. Exit";

        cout<<"\n\nEnter Choice: ";

        cin>>choice;

        switch(choice){

            case 1:

                addStudent();

                break;

            case 2:

                displayStudents();

                break;

            case 3:

                searchStudent();

                break;

            case 4:

                updateStudent();

                break;

            case 5:

                deleteStudent();

                break;

            case 6:

                cout<<"\nThank You!\n";

                break;

            default:

                cout<<"\nInvalid Choice!\n";
        }

        if(choice!=6){

            cout<<"\nPress Enter To Continue...";

            cin.ignore();

            cin.get();
        }

    }while(choice!=6);

    return 0;
}