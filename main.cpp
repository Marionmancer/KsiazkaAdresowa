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

int zwrocIdOstatniegoAdresataWPliku (){

    int idOstatniegoAdresata = 0;
    fstream plik;
    string nazwaPliku = "Adresaci.txt";

    plik.open(nazwaPliku, ios::in);

    if (plik.good() == false) {
        return idOstatniegoAdresata;
    }

    if(plik.is_open()) {
        plik.seekg(-1,ios_base::end);

        bool czyNadalPoszukujeWPetliOstatniegoId = true;
        while(czyNadalPoszukujeWPetliOstatniegoId) {
            char ch;
            plik.get(ch);

            if((int)plik.tellg() <= 1) {
                plik.seekg(0);
                czyNadalPoszukujeWPetliOstatniegoId = false;
            }
            else if(ch == '\n') {
                czyNadalPoszukujeWPetliOstatniegoId = false;
            }
            else {
                plik.seekg(-2,ios_base::cur);
            }
        }
        string ostatnieIdOdczytaneZPliku = "";
        getline(plik,ostatnieIdOdczytaneZPliku,'|');
        idOstatniegoAdresata = atoi(ostatnieIdOdczytaneZPliku.c_str());
    }
    plik.close();

    return idOstatniegoAdresata;
}

void dodajNowaOsobeDoKsiazki (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    Adresat adresat;
    int idOstatniegoAdresata=0;
    idOstatniegoAdresata = zwrocIdOstatniegoAdresataWPliku();
    idOstatniegoAdresata++;

    adresat.idAdresata = idOstatniegoAdresata;
    adresat.idUzytkownika = idZalogowanegoUzytkownika;
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
}

