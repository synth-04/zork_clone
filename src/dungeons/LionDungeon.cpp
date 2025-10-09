#include "Dungeon.h"
#include "Stanza.h"
#include "Oggetto.h"
#include "Nemico.h"
#include "Evento.h"
#include <memory>
#include <utility>

namespace dungeon {

DungeonData buildLionDungeon() {
    DungeonData d;

    // ======= Creazione stanze ======= //
        // Stanza(nome, descrizione, descrizione_breve)

        Stanza* entrata = new Stanza("Entrata", 
            "Sei all'entrata del dungeon del Leone. Di fronte a te, un immenso portone reca i simboli di un leone dorato. Il portone sembra inaspettatamente aperto. Forse qualcuno è già passato di qui...", 
            "entrata del dungeon");

        Stanza* sala_spada = new Stanza("Sala della Spada", 
            "Ti ritrovi in una piccola stanza, poco dopo il grande portone. Al centro, uno scheletro giace appoggiato ad un pilastro.", 
            "sala della spada");
        

        Stanza* sala_boss = new Stanza("Sala Boss", 
            "La luce delle torce illumina questa stanza gigantesca. Odore di carcasse in putrefazione inonda la stanza.", 
            "una grande sala illuminata dalle torce");

        Stanza* sala_alchimia = new Stanza("Sala dell'Alchimia", 
            "Questa stanza è piena di strani alambicchi e bottiglie. Molti sono rotti da tempo, altri ancora brillano fosforescenti nell'oscurità.", 
            "sala dell'alchimia");
        
        Stanza* sala_ragni = new Stanza("Sala dei Ragni", 
            "La stanza è avvolta in una fitta ragnatela. Il pavimento è disseminato di ossa di piccoli animali. Alcuni avventurieri sono caduti nella trappola degli aracnidi...fortunatamente, è possibile recuperare i loro averi.", 
            "sala buia e piena di ragnatele");

        // ==== Creazione azioni aggiuntive ===== //
        // id, label, effetto, condizione(nullptr se non presente), one-shot (true se sparisce una volta attivato)

        entrata->aggiungiAzione(
                    "osserva_porta",
                    "Osserva la porta",
                    [](Player& p, Stanza& s){
                        if (p.prova(p.getMind()/2, 15)) {
                            cout << "Noti l'araldica del casato Lathander, estinto da secoli. Il Leone d'Oro simboleggiava il suo potere.\n";
                        } else {
                            cout << "Non riesci a ricordare nulla di utile su quel portone.\n";
                        }
                    },
                    nullptr,
                    true
                );

        // ======= Creazione oggetti ======= //
        // Oggetto(nome, tipo, descrizione, bonus_hp, bonus_mana, bonus_str, bonus_agi, bonus_mind, bonus_faith, bonus_def)

        sala_spada->aggiungiOggetto(new Oggetto
            ("Spada Arrugginita del Guerriero", "arma", 
                "Una spada vecchia e arrugginita giace accanto allo scheletro.", 
                0, 0, 2, 0, 0, 0, 0));

        sala_alchimia->aggiungiOggetto(new Oggetto
            ("Pozione di Guarigione", "pozione", 
                "Una piccola pozione rossa, con un liquido zampillante.", 
                30, 0, 0,0,0,0, 0));

        sala_alchimia->aggiungiOggetto (new Oggetto
            ("Bastone dell'Eremita", "arma", 
            "Un vecchio bastone logoro. Sembra possedere potere arcano sopito.",
            0, 0, 0, 0, 3, 2, 0));

        sala_ragni->aggiungiOggetto ( new Oggetto
            ("Armatura a piastre", "armatura", 
            "Un'armatura a piastre, appartenuta ad uno sfortunato avventuriero.",
            0, 0, 0, -2, 0, 0, 6));

        // ======= Creazione magie ====== //
        // Magia(nome, descrizione, costo_mana, effetto, tipo)

        Magia* dardo_forza = (new Magia
            ("Dardo di forza", "Una magia che lancia un dardo di forza cosmica contro l'avversario.", 7,
            [](Player& p, Nemico& n) {
                if (p.getMind() >= 5)
                {
                    n.subisciDanno(p.getMind());
                    cout << "Colpisci con il tuo dardo incantato e infliggi " << p.getMind() << " danni \n";
                }
                else 
                {
                    cout << "Provi a lanciare la magia, ma le tua abilità arcane sono insufficienti. \n";
                }
            }, "arcano"));

        sala_alchimia->aggiungiMagia(dardo_forza);

        // ======= Creazione nemici ======= //
        // Nemico(nome, descrizione, hp, tipo, potenza, danno, flag)

        Nemico* drago = new Nemico
            ("Viverna", 
            "Un enorme viverna si erge di fronte a te: una creatura dall'aspetto di rettile, con due ali squamate, due possenti arti inferiori e una coda con aculei. La viverna si prepara a renderti il suo prossimo pasto.", 
            40, "fisico", 20, 30);

        Nemico* ragno = new Nemico
            ("Ragno Gigante", 
            "Il ragno, con zanne grondanti di veleno e otto occhi rossi, ti osserva minacciosamente, pronto a colpire di nuovo.", 
            18, "fisico", 15, 8);

        // ancora da usare

        /*

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

        // ======= Creazione eventi ======= //
        // Evento(nome, condizione, effetto, attivato=false)

        Evento attacco_ragno ("Attacco del Ragno",
            [](Player& p, Stanza& s) -> bool {
                return !(p.prova(p.getAgi(), 15)) && s.getNome() == "Sala dei Ragni";
            },

            [ragno](Player& p, Stanza& s) {
                p.subisciDanno(5);
                cout << "Mentre osservi la stanza, un enorme ragno ti salta addosso dalle ombre! Subisci 5 danni!\n";
                s.aggiungiScontro(ragno);
            }
        );

        sala_ragni->aggiungiEvento(attacco_ragno);
        
        // Aggiungi scontro: stanza->aggiungiScontro(nemico)

        sala_boss->aggiungiScontro(drago);

        // ======= Collegamento stanze ======= //
        // Aggiungi uscita: stanza->aggiungiUscita(stanza_adiacente)
        // collega (stanza a, stanza b)

        dungeon::collega(entrata, sala_spada);
        dungeon::collega(sala_spada, sala_alchimia);
        dungeon::collega(sala_spada, sala_ragni);
        dungeon::collega(sala_spada, sala_boss);

    // wrapping in unique_ptr

    d.stanze.emplace_back(unique_ptr<Stanza>(entrata));
    d.stanze.emplace_back(unique_ptr<Stanza>(sala_spada));
    d.stanze.emplace_back(unique_ptr<Stanza>(sala_ragni));
    d.stanze.emplace_back(unique_ptr<Stanza>(sala_alchimia));
    d.stanze.emplace_back(unique_ptr<Stanza>(sala_boss));

    d.start = entrata;

    return d;

}

}
