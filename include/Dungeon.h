#ifndef DUNGEON_H
#define DUNGEON_H

#include <memory>
#include <vector>

#include "Stanza.h"

using namespace std;

namespace dungeon {

inline void collega(Stanza* a, Stanza* b) {
    a->aggiungiUscita(b);
    b->aggiungiUscita(a);
}

struct DungeonData {
    vector<unique_ptr<Stanza>> stanze;
    Stanza* start = nullptr;           // entrata al dungeon
};

DungeonData buildLionDungeon();

}





#endif