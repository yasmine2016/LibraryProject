#ifndef STUDENTS_H
#define STUDENTS_H
#include "Users.h" 
using namespace std;


class Students:public Users {


public:
	bool ifBorrowed(string userid);
	void addBorrowInfo(string userid, string bookid);
	void returnBook(string userid, string bookid);
	void borrowBook(string userid,string bookid);
};




#endif // !STUDENTS_H
