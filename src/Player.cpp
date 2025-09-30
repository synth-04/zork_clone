#include "Player.h"
#include "Stanza.h"
#include "Oggetto.h"
#include <algorithm>

using namespace std;

// Getter statistiche
int Player::getHp() const
{
    int total_hp = hp;
    if (armatura)
        total_hp += armatura->getBonusHp();
    if (anello)
        total_hp += anello->getBonusHp();
    if (amuleto)
        total_hp += amuleto->getBonusHp();
    return total_hp;
}

int Player::getMana() const
{
    int total_mana = mana;
    if (armatura)
        total_mana += armatura->getBonusMana();
    if (anello)
        total_mana += anello->getBonusMana();
    if (amuleto)
        total_mana += amuleto->getBonusMana();
    return total_mana;
}

int Player::getStr() const
{
    int total_str = str;
    if (arma)
        total_str += arma->getBonusStr();
    if (anello)
        total_str += anello->getBonusStr();
    if (amuleto)
        total_str += amuleto->getBonusStr();
    return total_str;
}

int Player::getAgi() const
{
    int total_agi = agi;
    if (armatura)
        total_agi += armatura->getBonusAgi();
    if (anello)
        total_agi += anello->getBonusAgi();
    if (amuleto)
        total_agi += amuleto->getBonusAgi();
    return total_agi;
}

int Player::getMind() const
{
    int total_mind = mind;
    if (armatura)
        total_mind += armatura->getBonusMind();
    if (anello)
        total_mind += anello->getBonusMind();
    if (amuleto)
        total_mind += amuleto->getBonusMind();
    return total_mind;
}

int Player::getFaith() const
{
    int total_faith = faith;
    if (armatura)
        total_faith += armatura->getBonusFaith();
    if (anello)
        total_faith += anello->getBonusFaith();
    if (amuleto)
        total_faith += amuleto->getBonusFaith();
    return total_faith;
}

// Prove
int Player::prova(int b, int ca)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 20);
    return dist(gen) + b >= ca;
}

// Scegli azione

void Player::scegliAzione(Stanza &stanza)
{
    cout << "\nCosa vuoi fare?\n";
    cout << "m. Muoviti\n";
    cout << "i. Statistiche e inventario\n";
    cout << "s. Interagisci\n";
    cout << "e. Abbandona\n";

    char scelta;
    cin >> scelta;

    switch (scelta)
    {
    case 'm':
        muovi(stanza);
        break;
    case 'i':
        gestisciInventario();
        break;
    case 's':
        interagisciStanza(stanza);
        break;
    case 'e':
        cout << "L'eroe, mesto, si ritira...\n";
        system("pause");
        exit(0);
    }
}

// Subisci danno
void Player::subisciDanno(int s)
{
    hp -= s;
}

// Cura danno
void Player::curaDanno(int c)
{
    // Cura fino al massimo degli hp base
    if (hp + c > hp_max)
    {
        hp = hp_max;
    }
    else
    {
        hp += c;
    }
}

// Cura mana
void Player::curaMana(int c)
{
    if (mana + c > mana_max)
    {
        mana = mana_max;
    }
    else
    {
        mana += c;
    }
}

// Equipaggia oggetto
void Player::equipaggiaOggetto(Oggetto *o)
{
    if (!o)
    {
        cout << "Oggetto non valido.\n";
        return;
    }

    string tipo = o->getTipo();
    if (tipo == "arma")
    {
        arma = o;
    }
    else if (tipo == "armatura")
    {
        armatura = o;
    }
    else if (tipo == "scudo")
    {
        scudo = o;
    }
    else if (tipo == "anello")
    {
        anello = o;
    }
    else if (tipo == "amuleto")
    {
        amuleto = o;
    }
    else
    {
        cout << "Non puoi equipaggiare questo oggetto.\n";
        return;
    }
    cout << "Hai equipaggiato: " << o->getNome() << "\n";
}

// Aggiungi oggetto
void Player::aggiungiOggettoInventario(Oggetto *o)
{
    inventario.push_back(o);
    cout << o->getNome() << " aggiunto all'inventario!\n";
}

