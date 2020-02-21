#include<iostream>
using namespace std;

void studnet(){
	system("cls");
	book_issue_class obi;
	int sid, menu, bid;
	cout << "ENTER YOUR ID = ";
	cin >> sid;
	if (obi.print_stu_info(sid) == 1){
		cout << "0 TO END APPLICATION \n1 TO ISSUE BOOK \n2 TO RETURN BOOK \n3 TO PAY DUE AMOUNT \n4 TO PRINT BOOK INFO\nENTER YOUR CHOICE : ";
		cin >>menu;
		cout << endl;
		switch(menu){
			case 0:
				break;
			case 1:
				cout << "ENTER BOOK ID = ";
				cin >> bid;
				obi.issue(sid, bid);
				break;
			case 2:
				cout << "ENTER BOOK ID = ";
				cin >> bid;
				obi.retturn(sid, bid);
				break;
			case 3:
				obi.pay(sid);
				break;
			case 4:
				cout << "ENTER BOOK ID = ";
				cin >> bid;
				obi.print_book_info(bid);
				break;
			default:
				cout << "ERROR! WRONG INPUT";
		}
	}
}
