// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application Description.cpp
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Sara Tamer Bihery - 20210155 - S25
// Author2 and ID and Group: Farah Mohamed Mohamed El-Sayed - 20210288 - S25
// Author3 and ID and Group: Rawnaa Mustafa Hussien - 20210137 - S25
// Teaching Assistant: Mahmoud Fateaha
// Purpose: To register and login


#include<iostream>
#include "Functions.h"

using namespace std;


int main(){

//    The of the options exists
    char choice;
    cout << " +----------------------------------------------------------+\n"
            " +     Welcome, Please choose one option of the following   +\n"
            " +----------------------------------------------------------+\n"
            "1.Registration\n"
            "2.Login\n"
            "3.Change Password\n"
            "4.Exit \n";

    cin >> choice;

    if( choice == '1'){
       registration();
       enterPassword();
       saveInfo();
       cout << "Successful registration! \n";
    }
    else if( choice == '2'){
        login();
    }
    else if( choice == '3'){
       changePW();
    }
    else if( choice == '4'){
        cout << "Good bye ^_^";
    }

}
