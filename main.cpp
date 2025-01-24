#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

struct Adresat {
    int idAdresata = 0;
    int idUzytkownika = 0;
    string imie ="";
    string nazwisko ="";
    int numerTelefonu = 0;
    string eMail ="";
    string adres ="";
};

struct Uzytkownik {
    int idUzytkownika;
    string loginUzytkownika;
    string haslo;
};

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while (true) {
        cin.sync();
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie." << endl;
    }
    return liczba;
}

string wczytajAdresEmail () {
    string wejscie = "";
    bool czyPosiadaMalpe = false;
    bool czyPosiadaKropke = false;

    while (true) {
        cin.sync();
        cout << "Podaj adres e-mail" << endl;
        getline(cin, wejscie);

        for (size_t i = 0; i < wejscie.length(); i++) {
            if (wejscie[i] == '@') czyPosiadaMalpe = true;
            if (wejscie[i] == '.') czyPosiadaKropke = true;
        }

        if (czyPosiadaMalpe && czyPosiadaKropke) break;
        cout << "To nie jest adres e-mail. Wpisz ponownie." << endl;
        czyPosiadaMalpe = false;
        czyPosiadaKropke = false;
    }
    return wejscie;
}

string wczytajLinie() {
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak = (0);

    while (true) {
        cin.sync();
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
        system("cls");
    }
    return znak;
}

void wyswietlMenuLogowania() {
    system("cls");
    cout << "MENU LOGOWANIA" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "9. Zakoncz program" << endl << endl;
}

void wyswietlMenuUzytkownika() {
    system("cls");
    cout << "KSIAZKA ADRESOWA" << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "9. Wyloguj sie" << endl << endl;
}

void wyswietlMenuEdycjiAdresatow() {
    system("cls");
    cout << "WYBIERZ DANE DO EDYCJI" << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. E-mail" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu" << endl;
}

int dodajNowaOsobeDoKsiazki (vector <Adresat> &adresaci, int idOstatniegoAdresata) {

    Adresat adresat;
    idOstatniegoAdresata++;

    adresat.idAdresata = idOstatniegoAdresata;
    cout << "Podaj imie: ";
    adresat.imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    adresat.nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    adresat.numerTelefonu = wczytajLiczbeCalkowita();
    cout << "Podaj e-mail: ";
    adresat.eMail = wczytajAdresEmail();
    cout << "Podaj adres: ";
    adresat.adres = wczytajLinie();

    adresaci.push_back(adresat);

    return idOstatniegoAdresata;
}

void wyszukajPoImieniu (vector <Adresat> adresaci) {
    string wyszukiwaneImie="";
    bool czyZnalezionoOsobe = false;
    cout << "Podaj imie do wyszukania w ksiazce adresowej: ";
    cin >> wyszukiwaneImie;

    system("cls");
    for (size_t i=0; i < adresaci.size(); i++) {
        if(adresaci[i].imie == wyszukiwaneImie) {
            czyZnalezionoOsobe = true;
            cout <<"ID: \t\t\t\t" << adresaci[i].idAdresata << endl;
            cout <<"Imie: \t\t\t\t" << adresaci[i].imie << endl;
            cout <<"Nazwisko: \t\t\t" << adresaci[i].nazwisko << endl;
            cout <<"Numer telefonu: \t\t" << adresaci[i].numerTelefonu << endl;
            cout <<"E-mail: \t\t\t" << adresaci[i].eMail << endl;
            cout <<"Adres: \t\t\t\t" << adresaci[i].adres << endl<< endl;
        }
    }
    if (czyZnalezionoOsobe == false) {
        cout << "Niestety nie ma takiej osoby w ksiazce adresowej." << endl;
    }

    system("pause");
}

void wyszukajPoNazwisku (vector <Adresat> adresaci) {
    string wyszukiwaneNazwisko="";
    bool czyZnalezionoOsobe = false;
    cout << "Podaj nazwisko do wyszukania w ksiazce adresowej: ";
    cin >> wyszukiwaneNazwisko;

    system("cls");
    for (size_t i=0; i < adresaci.size(); i++) {
        if(adresaci[i].nazwisko == wyszukiwaneNazwisko) {
            czyZnalezionoOsobe = true;
            cout <<"ID: \t\t\t\t" << adresaci[i].idAdresata << endl;
            cout <<"Imie: \t\t\t\t" << adresaci[i].imie << endl;
            cout <<"Nazwisko: \t\t\t" << adresaci[i].nazwisko << endl;
            cout <<"Numer telefonu: \t\t" << adresaci[i].numerTelefonu << endl;
            cout <<"E-mail: \t\t\t" << adresaci[i].eMail << endl;
            cout <<"Adres: \t\t\t\t" << adresaci[i].adres << endl<< endl;
        }
    }
    if (czyZnalezionoOsobe == false) {
        cout << "Niestety nie ma takiej osoby w ksiazce adresowej." << endl;
    }

    system("pause");
}

