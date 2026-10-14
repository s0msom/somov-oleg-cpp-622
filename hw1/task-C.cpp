#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void clear(char (*tablo)[10]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            tablo[i][j] = ' ';
        }
    }
}

bool can(int x, int y) {
    if (0 <= x && x < 10 && y >= 0 && y < 5) {
        return true;
    }
    return false;
}

bool put(char (*tablo)[10], int x, int y, char z) {
    if (can(x, y)) {
        tablo[y][x] = z;
        return true;
    }
    return false;
}

bool text(char (*tablo)[10], int x, int y, char* txt, int len) {
    if (!(can(x, y) && x + len - 1 < 10)) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        tablo[y][x + i] = txt[i];
    }
    return true;
}

void print(char (*tablo)[10]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << tablo[i][j];
        }
        cout << '\n';
    }
}

int main() {
    char tablo[5][10];
    clear(tablo);
    while (true) {
        char in[10];
        cin >> setw(10) >> in;
        if (in[0] == 'q') {
            break;
        }
        if (in[0] == 'c') {
            clear(tablo);
            continue;
        }
        if (in[0] == 't') {
            int x;
            int y;
            char txt[10];
            cin >> x >> y;
            cin >> setw(10) >> txt;
            int sz = 0;
            while (txt[sz] != '\0') {
                sz++;
            }
            if (!text(tablo, x, y, txt, sz)) {
                cout << "error" << '\n';
            }
            continue;
        }
        if (in[1] == 'u') {
            int x, y;
            char c;
            cin >> x >> y >> c;
            if (!put(tablo, x, y, c)) {
                cout << "error" << '\n';
            }
            continue;
        }
        print(tablo);
    }
}
