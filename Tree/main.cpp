#include <iostream>
using namespace std;

template <typename T> class Nod;
template <typename T> class Nod_ABC;
template <typename T> class Nod_fiu_frate;
template <typename T> class Arbore;
template <typename T> class ABC;
template <typename T> class AB_oarecare;

//***************************************************************************************************************
template <typename T> class Nod {
protected:
    T info;
public:
    explicit Nod(int x = 0) {
        info = x;
    }

    Nod(const Nod &x) {
        info = x.info;
    }

    int GetInfo() const {
        return info;
    }

    void SetInfo(const T & x) {
        info = x;
    }

    void SetInfo(const Nod & x) {
        info = x.info;
    }

    friend istream &operator >> (istream &in, Nod &x) {
        in >> x.info;
        return in;
    }

    friend ostream &operator << (ostream &out, Nod &x) {
        out << x.info;
        return out;
    }

    Nod & operator = (const Nod &x) {
        info = x.info;
        return *this;
    }

    Nod & operator = (const T &x) {
        info = x;
        return *this;
    }

    const bool operator < (const Nod &x) {
        return info < x.info;
    }

    const bool operator < (const T &x) {
        return info < x;
    }

    const bool operator == (const Nod &x) {
        return info == x.info;
    }

    const bool operator == (const T &x) {
        return info == x;
    }

    const bool operator != (const Nod &x) {
        return info != x.info;
    }

    const bool operator != (const T &x) {
        return info != x;
    }
};

//***************************************************************************************************************
template <typename T> class Nod_fiu_frate : public Nod <T> {
protected:
    int copii;
    Nod_fiu_frate *frate, *fiuStang;
public:
    Nod_fiu_frate(int c = 0, Nod_fiu_frate *fr = nullptr, Nod_fiu_frate *f = nullptr) : Nod<T>(){
        copii = c;
        frate = fr;
        fiuStang = f;
    }

    int GetCopii() const {
        return copii;
    }

    Nod_fiu_frate * GetFiuStang() const {
        return fiuStang;
    }

    Nod_fiu_frate * GetFrate() const {
        return frate;
    }

    void SetFiuStang(Nod_fiu_frate * nod) {
        fiuStang = nod;
    }

    void SetFrate(Nod_fiu_frate * nod) {
        frate = nod;
    }

    void SetCopii(const int & x) {
        copii = x;
    }

    friend istream &operator >> (istream &in, Nod_fiu_frate & x) {
        in >> x.info >> x.copii;
        x.fiuStang = nullptr;
        x.frate = nullptr;
        return in;
    }

    Nod_fiu_frate &operator = (const Nod_fiu_frate & x) {
        this->info = x.info;
        copii = x.copii;
        frate = x.frate;
        fiuStang = x.fiuStang;
        return *this;
    }

    ~Nod_fiu_frate() {}
};

//***************************************************************************************************************
template <typename T> class Nod_ABC : public Nod <T> {
private:
    Nod_ABC *st, *dr;
public:
    Nod_ABC(int x = 0, Nod_ABC *a = nullptr, Nod_ABC *b = nullptr) : Nod<T>(x) {
        st = a;
        dr = b;
    }

    Nod_ABC * GetSt() const {
        return st;
    }

    Nod_ABC * GetDr() const {
        return dr;
    }

    void SetSt(Nod_ABC * nod = nullptr) {
        st = nod;
    }

    void SetDr(Nod_ABC * nod = nullptr) {
        dr = nod;
    }

    friend istream & operator >> (istream & in, Nod_ABC & x) {
        in >> x.info;
        x.st = nullptr;
        x.dr = nullptr;

        return in;
    }

    Nod_ABC & operator = (const Nod_ABC &x) {
        this->info = x.info;
        st = x.st;
        dr = x.dr;
        return *this;
    }

    ~Nod_ABC() {
        delete st;
        delete dr;
    }
};

//***************************************************************************************************************
template <typename T> class Arbore {  // clasa abstracta
protected:
    int nr_noduri;
public:
    virtual void AfisareParcurgereSiListeFii() = 0;
    ~Arbore() {};
};

//***************************************************************************************************************
template <typename T>
void rec(Nod_ABC<T> *actual, int &last, Nod_ABC<T> ** v) {
    if (actual != nullptr) {
        v[last] = actual;
        last ++;
        rec(actual->GetSt(), last, v);
        rec(actual->GetDr(), last, v);
    }
}

template <typename T>
void rec2(Nod_ABC<T> *actual, int &last, Nod_ABC<T> ** v) {
    if (actual != nullptr) {
        rec2(actual->GetSt(), last, v);
        v[last] = actual;
        last ++;
        rec2(actual->GetDr(), last, v);
    }
}

