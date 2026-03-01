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
    for(unsigned i = 0; i < x.size(); i++)
        y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names,
                        vector<int>& scores, vector<char>& grades){

    ifstream fin(filename.c_str());
    string line;

    while(getline(fin, line)){
        size_t pos = line.find(':');
        if(pos == string::npos) continue;

        string name = line.substr(0, pos);
        string rest = line.substr(pos + 1);

        int a, b, c;
        sscanf(rest.c_str(), "%d %d %d", &a, &b, &c);

        int sum = a + b + c;

        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
    fin.close();
}

void getCommand(string& command, string& key){
    cout << "Please input your command:\n";
    cin >> command;

    if(command == "exit" || command == "EXIT"){
        key = "";
        return;
    }

    getline(cin, key);
    if(key.size() > 0 && key[0] == ' ')
        key.erase(0,1);
}

void searchName(vector<string>& names, vector<int>& scores,
                vector<char>& grades, string key){

    bool found = false;
    cout << "---------------------------------\n";

    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
            break;
        }
    }

    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string>& names, vector<int>& scores,
                 vector<char>& grades, string key){

    bool found = false;
    char g = key[0];

    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        if(grades[i] == g){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }

    if(!found){
        cout << "Cannot found.\n";
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