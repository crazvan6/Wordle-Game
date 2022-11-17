#include <iostream>
#include <string.h>
#include <vector>
#include <windows.h>
#include <fstream>
#include <time.h>
using namespace std;

ifstream f("words.in");

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);    // pentru culori

void word_verifier(string correct_word, string guess_word, bool &verif){
    char state[6] = {'_', '_', '_', '_', '_'};        // starea fiecarei litere din cuvantul introdus
    int used[6] = {0,0,0,0,0};
    for(int i = 0; i < 5; ++i){
        if(correct_word[i] == guess_word[i]){         // verific daca am litere care deja se potrivesc pe aceeasi pozitie in cele 2 cuvinte
            state[i] = 'G';
            used[i] = 1;
        }
    }
    
    for(int i = 0; i < 5; ++i){
        bool ok = false;
        if(state[i] == '_'){                            //verific starea literei de pe pozitia "i"
            for(int j = 0; j < 5; ++j){
                if(correct_word[j] == guess_word[i]){   //caut aparitii ale literei in cuvantul corect
                    if(used[j] == 0){                   //daca pozitia nu e marcata, inseamna ca pot contoriza litera drept una care apare
                        state[i] = 'Y';
                        ok = true;
                        used[j] = 1;
                        break;
                    }
                    else{                               //pozitia e marcata, deci nu sunt folosite atat de multe litere de tip guess_word[i] in cuvantul corect
                        ok = true;
                        state[i] = 'N';
                    }
                } 
                if(ok == false) state[i] = 'R';
            }           
        }
    }
    int cnt = 0;
    for(int i = 0; i < 5; ++i){
        if(state[i] == 'G'){
            SetConsoleTextAttribute(h, 10);     //setez culoarea verde
            cout << guess_word[i], Sleep(60);
            cnt++;
            }
        else if(state[i] == 'Y'){           
            SetConsoleTextAttribute(h, 14);     //setez culoarea galbena la afisare
            cout << guess_word[i], Sleep(60);
        }
        else if(state[i] == 'R'){
            SetConsoleTextAttribute(h, 12);     //setez culoarea rosie   [...]
            cout << guess_word[i], Sleep(60);
        }
        else{
            SetConsoleTextAttribute(h, 8);     //sstez culoarea gri la afisare
            cout << guess_word[i], Sleep(60);
        }
    }
    SetConsoleTextAttribute(h, 7);              // setez culoarea default
    if(cnt == 5){                              // verific daca toate literele se potrivesc
        verif = true;
    }
}
void screen1(){
    cout << '\n';
    string str1 = "Introdu un cuvant: ";
    for(char c : str1){
        cout << c, Sleep(60);
    }
}
void screen2(){
    cout << '\n';
    string str2 = "Ai ghicit!";
    for(char c : str2){
        cout << c, Sleep(60);
    }
}
void screen3(){
    cout << '\n';
    string str3 = "Mai incearca: ";
    for(char c : str3){
        cout << c, Sleep(60);
    }
}
void screen4(string ans){
    cout << '\n';
    string str4 = "Cuvantul era: ";
    for(char c : str4){
        cout << c, Sleep(60);
    }
    SetConsoleTextAttribute(h,10);
    for(char c :ans){
        cout << c, Sleep(60);
    }
}
int main(){
    vector <string > lines;
    string line;
    srand(time(0));
    int total_lines = 0;
    while(getline(f, line)){
        total_lines++;
        lines.push_back(line);
    }
    int random_number = rand()%total_lines;
    string word = lines[random_number];
    string ex;
    bool solved = false;
    screen1();
    while(solved == false){
        cin >> ex;
        if(ex == "SURRENDER"){
                screen4(word);
                break;
            }
        else{
            word_verifier(word, ex, solved);
            if(solved) screen2();
            else screen3();
        }
    }
    return 0;
}
