#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

void zwiekszIloscUzytkownikow (vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik tempUser = { 0, "", "" };
    uzytkownicy.push_back(tempUser);
}

struct Adresat {
    int id, idUzytkownika;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void zwiekszIloscAdresatow (vector <Adresat> &adresaci) {
    Adresat nowyAdresat = { 0, 0, "", "" , "" , "" , "" };
    adresaci.push_back(nowyAdresat);
}

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

void odczytPlikuAdresaci (vector <Adresat> &adresaci) {
    fstream plik;
    plik.open("Adresaci.txt", ios::in);
    string linia;
    int nrLinijki = 1;

    if (plik.good()) {
        while (getline(plik,linia,'|')) {
            switch (nrLinijki) {
            case 1:
                zwiekszIloscAdresatow(adresaci);
                adresaci[adresaci.size() - 1].id = atoi(linia.c_str());
                break;
            case 2:
                adresaci[adresaci.size() - 1].idUzytkownika = atoi(linia.c_str());
                break;
            case 3:
                adresaci[adresaci.size() - 1].imie = linia;
                break;
            case 4:
                adresaci[adresaci.size() - 1].nazwisko = linia;
                break;
            case 5:
                adresaci[adresaci.size() - 1].numerTelefonu = linia;
                break;
            case 6:
                adresaci[adresaci.size() - 1].email = linia;
                break;
            case 7: {
                adresaci[adresaci.size() - 1].adres = linia;
                nrLinijki = 0;
            }
            break;
            }
            nrLinijki++;
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

    string nazwa, haslo;
    zwiekszIloscUzytkownikow (uzytkownicy);

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

    uzytkownicy[uzytkownicy.size() - 1].nazwa = nazwa;
    uzytkownicy[uzytkownicy.size() - 1].haslo = haslo;

    if ((uzytkownicy.size() - 1) == 0){
        uzytkownicy[uzytkownicy.size() - 1].id = 1;
    }
    else
        uzytkownicy[uzytkownicy.size() - 1].id = uzytkownicy [uzytkownicy.size() - 2].id + 1;

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

void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
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

void zapisAdresatowDoPliku (vector <Adresat> &adresaci) {
    fstream plik;
    const int PIERWSZY_RECORD_W_PLIKU = 0;
    plik.open("Adresaci.txt", ios::out | ios::app);

    if ((adresaci.size() - 1) > PIERWSZY_RECORD_W_PLIKU) plik << endl;

    plik << adresaci[adresaci.size() - 1].id << "|";
    plik << adresaci[adresaci.size() - 1].idUzytkownika << "|";
    plik << adresaci[adresaci.size() - 1].imie << "|";
    plik << adresaci[adresaci.size() - 1].nazwisko << "|";
    plik << adresaci[adresaci.size() - 1].numerTelefonu << "|";
    plik << adresaci[adresaci.size() - 1].email << "|";
    plik << adresaci[adresaci.size() - 1].adres << "|";

    plik.close();
}

void dodajAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    zwiekszIloscAdresatow(adresaci);
    cout << "Podaj imie: " << endl;

    adresaci[adresaci.size() - 1].idUzytkownika = idZalogowanegoUzytkownika;

    do {
        adresaci[adresaci.size() - 1].imie = wczytajLinieTekstu();
        if (czyTekstMaDozwoloneZnaki(adresaci[adresaci.size() - 1].imie) == false) {
            cout << "Wprowadzone imie jest niepoprawne, wprowadz raz jeszcze" << endl;
        }
    } while (czyTekstMaDozwoloneZnaki(adresaci[adresaci.size() - 1].imie) == false);

    cout << "Podaj nazwisko: " << endl;
    do {
        adresaci[adresaci.size() - 1].nazwisko = wczytajLinieTekstu();
        if (czyTekstMaDozwoloneZnaki(adresaci[adresaci.size() - 1].nazwisko) == false) {
            cout << "Wprowadzone nazwisko jest niepoprawne, wprowadz raz jeszcze" << endl;
        }
    } while (czyTekstMaDozwoloneZnaki(adresaci[adresaci.size() - 1].nazwisko) == false);

    cout << "Podaj numer telefonu: " << endl;
    adresaci[adresaci.size() - 1].numerTelefonu = wczytajLinieTekstu();

    cout << "Podaj e-mail: " << endl;
    do {
        adresaci[adresaci.size() - 1].email = wczytajLinieTekstu();
        if (czyEmailPoprawny(adresaci[adresaci.size() - 1].email) == false) {
            cout << "Wprowadzony e-mail jest niepoprawny, wprowadz raz jeszcze" << endl;
        }
    } while (czyEmailPoprawny(adresaci[adresaci.size() - 1].email) == false);

    cout << "Podaj adres: " << endl;
    adresaci[adresaci.size() - 1].adres = wczytajLinieTekstu();

    if ((adresaci.size() - 1) == 0){
        adresaci[adresaci.size() - 1].id = 1;
    }
    else
        adresaci[adresaci.size() - 1].id = adresaci [adresaci.size() - 2].id + 1;

    zapisAdresatowDoPliku (adresaci);
    cout << "Dodano osobe do bazy adresatow" << endl;
    Sleep(1000);
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

void wyszukajPoImieniu (vector <Adresat> &adresaci, string szukaneImie) {
    int iloscWynikow = 0;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
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

void wyszukajPoNazwisku (vector <Adresat> &adresaci, string szukaneNazwisko) {
    int iloscWynikow = 0;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
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

void wyswietlDaneWszystkichOsob (vector <Adresat> &adresaci) {
    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if (adresaci.size() > 0) {
            wyswietlDaneOsoby(adresaci, i);
        }
    }
    if (adresaci.size() == 0) {
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
    plik.open("Adresaci.txt", ios::out);

    if (plik.good() == true) {
        for (unsigned int i = 0; i < adresaci.size(); i++) {
            if (i != PIERWSZY_RECORD_W_PLIKU) plik << endl;
            plik << adresaci[i].id << "|";
            plik << adresaci[i].idUzytkownika << "|";
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

void dokonajEdycjiDanychAdresata (vector <Adresat> &adresaci) {
    int idEdytowanegoAdresata = podbierzIdAdresataDoEdycji (adresaci);
    int polozenieAdresataPoNumerzeId = podajPolozenieAdresataPoId (adresaci, idEdytowanegoAdresata);

    wyswietlMenuEdycjiDanychAdresatow();

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

void usunAdresata (vector <Adresat> &adresaci) {
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
}

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0;

    odczytPlikuAdresaci (adresaci);

    while (true) {
        if (idZalogowanegoUzytkownika == 0) {

            wyswietlMenuLogowania();

            char wybor = getch();
            switch (wybor) {

            case'1':
                    rejestracjaUzytkownika(uzytkownicy);
                break;

            case'2':
                    idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                break;

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

            case'2': {
                    cout << "Podaj imie do wyszukania" <<endl;
                string szukaneImie = wczytajLinieTekstu();
                wyszukajPoImieniu (adresaci, szukaneImie);
                break;
            }
            case'3':{
                    cout << "Podaj nazwisko do wyszukania" <<endl;
                string szukaneNazwisko = wczytajLinieTekstu();
                wyszukajPoNazwisku (adresaci, szukaneNazwisko);
                break;
            }
            case'4':{
                    cout << "Lista danych Twoich adresatow wyglada nastepujaco: " << endl;
                wyswietlDaneWszystkichOsob(adresaci);
                break;
            }
            case'5':{
                if (adresaci.size() == 0) {
                    cout << "Baza adresatow jest pusta. Dodaj kogos" << endl;
                    Sleep (1000);
                } else
                    usunAdresata (adresaci);
                break;
            }
            case'6':{
                if (adresaci.size() == 0) {
                    cout << "Baza adresatow jest pusta. Dodaj kogos" << endl;
                    Sleep (1000);
                } else
                    dokonajEdycjiDanychAdresata(adresaci);
                break;
            }
            case'7':
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            break;

            case'9':
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
