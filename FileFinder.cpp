//
// Created by Rick Lattin on 4/14/21.
//
#include "FileFinder.h"
#include "wordFile.h"
#include <fstream>
#include <sstream>
#include "rapidjson/include/rapidjson/document.h"


FileFinder::FileFinder() {

}

FileFinder::FileFinder(std::string arg) {
    filesArg = arg;
}

void FileFinder::runDirent() {               //parse json functions and fill vectors with appropriate info

    struct dirent *dp;
    const std::string path = filesArg; // as an agr
    DIR *dir = opendir(path.c_str());
    while(dp = readdir(dir)){
        if (dp->d_name[0] == '.') continue;

        if (DEBUG) std::cout << "adding " << dp->d_name << " to vector" << std::endl;

        std::string fullPath;
        fullPath = path + dp->d_name;
        fileNamesTrue.push_back(fullPath);

//        fileNames.push_back(dp->d_name);

    }
    closedir(dir);

//    for(int i = 0; i<fileNames.size(); i++){
//        std::cout<<fileNames[i]<<std::endl;
//    }
    //using: https://stackoverflow.com/questions/25070751/navigating-through-files-using-dirent-h
}

void FileFinder::jsonParser(){               //parse json functions and fill vectors with appropriate info
    int count;
    std::stringstream allBigText;
    std::stringstream allAuth;
    for(int i = 0; i<fileNamesTrue.size(); i++) {
        std::ifstream inFS;
        std::stringstream allBigText;
        std::stringstream allAuth;
        if (DEBUG) std::cout<<"Processing file " << fileNames[i] << std::endl;
        inFS.open(fileNamesTrue[i]);
        count++;
        if(count%100 == 0)
            std::cout<< "File: " << count<<std::endl;
        std::string total;
        while (!inFS.eof()) {
            //std::cout<<"   FileFinder Inner loop"<<std::endl;
            char* line = new char[1000000];
            inFS.getline(line, 1000000);
            std::string strLine;
            strLine += line;
            total = total + strLine;
            delete[] line;
        }
        rapidjson::Document document;
        document.Parse(total.c_str());

        if(document.IsObject()) {
            assert(document.IsObject());

            assert(document.HasMember("paper_id"));
            assert(document["paper_id"].IsString());
            fileNames.push_back(document["paper_id"].GetString());

            assert(document.HasMember("abstract"));
            assert(document["abstract"].IsArray());
            for (const auto &line : document["abstract"].GetArray()) {
                std::string addition = line["text"].GetString();
                addition += " ";
//            allImportantText += addition;
                allBigText << addition;
            }

            assert(document.HasMember("metadata"));
            assert(document["metadata"].IsObject());
            std::string addition = document["metadata"]["title"].GetString();
            addition += " ";
//        allImportantText += addition;
            allBigText << addition;

            assert(document.HasMember("body_text"));
            assert(document["body_text"].IsArray());
            for (const auto &line : document["body_text"].GetArray()) {
                std::string addition = line["text"].GetString();
                addition += " ";
//            allImportantText += addition;
                allBigText << addition;
            };

            assert(document.HasMember("metadata"));
            assert(document["metadata"].IsObject());
            for (const auto &line : document["metadata"]["authors"].GetArray()) {
                std::string addition = line["last"].GetString();
                addition += " ";
//            allAuthors += addition;
                allAuth << addition;
            }


            int strLoc = 0;
            std::string oneWord;
            allImportantText = allBigText.str();
            while (strLoc < allImportantText.size()) {
                std::string curLetter;
                curLetter += allImportantText[strLoc];
                if (curLetter == " ") {   //add word to map and clear
//                if(oneWord.size() > 2) {
                    wordFile entry;
                    entry.setKey(oneWord);
                    entry.setLoc(fileNames[i]);
                    fileWords.push_back(entry);
                    oneWord = "";
                } else        //add one letter to the word
                    oneWord += curLetter;           //changed to plus/equals
                strLoc++;
            }

            int authStrLoc = 0;
            std::string authOneWord;
            allAuthors = allAuth.str();
            while (authStrLoc < allAuthors.size()) {
                std::string authCurLetter;
                authCurLetter += allAuthors[authStrLoc];
                if (authCurLetter == " ") {   //add word to map and clear
//                if(oneWord.size() > 2) {
                    wordFile entry;
                    entry.setKey(authOneWord);
                    entry.setLoc(fileNames[i]);
                    fileAuthors.push_back(entry);
                    authOneWord = "";
                } else        //add one letter to the word
                    authOneWord += authCurLetter;           //changed to plus/equals
                authStrLoc++;
            }
        }
        inFS.close();
    }
    std::cout<<"Finished Parsing"<<std::endl;
    filesParsed = count;

//    for(int i = 0; i<fileNames.size(); i++){
//        std::cout<<fileNames[i]<<std::endl;
//    }
}

std::vector<wordFile>& FileFinder::getFileWords() {
    return fileWords;
}

std::vector<wordFile>& FileFinder::getFileAuthors() {
    return fileAuthors;
}

int FileFinder::getFilesParsed(){
    return filesParsed;
}