#ifndef GAME_H
#define GAME_H

class Player;
class Stanza;

class Game {
    Player* player_;
    Stanza* start_;

public:
    Game(Player* p, Stanza* start) : player_(p), start_(start) {}

    void loop();
};

#endif
