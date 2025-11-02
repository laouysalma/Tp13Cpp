#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class ArrayDyn {
private:
    T* data;           
    size_t taille;     
    size_t capacite;   

public:
    ArrayDyn(size_t cap = 10)
        : data(new T[cap]), taille(0), capacite(cap) {}

    ArrayDyn(const ArrayDyn& other)
        : data(new T[other.capacite]), taille(other.taille), capacite(other.capacite) {
        for (size_t i = 0; i < taille; ++i)
            data[i] = other.data[i];
    }

    ArrayDyn& operator=(const ArrayDyn& other) {
        if (this != &other) { 
            delete[] data;
            capacite = other.capacite;
            taille = other.taille;
            data = new T[capacite];
            for (size_t i = 0; i < taille; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~ArrayDyn() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (taille == capacite) resize(capacite * 2);  
        data[taille++] = value;
    }

    void pop_back() {
        if (taille > 0) taille--;
    }

    T& operator[](size_t index) {
        if (index >= taille) throw out_of_range("Index invalide !");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= taille) throw out_of_range("Index invalide !");
        return data[index];
    }

    size_t size() const { return taille; }
    size_t capacity() const { return capacite; }

private:
    void resize(size_t newCap) {
        T* temp = new T[newCap];
        for (size_t i = 0; i < taille; ++i)
            temp[i] = data[i];
        delete[] data;
        data = temp;
        capacite = newCap;
    }

public:
     class Iterator {
        T* ptr;
    public:
        Iterator(T* p = nullptr) : ptr(p) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        Iterator& operator--() { --ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + taille); }
};

class Produit {
private:
    string nom;
    double prix;
public:
    Produit(string n="" , double p=0.0 ) : nom(n), prix(p) {}
    friend ostream& operator<<(ostream& os, const Produit& p) {
        os << p.nom << "  " << p.prix << " DH";
        return os;
    }
};

int main() {
    ArrayDyn<int> tabInt;
    tabInt.push_back(10);
    tabInt.push_back(20);   
    for (auto &e : tabInt)
        cout << e << " "<<endl;
    
    ArrayDyn<string> tabStr;
    tabStr.push_back("Bonjour");
    tabStr.push_back("Salma");
    for (auto &st : tabStr)
        cout << st << " "<<endl;

    ArrayDyn<Produit> tabProd;
    tabProd.push_back(Produit("Clé USB", 70.0));
    tabProd.push_back(Produit("Casque", 150.0));
    for (auto &produit : tabProd)
        cout<< produit<<" "<<endl;

    cout<<"apres supression d un entier"<<endl;
    tabInt.pop_back();
    for (auto &e : tabInt)
         cout << e << " "<<endl;

    cout<<tabStr[1]<<endl;
    
    try{
        cout<<tabProd[4]<<endl;
    }catch(const out_of_range&e){
        cout<<e.what()<<endl;
    }
    
   return 0; 
}
   
