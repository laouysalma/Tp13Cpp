#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <concepts>
using namespace std;

template<typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> convertible_to<bool>;
};

template<Sortable T, typename Comp = less<T>>
void quickSort(vector<T>& v, int left, int right, Comp comp = Comp{}) {
    if (left >= right) return;
    int i = left, j = right;
    T pivot = v[(left + right) / 2];
    while (i <= j) {
        while (comp(v[i], pivot)) i++;
        while (comp(pivot, v[j])) j--;
        if (i <= j) {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    if (left < j) quickSort(v, left, j, comp);
    if (i < right) quickSort(v, i, right, comp);
}

template<Sortable T, typename Comp = less<T>>
void quickSort(vector<T>& v, Comp comp = Comp{}) {
    if (!v.empty()) quickSort(v, 0, v.size() - 1, comp);
}

struct Asc {
    template<typename T>
    bool operator()(const T& a, const T& b) const { return a < b; }
};

struct Desc {
    template<typename T>
    bool operator()(const T& a, const T& b) const { return b < a; } 
};

struct Etudiant {
    string nom;
    int note;
    bool operator<(const Etudiant& autre) const { return note < autre.note; }
};

int main() {
    vector<int> v1 = {54, 2, 9, 1, 3};
    quickSort(v1, Asc{});
    cout << "Tri croissant int : ";
    for (auto& x : v1) cout << x << " ";
    cout << endl;

    vector<int> v2 = {5, 2, 9, 1, 3};
    quickSort(v2, Desc{});
    cout << "Tri decroissant int : ";
    for (auto& x : v2) cout << x << " ";
    cout << endl;

    vector<string> mots = {"salle", "arbre", "zombi", "banane"};
    quickSort(mots, Asc{});
    cout << "Tri croissant string : ";
    for (auto& m : mots) cout << m << " ";
    cout << endl;

    vector<Etudiant> etu = {{"salma", 21}, {"fati", 21}, {"hiba", 19}};
    quickSort(etu, Desc{});
    cout << "Tri decroissant note : ";
    for (auto& e : etu) cout << e.nom << "(" << e.note << ") ";
    cout << endl;

    system("pause");
    return 0;
}
