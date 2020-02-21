#include<iostream>
#include<fstream>
#include"book_status.cpp"

typedef struct books_variables{
	char name[20];
	int id, amount_due, noc;
}bv;

class book_class : protected book_status_class{
	private:
		bv s;
		void take_book_info(){
			cout << "ENTER BOOK NAME : ";
			cin >> s.name;
			cout << "ENTER BOOK ID : ";
			cin >> s.id;
			cout << "ENTER AMOUNT = ";
			cin >> s.amount_due;
			cout << "ENTER NO. OF BOOK IN LIBRARY = ";
			cin >> s.noc;
		}
	protected:
		int search_book(int bid){
			int y = 0;
			ifstream search;
			search.open("book.lib", ios::in | ios::binary);
			if(search.is_open()){
				while(!search.eof()){
					search.read((char *)&s, sizeof(s));
					if(s.id == bid){
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
		int ret_amount(int bid){
			ifstream sea;
			sea.open("book.lib", ios::binary | ios::in);
			while(!sea.eof()){
				sea.read((char *)&s, sizeof(s));
				if (s.id == bid){
					return s.amount_due;
				}
			}
			return -1;
		}
	public:
		void add_book(){
			take_book_info();
			add_record_status(s.id, s.noc);
			ofstream add;
			add.open("book.lib", ios::app | ios::binary);
			add.write((char *) &s, sizeof(s));
			add.close();
		}
		void delete_book(int bid){
			if (search_book(bid) == 1){
				if(this->ret_left_cop(bid) == this->ret_total_cop(bid)){
					delete_record_status(bid);
					ifstream p;
					p.open("book.lib", ios::binary | ios::in);
					ofstream temp;
					temp.open("temp.lib", ios::binary | ios::out);
					while(!p.eof()){
						p.read((char *)&s, sizeof(s));
						if(s.id != bid){
							temp.write((char *)&s, sizeof(s));
						}
					}
					cout << "BOOK DELETED ";
					p.close();
					temp.close();
					remove("book.lib");
					rename("temp.lib", "book.lib");
				}
				else{
					cout << "ALL BOOKS ARE NOT IN LIBRARY!";
				}
			}
			else {
				cout << "BOOK NOT FOUND ";
			}
		}
		void print_book_info(int bid){
			if (search_book(bid)==1){
				ifstream pri;
				pri.open("book.lib", ios::binary | ios::in);
				while(!pri.eof()){
					pri.read((char *)&s, sizeof(s));
					if (s.id == bid){
						cout << "NAME : " << s.name << endl;
						cout << "ID : " << s.id << endl;
						cout << "AMOUNT : "<< s.amount_due << endl;
						cout << "TOTAL NO. OF COPIES IN LIBRARY = " << s.noc << endl;
						cout << "NO. OF UNISSUED COPIES IN LIBRARY = " << ret_left_cop(bid) << endl;
						break;
					}
				}
				pri.close();
			}
			else {
				cout << "BOOK NOT FOUND";
			}
		}
};
