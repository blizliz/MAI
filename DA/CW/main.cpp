#include <iostream>
#include <string>

#include "treap.h"
#include "preprocessing.h"

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cout << "More arguments expected";
        return 0;
    }

    if (std::string(argv[1]) == "index") {
        std::string inputFile, indexFile;

        for (int16_t i = 2; i < argc; i += 2) {
            if ((std::string)argv[i] == "--input") {
                inputFile = argv[i + 1];
            }
            else if ((std::string)argv[i] == "--output") {
                indexFile = argv[i + 1];
            }
        }

        std::set<int32_t> abscissa;
        std::vector<std::vector<TPoint>> polygons;
        ReadPolygons(inputFile, abscissa, polygons);

        std::vector<TSide> segments;
        SortingSides(polygons, segments);

        TPersTreap treap;
        treap.MakeTreap(abscissa, segments);
        treap.Serialize(indexFile, abscissa);
    }
    else if (std::string(argv[1]) == "search") {
        std::string indexFile, inputFile, outputFile;
        for (int16_t i = 2; i < argc; i += 2) {
            if ((std::string)argv[i] == "--index") {
                indexFile = argv[i + 1];
            }
            if ((std::string)argv[i] == "--input") {
                inputFile = argv[i + 1];
            }
            if ((std::string)argv[i] == "--output") {
                outputFile = argv[i + 1];
            }
        }

        std::vector<int32_t > abscissa;
        TPersTreap treap;
        treap.Deserialize(indexFile, abscissa);

        treap.SearchFigures(inputFile, outputFile, abscissa);
    }
    return 0;
}