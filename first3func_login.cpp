// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application Description.cpp
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Sara Tamer Bihery - 20210155 - S25
// Author2 and ID and Group: Farah Mohamed Mohamed El-Sayed - 20210288 - S25
// Author3 and ID and Group: Rawnaa Mustafa  - 20210137 - S2
// Teaching Assistant: Mahmoud Fateaha
// Purpose: To register and login


#include<iostream>
#include<string.h>
#include<fstream>
#include<regex>
#include<cctype>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

void registration();
void enterPassword();
string hidepw();
void saveInfo();
void login();
void changePassword();
bool searchForID(string& word);
bool searchForEmail(string& mail);

const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
const regex phone("^(2)?(01){1}[0-9]{9}$");
const regex pass("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9]})(?=.*[@$!%*?&])[A-Za-z0-9]@$!%*?&]{8,}$");

struct user {
    string username;
    string email;
    string password;
    string encr_Hex = "";
    string phone_num;
    string ID;
} newUser;

int main(){

    char choice;
    cout << " +----------------------------------------------------------+\n"
            " +     Welcome, Please choose one option of the following   +\n"
            " +----------------------------------------------------------+\n"
            "1.Registration\n"
            "2.Login\n"
            "3.Change Password\n"
            "4.Exit";

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
        //changePassword();
    }
    else if( choice == '4'){
        cout << "Good bye ^-^";
    }

}

void registration() {

    cout <<"please enter your personal data\n"
           "User Name: ";
    cin >> newUser.username;

    cout <<"ID : ";
    cin >> newUser.ID;
    while(newUser.ID.size() != 8){
        cout << "Invalid ID.\n"
                "ID: ";
        cin >> newUser.ID;
    }
    bool i = true;
    while (i){
        if (searchForID(newUser.ID)) {
            i = false;
        } else {
            cout << "Invalid ID.\n"
                    "ID: ";
            cin >> newUser.ID;
        }
    }

    cout << "E-Mail: " ;
    cin >> newUser.email;

    while (!regex_match(newUser.email, pattern)) {
        cout << "Please enter a valid email format.\n";
        cout << "E-Mail: ";
        cin >> newUser.email;
    }
    i = true;
    while(i){
        if(searchForEmail(newUser.email)){
            i = false;
        }else{
            cout << "Invalid Email!"
                    "E-mail: ";
            cin >> newUser.email;
        }
    }
    cout << "Phone Number: ";
    cin >> newUser.phone_num;
    while (!regex_match(newUser.phone_num, phone)) {
        cout << "Please enter a valid phone format.\n";
        cout << "Phone Number: ";
        cin >> newUser.phone_num;
    }

}

void enterPassword(){
    
    stringstream res;
    string keyword, confirm;
    bool upper_case = false;
    bool lower_case = false;
    bool number_case = false;
    bool special_char = false;

    regex upper_case_expression{ "[A-Z]+" };
    regex lower_case_expression{ "[a-z]+" };
    regex number_expression{ "[0-9]+" }; //...
    regex special_char_expression{ "[@!?@$#&^*:]+"};
    
    int keyItr = 1;
    bool done = false;

    do{
        cout << "Please enter a valid password:"
                "It must be 8 characters or more and\n"
                "include letters in upper and lower cases , special characters and digits. \n"
                "Password: ";
        newUser.password = hidepw();
        
         for (int i = 0; i < newUser.password.length(); i++){
             
            int temp = newUser.password[i] ^ keyword[keyItr];
            res << hex << setfill('0') << std::setw(2) << (int)temp;
            keyItr++;
             
            if (keyItr >= keyword.length()){
            keyItr = 0;
            }
         }
            res >> newUser.encr_Hex;


        if (newUser.password.length() <= 8){                    //too short!
            cout << "Invalid password! Try again\n";
        }
        else{

            upper_case = regex_search(newUser.password, upper_case_expression);
            lower_case = regex_search(newUser.password, lower_case_expression);
            number_case =regex_search(newUser.password, number_expression);
            special_char = regex_search(newUser.password, special_char_expression);

            int sum_of_positive_results = upper_case + lower_case + number_case + special_char;

            if (sum_of_positive_results < 3){                   //not enough booleans were true!
                cout << "Invalid password! Try again\n";
            }
            else{
                cout << "That's a valid Password!" << endl;
                done = true;
            }
        }

    } while (!done);
    cout << "Please confirm the password you have entered. \n"
            "Confirm password: ";
    confirm = hidepw();
    while(confirm != newUser.password){
        cout << "Please confirm the password you have entered correctly.\n"
                "Confirm password: ";
       confirm = hidepw();
    }
}

