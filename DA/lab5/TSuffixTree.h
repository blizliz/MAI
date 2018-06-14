//
// Created by elizaveta on 09.03.18.
//

#ifndef DA5_TSUFFIXTREE_H
#define DA5_TSUFFIXTREE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

struct TNode {
    std::map<char, TNode *> children;

    TNode *suffixLink;

    int32_t start;
    int32_t *end;
};

class TSuffixArray;

class TSuffixTree {
public:
    TSuffixTree(std::string str);
    friend TSuffixArray;

private:
    std::string s; //Input string
    TNode *root = nullptr; //Pointer to root node
    TNode *lastNewNode = nullptr;

    TNode *activeNode = nullptr;
    int32_t activeEdge = -1;
    int32_t activeLength = 0;

    int32_t remaining = 0;
    int32_t leafEnd = -1;
    int32_t *rootEnd = nullptr;
    int32_t *splitEnd = nullptr;
    int32_t size = -1; //Length of input string

    TNode *NewNode(int32_t start, int32_t *end);
    int32_t EdgeLength(TNode *n);
    bool WalkDown(TNode *currNode);
    void ExtendSuffixTree(int32_t pos);
    void SetSuffixIndexByDFS(TNode *n, int labelHeight, std::vector<int32_t> &array);
    void FreeSuffixTree(TNode *n);
};

class TSuffixArray {
public:
    TSuffixArray(TSuffixTree &tree);
    void Search(std::string patt);
private:
    std::vector<int32_t> array;
    std::string s;
    int32_t FindLeftBorder(std::string patt);
    int32_t FindRightBorder(std::string patt);
};


#endif //DA5_TSUFFIXTREE_H
