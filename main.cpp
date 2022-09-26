#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Przyjaciel {
    int id;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void zwiekszIloscPrzyjaciol (vector <Przyjaciel> &przyjaciele) {
    Przyjaciel nowyPrzyjaciel;
    przyjaciele.push_back(nowyPrzyjaciel);
}

int odczytPliku (vector <Przyjaciel> &przyjaciele, int i) {
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::in);
    string linia;
    int nrLinijki = 1;

    if (plik.good()) {
        while (getline(plik,linia,'|')) {
            switch (nrLinijki) {
            case 1:
                zwiekszIloscPrzyjaciol(przyjaciele);
                przyjaciele[i].id = atoi(linia.c_str());
                break;
            case 2:
                przyjaciele[i].imie = linia;
                break;
            case 3:
                przyjaciele[i].nazwisko = linia;
                break;
            case 4:
                przyjaciele[i].numerTelefonu = linia;
                break;
            case 5:
                przyjaciele[i].email = linia;
                break;
            case 6: {
                przyjaciele[i].adres = linia;
                i++;
                nrLinijki = 0;
            }
            break;
            }
            nrLinijki++;
        }
        plik.close();
    }

    return przyjaciele.size();
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

void zapisDoPliku (vector <Przyjaciel> &przyjaciele, int i) {
    fstream plik;
    const int PIERWSZY_RECORD_W_PLIKU = 0;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);

    if (i != PIERWSZY_RECORD_W_PLIKU) plik << endl;

    plik << przyjaciele[i].id << "|";
    plik << przyjaciele[i].imie << "|";
    plik << przyjaciele[i].nazwisko << "|";
    plik << przyjaciele[i].numerTelefonu << "|";
    plik << przyjaciele[i].email << "|";
    plik << przyjaciele[i].adres << "|";

    plik.close();
}

int dodajPrzyjaciela (vector <Przyjaciel> &przyjaciele, int iloscPrzyjaciol) {

    zwiekszIloscPrzyjaciol(przyjaciele);
    cout << "Podaj imie: " << endl;
    do {
        przyjaciele[iloscPrzyjaciol].imie = wczytajLinieTekstu();
        if (czyTekstMaDozwoloneZnaki(przyjaciele[iloscPrzyjaciol].imie) == false) {
            cout << "Wprowadzone imie jest niepoprawne, wprowadz raz jeszcze" << endl;
        }
    } while (czyTekstMaDozwoloneZnaki(przyjaciele[iloscPrzyjaciol].imie) == false);

    cout << "Podaj nazwisko: " << endl;
    do {
        przyjaciele[iloscPrzyjaciol].nazwisko = wczytajLinieTekstu();
        if (czyTekstMaDozwoloneZnaki(przyjaciele[iloscPrzyjaciol].nazwisko) == false) {
            cout << "Wprowadzone nazwisko jest niepoprawne, wprowadz raz jeszcze" << endl;
        }
    } while (czyTekstMaDozwoloneZnaki(przyjaciele[iloscPrzyjaciol].nazwisko) == false);

    cout << "Podaj numer telefonu: " << endl;
    przyjaciele[iloscPrzyjaciol].numerTelefonu = wczytajLinieTekstu();

    cout << "Podaj e-mail: " << endl;
    do {
        przyjaciele[iloscPrzyjaciol].email = wczytajLinieTekstu();
        if (czyEmailPoprawny(przyjaciele[iloscPrzyjaciol].email) == false) {
            cout << "Wprowadzony e-mail jest niepoprawny, wprowadz raz jeszcze" << endl;
        }
    } while (czyEmailPoprawny(przyjaciele[iloscPrzyjaciol].email) == false);

    cout << "Podaj adres: " << endl;
    przyjaciele[iloscPrzyjaciol].adres = wczytajLinieTekstu();

    if (iloscPrzyjaciol == 0){
        przyjaciele[iloscPrzyjaciol].id = 1;
    }
    else
        przyjaciele[iloscPrzyjaciol].id = przyjaciele [iloscPrzyjaciol-1].id + 1;

    zapisDoPliku (przyjaciele, iloscPrzyjaciol);
    cout << "Dodano osobe do bazy przyjaciol" << endl;
    Sleep(1000);

    return iloscPrzyjaciol = przyjaciele.size();
}

void wyswietlKomunikatZamknieciaWynikowWyszukiwania () {
    cout << endl << "Dowolny klawisz zamknie wyniki wyszukiwania" << endl;
    system("PAUSE");
}