// Rimuovi oggetto
void Player::rimuoviOggettoInventario(Oggetto *o)
{
    auto it = find(inventario.begin(), inventario.end(), o);
    if (it != inventario.end())
    {
        inventario.erase(it);
        cout << o->getNome() << " rimosso dall'inventario.\n";
    }
    else
    {
        cout << o->getNome() << " non trovato nell'inventario.\n";
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
    cout << "Arma: \t\t" << (arma ? arma->getNome() : "Nessuna") << "\n";
    cout << "Armatura: \t" << (armatura ? armatura->getNome() : "Nessuna") << "\n";
    cout << "Scudo: \t\t" << (scudo ? scudo->getNome() : "Nessuno") << "\n";
    cout << "Anello: \t" << (anello ? anello->getNome() : "Nessuno") << "\n";
    cout << "Amuleto: \t" << (amuleto ? amuleto->getNome() : "Nessuno") << "\n\n";

    if (inventario.empty())
    {
        cout << "Il tuo inventario è vuoto.\n";
        return;
    }

    cout << "Oggetti nello zaino:\n";
    for (size_t i = 0; i < inventario.size(); i++)
    {
        cout << i + 1 << ". " << inventario[i]->getNome() << "\n";
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
        if (scelta < 0 || scelta > (int)inventario.size())
        {
            cout << "Scelta non possibile. Riprova.\n";
            continue;
        }
        break;
    }
    if (scelta > 0 && scelta <= (int)inventario.size())
    {
        inventario[scelta - 1]->usa(*this);
    }
}

// Interagisci con la stanza
void Player::interagisciStanza(Stanza &stanza)
{
    stanza.mostraAzioni();
    int scelta;
    cin >> scelta;
    auto [id, msg] = stanza.scegliAzione(scelta);
    if (id.empty())
        return;

    if (id.rfind("Raccogli ", 0) == 0)
    { // inizia con "Raccogli "
        std::string nome_oggetto = id.substr(9);
        auto it = std::find_if(stanza.oggetti_stanza.begin(), stanza.oggetti_stanza.end(),
                               [&nome_oggetto](Oggetto *o)
                               { return o->getNome() == nome_oggetto; });
        if (it != stanza.oggetti_stanza.end())
        {
            aggiungiOggettoInventario(*it);
            stanza.rimuoviOggetto(nome_oggetto);
            // Se hai un messaggio specifico:
            if (!msg.empty())
                {
                std::cout << msg << "\n";
                }
            else
            {
                std::cout << "Hai raccolto " << nome_oggetto << "!\n";
                stanza.azioni.erase(stanza.azioni.begin() + (scelta - 1));
            }
        }
        else
        {
            std::cout << "Oggetto non trovato nella stanza.\n";
        }
    }
    else
    {
        // altre azioni base: stampa il messaggio descrittivo, se presente
        if (!msg.empty())
            std::cout << msg << "\n";
        else
            std::cout << id << "\n";
    }
}

    // Movimento

    void Player::muovi(Stanza & stanza)
    {
        stanza.mostraUscite();
        int scelta;
        cin >> scelta;
        if (scelta >= 1 && scelta <= (int)stanza.uscite.size())
        {
            setPos(stanza.uscite[scelta - 1]);
        }
        else
        {
            cout << "Uscita non valida.\n";
        }
    }

    // Attacca nemico

    void Player::attacca(Nemico & n)
    {

        // Attacco base (da modificare)

        int danno = getStr();
        cout << "Attacchi " << n.getNome() << " e infliggi " << danno << " danni.\n";
        n.subisciDanno(danno);
    }

    void Player::aggiornaStatistiche()
    {

        getHp();
        getMana();
        getStr();
        getAgi();
        getMind();
        getFaith();

    }

    // Genera personaggio

    void Player::generaPersonaggio()
    {

        cout << "Inserisci il nome del tuo eroe: ";
        cin >> nome;

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dist(5, 20);

        do {

        str = dist(gen);
        agi = dist(gen);
        mind = dist(gen);
        faith = dist(gen);

        } while (str + agi + mind + faith != 40);

        hp = 50 + str * 2;
        setHpMax(hp);
        mana = 30 + mind * 2 + faith;
        setManaMax(mana);
        

        cout << "Benvenuto, " << nome << "! Le tue statistiche iniziali sono:\n";
        cout << "HP: \t\t" << getHp() << "\n";
        cout << "Mana: \t\t" << getMana() << "\n";
        cout << "Forza: \t\t" << getStr() << "\n";
        cout << "Agilità: \t" << getAgi() << "\n";
        cout << "Mente: \t\t" << getMind() << "\n";
        cout << "Fede: \t\t" << getFaith() << "\n\n";

        system("pause");
    }

    // Distruttore

    Player::~Player()
    {
        for (auto *o : inventario)
        {
            delete o;
        }

        inventario.clear();
    }
