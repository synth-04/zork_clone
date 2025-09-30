#ifndef OGGETTO_H
#define OGGETTO_H

#include <string>
#include <memory>
#include <iostream>

using namespace std;

class Player;

class Oggetto {
protected:
    string nome_;
    string tipo_; // "arma", "armatura", "scudo", "anello", "amuleto", "consumabile"
    int bHp_=0, bMana_ = 0, bStr_=0, bAgi_=0, bMind_=0, bFaith_=0;
    string descrizioneStanza_;

public:

    // Costruttore

    Oggetto(string nome, string tipo, string descr,
            int hp=0, int mana = 0, int str=0, int agi=0, int mind=0, int faith=0)
        : nome_(move(nome)), tipo_(move(tipo)), bHp_(hp), bMana_(mana), bStr_(str),
          bAgi_(agi), bMind_(mind), bFaith_(faith), descrizioneStanza_(move(descr)) {}

    // Metodi getter

    const string& getNome() const { return nome_; }
    const string& getTipo() const { return tipo_; }

    int getBonusHp()   const { return bHp_; }
    int getBonusMana() const { return bMana_; }
    int getBonusStr()  const { return bStr_; }
    int getBonusAgi()  const { return bAgi_; }
    int getBonusMind() const { return bMind_; }
    int getBonusFaith()const { return bFaith_; }

    const string& getDescrizioneStanza() const { return descrizioneStanza_; }

    // Azione quando l'oggetto viene usato o equipaggiato
    void usa(Player& p);

    // Factory helper
    template<class T, class...Args>
    static unique_ptr<Oggetto> make(Args&&...args) {
        return make_unique<T>(forward<Args>(args)...);
    }
};

#endif

