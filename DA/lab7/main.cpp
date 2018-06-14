#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int16_t LENGTH, WIDTH;

void ReadData(vector<vector<int8_t> > &rect) {
    rect.resize(LENGTH);
    for (int i = 0; i < LENGTH; ++i) {
        rect[i].resize(WIDTH);
        for (int j = 0; j < WIDTH; ++j) {
            cin >> rect[i][j];
        }
    }
}

int32_t MaxSqrInLine(vector<int16_t> &column) {
    stack<int16_t> stack;
    int32_t maxLineSqr = 0;

    int16_t i = 0;
    while(i < WIDTH || !stack.empty()) {
        if(stack.empty() || (column[stack.top()] <= column[i] && i < WIDTH)) {
            stack.push(i);
            i++;
        } else {
            int16_t prevTop = stack.top();
            stack.pop();
            int32_t currSqr = column[prevTop] * (stack.empty() ? i : i - stack.top() - 1);

            if (currSqr > maxLineSqr) {
                maxLineSqr = currSqr;
            }
        }
    }
    return  maxLineSqr;
}

int main() {
    cin >> LENGTH >> WIDTH;
    vector<vector<int8_t> > rectangle;
    ReadData(rectangle);

    vector<int16_t> columnCount(WIDTH);
    int32_t maxSqr = 0;

    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (rectangle[i][j] == '0') {
                columnCount[j]++;
            } else {
                columnCount[j] = 0;
            }
        }
        int32_t tmpSqr = MaxSqrInLine(columnCount);
        if (tmpSqr > maxSqr) {
            maxSqr = tmpSqr;
        }
    }

    cout << maxSqr << endl;

    return 0;
}