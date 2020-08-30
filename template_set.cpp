#include <iostream>
using namespace std;

template<class T, class F=Comparator<T>> class set {
    T* p;
    int size;
    F cmp;
public:
    set();
    set(const set& a);
    friend ostream& operator<<(ostream&, const  set<U, G>&);
    set& operator=(const set& s);
    void add(T a);
    void deleteEl(T a);
    int nr_elemente() const;
    bool exist(const T a);
    template<typename U, typename G>
};

template<class T, class F>  //constructor fara parametrii
set<T, F>::set() {
    p = NULL;
    size = 0;
}

template<class T, class F>  //constructor de copiere
set<T, F>::set(const set& a) {
    p = new T[a.size];
    for (int i = 0;i < a.size; i++)
        p[i] = a.p[i];
    size =a.size;
}

template<class T, class F>  //supraincarcare operator de afisare
ostream& operator<<(ostream& out, const  set<T, F>& s) {
    out << s.size << endl;
    for (int i = 0; i < s.size; i++)
        out << s.p[i] << " ";
    cout << endl;
    return out;
}

template<class T, class F>  //operatorul de atribuire
set<T, F>& set<T, F>::operator=(const set& s){
    delete[] p;
    p = new T[s.size];
    for (int i = 0;i < s.size; i++)
        p[i] = s.p[i];
    size = s.size;
    return *this;
}

template<class T, class F>  //metoda de adaugare element in set
void set<T, F>::add(T a) {
    bool ok=false;
    for (int i = 0; i < size; i++)
        if (cmp(p[i], a) == true)
            ok = true;
    if (ok == false)
    {
        set<T> aux;
        aux.p = new T[size + 1];
        for (int i = 0; i < size; i++)
            aux.p[i] = p[i];
        aux.p[size] = a;
        aux.size = size + 1;
        *this = aux;
    }
}

template<class T, class F>  //metoda de stergere element din set
void set<T, F>::deleteEl(T a) {
    bool ok = false;
    for (int i = 0; i < size; i++)
        if (cmp(p[i], a) == true)
            ok = true;
    if (ok == true) {
        for (int i = 0; i < size; i++) {
            if (p[i] == a)
            {
                for (int j = i; j < size - 1; j++)
                    p[j] = p[j + 1];
                break;
            }
        }
        size--;
    }
}

template<class T, class F>  //metoda de afisare a numarului de elemente din set
int set<T, F>::nr_elemente() const {
    return size;
}

template<class T, class F>  //metoda de verificare daca un element se regaseste in set
bool set<T, F>::exist(const T a) {
    bool ok = false;
    for (int i = 0; i < size; i++)
        if (cmp(p[i], a) == true)
            ok = true;
    return ok;
}

template <class T> class Comparator {
public:
    bool operator () (const T& x, const T& y) {
        if (x == y)
            return true;
        else
            return false;
    }
};

template <> class Comparator<int> {
public:
    bool operator () (const int& x, const int& y) { //verificarea paritatii a cate doua numere
        if (x%2 == 0 && y%2 == 0 || x%2 != 0 && y%2 != 0)
            return true;
        else
            return false;
    }
};

int main()
{
    set<char> a;
    a.add('m');
    a.add('r');
    a.add('c');
    cout << a;
    a.deleteEl('c');
    cout << a;
    cout << a.exist('r') <<' '<< a.exist('s') << endl;
    set<int> b;
    for (int i = 0; i < 5; i++)
        b.add(i);
    cout << b;
    b.deleteEl(3);
    cout << b;
}
