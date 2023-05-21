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
#define NUM_OF_FILE 12
#define R_FILE "reduce.out"
#define M_FILE "maps.out"

using namespace std;

vector<string> getNameOfFiles(string library) {
    DIR *dp;
    int i = 0;
    struct dirent *ep;     
    dp = opendir ("./library");
    if (dp != NULL) {
        while (ep = readdir (dp))
            i++;
        (void) closedir (dp);
    }
    else
        perror ("Couldn't open the directory");
    vector<string> nameOfFiles;
    for(int j = 1; j < i - 2; j++)
        nameOfFiles.push_back("part" + to_string(j) + ".csv");
    return nameOfFiles;
}

string getNameOfGenres(string library) {
    string name = "./" + library + "/genres.csv";
    ifstream inp(name);
    string line;
    getline(inp,line);
    stringstream lineStream(line);
    string str;
    getline(lineStream, str, '\n');
    return str;
}

int main(int argc, char* argv[]){
    string library = argv[1];
    string reduce = R_FILE;
    string map = M_FILE;
    vector<string> nameOfFiles;
    nameOfFiles = getNameOfFiles(library);
    vector<string> nameOfGenres;
    string nameOfGenresStr;
    nameOfGenresStr = getNameOfGenres(library);
    stringstream str1(nameOfGenresStr);
    while (str1.good()) {
        string substr;
        getline(str1, substr, ',');
        nameOfGenres.push_back(substr);
    }
    int fdG[NUM_OF_FILE][2];
    int pidG[NUM_OF_FILE];
    int fdF[NUM_OF_FILE][2];
    int pidF[NUM_OF_FILE];
    for(int i = 0; i < nameOfGenres.size(); i++) {
        pipe(fdG[i]);
        pidG[i] = fork();
        if (pidG[i] == 0){
            close(fdG[i][0]);
            string sizeArgv = to_string(nameOfFiles.size());
            string fdArgv = to_string(fdG[i][1]);
            string nameArgv = nameOfGenres[i];
            char* argv_list[] = {(char*)reduce.c_str(), (char*)sizeArgv.c_str(), (char*)nameArgv.c_str(), NULL};
            execv(argv_list[0], argv_list); 
            close(fdG[i][1]);
        }
    }
    for(int i = 0; i < nameOfFiles.size(); i++) {
        pipe(fdF[i]);
        pidF[i] = fork();
        if (pidF[i] > 0) {
            close(fdF[i][0]);
            char arrayType[LENGTH];
            strcpy(arrayType, nameOfFiles[i].c_str());
            write(fdF[i][1], arrayType, LENGTH);
            close(fdF[i][1]);
        }
        else {
            close(fdF[i][1]);
            char arrayType[LENGTH];
            read(fdF[i][0], arrayType, LENGTH);
            string nameOfFile = arrayType;
            close(fdF[i][0]);
            char* argv_list[] = {(char*)map.c_str(), (char*)nameOfFile.c_str(), (char*)nameOfGenresStr.c_str(), NULL};    
            execv(argv_list[0], argv_list); 
        }
    }
    int status;
    while(wait(&status) > 0)
    return 0;
}