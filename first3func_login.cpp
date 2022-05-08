#include<iostream>
#include<string.h>
#include<fstream>
#include<regex>
#include<cctype>
using namespace std;
const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

const regex phone("^(2)?(01){1}[0-9]{9}$");

void registration();

int main(){
    registration();

}
void registration() {
    string name, username, email, phone_num;

    cout << "Enter your email :";
    cin >> email;

    while (!regex_match(email, pattern)) {
        cout << "Please enter a valid email format.";
        cin >> email;
    }
    cout << "enter your phone num";
    cin >> phone_num;
    while (!regex_match(phone_num, phone)) {
        cout << "Please enter a valid email format.";
        cin >> phone_num;
    }



}