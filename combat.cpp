#include "combat.hpp"
#include <iostream>

void demarrerCombat(Entraineur& joueur, Entraineur& adversaire ) {
    std::cout << "\n⚔️  Le combat commence !\n";

    while (!joueur.touteEquipeKO() && !adversaire.touteEquipeKO()) {
        // Tour du joueur
        Pokemon* attaquant = joueur.pokemonActif();
        Pokemon* cible = adversaire.pokemonActif();

        if (attaquant && cible && !attaquant->estKo() && !cible->estKo()) {
            std::cout << attaquant->getNom() << " lance " << attaquant->getAttaque() << " !\n";
            double multiplicateur = cible->calculerMultiplicateur(attaquant->getType1());
            int degats = static_cast<int>(attaquant->getPuissance() * multiplicateur);
            cible->subirDegats(degats);
            std::cout << cible->getNom() << " subit " << degats << " points de degats.\n";

            if (cible->estKo()) {
                std::cout << cible->getNom() << " est K.O. !\n";
                attaquant->gagnerExperience();
                std::cout << attaquant->getNom() << " gagne un niveau ! (Nv. " << attaquant->getNiveau() << ")\n";
            }
        }

        // Tour du adversaire
        attaquant = adversaire.pokemonActif();
        cible = joueur.pokemonActif();

        if (attaquant && cible && !attaquant->estKo() && !cible->estKo()) {
            std::cout << attaquant->getNom() << " utilise " << attaquant->getAttaque() << " !\n";
            double multiplicateur = cible->calculerMultiplicateur(attaquant->getType1());
            int degats = static_cast<int>(attaquant->getPuissance() * multiplicateur);
            cible->subirDegats(degats);
            std::cout << cible->getNom() << " perd " << degats << " PV.\n";

            if (cible->estKo()) {
                std::cout << cible->getNom() << " est hors-combat !\n";
                attaquant->gagnerExperience();
                std::cout << attaquant->getNom() << " gagne un niveau ! (Nv. " << attaquant->getNiveau() << ")\n";
            }
        }
    }

    // Résultat du combat
    if (joueur.touteEquipeKO()) {
        std::cout << "\n🏆 " << adversaire.pokemonActif()->getNom() << " remporte le duel !\n";
    } else {
        std::cout << "\n🏆 " << joueur.pokemonActif()->getNom() << " sort vainqueur du combat !\n";
    }
}
