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
bool Player::prova(int b, int ca)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 20);
    // cout << "Risultato test:  " << dist(gen) + b << "vs " << ca << "\n"; // Debug
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
    stanza.mostraAzioni();
    const size_t n = stanza.numAzioni();
    if (n == 0) return;

    cout << "Scegli azione (1-" << n << ", 0 per annullare): ";
    int scelta;
    for (;;) {
        if (cin >> scelta) {
            if (scelta == 0) return;
            if (scelta >= 1 && scelta <= (int)n) break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input non valido. Riprova: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    stanza.eseguiAzioneByIndex((size_t)(scelta - 1), *this);
}


// Movimento

void Player::muovi(Stanza& stanza) {
    stanza.mostraUscite();
    int scelta; 
    cin >> scelta;
    const auto& uscite = stanza.getUscite();
    if (scelta >= 1 && scelta <= (int)uscite.size()) {
        setPos(uscite[scelta-1]);
        // getPos()->entra(*this);
    } else if  (scelta == 0) return;
    else {
        cout << "Uscita non valida.\n";
    }
}

// ======= Combattimento =======

void Player::attacca(Nemico & n){

        // Attacco base

        int danno_ = getStr()*2;
        prova(getAgi(), n.getPotenza()) ? danno_ = 0 : danno_ = danno_;
        
        if (danno_ == 0) {
        cout << "Attacchi " << n.getNome() << " ma manchi il colpo!\n";
        return;
    }
    else {
        cout << "Colpisci " << n.getNome() << " e infliggi " << danno_ << " danni.\n";
        n.subisciDanno(danno_);
    }
}

void Player::usaMagia(Nemico& n){

    if (magie_.empty())
    {
        cout << "Il tuo grimorio è vuoto.\n";
        return;
    }

    cout << "Grimorio:\n";
    for (size_t i = 0; i < magie_.size(); i++)
    {
        cout << i + 1 << ". " << magie_[i]->getNome() << "\n";
    }
    cout << "0. Annulla\n";

    int scelta;
    while (true)
    {
        cout << "Usa una magia (numero): ";
        if (!(cin >> scelta))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input non valido. Inserisci un numero.\n";
            continue;
        }
        if (scelta < 0 || scelta > (int)magie_.size())
        {
            cout << "Scelta non possibile. Riprova.\n";
            continue;
        }
        break;
    }
    if (scelta > 0 && scelta <= (int)magie_.size())
    {
        magie_[scelta - 1]->usa(*this, n);
    }
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
    if (c <= 0) return;
    int maxVis = getHpMaxVisibile();
    hp_ += c;             // curi la base
    if (hp_ > maxVis) hp_ = maxVis;
}

// Cura mana

void Player::curaMana(int cura) {
    if (cura <= 0) return;
    int maxVis = getManaMaxVisibile();
    mana_ += cura;             // curi la base
    if (mana_ > maxVis) mana_ = maxVis;
}

// Usa mana per magie

bool Player::spendiMana(int costo) {
    if (costo <= 0) return true;
    if (mana_ < costo) return false;
    mana_ -= costo;
    return true;
}

// ==Inventario e personaggio==

void Player::cambioEquip() {
    int maxVis = getManaMaxVisibile();
    if (mana_ > maxVis) mana_ = maxVis;
    maxVis = getHpMaxVisibile();
    if (hp_ > maxVis) hp_ = maxVis;
}

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

void Player::equipaggiaOggetto(Oggetto* o) {
    if (!o) { 
        std::cout << "Oggetto non valido.\n"; 
        return; 
    }

    const std::string& t = o->getTipo();
    Oggetto** slot = nullptr;

    if      (t == "arma")     slot = &arma_;
    else if (t == "armatura") slot = &armatura_;
    else if (t == "scudo")    slot = &scudo_;
    else if (t == "anello")   slot = &anello_;
    else if (t == "amuleto")  slot = &amuleto_;
    else {
        std::cout << "Non è equipaggiabile.\n";
        return;
    }
    if (*slot && *slot != o) {
        std::cout << "Riponi " << (*slot)->getNome() << " nello zaino.\n";
    }
    *slot = o;
    std::cout << "Hai equipaggiato: " << o->getNome() << "\n";
    cambioEquip();
}


// Aggiungi oggetto

void Player::aggiungiOggettoInventario(unique_ptr<Oggetto> o)
{
    inventario_.push_back(move(o));
    cout << inventario_.back()->getNome() << " aggiunto all'inventario.\n";
}

// Aggiungi magia al grimorio

void Player::aggiungiMagiaGrimorio(unique_ptr<Magia> m)
{
    magie_.push_back(move(m));
    cout << magie_.back()->getNome() << " aggiunto al grimorio.\n";
}