void wyswietlDaneOsoby (vector <Przyjaciel> &przyjaciele, int idOsoby) {
    cout << przyjaciele[idOsoby].id << "|";
    cout << przyjaciele[idOsoby].imie << "|";
    cout << przyjaciele[idOsoby].nazwisko << "|";
    cout << przyjaciele[idOsoby].numerTelefonu << "|";
    cout << przyjaciele[idOsoby].email << "|";
    cout << przyjaciele[idOsoby].adres << "|" << endl;
}

void wyszukajPoImieniu (vector <Przyjaciel> &przyjaciele, int iloscPrzyjaciol, string szukaneImie) {
    int iloscWynikow = 0;

    for (int i = 0; i < iloscPrzyjaciol; i++) {
        if (przyjaciele[i].imie == szukaneImie) {
            wyswietlDaneOsoby(przyjaciele, i);
            ++iloscWynikow;
        }
    }

    if (iloscWynikow == 0) {
        cout << "Brak osoby o tym imieniu w bazie. Wcisnij dowolny klawisz" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

void wyszukajPoNazwisku (vector <Przyjaciel> &przyjaciele, int iloscPrzyjaciol, string szukaneNazwisko) {
    int iloscWynikow = 0;

    for (int i = 0; i < iloscPrzyjaciol; i++) {
        if (przyjaciele[i].nazwisko == szukaneNazwisko) {
            wyswietlDaneOsoby(przyjaciele, i);
            ++iloscWynikow;
        }
    }

    if (iloscWynikow == 0) {
        cout << "Brak osoby o tym imieniu w bazie. Wcisnij dowolny klawisz" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

void wyswietlDaneWszystkichOsob (vector <Przyjaciel> &przyjaciele, int iloscPrzyjaciol) {
    for (int i = 0; i < iloscPrzyjaciol; i++) {
        if (iloscPrzyjaciol > 0) {
            wyswietlDaneOsoby(przyjaciele, i);
        }
    }
    if (iloscPrzyjaciol == 0) {
        cout << "Nie masz przyjaciol :/. Dodaj kogos! ;)" << endl;
        system("PAUSE");
    }
    else wyswietlKomunikatZamknieciaWynikowWyszukiwania();
}

bool czyAdresatJestWKsiazceAdresowej (vector <Przyjaciel> przyjaciele, int idAdresataDoSprawdzenia) {
    bool wynikWyszukiwania = false;

    for (unsigned int i = 0; i < przyjaciele.size(); i++) {
        if (przyjaciele[i].id == idAdresataDoSprawdzenia) {
            wynikWyszukiwania = true;
            i = przyjaciele.size();
        }
    }
    return wynikWyszukiwania;
}

int podbierzIdAdresataDoEdycji (vector <Przyjaciel> przyjaciele) {

    int idEdytowanegoAdresata = 0;

    do {
        system("cls");
        cout << "Podaj ID edytowanego adresata" << endl;
        cin >> idEdytowanegoAdresata;
        if (!czyAdresatJestWKsiazceAdresowej(przyjaciele, idEdytowanegoAdresata)) {
            cout << "Brak w ksiazce adresata o tym numerze ID" << endl;
            Sleep (1000);
            system("cls");
        }
    } while (!czyAdresatJestWKsiazceAdresowej(przyjaciele, idEdytowanegoAdresata));
    return idEdytowanegoAdresata;
}

void nadpiszPlik (vector <Przyjaciel> &przyjaciele) {
    fstream plik;
    const int PIERWSZY_RECORD_W_PLIKU = 0;
    plik.open("ksiazka_adresowa.txt", ios::out);

    if (plik.good() == true) {
        for (unsigned int i = 0; i < przyjaciele.size(); i++) {
            if (i != PIERWSZY_RECORD_W_PLIKU) plik << endl;
            plik << przyjaciele[i].id << "|";
            plik << przyjaciele[i].imie << "|";
            plik << przyjaciele[i].nazwisko << "|";
            plik << przyjaciele[i].numerTelefonu << "|";
            plik << przyjaciele[i].email << "|";
            plik << przyjaciele[i].adres << "|";
        }
        plik.close();
    }
}

int podajPolozenieAdresataPoId (vector <Przyjaciel> przyjaciele, int idAdresataDoSprawdzenia){
    int polozenieAdresataPoId = 0;

    for (unsigned int i = 0; i < przyjaciele.size(); i++) {
        if (przyjaciele[i].id == idAdresataDoSprawdzenia) {
            polozenieAdresataPoId = i;
            i = przyjaciele.size();
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

void dokonajEdycjiDanychAdresata (vector <Przyjaciel> &przyjaciele) {
    int idEdytowanegoAdresata = podbierzIdAdresataDoEdycji (przyjaciele);
    int polozenieAdresataPoNumerzeId = podajPolozenieAdresataPoId (przyjaciele, idEdytowanegoAdresata);

    wyswietlMenuEdycyjne();

    switch (getch()) {
        case'1':
                cout << "Wprowadz nowe imie:" << endl;
            cin.sync();
            getline(cin,przyjaciele[polozenieAdresataPoNumerzeId].imie);
            nadpiszPlik (przyjaciele);
            system("PAUSE");
            break;

        case'2': {
                cout << "Wprowadz nowe nazwisko:" << endl;
            cin.sync();
            getline(cin, przyjaciele[polozenieAdresataPoNumerzeId].nazwisko);
            nadpiszPlik (przyjaciele);
            system("PAUSE");
            break;
        }
        case'3':{
                cout << "Wprowadz nowy numer telefonu:" << endl;
            cin.sync();
            cin >> przyjaciele[polozenieAdresataPoNumerzeId].numerTelefonu;
            nadpiszPlik (przyjaciele);
            system("PAUSE");
            break;
        }
        case'4':{
                cout << "Wprowadz nowy email:" << endl;
            cin.sync();
            getline(cin, przyjaciele[polozenieAdresataPoNumerzeId].email);
            nadpiszPlik (przyjaciele);
            system("PAUSE");
            break;
        }
        case'5':{
                cout << "Wprowadz nowy adres:" << endl;
            cin.sync();
            getline(cin, przyjaciele[polozenieAdresataPoNumerzeId].adres);
            nadpiszPlik (przyjaciele);
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

int usunAdresata (vector <Przyjaciel> &przyjaciele, int iloscPrzyjaciol) {
    int idAdresataDoUsuniecia = 0;
    cout << "Podaj ID adresata do usuniecia z ksiazki adresowej" << endl;

    do {
        cin >> idAdresataDoUsuniecia;
        if (!czyAdresatJestWKsiazceAdresowej (przyjaciele, idAdresataDoUsuniecia)) {
            cout << "Adresata o podanym ID nie ma w Ksiazce Adresowej. Podaj poprawne ID." << endl;
        }
    } while (!czyAdresatJestWKsiazceAdresowej (przyjaciele, idAdresataDoUsuniecia));

    if (czyUzytkownikPotwierdzilUsuniecieAdresata()) {
        for (unsigned int i = 0; i < przyjaciele.size(); i++) {
            if (przyjaciele[i].id == idAdresataDoUsuniecia) {
                przyjaciele.erase(przyjaciele.begin() + i);
                iloscPrzyjaciol = przyjaciele.size();
                i = przyjaciele.size();
                nadpiszPlik (przyjaciele);
                cout << "Adresat o wskazanym ID zostal usuniety z Ksiazki Adresowej" << endl;
                system("PAUSE");
            }
        }
    }
    else {
        cout << "Operacja usuniecia adresata anulowana przez uzytkownika" << endl;
        system("PAUSE");
    }

    return iloscPrzyjaciol;
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
    vector <Przyjaciel> przyjaciele;
    int iloscPrzyjaciol = 0;

    iloscPrzyjaciol = odczytPliku (przyjaciele, iloscPrzyjaciol);

    while(true) {
        wyswietlMenuGlowne ();

        char wybor = getch();
        switch (wybor) {
        case'1':
                iloscPrzyjaciol = dodajPrzyjaciela (przyjaciele, iloscPrzyjaciol);
            break;

        case'2': {
                cout << "Podaj imie do wyszukania" <<endl;
            string szukaneImie = wczytajLinieTekstu();
            wyszukajPoImieniu (przyjaciele, iloscPrzyjaciol, szukaneImie);
            break;
        }
        case'3':{
                cout << "Podaj nazwisko do wyszukania" <<endl;
            string szukaneNazwisko = wczytajLinieTekstu();
            wyszukajPoNazwisku (przyjaciele, iloscPrzyjaciol, szukaneNazwisko);
            break;
        }
        case'4':{
                cout << "Lista danych Twoich przyjaciol wyglada nastepujaco: " << endl;
            wyswietlDaneWszystkichOsob(przyjaciele, iloscPrzyjaciol);
            break;
        }
        case'5':{
            if (iloscPrzyjaciol == 0) {
                cout << "Baza adresatow jest pusta. Dodaj kogos" << endl;
                Sleep (1000);
            } else
                iloscPrzyjaciol = usunAdresata (przyjaciele, iloscPrzyjaciol);
            break;
        }
        case'6':{
            if (iloscPrzyjaciol == 0) {
                cout << "Baza adresatow jest pusta. Dodaj kogos" << endl;
                Sleep (1000);
            } else
                dokonajEdycjiDanychAdresata(przyjaciele);
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
