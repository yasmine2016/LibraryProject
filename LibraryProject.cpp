// LibraryProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <fstream>
#include <stdlib.h>
#include "Students.h"
#include "Staffs.h"
#include "Suppliers.h"
#include "Books.h"
#include <list>
using namespace std;






Students stud;
Staffs staf;
Suppliers supp;
Books bk;



int chkStatus(Users u) {
    string userid = u.getUid();
    int ck = stud.checkUserStatus(userid);
    return ck;
}

void option(int ch,int opt) {
    string nm, pw, book,b_name,b_author,b_id,b_publisher, usid_member, id_staff1, id_staff;
    string bid, bid1, userid, uid_student, uid_staff, uid_staff1,uid_supp, bkid,b_bid,uid_lend;
    int choix, num, ck_stat, b_num, stat_staf2, stat_staf, stat_stud, stat_staf4;
    int stat_staf3, stat_supp, stat_staf1, stat_stud5, num_book;
    list<string> book_list;

   // while (true) {
        switch (opt) {

            case 1:

                cout << "Please enter username/userId:\n";
                cin >> nm;
                cout << "Please enter password:\n";
                cin >> pw;
                
                // check login
                if (ch == 1) {
                    stud.checkLogin(nm, pw);
                    stud.setUid(nm);
                }
                if (ch == 2) {
                    staf.checkLogin(nm, pw);
                    staf.setUid(nm);
                }
                if (ch == 3) {
                    supp.checkLogin(nm, pw);
                    supp.setUid(nm);
                }
                break;
            case 2:

                cout << "You want to search book by \n1.book's Name\n2.book's Author\n3.book's Publisher:\n4.Exit\n";
                cin >> choix;
                if (choix == 1 || choix == 2 || choix == 3) {
                    cout << "Please enter book's Name or Author or Publisher:\n";
                    cin >> book;
                    //search book info
                    bk.findBook(choix, book);
                }
                else if(choix != 4)
                {
                    cout << "Invalid enter!\n";
                }
                break;
            case 3:

                //Apply for membership(student)
                if (ch == 1) {
                    //check if login
                    ck_stat = chkStatus(stud);
                    if (ck_stat == 0) {
                        //get a membership number
                        string newMemberNo = stud.setMemberNum(userid.substr(0, 7));
                        //update member number
                        stud.updateMemberNo(userid, newMemberNo);
                    }
                    else if(ck_stat == 1){
                        cout << "Sorry! you are already membership!\n";
                    }
                    else {
                        cout << "Sorry! please Login first!\n";
                    }
                }

                //Add book(Library Staff)
                if (ch == 2) {
                    //check if login
                    stat_staf = chkStatus(stud);
                    if (stat_staf == -1) {
                        cout << "Sorry! please Login first!\n";
                    }
                    else {
                        
                        cout << "Enter book's name:\n";
                        cin >> b_name;
                        cout << "Enter book's author:\n";
                        cin >> b_author;
                        cout << "Enter book's publisher:\n";
                        cin >> b_publisher;
                        //check if exist
                        if (bk.isExistSameBook(b_name, b_author, b_publisher) != "") {
                            cout << "This book is already exist!\n";
                        }
                        else {
                            cout << "Enter book's count:\n";
                            cin >> b_num;
                            // write book
                            bk.addBook(b_name, b_author, b_publisher,b_num);
                        }
                    }
                   
                }

                //Sell book(Supplier)
                if (ch == 3) {
                    //check if login
                    stat_supp = chkStatus(stud);
                    if (stat_supp == -1) {
                        cout << "Sorry! please Login first!\n";
                    }
                    else {
                        cout << "Enter book's name:\n";
                        cin >> b_name;
                        cout << "Enter book's author:\n";
                        cin >> b_author;
                        cout << "Enter book's publisher:\n";
                        cin >> b_publisher;
                        cout << "Enter book's count:\n";
                        cin >> b_num;
                        //check if exist
                        string book_id = bk.isExistSameBook(b_name, b_author, b_publisher);
                        if (book_id != "") {
                            // exist , update count 
                            bk.updateBookCount(book_id, b_num);
                        }
                        else {
                            // write book
                            bk.addBook(b_name, b_author, b_publisher, b_num);
                        }
                    }
                }
                break;

            case 4:

                //Borrow book(student)
                if (ch == 1) {
                    //check if login
                    stat_stud = chkStatus(stud);
                    if (stat_stud == -1) {
                        cout << "Sorry! please Login first!\n";
                    }
                    else {
                        cout << "Enter book's ID:\n";
                        cin >> b_id;
                        stud.borrowBook(uid_student, b_id);
                    }
                }

                //Modify book's information(Library Staff)
                if (ch == 2) {
                    
                    //check if login
                    stat_staf3 = chkStatus(stud);
                    if (stat_staf3 == -1) {
                        cout << "Sorry! please Login first!\n";
                    }
                    else {
                        cout << "Enter book's ID:\n";
                        cin >> bid;
                        staf.modifyInfo(bid);
                    }
                }
                break;

            case 5:
                
                //Return book(student)
                if (ch == 1) {
                    //check if login
                    stat_stud5 = chkStatus(stud);
                    if (stat_stud5 == -1) {
                        cout << "Sorry! please Login first!\n";
                    }
                    else {
                        cout << "Enter book's ID:\n";
                        cin >> bid1;
                        stud.returnBook(uid_student, bid1);
                    }
                }

                //Add member(Library Staff)
                if (ch == 2) {
                    //check if login
                    stat_staf1 = chkStatus(stud);
                    if (stat_staf1 == 0) {
                        cout << "Enter user's ID:\n";
                        cin >> usid_member;
                        staf.addMemberShip(usid_member);
                    }
                    else if (ck_stat == 1) {
                        cout << "Sorry! the person is already membership!\n";
                    }
                    else {
                        cout << "Sorry! please Login first!\n";
                    }
                }
                break;

            case 6:

                //Change reserved(Library Staff)
                //check if login
                stat_staf2 = chkStatus(stud);
                if (stat_staf2 == -1) {
                    cout << "Sorry! please Login first!\n";
                }
                else {
                    cout << "Enter book's ID:\n";
                    cin >> bkid;
                    staf.changeReserv(bkid);
                }
                break;

            case 7:

                //Lend book to list(Library Staff)
                //check if login
                if (chkStatus(staf) == -1) {
                    cout << "Sorry! please Login first!\n";
                }
                else {
                    cout << "Please enter book's ID:\n";
                    cin >> b_bid;
                    //check book count
                    num_book = bk.getCount(b_bid);
                    cout << "Promopt:::This book's count just left \t"<<num_book <<"\n";
                    cout << "Please enter number of list of users:\n";
                    cin >> num;
                    if (num <= num_book) {
                        for (int i = 0; i < num; i++) {
                            uid_lend = "";
                            cout << "Please enter the " << i << "e userID list which needs borrow book: \n";
                            cin >> uid_lend;
                            book_list.push_back(uid_lend);
                        }
                        staf.lentBookToList(b_bid, book_list);
                    }
                    else {
                        cout << "the count you entered is greater than left book's count!\n";
                    }
                }

                break;

            default:
                cout << "Invalid input!\n";
                break;
        }
    //}
}


