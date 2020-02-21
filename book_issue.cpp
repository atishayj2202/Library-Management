#include<iostream>
#include<fstream>
#include"book.cpp"
#include"student.cpp"
using namespace std;

typedef struct book_issue_variables{
	int bid, sid, amount;
}biv;

class book_issue_class : public book_class, public student_class{
	private:
		biv lib;
		int search(int sid, int bid){
			int y = 0;
			ifstream search;
			search.open("book_issue.lib", ios::in | ios::binary);
			if (search.is_open()){
				while(!search.eof()){
					cout << lib.bid <<"\t"<<lib.sid;
					search.read((char *)&lib, sizeof(lib));
					if (lib.bid == bid && lib.sid == sid){
						y = 1;
						
						return 1;
					}
				}
			}
			search.close();
			if (y == 1){
				return 1;
			}
			else{
				return 0;
			}
		}
		void make_data(int bid, int sid){
			lib.amount = this->ret_amount(bid);
			lib.bid = bid;
			lib.sid = sid;
		}
	public:
		void issue(int sid, int bid){
			if (this->search_stu(sid) == 1 && this->search_book(bid) == 1){
				if (this->ret_noi(sid) == 0 && this->ret_left_cop(bid) != 0){
					if (this->search(sid, bid) == 0){
						this->make_data(bid, sid);
						ofstream fout;
						fout.open("book_issue.lib", ios::binary | ios::app);
						fout.write((char *) &lib, sizeof(lib));
						fout.close();
						this->modify_left_book_status(bid, -1);
						this->modify_left_student(sid, lib.amount);
						this->modify_left_student_status(sid, +1);
						cout << "ISSUED";
					}
					else {
						cout << "YOU HAVE SAME BOOK!";
					}
				}
				else {
					cout << "FIRST RETURN YOUR LAST BOOK!";
				}
			}
			else {
				cout << "ERROR! BOOK NOT FOUND!";
			}	
		}
		void retturn(int sid, int bid){
			if (this->search_book(bid) == 1 && this->search_stu(sid) == 1){
				if(this->search(sid, bid) == 1){
					ofstream fout;
					ifstream fin;
					fin.open("book_issue.lib", ios::binary | ios::in);
					fout.open("temp.lib", ios::binary | ios::out);
					while(!fin.eof()){
						fin.read((char *) &lib, sizeof(lib));
						if (lib.bid != bid && lib.sid != sid){
							fout.write((char *)&lib, sizeof(lib));
						}
					}
					fout.close();
					fin.close();
					remove("book_issue.lib");
					rename("temp.lib", "book_issue.lib");
					this->modify_left_book_status(bid, +1);
					this->modify_left_student_status(sid, -1);
					cout << "RETURNED";
				}
				else{
					cout << "YOU DO NOT HAVE THIS BOOK!";
				}
			}
			else{
				cout << "BOOK NOT FOUND!";
			}
		}
};
