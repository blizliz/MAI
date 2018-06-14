#include "TSuffixTree.h"

int32_t COUNT = 1;

TSuffixTree::TSuffixTree(std::string str): s(str) {
    size = s.size();
    rootEnd = new int32_t;
    *rootEnd = - 1;

    root = NewNode(-1, rootEnd);

    activeNode = root;

    for (int32_t i = 0; i < size; i++) {
        ExtendSuffixTree(i);
    }
}

TNode* TSuffixTree::NewNode(int32_t start, int32_t *end) {
    TNode *node = new TNode;

    node->suffixLink = root;
    node->start = start;
    node->end = end;

    return node;
}

int32_t TSuffixTree::EdgeLength(TNode *n) {
    return *(n->end) - (n->start) + 1;
}

bool TSuffixTree::WalkDown(TNode *currNode) {
    if (activeLength >= EdgeLength(currNode)) {
        activeEdge += EdgeLength(currNode);
        activeLength -= EdgeLength(currNode);
        activeNode = currNode;
        return true;
    }
    return false;
}

void TSuffixTree::ExtendSuffixTree(int32_t pos) {
    leafEnd = pos;

    remaining++;

    lastNewNode = nullptr;

    while (remaining) {
        if (activeLength == 0) {
            activeEdge = pos;
        }

        if (activeNode->children.find(s[activeEdge]) == activeNode->children.end()) {
            //Extension Rule 2
            activeNode->children[s[activeEdge]] =  NewNode(pos, &leafEnd);

            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        } else {
            TNode *next = activeNode->children[s[activeEdge]];
            if (WalkDown(next)) {
                //Start from next node
                continue;
            }
            //Extension Rule 3
            if (s[next->start + activeLength] == s[pos]) {
                if(lastNewNode != nullptr && activeNode != root) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
                activeLength++;
                break;
            }

            splitEnd = new int32_t;
            *splitEnd = next->start + activeLength - 1;

            TNode *split = NewNode(next->start, splitEnd);
            activeNode->children[s[activeEdge]] = split;

            split->children[s[pos]] = NewNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[s[next->start]] = next;

            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = split;
            }

            lastNewNode = split;
        }

        remaining--;
        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = pos - remaining + 1;
        } else if (activeNode != root) {
            activeNode = activeNode->suffixLink;
        }
    }
}

void TSuffixTree::SetSuffixIndexByDFS(TNode *n, int32_t labelHeight, std::vector<int32_t> &array) {
    if (n == nullptr) {
        return;
    }

    if(n->children.empty()) {
        array.push_back(size - labelHeight);
        return;
    }

    std::map<char, TNode *>::iterator i;
    for (i = n->children.begin(); i != n->children.end() ; ++i) {
        SetSuffixIndexByDFS(i->second, labelHeight + EdgeLength(i->second), array);
    }
}

void TSuffixTree::FreeSuffixTree(TNode *n) {
    if (n == nullptr) {
        return;
    }

    for(auto i = n->children.begin(); i != n->children.end(); i++ ) {
        FreeSuffixTree(i->second);
    }

    delete n;
}

TSuffixArray::TSuffixArray(TSuffixTree &tree) : s(tree.s) {
    tree.SetSuffixIndexByDFS(tree.root, 0, array);
    tree.FreeSuffixTree(tree.root);
}

void TSuffixArray::Search(std::string patt) {
    int32_t ansLeft = FindLeftBorder(patt);
    int32_t ansRight = FindRightBorder(patt);
    if (ansLeft > ansRight) {
        ++COUNT;
        return;
    } else {
        std::vector<int32_t> res(array.begin() + ansLeft, array.begin() + ansRight + 1);
        std::sort(res.begin(), res.end());
        if (ansRight < ansLeft) {
            ++COUNT;
            return; //нет вхождений
        } else {
            std::cout << COUNT << ": ";
            int32_t size = res.size();
            for (int32_t i = 0; i < size - 1; i++) {
                std::cout << res[i] + 1 << ", ";
            }
            std::cout << res[size - 1] + 1 << '\n';
        }
        ++COUNT;
    }
}

int32_t TSuffixArray::FindLeftBorder(std::string patt) {
    int32_t strSize = s.size();
    int32_t pattSize = patt.size();

    int32_t l = -1, r = strSize;

    while (l < r - 1) {
        int32_t mid = (l + r) / 2;

        if (patt > s.substr(array[mid], pattSize)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return r;
}

int32_t TSuffixArray::FindRightBorder(std::string patt) {
    int32_t strSize = s.size();
    int32_t pattSize = patt.size();

    int32_t l = -1, r = strSize;

    while (l < r - 1) {
        int32_t mid = (l + r) / 2;

        if (patt >= s.substr(array[mid], pattSize)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return l;
}