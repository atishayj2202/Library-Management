//
// Created by Atishay Jain on 11/08/2018.
//

#ifndef TEST_BOOK_STATUS_H
#define TEST_BOOK_STATUS_H
#include<iostream>
#include<fstream>
using namespace std;

typedef struct book_status_variables{
    int bsid, left, noc;
}bsv;

class book_status_class{
private:
    bsv r;
    void make_data_status(int bid, int noc){
        r.bsid = bid;
        r.left = noc;
        r.noc = noc;
    }
protected:
    void modify_left_book_status(int bid, int num){
        ifstream fin;
        fin.open("book_status.lib", ios::binary | ios::in);
        ofstream fout;
        fout.open("temp.lib", ios::binary | ios::out);
        while(!fin.eof()){
            fin.read((char *)&r, sizeof(r));
            if (r.bsid != bid){
                fout.write((char *)&r, sizeof(r));
            }
            else {
                r.left = r.left + num;
                fout.write((char *)&r, sizeof(r));
            }
        }
        fin.close();
        fout.close();
        remove("book_status.lib");
        rename("temp.lib", "book_status.lib");
    }
    void add_record_status(int bid, int noc){
        make_data_status(bid, noc);
        ofstream record;
        record.open("book_status.lib", ios::binary | ios::app);
        record.write((char *)&r, sizeof(r));
        record.close();
    }
    void delete_record_status(int bid){
        ifstream da;
        da.open("book_status.lib", ios::binary | ios::in);
        ofstream temp;
        temp.open("temp.lib", ios::binary | ios::out);
        while(!da.eof()){
            da.read((char *)&r, sizeof(r));
            if(r.bsid != bid){
                temp.write((char *)&r, sizeof(r));
            }
        }
        temp.close();
        da.close();
        remove("book_status.lib");
        rename("temp.lib", "book_status.lib");
    }
    int ret_left_cop(int bid){
        ifstream ret;
        ret.open("book_status.lib");
        while(!ret.eof()){
            ret.read((char *)&r, sizeof(r));
            if (r.bsid == bid){
                return r.left;
            }
        }
        return -1;
    }
    int ret_total_cop(int bid){
        ifstream ret;
        ret.open("book_status.lib");
        while(!ret.eof()){
            ret.read((char *)&r, sizeof(r));
            if (r.bsid == bid){
                return r.noc;
            }
        }
        return -1;
    }
};

#endif //TEST_BOOK_STATUS_H
