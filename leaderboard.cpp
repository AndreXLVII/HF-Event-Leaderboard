#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <cstdio>

#define PAUSE system("pause");
#define CLS system("cls");
#define MAX_GIOCATORI 200

using namespace std;

typedef struct struct_player {
    string steamId;
    string nome;
    string kills;
    string morti;
    string punti;
    string fazione;
} players;

players giocatori[MAX_GIOCATORI]; // Dichiaro vettore di giocatori
players fenix[MAX_GIOCATORI]; //giocatori Fenix
int sizeFen = 0;
int sizeTot = 0;

void stampaClassifica();
void stampaClassReg();
void stampaLista();
void cercaGioc();
void menu();

bool compara ( players a, players b){  //Funzione compara punti

	if( atoi(a.punti.c_str()) > atoi(b.punti.c_str()) ) 
		return 1;
	else 
		return 0;
}

int main (){
    
    system("color F0");

    int i=0, stessoGioc=0;
    
    fstream fin("input.txt", ios::in);
    //ofstream fout2("classificaInterna.txt");

    if (!fin.is_open()){ cout<<("ERRORE: Impossibile aprire il file input.txt"); PAUSE exit(1); }
    //if (!fout2.is_open()){ cout<<("ERRORE: Impossibile aprire il file classificaInterna.txt"); PAUSE exit(1); }
    
    players appo;

    while (fin){

        stessoGioc=0;

        getline(fin, appo.steamId, ',');   // Legge dal file input i dati
        getline(fin, appo.nome, ',');
        getline(fin, appo.kills, ',');
        getline(fin, appo.morti, ',');
        getline(fin, appo.punti, ',');
        getline(fin, appo.fazione);

        appo.nome.erase(0, 1);  //Elimino primo e ultimo carattere del nome (')
        appo.nome.erase(appo.nome.size() - 1);

        for (i=0; i<sizeTot; i++){   //Controllo stesso giocatore

            if ( appo.steamId.compare(giocatori[i].steamId) == 0){
                    
                giocatori[i].kills = to_string(stoi(giocatori[i].kills) + stoi(appo.kills));
                giocatori[i].morti = to_string(stoi(giocatori[i].morti) + stoi(appo.morti));
                giocatori[i].punti = to_string(stoi(giocatori[i].punti) + stoi(appo.punti));
                stessoGioc=1;
            }
                
        }

        if (!stessoGioc){  //Se non è lo stesso aggiunge al vettore un nuovo giocatore
            giocatori[sizeTot].steamId = appo.steamId;
            giocatori[sizeTot].nome = appo.nome;
            giocatori[sizeTot].kills = appo.kills;
            giocatori[sizeTot].morti = appo.morti;
            giocatori[sizeTot].punti = appo.punti;
            giocatori[sizeTot].fazione = appo.fazione;

            sizeTot++;
        }

        
    }
    
    fin.close();

    sizeTot=sizeTot-1;

    sort(giocatori, giocatori+sizeTot, compara); // Ordinamento per punteggio

    for (i=0; i<sizeTot; i++){     //Fenix (classifica interna)

        if (giocatori[i].nome.find("VII Fenix")!= string::npos){
            
            fenix[sizeFen].steamId = giocatori[i].steamId;
            fenix[sizeFen].nome = giocatori[i].nome;
            fenix[sizeFen].nome.erase(0, 12);
            fenix[sizeFen].kills = giocatori[i].kills;
            fenix[sizeFen].morti = giocatori[i].morti;
            fenix[sizeFen].punti = giocatori[i].punti;
            fenix[sizeFen].punti = giocatori[i].punti;    
            sizeFen++;
        }
    }

    menu();

    return 0;    
}

void stampaClassGen(){     //Stampa classifica generale

    time_t rawtime;     //Roba per il tempo
    time(&rawtime);
    struct tm* time;
    time=localtime(&rawtime);

    ofstream fout("classificaGenerale.txt");
    if (!fout.is_open()){ cout<<("ERRORE: Impossibile aprire il file classificaGenerale.txt"); PAUSE exit(1); }
    
    fout<<"╔═════════════════════☩══♛══☩═════════════════════╗\n\n";

    fout<<"ㅤ                         :trophy:  ** VII FENIX EVENT SCORE LEADERBOARD**   :trophy:     *"<<time->tm_mday<<"/"<<time->tm_mon+1<<"/"<<time->tm_year+1900<<"*\n\n\n";
    fout<<"                                    :first_place:  **"<<giocatori[0].nome<<"**  :dagger: "<<giocatori[0].kills<<"  :skull: "<<giocatori[0].morti<<"  :star2: "<<giocatori[0].punti<<"\n\n";
    fout<<"                                    :second_place:  **"<<giocatori[1].nome<<"**  :dagger: "<<giocatori[1].kills<<"  :skull: "<<giocatori[1].morti<<"  :star2: "<<giocatori[1].punti<<"\n\n";
    fout<<"                                    :third_place:  **"<<giocatori[2].nome<<"**  :dagger: "<<giocatori[2].kills<<"  :skull: "<<giocatori[2].morti<<"  :star2: "<<giocatori[2].punti<<"\n\n";

    for (int i=3; i<5; i++){

        fout<<"                                     :Spilla_della_Costanza_2:  "<<giocatori[i].nome<<"  :dagger: "<<giocatori[i].kills<<"  :skull: "<<giocatori[i].morti<<"  :star: "<<giocatori[i].punti<<"\n\n";
    }

    for (int i=5; i<10; i++){

        fout<<"                                     :Spilla_della_Costanza_1:  "<<giocatori[i].nome<<"  :dagger: "<<giocatori[i].kills<<"  :skull: "<<giocatori[i].morti<<"  :star: "<<giocatori[i].punti<<"\n\n";
    }

    fout<<"\n╚═════════════════════☩══✦══☩═════════════════════╝";    
    
    fout.close();
}

