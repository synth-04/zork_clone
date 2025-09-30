#ifndef EVENTO_H
#define EVENTO_H

#include <string>
#include <functional>

using namespace std;

class Player;
class Stanza;

class Evento {

    // Attributi evento

    string nome_;
    function<bool(Player&, Stanza&)> condizione_;
    function<void(Player&, Stanza&)> azione_;
    bool attivato_ = false;

public:

    // Costruttore

    Evento(string nome,
           function<bool(Player&, Stanza&)> cond,
           function<void(Player&, Stanza&)> az)
        : nome_(move(nome)), condizione_(move(cond)), azione_(move(az)) {}

    const string& getNome() const { return nome_; }

    // Controlla e attiva l'evento se la condizione è soddisfatta

    bool trigger(Player& p, Stanza& s) {
        if (!attivato_ && condizione_(p, s)) {
            azione_(p, s);
            attivato_ = true;
            return true;
        }
        return false;
    }

    bool attivato() const { return attivato_; }
};

#endif
