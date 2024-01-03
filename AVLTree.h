//
// Created by Rick Lattin on 4/14/21.
//

#ifndef SEARCH_ENGINE_AVLTREE_H
#define SEARCH_ENGINE_AVLTREE_H
//#include "DSVector.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "wordFile.h"
#include "TreeNode.h"



class AVLTree{
    private:
        std::vector<std::string> fileNames;
        TreeNode* headNode;
        std::vector<std::string>* finOut;
        std::vector<int>* freqOut;
        int numWordsInserted;
    public:
        AVLTree();
        AVLTree(std::vector<std::string>);
        ~AVLTree();
        void clearTree(TreeNode*&);
        int getHeight(TreeNode*);
        TreeNode* makeNode(std::string);    //initializes TreeNode Object
        TreeNode* makeNode(wordFile);
        void rotateRight(TreeNode*&);       //same as rotate left branch
        void rotateLeft(TreeNode*&);       //same as rotate right branch
        void rotateRight_Left(TreeNode*&);        //same as double rotate left branch
        void rotateLeft_right(TreeNode*&);       //same as double rotate right branch
//        void insertNode(TreeNode*, TreeNode*&);
        void insertNode(wordFile, TreeNode*&);     //inserts and balances
        void balance(TreeNode*&);
//        TreeNode* getTreeNode(std::string);
        void find(std::string, TreeNode*, std::vector<std::string>&);       //searches Tree and fills vector parameter with article IDs
        void findNum(std::string, TreeNode*, std::vector<int>&);            //same thing but with frequencies
        TreeNode*& getHeadNode();
        void printTree(TreeNode*);
        void display();
        std::string correctWord(std::string);       //removes non letter characters and makes word lowercase
        void fillTree(std::vector<wordFile>);       //fills AVLTree object
        void outPutTree(std::ofstream&, TreeNode*);     //Prints Tree to persistence file
        void outputCaller();
        void clearOutput();                             //Clears persistence file
        int getNumWordsInserted();
};

#endif //SEARCH_ENGINE_AVLTREE_H
