#ifndef _Function_
#define _Function_

#include "Inclue.hpp"

vector<string> BreakString(string str, char sep = ' ')
{
    istringstream ss(str);
    string word;
    vector<string> words;

    while (getline(ss, word, sep)) 
        words.push_back(word);
    return words;
}


bool IsDigit(string str){
    for(int i = 0 ; i < str.length() ; i++){
        if ( (str[i] != '0') && (!isdigit(str[i])) )
            return false;
    }
    return true;
}
   

#endif