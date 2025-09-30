#include "Stanza.h"
#include "Player.h"


#include <algorithm>

using namespace std;

// Mostra stanza

void Stanza::mostra() const {
    cout << "\n== " << nome_ << " ==\n";
    cout << descrizione_ << "\n";

    if (!oggetti_stanza_.empty()) {
        cout << "Nella stanza vedi:\n";
        for (auto const& o : oggetti_stanza_) {
            cout << "- " << o->getNome() << ": " << o->getDescrizioneStanza() << "\n";
        }
    }
}

// Mostra uscite

void Stanza::mostraUscite() const {
    if (uscite_.empty()) {
        cout << "Non vedi altre vie d'uscita.\n";
        return;
    }

    for (size_t i = 0; i < uscite_.size(); i++) {
        cout << i+1 << ". Vai verso " << uscite_[i]->getDescrizioneBreve() << "\n";
    }
}

// Mostra azioni

void Stanza::mostraAzioni() const {
    if (azioni_.empty()) {
        cout << "Non ci sono azioni disponibili in questa stanza.\n";
        return;
    }
    cout << "Azioni disponibili:\n";
    for (size_t i = 0; i < azioni_.size(); ++i) {
        cout << (i+1) << ". " << azioni_[i].first << "\n";
    }
}

// Scegli azione

pair<string,string> Stanza::scegliAzione(int scelta) const {
    if (scelta < 1 || scelta > (int)azioni_.size()) {
        cout << "Azione non disponibile.\n";
        return {"",""};
    }
    return azioni_[scelta-1]; // {id, msg}
}

// Aggiungi oggetto

void Stanza::aggiungiOggetto(unique_ptr<Oggetto> o) {
    oggetti_stanza_.push_back(move(o));
    string id = "Raccogli " + o->getNome();
    string msg = "Hai raccolto " + o->getNome() + ".";
    aggiungiAzione(id, msg);

}

// Prendi oggetto

unique_ptr<Oggetto> Stanza::prendiOggetto(const string& nome) {
    for (auto it = oggetti_stanza_.begin(); it != oggetti_stanza_.end(); ++it) {
        if ((*it)->getNome() == nome) {
            unique_ptr<Oggetto> trovato = move(*it);
            oggetti_stanza_.erase(it);
            return trovato;
        }
    }
    return nullptr;
}

// Rimuovi oggetto

void Stanza::rimuoviOggetto(const string& nome) {
    auto it = remove_if(oggetti_stanza_.begin(), oggetti_stanza_.end(),
                        [&nome](const unique_ptr<Oggetto>& o) { return o->getNome() == nome; });
    if (it != oggetti_stanza_.end()) {
        oggetti_stanza_.erase(it, oggetti_stanza_.end());
        // Rimuovi azione associata
        azioni_.erase(remove_if(azioni_.begin(), azioni_.end(),
                                [&nome](const pair<string,string>& a) {
                                    return a.first == "Raccogli " + nome;
                                }), azioni_.end());
    }
}

// Trigger eventi

void Stanza::triggerEventi(Player& p) {
    for (auto& e : eventi_) {
        if (e.trigger(p, *this)) {
            break; // solo un evento per volta
        }
    }
}

// Scontro

void Stanza::scontro(Player& p) {
    if (!nemico_) return;

    cout << nemico_->getDescrizione() << "\n";

    while (p.getHp() > 0 && nemico_->getHp() > 0) {
        cout << p.getNome() << " HP: " << p.getHp()
             << " | " << nemico_->getNome() << " HP: " << nemico_->getHp() << "\n";

        // Turno player
        cout << "Scegli un'azione:\n";
        cout << "a. Attacca \n";
        cout << "i. Inventario \n";

        char scelta;
        cin >> scelta;
        switch(scelta) {
            case 'a': p.attacca(*nemico_); break;
            case 'i': p.gestisciInventario(); break;
            default: 
                cout << "Azione non valida.\n";
                continue;
        }

        // Turno nemico
        if (nemico_->getHp() > 0) {
            nemico_->attacca(p);
        }
    }

    if (p.getHp() <= 0) {
        cout << p.getNome() << " è stato sconfitto...\n";
        cout << "Game Over.\n";
        system("pause");
        exit(0);
    } else if (nemico_->getHp() <= 0) {
        cout << nemico_->getNome() << " è stato sconfitto!\n";
        nemico_ = nullptr; // rimuove il nemico dalla stanza
    }
}


// Quando il player entra

void Stanza::entra(Player& p) {
    mostra();           // descrizione
    triggerEventi(p);   // eventi scriptati
    if (nemico_) scontro(p); // eventuale scontro
}

Stanza::~Stanza() = default;


