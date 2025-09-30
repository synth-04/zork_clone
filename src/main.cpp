#include <iostream>
#include <map>
#include <string>
#include <random>
#include "Player.h"
#include "Stanza.h"
#include "Oggetto.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "it_IT.UTF-8");

        // ======= Creazione stanze ======= //
        // Stanza(nome, descrizione, descrizione_breve)

        Stanza* entrata = new Stanza("Entrata", "Sei all'entrata dell'immenso dungeon...", "entrata del dungeon");
        entrata->aggiungiAzione("Osserva la porta", "Una grande portone, pieno di sigilli arcani, blocca il tuo cammino. Inspiegabilmente, è aperto. Sembra che qualcuno sia già passato di qui.");

        Stanza* sala_spada = new Stanza("Sala della Spada", "Ti ritrovi in una piccola stanza, poco dopo il grande portone. Al centro, uno scheletro giace appoggiato ad un pilastro.", "sala della spada");
        sala_spada->aggiungiOggetto(new Oggetto
            ("Spada Arrugginita del Guerriero", "arma", 
                "Una spada vecchia e arrugginita giace anch'essa accanto allo scheletro.", 
                0,0,2,0,0,0));

        Stanza* sala_boss = new Stanza("Sala Boss", "Il fuoco inonda questa immensa sala.", "una grande sala illuminata dal fuoco");

        // ======= Creazione nemici ======= //
        // Nemico(nome, descrizione, hp, tipo, potenza, danno, flag)

        Nemico* drago = new Nemico
            ("Drago", 
            "Un enorme drago rosso con occhi fiammeggianti si erge di fronte a te.", 
            20, "fisico", 20, 20);

        Nemico* goblin = new Nemico
            ("Goblin", 
            "Un piccolo goblin verde con uno sguardo folle ti blocca il cammino. Vuole sgozzarti!", 
            10, "fisico", 10, 5);

        Nemico* fantasma = new Nemico
            ("Fantasma", 
            "Un inquietante fantasma traslucido fluttua nell'aria, emettendo un lamento spettrale.", 
            15, "magico", 15, 10);

        Nemico* lich = new Nemico
            ("Lich", 
            "Un potente lich, avvolto in vesti logore e con occhi che brillano di una luce malvagia, ti fissa con disprezzo.", 
            25, "magico", 20, 15);

        Nemico* ragno = new Nemico
            ("Ragno Gigante", 
            "Un enorme ragno con zanne velenose e otto occhi rossi ti osserva minacciosamente.", 
            18, "fisico", 15, 8);

        
        // Aggiungi scontro: stanza->aggiungiScontro(nemico)

        sala_boss->aggiungiScontro(drago);

        // ======= Collegamento stanze ======= //
        // Aggiungi uscita: stanza->aggiungiUscita(stanza_adiacente)

        entrata->aggiungiUscita(sala_spada);
        sala_spada->aggiungiUscita(entrata);
        sala_spada->aggiungiUscita(sala_boss);
        sala_boss->aggiungiUscita(sala_spada);

        // ======= Creazione player ======= //
        // Player(nome, hp, mana, str, agi, mind, faith, pos)

        string nome;

        cout << "Benvenuto nello Zork Clone!\n";
        

        // Genera statistiche base

        Player p;

        p.generaPersonaggio();
        p.setPos(entrata);

        // ======= Inizio gioco ======= //


        // Loop principale
        while (true) {
            p.getPos()->mostra(p);
            p.scegliAzione(*p.getPos());
        }


    system("pause");

    return 0;
}
