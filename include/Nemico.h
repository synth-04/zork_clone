#ifndef NEMICO_H
#define NEMICO_H

#include <string>

using namespace std;

class Player;

class Nemico {
    string nome_;
    string descrizione_;
    int hp_;
    string tipo; // "fisico", "magico", "sacrilego"
    int potenza_;
    int danno_;

public:
    // Costruttore
    Nemico(string nome, string descr, int hp, string tipo, int potenza, int danno)
        : nome_(move(nome)), descrizione_(move(descr)), hp_(hp), tipo(move(tipo)), potenza_(potenza), danno_(danno) {}

    // Metodi getter
    const string& getNome() const { return nome_; }
    const string& getDescrizione() const { return descrizione_; }
    int getHp() const { return hp_; }
    const string& getTipo() const { return tipo; }
    int getPotenza() const { return potenza_; }
    int getDanno() const { return danno_; }
    

    void subisciDanno(int d) { hp_ -= d; if (hp_ < 0) hp_ = 0; }

    void attacca(Player& p);
};

#endif