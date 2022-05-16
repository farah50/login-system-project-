#include<iostream>
#include<fstream>
#include<regex>
#include<cctype>
#include <conio.h>
#include <iomanip>
#include "Functions.h"


using namespace std;
//global variable of the structure
user newUser;

//function to the register of the user
void registration() {

    cout <<"please enter your personal data\n"
           "User Name: ";
    cin >> newUser.username;                        //get the username

    cout <<"ID : ";
    cin >> newUser.ID;                              //get the ID
    while(newUser.ID.size() != 8){                  //check the ID is valid (not used before)
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

    cout << "E-Mail: " ;                            // get the email
    cin >> newUser.email;

    while (!regex_match(newUser.email, pattern)) {      // check that it match the pattern of the emails
        cout << "Please enter a valid email format.\n";
        cout << "E-Mail: ";
        cin >> newUser.email;
    }
    i = true;
    while(i){                                           // check it's not used before
        if(searchForEmail(newUser.email)){
            i = false;
        }else{
            cout << "Invalid Email!"
                    "E-mail: ";
            cin >> newUser.email;
        }
    }
    cout << "Phone Number: ";
    cin >> newUser.phone_num;                               // get the phone number
    while (!regex_match(newUser.phone_num, phone)) {    // check it's valid number
        cout << "Please enter a valid phone format.\n";
        cout << "Phone Number: ";
        cin >> newUser.phone_num;
    }

}
// Function to get the strong password and encrypt it
void enterPassword(){

    stringstream res;
    string keyword, confirm;

    // to check its strong password using regex

    bool upper_case = false;
    bool lower_case = false;
    bool number_case = false;
    bool special_char = false;

    regex upper_case_expression{ "[A-Z]+" };            //check presence of upper characters
    regex lower_case_expression{ "[a-z]+" };            //check presence of lower characters
    regex number_expression{ "[0-9]+" }; //...          //check the presence of digits
    regex special_char_expression{ "[@!?@$#&^*:]+"};        //check the presence of special characters

    int keyItr = 1;
    bool done = false;

    do{
        cout << "Please enter a valid password:"
                "It must be 8 characters or more and\n"
                "include letters in upper and lower cases , special characters and digits. \n"
                "Password: ";
        newUser.password = hidepw();                            //get the password and hide it with **

        for (int i = 0; i < newUser.password.length(); i++){            //to encrypt the password

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

            if (sum_of_positive_results < 3){                   //not enough booleans were true! ,therefore not strong
                cout << "Invalid password! Try again\n";
            }
            else{
                cout << "That's a valid Password!" << endl;
                done = true;
            }
        }

    } while (!done);                                    // to confirm the password and hide it with **
    cout << "Please confirm the password you have entered. \n"
            "Confirm password: ";
    confirm = hidepw();
    while(confirm != newUser.password){                 // check it's the password entered first
        cout << "Please confirm the password you have entered correctly.\n"
                "Confirm password: ";
        confirm = hidepw();
    }
}
// Function to hide the password with ** while the user entering it and return the password
string hidepw(){
    char ch;
    string hidden ;
    int s = hidden.size(), j = 0;

    while(true){                // loop to get the password and hide it

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
//function to save information in our file just after the password is confirmed
void saveInfo(){
    fstream input("information.txt", ios::app);
    input  << "User Name: " << newUser.username<< " | " << "ID: " << newUser.ID << " | " << " E-Mail: " << newUser.email << " | " << " Phone Number: " << newUser.phone_num;
    input  << " | " << " Password: " << newUser.encr_Hex << "\n";
}
//function to search for the ID when the user want to login and return the validty of loging in
bool searchForID(string& word) {
    char text[1000];
    vector<string> lines;

    fstream InfoFile;
    InfoFile.open("information.txt", fstream::in | fstream::out);
    while (!InfoFile.eof()) {
        InfoFile.getline(text, 1000, '\n');
        lines.push_back(string(text));
    }
    InfoFile.close();

    bool k = true;
    for (int i = 0; i < lines.size(); i++) {                    //check if the ID is not exist
        if (lines[i].find(word) != string::npos) {
            k = false;
            break;
        }
    }
    return k;
}
//function to search for the email to check the validity while registering
bool searchForEmail(string& mail){
    char text[1000];
    vector<string> lines;
    int i = 0;
    while (i < mail.size()) {                       //change the email entered to lower
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

    for (int i = 0; i < lines.size(); i++) {                //change the file content to lower
        for (int j = 0; j < lines[i].size(); j++) {
            lines[i][j] = tolower(lines[i][j]);
        }
    }
    bool k = true;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].find(mail) != string::npos) {      //check if the email used before
            k = false;
            break;
        }
    }
    return k;
}
// function to login to the app after register
void login(){

    stringstream res ,line, name ;
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
            ifstream myfile("information.txt");

//            myfile.open("information.txt", ios::in | ios::out );

            while(!myfile.fail() && !myfile.eof()){
                if(!myfile.eof()){
                    while(getline(myfile,line)){
                        int found = 0;
                        if(line.find(newUser.ID ) !=  string::npos){

                            if(line.find("User Name: ") !=  string::npos ){
                                found = line.find("User Name: ") + 11;

                                while(line[found] != ' '){
                                    name += line[found];
                                    found ++;
                                }
                                cout << "Successful login, welcome " << name;
                            }
                        }

                    }
                }
            }
            break;
        }
    }
}

// Function to change password
void changePW(){
    stringstream res;
    int keyItr = 1;
    string keyword;
    char text[1000];
    vector<string> lines;
    string oldP, newPW_encr;

    login();                        // the user must login first

    cout <<"The old password:  ";
    cin >> oldP;                    // get the old password
    hidepw();
    while(true){                    // check if it matches the old password
        if(oldP == newUser.password){
            enterPassword();            // call the function that enter the password
            break;
        }
        else{
            cout << "Wrong old password! \n"
                    "Old Password : ";
            cin >> oldP;
            hidepw();
        }
    }
    newPW_encr = newUser.encr_Hex;
    for (int i = 0; i < oldP.length(); i++){                //encrypt the password

        int temp = oldP[i] ^ keyword[keyItr];
        res << hex << setfill('0') << std::setw(2) << (int)temp;
        keyItr++;

        if (keyItr >= keyword.length()){
            keyItr = 0;
        }
    }
    res >> newUser.encr_Hex;

    fstream InfoFile;
    InfoFile.open("information.txt", fstream::in | fstream::out);       //load the file content in vector of strings
    while (!InfoFile.eof()) {
        InfoFile.getline(text, 1000, '\n');
        lines.push_back(string(text));
    }

    InfoFile.close();
    InfoFile.open("information.txt", fstream::out);                 // empty the old file content
    InfoFile.close();
    InfoFile.open("information.txt", fstream::app);                 // open the file in the append mode
    for (int i = 0; i < lines.size(); i++){                                 // access the old password and change it with the new one
        if (lines[i] == newUser.encr_Hex){
            lines[i] = newPW_encr;
        }
        InfoFile << lines[i];                                               //fill the file again after changing the password
    }
    InfoFile.close();
}
