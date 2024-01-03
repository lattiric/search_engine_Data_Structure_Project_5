//
// Created by Rick Lattin on 5/1/21.
//
#include "QueryPro.h"
#include "porter2_stemmer/porter2_stemmer.h"

QueryPro::QueryPro(){

}

QueryPro::QueryPro(AVLTree& tr, HashTable<std::string, std::string>& hs){
    tree = &tr;
    hash = &hs;
}

void QueryPro::getUserInput(){
    std::cout<<"Enter Search Query: ";
    char* queryEntry = new char[10000];
    std::cin.getline(queryEntry, 10000);
    std::string userEntry =+ queryEntry;
    userEntry = userEntry+" ";
    std::cout<<std::endl;
    delete[] queryEntry;

    std::string pushWord = "";
    for(int i = 0; i<userEntry.size(); i++){
        if(userEntry[i] == ' ') {
            allInWords.push_back(pushWord);
            pushWord = "";
        }
        else
            pushWord = pushWord + userEntry[i];
    }

    std::string wordOne = correctWord(allInWords[0]);
    if(wordOne == "and")
        andOr = "and";
    else if(wordOne == "or")
        andOr = "or";

    for(int x = 0; x<allInWords.size(); x++){
        if(correctWord(allInWords[x]) == "not") {
            notWord = allInWords[x + 1];
            Porter2Stemmer::stem(notWord);
            notIndex = x;
        }
        if(correctWord(allInWords[x]) == "author") {
            authorWord = allInWords[x + 1];
            Porter2Stemmer::stem(authorWord);
            authorIndex = x;
        }
    }

    int searchWordLength;
    if(authorIndex != -1 && notIndex != -1)
        searchWordLength = std::min(authorIndex, notIndex);
    else if(authorIndex != -1)
        searchWordLength = authorIndex;
    else if(notIndex != -1)
        searchWordLength = notIndex;
    else
        searchWordLength = allInWords.size();

    std::cout<<"Search Word Length: "<<searchWordLength<< std::endl;
    std::cout<<"AndOr: "<<andOr<< std::endl;


    if(andOr == "and") {
        for (int y = 1; y<searchWordLength; y++){
            Porter2Stemmer::stem(allInWords[y]);
            andWords.push_back(allInWords[y]);
        }
    }
    else if(andOr == "or"){
        for (int y = 1; y<searchWordLength; y++) {
            Porter2Stemmer::stem(allInWords[y]);
            orWords.push_back(allInWords[y]);
        }
    }
    else if(andOr == ""){
        for (int y = 0; y<searchWordLength; y++){
            Porter2Stemmer::stem(allInWords[y]);
            andWords.push_back(allInWords[y]);
        }
    }

}

void QueryPro::searchTree(){      //gets article ids from AVL tree for AND and OR operators
    std::vector<std::string> currIDs;
    std::vector<std::string> currFreqs;
//        TreeNode* currNode;
    if(andOr == "or") {
        for (int i = 0; i < orWords.size(); i++) {
            std::vector<std::string> currIDs;
            std::vector<int> currFreqs;
            tree->find(orWords[i], tree->getHeadNode(), currIDs);
            tree->findNum(orWords[i], tree->getHeadNode(), currFreqs);
            std::cout<<"Files from beginning: ";
            for(int x = 0; x<currIDs.size(); x++) {
                std::cout << currIDs[x] << " ";
            }
            std::cout<<std::endl;

//            currNode = tree.find(orWords[i], tree.getHeadNode());
            for (int x = 0; x < currIDs.size(); x++) {
                bool alreadyIn = false;
                for (int y = 0; y < orFiles.size(); y++) {
                    if (orFiles[y] == currIDs[x])
                        alreadyIn = true;
                }
                if (!alreadyIn) {
                    orFiles.push_back(currIDs[x]);
                    orNums.push_back(currFreqs[x]);
                }
            }

            std::cout<<"Overall Or Files: ";
            for(int i = 0; i<orFiles.size(); i++)
                std::cout << orFiles[i] <<" ";
            std::cout<<std::endl;
        }
    }
    else {
        for (int i = 0; i < andWords.size(); i++) {
            std::vector<std::string> currIDs;
            std::vector<int> currFreqs;
            tree->find(andWords[i], tree->getHeadNode(), currIDs);
            tree->findNum(andWords[i], tree->getHeadNode(), currFreqs);
            std::cout<<"Files from beginning: ";
            for(int x = 0; x<currIDs.size(); x++)
                std::cout << " "+currIDs[x] << " ";
            std::cout<<std::endl;

//            currNode = tree.find(andWords[i], tree.getHeadNode());
            std::vector<std::string> collabFiles;
            std::vector<int> collabNums;
            for (int x = 0; x < currIDs.size(); x++) {
                bool alreadyIn = false;
                for (int y = 0; y < andFiles.size(); y++) {
                    if (andFiles[y] == currIDs[x])
                        alreadyIn = true;
                }
                if (alreadyIn || i == 0) {
                    collabFiles.push_back(currIDs[x]);
                    collabNums.push_back(currFreqs[x]);
                }
            }
            andFiles = collabFiles;
            andNums = collabNums;
            std::cout<<"        Overall And File: ";
            for(int i = 0; i<andFiles.size(); i++)
                std::cout << andFiles[i] <<" ";
            std::cout<<std::endl;
        }
    }
}

