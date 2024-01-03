//
// Created by Rick Lattin on 4/19/21.
//

#ifndef SEARCH_ENGINE_WORDFILE_H
#define SEARCH_ENGINE_WORDFILE_H
#include <iostream>

class wordFile{
    private:
        std::string key;        //word
        std::string loc;        //articles word appears in
    public:
        wordFile();
        wordFile(std::string, std::string);      //goes word then loc
        std::string getKey();
        std::string getLoc();
        void setKey(std::string);
        void setLoc(std::string);
};

#endif //SEARCH_ENGINE_WORDFILE_H
