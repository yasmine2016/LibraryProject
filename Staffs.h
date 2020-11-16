#ifndef STAFFS_H
#define STAFFS_H
#include "Users.h" 
#include <list>
using namespace std;


class Staffs :public Users {

public:

	void modifyInfo(string bookid);
	void addMemberShip(string userid);
	void changeReserv(string bookid);
	void lentBookToList(string bookid, list<string> user_list);
};




#endif // !STAFFS_H
