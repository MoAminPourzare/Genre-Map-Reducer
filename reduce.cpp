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
#include <sys/wait.h>

#define LENGTH 10000
#define R_FILE "reduce.out"
#define M_FILE "maps.out"

using namespace std;

int main(int argc, char* argv[]) {
    string outputArgv = argv[0];
    int sizeArgv = stoi(argv[1]);
    string nameArgv = argv[2];
    int sum = 0;
    for (int i = 0; i < sizeArgv; i++){
        const char* genre_Reduce = nameArgv.c_str();
        char arrayType[LENGTH];
        mkfifo(genre_Reduce, 0666);
        int fileDescriptor = open(genre_Reduce, O_RDONLY);
        read(fileDescriptor, arrayType, LENGTH);
        string strNumbers = arrayType;
        sum = sum + stoi(strNumbers);
        close(fileDescriptor);
    }
    cout << nameArgv << "  :  " << sum << endl;
    return 0;
}