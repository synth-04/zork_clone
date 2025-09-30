#include <iostream>
#include "Nemico.h"
#include "Player.h"
#include <random>
using namespace std;

// Attacca player

void Nemico::attacca(Player& p) {

        if (getTipo() == "fisico") // fisico

        {int bonus_fisico = p.getAgi()/2;
            p.prova(bonus_fisico, potenza_) ? danno_ = 0 : danno_ = danno_;}

        else if (getTipo() == "magico") // magico

        {int bonus_magico = p.getMind()/2;
            p.prova(bonus_magico, potenza_) ? danno_ = 0 : danno_ = danno_;}

        else if (getTipo() == "sacrilego") // sacrilego
        
        {int bonus_sacrilego = p.getFaith()/2;
            p.prova(bonus_sacrilego, potenza_) ? danno_ = 0 : danno_ = danno_;}
        // esito attacco

    if (danno_ == 0) {
        cout << nome_ << " attacca " << p.getNome() << " ma manca il colpo!\n";
        return;
    }
    else {
        cout << nome_ << " attacca " << p.getNome() << " e infligge " << danno_ << " danni di tipo " << getTipo()<< ".\n";
        p.subisciDanno(danno_);

    }
    
}



