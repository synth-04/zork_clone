#include "Game.h"
#include "Player.h"
#include "Stanza.h"
#include <iostream>

void Game::loop() {
    while (true) {
        current_->entra(*player_);
        player_->scegliAzione(*current_);
        current_ = player_->getPos();
    }
}
