#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <string>
#include <random>

#include "Oggetto.h"
#include "Magia.h"

class Stanza;
class Oggetto;
class Nemico;
class Magia;

using namespace std;

/* Player */

class Player {

    // Attributi

    private:

        string nome_;
        int hp_;
        int hp_max_;
        int mana_;
        int mana_max_;
        int str_;
        int agi_;
        int mind_;
        int faith_;
        int def_;
        string classe_;

        Stanza* pos = nullptr; // posizione attuale

        vector<unique_ptr<Oggetto>> inventario_;
        vector<unique_ptr<Magia>> magie_;

        /* Ancora non utilizzati */

        // vector<string> skill;
        // vector<string> resistenze;
        // vector<string> debolezze;
        // vector<string> status;
        // vector<string> immunita;

        /*------------------------*/

        // Slot equipaggiamento

        Oggetto* arma_ = nullptr;
        Oggetto* armatura_ = nullptr;
        Oggetto* scudo_ = nullptr;
        Oggetto* anello_ = nullptr;
        Oggetto* amuleto_ = nullptr;


    // Metodi

    public:

        // Costruttore

        Player(const string& n, int h, int m, int s, int a, int mi, int f, int d, string cl, Stanza* st) :
            nome_(n), hp_(h), hp_max_(h), mana_(m), mana_max_(m),
            str_(s), agi_(a), mind_(mi), faith_(f), def_(d), classe_(cl), pos(st) {}

        Player() : nome_("Eroe"), hp_(100), hp_max_(100), mana_(50), mana_max_(50),
                   str_(10), agi_(10), mind_(10), faith_(10), classe_("Guerriero"), pos(nullptr) {}



        // Metodi getter

        string getNome () const { return nome_;}
        int getHp () const;
        int getHpMax() const { return hp_max_;}
        int getMana () const;
        int getManaMax() const { return mana_max_;}
        int getStr () const;
        int getAgi () const;
        int getMind () const;
        int getFaith () const;
        int getDef () const;
        string getClasse () const {return classe_;}
        Stanza* getPos () const { return pos;}
        bool spendiMana(int costo);

        // Metodi setter

        void setNome (const string& n) { nome_ = n; }
        void setHp (int h) { hp_ = h; if (hp_ > hp_max_) hp_ = hp_max_; }
        void setHpMax (int h) { hp_max_ = h; if (hp_ > hp_max_) hp_ = hp_max_; }
        void setMana (int m) { mana_ = m; if (mana_ > mana_max_) mana_ = mana_max_; }
        void setManaMax (int m) { mana_max_ = m; if (mana_ > mana_max_) mana_ = mana_max_; }
        void setStr (int s) { str_ = s; }
        void setAgi (int a) { agi_ = a; }
        void setMind (int m) { mind_ = m; }
        void setFaith (int f) { faith_ = f; }
        void setDef (int d) { def_ = d;}
        void setClasse (string cl) { classe_ = cl;}
        void setPos (Stanza* s) { pos = s; }

        // Azioni

        bool prova(int b, int ca);
        void scegliAzione(Stanza& stanza);
        void subisciDanno(int s);
        void curaDanno(int c);
        void curaMana(int c);
        void equipaggiaOggetto(Oggetto* o);
        void aggiungiOggettoInventario(unique_ptr<Oggetto> o);
        void rimuoviOggettoInventario(Oggetto* o);
        void aggiungiMagiaGrimorio(unique_ptr<Magia> m);
        void gestisciInventario();
        void interagisciStanza(Stanza& stanza);
        void muovi(Stanza& stanza);
        void attacca(Nemico& n);
        void usaMagia(Nemico& n);
        void generaPersonaggio();
        int hpBonusEquip() const {return sommaBonus(&Oggetto::getBonusHp);}
        int manaBonusEquip()  const { return sommaBonus(&Oggetto::getBonusMana); }


        template<typename F>
        int sommaBonus(F f) const;

        // Distruttore
        ~Player();
};

#endif 
