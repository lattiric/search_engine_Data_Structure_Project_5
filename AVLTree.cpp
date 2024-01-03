//
// Created by Rick Lattin on 5/1/21.
//
#include "AVLTree.h"
#include "porter2_stemmer/porter2_stemmer.h"
#include <iostream>
#include <fstream>

using Porter2Stemmer::stem;


AVLTree::AVLTree() {
    headNode = nullptr;
}

AVLTree::AVLTree(std::vector<std::string> names) {
    fileNames = names;
    headNode = nullptr;
}

AVLTree::~AVLTree(){
    clearTree(headNode);
//    delete finOut;
//    delete freqOut;
}

void AVLTree::clearTree(TreeNode*& head) {
    std::cout<<"destroy"<<std::endl;
    if(head != nullptr){
        clearTree(head->leftBranch);
        clearTree(head->rightBranch);
        delete head;
    }
    head = nullptr;
}

int AVLTree::getHeight(TreeNode* node) {
    if(node == nullptr)
        return 0;
    else
        return node->height;
}

TreeNode* AVLTree::makeNode(std::string key) {    //initializes TreeNode Object
    TreeNode *newNode = new TreeNode;
    newNode->height = 1;
    newNode->key = key;
    newNode->leftBranch = nullptr;
    newNode->rightBranch = nullptr;

    return newNode;
}

TreeNode* AVLTree::makeNode(wordFile word) {
    TreeNode *newNode = new TreeNode;
    newNode->height = 0;
    newNode->key = word.getKey();
    newNode->leftBranch = nullptr;
    newNode->rightBranch = nullptr;
    newNode->data.push_back(word.getLoc());

    return newNode;
}

void AVLTree::rotateRight(TreeNode*& startNode) {       //same as rotate left branch
    bool wasHead = false;
    if(startNode == headNode)
        wasHead = true;

    TreeNode* left = startNode->leftBranch;
    TreeNode* rightDown = left->rightBranch;

    left->rightBranch = startNode;
    startNode->leftBranch = rightDown;

    if(getHeight(left->rightBranch) > getHeight(left->leftBranch))
        left->height = left->rightBranch->height + 1;
    else
        left->height = left->leftBranch->height + 1;

    if(getHeight(startNode->rightBranch) > getHeight(startNode->leftBranch))
        startNode->height = startNode->rightBranch->height + 1;
    else
        startNode->height = getHeight(startNode->leftBranch) + 1;

    if(wasHead)
        headNode = left;
}

void AVLTree::rotateLeft(TreeNode*& startNode) {       //same as rotate right branch
    bool wasHead = false;
    if(startNode == headNode)
        wasHead = true;

    TreeNode* right = startNode->rightBranch;
    TreeNode* leftDown = right->leftBranch;

    right->leftBranch = startNode;
    startNode->rightBranch = leftDown;

    if(getHeight(right->rightBranch) > getHeight(right->leftBranch))
        right->height = getHeight(right->rightBranch) + 1;
    else
        right->height = getHeight(right->leftBranch) + 1;
    if(getHeight(startNode->rightBranch) > getHeight(startNode->leftBranch))
        startNode->height = getHeight(startNode->rightBranch) + 1;
    else
        startNode->height = getHeight(startNode->leftBranch) + 1;

    if(wasHead)
        headNode = right;
}

void AVLTree::rotateRight_Left(TreeNode*& startNode) {        //same as double rotate left branch
    rotateLeft(startNode->leftBranch);
    rotateRight(startNode);
}

void AVLTree::rotateLeft_right(TreeNode*& startNode) {        //same as double rotate right branch
    rotateRight(startNode->rightBranch);
    rotateLeft(startNode);
}

