#include <iostream>
using namespace std;

//Задача: есть соревнования участники и оценки от разных судей, надо уметь брать одно какое-то соревнование и сортировать участников по оценкам какого то судьи

// int*** хранит оценки: соревнование -> участник -> судья.
//Здесь я использую void* чтобы мы могли делать сортировку какую угодно, например как строк,
//как double, по первому судье и тд. Плюс если проект более глобальный то жту же сортирку можно использовать для разных целей,
//и удобно чтобы она могла работать с любыми типами данных

bool cmp(void* a, void* b) {
    int* x = (int*)a;
    int* y = (int*)b;

    return x[0] > y[0];
}

void sort(void** arr, int n, bool (*cmp)(void*, void*)) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (cmp(arr[j], arr[i])) {
                void* tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int*** scores = new int**[n];
    for (int i = 0; i < n; ++i) {
        scores[i] = new int*[m];
        for (int j = 0; j < m; ++j) {
            scores[i][j] = new int[k];
            for (int t = 0; t < k; ++t) {
                cin >> scores[i][j][t];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        void** rank = new void*[m];
        for (int j = 0; j < m; ++j) {
            rank[j] = scores[i][j];
        }
        sort(rank, m, cmp);
        cout << "Competition " << i + 1 << ":\n";
        for (int j = 0; j < m; ++j) {
            int* marks = (int*)rank[j];
            for (int t = 0; t < k; ++t) {
                cout << marks[t] << ' ';
            }
            cout << '\n';
        }
        delete[] rank;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            delete[] scores[i][j];
        }
        delete[] scores[i];
    }
    delete[] scores;
}

//пример:
/* на тест
2 3 2
10 20
30 15
20 25
50 40
70 60
60 80

дается ответ:
Competition 1:
30 15
20 25
10 20
Competition 2:
70 60
60 80
50 40*/
