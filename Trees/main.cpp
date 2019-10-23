#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define timp_calcat_pantaloni 90
#define timp_calcat_camasa 120
#define timp_calcat_rochie 100
#define timp_calcat_sacouri 150

#define detergent_fix 200
#define detergent_rest 100

#define capacitate_spalat 10
#define capacitate_stors 10
#define capacitate_uscat 30

#define durata_functionare_spalat 100
#define durata_functionare_stors 50
#define durata_functionare_uscat 30

enum Culori {inchise, deschise};
enum Tipuri {PANTALONI, ROCHIE, CAMASA, PALTON, GEACA, COSTUM};

class Masini {
    double spalat_usoare_deschise, spalat_usoare_inchise, spalat_grele_deschise, spalat_grele_inchise;
    double stors;
    int uscat;

public:
    Masini() {
        spalat_usoare_deschise = 0;
        spalat_usoare_inchise = 0;
        spalat_grele_deschise = 0;
        spalat_grele_inchise = 0;
        stors = 0;
        uscat = 0;
    }

    double Get_spalat_usoare_deschise() {
        return spalat_usoare_deschise;
    }

    void Set_spalat_usoare_deschise(double x = 0) {
        spalat_usoare_deschise = x;
    }

    double Get_spalat_usoare_inchise() {
        return spalat_usoare_inchise;
    }

    void Set_spalat_usoare_inchise(double x = 0) {
        spalat_usoare_inchise = x;
    }

    double Get_spalat_grele_deschise() {
        return spalat_grele_deschise;
    }

    void Set_spalat_grele_deschise(double x = 0) {
        spalat_grele_deschise = x;
    }

    double Get_spalat_grele_inchise() {
        return spalat_grele_inchise;
    }

    void Set_spalat_grele_inchise(double x = 0) {
        spalat_grele_inchise = x;
    }

    double Get_stors() {
        return stors;
    }

    void Set_stors(double x) {
        stors = x;
    }

    int Get_uscat() {
        return uscat;
    }

    void Set_uscat(int x) {
        uscat = x;
    }

} masina;

class Haine {
    bool culori;    // true = deschise, false = inchise
    string type;
    double greutate;
public:
    bool Get_culori() {
        return culori;
    }

    string Get_type() {
        return type;
    }

    double Get_greutate() {
        return greutate;
    }

    friend istream &operator >> (istream &in, Haine &h) {
        in >> h.type >> h.greutate >> h.culori;
        return in;
    }

    friend ostream &operator << (ostream &out, Haine &c) {
        out << c.type << " " << c.culori << " ";
        return out;
    }

    int Detergent_Spalare() {
        if (type == "PANTALONI" && !culori) {
            return detergent_fix * 2;
        } else if (type == "PANTALONI" || type == "CAMASA" || type == "ROCHIE") {
            return detergent_fix;
        } else {
            return detergent_rest * greutate;
        }
    }

    void Istoric() {
        int durata;
        if (type == "PANTALONI" || type == "CAMASA" || type == "ROCHIE") {
            durata = durata_functionare_spalat + durata_functionare_stors + durata_functionare_uscat;
        } else {
            durata = durata_functionare_spalat + durata_functionare_uscat;
        }

        cout << type << " " << greutate << "kg \nTotal detergent folosit: " << Detergent_Spalare() << "\n";
        cout << "Timp total petrecut in masini: " << durata + Timp_Calcat() << "\n";
    }

