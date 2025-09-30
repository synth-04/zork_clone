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
    string descrizioneStanza_;
    int bHp_=0, bMana_ = 0, bStr_=0, bAgi_=0, bMind_=0, bFaith_=0;
    

public:

    // Costruttore

    Oggetto (const string& n, const string& t, const string& ds,
            int bh=0, int bm=0, int bs=0, int ba=0, int bmi=0, int bf=0) :
        nome_(n), tipo_(t), descrizioneStanza_(ds),
        bHp_(bh), bMana_(bm), bStr_(bs), bAgi_(ba), bMind_(bmi), bFaith_(bf) {}

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

    // Distruttore
    virtual ~Oggetto() = default;
};

#endif

