#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// orice depunere este gratuită
// retragerea poate sa coste
// dacă s-a depășit numărul de tranzacții gratuite
// sau e făcută de la bancomatele altor bănci
// sau orice cumparatura online are un cost


class ContBancar
{
protected:
    string detinator;
    string data_deschidere;
    int sold;

public:
    ContBancar()
    {
        detinator = "";
        data_deschidere = "";
        sold = 0;
    }
    ContBancar(string& d, string& dd, int s)
    {
        detinator = d;
        data_deschidere = d;
        sold = s;
    }
    virtual ~ContBancar() = default;
    ContBancar(const ContBancar& obj) {
        detinator = obj.detinator;
        data_deschidere = obj.data_deschidere;
        sold = obj.sold;
    }
    ContBancar& operator=(const ContBancar& obj) {
        if (this != &obj)
        {
            detinator = obj.detinator;
            data_deschidere = obj.data_deschidere;
            sold = obj.sold;
        }
        return *this;
    }
    virtual void depunere(int suma) {
        sold += suma;
    }


    friend istream& operator >> (istream& in, ContBancar& bj);
    friend ostream& operator << (ostream& out, ContBancar& obj);
    virtual void afisare() { cout << (*this); }
    int getSold() { return sold; }
};

istream& operator>>(istream& in, ContBancar& obj)
{
    cout << "DATELE CONTULUI BANCAR" << endl;
    cout << "Numele detinatorului:\n";
    in >> obj.detinator;
    cout << "\nData deschiderii contului:\n";
    in >> obj.data_deschidere;
    try
    {
        cout << "\nSold: ";
        if (!(in >> obj.sold))
            throw 13;
    }
    catch (int x)
    {
        if (x == 13)
            cout << endl << "Eroare" << endl;
    }
    return in;
}

ostream& operator<<(ostream& out, ContBancar& obj)
{
    out << endl;
    out << "DATELE CONTULUI BANCAR" << endl;
    out << "Detinator: " << obj.detinator << endl;
    out << "Data deschiderii contului: " << obj.data_deschidere << endl;
    out << "Sold: " << obj.sold;
    return out;
}

class ContEconomii : public ContBancar
{
protected:
    double rata_dobanda;
    int tip_rata;
    vector<int> istoric_sold;

public:
    ContEconomii()
    {
        rata_dobanda = 0;
        tip_rata = 0;
        istoric_sold.push_back(0);
    };
    ContEconomii(string& d, string& dd, double s, double& r, int& n, vector<int>& i) :ContBancar(d, dd, s) {
        rata_dobanda = r;
        tip_rata = n;
        istoric_sold = i;
    }

    virtual ~ContEconomii() = default;

    ContEconomii(const ContEconomii& obj)
    {
        rata_dobanda = obj.rata_dobanda;
        tip_rata = obj.tip_rata;
        istoric_sold = obj.istoric_sold;

    }
    ContEconomii& operator = (const ContEconomii& obj)
    {
        if (this != &obj)
        {
            this->ContBancar::operator=(obj);
            rata_dobanda = obj.rata_dobanda;
            tip_rata = obj.tip_rata;
            istoric_sold = obj.istoric_sold;
        }
        return *this;
    }

    void setIstoricSold(const vector<int>& istoricSold) {
        istoric_sold = istoricSold;
    }

    vector<int> getIstoricSold(vector<int>& istoricSold)
    {
        return istoric_sold;
    }


    int getTipRata() {
        return tip_rata;
    }
    friend istream& operator>>(istream& in, ContEconomii& obj);
    friend ostream& operator<<(ostream& out, ContEconomii& obj);
};

