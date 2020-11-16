#ifndef BOOKS_H
#define BOOKS_H
#include "json/json.h"
#include "json/json-forwards.h"
using namespace std;

class Books {


private:
	string book_id;
	string name;
	string author;
	string publisher;
	int status;
	int count;
	double price;

public:

	Books();
	Books(string name, string author, string publisher);
	Books(string book_id,string name, string author, string publisher, int status, int count);
	void findBook(int ch, string str);
	string getStatusDesc(int st);
	int getStatus(string bookid);
	int getCount(string bookid);
	string trimLower(string str);
	void printBook(string book_id,string name,string author,string publisher,string status,int count);
	bool isExistBookId(string book_id);
	string isExistSameBook(string name, string author, string publisher);
	void writeFile();
	void removeOldData(int index);
	void modifyBookInfo(string bookid);
	void changBookStatus(string bookid);
	void addBook(string book_name, string book_author, string publicsher, int num);
	void updateBookCount(string book_id, int count);
	int getRandNum(int num);
	string setBookId(string book_name);
};




#endif // !BOOKS_H
