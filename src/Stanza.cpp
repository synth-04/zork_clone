#include "Stanza.h"
#include "Player.h"

#include <functional>
#include <algorithm>

using namespace std;

// Mostra stanza

void Stanza::mostra() const {
    cout << "\n=== " << nome_ << " ===\n";
    cout << descrizione_ << "\n";
    if (!oggetti_stanza_.empty()) {
        cout << "Nella stanza vedi:\n";
        for (auto const& o : oggetti_stanza_) {
            cout << "- " << o->getNome() << ": " << o->getDescrizioneStanza() << "\n";
        }
        for (auto const& m : magia_stanza_) {
            cout << "- " << m->getNome() << ": " << m->getDescrizione() << "\n";
        }
    }
}

// Entra in stanza

void Stanza::entra(Player& p) {
    mostra();           // descrizione
    triggerEventi(p);   // eventi scriptati
    if (nemico_) scontro(p); // eventuale scontro
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
    cout << "0. Annulla \n";
}

// == AZIONI ==

// Aggiungi azione

void Stanza::aggiungiAzione(string id, 
                            string label,
                            function<void(Player&, Stanza&)> effetto,
                            function<bool(const Player&, const Stanza&)> abilitata,
                            bool one_shot) {
        azioni_.push_back(Azione{
        move(id), 
        move(label),
        move(effetto), 
        move(abilitata), 
        one_shot
    });
}

// Aggiungi azione pickup

void Stanza::aggiungiAzionePickup(const string& nome_oggetto,
                                  const string& label) {
    const string id  = "pickup:" + nome_oggetto;
    const string lab = !label.empty() ? label : ("Raccogli " + nome_oggetto);

    aggiungiAzione(
        id, lab,
        // effetto (si esegue SOLO dopo la scelta):
        [nome_oggetto](Player& p, Stanza& s) {
            auto obj = s.prendiOggetto(nome_oggetto);
            if (obj) {
                p.aggiungiOggettoInventario(move(obj));
                cout << "Hai raccolto " << nome_oggetto << ".\n";
            } else {
                cout << "Non trovi " << nome_oggetto << ".\n";
            }
        },
        // abilitata (nessun side-effect):
        [nome_oggetto](const Player&, const Stanza& s) {
            return s.haOggetto(nome_oggetto);
        },
        true
    );
}

// Aggiungi azione apprendi magia

void Stanza::aggiungiAzioneMagia(const string& nome_magia,
                                  const string& label) {
    const string id  = "learn:" + nome_magia;
    const string lab = !label.empty() ? label : ("Leggi il tomo di " + nome_magia);

    aggiungiAzione(
        id, lab,
        // effetto (si esegue SOLO dopo la scelta):
        [nome_magia](Player& p, Stanza& s) {
            auto obj = s.prendiMagia(nome_magia);
            if (obj) {
                p.aggiungiMagiaGrimorio(move(obj));
                cout << "Hai appreso " << nome_magia << ".\n";
            } else {
                cout << "Non trovi " << nome_magia << ".\n";
            }
        },
        // abilitata (nessun side-effect):
        [nome_magia](const Player&, const Stanza& s) {
            return s.haMagia(nome_magia);
        },
        true
    );
}

// Controlla se la stanza ha una magia

bool Stanza::haMagia(const string& nome) const {
    for (auto const& m : magia_stanza_) if (m->getNome() == nome) return true;
    return false;
}

// Mostra azioni

void Stanza::mostraAzioni() const {
    if (azioni_.empty()) { cout << "Non ci sono azioni disponibili.\n"; return; }
    cout << "Azioni:\n";
    for (size_t i = 0; i < azioni_.size(); ++i) {
        cout << (i+1) << ". " << azioni_[i].label << "\n";
    }
}

// Scegli azione

bool Stanza::eseguiAzioneByIndex(size_t index, Player& p) {
    if (index >= azioni_.size()) { cout << "Scelta non valida.\n"; return false; }
    auto &a = azioni_[index];

    if (a.abilitata && !a.abilitata(p, *this)) {
        cout << "Non puoi farlo ora.\n";
        return false;
    }

    a.effetto(p, *this);

    if (a.one_shot) {
        azioni_.erase(azioni_.begin() + static_cast<long long>(index));
    }
    return true;
}

void Stanza::rimuoviAzioneById(const string& id) {
    azioni_.erase(
        remove_if(azioni_.begin(), azioni_.end(),
                  [&](const Azione& a){ return a.id == id; }),
        azioni_.end()
    );
}

// Aggiungi oggetto

void Stanza::aggiungiOggetto(unique_ptr<Oggetto> o) {
    if (!o) return;
    const string nome = o->getNome();
    oggetti_stanza_.push_back(move(o));
    aggiungiAzionePickup(nome);
}

void Stanza::aggiungiOggetto(Oggetto* o) {
    if (!o) return;
    const string nome = o->getNome();
    oggetti_stanza_.emplace_back(o);
    aggiungiAzionePickup(nome);
}

// Aggiungi Magie

void Stanza::aggiungiMagia(unique_ptr<Magia> m) {
    if (!m) return;
    const string nome = m->getNome();
    magia_stanza_.push_back(move(m));
    aggiungiAzioneMagia(nome);
}

void Stanza::aggiungiMagia(Magia* m) {
    if (!m) return;
    const string nome = m->getNome();
    magia_stanza_.emplace_back(m);
    aggiungiAzioneMagia(nome);
}

// Controlla se la stanza ha un oggetto

bool Stanza::haOggetto(const string& nome) const {
    for (auto const& o : oggetti_stanza_) if (o->getNome() == nome) return true;
    return false;
}

// Prendi oggetto

unique_ptr<Oggetto> Stanza::prendiOggetto(const string& nome) {
    for (auto it = oggetti_stanza_.begin(); it != oggetti_stanza_.end(); ++it) {
        if ((*it)->getNome() == nome) {
            auto out = move(*it);
            oggetti_stanza_.erase(it);
            return out;
        }
    }
    return nullptr;
}

// Prendi magia

unique_ptr<Magia> Stanza::prendiMagia(const string& nome) {
    for (auto it = magia_stanza_.begin(); it != magia_stanza_.end(); ++it) {
        if ((*it)->getNome() == nome) {
            auto out = move(*it);
            magia_stanza_.erase(it);
            return out;
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
    }
    rimuoviAzioneById("pickup:" + nome);
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
        cout << "m. Usa magia \n";
        cout << "i. Inventario \n";

        char scelta;
        cin >> scelta;
        switch(scelta) {
            case 'a': p.attacca(*nemico_); break;
            case 'm': p.usaMagia(*nemico_); break;
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

Stanza::~Stanza() = default;