istream& operator>>(istream& in, ContEconomii& obj) {
    in >> (ContBancar&)obj;
    in >> obj.rata_dobanda;
    in >> obj.tip_rata;
    int ok = 0;
    cout << "tip rata (3, 6, 9, 12):\n";
    switch (obj.tip_rata) {
    case 3:
        ok = 1;
        break;
    case 6:
        ok = 1;
        break;
    case 9:
        ok = 1;
        break;
    case 12:
        ok = 1;
        break;
    case 0:
        cout << "Imposibil. Datele sunt invalide\n";
    }
    return in;
}


ostream& operator<<(ostream& out, ContEconomii& obj)
{
    out << (static_cast<ContBancar&>(obj));
    out << '\n';
    out << "Rata dobanda:" << obj.rata_dobanda << '\n';
    out << "Durata ratei:" << obj.tip_rata << '\n';
    out << "Istoric sold:" << '\n';
    for (int i = 0; i < obj.istoric_sold.size(); ++i) {
        out << obj.istoric_sold[i] << "\n";
    }
    return out;
}

class ContCurent : public ContBancar
{
protected:
    int tranzactii_gratuite;
    double comision;

public:
    ContCurent() :ContBancar()
    {
        tranzactii_gratuite = 0;
        comision = 0;
    }
    ContCurent(string& d, string& dd, int s, int& tg, double& c) :ContBancar(d, dd, s) {
        tranzactii_gratuite = tg;
        comision = c;
    }

    ContCurent(const ContCurent& obj) : ContBancar(obj) {
        tranzactii_gratuite = obj.tranzactii_gratuite;
        comision = obj.comision;
    }

    ContCurent& operator=(const ContCurent& obj) {
        if (this != &obj)
        {
            this->ContBancar::operator=(obj);
            tranzactii_gratuite = obj.tranzactii_gratuite;
            comision = obj.comision;
        }
        return *this;
    }

    virtual ~ContCurent() = default;
    void afisare()
    {
        this->ContBancar::afisare();
        cout << "Tranzactii gratuite ramase:" << this->tranzactii_gratuite << '\n';
        cout << "Comision retrageri:" << this->comision << '\n';
    }
    int getTranzactiiGratuite() {
        return tranzactii_gratuite;
    }

    virtual void retragere(double x)
    {
        if (tranzactii_gratuite > 0) {
            if (x > sold)
            {
                cout << "Fonduri insuficiente\n";
                return;
            }
            else
            {
                tranzactii_gratuite--;
                sold = sold - x;
            }
        }
        else
        {
            double y;
            y = sold * comision;
            if (x + y > sold)
            {
                cout << "Fonduri insuficiente\n";
                return;
            }
            else
                sold = sold - x - y;
        }
    }

    void depunere(int suma) {
        sold += suma;
    }

    friend istream& operator>>(istream& in, ContCurent& obj);
    friend ostream& operator<<(ostream& out, ContCurent& obj);

};

istream& operator>>(istream& in, ContCurent& obj)
{
    cout << "CONT CURENT:\n";
    in >> (dynamic_cast<ContBancar&>(obj));
    cout << "Tranzactii gratuite: ";
    in >> obj.tranzactii_gratuite;
    cout << "Comision: ";
    in >> obj.comision;
    return in;
}

ostream& operator<<(ostream& out, ContCurent& obj)
{
    out << (static_cast<ContBancar&>(obj));
    out << "Tranzactii gratuite ramase: " << obj.tranzactii_gratuite << '\n';
    out << "Comision: " << obj.comision << '\n';
    return out;
}

template <class T>
class GestionareConturi {
private:
    unordered_map<int, T*> conturi;
    static int index_cont;
public:
    GestionareConturi()
    {
        index_cont++;
    }

    unordered_map<int, T*> getconturi() {
        return conturi;
    }
    ~GestionareConturi() {};

    /// da eroare :(


    GestionareConturi& operator+=(const T& obj)
    {
        conturi.push_back(obj);
        index_cont++;
    }


    virtual void depunere(int i, int suma)
    {
        conturi[i].depunere(suma);
        conturi[i].push_back(suma);
    }
};




