#define CATCH_CONFIG_RUNNER


#include <iostream>
#include <vector>
#include "FileFinder.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "wordFile.h"
#include "QueryPro.h"
#include "UI.h"

#include "catch2/catch.hpp"

int main(int argc, char** argv) {
    int result = 0;
    if(argc > 1) {
        UI interface(argv[1]);
        interface.askUser();

//        AVLTree tree;
//        FileFinder essays(argv[1]);
//        essays.runDirent();
//        essays.jsonParser();
//        tree.fillTree(essays.getFileWords());
//        tree.clearOutput();
//        tree.outputCaller();
////        tree.display();
//        std::cout<<std::endl;
//        std::cout<<std::endl;
//
//        HashTable<std::string, std::string> hash;
//        hash.fillTable(essays.getFileAuthors());
//        hash.outPutHash();
////        hash.displayHash();
//
//        QueryPro search(tree, hash);
//        search.getUserInput();
//        search.searchTree();
//        search.compareNotAuthor();
//        search.frequencyOrder();
//        search.display();
    }
    else{
        result = Catch::Session().run(argc, argv);
    }
    return result;
}
