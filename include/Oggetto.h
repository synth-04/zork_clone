#ifndef OGGETTO_H
#define OGGETTO_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include "Player.h"
#include "Stanza.h"

using namespace std;

class Player;
class Stanza;

/* Oggetto */

class Oggetto {

    // Attributi

    private:

        string nome;
        string tipo;
        string descrizione_stanza;

        // Bonus oggetto

        int bonus_hp;
        int bonus_mana;
        int bonus_str;
        int bonus_agi;
        int bonus_mind;
        int bonus_faith;

    // Metodi

    public:

        // Costruttore

        Oggetto ( string n, string t, string ds, int bh=0, int bm=0, int bs=0, int ba=0, int bmi=0, int bf=0)
            : nome(n), tipo(t), descrizione_stanza(ds), bonus_hp(bh), bonus_mana(bm), bonus_str(bs), bonus_agi(ba), bonus_mind(bmi), bonus_faith(bf) {};

        // Metodi getter

        string getNome () const { return nome;}
        string getTipo () const { return tipo;}
        string getDescrizioneStanza () const { return descrizione_stanza;}
        int getBonusHp () const { return bonus_hp;}
        int getBonusMana () const { return bonus_mana;}
        int getBonusStr () const { return bonus_str;}
        int getBonusAgi () const { return bonus_agi;}
        int getBonusMind () const { return bonus_mind;}
        int getBonusFaith () const { return bonus_faith;}


        // Metodi setter

        void setNome (const string& n) { nome = n;}
        void setTipo (const string& t) { tipo = t;}
        void setDescrizioneStanza (const string& ds) { descrizione_stanza = ds;}

        // Azioni

        void usa(Player& p); 

};

#endif 