void AVLTree::insertNode(wordFile word, TreeNode*& topNode){     //inserts and balances
    std::string thisKey = correctWord(word.getKey());
    std::string otherKey;
    Porter2Stemmer::stem(thisKey);

    if(topNode != nullptr){
        otherKey = topNode->key;
        Porter2Stemmer::stem(otherKey);
        topNode->key = otherKey;
    }

    if(topNode == nullptr) {
        topNode = makeNode(thisKey);
        topNode->data.push_back(word.getLoc());
        topNode->occurrences.push_back(1);
    }
    else if(otherKey < thisKey){
        insertNode(word, topNode->rightBranch);
        if( getHeight(topNode->rightBranch) - getHeight(topNode->leftBranch) == 2 ){
            if( topNode->rightBranch->key < thisKey )
                rotateLeft( topNode );
            else
                rotateLeft_right( topNode );
        }
    }

    else if(thisKey < otherKey){
        insertNode(word, topNode->leftBranch);
        if(getHeight(topNode->leftBranch) - getHeight(topNode->rightBranch) == 2 ) {
            if (thisKey < topNode->leftBranch->key)
                rotateRight(topNode);
            else
                rotateRight_Left(topNode);
        }
    }

    else if(thisKey == otherKey) {
        bool isThere = false;
        for(int i = 0; i<topNode->data.size(); i++) {
            if (topNode->data[i] == word.getLoc()) {
                isThere = true;
                topNode->occurrences[i] = topNode->occurrences[i]+1;
            }
        }
        if(!isThere) {
            topNode->data.push_back(word.getLoc());
            topNode->occurrences.push_back(1);
        }
    }
//    balance(topNode);
}

void AVLTree::balance(TreeNode*& head){
    if(getHeight(head->leftBranch)-getHeight(head->rightBranch) > 1) {
        if (getHeight(head->leftBranch->leftBranch) >= getHeight(head->leftBranch->rightBranch))
            rotateRight(head);
        else
            rotateRight_Left(head);
    }
    else if(getHeight(head->rightBranch)-getHeight(head->leftBranch) > 1){
        if (getHeight(head->rightBranch->leftBranch) >= getHeight(head->rightBranch->rightBranch))
            rotateLeft_right(head);
        else
            rotateLeft(head);
    }
    head->height = std::max(getHeight(head->leftBranch), getHeight(head->rightBranch))+1;
};
//std::string keyWord, std::string fileLoc
//void AVLTree::insertNode(wordFile keyWord, TreeNode*& topNode){
//    if( topNode == nullptr ) {
//        topNode = makeNode(keyWord);
////        std::cout<<"      found a place for the node"<<std::endl;
//    }
//    else if(topNode->key == keyWord.getKey()){
////        std::cout<<"             adds to other node"<<std::endl;
//        bool willAdd = true;
//        for(int i = 0; i<topNode->data.size(); i++) {
//            if (topNode->data[i] == keyWord.getLoc())
//                willAdd = false;
//        }
//        if(willAdd)
//            topNode->data.push_back(keyWord.getLoc());
//    }
//    else if( keyWord.getKey() < topNode->key )
//    {
//        insertNode( keyWord, topNode->leftBranch);
//        if(getHeight(topNode->leftBranch) - getHeight(topNode->rightBranch) == 2 ) {
//            if (keyWord.getKey() < topNode->leftBranch->key)
//                rotateRight(topNode);
//            else
//                rotateRight_Left(topNode);
//        }
//    }
//    else if( topNode->key < keyWord.getKey() )
//    {
//        insertNode( keyWord, topNode->rightBranch );
//        if( getHeight(topNode->rightBranch) - getHeight(topNode->leftBranch) == 2 )
//            if( topNode->rightBranch->key < keyWord.getKey() )
//                rotateLeft( topNode );
//            else
//                rotateLeft_right( topNode );
//    }
//    else {
//        int nothing;  // Duplicate; do nothing
//    }
//    if(topNode->leftBranch > topNode->rightBranch)
//        topNode->height = getHeight(topNode->leftBranch) + 1;
//    else
//        topNode->height = getHeight(topNode->rightBranch) + 1;
//}

//TreeNode* AVLTree::find(std::string currKey, TreeNode* headNode)
//{
//    TreeNode* checkingNode = headNode;
//    while(checkingNode != nullptr){
//        if(currKey < checkingNode->key)
//            checkingNode = checkingNode->leftBranch;
//        else if(checkingNode->key < currKey)
//            checkingNode = checkingNode->rightBranch;
//        else
//            return checkingNode;
//    }
//}

