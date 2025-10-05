#include "Player.h"
#include "Stanza.h" 

#include "Oggetto.h"
#include <algorithm>

using namespace std;

bool Oggetto::usa(Player& p) {

            // Pozione
            if (getTipo() == "pozione") {
                cout << "Usi " << getNome() << ". " << "\n";
                p.curaDanno(getBonusHp());
                p.curaMana(getBonusMana());
                return true;
                // p.rimuoviOggettoInventario(this);               
            
            } 
            // Equipaggiamento

            else if (getTipo() == "arma" || getTipo() == "armatura" || getTipo() == "scudo" || getTipo() == "anello" || getTipo() == "amuleto") {
                cout << "Equipaggi " << getNome() << ". " << "\n";
                p.equipaggiaOggetto(this);
                return false;

            } else {
            cout << "Non puoi usarlo ora. " << "\n";
            return false;
        }

};