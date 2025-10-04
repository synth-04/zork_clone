#ifndef STANZA_H
#define STANZA_H

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <functional>

#include "Oggetto.h"
#include "Nemico.h"
#include "Evento.h"
#include "Magia.h"

using namespace std;

class Player;

class Stanza {

public:
    struct Azione {
        std::string id;      // es. "pickup:Spada" o "osserva_porta"
        std::string label;   // testo nel menu
        std::function<void(Player&, Stanza&)> effetto;  // cosa fa
        std::function<bool(const Player&, const Stanza&)> abilitata; // condizione
        bool one_shot = false; // se true si rimuove dopo l'esecuzione
    };


private:
    string nome_;
    string descrizione_;
    string descr_breve_;

    vector<Stanza*> uscite_;
    vector<Azione> azioni_;
    vector<unique_ptr<Oggetto>> oggetti_stanza_;
    vector<unique_ptr<Magia>> magia_stanza_;
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

    void aggiungiAzione(std::string id, 
                        std::string label,
                        std::function<void(Player&, Stanza&)> effetto,
                        std::function<bool(const Player&, const Stanza&)> abilitata = nullptr,
                        bool one_shot = false);

    void aggiungiAzionePickup(const std::string& nome_oggetto,
                              const std::string& label = "");

    void aggiungiAzioneMagia(const string& nome_magia,
                            const string& label = "");

    bool haMagia(const std::string& nome) const;


    void aggiungiOggetto(unique_ptr<Oggetto> o);
    void aggiungiOggetto(Oggetto* o);
    void aggiungiMagia(unique_ptr<Magia> m);
    void aggiungiMagia(Magia* m);
    unique_ptr<Oggetto> prendiOggetto(const string& nome);
    unique_ptr<Magia> prendiMagia(const string& nome);
    bool haOggetto(const std::string& nome) const;
    void rimuoviOggetto(const string& nome);

    size_t numAzioni() const { return azioni_.size(); }
    bool eseguiAzioneByIndex(size_t index, Player& p);
    void rimuoviAzioneById(const std::string& id);

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
