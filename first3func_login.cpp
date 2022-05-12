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
#include <conio.h>

using namespace std;

void registration();
void enterPassword();
string hidepw();

const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
const regex phone("^(2)?(01){1}[0-9]{9}$");
const regex pass("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9]})(?=.*[@$!%*?&])[A-Za-z0-9]@$!%*?&]{8,}$");
int i = 0;

struct user {
    string username;
    string email;
    string password;
    string phone_num;
    long ID;
} newUser;

int main(){
//    registration();
    enterPassword();
}

void registration() {
    
    string name, username, email, phone_num;
    fstream input("information.txt", ios::app);
    
    cout << "Welcome \n"
            " Please enter your personal data\n" ;

    cout << "Name: ";
    cin >> name;
    
    cout << "User Name: ";
    cin >> username;
    
    cout << "E-Mail: " ;
    cin >> email;

    while (!regex_match(email, pattern)) {
        cout << "Please enter a valid email format.\n";
        cout << "E-Mail: ";
        cin >> email;
    }
    cout << "Phone Number: ";
    cin >> phone_num;
    while (!regex_match(phone_num, phone)) {
        cout << "Please enter a valid phone format.\n";
        cout << "Phone Number: ";
        cin >> phone_num;
    }
input << "Name: " << name << " | " << " User Name: " << username<< " | " << " E-Mail: " << email << " | " << " Phone Number: " << phone_num; 
}

void enterPassword(){
    
    fstream input("information.txt", ios::app);
    string confirm;
    bool upper_case = false;
    bool lower_case = false;
    bool number_case = false;
    bool special_char = false;


    regex upper_case_expression{ "[A-Z]+" };
    regex lower_case_expression{ "[a-z]+" };
    regex number_expression{ "[0-9]+" }; //...
    regex special_char_expression{ "[@!?@$#&^*:]+"};



    bool done = false;

    do{
        cout << "Please enter a valid password:"
                     "It must be 8 characters or more and\n"
                     "include letters in upper and lower cases , special characters and digits. \n"
                     "Password: ";
        newUser.password = hidepw();


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
    cin >> confirm;
    while(confirm != newUser.password){
        cout << "Please confirm the password you have entered correctly.\n"
                "Confirm password: ";
        cin >> confirm;
    }
  input  << " | " << " Password: " << newUser.password << '\n';
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

