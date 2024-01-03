//
// Created by Rick Lattin on 4/14/21.
//

#ifndef SEARCH_ENGINE_FILEFINDER_H
#define SEARCH_ENGINE_FILEFINDER_H
//#include "DSVector.h"
#include <vector>
#include <dirent.h>
#include <map>
#include "wordFile.h"

#define DEBUG false

class FileFinder{
    private:
        std::vector<std::string> fileNames;
        std::vector<std::string> fileNamesTrue;
        std::vector<wordFile> fileWords;
        std::vector<wordFile> fileAuthors;
        std::string filesArg;
        std::string allImportantText = "";
        std::string allAuthors = "";
        int filesParsed;
    public:
        FileFinder();
        FileFinder(std::string);
        void runDirent();               //these two functions parse json functions and fill vectors with appropriate info
        void jsonParser();
        std::vector<wordFile>& getFileWords();
        std::vector<wordFile>& getFileAuthors();
        int getFilesParsed();
};


#endif //SEARCH_ENGINE_FILEFINDER_H
