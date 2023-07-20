//
// Created by Atishay Jain on 11/08/2018.
//

#ifndef TEST_STUDENT_H
#define TEST_STUDENT_H
#include<iostream>
#include<fstream>
#include"student_status.h"
using namespace std;

typedef struct student_variables{
    char clas[4], name[20];
    int amount, id;
}sv;

class student_class : protected student_status_class{
private:
    sv dat;
    void take_stu_info(){
        cout << "ENTER NAME : ";
        cin >> dat.name;
        cout << "ENTER ID : ";
        cin >> dat.id;
        dat.amount = 0;
        cout << "ENTER CLASS : ";
        cin >> dat.clas;
    }
    int ret_amount_stu_due(int sid){
        ifstream ret;
        ret.open("student.lib");
        while(!ret.eof()){
            ret.read((char *)&dat, sizeof(dat));
            if (dat.id == sid){
                return dat.amount;
            }
        }
        ret.close();
        return -1;
    }
protected:
    int search_stu(int sid){
        int y = 0;
        ifstream search;
        search.open("student.lib", ios::in | ios::binary);
        if(search.is_open()){
            while(!search.eof()){
                search.read((char *)&dat, sizeof(dat));
                if(dat.id == sid){
                    y = 1;
                    return 1;
                }
            }
        }
        else{
            cout << "DIRECTORY NOT FOUND!";
        }
        if (y == 0){
            return 0;
        }
        else{
            return 1;
        }
    }

    void modify_left_student(int sid, int num){
        ifstream fin;
        fin.open("student.lib", ios::binary | ios::in);
        ofstream fout;
        fout.open("temp.lib", ios::binary | ios::out);
        while(!fin.eof()){
            fin.read((char *)&dat, sizeof(dat));
            if (dat.id != sid){
                fout.write((char *)&dat, sizeof(dat));
            }
            else {
                dat.amount = dat.amount + num;
                fout.write((char *)&dat, sizeof(dat));
            }
        }
        fin.close();
        fout.close();
        remove("student.lib");
        rename("temp.lib", "student.lib");
    }

public:
    void pay(int sid){
        int am;

        cout << "ENTER AMOUNT = ";
        cin >> am;
        if (this->ret_amount_stu_due(sid) <= am){
            this->modify_left_student(sid, -am);
            cout << "PAYMENT DONE!";
        }
        else{
            cout << "YOU HAVE ENTERED EXTRA AMOUNT";
        }
    }
    void add_stu(){
        take_stu_info();
        add_record_stu_status(dat.id);
        ofstream make;
        make.open("student.lib", ios::binary | ios::app);
        make.write((char *)&dat, sizeof(dat));
        make.close();
    }
    void delete_stu(int sid){
        if (search_stu(sid) == 1){
            if (this->ret_noi(sid) == 0){
                this->delete_record_stu_status(sid);
                ifstream p;
                p.open("student.lib", ios::binary | ios::in);
                ofstream temp;
                temp.open("temp.lib", ios::binary | ios::out);
                while(!p.eof()){
                    p.read((char *)&dat, sizeof(dat));
                    if(dat.id != sid){
                        temp.write((char *)&dat, sizeof(dat));
                    }
                }
                cout << "STUDENT DELETED";
                p.close();
                temp.close();
                remove("student.lib");
                rename("temp.lib", "student.lib");
            }
            else{
                cout << "STUDENT HAVE BOOK";
            }
        }
        else {
            cout << "STUDENT NOT FOUND!";
        }
    }
    int print_stu_info(int sid){
        if (this->search_stu(sid) == 1){
            ifstream pr;
            pr.open("student.lib", ios::binary | ios::in);
            while(!pr.eof()){
                pr.read((char *)&dat, sizeof(dat));
                if(dat.id == sid){
                    cout << "NAME               : " << dat.name << endl;
                    cout << "ID                 : " << dat.id << endl;
                    cout << "CLASS              : " << dat.clas << endl;
                    cout << "AMOUNT             = " << dat.amount << endl;
                    cout << "TOTAL ISSUED BOOKS = " << this->ret_noi(dat.id)<< endl;
                    return 1;
                    break;
                }
            }
            pr.close();
        }
        else {
            cout << "ERROR! STUDENT NOT FOUND!";
            return 0;
        }
        cout << "Unexpected";
        return 0;
    }
};

#endif //TEST_STUDENT_H
