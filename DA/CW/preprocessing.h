#ifndef DA_KP_PREPROCESSING_H
#define DA_KP_PREPROCESSING_H

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <iterator>

struct TPoint {
    int32_t x, y;
    bool operator ==(const TPoint &obj) const {
        return (x == obj.x && y == obj.y);
    }
};

struct TSide {
    TPoint start, end;
    int8_t dir;     //side direction
    int32_t idx;    //polygon index
    bool operator ==(const TSide &obj) const {
        return (start == obj.start && end == obj.end);
    }
    bool operator <(const TSide &obj) const {
        return (start.y < obj.start.y || end.y < obj.end.y);
    }
};

void ReadPolygons(std::string &inputFile, std::set<int32_t> &abscissa, std::vector<std::vector<TPoint> > &polygons);
void SortingSides(std::vector<std::vector<TPoint> > &polygons, std::vector<TSide> &segments);

#endif //DA_KP_PREPROCESSING_H
