#include <iostream>
#include <fstream>
#include "json/json.h"
#include "json/json-forwards.h"
#include "Books.h"
#include <algorithm>
#include <time.h>
using namespace std;


Json::Value root;
Json::Value Item;
Json::CharReaderBuilder rb;
//rb["collectComments"] = false;
Json::CharReader* reader(rb.newCharReader());
JSONCPP_STRING errs;
ifstream ifs;




Books::Books() {
	this->status = -1;
	this->count = 0;
}

Books::Books(string nm, string au, string pub) {
	this->name = nm;
	this->author = au;
	this->publisher = pub;
}

Books::Books(string bid, string nm, string au, string pub, int stat, int cnt) {
	this->book_id = bid;
	this->name = nm;
	this->author = au;
	this->publisher = pub;
	this->status = stat;
	this->count = cnt;
}




void Books::findBook(int ch, string strs) {
	ifs.open("books.json");
	root.clear();

	//从ifs中读取数据到Root
	if (parseFromStream(rb, ifs, &root, &errs) && errs.size() == 0){
		string name, author, publisher, status;
		string name_new, author_new, publisher_new, strs_new;
		//Read array info
		for (unsigned int i = 0; i < root["books"].size(); i++)
		{
			name = root["books"][i]["name"].asString();
			author = root["books"][i]["author"].asString();
			publisher = root["books"][i]["publisher"].asString();
			
			int count = root["books"][i]["count"].asInt();
			string bid = root["books"][i]["book_id"].asString();
			status = getStatus(bid);

			//tirm and lower
			name_new = trimLower(name);
			author_new = trimLower(author);
			publisher_new = trimLower(publisher);
			strs_new = trimLower(strs);

			// search
			if ((ch == 1 && name_new == strs_new) || (ch == 2 && author_new == strs_new) || (ch == 3 && publisher_new == strs_new)) {
				//read info of book
				printBook(bid,name, author, publisher, status, count);
				return;
			}
		}
		cout << "This book is not exist!" << endl;
		return;
	}
	else {
		cout << "parse error\n" << endl;
		return;
	}
	//delete reader;
}

string Books::getStatusDesc(int sta) {
	string rtn = "";
	ifs.open("status.json");
	root.clear();

	if (parseFromStream(rb, ifs, &root, &errs) && errs.size() == 0) {
		for (unsigned int i = 0; i < root["status"].size(); i++) {
			int st = root["status"][i]["status_id"].asInt();
			if (st == sta) {
				rtn = root["status"][i]["description"].asString();
				return rtn;
			}
		}
	}
	else
	{
		cout << "parse error\n" << endl;
		return rtn;
	}
	//delete reader;
}

string Books::trimLower(string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	auto itor = remove_if(str.begin(), str.end(), ::isspace);
	str.erase(itor, str.end());
	return str;
}

void Books:: printBook(string book_id,string name, string author, string publisher, string status,int count) {
	cout << "book_id: \t" << book_id << "Name: \t" << name << "\tAuthor: \t" << author << "\tPublisher: \t"
		<< publisher << "\tStatus: " << status << "\tCount: \n" << count << endl;
}

bool Books::isExistBookId(string book_id) {
	for (unsigned int i = 0; i < root["books"].size(); i++) {
		string id = root["books"][i]["book_id"].asString();
		if (id == book_id) {
			return true;
		}
	}
	return false;
}

string Books::isExistSameBook(string name, string author, string publisher) {
	for (unsigned int i = 0; i < root["books"].size(); i++) {
		string nm = root["books"][i]["name"].asString();
		string au = root["books"][i]["author"].asString();
		string pu = root["books"][i]["publisher"].asString();

		//tirm and lower
		string name_new = trimLower(name);
		string author_new = trimLower(author);
		string publisher_new = trimLower(publisher);
		string nm_new = trimLower(nm);
		string au_new = trimLower(au);
		string pu_new = trimLower(pu);

		if (name_new == nm_new && author_new == au_new && publisher_new == pu_new) {
			return root["books"][i]["book_id"].asString();
		}
	}
	return "";
}


void Books::writeFile() {
	ofstream ofs;
	ofs.open("books.json");
	ofs << root.toStyledString();
	ofs.close();
}

void Books::addBook(string b_name, string b_author, string b_publisher, int num) {
	//create bookid
	string id = setBookId(b_name);
	Item["book_id"] = id;
	Item["status"] = 0;
	Item["name"] = b_name;
	Item["author"] = b_author;
	Item["publisher"] = b_publisher;
	Item["count"] = num;
	root["books"].append(Item);
	Item.clear();
	writeFile();
}

void Books::updateBookCount(string book_id, int number) {
	ifs.open("books.json");
	root.clear();
	string id;
	int cont;
		if (parseFromStream(rb, ifs, &root, &errs) && errs.size() == 0) {
			for (unsigned int i = 0; i < root["books"].size(); i++) {
				if (book_id == id) {
					//record new 
					Books b_temp;
					b_temp.book_id = root["books"][i]["book_id"].asString();
					b_temp.status = root["books"][i]["status"].asInt();
					b_temp.name = root["books"][i]["name"].asString();
					b_temp.count = root["books"][i]["count"].asInt() + number;
					b_temp.author = root["books"][i]["author"].asString();
					b_temp.publisher = root["books"][i]["publisher"].asString();
					b_temp.price = root["books"][i]["price"].asDouble();

					//remove old
					removeOldData(i);

					//write a new
					writeFile();

					return;
				}
			}
			cout << "This book is not exist!" << endl;
			return;
		}
		else
		{
			cout << "parse error\n" << endl;
			return;
		}
}

void Books::removeOldData(int index) {
	root["books"][index].resize(0);

}

void Books::changBookStatus(string bid) {


}


void Books::modifyBookInfo(string bid) {

}

int Books::getStatus(string bookid) {
	return 0;
}

int Books::getCount(string bookid) {
	return 0;
}

string Books::setBookId(string b_name) {
	string part_str = trimLower(b_name).substr(0, 4);
	int part_num = getRandNum(10000);
	string newBookId = part_str + to_string(part_num);
	//check this bookId if exist in users file
	while (isExistBookId(newBookId) == true) {
		part_num = getRandNum(10000);
		newBookId = part_str + to_string(part_num);
	}
	return newBookId;
}

int Books::getRandNum(int num) {
	srand((int)time(0));
	return rand() % num;
}