template <typename T>
void rec3(Nod_ABC<T> *actual, int &last, Nod_ABC<T> ** v) {
    if (actual != nullptr) {
        rec3(actual->GetSt(), last, v);
        rec3(actual->GetDr(), last, v);
        v[last] = actual;
        last ++;
    }
}

template <typename T>
void rec4(Nod_ABC<T> * actual) {
    if (actual->GetSt() != nullptr) {
        rec4(actual->GetSt());
    }

    if (actual->GetDr()) {
        rec4(actual->GetDr());
    }

    delete actual;
}

template <typename T>
Nod_ABC<T> * rec5(const Nod_ABC<T> *actual) {
    Nod_ABC<T> * nod = new Nod_ABC<T>;
    nod->SetInfo(actual->GetInfo());

    if (actual->GetSt() != nullptr) {
        nod->SetSt(rec3(actual->GetSt()));
    }

    if (actual->GetDr()) {
        nod->SetDr(rec3(actual->GetDr()));
    }

    return nod;
}

template <typename T> class ABC : virtual public Arbore<T> {
    Nod_ABC<T> *rad;
public:
    ABC(Nod_ABC<T> *r = nullptr) {
        rad = r;
    }

    friend istream & operator >> (istream & in, ABC & A) {
        in >> A.nr_noduri;

        for (int i = 0; i < A.nr_noduri; i ++) {
            Nod_ABC<T> * x = new Nod_ABC<T>;
            in >> * x;
            A.push(x);
        }

        return in;
    }

    friend ostream & operator << (ostream & out, ABC & A) {
        out << "Numarul de noduri ale arborelui: " << A.nr_noduri << endl;

        int first = 0, last = 1;
        Nod_ABC<T> * v[A.nr_noduri + 1];
        v[first] = A.rad;
        while (first < A.nr_noduri) {
            Nod_ABC<T> * tata = v[first];
            first ++;
            out << *tata << ": ";

            if (tata->GetSt() != nullptr) {
                v[last] = tata->GetSt();
                out << *v[last] << " ";
                last ++;
            } else {
                out << ". ";
            }

            if (tata->GetDr() != nullptr) {
                v[last] = tata->GetDr();
                out << *v[last] << " ";
                last ++;
            } else {
                out << ".";
            }

            out << endl;
        }

        return out;
    }

    ABC & operator = (const ABC & x) {
        erase();
        rad = rec5(x.rad);
        return * this;
    }

    const bool operator == (const ABC & x) {
        if (this->nr_noduri != x.nr_noduri) {
            return false;
        }

        Nod_ABC<T> ** v1 = Inordine(), ** v2 = x.Postordine();
        Nod_ABC<T> ** w1 = Inordine(), ** w2 = x.Postordine();
        for (int i = 0; i < this->nr_noduri; i ++) {
            if (*v1[i] != *v2[i] || *w1[i] != *w2[i]) {
                delete [] v1;
                delete [] v2;
                delete [] w1;
                delete [] w2;
                return false;
            }
        }

        delete [] v1;
        delete [] v2;
        delete [] w1;
        delete [] w2;
        return true;
    }

    const bool operator != (const ABC & x) {
        return !(* this == x);
    }

    const bool operator < (const ABC & x) {
        if(this->nr_noduri >= x.nr_noduri) {
            return false;
        }

        Nod_ABC<T> ** v = this->Inordine(), ** w = x.Inordine();

        for (int i = 0; i < this->nr_noduri; i ++) {
            if (v[i] >= w[i]) {
                delete [] v;
                delete [] w;
                return false;
            }
        }

        return true;
    }

    void push(Nod_ABC<T> * x) {
        Nod_ABC<T> *actual = new Nod_ABC<T>(x->GetInfo());
        if (rad == nullptr) {
            rad = actual;
            return ;
        }

        delete actual;
        actual = rad;

        while (actual != nullptr) {
            if (actual->GetInfo() > x->GetInfo()) {
                if (actual->GetSt() == nullptr) {
                    actual->SetSt(x);
                    return ;
                }
                actual = actual->GetSt();
            } else {
                if (actual->GetDr() == nullptr) {
                    actual->SetDr(x);
                    return ;
                }
                actual = actual->GetDr();
            }
        }
    }

    Nod_ABC<T> ** Preordine() {
        int last = 0;
        Nod_ABC<T> ** v = new Nod_ABC<T> * [this->nr_noduri + 1];
        rec(rad, last, v);

        return v;
    }

    Nod_ABC<T> ** Inordine() {
        int last = 0;
        Nod_ABC<T> ** v = new Nod_ABC<T> * [this->nr_noduri + 1];
        rec2(rad, last, v);

        return v;
    }

    Nod_ABC<T> ** Postordine() {
        int last = 0;
        Nod_ABC<T> ** v = new Nod_ABC<T> * [this->nr_noduri + 1];
        rec3(rad, last, v);

        return v;
    }

    void AfisareParcurgere(Nod_ABC<T> ** v) {
        for (int i = 0; i < this->nr_noduri; i ++) {
            cout << *v[i] << " ";
        }
        cout << endl;
    }

    virtual void AfisareParcurgereSiListeFii() {
        cout << *this;
    }

    bool empty() {
        return rad == nullptr;
    }

    void erase() {
        if (empty()) {
            return ;
        }

        rec4(rad);
    }

    ~ABC() {
        erase();
    }
};

