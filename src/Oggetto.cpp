#include "Player.h"
#include "Stanza.h" 

#include "Oggetto.h"
#include <algorithm>

using namespace std;

void Oggetto::usa(Player& p) {

            // Pozione
            if (getTipo() == "pozione") {
                cout << "Usi " << getNome() << ". " << "\n";
                p.curaDanno(getBonusHp());
                p.curaMana(getBonusMana());
                p.rimuoviOggettoInventario(this);               
            
            } 
            // Equipaggiamento

            else if (getTipo() == "arma" || getTipo() == "armatura" || getTipo() == "scudo" || getTipo() == "anello" || getTipo() == "amuleto") {
                cout << "Equipaggi " << getNome() << ". " << "\n";
                p.equipaggiaOggetto(this);

            } else {
            cout << "Non puoi usarlo ora. " << "\n";
        }

};