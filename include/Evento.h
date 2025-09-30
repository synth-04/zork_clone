#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "Player.h"
#include "Stanza.h"

using namespace std;

class Player;
class Stanza;

class Evento {

    // Attributi

    private:

        string nome;
        function <bool( Player&, Stanza&) > condizione ; // funzione che ritorna un bool
        function <void (Player&, Stanza&) > effetto; // funzione che ritorna void
        bool attivato = false; // per eventi che si attivano una sola volta

    // Metodi

    public:

        // Costruttore

        Evento (string n,
                function <bool( Player&, Stanza&) > c,
                function <void (Player&, Stanza&) > e,
                bool a = false)
            : nome(n), condizione(c), effetto(e), attivato(a) {};

        // Metodi getter
        string getNome () const { return nome;}
        function <bool( Player&, Stanza&) > getCondizione () const { return condizione;}
        function <void (Player&, Stanza&) > getEffetto () const { return effetto;}
        bool isAttivato () const { return attivato;}

        // Metodi setter
        void setNome (const string& n) { nome = n;}
        void setCondizione (function <bool( Player&, Stanza&) > c) { condizione = c;}
        void setEffetto (function <void (Player&, Stanza&) > e) { effetto = e;}
        void setAttivato (bool a) { attivato = a;}

};