int main()
{
    int ch_role, opt,rtn;
    cout << "******************************* Welcome to Library System *******************************\n";
    cout << "You are :\n1.Student\n2.Library Staff\n3.Supplier\n4.Exit\n";
    
    cin >> ch_role;
    system("cls");
    while (true) {
        switch (ch_role)
        {
        case 1://students
            
            cout << "You want to :\n1.Login\n2.Search book\n3.Apply for membership\n4.Borrow book\n" <<
                "5.Return book\n6.Exit\n";
            cin >> opt;
            if (opt >= 6) {
                stud.resetUserStatus(0);
                exit;
            }
            else{
                option(1, opt);
                break;
            }
        case 2://Library Staff
            cout << "You want to :\n1.Login\n2.Search book\n3.Add book\n4.Modify book's information\n5.Add member\n"
                 <<"6.Change reserved\n7.Lend book to list\n8.Exit\n";
            cin >> opt;
            if (opt >= 8) {
                staf.resetUserStatus(0);
                exit;
            }
            else {
                option(2, opt);
                break;
            }
        case 3://Supplier
            cout << "You want to :\n1.Login\n2.Search book\n3.Sell book\n4.Exit\n";
            cin >> opt;
            if (opt >= 4) {
                supp.resetUserStatus(0);
                exit;
            }
            else {
                option(3, opt);
                break;
            }
        case 4:
            stud.resetUserStatus(0);
            staf.resetUserStatus(0);
            supp.resetUserStatus(0);
            exit;
        default:
            cout << "Invalid input!\n";
            break;
        }
    }



}

