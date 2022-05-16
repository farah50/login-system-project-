#ifndef UNTITLED8_FUNCTIONS_H
#define UNTITLED8_FUNCTIONS_H

#include<iostream>
#include<fstream>
#include<regex>
#include<cctype>
#include <conio.h>
#include <iomanip>

using namespace std;
// all functions created in the project
void registration();
void enterPassword();
string hidepw();
void saveInfo();
void login();
bool searchForID(string& word);
bool searchForEmail(string& mail);
void changePW();

//the global variables, regex used

const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
const regex phone("^(2)?(01){1}[0-9]{9}$");

//the structure of the user information
struct user {
    string username;
    string email;
    string password;
    string encr_Hex;
    string phone_num;
    string ID;
};

#endif //UNTITLED8_FUNCTIONS_H