void AVLTree::find(std::string currKey, TreeNode* headNode, std::vector<std::string>& output)       //searches Tree and fills vector parameter with article IDs
{
    finOut = &output;
    TreeNode* checkingNode = headNode;
//    TreeNode*
    while(checkingNode != nullptr){
        if(currKey < checkingNode->key)
            checkingNode = checkingNode->leftBranch;
        else if(checkingNode->key < currKey)
            checkingNode = checkingNode->rightBranch;
        else {
            output = checkingNode->data;
            return;
        }
    }
}

void AVLTree::findNum(std::string currKey, TreeNode* headNode, std::vector<int>& output)            //same thing but with frequencies
{
    freqOut = &output;
    TreeNode* checkingNode = headNode;
//    TreeNode*
    while(checkingNode != nullptr){
        if(currKey < checkingNode->key)
            checkingNode = checkingNode->leftBranch;
        else if(checkingNode->key < currKey)
            checkingNode = checkingNode->rightBranch;
        else {
            output = checkingNode->occurrences;
            return;
        }
    }
}

//TreeNode* AVLTree::getTreeNode(std::string key) {
//    TreeNode* checkingNode = headNode;
//    bool fartherDown = true;
//
//    while(fartherDown) {
//        if(checkingNode->key == key)
//            return checkingNode;
//        else if(checkingNode->key > key)
//            if(checkingNode->leftBranch != nullptr && checkingNode->leftBranch->key == key)
//                return checkingNode;
//            else
//                checkingNode = checkingNode->leftBranch;
//        else if(checkingNode->key < key){
//            if (checkingNode->rightBranch != nullptr && checkingNode->rightBranch->key != key)
//                checkingNode = checkingNode->rightBranch;
//            else
//                return checkingNode;
//        }
//        else{
//            return checkingNode;
//        }
//    }
//}

TreeNode*& AVLTree::getHeadNode() {
    return headNode;
}

//int AVLTree::checkBalance(TreeNode* node) {
//    if(node == nullptr)
//        return nullptr;        //maybe check
//    else
//        return (node->leftBranch->height) - (node->rightBranch->height);
//}

void AVLTree::printTree(TreeNode* startNode) {
    if(startNode == nullptr)
        return;
    printTree(startNode->leftBranch);
    std::cout<<startNode->key<<": ";
    for(int i = 0; i<startNode->data.size(); i++)
        std::cout<<startNode->data[i]<<" ";
    std::cout<<std::endl;
    printTree(startNode->rightBranch);
}

void AVLTree::display(){
    printTree(headNode);
    std::cout<<std::endl;
}

std::string AVLTree::correctWord(std::string word) {       //removes non letter characters and makes word lowercase
    std::string newWord;
    for(int i = 0; i<word.size(); i++) {
        if(isalpha(word[i])) {
            newWord += tolower(word[i]);
        }
    }
    return newWord;
}

void AVLTree::fillTree(std::vector<wordFile> entries){      //fills AVLTree object
    int count = 0;
    for(int i = 0; i<entries.size(); i++){
        this->insertNode(entries[i], headNode);
        count++;
        if(count%1000 == 0)
            std::cout<<count<<std::endl;
//        std::cout<<"Adding "<<entries[i].getKey()<<" to tree"<<std::endl;
    }
    numWordsInserted = count;
}

void AVLTree::outPutTree(std::ofstream& AVLFile, TreeNode* startNode) {     //Prints Tree to persistence file
    if(startNode == nullptr)
        return;
    outPutTree(AVLFile, startNode->leftBranch);
    AVLFile<<startNode->key<<" ";
    for(int i = 0; i<startNode->data.size(); i++)
        AVLFile<<startNode->data[i]<<" ";
    AVLFile<<std::endl;
    outPutTree(AVLFile, startNode->rightBranch);
}

void AVLTree::outputCaller(){
    std::ofstream AVLFile;
    AVLFile.open("OutputAVL.txt");
    outPutTree(AVLFile, headNode);
    AVLFile.close();
}

void AVLTree::clearOutput() {     //Prints Tree to persistence file
    std::ofstream AVLFile;
    remove("OutputAVL.txt");
//    AVLFile.open("OutputAVL.txt");
//    AVLFile.close();
}

int AVLTree::getNumWordsInserted() {
    return numWordsInserted;
}