void wyszukajPoImieniu (vector <Adresat> adresaci, int idZalogowanegoUzytkownika) {
    string wyszukiwaneImie="";
    bool czyZnalezionoOsobe = false;
    cout << "Podaj imie do wyszukania w ksiazce adresowej: ";
    cin >> wyszukiwaneImie;

    system("cls");
    for (size_t i=0; i < adresaci.size(); i++) {
        if(adresaci[i].imie == wyszukiwaneImie && adresaci[i].idUzytkownika == idZalogowanegoUzytkownika) {
            czyZnalezionoOsobe = true;
            cout <<"ID adresata: \t\t\t" << adresaci[i].idAdresata << endl;
            cout <<"ID uzytkownika: \t\t" << adresaci[i].idUzytkownika << endl;
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

void wyszukajPoNazwisku (vector <Adresat> adresaci, int idZalogowanegoUzytkownika) {
    string wyszukiwaneNazwisko="";
    bool czyZnalezionoOsobe = false;
    cout << "Podaj nazwisko do wyszukania w ksiazce adresowej: ";
    cin >> wyszukiwaneNazwisko;

    system("cls");
    for (size_t i=0; i < adresaci.size(); i++) {
        if(adresaci[i].nazwisko == wyszukiwaneNazwisko && adresaci[i].idUzytkownika == idZalogowanegoUzytkownika) {
            czyZnalezionoOsobe = true;
            cout <<"ID adresata: \t\t\t" << adresaci[i].idAdresata << endl;
            cout <<"ID uzytkownika: \t\t" << adresaci[i].idUzytkownika << endl;
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

void wypiszWszystkieOsoby (vector <Adresat> adresaci, int idZalogowanegoUzytkownika) {

    system("cls");
    if (adresaci.size() > 0) {
        for (size_t i=0; i < adresaci.size(); i++) {
            if (adresaci[i].idUzytkownika == idZalogowanegoUzytkownika){
                cout <<"ID adresata: \t\t\t" << adresaci[i].idAdresata << endl;
                cout <<"ID uzytkownika: \t\t" << adresaci[i].idUzytkownika << endl;
                cout <<"Imie: \t\t\t\t" << adresaci[i].imie << endl;
                cout <<"Nazwisko: \t\t\t" << adresaci[i].nazwisko << endl;
                cout <<"Numer telefonu: \t\t" << adresaci[i].numerTelefonu << endl;
                cout <<"E-mail: \t\t\t" << adresaci[i].eMail << endl;
                cout <<"Adres: \t\t\t\t" << adresaci[i].adres << endl<< endl;
            }
        }
    } else {
        cout << "Niestety, ksiazka adresowa jest pusta." << endl;
    }
    system("pause");
}

void edytujDaneAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    int idAdresataDoEdycji;
    bool czyAdresatJestWKsiazce = false;
    cout << "Podaj ID adresata do edycji!" << endl;
    idAdresataDoEdycji = wczytajLiczbeCalkowita();

    for (vector <Adresat> :: iterator itr = adresaci.begin();
            itr != adresaci.end(); itr++) {
        if (itr->idAdresata == idAdresataDoEdycji && itr->idUzytkownika == idZalogowanegoUzytkownika) {
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

void usunAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    int idAdresataDoUsuniecia;
    bool czyAdresatOPodanymIdJestWKsiazce = false;

    cout << "Podaj ID adresata do usuniecia" << endl;
    idAdresataDoUsuniecia = wczytajLiczbeCalkowita();

    cout << "Czy jestes pewien, ze chcesz usunac tego adresata? - wcisnij 't'" << endl;
    if (getch() == 't') {
        for (vector <Adresat> :: iterator itr = adresaci.begin();
                itr != adresaci.end(); itr++) {

            if (itr->idAdresata == idAdresataDoUsuniecia && itr->idUzytkownika == idZalogowanegoUzytkownika) {
                czyAdresatOPodanymIdJestWKsiazce = true;
                adresaci.erase(itr);
                cout << "Adresata o podanym numerze ID zostal usuniety!" << endl;
                system("pause");
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
}

void zmianaHaslaLogowania(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika){
    string haslo;
    const int POZYCJA_ZALOGOWANEGO_UZYTKOWNIKA_W_WEKTORZE = idZalogowanegoUzytkownika - 1;

    cout << "Podaj haslo: ";
    cin.sync();
    cin >> haslo;

    uzytkownicy[POZYCJA_ZALOGOWANEGO_UZYTKOWNIKA_W_WEKTORZE].haslo = haslo;
    cout << "Haslo zostalo zmienione " << endl;
    Sleep(1000);
}

//int zwrocParametrAdresataZWczytanejLinijki (string wczytanaLinijka, int numerParametru){
//    int wczytanyParametr = 0;
//
//    int nrLinii = 1;
//    string linia = "";
//    while (getline(wczytanaLinijka,linia,'|')) {
//        switch (nrLinii) {
//        case numerParametru:
//            wczytanyParametr = atoi(linia.c_str());
//            break;
//        default: ;
//        }
//        nrLinii++;
//    }
//
//    return wczytanyParametr;
//}

void zapiszKsiazkeAdresowa(vector <Adresat> adresaci) {
    fstream plikTymczasowy;
    fstream plikOryginalny;
    int nrLinii = 1;
    int idAdresataWPlikuOryginalnym = 0;
    int idUzytkownikaWPlikuOryginalnym = 0;

    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out);
    plikOryginalny.open("Adresaci.txt", ios::in);
    if (plikOryginalny.good() == true) {
        string linia;
        int numerPozycjiAdresataWWektorze = 0;
        while (getline(plik,linia)) {
            idAdresataWPlikuOryginalnym = atoi(linia.substr(0,linia.find('|')).c_str());
            idUzytkownikaWPlikuOryginalnym = atoi(linia.substr(linia.find('|') + 1,linia.find('|',2)).c_str());
        }
    }

    for (size_t i = 0; i < adresaci.size(); i++) {
        if(i > 0) plikTymczasowy << endl;
        plikTymczasowy << adresaci[i].idAdresata << "|";
        plikTymczasowy << adresaci[i].idUzytkownika << "|";
        plikTymczasowy << adresaci[i].imie << "|";
        plikTymczasowy << adresaci[i].nazwisko << "|";
        plikTymczasowy << adresaci[i].numerTelefonu << "|";
        plikTymczasowy << adresaci[i].eMail << "|";
        plikTymczasowy << adresaci[i].adres << "|";
    }

    plikTymczasowy.close();
    //Usunac plik adresaci.txt
    //Zmienic nazwe pliku tymczasowego
}

void zapiszDaneUzytkownikow(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika) {
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

void odczytDanychKsiazkiAdresowej (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    fstream plik;
    int nrLinii = 1;
    Adresat adresat;

    plik.open("Adresaci.txt", ios::in);

    if (plik.good() == true) {
        string linia;
        while (getline(plik,linia,'|')) {
            switch (nrLinii) {
            case 1:
                adresat.idAdresata = atoi(linia.c_str());
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
                if (adresat.idUzytkownika == idZalogowanegoUzytkownika)
                    adresaci.push_back(adresat);
                nrLinii = 0;
                break;
            }
            nrLinii++;
        }
        plik.close();
    }
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

void panelMenuUzytkownika(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    vector <Adresat> adresaci;
    odczytDanychKsiazkiAdresowej (adresaci, idZalogowanegoUzytkownika);

    char wybor = (0);

    while(idZalogowanegoUzytkownika != 0) {
        wyswietlMenuUzytkownika();
        wybor = wczytajZnak();
        system("cls");

        switch(wybor) {
        case '1':
            dodajNowaOsobeDoKsiazki(adresaci, idZalogowanegoUzytkownika);
            zapiszKsiazkeAdresowa(adresaci);
            break;
        case '2':
            wyszukajPoImieniu(adresaci, idZalogowanegoUzytkownika);
            break;
        case '3':
            wyszukajPoNazwisku(adresaci, idZalogowanegoUzytkownika);
            break;
        case '4':
            wypiszWszystkieOsoby(adresaci, idZalogowanegoUzytkownika);
            break;
        case '5':
            usunAdresata(adresaci, idZalogowanegoUzytkownika);
            zapiszKsiazkeAdresowa(adresaci);
            break;
        case '6':
            edytujDaneAdresata(adresaci, idZalogowanegoUzytkownika);
            zapiszKsiazkeAdresowa(adresaci);
            break;
        case '7':
            zmianaHaslaLogowania(uzytkownicy, idZalogowanegoUzytkownika);
            zapiszDaneUzytkownikow(uzytkownicy, idZalogowanegoUzytkownika);
            break;
        case '9':
            idZalogowanegoUzytkownika = 0;
            break;
        }
    }
}

int logowanieUzytkownika(vector <Uzytkownik> uzytkownicy) {
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
            idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
            panelMenuUzytkownika(uzytkownicy, idZalogowanegoUzytkownika);
            break;
        case '2':
            idOstatniegoUzytkownika = rejestracjaNowegoUzytkownika (uzytkownicy, idOstatniegoUzytkownika);
            zapiszDaneUzytkownikow(uzytkownicy, idZalogowanegoUzytkownika);
            break;
        case '9':
            exit(0);
            break;
        }
    }
    return 0;
}
