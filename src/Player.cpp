#include "Player.h"
#include "Stanza.h"
#include "Oggetto.h"
#include <algorithm>
#include <limits>

#include "Player.h"
#include "Stanza.h"
#include "Oggetto.h"
#include "Nemico.h"

using namespace std;

// ===== Statistiche calcolate =====
template<typename F>
int Player::sommaBonus(F f) const {
    int tot = 0;
    if (arma_)    tot += (arma_->*f)();
    if (armatura_)tot += (armatura_->*f)();
    if (scudo_)   tot += (scudo_->*f)();
    if (anello_)  tot += (anello_->*f)();
    if (amuleto_) tot += (amuleto_->*f)();
    return tot;
}


int Player::getHp() const       { return hp_   + sommaBonus(&Oggetto::getBonusHp); }
int Player::getMana() const     { return mana_ + sommaBonus(&Oggetto::getBonusMana); }
int Player::getStr() const       { return str_ + sommaBonus(&Oggetto::getBonusStr); }
int Player::getAgi() const       { return agi_  + sommaBonus(&Oggetto::getBonusAgi); }
int Player::getMind() const      { return mind_ + sommaBonus(&Oggetto::getBonusMind); }
int Player::getFaith() const     { return faith_ + sommaBonus(&Oggetto::getBonusFaith); }


// Prove
int Player::prova(int b, int ca)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 20);
    return dist(gen) + b >= ca;
}

// Scegli azione

void Player::scegliAzione(Stanza& stanza) {
    cout << "\nCosa vuoi fare?\n";
    cout << "m. Muoviti\n";
    cout << "i. Inventario\n";
    cout << "t. Interagisci\n";
    cout << "e. Esci\n";
    char scelta; cin >> scelta;

    switch (scelta) {
        case 'm': muovi(stanza); break;
        case 'i': gestisciInventario(); break;
        case 't': interagisciStanza(stanza); break;
        case 'e': cout << "L'eroe, mesto, fugge...\n"; system("pause"); exit(0);
        default: cout << "Scelta non valida.\n"; break;
    }
}

// Interagisci con la stanza

void Player::interagisciStanza(Stanza& stanza) {
    // Mostra il menu azioni della stanza
    stanza.mostraAzioni();
    if (true) {
        cout << "Seleziona azione (numero, 0 per annullare): ";
        int scelta;
        if (!(cin >> scelta)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input non valido.\n";
            return;
        }
        if (scelta == 0) return;

        // Ottieni {id logico, messaggio} dell’azione scelta
        auto [id, msg] = stanza.scegliAzione(scelta);
        if (id.empty()) return; // scelta fuori range già gestita da Stanza

        // Caso: azione di raccolta oggetto
        if (id.rfind("Raccogli ", 0) == 0) {
            const string nome = id.substr(9); // dopo "Raccogli "
            // Sposta l’oggetto dalla stanza all’inventario
            auto obj = stanza.prendiOggetto(nome);   // unique_ptr<Oggetto>
            if (obj) {
                aggiungiOggettoInventario(std::move(obj));
                if (!msg.empty()) cout << msg << "\n";
                else cout << "Hai raccolto " << nome << ".\n";
            } else {
                cout << "Oggetto non trovato.\n";
            }
            return;
        }

        // Altre azioni "non di raccolta": stampa messaggio o ID
        if (!msg.empty()) cout << msg << "\n";
        else cout << id << "\n";
    }
}

    // Movimento

    void Player::muovi(Stanza& stanza) {
    stanza.mostraUscite();
    int scelta; cin >> scelta;
    const auto& uscite = stanza.getUscite();
    if (scelta >= 1 && scelta <= (int)uscite.size()) {
        setPos(uscite[scelta-1]);
        // getPos()->entra(*this);
    } else {
        cout << "Uscita non valida.\n";
    }
}

// ======= Combattimento =======

    void Player::attacca(Nemico & n)
    {

        // Attacco base (da modificare)

        int danno = getStr();
        cout << "Attacchi " << n.getNome() << " e infliggi " << danno << " danni.\n";
        n.subisciDanno(danno);
    }

    // Subisci danno
void Player::subisciDanno(int s)
{
    hp_ -= s;
}

// Cura danno
void Player::curaDanno(int c)
{
    // Cura fino al massimo degli hp base
    if (hp_ + c > hp_max_)
    {
        hp_ = hp_max_;
    }
    else
    {
        hp_ += c;
    }
}

// Cura mana
void Player::curaMana(int c)
{
    if (mana_ + c > mana_max_)
    {
        mana_ = mana_max_;
    }
    else
    {
        mana_ += c;
    }
}

// ==Inventario e personaggio==

// Aggiorna statistiche
    
