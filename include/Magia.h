#ifndef MAGIA_H
#define MAGIA_H

#include <string>
#include <iostream>
#include <functional>
#include "Nemico.h"
#include "Player.h"

using namespace std;

class Magia {
    private:
        string nome_;
        string descrizione_;
        int costo_mana_;
        function<void(Player&, Nemico&)> effetto_;
        string tipo_; // "divino, "arcano", "sacrilego"

    public:
        Magia(const string& n, const string& d, int cm, function<void(Player&, Nemico&)> ef, const string& t) :
            nome_(n), descrizione_(d), costo_mana_(cm), effetto_(ef), tipo_(t) {}

        string getNome() const { return nome_; }
        string getDescrizione() const { return descrizione_; }
        int getCostoMana() const { return costo_mana_; }
        string getTipo() const { return tipo_; }

        void usa(Player& p, Nemico& n);

        ~Magia();
};

#endif