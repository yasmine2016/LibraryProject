#ifndef SUPPLIERS_H
#define SUPPLIERS_H
#include "Users.h" 
using namespace std;


class Suppliers :public Users {

public:

	void sellBook(string bookname,string author,string publisher,int count );
};




#endif // !SUPPLIERS_H
