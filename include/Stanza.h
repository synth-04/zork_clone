#ifndef STANZA_H
#define STANZA_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "Player.h"
#include "Oggetto.h"
#include "Nemico.h"
#include "Evento.h"

using namespace std;

class Oggetto;
class Player;
class Nemico;

class Stanza {
private:
    string nome;
    string descrizione;
    string descr_breve;
    
    Nemico* nemico = nullptr;

public:

    vector<Stanza*> uscite;
    vector<pair<string,string>> azioni;
    vector<Oggetto*> oggetti_stanza;
    vector <Evento> eventi;

    // Costruttori

    Stanza() : nome(""), descrizione(""), descr_breve("") {}
    Stanza(const string& n, const string& d, const string& db)
        : nome(n), descrizione(d), descr_breve(db) {}

    // Getter

    string getNome() const { return nome; }
    string getDescrizione() const { return descrizione; }
    string getDescrizioneBreve() const { return descr_breve; }
    Stanza* getStanzaAdiacente(const string& nome) const;

    // Setter

    void setNome(const string& n) { nome = n; }
    void setDescrizione(const string& d) { descrizione = d; }
    void setDescrizioneBreve(const string& db) { descr_breve = db; }

    // Metodi

    void scontro(Player& p);
    void aggiungiScontro(Nemico* n);
    void mostra(Player& p);
    void mostraUscite() const;

    void aggiungiUscita(Stanza* stanza);
    void aggiungiOggetto(Oggetto* o);     
    Oggetto* prendiOggetto(const string& nome);
    void rimuoviOggetto(const string& nome);

    void aggiungiAzione(const string& id, const string& msg);
    void mostraAzioni() const;
    pair<string,string> scegliAzione(int scelta) const;

    string scegliUscita(int scelta) const;
    void aggiungiEvento(const Evento& e);
};

#endif
