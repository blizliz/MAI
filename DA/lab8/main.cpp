#include <iostream>
#include <vector>

int main() {
    //3
    //3 2 1

    int32_t n;
    std::cin >> n;
    std::vector<int8_t> seq(n);
    for (int32_t i = 0; i < n; i++) {
        std::cin >> seq[i];
    }

    int32_t count1 = 0, count2 = 0;
    for (int32_t i = 0; i < n; i++) {
        switch(seq[i]) {
            case '1':
                count1++;
                break;
            case '2':
                count2++;
                break;
            default:
                break;
        }
    }

    int32_t res = 0;

    for (int32_t i = 0; i < n; i++) {
        if (i < count1) {                 //зона 1
            if (seq[i] == '3') {
                for (int32_t j = n - 1; j >= count1; j--) {
                    if (seq[j] == '1') {
                        std::swap(seq[i], seq[j]);
                        ++res;
                        break;
                    }
                }
            } else if (seq[i] == '2') {
                for (int32_t j = count1; j < n; j++) {
                    if (seq[j] == '1') {
                        std::swap(seq[i], seq[j]);
                        ++res;
                        break;
                    }
                }
            }
        } else if (i < count1 + count2) { //зона 2
            if (seq[i] == '3') {
                for (int32_t j = count1 + count2; j < n; j++) {
                    if (seq[j] == '2') {
                        std::swap(seq[i], seq[j]);
                        ++res;
                        break;
                    }
                }
            }
        }
    }

    std::cout << res << '\n';

    return 0;
}