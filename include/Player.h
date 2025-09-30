#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include "Oggetto.h"
#include "Stanza.h"
#include "Nemico.h"

class Stanza;

using namespace std;

/* Player */

class Player {

    // Attributi

    private:

        string nome;
        int hp;
        int hp_max;
        int mana;
        int mana_max;
        int str;
        int agi;
        int mind;
        int faith;
        Stanza* pos;
        vector<Oggetto*> inventario;

        /* Ancora non utilizzati */

        // vector<string> skill;
        // vector<string> magie;
        // vector<string> resistenze;
        // vector<string> debolezze;
        // vector<string> status;
        // vector<string> immunita;

        /*------------------------*/

        // Slot equipaggiamento

        Oggetto* arma = nullptr;
        Oggetto* armatura = nullptr;
        Oggetto* scudo = nullptr;
        Oggetto* anello = nullptr;
        Oggetto* amuleto = nullptr;


    // Metodi

    public:

        // Costruttore

        Player (string n, int h, int ma, int s, int a, int mi, int f, Stanza* p)
            : nome(n), hp(h), mana(ma), str(s), agi(a), mind(mi), faith(f), pos(p) {}

        Player() : nome(""), hp(100), mana(50), str(10), agi(10), mind(10), faith(10), pos(nullptr) {}

        // Metodi getter

        string getNome () const { return nome;}
        int getHp () const;
        int getMana () const;
        int getStr () const;
        int getAgi () const;
        int getMind () const;
        int getFaith () const;
        Stanza* getPos () { return pos;}

        // Metodi setter

        void setNome (const string& n) { nome = n;}
        void setHp (int h) {hp = h;}
        void setHpMax (int hmax) {hp_max = hmax;}
        void setMana (int ma) {mana = ma;}
        void setManaMax (int mamax) {mana_max = mamax;}
        void setStr (int s) {str = s;}
        void setAgi (int a) {agi = a;}
        void setMind (int mi) {mind = mi;}
        void setFaith (int f) {faith = f;}
        void setPos (Stanza* p) {pos = p;}

        // Azioni

        int prova(int b, int ca);
        void scegliAzione(Stanza& stanza);
        void subisciDanno(int s);
        void curaDanno(int c);
        void curaMana(int c);
        void equipaggiaOggetto(Oggetto* o);
        void aggiungiOggettoInventario(Oggetto *o);
        void rimuoviOggettoInventario(Oggetto* o);
        void gestisciInventario();
        void interagisciStanza(Stanza& stanza);
        void muovi(Stanza& stanza);
        void attacca(Nemico& n);
        void aggiornaStatistiche();
        void generaPersonaggio();

    // Distruttore

    ~Player();

};
#endif 