//***************************************************************************************************************
template <typename T>
void rec(Nod_fiu_frate<T> *actual, int &last, Nod_fiu_frate<T> ** v) {
    while (actual != nullptr) {
        v[last] = actual;
        last ++;
        rec(actual->GetFiuStang(), last, v);
        actual = actual->GetFrate();
    }
}

template <typename T>
void rec2(Nod_fiu_frate<T> *actual, int h, int &hmax) {
    if (hmax < h) {
        hmax = h;
    }

    while (actual != nullptr) {
        rec2(actual->GetFiuStang(), h + 1, hmax);
        actual = actual->GetFrate();
    }
}

template <typename T>
Nod_fiu_frate<T> * rec3(const Nod_fiu_frate<T> *actual) {
    Nod_fiu_frate<T> * nod = new Nod_fiu_frate<T>;
    nod->SetInfo(actual->GetInfo());

    if (actual->GetFrate() != nullptr) {
        nod->SetFrate(rec3(actual->GetFrate()));
    }

    if (actual->GetFiuStang()) {
        nod->SetFiuStang(rec3(actual->GetFiuStang()));
    }

    return nod;
}

template <typename T>
void rec4(Nod_fiu_frate<T> * actual) {
    if (actual->GetFrate() != nullptr) {
        rec4(actual->GetFrate());
    }

    if (actual->GetFiuStang()) {
        rec4(actual->GetFiuStang());
    }

    delete actual;
}

