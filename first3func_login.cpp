// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Text Editor.cpp
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Sara Tamer Bihery - 20210155 - S25
// Author2 and ID and Group: Farah Mohamed Mohamed El-Sayed - 20210288 - S25
// Author3 and ID and Group: Rawnaa Mustafa  - 20210137 - S2
// Teaching Assistant: Mahmoud Fateaha
// Purpose: Edit an existing or new text file.


#include<iostream>
#include<string.h>
#include<fstream>
#include<regex>
#include<cctype>
using namespace std;

void registration();
void enterPassword();

const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
const regex phone("^(2)?(01){1}[0-9]{9}$");
const regex pass("^[0-9]+[a-z_]+[A-Z]+[^0-9a-zA-z_]+$");
int i = 0;
struct user {
    string username;
    string email;
    string password;
    string phone_num;
};
int main(){
    user info[100] ;
    registration();
    enterPassword();
}
void registration() {
    string name, username, email, phone_num;

    cout << "Welcome \n"
            "Enter your email : \n" ;
    cin >> email;

    while (!regex_match(email, pattern)) {
        cout << "Please enter a valid email format.\n";
        cin >> email;
    }
    cout << "Enter your phone number\n";
    cin >> phone_num;
    while (!regex_match(phone_num, phone)) {
        cout << "Please enter a valid phone format.\n";
        cin >> phone_num;
    }

}
void enterPassword(){
    user info[100] = {};
    string confirm;
    cout << "Please enter your password. \n"
            "It must be 8 characters or more and"
            "include letters in upper and lower cases , special characters and digits";
    cin >> info[i].password;

    while (!regex_match(info[i].password, pass) || info[i].password.size() < 8 ) {
        cout << "Please enter a valid password format.\n";
        cin >> info[i].password;
    }
    cout << "Please confirm the password you have entered. \n";
    cin >> confirm;
    while(confirm != info[i].password){
        cout << "Please confirm the password you have entered correctly.\n";
        cin >> confirm;
    }
}
