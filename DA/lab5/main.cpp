#include "TSuffixTree.h"

int main() {
    std::string str, pattern;
    std::cin >> str;
    if (str.empty()) {
        return 0;
    }

    TSuffixTree tree(str + '$');
    TSuffixArray array(tree);

    while(std::cin >> pattern) {
        if (!pattern. empty()) {
            array.Search(pattern);
        }
    }
    return 0;
}
