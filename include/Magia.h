#ifndef MAGIA_H
#define MAGIA_H

#include <string>
#include <iostream>
#include "Player.h"
#include "Nemico.h"

using namespace std;

class Magia {
    private:
        string nome_;
        string descrizione_;
        int costo_mana_;
        int potenza_;
        string tipo_; // "divino, "arcano", "sacrilego"

    public:
        Magia(const string& n, const string& d, int cm, int p, const string& t) :
            nome_(n), descrizione_(d), costo_mana_(cm), potenza_(p), tipo_(t) {}

        string getNome() const { return nome_; }
        string getDescrizione() const { return descrizione_; }
        int getCostoMana() const { return costo_mana_; }
        int getPotenza() const { return potenza_; }
        string getTipo() const { return tipo_; }

        void usa(Player& p, Nemico& n) {
            if (p.getMana() < costo_mana_) {
                cout << "Non hai abbastanza mana per usare " << nome_ << ".\n";
                return;
            }
            p.setMana(p.getMana() - costo_mana_);
            cout << p.getNome() << " usa " << nome_ << " su " << n.getNome() << ", infliggendo " << potenza_ << " danni.\n";
            n.subisciDanno(potenza_);
        }
};

#endif