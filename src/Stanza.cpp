#include "Stanza.h"
#include "Oggetto.h"
#include "Player.h"
#include "Nemico.h"

#include <algorithm>

using namespace std;

// Scontro nella stanza

void Stanza::scontro(Player& p) {
    if (!nemico) return;

    cout << nemico->getDescrizione() << "\n";

    while (p.getHp() > 0 && nemico->getHp() > 0) {
        cout << p.getNome() << " HP: " << p.getHp()
             << " | " << nemico->getNome() << " HP: " << nemico->getHp() << "\n";

        // Turno player
        cout << "Scegli un'azione:\n";
        cout << "a. Attacca \n";
        cout << "i. Inventario \n";

        char scelta;
        cin >> scelta;
        switch(scelta) {
            case 'a': p.attacca(*nemico); break;
            case 'i': p.gestisciInventario(); break;
            default: 
                cout << "Azione non valida.\n";
                continue;
        }

        // Turno nemico
        if (nemico->getHp() > 0) {
            nemico->attacca(p, nemico->getTipo(), nemico->getPotenza(), nemico->getDanno());
        }
    }

    if (p.getHp() <= 0) {
        cout << p.getNome() << " è stato sconfitto...\n";
        cout << "Game Over.\n";
        system("pause");
        exit(0);
    } else if (nemico->getHp() <= 0) {
        cout << nemico->getNome() << " è stato sconfitto!\n";
        nemico = nullptr; // 👈 rimosso dalla stanza
    }
}

// Aggiungi scontro

void Stanza::aggiungiScontro(Nemico* n) {
    nemico = n;
}


// Mostra stanza

void Stanza::mostra(Player& p) {
    if (nemico) {
        scontro(p);
    }

    if (eventi.size() > 0) {
        for (auto& e : eventi) {
            if (!e.isAttivato() && e.getCondizione()(p, *this)) {
                e.getEffetto()(p, *this);
                e.setAttivato(true);
            }
        }
    }

    cout << nome << "\n\n";
    cout << descrizione << "\n\n";
    if (!oggetti_stanza.empty()) {
        cout << "Nella stanza vedi:\n";
        for (const auto& o : oggetti_stanza) {
            cout << "- " << o->getNome() << ": " << o->getDescrizioneStanza() << "\n";
        }
    } else {
        cout << "La stanza è vuota.\n";
    }
}

// Mostra uscite

void Stanza::mostraUscite() const {
    if (uscite.empty()) {
        cout << "Non ci sono uscite disponibili in questa stanza.\n";
        return;
    }

    for (size_t i = 0; i < uscite.size(); i++) {
        cout << i+1 << ". Vai verso " << uscite[i]->getDescrizioneBreve() << "\n";
    }
}

// Aggiungi uscita

void Stanza::aggiungiUscita(Stanza* stanza) {
    uscite.push_back(stanza);
}

// Aggiungi oggetto

void Stanza::aggiungiOggetto(Oggetto* o) {
    oggetti_stanza.push_back(o);
    string id = "Raccogli " + o->getNome();
    string desc = "Hai raccolto " + o->getNome();
    aggiungiAzione(id, desc);
}

// Prendi oggetto

Oggetto* Stanza::prendiOggetto(const string& nome) {
    for (auto it = oggetti_stanza.begin(); it != oggetti_stanza.end(); ++it) {
        if ((*it)->getNome() == nome) {
            Oggetto* trovato = *it;
            oggetti_stanza.erase(it);
            return trovato;
        }
    }
    return nullptr;
}

// Rimuovi oggetto

void Stanza::rimuoviOggetto(const string& nome) {
    auto it = remove_if(oggetti_stanza.begin(), oggetti_stanza.end(),
                             [&nome](Oggetto* o) { return o->getNome() == nome; });
    if (it != oggetti_stanza.end()) {
        oggetti_stanza.erase(it, oggetti_stanza.end());
    } else {
        cout << nome << " non trovato nella stanza.\n";
    }
}

// Scelta uscita

string Stanza::scegliUscita(int scelta) const {
    if (scelta >= 1 && scelta <= (int)uscite.size()) {
        return uscite[scelta-1]->getNome();
    }
    cout << "Uscita non disponibile.\n";
    return "";
}



// Ottieni stanza adiacente

Stanza* Stanza::getStanzaAdiacente(const string& nome) const {
    for (Stanza* s : uscite) {
        if (s->getNome() == nome) {
            return s;
        }
    }
    return nullptr;
}

// Aggiungi azione

void Stanza::aggiungiAzione(const string& id, const string& msg) {
    azioni.emplace_back(id, msg);
}

// Mostra azioni

void Stanza::mostraAzioni() const {
    if (azioni.empty()) {
        cout << "Non ci sono azioni disponibili in questa stanza.\n";
        return;
    }
    cout << "Azioni disponibili:\n";
    for (size_t i = 0; i < azioni.size(); ++i) {
        cout << (i+1) << ". " << azioni[i].first << "\n";
    }
}

// Scegli azione

pair<string,string> Stanza::scegliAzione(int scelta) const {
    if (scelta < 1 || scelta > (int)azioni.size()) {
        cout << "Azione non disponibile.\n";
        return {"",""};
    }
    return azioni[scelta-1]; // {id, msg}
}

// Aggiungi evento
void Stanza::aggiungiEvento(const Evento& e) {
    eventi.push_back(e);
}


