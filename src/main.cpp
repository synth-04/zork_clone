#include <iostream>
#include <map>
#include <string>
#include <random>
#include <functional>
#include "Player.h"
#include "Stanza.h"
#include "Oggetto.h"
#include "Magia.h"
#include "Nemico.h"
#include "Evento.h"
#include "Game.h"
#include "Dungeon.h"

using namespace std;
using namespace dungeon;

int main() {

    setlocale(LC_ALL, "it_IT.UTF-8");

    cout << "Benvenuto in Lumen et Umbra!\n";

    // ======= Carica Dungeon a scelta ======== //
    
    cout << "Dove vuoi avventurarti? \n\n";
    cout << "1. Dungeon del Leone\n0. Esci \n";
    int scelta;

    DungeonData d;

    while (true)
        {
            cin >> scelta;
            switch (scelta){
                case 0: exit(0); break;
                case 1: d = buildLionDungeon(); break;
                default: cout << "Scelta non disponibile. \n"; break;
            }
            if (scelta < 2) break;
                

        }

    // ======= Creazione player ======= //

        // Genera statistiche base

        Player p;
        p.generaPersonaggio();

        // ======= Inizio gioco ======= //


        // == Creazione gioco == //
        
        Game game( &p, d.start);
        game.loop();


        return 0;
}
