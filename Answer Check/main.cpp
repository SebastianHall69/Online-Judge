/* 
 * File:   main.cpp
 * Author: Sebastian Hall
 * Created on September 4, 2020, 12:12 AM
 * Purpose: Compare differences between two files
 */

#include <bits/stdc++.h>
using namespace std;

#define RIGHT_ANS 0;
#define WRONG_ARGS 1;
#define BAD_FILES 2;
#define WRONG_ANS 3;

typedef long long ll;
typedef long double triple;

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    
    //Check if called properly
    if(argc != 3) return WRONG_ARGS;
    
    //Try to open files
    ifstream userOutput(argv[1], ios::in), masterOutput(argv[2], ios::in);
    if(!(userOutput.is_open() && masterOutput.is_open())) return BAD_FILES;
    
    //Compare until reach end of masterOutput file
    while(!masterOutput.eof()) {
        //Declare variables
        int lines = 0, params = 0;
        string format;
        
        //Read format string
        getline(masterOutput, format);
        stringstream ss(format);
        
        //Get lines and parameters from format
        ss>>lines>>params;
        
        //Read formats to read in
        int type[params];
        for(int i = 0; i < params; ++i) ss>>type[i];
        
        //For each line, compare input
        for(int i = 0; i < lines; ++i) {
            string userLine = "", masterLine = "";
            
            //Get solution master output
            getline(masterOutput, masterLine);
            
            //Get next non empty line of user output, check for file that ends too soon
            while(userLine.empty()) {
                if(userOutput.eof()) return WRONG_ANS;
                getline(userOutput, userLine);
            }
            
            //Create string streams
            stringstream masterSS(masterLine), userSS(userLine);
            
            //For each type of input in the line
            for(int j = 0; j < params; ++j) {
                //Read type to read in: long long, long double, string
                switch(type[j]) {
                    case 0: {//Integer type case
                        ll masterAns = 0, userAns = 0;
                        masterSS>>masterAns;
                        if(!(userSS>>userAns)) return WRONG_ANS;
                        if(userAns != masterAns) return WRONG_ANS;
                        break;
                    }
                    case 1: {//Floating point type case
                        triple masterAns = 0.0L, userAns = 0.0L;
                        masterSS>>masterAns;
                        if(!(userSS>>userAns)) return WRONG_ANS;
                        if(abs(masterAns - userAns) > 1e-6) return WRONG_ANS;
                        break;
                    }
                    case 2: {//String / character type case
                        string masterAns, userAns;
                        masterSS>>masterAns;
                        if(!(userSS>>userAns)) return WRONG_ANS;
                        if(userAns != masterAns) return WRONG_ANS;
                        break;
                    }
                }
            }
            
            //Check if user string stream has extra non empty characters, if so WA
            char c;
            if(userSS>>c) return WRONG_ANS;
        }
    }
    
    //Check for extra non empty strings in user output
    while(!userOutput.eof()) {
        string userLine = "";
        getline(userOutput, userLine);
        if(userLine.size()) return WRONG_ANS;
    }
    
    //A Sebastian Production
    return RIGHT_ANS;
}