//
// Created by Rick Lattin on 4/30/21.
//

#ifndef SEARCH_ENGINE_TREENODE_H
#define SEARCH_ENGINE_TREENODE_H
#include <iostream>
#include <vector>


class TreeNode{
public:
    std::string key;
    TreeNode* leftBranch;
    TreeNode* rightBranch;
    std::vector<std::string> data;
    std::vector<int> occurrences;
    int height;
    TreeNode();
};

#endif //SEARCH_ENGINE_TREENODE_H
