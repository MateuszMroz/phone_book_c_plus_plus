#include <iostream>
#include <fstream>      // wysylanie i pobieranie z pliku txt
#include <windows.h>    // system ("cls")
#include <cstdlib>      // exit
#include <time.h>       // funkcja Sleep
#include <string>       // funkcja getline
#include <conio.h>      // funkcja getch()

using namespace std;

struct AdressBook {
    int id;
    string name;
    string surname;
    string adress;
    string email;
    long int number;
    AdressBook *nextElement;
};
void uptakeList(AdressBook *&start, int *howPerson);
void addNewPerson(AdressBook *&start, int *amountOfContacts);
void showPersons(AdressBook *&start, int *howPeople);
void findPerson(AdressBook *&start, int *howUsers);
void deletePerson(AdressBook *&start, int *howUsers);
void deleteOldTxt(AdressBook *&start, int *howPerson);
void sendToTxt(AdressBook *&start, int *howPerson);
void deleteAll(AdressBook *&start);

int main() {

    AdressBook *start=NULL;

    int howContacts=0;
    char choice;

    uptakeList(start,&howContacts);

    cout<<"\n\n================================"<<endl<<endl;
    cout<<"\tKSIAZKA ADRESOWA"<<endl<<endl;
    cout<<"================================"<<endl<<endl;
    Sleep(1500);
    while(true) {
        system("cls");
        cout<<endl;
        cout<<"Kontaktow w bazie: "<<howContacts<<endl;
        cout<<"==============================="<<endl<<endl;
        cout<<"WYBIERZ OPCJE Z MENU(1..5)"<<endl<<endl;
        cout<<"1. DODAJ NOWY KONTAKT."<<endl<<endl;
        cout<<"2. WYSZUKAJ."<<endl<<endl;
        cout<<"3. WYSWIETL WSZYSTKIE KONTAKTY."<<endl<<endl;
        cout<<"4. USUN KONTAKT."<<endl<<endl;
        cout<<"5. WYJSCIE."<<endl<<endl;

        choice=getch();  // nie trzeba czekac na enter
        switch(choice) {
        case '1': {
            addNewPerson(start,&howContacts);
            break;
        }
        case '2': {
            if(howContacts==0) {
                cout<<"Ksiazka adresowa jest pusta!"<<endl;
                break;
            }
            findPerson(start,&howContacts);
            break;
        }
        case '3': {
            if(howContacts==0) {
                cout<<"Ksiazka adresowa jest pusta!"<<endl;
                break;
            }
            showPersons(start,&howContacts);
            break;
        }
        case '4': {
            if(howContacts==0) {
                cout<<"Ksiazka adresowa jest pusta!"<<endl;
                break;
            }
            deletePerson(start,&howContacts);
            break;
        }
        case '5': {
            exit(0);
        }
        default : {
            cout<<"Nie ma takiej opcji w menu!"<<endl;
            Sleep(1000);
        }
        }

    }
    deleteAll(start);
    return 0;
}
void uptakeList(AdressBook *&start, int *howPerson) {

    fstream file;
    file.open("wizytowka.txt",ios::in);
    if(file.good()==false) {
        cout<<"Plik nie istnieje!";
        exit(0);
    }

    string line;
    int no_line=1;

    AdressBook *newAdres=start;
    AdressBook *pomoc;

    while(!file.eof()) {
        getline(file,line);
        if(*howPerson>=1) {
            if(no_line==1) {
                while(newAdres->nextElement) newAdres=newAdres->nextElement;
                pomoc=new AdressBook;
            }
        }
        if(no_line==1&&*howPerson==0) {
            newAdres=new AdressBook;
        }
        switch(no_line) {
        // tutaj chodzi o to ze jak mamy 0 kontaktow to nie mozna dodawac kontaktow z tyl. Pierwszy upload ustawia wskazniki
        // w odpowiedni sposob, dzieki temu drugi kontak moze byc dodany za tym pierwszym a nie przed.
        // przynajmniej mnie sie wydaje ze tak ma byc :)
        case 1:
            if(*howPerson==0) newAdres->id=atoi(line.c_str());
            else pomoc->id=atoi(line.c_str());
            break;
        case 2:
            if(*howPerson==0) newAdres->name=line;
            else pomoc->name=line;
            break;
        case 3:
            if(*howPerson==0) newAdres->surname=line;
            else pomoc->surname=line;
            break;
        case 4:
            if(*howPerson==0) newAdres->adress=line;
            else pomoc->adress=line;
            break;
        case 5:
            if(*howPerson==0) newAdres->email=line;
            else pomoc->email=line;
            break;
        case 6:
            if(*howPerson==0) newAdres->number=atoi(line.c_str());
            else pomoc->number=atoi(line.c_str());
            break;
        }


        if(no_line==6) {
            if(*howPerson==0) {
                newAdres->nextElement=start;
                start=newAdres;
            } else {
                pomoc->nextElement=NULL;
                newAdres->nextElement=pomoc;
            }
            no_line=0;
            *howPerson+=1;
        }
        no_line++;
    }
    file.close();
}
void addNewPerson(AdressBook *&start, int *amountOfContacts) {

    AdressBook *connectPerson=start;

    while(connectPerson->nextElement) connectPerson=connectPerson->nextElement;
    AdressBook *addPerson = new AdressBook;

    addPerson->id=*amountOfContacts;
    cout<<"ID:"<<addPerson->id<<endl;
    cout<<"Wprowadz imie: ";
    cin>>addPerson->name;
    cout<<"Wprowadz nazwisko: ";
    cin>>addPerson->surname;
    cout<<"Wprowadz adres: ";
    cin.ignore();
    getline(cin,addPerson->adress);
    cout<<"Wprowadz e-mail: ";
    cin>>addPerson->email;
    cout<<"Wprowadz numer telefonu: ";
    cin>>addPerson->number;

    addPerson->nextElement=NULL;
    connectPerson->nextElement=addPerson;

    fstream file;
    file.open("wizytowka.txt",ios::out|ios::app);

    file<<addPerson->id<<endl;
    file<<addPerson->name<<endl;
    file<<addPerson->surname<<endl;
    file<<addPerson->adress<<endl;
    file<<addPerson->email<<endl;
    file<<addPerson->number<<endl;

    file.close();
    file.clear();

    cout<<"Kontakt zostal dodany!"<<endl;
    Sleep(1000);

    *amountOfContacts+=1;
    file.clear();
}
void showPersons(AdressBook *&start, int *howPeople) {

    char sign;
    AdressBook *show=start;

    while(show) {
        cout<<show->id<<endl;
        cout<<show->name<<endl;
        cout<<show->surname<<endl;
        cout<<show->adress<<endl;
        cout<<show->email<<endl;
        cout<<show->number<<endl;
        show=show->nextElement;
    }
    cout<<endl;
    cout<<"Powrot do MENU, wcisnij p."<<endl;
    sign=getch();
    if(sign=='p') {
        return;
    } else exit(0);
}
void findPerson(AdressBook *&start, int *howUsers) {

    AdressBook *lookingFor=start;

    char helpvar, symbol, option;
    bool isFound;
    string nameUser, surnameUser;
    cout<<"Wybierz [1] jesli chcesz szukac po NAZWISKU.\nWybierz [2] jesli chcesz szukac po IMIENIU.\n";
    option=getch();
    do {
        isFound=false;
        switch(option) {
        case '1': {
            cout<<"Wprowadz nazwisko: ";
            cin>>surnameUser;

            while(lookingFor) {
                if(lookingFor->surname==surnameUser) {
                    cout<<"Znaleziono!\n";
                    cout<<lookingFor->id<<endl;
                    cout<<lookingFor->name<<endl;
                    cout<<lookingFor->surname<<endl;
                    cout<<lookingFor->adress<<endl;
                    cout<<lookingFor->email<<endl;
                    cout<<lookingFor->number<<endl;

                    isFound=true;
                }
                lookingFor=lookingFor->nextElement;
            }
            if(isFound==false) {
                cout<<"Nie ma podanego nazwiska w bazie!"<<endl;
                cout<<"Czy chcesz wprowadzic nazwisko ponownie[t/n]\n";
                helpvar=getch();
                if(helpvar=='t') continue;
                else return;
            }
            break;
        }
        case '2': {
            cout<<"Wprowadz imie: ";
            cin>>nameUser;

            while(lookingFor) {
                if(lookingFor->name==nameUser) {
                    cout<<"Znaleziono!\n";
                    cout<<lookingFor->id<<endl;
                    cout<<lookingFor->name<<endl;
                    cout<<lookingFor->surname<<endl;
                    cout<<lookingFor->adress<<endl;
                    cout<<lookingFor->email<<endl;
                    cout<<lookingFor->number<<endl;

                    isFound=true;
                }
                lookingFor=lookingFor->nextElement;
            }

            if(isFound==false) {
                cout<<"Nie ma podanego imienia w bazie!"<<endl;
                cout<<"Czy chcesz wprowadzic imie ponownie[t/n]\n";
                helpvar=getch();
                if(helpvar=='t') continue;
                else return;
            }
            break;
        }
        default : {
            cout<<"Blad, wprowadz ponownie!"<<endl;
            cout<<"Wybierz [1] jesli chcesz szukac po NAZWISKU.\nWybierz [2] jesli chcesz szukac po IMIENIU.\n";
            option=getch();
        }   // w default uzyto jeszcze raz instrukcji filtrujacej poniewaz w calej petli nie ma wyboru filtra, tylko jest tuz przed nia. Jesli wybrano zle instrukcja sie zapetlala.

        }

    } while(isFound!=true);

    cout<<endl;
    cout<<"Powrot do MENU, wcisnij p."<<endl;
    symbol=getch();
    if(symbol=='p') {
        return;
    } else exit(0);
}
void deletePerson(AdressBook *&start, int *howUsers) {

    string givenName, lastName;
    char mark;
    AdressBook *removeUser=start;
    AdressBook *previousUser=start;

    cout<<"Wprowadz imie oraz nazwisko (odziel spacja lub enterem): ";
    cin>>givenName>>lastName;

    while(removeUser) {
        if((removeUser->name==givenName)&&(removeUser->surname==lastName)) {
            if(removeUser==start) {
                cout<<"Czy napewno chcesz usunac uzytkownika? [t/n]:"<<endl;
                cout<<removeUser->id<<endl;
                cout<<removeUser->name<<endl;
                cout<<removeUser->surname<<endl;
                cout<<removeUser->adress<<endl;
                cout<<removeUser->email<<endl;
                cout<<removeUser->number<<endl;
                mark=getch();
                if(mark=='t') {
                    start=start->nextElement;
                    delete removeUser;
                    removeUser=start;
                    previousUser=start;
                    *howUsers-=1;

                    deleteOldTxt(start,howUsers);
                    sendToTxt(start,howUsers);
                    //usowanie z RAM;
                    deleteAll(start);
                    *howUsers=0;
                    uptakeList(start,howUsers);

                    return;
                } else {
                    return;
                }
            } else {
                cout<<"Czy napewno chcesz usunac uzytkownika? [t/n]:"<<endl;
                cout<<removeUser->id<<endl;
                cout<<removeUser->name<<endl;
                cout<<removeUser->surname<<endl;
                cout<<removeUser->adress<<endl;
                cout<<removeUser->email<<endl;
                cout<<removeUser->number<<endl;
                mark=getch();
                if(mark=='t') {
                    previousUser->nextElement=removeUser->nextElement;
                    delete removeUser;
                    removeUser=previousUser->nextElement;
                    *howUsers-=1;

                    deleteOldTxt(start,howUsers);
                    sendToTxt(start,howUsers);
                    //tutaj trzeba usunac dane ktore sa w RAM
                    deleteAll(start);
                    *howUsers=0;
                    uptakeList(start,howUsers);

                    return;
                } else {
                    return;
                }
            }
        } else if((removeUser->name!=givenName)&&(removeUser->surname!=lastName)) {
            previousUser=removeUser;
            removeUser=removeUser->nextElement;
        } else {
            cout<<"Nie znaleziono! Byc moze wprowadziles bledne dane. Sprawdz i wprowadz ponownie.";
            cin>>givenName>>lastName;
        }
    }
}
void deleteOldTxt(AdressBook *&start, int *howPerson) {

    if(remove("wizytowka.txt")==0) {
        cout<<"Usunieto kontakt!"<<endl; // Powinno byc ze usunieto caly plik ale wykorzystamy to w celu informacji ¿e usunieto kontak.
        Sleep(500);
    } else cout<<"Nie udalo sie skasowac!"<<endl;
}
void sendToTxt(AdressBook *&start, int *howPerson) {

    AdressBook *oldUserInNewTxt = start;

    fstream file;
    file.open("wizytowka.txt",ios::out|ios::app);
    *howPerson=0;
    while(oldUserInNewTxt) {
        oldUserInNewTxt->id=*howPerson;
        file<<oldUserInNewTxt->id<<endl;
        file<<oldUserInNewTxt->name<<endl;
        file<<oldUserInNewTxt->surname<<endl;
        file<<oldUserInNewTxt->adress<<endl;
        file<<oldUserInNewTxt->email<<endl;
        file<<oldUserInNewTxt->number<<endl;
        *howPerson+=1;
        oldUserInNewTxt=oldUserInNewTxt->nextElement;
    }
    file.close();
    file.clear();
}
void deleteAll(AdressBook *&start) {

    AdressBook *removePerson;
    while(start) {
        removePerson=start;
        start=start->nextElement;
        delete removePerson;
    }
}