void wypiszWszystkieOsoby (vector <Adresat> adresaci) {

    system("cls");
    if (adresaci.size() > 0) {
        for (size_t i=0; i < adresaci.size(); i++) {
            cout <<"ID: \t\t\t\t" << adresaci[i].idAdresata << endl;
            cout <<"Imie: \t\t\t\t" << adresaci[i].imie << endl;
            cout <<"Nazwisko: \t\t\t" << adresaci[i].nazwisko << endl;
            cout <<"Numer telefonu: \t\t" << adresaci[i].numerTelefonu << endl;
            cout <<"E-mail: \t\t\t" << adresaci[i].eMail << endl;
            cout <<"Adres: \t\t\t\t" << adresaci[i].adres << endl<< endl;
        }
    } else {
        cout << "Niestety, ksiazka adresowa jest pusta." << endl;
    }
    system("pause");
}

void edytujDaneAdresata (vector <Adresat> &adresaci) {

    int idAdresataDoEdycji;
    bool czyAdresatJestWKsiazce = false;
    cout << "Podaj ID adresata do edycji!" << endl;
    idAdresataDoEdycji = wczytajLiczbeCalkowita();

    for (vector <Adresat> :: iterator itr = adresaci.begin();
            itr != adresaci.end(); itr++) {
        if (itr->idAdresata == idAdresataDoEdycji) {
            wyswietlMenuEdycjiAdresatow();
            czyAdresatJestWKsiazce = true;
            char wybor;
            wybor = wczytajZnak();
            switch (wybor) {
            case '1':
                itr->imie = wczytajLinie();
                break;
            case '2':
                itr->nazwisko = wczytajLinie();
                break;
            case '3':
                itr->numerTelefonu = wczytajLiczbeCalkowita();
                break;
            case '4':
                itr->eMail = wczytajAdresEmail();
                break;
            case '5':
                itr->adres = wczytajLinie();
                break;
            case '6':
                exit(0);
                break;
            }
        }
    }
    if (czyAdresatJestWKsiazce == false) {
        cout << "Adresat o podanym numerze ID nie wystepuje w Ksiazce Adresowej" << endl;
        system("pause");
    }
    system("cls");
}

int usunAdresata (vector <Adresat> &adresaci, int idOstatniegoAdresata) {

    int idAdresataDoUsuniecia;
    bool czyAdresatOPodanymIdJestWKsiazce = false;

    cout << "Podaj ID adresata do usuniecia" << endl;
    idAdresataDoUsuniecia = wczytajLiczbeCalkowita();

    cout << "Czy jestes pewien, ze chcesz usunac tego adresata? - wcisnij 't'" << endl;
    if (getch() == 't') {
        for (vector <Adresat> :: iterator itr = adresaci.begin();
                itr != adresaci.end(); itr++) {

            if (itr->idAdresata == idAdresataDoUsuniecia) {
                czyAdresatOPodanymIdJestWKsiazce = true;
                adresaci.erase(itr);
                idOstatniegoAdresata = adresaci[adresaci.size()-1].idAdresata;
                if(itr == adresaci.end()) {
                    break;
                }
            }
        }
    }
    if (czyAdresatOPodanymIdJestWKsiazce == false) {
        system("cls");
        cout << "Adresata o podanym numerze ID nie ma w ksiazce!" << endl;
        system("pause");
    }

    return idOstatniegoAdresata;
}

void zapiszKsiazkeAdresowa(vector <Adresat> adresaci) {
    fstream plik;
    plik.open("Adresaci.txt", ios::out);

    for (size_t i = 0; i < adresaci.size(); i++) {
        if(i > 0) plik << endl;
        plik << adresaci[i].idAdresata << "|";
        plik << adresaci[i].idUzytkownika << "|";
        plik << adresaci[i].imie << "|";
        plik << adresaci[i].nazwisko << "|";
        plik << adresaci[i].numerTelefonu << "|";
        plik << adresaci[i].eMail << "|";
        plik << adresaci[i].adres << "|";
    }

    plik.close();
}

void zapiszDaneUzytkownikow(vector <Uzytkownik> uzytkownicy) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    for (size_t i = 0; i < uzytkownicy.size(); i++) {
        if(i > 0) plik << endl;
        plik << uzytkownicy[i].idUzytkownika << "|";
        plik << uzytkownicy[i].loginUzytkownika << "|";
        plik << uzytkownicy[i].haslo << "|";
    }

    plik.close();
}