    void Spalat() {
        if (culori) {
            if (type == "PANTALONI" || type == "CAMASA" || type == "ROCHIE") {
                masina.Set_spalat_usoare_deschise(masina.Get_spalat_usoare_deschise() + greutate);
                if (masina.Get_spalat_usoare_deschise() >= capacitate_spalat / 2) {
                    // daca e mai mare greutatea ??????????????????????????????????????????????????????????????
                    masina.Set_spalat_usoare_deschise(0);
                    masina.Set_stors(masina.Get_stors() + greutate);
                }
            } else {
                masina.Set_spalat_usoare_inchise(masina.Get_spalat_usoare_inchise() + greutate);
                if (masina.Get_spalat_usoare_inchise() >= capacitate_spalat / 2) {
                    masina.Set_spalat_usoare_inchise(0);
                    masina.Set_stors(masina.Get_stors() + greutate);
                }
            }
        } else {
            masina.Set_spalat_grele_deschise(masina.Get_spalat_grele_deschise() + greutate);
            if (masina.Get_spalat_grele_deschise() >= capacitate_spalat / 2) {
                masina.Set_spalat_grele_deschise(0);
                masina.Set_stors(masina.Get_stors() + greutate);
            } else {
                masina.Set_spalat_grele_inchise(masina.Get_spalat_grele_inchise() + greutate);
                if (masina.Get_spalat_grele_inchise() >= capacitate_spalat / 2) {
                    masina.Set_spalat_grele_inchise(0);
                    masina.Set_stors(masina.Get_stors() + greutate);
                }
            }
        }
    }

    void Stors() {
        if (masina.Get_stors() >= capacitate_stors / 2) {
            masina.Set_stors(0);
            masina.Set_uscat(masina.Get_uscat() + 1);
        }
    }

    void Uscat() {
        if (masina.Get_uscat() >= capacitate_uscat / 2) {
            masina.Set_uscat(0);
        }
    }

    int Timp_Calcat() {
        if (type == "PANTALONI") {
            return timp_calcat_pantaloni * greutate;
        } else if (type == "CAMASA"){
            return timp_calcat_camasa * greutate;
        } else if (type == "ROCHIE") {
            return timp_calcat_rochie * greutate;
        } else if (type == "COSTUM") {
            return (timp_calcat_pantaloni + timp_calcat_sacouri) * greutate;
        }

        return 0;
    }
};

class Client {
    int n;
    vector <Haine> h;
public:
    Client() {
        erase();
    }
    Client(const Client & c) {
        SetHaine(c);
    }
    Client (const vector <Haine> & H) {
        SetHaine(H);
    }

    void SetHaine(const Client & c) {
        SetHaine(c.h);
    }
    void SetHaine(const vector <Haine> & H, const int & N = 0) {
        erase();
        n = H.size();
        for (int i = 0; i < n; i ++) {
            h.push_back(H[i]);
        }
    }

    vector <Haine> GetHaine() const {
        return h;
    }

    Client &operator = (const vector <Haine> & H) {
        SetHaine(H);
        return *this;
    }
    Client &operator = (const Client &c) {
        SetHaine(c);
        return *this;
    }

    const bool operator < (const Client &c) {
        return n < c.n;
    }
    const bool operator < (const vector <Haine> & H) {
        return n < H.size();
    }

    friend istream &operator >> (istream &in, Client & c) {
        in >> c.n;
        Haine x;
        for (int i = 0; i < c.n; i ++) {
            in >> x;
            c.h.push_back(x);
        }

        return in;
    }
    friend ostream &operator << (ostream &out, Client &c) {
        out << "Numarul de haine ale clientului: " << c.n;
        out << "\n Hainele sunt: ";
        for (int i = 0; i < c.n; i ++) {
            out << c.h[i] << endl;
        }

        return out;
    }

    void Afisare_Istoric() {
        for (int i = 0; i < n; i ++) {
            h[i].Istoric();
        }
    }

    void erase() {
        n = 0;
        while (!h.empty()) {
            h.pop_back();
        }
    }
    ~Client() {
        erase();
    }
};

int main() {
    int numar_clienti;
    cin >> numar_clienti;
    for (int i = 0; i < numar_clienti; i ++) {
        Client x;
        cin >> x;
        x.Afisare_Istoric();
        cout << "\n";
    }
    return 0;
}

