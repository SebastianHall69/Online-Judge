/* 
 * File:   main.cpp
 * Author: Sebastian Hall
 * Created on September 4, 2020, 12:12 AM
 * Purpose: Compare differences between two files, not strict
 */

#include <fstream>
#include <sstream>
using namespace std;

#define RIGHT_ANS 0;
#define WRONG_ARGS 1;
#define WRONG_ANS 2;
#define BAD_FILES 3;
#define INCOMPLETE_ANSWER 4;
#define EXTRA_STUFF 5;
#define FAIL_TO_READ 6;

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
                if(userOutput.eof()) return INCOMPLETE_ANSWER;
                getline(userOutput, userLine);
            }
            
            //Create string streams
            stringstream masterSS(masterLine), userSS(userLine);
            
            //For each type of input in the line
            for(int j = 0; j < params; ++j) {
                //Read type to read in: long long, long double, string
                switch(type[j]) {
                    //Numeric type case
                    case 0: {
                        //Read answer from master and user files
                        triple masterAns = 0.0L, userAns = 0.0L;
                        masterSS>>masterAns;
                        if(!(userSS>>userAns)) return FAIL_TO_READ;
                        
                        //Compare answers, return if bad comparison
                        if(abs(masterAns - userAns) > 1e-6) return WRONG_ANS;
                        break;
                    }
                    //String / character type case
                    case 1: {
                        //Read answer from master and user files
                        string masterAns, userAns;
                        masterSS>>masterAns;
                        if(!(userSS>>userAns)) return FAIL_TO_READ;
                        
                        //Compare answers, return if bad comparison
                        if(userAns.size() != masterAns.size()) return WRONG_ANS;
                        for(int k = 0; k < masterAns.size(); ++k) {
                            if(tolower(masterAns[k]) != tolower(userAns[k])) return WRONG_ANS;
                        }
                        break;
                    }
                }
            }
            
            //Check if user string stream has extra non empty characters, if so WA
            char c;
            if(userSS>>c) return EXTRA_STUFF;
        }
    }
    
    //Check for extra non empty strings in user output
    while(!userOutput.eof()) {
        string userLine = "";
        getline(userOutput, userLine);
        if(userLine.size()) return EXTRA_STUFF;
    }
    
    //A Sebastian Production
    return RIGHT_ANS;
}