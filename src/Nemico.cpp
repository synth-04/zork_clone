#include <iostream>
#include "Nemico.h"
#include "Player.h"
#include <random>
using namespace std;

// Attacca player

void Nemico::attacca(Player& p, string tipo, int potenza, int danno) {

    if (tipo == "fisico") {

        int bonus_fisico = p.getAgi()/2;
        p.prova(bonus_fisico, potenza) ? danno = 0 : danno = danno;

    } else if (tipo == "magico") {

        int bonus_magico = p.getMind()/2;
        p.prova(bonus_magico, potenza) ? danno = 0 : danno = danno;

    } else if (tipo == "sacrilego") {

        int bonus_sacrilego = p.getFaith()/2;
        p.prova(bonus_sacrilego, potenza) ? danno = 0 : danno = danno;

    }
    cout << nome << " attacca " << p.getNome() << " e infligge " << danno << " danni di tipo " << tipo << "\n";
    p.subisciDanno(danno);
}

// Subisci danno

void Nemico::subisciDanno(int s) {
    hp -= s;
}

// Cura danno
void Nemico::curaDanno(int c) {
    hp += c;
}