int odczytDanychKsiazkiAdresowej (vector <Adresat> &adresaci) {
    fstream plik;
    int idOstatniegoAdresata = 0;
    int nrLinii = 1;
    Adresat adresat;

    plik.open("Adresaci.txt", ios::in);

    if (plik.good() == false) {
        cout << "Plik nie istnieje!";
        return idOstatniegoAdresata;
    }

    string linia;
    while (getline(plik,linia,'|')) {
        switch (nrLinii) {
        case 1:
            adresat.idAdresata = atoi(linia.c_str());
            idOstatniegoAdresata = adresat.idAdresata;
            break;
        case 2:
            adresat.idUzytkownika = atoi(linia.c_str());
            break;
        case 3:
            adresat.imie = linia;
            break;
        case 4:
            adresat.nazwisko = linia;
            break;
        case 5:
            adresat.numerTelefonu = stoi(linia);
            break;
        case 6:
            adresat.eMail = linia;
            break;
        case 7:
            adresat.adres = linia;
            adresaci.push_back(adresat);
            nrLinii = 0;
            break;
        }
        nrLinii++;
    }

    plik.close();

    return idOstatniegoAdresata;
}

int odczytDanychLogowaniaUzytkownikow (vector <Uzytkownik> &uzytkownicy) {
    fstream plik;
    int idOstatniegoUzytkownika = 0;
    int nrLinii = 1;
    Uzytkownik uzytkownik;

    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == false) {
        cout << "Plik nie istnieje!";
        return idOstatniegoUzytkownika;
    }

    string linia;
    while (getline(plik,linia,'|')) {
        switch (nrLinii) {
        case 1:
            uzytkownik.idUzytkownika = atoi(linia.c_str());
            idOstatniegoUzytkownika = uzytkownik.idUzytkownika;
            break;
        case 2:
            uzytkownik.loginUzytkownika = linia;
            break;
        case 3:
            uzytkownik.haslo = linia;
            uzytkownicy.push_back(uzytkownik);
            nrLinii = 0;
            break;
        }
        nrLinii++;
    }
    plik.close();

    return idOstatniegoUzytkownika;
}

void panelOpcjiUzytkownika(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika) {
    vector <Adresat> adresaci;
    int idOstatniegoAdresata = 0;

    char wybor = (0);

    idOstatniegoAdresata = odczytDanychKsiazkiAdresowej(adresaci);

    while(idZalogowanegoUzytkownika != 0) {
        wyswietlMenuUzytkownika();
        wybor = wczytajZnak();
        system("cls");

        switch(wybor) {
        case '1':
            idOstatniegoAdresata = dodajNowaOsobeDoKsiazki(adresaci, idOstatniegoAdresata);
            zapiszKsiazkeAdresowa(adresaci);
            break;
        case '2':
            wyszukajPoImieniu(adresaci);
            break;
        case '3':
            wyszukajPoNazwisku(adresaci);
            break;
        case '4':
            wypiszWszystkieOsoby(adresaci);
            break;
        case '5':
            idOstatniegoAdresata = usunAdresata(adresaci, idOstatniegoAdresata);
            break;
        case '6':
            edytujDaneAdresata(adresaci);
            break;
        case '9':
            zapiszKsiazkeAdresowa(adresaci);
            idZalogowanegoUzytkownika = 0;
            break;
        }
    }
}

int logowanie(vector <Uzytkownik> uzytkownicy) {
    string login, haslo;
    cout << "Podaj login: ";
    cin >> login;

    for (size_t i = 0; i < uzytkownicy.size(); i++) {
        if (uzytkownicy[i].loginUzytkownika == login) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 2 sekundy przed kolejna proba" << endl;
            Sleep(2000);
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

int rejestracjaNowegoUzytkownika (vector <Uzytkownik> &uzytkownicy, int idOstatniegoUzytkownika) {
    string login, haslo;
    Uzytkownik uzytkownik;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;

    size_t i=0;
    while(i < uzytkownicy.size()) {
        if (uzytkownicy[i].loginUzytkownika == login) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> login;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;

    idOstatniegoUzytkownika++;
    uzytkownik.loginUzytkownika = login;
    uzytkownik.haslo = haslo;
    uzytkownik.idUzytkownika = idOstatniegoUzytkownika;
    uzytkownicy.push_back(uzytkownik);
    cout << "Konto zalozone " << endl;
    Sleep(1000);

    return idOstatniegoUzytkownika;
}

int main() {

    vector <Uzytkownik> uzytkownicy;
    int idOstatniegoUzytkownika = 0;
    idOstatniegoUzytkownika = odczytDanychLogowaniaUzytkownikow (uzytkownicy);

    int idZalogowanegoUzytkownika = 0;
    char wybor = (0);

    while(true) {
        wyswietlMenuLogowania();
        wybor = wczytajZnak();
        system("cls");

        switch(wybor) {
        case '1':
            //Logowanie
            idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            panelOpcjiUzytkownika(uzytkownicy, idZalogowanegoUzytkownika);
            break;
        case '2':
            //Rejestracja
            idOstatniegoUzytkownika = rejestracjaNowegoUzytkownika (uzytkownicy, idOstatniegoUzytkownika);
            zapiszDaneUzytkownikow(uzytkownicy);
            break;
        case '9':
            //Zakonczenie programu
            exit(0);
            break;
        }
    }

    return 0;
}
