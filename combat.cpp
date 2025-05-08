#include "combat.hpp"
#include "interface.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>  

void choisirPokemonActif(Joueur& joueur); // ✅ Déclaration nécessaire

void pauseCourt(int ms = 900) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void afficherBarreDeVie(int hp, int hpMax, int largeur = 20) {
    float ratio = static_cast<float>(hp) / hpMax;
    int barres = static_cast<int>(ratio * largeur);
    std::cout << "[";
    for (int i = 0; i < barres; ++i) std::cout << "█";
    for (int i = barres; i < largeur; ++i) std::cout << "-";
    std::cout << "] " << hp << "/" << hpMax << " PV";
}

void afficherBoite(const std::string& message) {
    int taille = message.size() + 4;
    std::cout << "+" << std::string(taille, '-') << "+\n";
    std::cout << "|  " << message << "  |\n";
    std::cout << "+" << std::string(taille, '-') << "+\n";
}

void afficherEntreeCombat(Pokemon* p, const std::string& proprio) {
    std::cout << proprio << " envoie " << p->getNom()
              << " (Nv. " << p->getNiveau() << ") ["
              << p->getType1();
    if (!p->getType2().empty()) std::cout << "/" << p->getType2();
    std::cout << "]" << std::endl;
    std::cout << "PV : ";
    afficherBarreDeVie(p->getHp(), p->getMaxHp());
    std::cout << std::endl;
    pauseCourt();
}

void afficherAttaque(const Pokemon* attaquant) {
    std::string nom = attaquant->getNom();
    std::string attaque = attaquant->getAttaque();
    std::string type = attaquant->getType1();

    std::string effet;

    if (type == "Feu") effet = "🔥";
    else if (type == "Eau") effet = "💧";
    else if (type == "Plante") effet = "🌿";
    else if (type == "Électrik" || type == "Electrik") effet = "⚡";
    else effet = "💥";

    std::cout << effet << effet << effet << "  [" << nom << " utilise " << attaque << "!]  " << effet << effet << effet << std::endl;

    // 🔊 Petit bip optionnel (Windows seulement)
    Beep(600, 100);  // fréquence, durée en ms
    Beep(800, 100);
    Beep(500, 100);

    pauseCourt();
}

void infligerDegats(Pokemon* cible, Pokemon* attaquant) {
    double coeff = cible->calculerMultiplicateur(attaquant->getType1());
    int degats = static_cast<int>(attaquant->getPuissance() * coeff);
    cible->subirDegats(degats);

    std::cout << cible->getNom() << " subit " << degats << " dégâts";
    if (coeff > 1.0) std::cout << " (c'est super efficace)";
    else if (coeff < 1.0) std::cout << " (ce n'est pas très efficace)";
    std::cout << " !" << std::endl;

    afficherBarreDeVie(cible->getHp(), cible->getMaxHp());
    std::cout << std::endl;
    pauseCourt();
}

bool verifierKO(Pokemon* cible, Pokemon* attaquant, Entraineur& possesseur) {
    if (cible->estKo()) {
        afficherBoite(cible->getNom() + " est K.O. !");
        attaquant->gagnerExperience();
        std::cout << attaquant->getNom() << " passe au niveau " << attaquant->getNiveau() << " !" << std::endl;
        pauseCourt();

        if (!possesseur.touteEquipeKO()) {
            Joueur* joueur = dynamic_cast<Joueur*>(&possesseur);
            if (joueur) {
                choisirPokemonActif(*joueur);
            } else {
                for (int i = 0; i < 6; ++i) {
                    possesseur.selectionnerPokemon(i);
                    if (!possesseur.pokemonActif()->estKo()) break;
                }
            }
        }
        return true;
    }
    return false;
}

bool tourDuJoueur(Joueur& joueur, Entraineur& adversaire) {
    while (true) {
        Pokemon* attaquant = joueur.pokemonActif();
        Pokemon* cible = adversaire.pokemonActif();

        std::cout << "\nQue voulez-vous faire ?\n";
        std::cout << "1. Attaquer\n";
        std::cout << "2. Changer de Pokémon\n";
        std::cout << "3. Utiliser un objet (indisponible)\n";
        std::cout << "4. Fuir\n";
        std::cout << "Votre choix : ";
        int choix;
        std::cin >> choix;

        switch (choix) {
            case 1:
                afficherAttaque(attaquant);
                infligerDegats(cible, attaquant);
                verifierKO(cible, attaquant, adversaire);
                return false;

            case 2:
                choisirPokemonActif(joueur);
                return false;

            case 3:
                std::cout << "🚫 Les objets ne sont pas utilisables pour le moment.\n";
                pauseCourt();
                break;

            case 4:
                std::cout << "Vous prenez la fuite...\n";
                pauseCourt();
                return true;

            default:
                std::cout << "Choix invalide.\n";
                pauseCourt();
        }
    }
}

void tourDeCombat(Pokemon* attaquant, Pokemon* cible, Entraineur& cibleOwner) {
    if (!attaquant || !cible || attaquant->estKo() || cible->estKo()) return;
    afficherAttaque(attaquant);
    infligerDegats(cible, attaquant);
    verifierKO(cible, attaquant, cibleOwner);
}

void demarrerCombat(Entraineur& joueur, Entraineur& adversaire) {
    afficherBoite("⚔️  COMBAT POKEMON !");

    if (Joueur* j = dynamic_cast<Joueur*>(&joueur)) {
        choisirPokemonActif(*j);
    }

    afficherEntreeCombat(joueur.pokemonActif(), "🔵 Joueur");
    afficherEntreeCombat(adversaire.pokemonActif(), "🔴 Adversaire");

    while (!joueur.touteEquipeKO() && !adversaire.touteEquipeKO()) {
        if (tourDuJoueur(dynamic_cast<Joueur&>(joueur), adversaire)) {
            afficherBoite("❌ Vous avez fui le combat.");
            return;
        }

        if (adversaire.touteEquipeKO()) break;

        tourDeCombat(adversaire.pokemonActif(), joueur.pokemonActif(), joueur);
    }

    std::cout << "\n==============================\n";
    std::cout << "💥 Fin du combat\n";

    Joueur* j = dynamic_cast<Joueur*>(&joueur);
    if (joueur.touteEquipeKO()) {
        afficherBoite("❌ Vous avez perdu le combat...");
        if (j) j->enregistrerDefaite();
    } else {
        afficherBoite("✅ Victoire ! Vous êtes le meilleur dresseur !");
        if (j) {
            j->enregistrerVictoire();
            j->enregistrerVaincu(&adversaire); // ✅ Enregistre le vaincu
        }
    }
    std::cout << "==============================\n";
    pauseCourt(1500);
}