template <typename T> class AB_oarecare : virtual public Arbore<T> {
    Nod_fiu_frate<T> * rad;
public:
    AB_oarecare(Nod_fiu_frate<T> * r = nullptr) {
        rad = r;
    }

    friend istream & operator >> (istream &in, AB_oarecare & A) {
        A.rad = new Nod_fiu_frate<T>;
        in >> A.nr_noduri >> *A.rad;

        int first = 0, last = 1;
        Nod_fiu_frate<T> * v[A.nr_noduri + 1];
        v[first] = A.rad;
        while (last < A.nr_noduri) {
            Nod_fiu_frate<T> * tata = v[first];
            first ++;
            if (tata->GetCopii() > 0) {
                v[last] = new Nod_fiu_frate<T>;
                in >> *v[last];
                tata->SetFiuStang(v[last]);
                last ++;
            }

            for (int j = 1; j < tata->GetCopii() && last < A.nr_noduri; j ++, last ++) {
                v[last] = new Nod_fiu_frate<T>;
                in >> *v[last];
                v[last - 1]->SetFrate(v[last]);
            }
        }

        return in;
    }

    friend ostream & operator << (ostream & out, AB_oarecare & A) {
        out << "Numarul de noduri ale arborelui: " << A.nr_noduri << endl;

        int first = 0, last = 1;
        Nod_fiu_frate<T> * v[A.nr_noduri + 1];
        v[first] = A.rad;
        while (first < A.nr_noduri) {
            Nod_fiu_frate<T> * tata = v[first];
            first ++;
            out << *tata << ": ";

            if (tata->GetFiuStang() != nullptr) {
                v[last] = tata->GetFiuStang();
                out << *v[last] << " ";
                last ++;
            }

            while (v[last - 1]->GetFrate() != nullptr) {
                v[last] = v[last - 1]->GetFrate();
                out << *v[last] << " ";
                last ++;
            }
            out << endl;
        }

        return out;
    }

    AB_oarecare & operator = (const AB_oarecare & x) {
        erase();
        rad = rec3(x.rad);
        return * this;
    }

    AB_oarecare operator + (const AB_oarecare & x) const {
        AB_oarecare a;
        a.rad = rec3(rad);
        Nod_fiu_frate<T> *actual = a.rad;
        if (a.rad->GetFiuStang() != nullptr) {
            actual = a.rad->GetFiuStang();
        }

        while (actual->GetFrate() != nullptr) {
            actual = actual->GetFrate();
        }

        actual->SetFrate(rec3(x.rad));
        a.rad->SetCopii(a.rad->GetCopii() + 1);
        a.nr_noduri += x.nr_noduri;

        return a;
    }

    const bool operator == (const AB_oarecare & x) {
        if (this->nr_noduri != x.nr_noduri) {
            return false;
        }

        Nod_fiu_frate<T> ** v1 = ParcurgereInLatime(), ** v2 = x.ParcurgereInLatime();
        Nod_fiu_frate<T> ** w1 = ParcurgereInAdancime(), ** w2 = x.ParcurgereInAdancime();
        for (int i = 0; i < this->nr_noduri; i ++) {
            if (*v1[i] != *v2[i] || *w1[i] != *w2[i]) {
                delete [] v1;
                delete [] v2;
                delete [] w1;
                delete [] w2;
                return false;
            }
        }

        delete [] v1;
        delete [] v2;
        delete [] w1;
        delete [] w2;
        return true;
    }

    const bool operator != (const AB_oarecare & x) {
        return !(* this == x);
    }

    const bool operator < (const AB_oarecare & x) {
        return this->nr_noduri < x.nr_noduri;
    }

    Nod_fiu_frate<T> ** ParcurgereInLatime() const {
        int first = 0, last = 1;
        Nod_fiu_frate<T> ** v = new Nod_fiu_frate<T> * [this->nr_noduri + 1];
        v[first] = rad;
        while (first < this->nr_noduri) {
            Nod_fiu_frate<T> * tata = v[first];
            first ++;

            if (tata->GetFiuStang() != nullptr) {
                v[last] = tata->GetFiuStang();
                last ++;
            }

            while (v[last - 1]->GetFrate() != nullptr) {
                v[last] = v[last - 1]->GetFrate();
                last ++;
            }
        }
        return v;
    }

    Nod_fiu_frate<T> ** ParcurgereInAdancime() const {
        int last = 0;
        Nod_fiu_frate<T> ** v = new Nod_fiu_frate<T> * [this->nr_noduri + 1];
        rec(rad, last, v);

        return v;
    }

    void AfisareParcurgere(Nod_fiu_frate<T> ** v) {
        for (int i = 0; i < this->nr_noduri; i ++) {
            cout << *v[i] << " ";
        }
        cout << endl;
    }

    virtual void AfisareParcurgereSiListeFii() {
        cout << *this;
    }

    int Inaltime() {
        int h = 0;
        rec2(rad, 0, h);
        return h;
    }

    int * DeterminareFrunze() {
        Nod_fiu_frate<T> ** v = ParcurgereInLatime();
        int n = 0;
        for (int i = 0; i < this->nr_noduri; i ++) {
            if (v[i]->GetCopii() == 0) {
                n ++;
            }
        }

        int * w = new int [n + 1], j = 1;
        w[0] = n;
        for (int i = 0; i < this->nr_noduri; i ++) {
            if (v[i]->GetCopii() == 0) {
                w[j] = v[i]->GetInfo();
                j ++;
            }
        }

        return w;
    }

    void AfisareFrunze() {
        int * v = DeterminareFrunze();
        for (int i = 1; i <= v[0]; i ++) {
            cout << v[i] << " ";
        }
        cout << endl;
    }

    bool empty() {
        return rad == nullptr;
    }

    void erase() {
        if (empty()) {
            return ;
        }

        rec4(rad);
    }

    ~AB_oarecare() {
        erase();
    }
};

int main() {
    // Citirea si afisarea unui arbore oarecare
    AB_oarecare<int> a;
    cin >> a;
    a.AfisareParcurgereSiListeFii();

    // Parcurgerea pe niveluri
    Nod_fiu_frate<int> ** v = a.ParcurgereInLatime(), ** w = a.ParcurgereInAdancime();
    cout << "Parcurgerea in latime a arborelui: ";
    a.AfisareParcurgere(v);     delete [] v;
    cout << "Parcurgerea in adancime a arborelui: ";
    a.AfisareParcurgere(w);     delete [] w;

    // Determinarea inaltimii arborelui
    cout << "Inaltimea arborelui: " << a.Inaltime() << "\n";

    // Afisarea listei frunzelor
    cout << "Lista frunzelor: ";
    a.AfisareFrunze();

    //Citirea si afisarea unui arbore binar de cautare
    ABC<int> b;
    cin >> b;
    b.AfisareParcurgereSiListeFii();

    // Parcurgerile unui ABC
    cout << "Parcurere in preordine: ";
    Nod_ABC<int> ** vv = b.Preordine();   b.AfisareParcurgere(vv);   delete [] vv;
    cout << "Parcurgere in inordine: ";
    vv = b.Inordine();   b.AfisareParcurgere(vv);               delete [] vv;
    cout << "Parcurgere in postordine: ";
    vv = b.Postordine();   b.AfisareParcurgere(vv);             delete [] vv;

    return 0;
}