void Player::aggiornaStatistiche()
    {

        getHp();
        getMana();
        getStr();
        getAgi();
        getMind();
        getFaith();

    }

// Equipaggia oggetto
void Player::equipaggiaOggetto(Oggetto* o) {
    if (!o) { cout << "Oggetto non valido.\n"; return; }
    const string& t = o->getTipo();
    if (t == "arma") arma_ = o;
    else if (t == "armatura") armatura_ = o;
    else if (t == "scudo") scudo_ = o;
    else if (t == "anello") anello_ = o;
    else if (t == "amuleto") amuleto_ = o;
    else { cout << "Non è equipaggiabile.\n"; return; }
    
    // cout << "Equipaggiato: " << o->getNome() << "\n";
}

// Aggiungi oggetto

void Player::aggiungiOggettoInventario(unique_ptr<Oggetto> o)
{
    inventario_.push_back(move(o));
    cout << inventario_.back()->getNome() << " aggiunto all'inventario.\n";
}

// Rimuovi oggetto
void Player::rimuoviOggettoInventario(Oggetto *o)
{
    auto& inv = inventario_;
    auto it = std::remove_if(inv.begin(), inv.end(),
                             [o](const std::unique_ptr<Oggetto>& ptr){ return ptr.get() == o; });
    if (it != inv.end()) {
        std::cout << o->getNome() << " rimosso dall'inventario.\n";
        inv.erase(it, inv.end());
    } else {
        std::cout << "Oggetto non trovato nell'inventario.\n";
    }
}

// Mostra inventario

void Player::gestisciInventario()
{

    aggiornaStatistiche();

    // Statistiche player

    cout << "\nStatistiche di " << getNome() << ":\n";
    cout << "HP: \t\t" << getHp() << "\n";
    cout << "Mana: \t\t" << getMana() << "\n";
    cout << "Forza: \t\t" << getStr() << "\n";
    cout << "Agilità: \t" << getAgi() << "\n";
    cout << "Mente: \t\t" << getMind() << "\n";
    cout << "Fede: \t\t" << getFaith() << "\n\n";

    // Equipaggiamento

    cout << "Equipaggiamento:\n";
    cout << "Arma: \t\t" << (arma_ ? arma_->getNome() : "Nessuna") << "\n";
    cout << "Armatura: \t" << (armatura_ ? armatura_->getNome() : "Nessuna") << "\n";
    cout << "Scudo: \t\t" << (scudo_ ? scudo_->getNome() : "Nessuno") << "\n";
    cout << "Anello: \t" << (anello_ ? anello_->getNome() : "Nessuno") << "\n";
    cout << "Amuleto: \t" << (amuleto_ ? amuleto_->getNome() : "Nessuno") << "\n\n";

    if (inventario_.empty())
    {
        cout << "Il tuo inventario è vuoto.\n";
        return;
    }

    cout << "Oggetti nello zaino:\n";
    for (size_t i = 0; i < inventario_.size(); i++)
    {
        cout << i + 1 << ". " << inventario_[i]->getNome() << "\n";
    }
    cout << "0. Annulla\n";

    int scelta;
    while (true)
    {
        cout << "Usa o equipaggia un oggetto (numero): ";
        if (!(cin >> scelta))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input non valido. Inserisci un numero.\n";
            continue;
        }
        if (scelta < 0 || scelta > (int)inventario_.size())
        {
            cout << "Scelta non possibile. Riprova.\n";
            continue;
        }
        break;
    }
    if (scelta > 0 && scelta <= (int)inventario_.size())
    {
        inventario_[scelta - 1]->usa(*this);
    }
}

// == Generazione personaggio ==

    void Player::generaPersonaggio()
    {


        string nome;
        cout << "Inserisci il nome del tuo eroe: ";
        cout.flush();
        cin >> nome;

        setNome(nome);

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dist(5, 20);

        do {

        str_ = dist(gen);
        agi_ = dist(gen);
        mind_ = dist(gen);
        faith_ = dist(gen);

        } while (str_ + agi_ + mind_ + faith_ != 40);

        hp_ = 50 + str_ * 2;
        setHpMax(hp_);
        mana_ = 30 + mind_ * 2 + faith_;
        setManaMax(mana_);
        

        cout << "Benvenuto, " << nome_ << "! Le tue statistiche iniziali sono:\n";
        cout << "HP: \t\t" << getHp() << "\n";
        cout << "Mana: \t\t" << getMana() << "\n";
        cout << "Forza: \t\t" << getStr() << "\n";
        cout << "Agilità: \t" << getAgi() << "\n";
        cout << "Mente: \t\t" << getMind() << "\n";
        cout << "Fede: \t\t" << getFaith() << "\n\n";
        
    }

    // Distruttore
    Player::~Player() = default;
