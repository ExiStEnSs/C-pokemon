// interface.cpp - Version sans codes ANSI
#include "interface.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>


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

// Nouvelles fonctions pour la gestion des leaders et l'historique des combats
void menuChoixLeader(Joueur& joueur, std::vector<Entraineur*>& leaders) {
    clearScreen();
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    std::cout << "|       CHOIX DU LEADER DE GYM        |" << std::endl;
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    
    if (leaders.empty()) {
        std::cout << "Aucun leader disponible." << std::endl;
        waitForEnter();
        return;
    }
    
    std::cout << "Leaders disponibles :" << std::endl;
    for (size_t i = 0; i < leaders.size(); ++i) {
        LeaderGym* leader = dynamic_cast<LeaderGym*>(leaders[i]);
        if (leader) {
            std::cout << (i + 1) << ". " << leader->getNom() << " (Arène de " << leader->getNomGym() << ")" << std::endl;
        } else {
            std::cout << (i + 1) << ". " << leaders[i]->getNom() << std::endl;
        }
    }
    
    std::cout << "\nVotre choix (0 pour revenir) : ";
    int choix;
    std::cin >> choix;
    
    if (choix > 0 && choix <= static_cast<int>(leaders.size())) {
        // Sauvegarder le nombre de victoires avant le combat
        int victoires_avant = joueur.getVictoires();
        
        // Lancer le combat
        menuCombat(joueur, *leaders[choix - 1]);
        
        // Vérifier si le joueur a gagné
        if (joueur.getVictoires() > victoires_avant) {
            sauvegarderLeaderBattu(joueur, leaders[choix - 1]);
        }
    }
}

void sauvegarderLeaderBattu(const Joueur& joueur, Entraineur* leader) {
    std::ofstream fichier("leaders_battus.txt", std::ios::app);
    if (!fichier) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier leaders_battus.txt" << std::endl;
        return;
    }
    
    // Obtenir la date et heure actuelles
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    
    // Écrire dans le fichier
    LeaderGym* gym_leader = dynamic_cast<LeaderGym*>(leader);
    if (gym_leader) {
        fichier << "Leader " << leader->getNom() 
                << " (Arène de " << gym_leader->getNomGym() << ")"
                << " battu par " << joueur.getNom() 
                << " le " << ss.str() << std::endl;
    } else {
        fichier << leader->getNom() << " battu par " << joueur.getNom() 
                << " le " << ss.str() << std::endl;
    }
    
    fichier.close();
}

void afficherLeadersBattus() {
    clearScreen();
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    std::cout << "|       LEADERS DE GYM BATTUS         |" << std::endl;
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    
    std::ifstream fichier("leaders_battus.txt");
    if (!fichier) {
        std::cout << "Aucun leader battu ou fichier introuvable." << std::endl;
    } else {
        std::string ligne;
        while (std::getline(fichier, ligne)) {
            std::cout << ligne << std::endl;
        }
        fichier.close();
    }
    
    waitForEnter();
}

