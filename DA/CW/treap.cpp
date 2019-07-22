#include <queue>

#include "treap.h"

int32_t TPersTreap::NewNode(TSide val, int32_t prior) {
    TNode node = TNode(val, prior);
    nodes.push_back(node);
    return (nodes.size() - 1);
}

void TPersTreap::Split(int32_t t, TSide k, int32_t &l, int32_t &r) {
    int32_t newT = -1;
    if(t == -1) {
        l = r = -1;
    } else if(k < nodes[t].key) {
        newT = CopyTree(nodes[t].left);
        Split(newT, k, l, newT);

        r = NewNode(nodes[t].key, nodes[t].prior);
        nodes[r].right = nodes[t].right;
        nodes[r].left = newT;
    } else {
        newT = CopyTree(nodes[t].right);
        Split(newT, k, newT, r);

        l = NewNode(nodes[t].key, nodes[t].prior);
        nodes[l].left = nodes[t].left;
        nodes[l].right = newT;
    }
}

void TPersTreap::Merge(int32_t l, int32_t r, int32_t &t) {
    int32_t newT = -1;
    if (l == -1 || r == -1) {
        t = (l != -1) ? l : r;
    } else if (nodes[l].prior > nodes[r].prior) {
        newT = CopyTree(nodes[l].right);
        Merge(newT, r, newT);

        t = NewNode(nodes[l].key, nodes[l].prior);
        nodes[t].left = nodes[l].left;
        nodes[t].right = newT;
    } else {
        newT = CopyTree(nodes[r].left);
        Merge(l, newT, newT);

        t = NewNode(nodes[r].key, nodes[r].prior);
        nodes[t].right = nodes[r].right;
        nodes[t].left = newT;
    }
}

//                      prev vers   new vers       ins elem
void TPersTreap::Insert(int32_t &t, int32_t &newT, int32_t val) {
    if (t == -1) {
        newT = val;
    } else {
        int32_t newleft = -1, newright = -1;

        Split(t, nodes[val].key, newleft, newright);
        Merge(newleft, val, newleft);
        Merge(newleft, newright, newT);
    }
}

void TPersTreap::Remove(int32_t &t, int32_t &newT, TSide key) {
    if (t == -1) {
        return;
    } else {
        int32_t newleft = -1, newright = -1;

        Split(t, key, newleft, newright);
        RemoveMaxKey(newleft);
        Merge(newleft, newright, newT);
    }
}

void TPersTreap::RemoveMaxKey(int32_t &t) {
    if (nodes[t].right != -1) {
        RemoveMaxKey(nodes[t].right);
    } else {
        t = nodes[t].left;
        return;
    }
}

int32_t TPersTreap::CopyTree(int32_t &t) {
    int32_t newleft, newright, newnode;

    if (t == -1) {
        return -1;
    }

    if (nodes[t].left != -1) {
        newleft = CopyTree(nodes[t].left);
    } else {
        newleft = -1;
    }

    if (nodes[t].right != -1) {
        newright = CopyTree(nodes[t].right);
    } else {
        newright = -1;
    }

    newnode = NewNode(nodes[t].key, nodes[t].prior);
    nodes[newnode].left = newleft;
    nodes[newnode].right = newright;

    return newnode;
}

struct PQComp {
    bool operator()(const TSide& lhs, const TSide& rhs) {
        return lhs.end.x > rhs.end.x;
    }
};

void TPersTreap::MakeTreap(std::set<int32_t> abscissa, std::vector<TSide> &segments) {
    //segments to be deleted in next slab
    std::priority_queue<TSide, std::vector<TSide>, PQComp> forDel;

    int32_t prevTreap = -1;
    int32_t tmpTreap = -1;

    int32_t nextSegmentInx = 0;
    for (auto it = abscissa.begin(); it != abscissa.end(); ++it) {
        int32_t x = *it;

        while (!forDel.empty() && x == forDel.top().end.x) {
            Remove(prevTreap, tmpTreap, forDel.top());
            forDel.pop();

            prevTreap = tmpTreap;
            tmpTreap = -1;
        }

        for (int32_t i = nextSegmentInx; i < segments.size(); ++i) {
            if (x == segments[i].start.x) {    //still the same slab
                //insert into the current slabTree
                int32_t val = NewNode(segments[i], rand());
                Insert(prevTreap, tmpTreap, val);
                prevTreap = tmpTreap;
                tmpTreap = -1;
                forDel.push(segments[i]);
            } else {
                roots.push_back(prevTreap);
                nextSegmentInx = i;
                break;
            }
            if (i == segments.size() - 1) {
                roots.push_back(prevTreap);
            }
        }

    }
}

void TPersTreap::Serialize(std::string &indexFile, std::set<int32_t > &abscissa) {
    std::ofstream fout(indexFile, std::ofstream::binary);

    std::vector<int32_t> xS(abscissa.begin(), abscissa.end());
    abscissa.clear();

    int32_t sizeXS = xS.size(), sizeRoots = roots.size(), sizeNodes = nodes.size();

    fout.write((char*)&sizeXS, sizeof(int32_t));
    fout.write((char*)(xS.data()), sizeof(int32_t) * sizeXS);

    fout.write((char*)&sizeRoots, sizeof(int32_t));
    fout.write((char*)(roots.data()), sizeof(int32_t) * sizeRoots);

    fout.write((char*)&sizeNodes, sizeof(int32_t));
    fout.write((char*)(nodes.data()), sizeof(TNode) * sizeNodes);

    fout.close();
}

