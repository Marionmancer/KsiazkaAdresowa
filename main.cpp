#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Adresat {
    int id;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void zwiekszIloscAdresatow (vector <Adresat> &adresaci) {
    Adresat nowyAdresat;
    adresaci.push_back(nowyAdresat);
}

int odczytPliku (vector <Adresat> &adresaci, int i) {
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::in);
    string linia;
    int nrLinijki = 1;

    if (plik.good()) {
        while (getline(plik,linia,'|')) {
            switch (nrLinijki) {
            case 1:
                zwiekszIloscAdresatow(adresaci);
                adresaci[i].id = atoi(linia.c_str());
                break;
            case 2:
                adresaci[i].imie = linia;
                break;
            case 3:
                adresaci[i].nazwisko = linia;
                break;
            case 4:
                adresaci[i].numerTelefonu = linia;
                break;
            case 5:
                adresaci[i].email = linia;
                break;
            case 6: {
                adresaci[i].adres = linia;
                i++;
                nrLinijki = 0;
            }
            break;
            }
            nrLinijki++;
        }
        plik.close();
    }

    return adresaci.size();
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

void zapisDoPliku (vector <Adresat> &adresaci, int i) {
    fstream plik;
    const int PIERWSZY_RECORD_W_PLIKU = 0;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);

    if (i != PIERWSZY_RECORD_W_PLIKU) plik << endl;

    plik << adresaci[i].id << "|";
    plik << adresaci[i].imie << "|";
    plik << adresaci[i].nazwisko << "|";
    plik << adresaci[i].numerTelefonu << "|";
    plik << adresaci[i].email << "|";
    plik << adresaci[i].adres << "|";

    plik.close();
}

int dodajAdresata (vector <Adresat> &adresaci, int iloscAdresatow) {

    zwiekszIloscAdresatow(adresaci);
    cout << "Podaj imie: " << endl;
    do {
        adresaci[iloscAdresatow].imie = wczytajLinieTekstu();
        if (czyTekstMaDozwoloneZnaki(adresaci[iloscAdresatow].imie) == false) {
            cout << "Wprowadzone imie jest niepoprawne, wprowadz raz jeszcze" << endl;
        }
    } while (czyTekstMaDozwoloneZnaki(adresaci[iloscAdresatow].imie) == false);

    cout << "Podaj nazwisko: " << endl;
    do {
        adresaci[iloscAdresatow].nazwisko = wczytajLinieTekstu();
        if (czyTekstMaDozwoloneZnaki(adresaci[iloscAdresatow].nazwisko) == false) {
            cout << "Wprowadzone nazwisko jest niepoprawne, wprowadz raz jeszcze" << endl;
        }
    } while (czyTekstMaDozwoloneZnaki(adresaci[iloscAdresatow].nazwisko) == false);

    cout << "Podaj numer telefonu: " << endl;
    adresaci[iloscAdresatow].numerTelefonu = wczytajLinieTekstu();

    cout << "Podaj e-mail: " << endl;
    do {
        adresaci[iloscAdresatow].email = wczytajLinieTekstu();
        if (czyEmailPoprawny(adresaci[iloscAdresatow].email) == false) {
            cout << "Wprowadzony e-mail jest niepoprawny, wprowadz raz jeszcze" << endl;
        }
    } while (czyEmailPoprawny(adresaci[iloscAdresatow].email) == false);

    cout << "Podaj adres: " << endl;
    adresaci[iloscAdresatow].adres = wczytajLinieTekstu();

    if (iloscAdresatow == 0){
        adresaci[iloscAdresatow].id = 1;
    }
    else
        adresaci[iloscAdresatow].id = adresaci [iloscAdresatow-1].id + 1;

    zapisDoPliku (adresaci, iloscAdresatow);
    cout << "Dodano osobe do bazy adresatow" << endl;
    Sleep(1000);

    return iloscAdresatow = adresaci.size();
}

void wyswietlKomunikatZamknieciaWynikowWyszukiwania () {
    cout << endl << "Dowolny klawisz zamknie wyniki wyszukiwania" << endl;
    system("PAUSE");
}