void QueryPro::compareNotAuthor() {    //gets article ids from AVL tree for NOT and AUTHOR operators

    std::vector<std::string> notIDs;
    std::vector<int> notNums;
    if (notIndex > -1) {
        tree->find(notWord, tree->getHeadNode(), notIDs);
        tree->findNum(notWord, tree->getHeadNode(), notNums);
    }
    notFiles = notIDs;
    std::cout<<"NOT Files Start: ";
    for(int i = 0; i<notFiles.size(); i++)
        std::cout << notFiles[i] <<" ";
    std::cout<<std::endl;

    std::vector<std::string> authorIDs;
    if (authorIndex > -1)
        hash->getValue(authorWord, authorIDs);
    authorFiles = authorIDs;
    std::cout<<"AUTHOR Files Start: ";
    for(int i = 0; i<authorFiles.size(); i++)
        std::cout << authorFiles[i] <<" ";
    std::cout<<std::endl;

    std::vector<std::string> tempVec;
    std::vector<int> tempVecN;
    bool isThere = false;
    if(notIndex > -1) {
        if(andOr == "or") {
            for (int i = 0; i < orFiles.size(); i++) {
                for (int x = 0; x < notFiles.size(); x++) {
                    if (orFiles[i] == notFiles[x])
                        isThere = true;
                }
                if (!isThere) {
                    tempVec.push_back(orFiles[i]);          //this right here
                    tempVecN.push_back(orNums[i]);
                }
            }
            orFiles = tempVec;
            orNums = tempVecN;
            std::cout<<"    Overall Or files: ";
            for(int i = 0; i<orFiles.size(); i++)
                std::cout << orFiles[i] <<" ";
            std::cout<<std::endl;
        }
        else{
            for (int i = 0; i < andFiles.size(); i++) {
                for (int x = 0; x < notFiles.size(); x++) {
                    if (andFiles[i] == notFiles[x])
                        isThere = true;
                }
                if (!isThere) {
                    tempVec.push_back(andFiles[i]);
                    tempVecN.push_back(andNums[i]);
                }
            }
            andFiles = tempVec;
            andNums = tempVecN;
            std::cout<<"        Overall And Files: ";
            for(int i = 0; i<andFiles.size(); i++)
                std::cout << andFiles[i] <<" ";
            std::cout<<std::endl;
        }
    }


    if(authorIndex > -1){
        if(andOr == "or") {
            for (int i = 0; i < orFiles.size(); i++) {
                for (int x = 0; x < authorFiles.size(); x++) {
                    if (orFiles[i] == authorFiles[x])
                        isThere = true;
                }
                if (isThere) {
                    tempVec.push_back(orFiles[i]);
                    tempVecN.push_back(orNums[i]);
                }
            }
            orFiles = tempVec;
            orNums = tempVecN;
            std::cout<<"    Overall Or files: ";
            for(int i = 0; i<orFiles.size(); i++)
                std::cout << orFiles[i] <<" ";
            std::cout<<std::endl;

        }
        else{
            for (int i = 0; i < andFiles.size(); i++) {
                for (int x = 0; x < authorFiles.size(); x++) {
                    if (andFiles[i] == authorFiles[x])
                        isThere = true;
                }
                if (isThere) {
                    tempVec.push_back(andFiles[i]);
                    tempVecN.push_back(andNums[i]);
                }
            }
            andFiles = tempVec;
            andNums = tempVecN;
            std::cout<<"        Overall And Files: ";
            for(int i = 0; i<andFiles.size(); i++)
                std::cout << andFiles[i] <<" ";
            std::cout<<std::endl;
        }
    }
}

