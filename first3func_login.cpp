#include <fstream>
#include <iostream>
#include <vector>
#include "MyHeaderFile.h"

using namespace std;

int choice;
fstream myFile;
fstream myFile2;
fstream targetFile;
vector<string> lines;
vector<string> lines2;
vector<string> wordvector;
vector<char> inside;
char text[100] , text2[100], name[100], text0 , name2[100];
string readWord, userWord, targetFileName , name_file;


//function that display the menu to the user
int menuDisplay() {

    cout << "\n Please choose one option of the following: \n"
            "1. Add new text to the end of the file \n"
            "2. Display the content of the file\n"
            "3. Empty the file\n"
            "4. Encrypt the file content \n"
            "5. Decrypt the file content\n"
            "6. Merge another file\n"
            "7. Count the number of words in the file.\n"
            "8. Count the number of characters in the file\n"
            "9. Count the number of lines in the file\n"
            "10. Search for a word in the file\n"
            "11. Count the number of times a word exists in the file\n"
            "12. Turn the file content to upper case.\n"
            "13. Turn the file content to lower case.\n"
            "14. Turn file content to 1st caps (1st char of each word is capital) \n"
            "15. Save\n"
            "16. Exit\n";
    cin >> choice;
    return choice;
}
//function that load the file into vector and array of characters
void loadFile(vector<string>& lines,fstream& myFile){
    cout << "Please enter the file name : \n";
    cin >> name;
    myFile.open(name , fstream::in | fstream::out);

    if (myFile){
        cout << "The file has opened successfully \n";
        while (!myFile.eof()){
            myFile.getline(text , 100 , '\n');
            lines.push_back(string(text));
        }
    }
    else {
        cout << "This file couldn't open.\n "
                "Another file will be created when saving \n";
    }
}
//function to load the second file in case of merge or some other cases
void loadFile2(vector<string>& lines2,fstream& myFile2){
    cout << "Please enter the name of the other file : \n";
    cin >> name2;
    myFile2.open(name2 , fstream::in | fstream::out);

    if (myFile2){
        cout << "The file has opened successfully \n";
        while (!myFile2.eof()){
            myFile2.getline(text2 , 100 , '\n');
            lines2.push_back(string(text2));
        }
    }
    else {
        cout << "This file couldn't open.\n "
                "Another file will be created when saving \n";
    }
}
//function to count the characters inside the file
void countChar(){
    long counter = 0 ;
    for(int i = 0 ; i < lines.size(); i ++){            //loop on each vector of strings and access the characters and count it
        for(int j = 0 ; j < lines[i].size() ; j++){
            counter ++;
        }
    }
    cout << "The number of characters in the file = " << counter << endl;
}
//function to count the words inside the file
void countWords(){
    long counter = 0 ;
    for(int i = 0 ; i < lines.size(); i ++){            //loop on the vector of strings and access the words and count it
        for(int j = 0 ; j < lines[i].size() ; j++){
            if(lines[i][j] == ' '){
                counter ++;
            }
        }
        counter ++;
    }
    cout << "The number of words in the file = " << counter  << endl;
}
//function to merge two files in  the first file
void mergeFile(){
//    close the files after loading it
    myFile2.close();
    myFile.close();
    myFile.open(name , ios::app);                           //open the 1st file in the append mode
    myFile2.open(name2 ,  fstream::in | fstream::out );     //open the 2nd file in the in mode
    myFile << "\n";
    while(!myFile2.eof()) {                         //loop on the second file and append its content into the first one
        myFile2 >> text2;
        myFile << " ";
        myFile << text2;
    }
    myFile.close();
    myFile2.close();
    cout << "The files merged successfully.\n" ;
}
//function to search for word and check its existence in the file
void searchForWord() {
    string word ;
    cout << "Please enter the word you want to search for. \n";
    cin >> word;                                                    // get the word the user want to check
    //convert the word to the lower case
    int i = 0;
    while(i < word.size()){
        word[i] = tolower(word[i]);
        i ++;
    }
//    close the file then open it in the mode of in
    myFile.close();
    myFile.open(name , fstream::in | fstream::out);
    while (!myFile.eof()){
        myFile.getline(text , 100 , '\n');
        lines.push_back(string(text));
    }
//    convert the text of the file into the lower case before checking
    for(int i = 0 ; i < lines.size(); i ++) {
        for (int j = 0; j < lines[i].size(); j++) {
            lines[i][j] = tolower(lines[i][j]);
        }
    }
//    check the presence of the word inside the file
    bool k = true;
    for(int i = 0 ; i < lines.size(); i ++) {
        if (lines[i].find(word) != string::npos) {
            cout << "Word was found in the file. \n";
            k = false;
            break;
        }
    }
    if(k){
        cout << "Word was not found in the file. \n";
    }
}
//function to change the file content into the upper case
void TurnToUpper(){


    cout << "Please enter the file name : ";
    cin >> name;

    cout << "Please enter the target file name: ";
    cin >> targetFileName;

    myFile.open(name,ios::in);
    targetFile.open(targetFileName, ios::out);

    if(myFile){
        while(myFile.get(text0)){                   //loop on the file and change the characters into the upper case

            inside.push_back(toupper(text0));

            for(int i=0 ; i<inside.size()-1 ; ++i){
                targetFile.put(inside[i]);
            }
        }
        myFile.close();
        targetFile.close();
        cout << "The file turned to uppercase successfully\n";
    }
    else{
        cout << " Can't open file.";
    }

}
//function to change the file content into the lower case
void TurnToLower(){

    cout << "Please enter the file name : ";
    cin >> name;

    cout << "Please enter the target file name: ";
    cin >> targetFileName;

    myFile.open(name,ios::in);
    targetFile.open(targetFileName, ios::out);

    if(myFile){
        while(myFile.get(text0)){                       //loop on the file characters and change it into lower case

            inside.push_back(toupper(text0));

            for(int i=0 ; i < inside.size()-1 ; ++i){
                targetFile.put(inside[i]);
            }
        }
        myFile.close();
        targetFile.close();
        cout << "The file turned to uppercase successfully\n";
    }
    else{
        cout << " Can't open file.";
    }

}
//function to search for word and count the number of times it repeated into the file
void FreqWord(){

    cout << "Please enter the file name : ";
    cin >> name;                                    // get the file name from the user

    myFile.open(name,ios::in);

    while(myFile >> readWord){

        wordvector.push_back(readWord);                //load the file content
    }

    while(true){                                    //infinite loop to count the word repetition

        int counter = 0;

        cout <<"Please enter the word you want to check occurrences of: ";
        cin >> userWord;                            //get the word the user want count its frequency

        for(int i = 0; i < wordvector.size(); i++){

            if( userWord == wordvector[i]){
                counter++;
            }

        }
        cout <<"The word " << userWord << " was found: " << counter << " times" << endl;
        break;
    }
}
//function to change the first character of each word into upper case
void firstUpper(){

    bool newSentence = true;

    cout << "Please enter the file name: " ;
    cin >> name;

    cout << "Please enter the target file name: " ;
    cin >> targetFileName;

    targetFile.open(targetFileName, ios::out);
    myFile.open(name, ios::in);

    if (myFile) {
        while (myFile.get(text0)) {
            if (text0 == ' ') {        // To check if there is a space or not
                newSentence = true;
            }
            if (isalpha(text0)) {
                if (newSentence) {
                    text0 = toupper(text0);
                    newSentence = false;   //To make the other letter of the word lowercase
                }
                else {
                    text0= tolower(text0);
                }
            }
            targetFile.put(text0);
        }
        myFile.close();
        targetFile.close();
    }
    else {
        cout << "Cannot open file(s)." << endl;
    }

    cout << "\nFile conversion successfully." << endl;

}
//function to add text to the file
void add_text (){
    string name_file;
    cout << "enter the name of file you want to add text to: \n";
    cin >> name_file;

    fstream myFile(name_file.c_str(), ios::app);    // open the file in the mood of append

    string line;
    cout << "Enter the text you want to add. \n";
    cin.get();
    getline(cin, line);                             // get the text the user want to append

    if (!cin.eof()) {
        myFile << line << '\n';                             //add the text to the file
    }

    myFile.close();

    cin.clear();
}
//function to empty the file
void empty_file(string& name_file) {

    fstream myFile(name_file.c_str(), ios::out);

    myFile.close();

}
//function to display or print the file content
void displayContent() {
    string name_file;
    cout << "enter the name of file you want to display: \n";
    cin >> name_file;

    fstream file(name_file.c_str(), ios::in);

    char str[10000];

    while (file.getline(str, 10000)) {
        cout << str << endl;
    }
    file.close();

}
//function to encrypt the file content
void encryption() {
    cout<<"enter the name of file you want to encrypt. \n";
    cin >> name_file;
    fstream myFile(name_file, ios::in );
    string file_content = "";
    string encrypt="";
    char line[1000];

    while (myFile.getline(line, 1000, '\n')) {
        file_content += line ;                              //load the file into string
        file_content += '\n';
    }
    myFile.close();
    myFile.open(name_file,  ios::out);              //empty the file
    char c;
    for (int i = 0 ; i < file_content.size(); i++){
        if(file_content[i] == '\n'){                        //keep the new lines in its position
            c = '\n';
            encrypt +=c;
        }
        else{
            c = file_content[i] + 1;              //encrypt the characters by changing them to the following char in ASCII
            encrypt +=c;
        }
    }
    myFile << encrypt;                          //put the encrypted string into the file
    myFile.close();
}
//function to decrypt the file content
void decryption(){
    string name_file;
    cout<<"enter the name of file you want to decrypt\n";
    cin >> name_file;
    fstream myFile(name_file, ios::in );
    string file_content = "";
    string decrypt="";
    char line[1000];

    while (myFile.getline(line, 1000, '\n')) {
        file_content += line ;                              //load the file content into string
        file_content += '\n';
    }
    myFile.close();
    myFile.open(name_file,  ios::out);              // empty the file

    char c;
    for (int i = 0 ; i < file_content.size(); i++){
        if(file_content[i] == '\n'){                        // keep the new lines in its position
            c = '\n';
            decrypt += c;

        }
        else{
            c = file_content[i] - 1;                  //decrypt the characters by return them to the previous char in ASCII
            decrypt += c;
        }
    }
    myFile << decrypt;                              //put the decrypted content in the file
    myFile.close();
}

