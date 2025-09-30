#ifndef STANZA_H
#define STANZA_H

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>

#include "Oggetto.h"
#include "Nemico.h"
#include "Evento.h"

using namespace std;

class Player;

class Stanza {
private:
    string nome_;
    string descrizione_;
    string descr_breve_;
    vector<Stanza*> uscite_;
    vector<pair<string,string>> azioni_; // {id, msg}
    vector<unique_ptr<Oggetto>> oggetti_stanza_;
    vector <Evento> eventi_;
    
    Nemico* nemico_ = nullptr;

public:

    

    // Costruttori

    Stanza(const string& nome, const string& descrizione, const string& descr_breve)
        : nome_(nome), descrizione_(descrizione), descr_breve_(descr_breve) {}

    // Getter

    string getNome() const { return nome_; }
    string getDescrizione() const { return descrizione_; }
    string getDescrizioneBreve() const { return descr_breve_; }
    const vector<Stanza*>& getUscite() const { return uscite_; }



    // Metodi

    void aggiungiUscita(Stanza* s) { uscite_.push_back(s); }

    void mostra() const;
    void mostraUscite() const;
    void mostraAzioni() const;

    void aggiungiAzione(const string& id, const string& msg) { azioni_.emplace_back(id, msg); };
    pair<string,string> scegliAzione(int scelta) const;

    void aggiungiOggetto(unique_ptr<Oggetto> o);
    void aggiungiOggetto(Oggetto* o) { aggiungiOggetto(std::unique_ptr<Oggetto>(o)); } // overload per raw pointer
    unique_ptr<Oggetto> prendiOggetto(const string& nome);
    void rimuoviOggetto(const string& nome);

    // Eventi

    void aggiungiEvento(const Evento& e) { eventi_.push_back(e); }
    void triggerEventi(Player& p);

    // Scontro

    void aggiungiScontro(Nemico* n) { nemico_ = n; }
    bool haNemico() const { return nemico_ != nullptr; }
    void scontro(Player& p);

    // Quando il player entra
    void entra(Player& p);

     ~Stanza();
};

#endif