// Rimuovi oggetto
void Player::rimuoviOggettoInventario(Oggetto *o)
{
    auto& inv = inventario_;
    auto it = remove_if(inv.begin(), inv.end(),
                             [o](const unique_ptr<Oggetto>& ptr){ return ptr.get() == o; });
    if (it != inv.end()) {
        cout << o->getNome() << " rimosso dall'inventario.\n";
        inv.erase(it, inv.end());
    } else {
        cout << "Oggetto non trovato nell'inventario.\n";
    }
}

// Mostra inventario

void Player::gestisciInventario()
{

    aggiornaStatistiche();

    // Statistiche player

    cout << "\nStatistiche di " << getNome() << ":\n";
    cout << "Classe: \t\t" << getClasse() << "\n";
    cout << "HP: \t\t" << getHpVisibile() << "(" << getHpMaxVisibile() << ")"<< "\n";
    cout << "Mana: \t\t" << getManaVisibile() << "(" << getManaMaxVisibile() << ")" << "\n";
    cout << "Forza: \t\t" << getStr() << "\n";
    cout << "Agilità: \t" << getAgi() << "\n";
    cout << "Mente: \t\t" << getMind() << "\n";
    cout << "Fede: \t\t" << getFaith() << "\n\n";

    // Grimorio

    if (magie_.empty())
    {
        cout << "Il tuo grimorio è vuoto.\n";
    }
    else
    {
        for (size_t i = 0; i < magie_.size(); i++)
    {
        cout << i + 1 << ". " << magie_[i]->getNome() << "\n";
    }
    }

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
        const size_t idx = static_cast<size_t>(scelta - 1);
        // Chiama usa e, SE consumato, rimuovi l’elemento
        bool consumato = inventario_[idx]->usa(*this);
        if (consumato) {
        inventario_.erase(inventario_.begin() + static_cast<long long>(idx));
    }
}
}

// == Generazione personaggio ==

    void Player::generaPersonaggio()
    {


        string nome, classe;
        cout << "Inserisci il nome del tuo eroe: ";
        cout.flush();
        cin >> nome;

        setNome(nome);

        cout << "Scegli la tua classe: \n\n";

        cout << "1. Guerriero \n\n";
        cout << "Un combattente abile nel corpo a corpo. Possiede una grande resistenza e una discreta agilità, ma non possiede abilità magiche particolari.\n\n";

        cout << "2. Ladro \n\n";
        cout << "Scaltro e veloce, il ladro si muove veloce durante il combattimento. I ladri sono abili scassinatori e borseggiatori. \n\n";

        cout << "3. Mago \n\n";
        cout << "Il mago è un abile incantatore arcano. Sei addestrato nell'uso della magia, ma sei limitato nel combattimento corpo a corpo. \n\n";

        cout << "4. Sacerdote di Lumen \n\n";
        cout << "I sacerdoti di Lumen sono esperti guaritori ed esperti della magia della luce. Possono combattere, ma non lo fanno volentieri. \n\n";

        int scelta_classe;

        do 
        {
        cout << "Inserisci la tua scelta (numero): ";
        cin >> scelta_classe;

        switch (scelta_classe)
        {
            case 1:
                setClasse("Guerriero");
                str_ = 8;
                agi_ = 6;
                mind_ = 0;
                faith_ = 0;
                break;
            case 2:
                setClasse("Ladro");
                str_ = 4;
                agi_ = 8;
                mind_ = 2;
                faith_ = 0;
                break;
            case 3:
                setClasse("Mago");
                str_ = 0;
                agi_ = 4;
                mind_ = 8;
                faith_ = 2;
                break;
            case 4:
                setClasse("Sacerdote di Lumen");
                str_ = 4;
                agi_ = 4;
                mind_ = 0;
                faith_ = 6;
                break;
            default:
                cout << "Scelta non possibile, riprova. \n\n";

        }

        } while (scelta_classe==0 || scelta_classe > 4);

        /*

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 10);

        do {

        str_ = dist(gen);
        agi_ = dist(gen);
        mind_ = dist(gen);
        faith_ = dist(gen);

        } while (str_ + agi_ + mind_ + faith_ != 20);

        */

        hp_ = 50 + str_ * 2;
        setHpMax(hp_);
        mana_ = 30 + mind_ * 2 + faith_;
        setManaMax(mana_);
        

        cout << "Benvenuto, " << nome_ << "! Le tue statistiche iniziali sono:\n";
        cout << "HP: \t\t" << getHpBase() << "\n";
        cout << "Mana: \t\t" << getManaBase() << "\n";
        cout << "Forza: \t\t" << getStr() << "\n";
        cout << "Agilità: \t" << getAgi() << "\n";
        cout << "Mente: \t\t" << getMind() << "\n";
        cout << "Fede: \t\t" << getFaith() << "\n\n";
        
    }

    // Distruttore
    Player::~Player() = default;
