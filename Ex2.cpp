#include <iostream>
using namespace std;

template<typename T, int N, int M>
class Matrice {
private:
    T data[N][M];
public:
    Matrice() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = 0;
            }
        }
    }

    Matrice(initializer_list<initializer_list<T>> init) {
        int i = 0;
        for (auto& ligne : init) {
            int j = 0;
            for (auto& val : ligne) {
                if (i < N && j < M)
                    data[i][j] = val;
                j++;
            }
            i++;
        }
    }

    Matrice operator+(const Matrice& autre) const {
        Matrice resultat;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] = data[i][j] + autre.data[i][j];
            }
        }
        return resultat;
    }

    template<int P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {
        Matrice<T, N, P> resultat;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < P; ++j)
                for (int k = 0; k < M; ++k)
                    resultat.data[i][j] += data[i][k] * autre.data[k][j];
        return resultat;
    }

    friend ostream& operator<<(ostream& os, const Matrice& m) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j)
                os << m.data[i][j] << " ";
            os << endl;
        }
        return os;
    }
};

int main() {
    Matrice<int, 2, 2> m1{{ {1, 2}, {3, 4} }};
    Matrice<int, 2, 2> m2{{ {5, 6}, {7, 8} }};

    cout << "Addition : " << endl << (m1 + m2) << endl;
    cout << "Produit m1 * m2 : " << endl << (m1 * m2) << endl;

    Matrice<double, 2, 2> m3{{ {1.05, 2.23}, {4.5, 12.32} }};
    Matrice<double, 2, 2> m4{{ {14.3, 15.34}, {120.5, 41.5} }};

    cout << "Produit m3 * m4 : " << endl << (m3 * m4) << endl;
}
