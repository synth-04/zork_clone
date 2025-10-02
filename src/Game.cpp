#include "Game.h"
#include "Player.h"
#include "Stanza.h"
#include <iostream>
#include <limits>

using namespace std;

static void flush_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Game::loop() {
    // Se il player non ha la posizione impostata, usa quella di start
    if (!player_->getPos()) {
        player_->setPos(start_);
    }

    while (true) {
        Stanza* current = player_->getPos();
        if (!current) {
            cout << "[ERRORE] Posizione del player nulla. Reimposto alla stanza iniziale.\n";
            player_->setPos(start_);
            current = player_->getPos();
            if (!current) {
                cout << "[ERRORE] Start nullo. Interrompo.\n";
                return;
            }
        }

        // Mostra/trigger eventi/combattimenti della stanza corrente
        current->entra(*player_);

        // Prompt azioni del player (muovi, inventario, interagisci, esci)
        player_->scegliAzione(*current);

        // Se lo stato dello stream di input è rotto, ripulisci per sicurezza
        if (!cin) flush_input();
    }
}

