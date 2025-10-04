#include <string>
#include <iostream>
#include <functional>
#include "Nemico.h"
#include "Player.h"

using namespace std;

void Magia::usa(Player& p, Nemico& n) {
            if (!p.spendiMana(costo_mana_)) {
                cout << "Non hai abbastanza mana per usare " << nome_ << ".\n";
                return;
            }
            effetto_(p, n);            
        }

        Magia::~Magia() = default;