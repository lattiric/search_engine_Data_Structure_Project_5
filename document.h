//
// Created by Rick Lattin on 5/3/21.
//

#ifndef SEARCH_ENGINE_DOCUMENT_H
#define SEARCH_ENGINE_DOCUMENT_H
#include "FileFinder.h"
#include <iostream>
#inlcude <vector>

class document{
private:
    std::string title;
    std::vector<std::string> authors;
    std::string firstWords;
public:
    document();
};

#endif //SEARCH_ENGINE_DOCUMENT_H
