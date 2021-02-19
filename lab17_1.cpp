#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    string textString;
    while(getline(file,textString)){
        const char *text = textString.c_str();
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int s1,s2,s3;
        sscanf(text,format,name,&s1,&s2,&s3);
        int sumScore = s1+s2+s3;
        scores.push_back(sumScore);
        names.push_back(name);
        grades.push_back(score2grade(sumScore));
    }
    return;
}

void getCommand(string& command, string& key){
    cout << "Please input your command: ";
    string textString;
    getline(cin,textString);
    const char *text = textString.c_str();
    char format[] = "%[^ ] %[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. ]";
    char commandC[100], keyC[100];
    sscanf(text,format,commandC,keyC);
    command = commandC;
    key = keyC;
    return;
}

void searchName(vector<string>& names, vector<int>& scores, vector<char>& grades, string& key){
    cout << "---------------------------------\n";
    for(unsigned int i = 0 ; i < names.size(); ++i){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "Cannot found." << endl;

    cout << "---------------------------------\n";
}

void searchGrade(vector<string>& names, vector<int>& scores, vector<char>& grades, string& key){

    cout << "---------------------------------\n";

    bool found = false;
    for(unsigned int i = 0 ; i < names.size(); ++i){
        if(grades[i] == key.c_str()[0]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found." << endl;    
    }
    

    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
