
#include <iostream>
#include <fstream>
#include "Staffs.h" 
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




void Staffs::modifyInfo(string bookid) {
	Books book;
	book.modifyBookInfo(bookid);
}



void Staffs::addMemberShip(string userid) {
    Users user;
    //get a membership number
    string newMemberNo = user.setMemberNum(userid.substr(0, 7));
    //update member number
    user.updateMemberNo(userid, newMemberNo);
   

}


void Staffs::changeReserv(string bookid) {
    Books book;
    book.changBookStatus(bookid);
}

void Staffs::lentBookToList(string bookid,list<string> user_list) {
    Users u;
    Books book;
    int rt,num;
    //check user if exist
    list<string>::iterator iter;
    if (user_list.empty()) {
        cout << "List of user can not be empty!\n";
    }
    else {
        for (iter = user_list.begin(); iter != user_list.end(); iter++) {
            //check user valid
            rt = u.checkUserStatus(*iter);
            if (rt==2 || rt==1) {
               //add students file and update book's count
            }
            else {
                cout << "User: " << *iter << "is not exist or is not membership yet! ";
                continue;
            }
        }

    }
    
}