void wyswietlDaneOsoby (vector <Adresat> &adresaci, int idOsoby) {
    cout << adresaci[idOsoby].id << "|";
    cout << adresaci[idOsoby].imie << "|";
    cout << adresaci[idOsoby].nazwisko << "|";
    cout << adresaci[idOsoby].numerTelefonu << "|";
    cout << adresaci[idOsoby].email << "|";
    cout << adresaci[idOsoby].adres << "|" << endl;
}

void wyszukajPoImieniu (vector <Adresat> &adresaci, int iloscAdresatow, string szukaneImie) {
    int iloscWynikow = 0;

    for (int i = 0; i < iloscAdresatow; i++) {
        if (adresaci[i].imie == szukaneImie) {
            wyswietlDaneOsoby(adresaci, i);
            ++iloscWynikow;
        }
    }

    if (iloscWynikow == 0) {
        cout << "Brak osoby o tym imieniu w bazie. Wcisnij dowolny klawisz" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

void wyszukajPoNazwisku (vector <Adresat> &adresaci, int iloscAdresatow, string szukaneNazwisko) {
    int iloscWynikow = 0;

    for (int i = 0; i < iloscAdresatow; i++) {
        if (adresaci[i].nazwisko == szukaneNazwisko) {
            wyswietlDaneOsoby(adresaci, i);
            ++iloscWynikow;
        }
    }

    if (iloscWynikow == 0) {
        cout << "Brak osoby o tym imieniu w bazie. Wcisnij dowolny klawisz" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

void wyswietlDaneWszystkichOsob (vector <Adresat> &adresaci, int iloscAdresatow) {
    for (int i = 0; i < iloscAdresatow; i++) {
        if (iloscAdresatow > 0) {
            wyswietlDaneOsoby(adresaci, i);
        }
    }
    if (iloscAdresatow == 0) {
        cout << "Nie masz adresatow w bazie :/. Dodaj kogos! ;)" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

bool czyAdresatJestWKsiazceAdresowej (vector <Adresat> adresaci, int idAdresataDoSprawdzenia) {
    bool wynikWyszukiwania = false;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id == idAdresataDoSprawdzenia) {
            wynikWyszukiwania = true;
            i = adresaci.size();
        }
    }
    return wynikWyszukiwania;
}

int podbierzIdAdresataDoEdycji (vector <Adresat> adresaci) {

    int idEdytowanegoAdresata = 0;

    do {
        system("cls");
        cout << "Podaj ID edytowanego adresata" << endl;
        cin >> idEdytowanegoAdresata;
        if (!czyAdresatJestWKsiazceAdresowej(adresaci, idEdytowanegoAdresata)) {
            cout << "Brak w ksiazce adresata o tym numerze ID" << endl;
            Sleep (1000);
            system("cls");
        }
    } while (!czyAdresatJestWKsiazceAdresowej(adresaci, idEdytowanegoAdresata));
    return idEdytowanegoAdresata;
}

void nadpiszPlik (vector <Adresat> &adresaci) {
    fstream plik;
    const int PIERWSZY_RECORD_W_PLIKU = 0;
    plik.open("ksiazka_adresowa.txt", ios::out);

    if (plik.good() == true) {
        for (unsigned int i = 0; i < adresaci.size(); i++) {
            if (i != PIERWSZY_RECORD_W_PLIKU) plik << endl;
            plik << adresaci[i].id << "|";
            plik << adresaci[i].imie << "|";
            plik << adresaci[i].nazwisko << "|";
            plik << adresaci[i].numerTelefonu << "|";
            plik << adresaci[i].email << "|";
            plik << adresaci[i].adres << "|";
        }
        plik.close();
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

void wyswietlMenuEdycyjne () {
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

void dokonajEdycjiDanychAdresata (vector <Adresat> &adresaci) {
    int idEdytowanegoAdresata = podbierzIdAdresataDoEdycji (adresaci);
    int polozenieAdresataPoNumerzeId = podajPolozenieAdresataPoId (adresaci, idEdytowanegoAdresata);

    wyswietlMenuEdycyjne();

    switch (getch()) {
        case'1':
                cout << "Wprowadz nowe imie:" << endl;
            cin.sync();
            getline(cin,adresaci[polozenieAdresataPoNumerzeId].imie);
            nadpiszPlik (adresaci);
            system("PAUSE");
            break;

        case'2': {
                cout << "Wprowadz nowe nazwisko:" << endl;
            cin.sync();
            getline(cin, adresaci[polozenieAdresataPoNumerzeId].nazwisko);
            nadpiszPlik (adresaci);
            system("PAUSE");
            break;
        }
        case'3':{
                cout << "Wprowadz nowy numer telefonu:" << endl;
            cin.sync();
            cin >> adresaci[polozenieAdresataPoNumerzeId].numerTelefonu;
            nadpiszPlik (adresaci);
            system("PAUSE");
            break;
        }
        case'4':{
                cout << "Wprowadz nowy email:" << endl;
            cin.sync();
            getline(cin, adresaci[polozenieAdresataPoNumerzeId].email);
            nadpiszPlik (adresaci);
            system("PAUSE");
            break;
        }
        case'5':{
                cout << "Wprowadz nowy adres:" << endl;
            cin.sync();
            getline(cin, adresaci[polozenieAdresataPoNumerzeId].adres);
            nadpiszPlik (adresaci);
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

int usunAdresata (vector <Adresat> &adresaci, int iloscAdresatow) {
    int idAdresataDoUsuniecia = 0;
    cout << "Podaj ID adresata do usuniecia z ksiazki adresowej" << endl;

    do {
        cin >> idAdresataDoUsuniecia;
        if (!czyAdresatJestWKsiazceAdresowej (adresaci, idAdresataDoUsuniecia)) {
            cout << "Adresata o podanym ID nie ma w Ksiazce Adresowej. Podaj poprawne ID." << endl;
        }
    } while (!czyAdresatJestWKsiazceAdresowej (adresaci, idAdresataDoUsuniecia));

    if (czyUzytkownikPotwierdzilUsuniecieAdresata()) {
        for (unsigned int i = 0; i < adresaci.size(); i++) {
            if (adresaci[i].id == idAdresataDoUsuniecia) {
                adresaci.erase(adresaci.begin() + i);
                iloscAdresatow = adresaci.size();
                i = adresaci.size();
                nadpiszPlik (adresaci);
                cout << "Adresat o wskazanym ID zostal usuniety z Ksiazki Adresowej" << endl;
                system("PAUSE");
            }
        }
    }
    else {
        cout << "Operacja usuniecia adresata anulowana przez uzytkownika" << endl;
        system("PAUSE");
    }

    return iloscAdresatow;
}

void wyswietlMenuGlowne () {
    system("cls");
    cout << "KSIAZKA ADRESOWA" << endl;
    cout << "---------------------" << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "9. Zamknij program" << endl << endl;
}

int main() {
    vector <Adresat> adresaci;
    int iloscAdresatow = 0;

    iloscAdresatow = odczytPliku (adresaci, iloscAdresatow);

    while(true) {
        wyswietlMenuGlowne ();

        char wybor = getch();
        switch (wybor) {
        case'1':
                iloscAdresatow = dodajAdresata (adresaci, iloscAdresatow);
            break;

        case'2': {
                cout << "Podaj imie do wyszukania" <<endl;
            string szukaneImie = wczytajLinieTekstu();
            wyszukajPoImieniu (adresaci, iloscAdresatow, szukaneImie);
            break;
        }
        case'3':{
                cout << "Podaj nazwisko do wyszukania" <<endl;
            string szukaneNazwisko = wczytajLinieTekstu();
            wyszukajPoNazwisku (adresaci, iloscAdresatow, szukaneNazwisko);
            break;
        }
        case'4':{
                cout << "Lista danych Twoich adresatow wyglada nastepujaco: " << endl;
            wyswietlDaneWszystkichOsob(adresaci, iloscAdresatow);
            break;
        }
        case'5':{
            if (iloscAdresatow == 0) {
                cout << "Baza adresatow jest pusta. Dodaj kogos" << endl;
                Sleep (1000);
            } else
                iloscAdresatow = usunAdresata (adresaci, iloscAdresatow);
            break;
        }
        case'6':{
            if (iloscAdresatow == 0) {
                cout << "Baza adresatow jest pusta. Dodaj kogos" << endl;
                Sleep (1000);
            } else
                dokonajEdycjiDanychAdresata(adresaci);
            break;
        }
        case'9':
            exit(0);
            break;

        default:
            cout << "Nie ma takiej opcji w menu!" <<endl;
            Sleep (1000);
        }
        system("cls");
        }
    return 0;
}
