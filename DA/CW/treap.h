#ifndef DA_KP_TREAP_H
#define DA_KP_TREAP_H

#include "preprocessing.h"

struct TNode {
    TSide key;
    int32_t prior;
    int32_t left, right;
    TNode() {}
    TNode(TSide k, int32_t p) : key(k), prior(p), left(-1), right(-1) {}
};

class TPersTreap {
public:
    void MakeTreap(std::set<int32_t> abscissa, std::vector<TSide> &segments);
    void Serialize(std::string &inputFile, std::set<int32_t > &abscissa);
    void Deserialize(std::string &indexFile, std::vector<int32_t> &abscissa);
    void SearchFigures(std::string &inputFile, std::string &outputFile, std::vector<int32_t> abscissa);

private:
    std::vector<int32_t> roots;
    std::vector<TNode> nodes;
    int32_t NewNode(TSide val, int32_t prior);
    void Split(int32_t t, TSide k, int32_t &l, int32_t &r);
    void Merge(int32_t l, int32_t r, int32_t &t);
    void Insert(int32_t &t, int32_t &newt, int32_t val);
    void Remove(int32_t &t, int32_t &newT, TSide key);
    void RemoveMaxKey(int32_t &t);
    int32_t CopyTree(int32_t &t);
    int32_t PointUnderLine(TPoint start, TPoint end, TPoint check);
    int32_t SearchNext(int32_t t, TPoint point);
};

#endif //DA_KP_TREAP_H
