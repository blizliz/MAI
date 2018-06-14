#include <iostream>
#include <cstring>
#include "TAVLTree.h"

using namespace std;

const size_t LEN_KEY = 256;  // Max length of key-string

void ReadLine(char *comand, char *string, unsigned long long *num);
char ToLower(char ch);
bool IsLetter(char ch);

int main() {

    TAVLTree avltree;

    while (true) {
        TData data;

        char comand;
        char buffer[LEN_KEY + 1];
        unsigned long long number;

        ReadLine(&comand, buffer, &number);

        if (comand == 'Q') {
            break;
        }

        switch (comand) {
            case '+':
            {
                data.key = new char[strlen(buffer) + 1];
                strcpy(data.key, buffer);
                data.value = number;

                if (!avltree.Search(data)) {
                    avltree.Insert(data);
                    printf("OK\n");
                }
                else {
                    printf("Exist\n");
                }

                delete[] data.key;
                break;
            }
            case '-':
            {
                data.key = new char[strlen(buffer) + 1];
                strcpy(data.key, buffer);

                if (!avltree.Search(data)) {
                    printf("NoSuchWord\n");
                }
                else {
                    avltree.Delete(data);

                    printf("OK\n");
                }
                delete[] data.key;
                break;
            }
            case 'S':
            {
                if (avltree.Serialize(buffer)) {
                    printf("OK\n");
                }
                else {
                    printf("ERROR: Couldn't create file\n");
                }
                break;
            }
            case 'L':
            {
                if (avltree.Deserialize(buffer)) {
                    printf("OK\n");
                }
                else {
                    printf("ERROR: Couldn't load file\n");
                }
                break;
            }
            case '?':
            {
                data.key = new char[strlen(buffer) + 1];
                strcpy(data.key, buffer);
                if (!avltree.Search(data)) {
                    printf("NoSuchWord\n");
                }
                else {
                    printf("OK: %llu\n",data.value);
                }
                delete[] data.key;
                break;
            }
            default:
            {
                return 0;
                break;
            }
        };
    }
    return 0;
}

void ReadLine(char *comand, char *string, unsigned long long *num) {

    size_t idx = 0;
    char ch;
    ch = getchar();

    if (ch == EOF) {
        *comand = 'Q';
        return;
    }

    if (ch == '+' || ch == '-') {

        *comand = ch;

        getchar();

        while (true) {
            ch = ToLower(getchar());

            if (!IsLetter(ch)) {
                break;
            }

            string[idx++] = ch;
        }

        string[idx] = '\0';

        if (*comand == '+') {
            *num = 0;
            while ((ch = getchar()) != '\n') {
                *num = *num * 10 + ch - '0';
            }
        }
    }
    else if (ch == '!') {

        getchar();

        string[0] = ch;

        while ((ch = getchar()) != ' ')
        {
            string[idx++] = ch;
        }

        string[idx] = '\0';
        idx = 0;

        *comand = string[0];

        while ((ch = getchar()) != '\n')
        {
            string[idx++] = ch;
        }

        string[idx] = '\0';

    }
    else {

        *comand = '?';
        string[0] = ToLower(ch);
        ++idx;

        while (true) {
            ch = ToLower(getchar());

            if (!IsLetter(ch)) {
                break;
            }

            string[idx++] = ch;
        }

        string[idx] = '\0';
    }
}

char ToLower(char ch) {
    return ch >= 'A' && ch <= 'Z' ? ch - 'A' + 'a' : ch;
}

bool IsLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}