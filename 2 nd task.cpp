#include<iostream>
#include <pqxx/pqxx> 
#include <string>
#include "VariadicTable.h"

using namespace std;
using namespace pqxx;


class hotel {
public:
	string sql, cat, input, room, floor, type, date, price, user_name, ps_word, query, psword,response;
	string connectionC = "dbname = HOTEL user = postgres password = admin@123 hostaddr = 127.0.0.1 port = 5432";
	void display();
	void search();
	void bookroom();
	void update();
	void add();
	int login();
};
int hotel::login()
{
	pqxx::connection C(connectionC.c_str());
	
	cout << "enter the user name  :" << endl;
	cin >> user_name;
	cout << "enter the password  :" << endl;
	cin >> ps_word;
	cout << "    ";
	if ((user_name == "Mark") && (ps_word == "MARK.2")|| (user_name == "David") && (ps_word == "DAVID.2")|| (user_name == "John") && (ps_word == "JOHN.2"))
	{
		return 0;
	}
	else
	{
		return 1;
	}
	

}






void hotel::display()
{
	pqxx::connection C(connectionC.c_str());
    sql = "SELECT * from ROOMS ";
	/* Create a non-transactional object. */
	nontransaction N(C);
   /* Execute SQL query */
	result R(N.exec(sql));

	VariadicTable<string, string, string, string, string> vt({ "r_no", "floor", "price", "date", "type" });
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		vt.addRow(c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>(), c[4].as<string>());
	}

	vt.print(cout);
}

void hotel::search()
{
	pqxx::connection C(connectionC.c_str());
	cout << "category to search";
	cin >> cat;
	cout << " your choice";
	cin >> input;
	cout << "     ";
	cout << "    ";


	sql = "SELECT * from  ROOMS where " + cat + " = '" + input + "' ";
	/* Create a non-transactional object. */
	nontransaction N(C);

	/* Execute SQL query */
	result R(N.exec(sql));

	VariadicTable<string, string, string, string, string> vt({ "r_no", "floor", "price", "date", "type" });
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		vt.addRow(c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>(), c[4].as<string>());
	}

	vt.print(cout);

}

void hotel::bookroom()
{
	pqxx::connection C(connectionC.c_str());

	cout << "enter the room number to book";
	cin >> room;
	cout << "    ";
	cout << "    ";



	sql = "DELETE from ROOMS where r_no = ' " + room + " ' ";
	cout << "YOUR ROOM HAS BEEN BOOKED SUCCESSFULLY";
	cout << "    ";


	work W(C);
	/* Execute SQL query */
	W.exec(sql);
	W.commit();


}
void hotel::update()
{
	pqxx::connection C(connectionC.c_str());

	cout << "enter the room number to update";
	cin >> room;
	cout << "enter the category to update";
	cin >> cat;
	cout << "enter the new value to update";
	cin >> input;
	cout << "    ";
	
		/* Create a transactional object. */

	sql = "UPDATE ROOMS set  " + cat + "  = '"+input+"' where r_no = ' " + room + " ' ";

	/* Execute SQL query */
	work W(C);
	W.exec(sql);
	W.commit();


}

void hotel::add()
{
	pqxx::connection C(connectionC.c_str());

	cout << "enter the room number to add";
	cin >>room;
	cout << "    ";
	cout << "enter the floor";
	cin >>floor;
	cout << "    ";
	cout << "enter the price";
	cin >>price;
	cout << "    ";
	cout << "enter the date";
	cin >>date;
	cout << "    ";
	cout << "enter the type";
	cin >>type;
	cout << "    ";
	sql = "INSERT INTO ROOMS (r_no, floor, price, date, type) "
		"VALUES (" + room + ",'"+floor+"', " + price + ", ' " + date + " ','"+type+"'); ";

	/* Create a transactional object. */
	work W(C);

	/* Execute SQL query */
	W.exec(sql);
	W.commit();


}




int main()
{
	hotel p;
	string  choice;
		int LoginVariable;
	
	LoginVariable=p.login();
	if (LoginVariable == 0)
	{

		cout << " opened database successfully "<< endl;
		p.display();
		p.search();

		do {
			cout << "--------------------------------------------------------" << endl;
			cout << "OPERATIONS :- " << endl;
			cout << "--------------------------------------------------------" << endl;
			cout << "a).book a room :\nb).search a room\nc).update\nd).add a room\ne).display list " << endl;
			cout << " ";
			cin >> choice;
			if ((choice == "a") || (choice == "A"))
			{
				p.bookroom();


				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;

			}

			else if ((choice == "b") || (choice == "B"))
			{
				p.search();

				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;
			}

			else if ((choice == "c") || (choice == "C"))
			{
				p.update();

				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;
				cout << "   " << endl;
				cout << "   " << endl;
			}

			else if ((choice == "d") || (choice == "D"))
			{
				p.add();


				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;
				cout << "   " << endl;
				cout << "   " << endl;
			}
			else if ((choice == "e") || (choice == "E"))
			{
				p.display();
				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;
				cout << "   " << endl;
				cout << "   " << endl;
			}
			else {

				cout << "wrong choice" << endl;

				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;
				cout << "   " << endl;
				cout << "   " << endl;
			}

		} while ((choice.compare("yes") == 0) || (choice.compare("YES") == 0));

	}
	else {
		cout << "Can't open database" << endl;
		
	}
	return 0;
}