void TPersTreap::Deserialize(std::string &indexFile, std::vector<int32_t> &xS) {
    std::ifstream fin(indexFile, std::fstream::binary);

    int32_t sizeXS = 0, sizeRoots = 0, sizeNodes = 0;
    fin.read((char*)&sizeXS, sizeof(int32_t));
    xS.resize(sizeXS);
    fin.read((char*)(xS.data()), sizeof(int32_t) * sizeXS);

    fin.read((char*)&sizeRoots, sizeof(int32_t));
    this->roots.resize(sizeRoots);
    fin.read((char*)(roots.data()), sizeof(int32_t) * sizeRoots);

    fin.read((char*)&sizeNodes, sizeof(int32_t));
    this->nodes.resize(sizeNodes);
    fin.read((char*)(nodes.data()), sizeof(TNode) * sizeNodes);

    fin.close();
}

void TPersTreap::SearchFigures(std::string &inputFile, std::string &outputFile, std::vector<int32_t> abscissa) {
    std::ifstream fin(inputFile);
    std::ofstream fout(outputFile);

    TPoint point;
    int32_t slab = -1;
    int32_t tree;
    int32_t slabLeft = -1, slabRight = -1;    //point on the border of slabs
    int32_t desNode;                //the desired line in tree

    while(fin >> point.x >> point.y) {
        //point not in slabs
        if (point.x < abscissa[0] || point.x > abscissa[abscissa.size() - 1]) {  //point on the last border
            fout << -1 << '\n';
            continue;
        }

        //search point slab
        for (int32_t i = 0; i < abscissa.size() - 1; ++i) {
            if (point.x == abscissa[i]) {
                if (i == 0) {
                    slab = i;
                } else {
                    slabLeft = i - 1;
                    slabRight = i;
                }
            } else if (point.x > abscissa[i] && point.x < abscissa[i + 1]) {
                slab = i;
                break;
            }
        }
        if (point.x == abscissa[abscissa.size() - 1]) {    // point on the right border of last slab
            slab = abscissa.size() - 2;
        }


        if (slab != -1) {
            tree = roots[slab];
            desNode = SearchNext(tree, point);
            //condition point belongs polygon
            bool cond1 = PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) == 0;
            bool cond2 = nodes[desNode].key.dir == 'l' && nodes[desNode].key.start.y <= nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) > 0;
            bool cond3 = nodes[desNode].key.dir == 'l' && nodes[desNode].key.start.y > nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) < 0;
            bool cond4 = nodes[desNode].key.dir == 'r' && nodes[desNode].key.start.y <= nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) < 0;
            bool cond5 = nodes[desNode].key.dir == 'r' && nodes[desNode].key.start.y > nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) > 0;
            if (desNode != -1 && (cond1 || cond2 || cond3 || cond4 || cond5)) {
                fout << nodes[desNode].key.idx << '\n';
            } else {
                fout << -1 << '\n';
            }
            slab = -1;
        } else {
            //check left slab
            tree = roots[slabLeft];
            desNode = SearchNext(tree, point);
            //condition point belongs polygon
            bool cond1 = PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) == 0;
            bool cond2 = nodes[desNode].key.dir == 'l' && nodes[desNode].key.start.y <= nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) > 0;
            bool cond3 = nodes[desNode].key.dir == 'l' && nodes[desNode].key.start.y > nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) < 0;
            bool cond4 = nodes[desNode].key.dir == 'r' && nodes[desNode].key.start.y <= nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) < 0;
            bool cond5 = nodes[desNode].key.dir == 'r' && nodes[desNode].key.start.y > nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) > 0;
            if (desNode != -1 && (cond1 || cond2 || cond3 || cond4 || cond5)) {
                fout << nodes[desNode].key.idx << '\n';
                continue;
            }

            //check right slab
            tree = roots[slabRight];
            desNode = SearchNext(tree, point);
            //condition point belongs polygon
            cond1 = PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) == 0;
            cond2 = nodes[desNode].key.dir == 'l' && nodes[desNode].key.start.y <= nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) > 0;
            cond3 = nodes[desNode].key.dir == 'l' && nodes[desNode].key.start.y > nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) < 0;
            cond4 = nodes[desNode].key.dir == 'r' && nodes[desNode].key.start.y <= nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) < 0;
            cond5 = nodes[desNode].key.dir == 'r' && nodes[desNode].key.start.y > nodes[desNode].key.end.y && PointUnderLine(nodes[desNode].key.start, nodes[desNode].key.end, point) > 0;
            if (desNode != -1 && (cond1 || cond2 || cond3 || cond4 || cond5)) {
                fout << nodes[desNode].key.idx << '\n';
                continue;
            } else {
                fout << -1 << '\n';
            }
            slabLeft = slabRight = -1;
        }

    }

    fin.close();
    fout.close();
}

int32_t TPersTreap::PointUnderLine(TPoint start, TPoint end, TPoint check) {
    return ((check.x - start.x) * (end.y - start.y)
            - (check.y - start.y) * (end.x - start.x));
}

int32_t TPersTreap::SearchNext(int32_t t, TPoint point) {
    int32_t curr = t, succ = -1;

    while (curr != -1) {
        int32_t location = PointUnderLine(nodes[curr].key.start, nodes[curr].key.end, point);
        if (location > 0 || location == 0) {
            succ = curr;
            curr = nodes[curr].left;
        } else {
            curr = nodes[curr].right;
        }
    }
    return succ;
}