void QueryPro::frequencyOrder(){      //sorts returned articles by word frequency
    if(andOr=="or") {
        for (int i = 0; i < orNums.size(); i++) {
            for(int x = 0; x<orNums.size()-1; x++)
                if(orNums[x] < orNums[x+1]){
                    int tempN = orNums[x];
                    orNums[x] = orNums[x+1];
                    orNums[x+1] = tempN;

                    std::string temp = orFiles[x];
                    orFiles[x] = orFiles[x+1];
                    orFiles[x+1] = temp;
                }
        }
    }
    else{
        for (int i = 0; i < andNums.size(); i++) {
            for(int x = 0; x<andNums.size()-1; x++)
                if(andNums[x] < andNums[x+1]){
                    int tempN = andNums[x];
                    andNums[x] = andNums[x+1];
                    andNums[x+1] = tempN;

                    std::string temp = andFiles[x];
                    andFiles[x] = andFiles[x+1];
                    andFiles[x+1] = temp;
                }
        }
    }
}

std::string QueryPro::correctWord(std::string word) {       //removes non letter characters and makes word lowercase
    std::string newWord;
    for(int i = 0; i<word.size(); i++) {
        if(isalpha(word[i])) {
            newWord += tolower(word[i]);
        }
    }
    return newWord;
}

void QueryPro::display() {
    if(andOr == "and") {
        std::cout << "And Words:  ";
        for (int i = 0; i < andWords.size(); i++)
            std::cout << andWords[i] << " ";
        std::cout << std::endl;
        if(authorWord != "")
            std::cout<<"Author Word:  "<<authorWord<<std::endl;
        if(notWord != "")
            std::cout<<"Not Words:  "<<notWord<<std::endl;

        std::cout<<"Files Found: "<<std::endl;
        for(int i = 0; i<andFiles.size(); i++)
            std::cout << "  "+andFiles[i] << " " << andNums[i] <<std::endl;
        std::cout<<std::endl;
    }
    else if(andOr == "or") {
        std::cout << "Or Words:  ";
        for (int x = 0; x < orWords.size(); x++)
            std::cout << orWords[x] << " ";
        std::cout << std::endl;

        if (authorWord != "")
            std::cout << "Author Word:  " << authorWord << std::endl;
        if (notWord != "")
            std::cout << "Not Words:  " << notWord << std::endl;

        std::cout<<"Files Found: "<<std::endl;
        for(int i = 0; i<orFiles.size(); i++)
            std::cout << "  "+orFiles[i]<< " " << orNums[i] <<std::endl;
        std::cout<<std::endl;
    }
    else{
        std::cout << "And Word:  ";
        for (int i = 0; i < andWords.size(); i++)
            std::cout << andWords[i] << " ";
        std::cout << std::endl;
        if(authorWord != "")
            std::cout<<"Author Word:  "<<authorWord<<std::endl;
        if(notWord != "")
            std::cout<<"Not Words:  "<<notWord<<std::endl;

        std::cout<<"Files Found: "<<std::endl;
        for(int i = 0; i<andFiles.size(); i++)
            std::cout << "  "+andFiles[i]<< " "<< andNums[i] <<std::endl;
        std::cout<<std::endl;
    }
}

void QueryPro::clearVecs(){
    std::vector<std::string> blankStr;
    std::vector<int> blankInt;
    std::string blankWord;

    allInWords = blankStr;

    notWord =blankWord;
    authorWord = blankWord;
    andOr = blankWord;

    andWords = blankStr;
    orWords = blankStr;
    andFiles = blankStr;
    orFiles = blankStr;
    notFiles = blankStr;
    authorFiles = blankStr;

    andNums = blankInt;
    orNums = blankInt;
    notNums = blankInt;
    authorNums = blankInt;
}