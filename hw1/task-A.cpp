#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

int count_below_zero(const int* a, int sz) {
    int count = 0;
    for (int i = 0; i < sz; ++i) {
        if (a[i] < 0) count++;
    }
    return count;
}

int* min_max(const int* a, int sz) {
    int mn = a[0];
    int mx = a[0];
    for (int i = 1; i < sz; ++i) {
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
    }
    int* ans = new int[2];
    ans[0] = mn;
    ans[1] = mx;
    return ans;
}

double mid(const int* a, int sz) {
    int sm = 0;
    for (int i = 0; i < sz; ++i) {
        sm += a[i];
    }
    return (double)sm / sz;
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << fixed << setprecision(1) << mid(a, n) << '\n';
    int* mn_mx = min_max(a, n);
    cout << mn_mx[0] << ' ' << mn_mx[1] << '\n';
    cout << count_below_zero(a, n);
    delete[] a;
    delete[] mn_mx;
    return 0;
}
