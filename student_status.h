//
// Created by Atishay Jain on 11/08/2018.
//

#ifndef TEST_STUDENT_STATUS_H
#define TEST_STUDENT_STATUS_H
#include<iostream>
#include<fstream>
using namespace std;

typedef struct student_status_variable{
    int id, issued;
}ssv;

class student_status_class{
private:
    ssv data;
    void make_data_stu_status(int sid){
        data.id= sid;
        data.issued = 0;
    }
protected:
    void modify_left_student_status(int sid, int num){
        ifstream fin;
        fin.open("student_status.lib", ios::binary | ios::in);
        ofstream fout;
        fout.open("temp.lib", ios::binary | ios::out);
        while(!fin.eof()){
            fin.read((char *)&data, sizeof(data));
            if (data.id != sid){
                fout.write((char *)&data, sizeof(data));
            }
            else {
                data.issued = data.issued + num;
                fout.write((char *)&data, sizeof(data));
            }
        }
        fin.close();
        fout.close();
        remove("student_status.lib");
        rename("temp.lib", "student_status.lib");
    }
    void add_record_stu_status(int sid){
        this->make_data_stu_status(sid);
        ofstream apple;
        apple.open("student_status.lib", ios::app | ios::binary);
        apple.write((char *)&data, sizeof(data));
        apple.close();
    }
    void delete_record_stu_status(int sid){
        ifstream da;
        da.open("student_status.lib", ios::binary | ios::in);
        ofstream temp;
        temp.open("temp.lib", ios::binary | ios::out);
        while(!da.eof()){
            da.read((char *)&data, sizeof(data));
            if(data.id != sid){
                temp.write((char *)&data, sizeof(data));
            }
        }
        temp.close();
        da.close();
        remove("student_status.lib");
        rename("temp.lib", "student_status.lib");
    }
    int ret_noi(int sid){
        ifstream ret;
        ret.open("student_status.lib");
        while(!ret.eof()){
            ret.read((char *)&data, sizeof(data));
            if (data.id == sid){
                return data.issued;
            }
        }
        return -1;
    }
};

#endif //TEST_STUDENT_STATUS_H
