
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "json/json-forwards.h"
#include "Users.h" 
#include <time.h>
using namespace std;



Json::Value root;
Json::Value Item;
Json::CharReaderBuilder rb;
//rb["collectComments"] = false;
Json::CharReader* reader(rb.newCharReader());
JSONCPP_STRING errs;
ifstream ifs;

Users::Users() {
	this->role = 111;
	this->status = 111;
	this->phone = 0;
}

Users::Users(string u, string m, int r, string p, int st, string nm, int ph, string em) {
	this->uid = u;
	this->mid = m;
	this->role = r;
	this->psw = p;
	this->status = st;
	this->name = nm;
	this->phone = ph;
}

void Users::setUid(string uid) {
	this->uid = uid;
}

string Users::getUid() {
	return this->uid;
}


void Users:: checkLogin(string name,string psw) {
	ifstream in("users.json", ios::binary);
	ifs.open("books.json");
	root.clear();
	
	if (parseFromStream(rb, ifs, &root, &errs) && errs.size() == 0)
	{
		//Read array info
		for (unsigned int i = 0; i < root["users"].size(); i++)
		{
			string username = root["users"][i]["user_id"].asString();
			string password = root["users"][i]["psw"].asString();
			int status = root["users"][i]["status"].asInt();
			if (username == name && password == psw) {
				if (status == 0) {
					// update status=1
					root["users"][i]["status"] = 1;
					writeFile();
					cout << "Login success\n" << endl;
				}
				else if (status == 1) {
					cout << "You are login status!\n" << endl;
				}
				return;
			}				
		}
		cout << "Username or Password is not correct!" << endl;
		return;
	}
	else
	{
		cout << "parse error\n" << endl;
		return;
	}
	in.close();
}

void Users::resetUserStatus(int s) {
	for (unsigned int i = 0; i < root["users"].size(); i++) {
		root["users"][i]["status"] = s;
		writeFile();
	}
}

void Users:: writeFile() {
	ofstream ofs;
	ofs.open("users.json");
	ofs << root.toStyledString();
	ofs.close();
}

int Users::checkUserStatus(string uid) {
	string u, m;
	int s, rt = -1;
	for (unsigned int i = 0; i < root["users"].size(); i++) {
		u = root["users"][i]["user_id"].asString();
		s = root["users"][i]["status"].asInt();
		m = root["users"][i]["member_id"].asString();
		if (u == uid ) {
			if (m != "" && s == 0) {
				//be already member but do not login
				return 2;
			}

			if (m == "" && s == 1) {
				//can apply and add membership
				return 0;
			}

			if (m != "" && s == 1) {
				//be already member and login
				return 1;
			}
		}
	}
	return rt;
}

string Users::setMemberNum(string role_name) {
	string newmeberid;
	int numb = getRandNum(1000);
	newmeberid = role_name + to_string(numb);
	//check this membernumber if exist in users file
	while (isExistMemberNo(newmeberid) == true) {
		numb = getRandNum(1000);
		newmeberid = role_name + to_string(numb);
	}
	return newmeberid;
}

int Users::getRandNum(int num) {
	srand((int)time(0));
	return rand() % num;
}

bool Users::isExistMemberNo(string memberno) {
	bool ck = false;
	string mb;
	for (unsigned int i = 0; i < root["users"].size(); i++) {
		mb = root["users"][i]["member_id"].asString();
		if (memberno == mb) {
			ck = true;
			return ck;
		}
	}
	return ck;
}

void Users::updateMemberNo(string userid,string membNo) {
	string u;
	for (unsigned int i = 0; i < root["users"].size(); i++) {
		u = root["users"][i]["user_id"].asString();
		if (u == userid) {
			//root["users"][i]["member_id"] = membNo;
			//record new data
			Users u_temp();
			string uid = u;
			string mbid = membNo;
			int role = root["users"][i]["role"].asInt();
			string pw = root["users"][i]["psw"].asString();
			int statu = root["users"][i]["status"].asInt();
			string nm = root["users"][i]["name"].asString();
			int phone = root["users"][i]["phone"].asInt();
			string email = root["users"][i]["email"].asString();

			removeOldData(i);

			writeFile();
			cout << "Congratulations! You are our membership now!\n" << endl;
			return;
		}
	}
	cout << "Update member number wrong!\n" << endl;
	return;
}

void Users::removeOldData(int index) {
	root["users"][index].resize(0);
}

