#ifndef USERS_H
#define USERS_H
#include "json/json.h"
#include "json/json-forwards.h"
using namespace std;


class Users {
	
protected:
	string uid;
	string mid;
	int role;
	string psw;
	int status;
	string name;
	int phone;
	string email;
	
		
public:
	void setUid(string id);
	string getUid();
	Users();
	Users(string u, string m, int r, string p, int st, string nm, int ph, string em);
	void checkLogin(string name, string psw);
	int checkUserStatus(string userid);
	void resetUserStatus(int stat);
	void writeFile();
	void removeOldData(int index);
	bool isUserValid(string uid);

	bool isExistMemberNo(string memberno);
	string setMemberNum(string role_name);
	void updateMemberNo(string userid,string membNo);
	int getRandNum(int num);
};




#endif // !USERS_H
