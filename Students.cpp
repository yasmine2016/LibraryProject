
#include <iostream>
#include <fstream>
#include "Students.h" 
#include "Books.h"
#include <time.h>
using namespace std;



Json::Value root;
Json::Value Item;
Json::CharReaderBuilder rb;
//rb["collectComments"] = false;
Json::CharReader* reader(rb.newCharReader());
JSONCPP_STRING errs;
ifstream ifs;


void Students::borrowBook(string userid ,string bookid) {
	Books book;
	//check if login
	int ck_status = checkUserStatus(userid);
	if (ck_status == -1) {
		cout << "Sorry! please Login first!\n";
		return;
	}

	//is membership, can borrow book
	if (ck_status == 1) {
		//update book count-1
		book.updateBookCount(bookid, -1);
		//add students file
		addBorrowInfo(userid, bookid);
		return;
	}

	//is not membership,borrow only one book
	//check borrowed book
	if (ck_status == 0) {
		if (ifBorrowed(userid)) {
			cout << "Sorry! you can just borrow one book,Please apply a membership !\n";
			return;
		}
	}
}

bool Students::ifBorrowed(string userid) {
	for (unsigned int i = 0; i < root["students.json"].size(); i++) {
		uid = root["students"][i]["user_id"].asString();
		if (uid == userid) {
			//already borrowed
			return true;
		}
	}
	return false;
}

void Students::returnBook(string userid, string bookid) {
	//check if login
	int ck_status = checkUserStatus(userid);
	if (ck_status == -1) {
		cout << "Sorry! please Login first!\n";
		return;
	}

	//check if over deadline?
	//student file CHECK 是否借了此书，且是否超时，超时提示罚款

	//否则update book's count +1,delete student file
}

void Students::addBorrowInfo(string userid, string bookid) {
	//limit time of borrowwing book 2months
	
}