string hidepw(){
    char ch;
    string hidden ;
    int s = hidden.size(), j = 0;

    while(true){

        ch = getch();
        if(ch == 13){
            cout << endl;
            break;
        }
        else if(ch >= 32){
            cout << "*";
            hidden += " ";
            hidden[j] = ch;
            ++j;
        }
    }
    if (hidden[s - 1] == ' '){
        hidden.replace(hidden[s - 1] , 1 , "");
    }
    return hidden;
}
void saveInfo(){
    fstream input("information.txt", ios::app);
    input  << "User Name: " << newUser.username<< " | " << "ID: " << newUser.ID << " | " << " E-Mail: " << newUser.email << " | " << " Phone Number: " << newUser.phone_num;
    input  << " | " << " Password: " << newUser.encr_Hex << "\n";
}
bool searchForID(string& word) {
    char text[1000];
    vector<string> lines;
//    int i = 0;
//    while (i < word.size()) {
//        word[i] = tolower(word[i]);
//        i++;
//    }
    fstream InfoFile;
    InfoFile.open("information.txt", fstream::in | fstream::out);
    while (!InfoFile.eof()) {
        InfoFile.getline(text, 1000, '\n');
        lines.push_back(string(text));
    }
    InfoFile.close();

//    for (int i = 0; i < lines.size(); i++) {
//        for (int j = 0; j < lines[i].size(); j++) {
//            lines[i][j] = tolower(lines[i][j]);
//            cout << lines[i][j];
//        }
//    }
    bool k = true;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].find(word) != string::npos) {
            k = false;
            break;
        }
    }
    return k;
}
bool searchForEmail(string& mail){
    char text[1000];
    vector<string> lines;
    int i = 0;
    while (i < mail.size()) {
        mail[i] = tolower(mail[i]);
        i++;
    }
    fstream InfoFile;
    InfoFile.open("information.txt", fstream::in | fstream::out);
    while (!InfoFile.eof()) {
        InfoFile.getline(text, 1000, '\n');
        lines.push_back(string(text));
    }
    InfoFile.close();

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            lines[i][j] = tolower(lines[i][j]);
        }
    }
    bool k = true;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].find(mail) != string::npos) {
            k = false;
            break;
        }
    }
    return k;
}

void login(){

    stringstream res;
    string confirm, keyword;
    int keyItr = 1;
    int CountLogin = 3;

    while( CountLogin > 0){

    cout << "ID: ";
    cin >> newUser.ID;

    cout << "Password: ";
    newUser.password = hidepw();
    for (int i = 0; i < newUser.password.length(); i++){
            int temp = newUser.password[i] ^ keyword[keyItr];
            res << hex << setfill('0') << std::setw(2) << (int)temp;
            keyItr++;
            if (keyItr >= keyword.length()){
            keyItr = 0;
            }
        }
    
       //to cheack if the id or password are not found.
        if (searchForID(newUser.ID) && searchForID(newUser.encr_Hex)) {  
            cout << "Invalid user name and password, please try again \n";
            CountLogin--;
        }
        else if(searchForID(newUser.ID) || searchForID(newUser.encr_Hex)){
            cout << "Invalid user name or password, please try again \n";
            CountLogin--;
        }
        else if(searchForID(newUser.encr_Hex) ||searchForID(newUser.ID)){
            cout << "Invalid user name or password";
            CountLogin--;
            cout << " your denied accses to the system";
        }  
       //if the user name and password are found    
        else {          
            cout << "Successful login.\n";  
            break; 
        }
    }
  
}
