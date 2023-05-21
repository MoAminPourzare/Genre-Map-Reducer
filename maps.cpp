#include <stdio.h>
#include <dirent.h> 
#include <unistd.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>
#include<sys/wait.h>

#define LENGTH 10000
#define R_FILE "reduce.out"
#define M_FILE "maps.out"

using namespace std;

int main(int argc, char* argv[]) {
    string outputArgv = argv[0];
    string nameOfFileArgv = argv[1];
    string nameOfGenresArgv = argv[2];
    vector <pair<string, int>> numOfAllGenres;
    stringstream ss(nameOfGenresArgv);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        numOfAllGenres.push_back({ substr, 0 });
    }
    vector <vector<string>> genresOfBook;
    vector<string> genres;
    string name = "./library/" + nameOfFileArgv;
    string line, word;
    fstream file (name, ios::in);
    if(file.is_open()) {    
        while(getline(file, line)) {
            genres.clear();
            stringstream str(line); 
            bool check = false;
            while(getline(str, word, ',')) {
                if (check == false){
                  check = true;
                  continue;
                }
                genres.push_back(word);
            }
            genresOfBook.push_back(genres);
        }
    }
    else
        cout<<"Could not open the file\n";

    for(int i = 0; i < numOfAllGenres.size(); i++) {
        for(int j = 0; j < genresOfBook.size(); j++) {
            for(int k = 0; k < genresOfBook[j].size(); k++) {
                if (genresOfBook[j][k] == numOfAllGenres[i].first)
                    numOfAllGenres[i].second++;
            }
        }
    }

    for(int i = 0; i < numOfAllGenres.size(); i++) {
        const char* genre_Reduce = numOfAllGenres[i].first.c_str();
        mkfifo(genre_Reduce, 0666);
        char arrayType[LENGTH];
        strcpy(arrayType, to_string(numOfAllGenres[i].second).c_str());
        int fileDescriptor = open(genre_Reduce, O_WRONLY);
        write(fileDescriptor, arrayType, LENGTH);
        close(fileDescriptor);
    }
    return 0;
}