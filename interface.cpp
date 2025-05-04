// interface.cpp - Version sans codes ANSI
#include "interface.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

// Définition des couleurs ANSI vides (pour désactiver les couleurs)
namespace Color {
    const std::string RESET = "";
    const std::string RED = "";
    const std::string GREEN = "";
    const std::string YELLOW = "";
    const std::string BLUE = "";
    const std::string MAGENTA = "";
    const std::string CYAN = "";
    const std::string WHITE = "";
    const std::string BOLD = "";
}

// Effacer l'écran (désactivé pour éviter les problèmes)
void clearScreen() {
    // Ne fait rien, juste pour éviter les problèmes
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
}

// Effet de frappe simplifié
void typingEffect(const std::string& text, int delayMs) {
    // Version simplifiée sans effet
    std::cout << text << std::endl;
}

// Attendre que l'utilisateur appuie sur Entrée
void waitForEnter() {
    std::cout << "\nAppuyez sur Entree pour continuer...";
    std::cin.ignore(10000, '\n');
    std::cin.get();
}

// Afficher une boîte de dialogue
void showDialogBox(const std::string& text) {
    int width = 60;
    std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
    std::cout << "| " << text << std::string(width - text.length() - 4, ' ') << " |" << std::endl;
    std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
}

// Afficher une barre de HP
void showHPBar(const std::string& name, int current, int max, int width) {
    float percentage = static_cast<float>(current) / max;
    int barFill = static_cast<int>(percentage * width);
    
    std::cout << name << " HP: [";
    for (int i = 0; i < barFill; i++) std::cout << "#";
    for (int i = barFill; i < width; i++) std::cout << "-";
    std::cout << "] " << current << "/" << max << std::endl;
}

// Afficher la carte d'un Pokémon
void showPokemonCard(const Pokemon* pokemon) {
    if (!pokemon) return;
    
    int width = 30;
    std::cout << "+" << std::string(width - 2, '=') << "+" << std::endl;
    std::cout << "| " << pokemon->getNom() << std::string(width - pokemon->getNom().length() - 4, ' ') << " |" << std::endl;
    
    // Type
    std::string typeInfo = "Type: " + pokemon->getType1();
    if (!pokemon->getType2().empty()) {
        typeInfo += "/" + pokemon->getType2();
    }
    std::cout << "| " << typeInfo << std::string(width - typeInfo.length() - 4, ' ') << " |" << std::endl;
    
    // Niveau
    std::string niveauInfo = "Niveau: " + std::to_string(pokemon->getNiveau());
    std::cout << "| " << niveauInfo << std::string(width - niveauInfo.length() - 4, ' ') << " |" << std::endl;
    
    // Séparateur
    std::cout << "|" << std::string(width - 2, '-') << "|" << std::endl;
    
    // Points de vie
    std::string hpInfo = "HP: " + std::to_string(pokemon->getHp()) + "/" + std::to_string(pokemon->getMaxHp());
    std::cout << "| " << hpInfo << std::string(width - hpInfo.length() - 4, ' ') << " |" << std::endl;
    
    // Attaque
    std::string attaqueInfo = "Attaque: " + pokemon->getAttaque();
    std::cout << "| " << attaqueInfo << std::string(width - attaqueInfo.length() - 4, ' ') << " |" << std::endl;
    
    std::string puissanceInfo = "Puissance: " + std::to_string(pokemon->getPuissance());
    std::cout << "| " << puissanceInfo << std::string(width - puissanceInfo.length() - 4, ' ') << " |" << std::endl;
    
    // Bas de la carte
    std::cout << "+" << std::string(width - 2, '=') << "+" << std::endl;
}

// Afficher la liste des Pokémon d'un entraîneur
void showPokemonList(const Entraineur* entraineur) {
    entraineur->afficherEquipe();
}

// Écran titre
void showTitleScreen() {
    clearScreen();
    std::cout << R"(

    ██████╗░░█████╗░██╗░░██╗███████╗███╗░░░███╗░█████╗░███╗░░██╗
    ██╔══██╗██╔══██╗██║░██╔╝██╔════╝████╗░████║██╔══██╗████╗░██║
    ██████╔╝██║░░██║█████═╝░█████╗░░██╔████╔██║██║░░██║██╔██╗██║
    ██╔═══╝░██║░░██║██╔═██╗░██╔══╝░░██║╚██╔╝██║██║░░██║██║╚████║
    ██║░░░░░╚█████╔╝██║░╚██╗███████╗██║░╚═╝░██║╚█████╔╝██║░╚███║
    ╚═╝░░░░░░╚════╝░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝
    )" << std::endl;
    
    std::cout << "                  Combat de Pokemon - C++ Edition" << std::endl;
    std::cout << "                       Appuyez sur Entree..." << std::endl;
    std::cin.get();
}