void stampaClassReg(){     //Stampa classifica interna

    time_t rawtime;     //Roba per il tempo
    time(&rawtime);
    struct tm* time;
    time=localtime(&rawtime);

    ofstream fout("classificaInterna.txt");
    if (!fout.is_open()){ cout<<("ERRORE: Impossibile aprire il file classificaInterna.txt"); PAUSE exit(1); }

    fout<<":trophy:  ** CLASSIFICA INTERNA EVENTO VII FENIX **   :trophy:     *"<<time->tm_mday<<"/"<<time->tm_mon+1<<"/"<<time->tm_year+1900<<"*\n\n\n";
    fout<<":first_place:  **"<<fenix[0].nome<<"**  :dagger: "<<fenix[0].kills<<"  :skull: "<<fenix[0].morti<<"  :star2: "<<fenix[0].punti<<"\n\n";
    fout<<":second_place:  **"<<fenix[1].nome<<"**  :dagger: "<<fenix[1].kills<<"  :skull: "<<fenix[1].morti<<"  :star2: "<<fenix[1].punti<<"\n\n";
    fout<<":third_place:  **"<<fenix[2].nome<<"**  :dagger: "<<fenix[2].kills<<"  :skull: "<<fenix[2].morti<<"  :star2: "<<fenix[2].punti<<"\n\n";

    for (int i=3; i<10; i++){

        fout<<":Spilla_della_Costanza_2:  "<<fenix[i].nome<<"  :dagger: "<<fenix[i].kills<<"  :skull: "<<fenix[i].morti<<"  :star: "<<fenix[i].punti<<"\n\n";
    } 

    for (int i=10;i<sizeFen; i++){

        fout<<fenix[i].nome<<"  :dagger: "<<fenix[i].kills<<"  :skull: "<<fenix[i].morti<<"  :star: "<<fenix[i].punti<<"\n";
    }    
    
    fout.close();
}

void stampaLista(){

    for (int i=0; i<sizeTot; i++){

        cout<<" "<<i+1<<")  "<<giocatori[i].nome<<"  Punteggio: "<<giocatori[i].punti<<endl;

    }

}

void cercaGioc(){

    char ricerca[80];
    bool trovato = false;
    int numTrov = 0;

    cout<<"Inserire il nome (o parte) del giocatore da cercare: ";
    gets_s(ricerca);
    cout<<"\n";

    for (int i=0; i<sizeTot; i++){

        if (giocatori[i].nome.find(ricerca)!= string::npos){

            cout<<"### Giocatore trovato ###\n"<<endl;
            cout<<"Nome: "<<giocatori[i].nome<<endl;
            cout<<"Kills: "<<giocatori[i].kills<<endl;
            cout<<"Morti: "<<giocatori[i].morti<<endl;
            cout<<"Score: "<<giocatori[i].punti<<endl;

            cout<<endl;

            trovato=true;
            numTrov++;        
        }

    }

    cout<<"Risultati trovati: "<<numTrov<<endl;

    if (trovato==false) cout<<"\nNessun giocatore trovato!"<<endl;

    cout<<"\n";

}

void menu(){

    char scelta;

    cout<<" ELABORAZIONE FILE DI SCORE EVENTO FENIX \n\n";

    cout<<" g. Genera Leaderboard Generale\n";
    cout<<" r. Genera Leaderboard Reggimentale\n";
    cout<<" l. Lista generale (ordinata)\n";
    cout<<" c. Cerca un giocatore\n";
    cout<<" e. Esci dal Programma\n";
    
    cout<<" La tua scelta: ";

    scelta=getch();

    switch (scelta)
    {
        case 'g': CLS stampaClassGen(); cout<<"Leaderboard generale creata con successo\n"<<endl; PAUSE CLS menu(); break;
            
        case 'r': CLS  stampaClassReg(); cout<<"Leaderboard interna creata con successo"<<endl; PAUSE CLS menu(); break;

        case 'l': CLS stampaLista(); PAUSE CLS menu(); break;

        case 'c': CLS cercaGioc(); PAUSE CLS menu(); break;

        case 'e': break;
        
        default: CLS cout<<"Scelta non valida!"<<endl; PAUSE CLS menu();
            break;
    }



}