// Menu principal amélioré
void menuPrincipal(Joueur* joueur, std::vector<Entraineur*> leaders, std::vector<Entraineur*> maitres) {
    bool continuer = true;
    while (continuer) {
        clearScreen();
        std::cout << R"(
        
███╗░░░███╗███████╗███╗░░██╗██╗░░░██╗  ██████╗░██████╗░██╗███╗░░██╗░█████╗░██╗██████╗░░█████╗░██╗░░░░░
████╗░████║██╔════╝████╗░██║██║░░░██║  ██╔══██╗██╔══██╗██║████╗░██║██╔══██╗██║██╔══██╗██╔══██╗██║░░░░░
██╔████╔██║█████╗░░██╔██╗██║██║░░░██║  ██████╔╝██████╔╝██║██╔██╗██║██║░░╚═╝██║██████╔╝███████║██║░░░░░
██║╚██╔╝██║██╔══╝░░██║╚████║██║░░░██║  ██╔═══╝░██╔══██╗██║██║╚████║██║░░██╗██║██╔═══╝░██╔══██║██║░░░░░
██║░╚═╝░██║███████╗██║░╚███║╚██████╔╝  ██║░░░░░██║░░██║██║██║░╚███║╚█████╔╝██║██║░░░░░██║░░██║███████╗
╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░╚═════╝░  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚════╝░╚═╝╚═╝░░░░░╚═╝░░╚═╝╚══════╝
        )" << std::endl;
        
        std::cout << "Dresseur: " << joueur->getNom() << std::endl;
        std::cout << std::endl;
        
        std::cout << "0. Quitter" << std::endl;
        std::cout << "1. Afficher l'equipe" << std::endl;
        std::cout << "2. Soigner les Pokemon" << std::endl;
        std::cout << "3. Modifier l'ordre" << std::endl;
        std::cout << "4. Voir les statistiques" << std::endl;
        std::cout << "5. Combattre un leader" << std::endl;
        std::cout << "6. Interagir avec un Pokémon" << std::endl;
        std::cout << "7. Affronter un Maître Pokémon" << std::endl;
        std::cout << "8. Afficher les leaders battus" << std::endl;

        std::cout << std::endl << "Votre choix : ";
        int choix;
        std::cin >> choix;
        
        switch (choix) {
            case 0:
                std::cout << "Fermeture de la simulation. A bientot !" << std::endl;
                continuer = false;
                break;
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
            case 3: {
                clearScreen();
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                std::cout << "|     MODIFICATION DE L'ORDRE          |" << std::endl;
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
            
                joueur->afficherEquipe();
            
                int i, j;
                std::cout << "\nEntrez le numéro du 1er Pokémon à échanger (1-6) : ";
                std::cin >> i;
                std::cout << "Entrez le numéro du 2e Pokémon à échanger (1-6) : ";
                std::cin >> j;
            
                joueur->echangerPokemon(i - 1, j - 1);
            
                std::cout << "\nNouvelle composition de l'équipe :\n";
                joueur->afficherEquipe();
                waitForEnter();
                break;
            }
            case 4:
                clearScreen();
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                std::cout << "|         VOS STATISTIQUES             |" << std::endl;
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                
                joueur->afficherStats();
                waitForEnter();
                break;
            case 5:
                menuChoixLeader(*joueur, leaders);
                break;
            case 6: {
                clearScreen();
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                std::cout << "|     INTERACTION AVEC UN POKÉMON      |" << std::endl;
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
            
                Pokemon* actif = joueur->pokemonActif();
                if (actif) {
                    std::cout << actif->interaction() << std::endl;
                } else {
                    std::cout << "Aucun Pokémon actif pour interagir." << std::endl;
                }
            
                waitForEnter();
                break;
            }
            case 7: {
                clearScreen();
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                std::cout << "|     MAÎTRE POKÉMON EN APPROCHE       |" << std::endl;
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
            
                if (joueur->getNombreBadges() < 4) {
                    std::cout << "⛔ Vous devez posséder les 4 badges pour affronter un Maître Pokémon !" << std::endl;
                    waitForEnter();
                    break;
                }
            
                if (!maitres.empty()) {
                    srand(static_cast<unsigned int>(time(0)));
                    int index = rand() % maitres.size();
                    Entraineur* maitre = maitres[index];
            
                    std::cout << "⚔️  Le Maître " << maitre->getNom() << " entre en scène !" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
            
                    menuCombat(*joueur, *maitre);
                } else {
                    std::cout << "Aucun Maître Pokémon disponible." << std::endl;
                }
            
                waitForEnter();
                break;
            }
            case 8:
                afficherLeadersBattus();
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

    std::cout << "Un adversaire approche..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "\n" << adversaire.getNom() << " envoie " << adversaire.pokemonActif()->getNom()
              << " ! Préparez-vous !" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));

    std::cout << "\nVous envoyez : " << joueur.pokemonActif()->getNom() << " !" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "\nLe combat commence..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Lancement réel du combat
    demarrerCombat(joueur, adversaire);

    std::cout << "\nRetour au menu principal..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void choisirPokemonActif(Joueur& joueur) {
    while (true) {
        clearScreen();
        std::cout << "=== Choisissez un Pokémon ===\n\n";
        joueur.afficherEquipe();

        std::cout << "\nNuméro du Pokémon à envoyer au combat : ";
        int choix;
        std::cin >> choix;

        if (choix >= 1 && choix <= 6) {
            Pokemon* selection = joueur.pokemonActif();
            joueur.selectionnerPokemon(choix - 1);
            if (!joueur.pokemonActif()->estKo()) {
                std::cout << "\nVous avez choisi : " << joueur.pokemonActif()->getNom() << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            } else {
                std::cout << "Ce Pokémon est K.O. ! Choisissez-en un autre.\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1200));
            }
        } else {
            std::cout << "Entrée invalide. Essayez encore.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}