/// EXEMPLU UTILIZARE SINGLETON

class DateClient {
    static DateClient* instance;
    string _nume;
    int _varsta;
    long long _cnp;
    string _ocupatie;
    DateClient() :_nume("Popescu Mihail"), _varsta(26), _cnp(5080205448910), _ocupatie("student") {}

public:
    static DateClient* getInstance() {
        if (!instance)
            instance = new DateClient;
        return instance;
    }

    string getNume() {
        return _nume;
    }

    void setNume(string _nume) {
        this->_nume = _nume;
    }

    int getVarsta()
    {
        return _varsta;
    }

    void setVarsta(int _varsta)
    {
        this->_varsta = _varsta;
    }

    long long getCNP(long long _cnp)
    {
        return _cnp;
    }

    void setCNP(long long _cnp)
    {
        this->_cnp = _cnp;
    }

    string getOcupatie() {
        return _ocupatie;
    }

    void setOcupatie(string _ocupatie) {
        this->_ocupatie = _ocupatie;
    }
    void afisareDateClient()
    {
        cout << "Nume: " << _nume << '\n';
        cout << "Varsta: " << _varsta << '\n';
        cout << "CNP: " << _cnp << '\n';
        cout << "Ocupatie: " << _ocupatie << '\n';
    }
};


/// EXEMPLU BUILDER (chiar daca nu apare clasa in exercitiu)
/// produsul final
/// Partea asta e facuta doar ca sa ilustreze BUILDER-ul, nu e prea are treaba cu aplicatia :D

class Card {

    string _card;
    long long _numarCard;
    string _numeDetinator;
    int _cvv;
    string _dataExpirare;
public:

    Card(string card) :_card{ card } {}
    void setNumar(long long numar) { _numarCard = numar; }
    void setCVV(int CVV) { _cvv = CVV; }
    void setNume(string nume) { _numeDetinator = nume; }
    void setDataExp(string dataExp) { _dataExpirare = dataExp; }

    void afisareDateCard()
    {
        cout << "Numar card: " << _numarCard << endl;
        cout << "Nume detinator: " << _numeDetinator << endl;
        cout << "CVV: " << _cvv << endl;
        cout << "Data expirare: " << _dataExpirare << endl << endl;
    }
};

class CreareCard {
protected: Card* _card;

public:
    virtual void creareCardFizic() = 0;
    virtual void scriereNumar() = 0;
    virtual void scriereNume() = 0;
    virtual void scriereCVV() = 0;
    virtual void scriereDataExp() = 0;
    Card* getCard() { return _card; }
};

class CrearePartiCard :public CreareCard {
public:
    void creareCardFizic() { _card = new Card("Card banca X"); }
    void scriereNumar() { _card->setNumar(293810381410); }
    void scriereNume() { _card->setNume("Popescu Mihail"); }
    void scriereCVV() { _card->setCVV(999); }
    void scriereDataExp() { _card->setDataExp("29.02.2035"); }
};


/// ne spune pasii
class Boss {
public:
    Card* jobDeFacutCarduri(CreareCard* angajat)
    {
        angajat->creareCardFizic();
        angajat->scriereNume();
        angajat->scriereNumar();
        angajat->scriereDataExp();
        angajat->scriereCVV();
        return angajat->getCard();
    }
};


void Meniu_Scris()
{
    cout << "Meniu\n";
    cout << "1. Introduceti conturile." << endl;
    cout << "2. Depuneti o suma de bani." << endl;
    cout << "3. Retrageti o suma de bani." << endl;
    cout << "4. Afisati contul de economii." << endl;
    cout << "5. Iesiti din program." << endl;
    cout << "Introduceti un numar de la 1 la 5 pentru a alege o optiune (daca nu alegeti un numar, veti fi scos din aplicatie): ";
}

