//
// Created by Rick Lattin on 5/1/21.
//
#ifndef SEARCH_ENGINE_QUERYPRO_H
#define SEARCH_ENGINE_QUERYPRO_H
#include <iostream>
#include "AVLTree.h"
#include "HashTable.h"
#include <vector>

class QueryPro{
private:
    std::string userInput;
    int numOfAdditions;
    std::string andOr;
    int notIndex = -1;
    int authorIndex = -1;
    AVLTree* tree;
    HashTable<std::string, std::string>* hash;
    std::vector<std::string> allInWords;

    std::vector<std::string> andWords;
    std::vector<std::string> orWords;
    std::string notWord;
    std::string authorWord;

    std::vector<std::string> andFiles;
    std::vector<std::string> orFiles;
    std::vector<std::string> notFiles;
    std::vector<std::string> authorFiles;

    std::vector<int> andNums;
    std::vector<int> orNums;
    std::vector<int> notNums;
    std::vector<int> authorNums;

public:
    QueryPro();
    QueryPro(AVLTree&, HashTable<std::string, std::string>&);
    void getUserInput();
    void searchTree();      //gets article ids from AVL tree for AND and OR operators
    void compareNotAuthor();    //gets article ids from AVL tree for NOT and AUTHOR operators
    void frequencyOrder();      //sorts returned articles by word frequency
    std::string correctWord(std::string);       //removes non letter characters and makes word lowercase
    void display();
    void clearVecs();
};

#endif //SEARCH_ENGINE_QUERYPRO_H
