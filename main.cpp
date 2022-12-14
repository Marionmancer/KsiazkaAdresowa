#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct Adresat {
    int id, idUzytkownika;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void wyswietlMenuLogowania () {
    system("cls");
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "9. Zakoncz program" << endl << endl;
}

void wyswietlGlowneMenuUzytkownika () {
    system("cls");
    cout << "KSIAZKA ADRESOWA" << endl;
    cout << "---------------------" << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "9. Wyloguj sie" << endl << endl;
}

void wyswietlMenuEdycjiDanychAdresatow () {
    system("cls");
    cout << "WYBIERZ DANE DO EDYCJI" << endl;
    cout << "---------------------" << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. e-mail" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu glownego" << endl << endl;
}

Uzytkownik pobierzDaneUzytkownika(string daneUzytkownikaOddzielonePionowymiKreskami) {

    Uzytkownik odczytywanyUzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerOdczytywanejDanej = 1;

    for (unsigned int pozycjaZnaku = 0; pozycjaZnaku < daneUzytkownikaOddzielonePionowymiKreskami.length(); pozycjaZnaku++) {
        if (daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            pojedynczaDanaUzytkownika += daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else {
            switch(numerOdczytywanejDanej) {
            case 1:
                odczytywanyUzytkownik.id = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                odczytywanyUzytkownik.nazwa = pojedynczaDanaUzytkownika;
                break;
            case 3:
                odczytywanyUzytkownik.haslo = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            numerOdczytywanejDanej++;
        }
    }
    return odczytywanyUzytkownik;
}

void odczytPlikuUzytkownicy (vector <Uzytkownik> &uzytkownicy) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);
    Uzytkownik uzytkownik;
    string daneUzytkownikaOddzielonePionowymiKreskami = "";

    if (plik.good()) {
        while (getline(plik,daneUzytkownikaOddzielonePionowymiKreskami)) {
            uzytkownik = pobierzDaneUzytkownika (daneUzytkownikaOddzielonePionowymiKreskami);

            uzytkownicy.push_back(uzytkownik);
        }
        plik.close();
    }
}

Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami) {

    Adresat odczytywanyAdresat;
    string pojedynczaDanaAdresata = "";
    int numerOdczytywanejDanej = 1;

    for (unsigned int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++) {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else {
            switch(numerOdczytywanejDanej) {
            case 1:
                odczytywanyAdresat.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                odczytywanyAdresat.idUzytkownika = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 3:
                odczytywanyAdresat.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                odczytywanyAdresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                odczytywanyAdresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 6:
                odczytywanyAdresat.email = pojedynczaDanaAdresata;
                break;
            case 7:
                odczytywanyAdresat.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerOdczytywanejDanej++;
        }
    }
    return odczytywanyAdresat;
}

void odczytPlikuAdresaci (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    fstream plik;
    plik.open("Adresaci.txt", ios::in);
    Adresat adresat;
    string daneAdresataOddzielonePionowymiKreskami = "";

    if (plik.good()) {
        while (getline(plik,daneAdresataOddzielonePionowymiKreskami)) {
            adresat = pobierzDaneAdresata (daneAdresataOddzielonePionowymiKreskami);

            if (adresat.idUzytkownika == idZalogowanegoUzytkownika) adresaci.push_back(adresat);
        }
        plik.close();
    }
}

void zapisUzytkownikowDoPliku (vector <Uzytkownik> &uzytkownicy) {
    fstream plik;
    const int PIERWSZY_RECORD_W_PLIKU = 0;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if ((uzytkownicy.size() - 1) > PIERWSZY_RECORD_W_PLIKU) plik << endl;

    plik << uzytkownicy[uzytkownicy.size() - 1].id << "|";
    plik << uzytkownicy[uzytkownicy.size() - 1].nazwa << "|";
    plik << uzytkownicy[uzytkownicy.size() - 1].haslo << "|";

    plik.close();
}

void rejestracjaUzytkownika (vector <Uzytkownik> &uzytkownicy) {

    Uzytkownik rejestrowanyUzytkownik;
    string nazwa, haslo;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    unsigned int i=0;
    while(i < uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;

    rejestrowanyUzytkownik.nazwa = nazwa;
    rejestrowanyUzytkownik.haslo = haslo;

    if (uzytkownicy.size() == 0){
        rejestrowanyUzytkownik.id = 1;
    }
    else
        rejestrowanyUzytkownik.id = uzytkownicy [uzytkownicy.size() - 1].id + 1;

    uzytkownicy.push_back(rejestrowanyUzytkownik);
    zapisUzytkownikowDoPliku (uzytkownicy);

    cout << "Konto zostalo zalozone " << endl;
    system("PAUSE");
}

int logowanie(vector <Uzytkownik> &uzytkownicy) {

    string nazwa, haslo;

    cout << "Podaj login: ";
    cin >> nazwa;

    unsigned int i=0;
    while(i < uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa == nazwa) {
            for (int iloscProb = 0; iloscProb < 3; iloscProb++) {
                cout << "Podaj haslo. Pozostalo prob " << 3 - iloscProb << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    system("PAUSE");
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void nadpiszPlikUzytkownicy (vector <Uzytkownik> &uzytkownicy) {
    fstream plik;
    const int PIERWSZY_RECORD_W_PLIKU = 0;
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true) {
        for (unsigned int i = 0; i < uzytkownicy.size(); i++) {
            if (i > PIERWSZY_RECORD_W_PLIKU) plik << endl;
            plik << uzytkownicy[i].id << "|";
            plik << uzytkownicy[i].nazwa << "|";
            plik << uzytkownicy[i].haslo << "|";
        }
        plik.close();
    }
}

void zmianaHaslaLogowania(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    string haslo;
    cout << "Podaj nowe haslo: " << endl;
    cin >> haslo;
    for (unsigned int i = 0; i < uzytkownicy.size(); i++) {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
    nadpiszPlikUzytkownicy (uzytkownicy);
}

bool czyTekstMaDozwoloneZnaki(string tekst) {
    return tekst.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- ") == string::npos;
}

string wczytajLinieTekstu() {
    string wejscie = "";
    while (wejscie == "") {
        cin.sync();
        getline (cin, wejscie);
    }
    return wejscie;
}

bool czyEmailPoprawny(string email) {
    size_t polozenieZnaku = email.find ("@");
    if (polozenieZnaku != string::npos)
        return true;
    else {
        return false;
    }
}

void zapisAdresatowDoPliku (vector <Adresat> &adresaci, int idDodawanegoAdresata) {
    fstream plik;
    const int PIERWSZY_RECORD_W_PLIKU = 1;
    plik.open("Adresaci.txt", ios::out | ios::app);

    if (idDodawanegoAdresata > PIERWSZY_RECORD_W_PLIKU) plik << endl;

    plik << adresaci[adresaci.size() - 1].id << "|";
    plik << adresaci[adresaci.size() - 1].idUzytkownika << "|";
    plik << adresaci[adresaci.size() - 1].imie << "|";
    plik << adresaci[adresaci.size() - 1].nazwisko << "|";
    plik << adresaci[adresaci.size() - 1].numerTelefonu << "|";
    plik << adresaci[adresaci.size() - 1].email << "|";
    plik << adresaci[adresaci.size() - 1].adres << "|";

    plik.close();
}

int pobierzIdOstatniegoAdresataWBazieDanych () {
    int idOstatniegoAdresataWBazieDanych = 0;
    string idOstatniegoAdresataWBazieDanychJakoString = "";
    string daneAdresataOddzielonePionowymiKreskami = "";
    fstream plik;

    plik.open("Adresaci.txt", ios::in);

    if (plik.good()) {
        while (getline(plik, daneAdresataOddzielonePionowymiKreskami)) {
            int polozenieZnakuPodzialu = daneAdresataOddzielonePionowymiKreskami.find('|');

            idOstatniegoAdresataWBazieDanychJakoString = daneAdresataOddzielonePionowymiKreskami.substr(0, polozenieZnakuPodzialu);
            idOstatniegoAdresataWBazieDanych = atoi(idOstatniegoAdresataWBazieDanychJakoString.c_str());
        }
        plik.close();
    }
    return idOstatniegoAdresataWBazieDanych;
}

void dodajAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    Adresat dodawanyAdresat;

    cout << "Podaj imie: " << endl;

    dodawanyAdresat.id = pobierzIdOstatniegoAdresataWBazieDanych() + 1;
    dodawanyAdresat.idUzytkownika = idZalogowanegoUzytkownika;

    do {
        dodawanyAdresat.imie = wczytajLinieTekstu();
        if (czyTekstMaDozwoloneZnaki(dodawanyAdresat.imie) == false) {
            cout << "Wprowadzone imie jest niepoprawne, wprowadz raz jeszcze" << endl;
        }
    } while (czyTekstMaDozwoloneZnaki(dodawanyAdresat.imie) == false);

    cout << "Podaj nazwisko: " << endl;
    do {
        dodawanyAdresat.nazwisko = wczytajLinieTekstu();
        if (czyTekstMaDozwoloneZnaki(dodawanyAdresat.nazwisko) == false) {
            cout << "Wprowadzone nazwisko jest niepoprawne, wprowadz raz jeszcze" << endl;
        }
    } while (czyTekstMaDozwoloneZnaki(dodawanyAdresat.nazwisko) == false);

    cout << "Podaj numer telefonu: " << endl;
    dodawanyAdresat.numerTelefonu = wczytajLinieTekstu();

    cout << "Podaj e-mail: " << endl;
    do {
        dodawanyAdresat.email = wczytajLinieTekstu();
        if (czyEmailPoprawny(dodawanyAdresat.email) == false) {
            cout << "Wprowadzony e-mail jest niepoprawny, wprowadz raz jeszcze" << endl;
        }
    } while (czyEmailPoprawny(dodawanyAdresat.email) == false);

    cout << "Podaj adres: " << endl;
    dodawanyAdresat.adres = wczytajLinieTekstu();

    adresaci.push_back(dodawanyAdresat);
    zapisAdresatowDoPliku (adresaci, dodawanyAdresat.id);
    cout << "Dodano osobe do bazy adresatow" << endl;
    Sleep(1000);
}

void wyswietlKomunikatZamknieciaWynikowWyszukiwania () {
    cout << endl << "Dowolny klawisz zamknie wyniki wyszukiwania" << endl;
    system("PAUSE");
}

void wyswietlDaneAdresata (vector <Adresat> &adresaci, int idAdresata) {
    cout << adresaci[idAdresata].id << "|";
    cout << adresaci[idAdresata].imie << "|";
    cout << adresaci[idAdresata].nazwisko << "|";
    cout << adresaci[idAdresata].numerTelefonu << "|";
    cout << adresaci[idAdresata].email << "|";
    cout << adresaci[idAdresata].adres << "|" << endl;
}

void wyszukajAdresataPoImieniu (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    cout << "Podaj imie do wyszukania" <<endl;
    string szukaneImie = wczytajLinieTekstu();

    int iloscWynikow = 0;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if ((adresaci[i].imie == szukaneImie) && (adresaci[i].idUzytkownika == idZalogowanegoUzytkownika)) {
            wyswietlDaneAdresata(adresaci, i);
            ++iloscWynikow;
        }
    }

    if (iloscWynikow == 0) {
        cout << "Brak osoby o tym imieniu w bazie. Wcisnij dowolny klawisz" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

void wyszukajAdresataPoNazwisku (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    cout << "Podaj nazwisko do wyszukania" <<endl;
    string szukaneNazwisko = wczytajLinieTekstu();

    int iloscWynikow = 0;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if ((adresaci[i].nazwisko == szukaneNazwisko) && (adresaci[i].idUzytkownika == idZalogowanegoUzytkownika)) {
            wyswietlDaneAdresata(adresaci, i);
            ++iloscWynikow;
        }
    }

    if (iloscWynikow == 0) {
        cout << "Brak osoby o tym imieniu w bazie. Wcisnij dowolny klawisz" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

void wyswietlDaneWszystkichAdresatow (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    int iloscAdresatowUzytkownika = 0;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if ((adresaci.size() > 0) && (adresaci[i].idUzytkownika == idZalogowanegoUzytkownika)) {
            wyswietlDaneAdresata(adresaci, i);
            iloscAdresatowUzytkownika++;
        }
    }
    if ((adresaci.size() == 0) || (iloscAdresatowUzytkownika == 0)) {
        cout << "Nie masz adresatow w bazie :/. Dodaj kogos! ;)" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

bool czyAdresatJestWKsiazceAdresowej (vector <Adresat> adresaci, int idAdresataDoSprawdzenia, int idZalogowanegoUzytkownika) {
    bool wynikWyszukiwania = false;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if ((adresaci[i].id == idAdresataDoSprawdzenia) && (adresaci[i].idUzytkownika == idZalogowanegoUzytkownika)) {
            wynikWyszukiwania = true;
            i = adresaci.size();
        }
    }
    return wynikWyszukiwania;
}

int podbierzIdAdresataDoEdycji (vector <Adresat> adresaci, int idZalogowanegoUzytkownika) {

    int idEdytowanegoAdresata = 0;

    do {
        system("cls");
        cout << "Podaj ID edytowanego adresata" << endl;
        cin >> idEdytowanegoAdresata;
        if (!czyAdresatJestWKsiazceAdresowej(adresaci, idEdytowanegoAdresata, idZalogowanegoUzytkownika)) {
            cout << "Brak w ksiazce adresata o tym numerze ID" << endl;
            Sleep (1000);
            system("cls");
        }
    } while (!czyAdresatJestWKsiazceAdresowej(adresaci, idEdytowanegoAdresata, idZalogowanegoUzytkownika));
    return idEdytowanegoAdresata;
}

void nadpiszPlikAdresaci (vector <Adresat> adresaci, int polozenieAdresataPoNumerzeId, string rodzajOperacji) {
    fstream plik, plikTymczasowy;
    const int PIERWSZY_RECORD_W_PLIKU = 1;
    Adresat adresat;
    string daneAdresataOddzielonePionowymiKreskami = "";

    plik.open("Adresaci.txt", ios::in);
    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out);

    if ((plik.good()) && (plikTymczasowy.good())) {
        int numerRecorduWPliku = 1;

        while (getline(plik,daneAdresataOddzielonePionowymiKreskami)) {
            adresat = pobierzDaneAdresata (daneAdresataOddzielonePionowymiKreskami);

            if ((adresat.id == adresaci[polozenieAdresataPoNumerzeId].id) && (rodzajOperacji == "edytujDaneAdresata")) {
                if (numerRecorduWPliku > PIERWSZY_RECORD_W_PLIKU) plikTymczasowy << endl;
                plikTymczasowy << adresaci[polozenieAdresataPoNumerzeId].id << "|";
                plikTymczasowy << adresaci[polozenieAdresataPoNumerzeId].idUzytkownika << "|";
                plikTymczasowy << adresaci[polozenieAdresataPoNumerzeId].imie << "|";
                plikTymczasowy << adresaci[polozenieAdresataPoNumerzeId].nazwisko << "|";
                plikTymczasowy << adresaci[polozenieAdresataPoNumerzeId].numerTelefonu << "|";
                plikTymczasowy << adresaci[polozenieAdresataPoNumerzeId].email << "|";
                plikTymczasowy << adresaci[polozenieAdresataPoNumerzeId].adres << "|";
            }
            else if ((adresat.id == adresaci[polozenieAdresataPoNumerzeId].id) && (rodzajOperacji == "usunAdresata")) {
                if (numerRecorduWPliku == PIERWSZY_RECORD_W_PLIKU) numerRecorduWPliku = 0;
            }
            else {
                if (numerRecorduWPliku > PIERWSZY_RECORD_W_PLIKU) plikTymczasowy << endl;
                plikTymczasowy << adresat.id << "|";
                plikTymczasowy << adresat.idUzytkownika << "|";
                plikTymczasowy << adresat.imie << "|";
                plikTymczasowy << adresat.nazwisko << "|";
                plikTymczasowy << adresat.numerTelefonu << "|";
                plikTymczasowy << adresat.email << "|";
                plikTymczasowy << adresat.adres << "|";
            }
            numerRecorduWPliku++;
        }
        plik.close();
        remove("Adresaci.txt");
        plikTymczasowy.close();
        rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
    }
}

int podajPolozenieAdresataPoId (vector <Adresat> adresaci, int idAdresataDoSprawdzenia){
    int polozenieAdresataPoId = 0;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id == idAdresataDoSprawdzenia) {
            polozenieAdresataPoId = i;
            i = adresaci.size();
        }
    }
    return polozenieAdresataPoId;
}

void edycjaDanychAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    int idEdytowanegoAdresata = podbierzIdAdresataDoEdycji (adresaci, idZalogowanegoUzytkownika);
    int polozenieAdresataPoNumerzeId = podajPolozenieAdresataPoId (adresaci, idEdytowanegoAdresata);

    wyswietlMenuEdycjiDanychAdresatow();

    switch (getch()) {
        case'1':
                cout << "Wprowadz nowe imie:" << endl;
            cin.sync();
            getline(cin,adresaci[polozenieAdresataPoNumerzeId].imie);
            nadpiszPlikAdresaci (adresaci, polozenieAdresataPoNumerzeId, "edytujDaneAdresata");
            system("PAUSE");
            break;

        case'2': {
                cout << "Wprowadz nowe nazwisko:" << endl;
            cin.sync();
            getline(cin, adresaci[polozenieAdresataPoNumerzeId].nazwisko);
            nadpiszPlikAdresaci (adresaci, polozenieAdresataPoNumerzeId, "edytujDaneAdresata");
            system("PAUSE");
            break;
        }
        case'3':{
                cout << "Wprowadz nowy numer telefonu:" << endl;
            cin.sync();
            cin >> adresaci[polozenieAdresataPoNumerzeId].numerTelefonu;
            nadpiszPlikAdresaci (adresaci, polozenieAdresataPoNumerzeId, "edytujDaneAdresata");
            system("PAUSE");
            break;
        }
        case'4':{
                cout << "Wprowadz nowy email:" << endl;
            cin.sync();
            getline(cin, adresaci[polozenieAdresataPoNumerzeId].email);
            nadpiszPlikAdresaci (adresaci, polozenieAdresataPoNumerzeId, "edytujDaneAdresata");
            system("PAUSE");
            break;
        }
        case'5':{
                cout << "Wprowadz nowy adres:" << endl;
            cin.sync();
            getline(cin, adresaci[polozenieAdresataPoNumerzeId].adres);
            nadpiszPlikAdresaci (adresaci, polozenieAdresataPoNumerzeId, "edytujDaneAdresata");
            system("PAUSE");
            break;
        }
        case'6':
            break;

        default:
            cout << "Nie ma takiej opcji w menu!" <<endl;
            system("PAUSE");
    }
    system("cls");
    }

bool czyUzytkownikPotwierdzilUsuniecieAdresata () {
    cout << "Wcisnij klawicz 't' jezeli potwierdzasz usuwanie adresata, w przeciwnym razie wcisnij dowolny klawisz " << endl;
    if (getch() == 't') return true;
    else return false;
}

void usunAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    int idAdresataDoUsuniecia = 0;
    bool wynikWyszukiwaniaAdresata = false;
    cout << "Podaj ID adresata do usuniecia z ksiazki adresowej" << endl;

    do {
        cin >> idAdresataDoUsuniecia;
        wynikWyszukiwaniaAdresata = czyAdresatJestWKsiazceAdresowej (adresaci, idAdresataDoUsuniecia, idZalogowanegoUzytkownika);

        if (!wynikWyszukiwaniaAdresata) {
            cout << "Adresata o podanym ID nie ma w Ksiazce Adresowej." << endl;
            cout << "Wcisnij 'n' aby wrocic do poprzedniego menu lub dowolny klawisz by podac inne ID" << endl;
            char wybor = getch();
            if (wybor == 'n') wynikWyszukiwaniaAdresata = true;
            else {
                system("cls");
                cout << "Podaj ID adresata do usuniecia" << endl;
            }
        }
        else if (wynikWyszukiwaniaAdresata) {
            if (czyUzytkownikPotwierdzilUsuniecieAdresata()) {
                        int polozenieAdresataPoNumerzeId = podajPolozenieAdresataPoId (adresaci, idAdresataDoUsuniecia);

                        nadpiszPlikAdresaci (adresaci, polozenieAdresataPoNumerzeId, "usunAdresata");
                        adresaci.erase(adresaci.begin() + polozenieAdresataPoNumerzeId);
                        cout << "Adresat o wskazanym ID zostal usuniety z Ksiazki Adresowej" << endl;
                        system("PAUSE");
            }
            else {
                cout << "Operacja usuniecia adresata anulowana przez uzytkownika" << endl;
                system("PAUSE");
            }
        }
    } while (!wynikWyszukiwaniaAdresata);
}

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0;

    odczytPlikuUzytkownicy (uzytkownicy);

    while (true) {
        if (idZalogowanegoUzytkownika == 0) {

            wyswietlMenuLogowania();

            char wybor = getch();
            switch (wybor) {

            case'1':
                    rejestracjaUzytkownika(uzytkownicy);
                break;

            case'2': {
                    idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                    odczytPlikuAdresaci (adresaci, idZalogowanegoUzytkownika);
                break;
            }
            case'9':
                    exit(0);
                break;

            default:
                ;
            }
        } else {
            wyswietlGlowneMenuUzytkownika ();

            char wybor = getch();
            switch (wybor) {
            case'1':
                    dodajAdresata (adresaci, idZalogowanegoUzytkownika);
                break;

            case'2':
                wyszukajAdresataPoImieniu (adresaci, idZalogowanegoUzytkownika);
                break;
            case'3':
                wyszukajAdresataPoNazwisku (adresaci, idZalogowanegoUzytkownika);
                break;
            case'4':{
                    cout << "Lista danych Twoich adresatow wyglada nastepujaco: " << endl;
                wyswietlDaneWszystkichAdresatow(adresaci, idZalogowanegoUzytkownika);
                break;
            }
            case'5':{
                if (adresaci.size() == 0) {
                    cout << "Baza adresatow jest pusta. Dodaj kogos" << endl;
                    Sleep (1000);
                } else
                    usunAdresata (adresaci, idZalogowanegoUzytkownika);
                break;
            }
            case'6':{
                if (adresaci.size() == 0) {
                    cout << "Baza adresatow jest pusta. Dodaj kogos" << endl;
                    Sleep (1000);
                } else
                    edycjaDanychAdresata(adresaci, idZalogowanegoUzytkownika);
                break;
            }
            case'7':
                zmianaHaslaLogowania(uzytkownicy, idZalogowanegoUzytkownika);
            break;

            case'9':
                adresaci.clear();
                idZalogowanegoUzytkownika = 0;
                break;

            default:
                cout << "Nie ma takiej opcji w menu!" <<endl;
                Sleep (1000);
            }
            system("cls");
        }
    }
    return 0;
}
