#include <iostream>
#include <map>
#include <string>
#include <random>
#include "Player.h"
#include "Stanza.h"
#include "Oggetto.h"
#include "Nemico.h"
#include "Evento.h"
#include "Game.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "it_IT.UTF-8");

        // ======= Creazione stanze ======= //
        // Stanza(nome, descrizione, descrizione_breve)

        Stanza* entrata = new Stanza("Entrata", "Sei all'entrata dell'immenso dungeon...", "entrata del dungeon");

        entrata->aggiungiAzione("Osserva la porta", "Una grande portone, pieno di sigilli arcani, blocca il tuo cammino. Inspiegabilmente, è aperto. Sembra che qualcuno sia già passato di qui.");

        Stanza* sala_spada = new Stanza("Sala della Spada", "Ti ritrovi in una piccola stanza, poco dopo il grande portone. Al centro, uno scheletro giace appoggiato ad un pilastro.", "sala della spada");
        

        Stanza* sala_boss = new Stanza("Sala Boss", "Il fuoco inonda questa immensa sala.", "una grande sala illuminata dal fuoco");

        Stanza* sala_alchimia = new Stanza("Sala dell'Alchimia", "Questa stanza è piena di strani alambicchi e bottiglie. Molti sono rotti da tempo, altri ancora brillano fosforescenti nell'oscurità.", "sala dell'alchimia");
        
        Stanza* sala_ragni = new Stanza("Sala dei Ragni", "La stanza è avvolta in una fitta ragnatela. Il pavimento è disseminato di ossa di piccoli animali.", "sala buia e piena di ragnatele");


        // ======= Creazione oggetti ======= //
        // Oggetto(nome, tipo, descrizione_stanza, bonus_hp=0, bonus_mana=0, bonus_str=0, bonus_agi=0, bonus_mind=0, bonus_faith=0)

        sala_spada->aggiungiOggetto(new Oggetto
            ("Spada Arrugginita del Guerriero", "arma", 
                "Una spada vecchia e arrugginita giace anch'essa accanto allo scheletro.", 
                0,0,2,0,0,0));

        sala_alchimia->aggiungiOggetto(new Oggetto
            ("Pozione di Cura Minore", "pozione", 
                "Una piccola pozione rossa, con un liquido zampillante'.", 
                20,0,0,0,0,0));

        // ======= Creazione nemici ======= //
        // Nemico(nome, descrizione, hp, tipo, potenza, danno, flag)

        Nemico* drago = new Nemico
            ("Drago", 
            "Un enorme drago rosso con occhi fiammeggianti si erge di fronte a te.", 
            20, "fisico", 20, 20);

       /* non ancora usati 

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
        
        */

        Nemico* ragno = new Nemico
            ("Ragno Gigante", 
            "Un enorme ragno con zanne velenose e otto occhi rossi ti osserva minacciosamente.", 
            18, "fisico", 15, 8);


        // ======= Creazione eventi ======= //
        // Evento(nome, condizione, effetto, attivato=false)

        Evento attacco_ragno ("Attacco del Ragno",
            [](Player& p, Stanza& s) -> bool {
                return p.prova(p.getAgi(), 12) && s.getNome() == "Sala dei Ragni";
            },

            [ragno](Player& p, Stanza& s) {
                cout << "Mentre entri nella stanza, un enorme ragno ti salta addosso dalle ombre!\n";
                p.subisciDanno(5);
                s.aggiungiScontro(ragno);
            }
        );

        sala_ragni->aggiungiEvento(attacco_ragno);
        
        // Aggiungi scontro: stanza->aggiungiScontro(nemico)

        sala_boss->aggiungiScontro(drago);

        // ======= Collegamento stanze ======= //
        // Aggiungi uscita: stanza->aggiungiUscita(stanza_adiacente)

        entrata->aggiungiUscita(sala_spada);
        sala_spada->aggiungiUscita(entrata);
        sala_spada->aggiungiUscita(sala_alchimia);
        sala_spada->aggiungiUscita(sala_ragni);
        sala_alchimia->aggiungiUscita(sala_spada);
        sala_spada->aggiungiUscita(sala_boss);
        sala_ragni->aggiungiUscita(sala_spada);
        sala_boss->aggiungiUscita(sala_spada);

        // ======= Creazione player ======= //
        // Player(nome, hp, mana, str, agi, mind, faith, pos)

        string nome;

        cout << "Benvenuto nello Zork Clone!\n";
        

        // Genera statistiche base

        Player p;

        p.generaPersonaggio();
        p.setPos(entrata); // posizione iniziale

        // ======= Inizio gioco ======= //


        // == Creazione game == //
        
        Game game( &p, entrata);
        game.loop();

        return 0;
}
