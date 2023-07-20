#include<iostream>
#include"Admin_Menu.h"
#include"Student_Menu.h"
using namespace std;

int main(){
	cout << "ENTER 1 TO LOGIN AS ADMIN  \nENTER 2 TO LOGIN AS STUDENT \nENTER YOUR CHOICE = ";
	short num10;
	cin >> num10;
	cout << endl;
	switch(num10){
		case 1:
			admin();
			break;
		case 2:
			studnet();
			break;
		default:
			cout << "ERROR! WRONG INPUT";
	}
}
