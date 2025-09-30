#ifndef NEMICO_H
#define NEMICO_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Oggetto.h"
#include "Stanza.h"
#include "Player.h"
using namespace std;

class Player;
class Stanza;
class Oggetto;

/* Nemico */

class Nemico {

    // Attributi

    private:

        string nome;
        string descrizione;
        int hp;
        string tipo; // fisico, magico, sacrilego
        int potenza;
        int danno;

        string flag; // per comportamenti speciali

    // Metodi

    public:

        // Costruttore

        Nemico ( string n, string d, int h, string t, int p, int da, string f = "")
            : nome(n), descrizione(d), hp(h), tipo(t), potenza(p), danno(da), flag(f) {};

        // Metodi getter

        string getNome () const { return nome;}
        string getDescrizione () const { return descrizione;}
        int getHp () const { return hp;}
        string getTipo () const { return tipo;}
        int getPotenza () const { return potenza;}
        int getDanno () const { return danno;}
        string getFlag () const { return flag;}


        // Metodi setter

        void setNome (const string& n) { nome = n;}
        void setDescrizione (const string& d) { descrizione = d;}
        void setHp (int h) {hp = h;}
        void setTipo (const string& t) { tipo = t;}
        void setPotenza (int p) { potenza = p;}
        void setDanno (int d) { danno = d;}
        void setFlag (const string& f) { flag = f;}

        // Azioni

        void subisciDanno(int s);
        void curaDanno(int c);
        void attacca(Player& p, string tipo, int potenza, int danno);

    // Distruttore

    ~Nemico() {
    };

};

#endif