void Meniu()
{
    int k = 0;
    vector<ContBancar*> ob;

    int i;
    int n;

    cout << "Cate conturi doriti sa introduceti? ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int opt;
        cout << "Ce tip de cont? Cont curent (1)/ Cont de economii (2): " << '\n';
        cin >> opt;
        if (opt == 1)
        {
            ContCurent cont_c;
            cin >> cont_c;
            ob.push_back(new ContCurent(cont_c));

        }
        else
        {
            ContEconomii cont_ec;
            cin >> cont_ec;
            ob.push_back(new ContEconomii(cont_ec));
        }
    }

    getchar();
    getchar();
    system("CLS");

    Meniu_Scris();
    ContCurent cont_c;
    ContEconomii cont_ec;
    do {
        cin >> k;
        while (k < 0 || k > 4)
        {
            cin >> k;
            if (k < 0 || k > 4)
                cout << "Va rugam sa introduceti un caracter valid ('1', '2', '3', '4', '5'): ";
        }
        if (k == 1)
        {
            cin >> cont_c;
            ob.push_back(new ContCurent(cont_c));
            cout << endl;
            cin >> cont_ec;
            ob.push_back(new ContEconomii(cont_ec));
            cout << "Apasati orice tasta pentru a va intoarce la meniu.\n";
            getchar();
            getchar();
            system("CLS");
            Meniu_Scris();

        }
        if (k == 2)
        {
            int suma;
            cout << "Introduceti suma pe care doriti sa o depuneti: ";
            cout << '\n';
            cin >> suma;

            cout << "Alegeti in ce cont doriti sa depuneti: 1 sau 2? ";
            int opt;
            cin >> opt;
            if (opt == 1)

                cout << "In ce cont doriti sa introduceti? (1 sau 2)";
            int opt2;
            cin >> opt2;
            if (opt2 == 1)
            {
                cont_c.depunere(suma);
                cout << "Aveti " << cont_c.getSold() << " RON.";
            }
            else
            {
                cont_ec.depunere(suma);
                cout << "Aveti " << cont_ec.getSold() << " RON.";
            }
            cout << endl << "Apasati orice tasta pentru a va intoarce la meniu.\n";
            getchar();
            getchar();
            system("CLS");
            Meniu_Scris();
        }

        if (k == 3)
        {
            cout << "Introduceti suma pe care doriti sa o retrageti: ";
            cout << '\n';
            int suma;
            cin >> suma;
            cont_c.retragere(suma);

            cout << "Apasati orice tasta pentru a va intoarce la meniu.\n";
            getchar();
            getchar();
            system("CLS");
            Meniu_Scris();
        }

        if (k == 4)
        {
            cout << cont_ec;
            cout << "Apasati orice tasta pentru a va intoarce la meniu.\n ";
            getchar();
            getchar();
            system("CLS");
            Meniu_Scris();
        }
    } while (k);


    /*
    * ContCurent A;
    * ContEconomii B;
    * int suma;
    * cin>>suma;
    * A.depunere(suma);
    * B.depunere(suma);
    * A.retragere(10);
    * cout<<A.getSold();
    *
    */

    cout << "Apasati orice tasta pentru a iesi din program.";
    getchar();
    exit(EXIT_SUCCESS);

}

DateClient* DateClient::instance = 0;


int main()
{
    cout << "\n--------------------------------------------\n";
    cout << "DATE CLIENT:\n";
    //EXEMPLU SINGLETON
    DateClient* s = s->getInstance();
    s->afisareDateClient();

    cout << "\nDATELE CARDULUI CLIENTULUI\n";
    //EXEMPLU BUILDER
    Boss dir;
    CrearePartiCard a;

    Card* b = dir.jobDeFacutCarduri(&a);
    b->afisareDateCard();
    delete b;

    cout << "--------------------------------------------\n";
    cout << "Apasati orice tasta pentru a afisa meniul aplicatiei.";
    getchar();
    system("CLS");
    Meniu();

    return 0;
}