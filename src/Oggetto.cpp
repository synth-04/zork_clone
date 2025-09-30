#include "Player.h"
#include "Stanza.h" 

#include "Oggetto.h"
#include <algorithm>

using namespace std;

void Oggetto::usa(Player& p) {

            // Pozione
            if (tipo == "pozione") {
                cout << "Usi " << nome << ". " << "\n";
                p.curaDanno(bonus_hp);
                p.curaMana(bonus_mana);
                p.rimuoviOggettoInventario(this);               
            
            } 
            // Equipaggiamento

            else if (tipo == "arma" || tipo == "armatura" || tipo == "scudo" || tipo == "anello" || tipo == "amuleto") {
                cout << "Equipaggi " << nome << ". " << "\n";
                p.equipaggiaOggetto(this);

            } else {
            cout << "Non puoi usarlo ora. " << "\n";
        }

};