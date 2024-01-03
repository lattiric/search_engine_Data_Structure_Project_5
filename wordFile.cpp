//
// Created by Rick Lattin on 4/19/21.
//
#include "wordFile.h"

wordFile::wordFile() {
    key = "";
    loc = "";
}

wordFile::wordFile(std::string k, std::string l) {
    key = k;
    loc = l;
}

std::string wordFile::getKey() {
    return key;
}

std::string wordFile::getLoc() {
    return loc;
}

void wordFile::setKey(std::string k) {
    key = k;
}

void wordFile::setLoc(std::string l) {
    loc = l;
}