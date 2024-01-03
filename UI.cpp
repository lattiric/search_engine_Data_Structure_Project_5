//
// Created by Rick Lattin on 5/2/21.
//
#include "UI.h"
#include "AVLTree.h"
#include "FileFinder.h"
#include "HashTable.h"
#include "QueryPro.h"

UI::UI(){

}

UI::UI(std::string str) {
    arg = str;
}

void UI::askUser(){

    AVLTree tree;
    FileFinder essays(arg);
    HashTable<std::string, std::string> hash;
    QueryPro search(tree, hash);

    bool keepRunning = true;
    while(keepRunning) {
        std::cout<<"Enter a Capitol Letter to Choose Option: "<<std::endl;
        std::cout<<"----------------------------------------------"<<std::endl;
        std::cout<<"A | Parse Corpus and Populate Index. "<<std::endl;
        std::cout<<"B | Open a Persistence File for Index."<<std::endl;
        std::cout<<"C | Display Indexes."<<std::endl;
        std::cout<<"D | Completely Clear Persistence Files."<<std::endl;
        std::cout<<"E | Input Boolean Search Query."<<std::endl;
        std::cout<<"F | Print Basic Stats of Search Engine."<<std::endl;
        std::cout<<"Input: ";
        char uEntry[10];
        std::cin.getline(uEntry, 10);
        std::string userEntry = +uEntry;
        std::cout<<std::endl;

        if (userEntry == "A") {
            essays.runDirent();
            essays.jsonParser();
            tree.fillTree(essays.getFileWords());
            hash.fillTable(essays.getFileAuthors());
            std::cout<<"**Index Created**"<<std::endl;
        } else if (userEntry == "B") {
            tree.outputCaller();
            hash.outPutHash();
            std::cout<<"**Persistence File Opened**"<<std::endl;
        } else if (userEntry == "C") {
            tree.display();
            hash.displayHash();
        } else if (userEntry == "D") {
            tree.clearOutput();
            hash.clearOutput();
            std::cout<<"**Index Cleared**"<<std::endl;
        } else if (userEntry == "E") {
            search.clearVecs();
            search.getUserInput();
            search.searchTree();
            search.compareNotAuthor();
            search.frequencyOrder();
            search.display();
        } else if (userEntry == "F") {
            std::cout<<"The Search Engine parses "<<essays.getFilesParsed()<<" documents total."<<std::endl;
            std::cout<<"The each article contains about "<<tree.getNumWordsInserted()/essays.getFilesParsed()<<" Words Indexed Words Per Article."<<std::endl;
//            std::cout<<"The articles contain "<<hash.getUniqueAuthors()<<" Unique Authors."<<std::endl;
            std::cout<<std::endl;
        }
        else if(userEntry == "ABCDEFG") {
            keepRunning = false;
        }
        else{
                std::cout << "Invalid Input! Please Try Again." << std::endl << std::endl;
                this->askUser();
        }
    }
}