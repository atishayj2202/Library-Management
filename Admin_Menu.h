//
// Created by Atishay Jain on 12/08/2018.
//
#ifndef TEST_ADMIN_MENU_H
#define TEST_ADMIN_MENU_H
#include<iostream>
#include"book_issue.h"
using namespace std;

void admin(){
    system("cls");
    short menu, bid, sid;
    cout << "1 TO ADD BOOK \n2 TO DELETE BOOK \n3 TO PRINT BOOK INFO \n4 TO ADD STUDENT \n5 TO DELETE STUDENT\n6 TO PRINT STUDENT INFO\nENTER YOUR CHOICE : ";
    cin >> menu;
    cout << endl;
    book_issue_class obj;
    switch(menu){
        case 1:
            obj.add_book();
            break;
        case 2:
            cout << "ENTER BOOK ID:";
            cin >> bid;
            obj.delete_book(bid);
            break;
        case 3:
            cout << "ENTER BOOK ID:";
            cin >> bid;
            obj.print_book_info(bid);
            break;
        case 4:
            obj.add_stu();
            break;
        case 5:
            cout << "ENTER STUDENT ID : ";
            cin >> sid;
            obj.delete_stu(sid);
            break;
        case 6:
            cout << "ENTER STUDENT ID : ";
            cin >> sid;
            obj.print_stu_info(sid);
            break;
        default:
            cout << "ERROR! WRONG INPUT!";
    }
}
#endif //TEST_ADMIN_MENU_H