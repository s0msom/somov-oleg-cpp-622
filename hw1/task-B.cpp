#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

bool deposit(int& sum) {
    int k;
    cin >> k;
    if (k <= 0) {
        return false;
    }
    sum += k;
    return true;
}

bool withdraw(int& sum) {
    int k;
    cin >> k;
    if (k <= 0) {
        return false;
    }
    if (sum < k) {
        return false;
    }
    sum -= k;
    return true;
}

bool balance(int& sum) {
    cout << sum << '\n';
    return true;
}

bool reset(int& sum) {
    sum = 0;
    return true;
}

bool inc(int& sum) {
    sum++;
    return true;
}

bool equal(char* a, char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        ++i;
    }
    return a[i] == b[i];
}

int main() {
    char (name[5][10]){"deposit","withdraw","balance","reset","inc"};
    bool (*func[5])(int&){&deposit,&withdraw,&balance,&reset,&inc};
    char stop[10]{"stop"};
    int sum = 0;
    while (true) {
        char in[10];
        cin >> setw(10) >> in;
        // cout << in << ' ' << stop << '\n';
        if (equal(stop, in)) {
            break;
        }
        int cl = 0;
        for (int i = 0; i < 5; ++i) {
            if (equal(in, name[i])) {
                // cout << in << ' ' << name[i] << '\n';
                cl++;
                bool res = func[i](sum);
                if (!res) {
                    cout << "error" << '\n';
                    break;
                }
            }
        }
        if (!cl) {
            cout << "error" << '\n';
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