// Écran de combat
void showBattleScreen(const Pokemon* playerPokemon, const Pokemon* enemyPokemon) {
    clearScreen();
    
    // Afficher le Pokémon ennemi
    std::cout << "ADVERSAIRE" << std::endl;
    showHPBar(enemyPokemon->getNom(), enemyPokemon->getHp(), enemyPokemon->getMaxHp());
    std::cout << std::endl;
    
    // Afficher un peu d'espace entre les deux
    std::cout << std::string(40, ' ') << std::endl;
    
    // Afficher le Pokémon du joueur
    showHPBar(playerPokemon->getNom(), playerPokemon->getHp(), playerPokemon->getMaxHp());
    std::cout << "VOTRE POKEMON" << std::endl;
    
    // Afficher les options du combat
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "Que voulez-vous faire ?" << std::endl;
    std::cout << "1. " << playerPokemon->getAttaque() << std::endl;
    std::cout << "2. Changer de Pokemon" << std::endl;
    std::cout << "3. Utiliser un objet" << std::endl;
    std::cout << "4. Fuir" << std::endl;
}

// Animation d'attaque
void showAttackAnimation(const std::string& attackName, int damage, bool isSuperEffective) {
    std::cout << attackName << " !" << std::endl;
    
    if (isSuperEffective) {
        std::cout << "C'est super efficace !" << std::endl;
    }
    
    std::cout << "-" << damage << " PV !" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

// Menu principal amélioré
void menuPrincipal(Joueur* joueur, std::vector<Entraineur*> leaders, std::vector<Entraineur*> maitres) {
    bool continuer = true;
    while (continuer) {
        clearScreen();
        std::cout << R"(
        
███╗░░░███╗███████╗███╗░░██╗██╗░░░██╗  ██████╗░██████╗░██╗███╗░░██╗░█████╗░██╗██████╗░░█████╗░██╗░░░░░
████╗░████║██╔════╝████╗░██║██║░░░██║  ██╔══██╗██╔══██╗██║████╗░██║██╔══██╗██║██╔══██╗██╔══██╗██║░░░░░
██╔████╔██║█████╗░░██╔██╗██║██║░░░██║  ██████╔╝██████╔╝██║██╔██╗██║██║░░╚═╝██║██████╔╝███████║██║░░░░░
██║╚██╔╝██║██╔══╝░░██║╚████║██║░░░██║  ██╔═══╝░██╔══██╗██║██║╚████║██║░░██╗██║██╔═══╝░██╔══██║██║░░░░░
██║░╚═╝░██║███████╗██║░╚███║╚██████╔╝  ██║░░░░░██║░░██║██║██║░╚███║╚█████╔╝██║██║░░░░░██║░░██║███████╗
╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░╚═════╝░  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚════╝░╚═╝╚═╝░░░░░╚═╝░░╚═╝╚══════╝
        )" << std::endl;
        
        std::cout << "Dresseur: Joueur" << std::endl;
        std::cout << std::endl;
        
        std::cout << "1. Afficher l'equipe" << std::endl;
        std::cout << "2. Soigner les Pokemon" << std::endl;
        std::cout << "3. Modifier l'ordre" << std::endl;
        std::cout << "4. Voir les statistiques" << std::endl;
        std::cout << "5. Combattre un leader" << std::endl;
        std::cout << "6. Quitter" << std::endl;
        
        std::cout << std::endl << "Votre choix : ";
        int choix;
        std::cin >> choix;
        
        switch (choix) {
            case 1: {
                clearScreen();
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                std::cout << "|            VOTRE EQUIPE              |" << std::endl;
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                
                joueur->afficherEquipe();
                waitForEnter();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "Vos Pokemon sont soignes au Centre Pokemon..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                joueur->soignerEquipe();
                std::cout << "Tous vos Pokemon ont retrouve toute leur energie !" << std::endl;
                waitForEnter();
                break;
            }
            case 3:
                std::cout << "Fonction de reorganisation a implementer.\n";
                waitForEnter();
                break;
            case 4:
                clearScreen();
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                std::cout << "|         VOS STATISTIQUES             |" << std::endl;
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                
                joueur->afficherStats();
                waitForEnter();
                break;
            case 5:
                if (!leaders.empty()) {
                    menuCombat(*joueur, *leaders.front());
                } else {
                    std::cout << "Aucun leader disponible." << std::endl;
                    waitForEnter();
                }
                break;
            case 6:
                std::cout << "Fermeture de la simulation. A bientot !" << std::endl;
                continuer = false;
                break;
            default:
                std::cout << "Choix non valide, veuillez reessayer." << std::endl;
                waitForEnter();
        }
    }
}

// Menu de combat amélioré
void menuCombat(Joueur& joueur, Entraineur& adversaire) {
    clearScreen();
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    std::cout << "|              COMBAT !                |" << std::endl;
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    
    std::cout << "Le combat commence !" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // Utiliser la fonction de combat existante
    demarrerCombat(joueur, adversaire);
    
    waitForEnter();
}