#include "combat.hpp"
#include "interface.hpp"
#include "sauvegarde.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>

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
    else if (type == "Electrik") effet = "⚡";
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

void infligerDegats(Pokemon* cible, Pokemon* attaquant, Entraineur* attaquantOwner) {
    // Obtenir les types pour le débogage
    std::string typeAttaquant = attaquant->getType1();
    std::string typeDefenseur = cible->getType1();
    
    // Débogage pour voir les types impliqués
    std::cout << "DEBUG: Type attaquant = " << typeAttaquant << ", Type défenseur = " << typeDefenseur << std::endl;
    
    // Calcul direct du multiplicateur sans passer par la méthode calculerMultiplicateur
    double coeff = 1.0;
    
    // === CAS SPÉCIAUX ===
    
    // Électrik > Eau (×2)
    if (typeAttaquant == "Electrik" && typeDefenseur == "Eau") {
        coeff = 2.0;
        std::cout << "DEBUG: Électrik est super efficace contre Eau!" << std::endl;
    }
    // Eau > Feu (×2)
    else if (typeAttaquant == "Eau" && typeDefenseur == "Feu") {
        coeff = 2.0;
        std::cout << "DEBUG: Eau est super efficace contre Feu!" << std::endl;
    }
    // Feu > Plante (×2)
    else if (typeAttaquant == "Feu" && typeDefenseur == "Plante") {
        coeff = 2.0;
        std::cout << "DEBUG: Feu est super efficace contre Plante!" << std::endl;
    }
    // Plante > Eau (×2)
    else if (typeAttaquant == "Plante" && typeDefenseur == "Eau") {
        coeff = 2.0;
        std::cout << "DEBUG: Plante est super efficace contre Eau!" << std::endl;
    }
    // Eau résiste au Feu (×0.5)
    else if (typeAttaquant == "Feu" && typeDefenseur == "Eau") {
        coeff = 0.5;
        std::cout << "DEBUG: Eau résiste au Feu!" << std::endl;
    }
    // Feu résiste à la Plante (×0.5)
    else if (typeAttaquant == "Plante" && typeDefenseur == "Feu") {
        coeff = 0.5;
        std::cout << "DEBUG: Feu résiste à la Plante!" << std::endl;
    }
    
    std::cout << "DEBUG: Multiplicateur final = " << coeff << std::endl;
    
    // Calculer les dégâts avec le multiplicateur de type
    int degats = static_cast<int>(attaquant->getPuissance() * coeff);
    
    // 🌟 NOUVEAUTÉ : Vérifier si l'attaquant appartient à un Maître Pokémon
    MaitrePokemon* maitre = dynamic_cast<MaitrePokemon*>(attaquantOwner);
    if (maitre) {
        int degatsAvantBonus = degats;
        degats = maitre->appliquerBonusDegats(degats);
        std::cout << "🌟 BONUS MAÎTRE POKÉMON APPLIQUÉ ! (" 
                  << degatsAvantBonus << " → " << degats << " dégâts)" << std::endl;
    }
    
    // Infliger les dégâts
    cible->subirDegats(degats);

    // Afficher des informations sur l'efficacité de l'attaque
    std::cout << cible->getNom() << " subit " << degats << " dégâts";
    
    if (coeff >= 2.0) {
        std::cout << " (C'est super efficace!) ";
        Beep(1000, 300);  // Son pour super efficace
    } 
    else if (coeff <= 0.1) {
        std::cout << " (Ça n'affecte pas " << cible->getNom() << "...) ";
        Beep(200, 300);  // Son pour inefficace
    } 
    else if (coeff <= 0.5) {
        std::cout << " (Ce n'est pas très efficace...) ";
        Beep(400, 300);  // Son pour pas très efficace
    } 
    else {
        std::cout << " ! ";
    }
    
    std::cout << std::endl;

    // Afficher la barre de vie
    afficherBarreDeVie(cible->getHp(), cible->getMaxHp());
    std::cout << std::endl;
    pauseCourt();
}

// Fonction automatique pour sélectionner le prochain Pokémon
void selectionnerPokemonAutomatique(Entraineur& entraineur) {
    if (!entraineur.touteEquipeKO()) {
        for (int i = 0; i < 6; ++i) {
            Pokemon* pokemon = entraineur.pokemonActif(i);
            if (pokemon && !pokemon->estKo()) {
                entraineur.selectionnerPokemon(i);
                std::cout << entraineur.getNom() << " envoie " << pokemon->getNom() << " !" << std::endl;
                pauseCourt();
                return;
            }
        }
    }
}

bool verifierKO(Pokemon* cible, Pokemon* attaquant, Entraineur& possesseur) {
    if (cible->estKo()) {
        afficherBoite(cible->getNom() + " est K.O. !");
        std::cout << attaquant->getNom() << " a vaincu " << cible->getNom() << " !" << std::endl;
        pauseCourt();

        if (!possesseur.touteEquipeKO()) {
            // Sélection automatique du prochain Pokémon
            selectionnerPokemonAutomatique(possesseur);
        }
        return true;
    }
    return false;
}

void tourDeCombat(Pokemon* attaquant, Pokemon* cible, Entraineur& cibleOwner, Entraineur& attaquantOwner) {
    if (!attaquant || !cible || attaquant->estKo() || cible->estKo()) return;
    afficherAttaque(attaquant);
    infligerDegats(cible, attaquant, &attaquantOwner); // ✅ Passer le propriétaire de l'attaquant
    verifierKO(cible, attaquant, cibleOwner);
}

void demarrerCombat(Entraineur& joueur, Entraineur& adversaire) {
    // Réinitialiser le compteur à chaque nouveau combat
    compteurAttaques = 0;
    
    afficherBoite("⚔️  COMBAT POKEMON !");

    // Afficher les Pokémon qui entrent au combat
    std::cout << "\n=== Début du combat ===" << std::endl;
    afficherEntreeCombat(joueur.pokemonActif(), "🔵 " + joueur.getNom());
    afficherEntreeCombat(adversaire.pokemonActif(), "🔴 " + adversaire.getNom());

    // Combat automatique : alternance de tours
    while (!joueur.touteEquipeKO() && !adversaire.touteEquipeKO()) {
        std::cout << "\n--- Tour du joueur ---" << std::endl;
        tourDeCombat(joueur.pokemonActif(), adversaire.pokemonActif(), adversaire, joueur); // ✅ Passer les deux entraîneurs
        
        if (adversaire.touteEquipeKO()) break;
        
        std::cout << "\n--- Tour de l'adversaire ---" << std::endl;
        tourDeCombat(adversaire.pokemonActif(), joueur.pokemonActif(), joueur, adversaire); // ✅ Passer les deux entraîneurs
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
            
            // Afficher un message qui rappelle au joueur qu'il peut sauvegarder sa partie
            MaitrePokemon* maitre = dynamic_cast<MaitrePokemon*>(&adversaire);
            if (maitre) {
                std::cout << "Victoire contre un Maître Pokémon ! N'oubliez pas de sauvegarder votre partie via le menu principal." << std::endl;
                pauseCourt(1500);
            }
        }
    }
    std::cout << "==============================\n";
    pauseCourt(1500);
}