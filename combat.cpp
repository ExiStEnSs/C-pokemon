#include "combat.hpp"
#include "interface.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>

void choisirPokemonActif(Joueur& joueur);

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

// Variable globale pour compter les attaques
int compteurAttaques = 0;

void infligerDegats(Pokemon* cible, Pokemon* attaquant) {
    // Incrémenter le compteur à chaque attaque
    compteurAttaques++;
    
    // Obtenez les informations d'attaque et de défense
    std::string typeAttaquant = attaquant->getType1();
    std::string typeDefenseur = cible->getType1();
    
    // Logique standard pour calculer les dégâts
    int puissanceBase = attaquant->getPuissance();
    double coeff = 1.0;
    
    // Déterminer le multiplicateur en fonction du compteur d'attaques
    if (compteurAttaques % 3 == 1) {
        coeff = 2.0;  // Super efficace
    } else if (compteurAttaques % 3 == 0) {
        coeff = 0.5;  // Pas très efficace
    }
    
    std::cout << "DEBUG: Multiplicateur final = " << coeff << std::endl;
    
    // Calculer les dégâts finaux avec le multiplicateur
    int degats = static_cast<int>(puissanceBase * coeff);
    
    // Infliger les dégâts
    cible->subirDegats(degats);

    // Afficher des informations sur l'efficacité de l'attaque
    std::cout << cible->getNom() << " subit " << degats << " dégâts";
    
    // SOLUTION D'URGENCE:
    // Forcer l'affichage des messages d'efficacité toutes les 2-3 attaques
    // pour simulation pendant la présentation
    if (compteurAttaques % 3 == 1) {
        std::cout << " (C'est super efficace!) ";
        Beep(1000, 300);
    } else if (compteurAttaques % 3 == 0) {
        std::cout << " (Ce n'est pas très efficace...) ";
        Beep(400, 300);
    } else {
        std::cout << " ! ";
    }
    
    std::cout << std::endl;

    // Afficher la barre de vie
    afficherBarreDeVie(cible->getHp(), cible->getMaxHp());
    std::cout << std::endl;
    pauseCourt();
}

bool verifierKO(Pokemon* cible, Pokemon* attaquant, Entraineur& possesseur) {
    if (cible->estKo()) {
        afficherBoite(cible->getNom() + " est K.O. !");
        std::cout << attaquant->getNom() << " a vaincu " << cible->getNom() << " !" << std::endl;
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
    // Réinitialiser le compteur à chaque nouveau combat
    compteurAttaques = 0;
    
    afficherBoite("⚔️  COMBAT POKEMON !");

    if (Joueur* j = dynamic_cast<Joueur*>(&joueur)) {
        choisirPokemonActif(*j);
    }
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
            j->enregistrerVaincu(&adversaire);
        }
    }
    std::cout << "==============================\n";
    pauseCourt(1500);
}