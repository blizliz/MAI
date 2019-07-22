#include "preprocessing.h"

void ReadPolygons(std::string &inputFile, std::set<int32_t > &abscissa, std::vector<std::vector<TPoint> > &polygons) {
    std::ifstream fin(inputFile);

    int32_t count;    //polygon nodes number
    TPoint coord;
    std::vector<TPoint> polygon;
    while (fin >> count) {
        for (int32_t i = 0; i < count; ++i) {
            fin >> coord.x;
            fin >> coord.y;
            polygon.push_back(coord);
            abscissa.insert(coord.x);    //get sorted array of X-coordinates
        }
        polygons.push_back(polygon);
        polygon.clear();
    }

    fin.close();
}

bool comp(TSide lhs, TSide rhs) {
    return lhs.start.x < rhs.start.x;
}

void SortingSides(std::vector<std::vector<TPoint>> &polygons, std::vector<TSide> &segments) {
    //polygons index counting starts from 0
    TSide side;

    int32_t polNum = polygons.size();
    for (int32_t i = 0; i < polNum; ++i) {
        int32_t pointNum = polygons[i].size();
        for (int32_t j = 0; j < pointNum - 1; ++j) {  //always min start-point in segment
            if (polygons[i][j].x < polygons[i][j + 1].x) {
                side.start = polygons[i][j];
                side.end = polygons[i][j + 1];
                side.dir = 'r';                       //direction determination
            } else if (polygons[i][j].x > polygons[i][j + 1].x) {
                side.start = polygons[i][j + 1];
                side.end = polygons[i][j];
                side.dir = 'l';
            } else {    //vertical segments skipping
                continue;
            }
            side.idx = i;  //polygon's index
            segments.push_back(side);
        }
        //last segment(last-point-first-point)
        if (polygons[i][pointNum - 1].x < polygons[i][0].x) {
            side.start = polygons[i][pointNum - 1];
            side.end = polygons[i][0];
            side.dir = 'r';                 //direction determination
        } else if (polygons[i][pointNum - 1].x > polygons[i][0].x) {
            side.start = polygons[i][0];
            side.end = polygons[i][pointNum - 1];
            side.dir = 'l';
        } else {    //vertical segments skipping
            continue;
        }
        side.idx = i;
        segments.push_back(side);
    }
    std::sort(segments.begin(), segments.end(), comp);
}