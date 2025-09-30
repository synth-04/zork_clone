#include "Game.h"
#include "Player.h"
#include "Stanza.h"
#include <iostream>
#include <limits>

// #define NDEBUG

static void flush_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::loop() {
    // Se il player non ha la posizione impostata, usa quella di start
    if (!player_->getPos()) {
        player_->setPos(start_);
    }

    while (true) {
        Stanza* current = player_->getPos();
        if (!current) {
            std::cout << "[ERRORE] Posizione del player nulla. Reimposto alla stanza iniziale.\n";
            player_->setPos(start_);
            current = player_->getPos();
            if (!current) {
                std::cout << "[ERRORE] Start nullo. Interrompo.\n";
                return;
            }
        }

        // Mostra/trigger eventi/combattimenti della stanza corrente
        current->entra(*player_);

        #ifdef NDEBUG
            std::cout << "[DBG] current room: " << current->getNome() << "\n"; std::cout.flush();
        #endif

        // Prompt azioni del player (muovi, inventario, interagisci, esci)
        player_->scegliAzione(*current);

        #ifdef NDEBUG
            std::cout << "[DBG] player action done\n"; std::cout.flush();
        #endif

        // Se lo stato dello stream di input è rotto, ripulisci per sicurezza
        if (!std::cin) flush_input();
    }
}

