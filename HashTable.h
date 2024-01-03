//
// Created by Rick Lattin on 4/30/21.
//

#ifndef SEARCH_ENGINE_HASHTABLE_H
#define SEARCH_ENGINE_HASHTABLE_H
#include <iostream>
#include <vector>
#include "wordFile.h"

template <typename keyType, typename valType>
class HashEntry{
public:
    keyType key;
    std::vector<valType> value;
    HashEntry(keyType k, std::vector<valType> v):key(k), value(v) {}
};

template <typename keyType, typename valType>
class HashTable{
private:
    std::vector<HashEntry<keyType, valType>>* table = nullptr;
    int num_elements = 0;
    int table_size = 0;
    std::vector<std::string>* hashOut;
    int numUniqueAuthors;

public:
    HashTable();
    ~HashTable();
    void insertEntry(const keyType&, const valType&);
    void getValue(const keyType, std::vector<std::string>&);       //searches hash table and fills vector argument
    //std::array<std::vector<HashEntry<keyType, valType>>>& getTable();
    std::string correctWord(std::string);       //removes non letter characters and makes word lowercase
    int& getTableSize();
    void fillTable(std::vector<wordFile>);
    void displayHash();
    void outPutHash();      //outputs hash table to persitence file
    void clearOutput();       //clears persistence file
    int getUniqueAuthors();
};

template <typename keyType, typename valType>
HashTable<keyType, valType>::HashTable() {
    table_size = 100;
    table = new std::vector<HashEntry<keyType, valType>>[table_size];
}

template <typename keyType, typename valType>
HashTable<keyType, valType>::~HashTable() {
    delete table;
//    delete hashOut;
}

template <typename keyType, typename valType>
void HashTable<keyType, valType>::insertEntry(const keyType& currKey, const valType& currValue){
    int count;

    auto hash_value = std::hash<keyType>{}(currKey);
    int location = hash_value % table_size;
    if(table[location].size() < 1){
        std::vector<valType> firstID;
        firstID.push_back(currValue);
        HashEntry<keyType, valType> entry(currKey, firstID);
        table[location].push_back(entry);
        count++;
//        std::cout<<location<<std::endl;     //for testing
    }
    else {
        bool inOneSection = false;
        for (int i = 0; i < table[location].size(); i++) {
            if (table[location][i].key == currKey) {
                table[location][i].value.push_back(currValue);
//                std::cout << location << std::endl;     //for testing
                inOneSection = true;
            }
        }
        if(!inOneSection){
            std::vector<valType> addID;
            addID.push_back(currValue);
            HashEntry<keyType, valType> entry(currKey, addID);
            table[location].push_back(entry);
            count++;
//            std::cout<<location<<std::endl;     //for testing
        }
    }

    numUniqueAuthors = count;
}

template <typename keyType, typename valType>
void HashTable<keyType, valType>::getValue(const keyType currKey, std::vector<std::string>& outPut){       //searches hash table and fills vector argument
    hashOut = &outPut;
    auto location = std::hash<keyType>{}(currKey) % table_size;
    for(auto &c : table[location]){
        if(c.key == currKey)
            outPut = c.value;
    }
}

template <typename keyType, typename valType>
std::string HashTable<keyType, valType>::correctWord(std::string word) {       //removes non letter characters and makes word lowercase
    std::string newWord;
    for(int i = 0; i<word.size(); i++) {
        if(isalpha(word[i])) {
            newWord += tolower(word[i]);
        }
    }
    return newWord;
}

template <typename keyType, typename valType>
void HashTable<keyType, valType>::fillTable(std::vector<wordFile> authIDs) {
    for(int i = 0; i<authIDs.size(); i++){
       insertEntry(correctWord(authIDs[i].getKey()), authIDs[i].getLoc());
       num_elements = num_elements+1;
    }
}

template <typename keyType, typename valType>
void HashTable<keyType, valType>::displayHash(){
    for(int i = 0; i<table_size; i++){
        std::cout << "Index: " << i << std::endl;
        for(int x = 0; x<table[i].size(); x++){
            std::cout<<table[i][x].key<<" | IDs: ";
            for(int y = 0; y<table[i][x].value.size(); y++)
                std::cout<<table[i][x].value[y]<<" ";
            std::cout<<std::endl;
        }

    }
}
/*
template <typename keyType, typename valType>
std::array<std::vector<HashEntry<keyType, valType>>>& HashTable<keyType, valType>::getTable(){
    return table;
}*/
template <typename keyType, typename valType>
int& HashTable<keyType, valType>::getTableSize(){
    return table_size;
}

template <typename keyType, typename valType>
void HashTable<keyType, valType>::outPutHash() {      //outputs hash table to persitence file
    std::ofstream HashFile;
    HashFile.open("OutputHash.txt");
    for(int i = 0; i<table_size; i++){
        HashFile << " " << i << " ";
        for(int x = 0; x<table[i].size(); x++){
            HashFile<<table[i][x].key<<" ";
            for(int y = 0; y<table[i][x].value.size(); y++)
                HashFile<<table[i][x].value[y]<<" ";
        }
        HashFile<<std::endl;
    }
    HashFile.close();
}

template <typename keyType, typename valType>
void HashTable<keyType, valType>::clearOutput(){        //clears persistence file
    std::ofstream HashFile;
    HashFile.open("OutputHash.txt");
    HashFile.close();
}

template <typename keyType, typename valType>
int HashTable<keyType, valType>::getUniqueAuthors(){
    return numUniqueAuthors;
}

#endif //SEARCH_ENGINE_HASHTABLE_H