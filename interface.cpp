// interface.cpp - Version sans codes ANSI
#include "interface.hpp"
#include "sauvegarde.hpp"
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

// Cette fonction a été déplacée dans la classe Sauvegarde

void afficherLeadersBattus() {
    clearScreen();
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    std::cout << "|       LEADERS DE GYM BATTUS         |" << std::endl;
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    
    std::vector<std::string> leaders = Sauvegarde::chargerLeadersBattus();
    
    if (leaders.empty()) {
        std::cout << "Aucun leader battu ou fichier introuvable." << std::endl;
    } else {
        for (const auto& ligne : leaders) {
            std::cout << ligne << std::endl;
        }
    }
    
    waitForEnter();
}

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
            Sauvegarde::sauvegarderLeaderBattu(joueur, leaders[choix - 1]);
            
            // Rappeler au joueur qu'il peut sauvegarder
            std::cout << "Félicitations ! N'oubliez pas que vous pouvez sauvegarder votre partie via le menu principal." << std::endl;
            waitForEnter();
        }
    }
}

// Menu de sauvegarde et chargement
void menuSauvegardeChargement(Joueur& joueur, std::vector<Pokemon*>& cataloguePokemon, std::vector<Entraineur*>& leaders, std::vector<Entraineur*>& maitres) {
    clearScreen();
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    std::cout << "|       SAUVEGARDE & CHARGEMENT       |" << std::endl;
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    
    std::cout << "Options disponibles :" << std::endl;
    std::cout << "1. 💾 Sauvegarder la progression actuelle (équipe, badges, statistiques)" << std::endl;
    std::cout << "2. 📂 Charger une partie sauvegardée précédemment" << std::endl;
    std::cout << "0. ◀️ Retour au menu principal" << std::endl;
    
    std::cout << "\nVotre choix : ";
    int choix;
    std::cin >> choix;
    
    switch (choix) {
        case 1:
            // Sauvegarder la partie
            Sauvegarde::sauvegarderPartie(joueur);
            std::cout << "Sauvegarde effectuée avec succès !" << std::endl;
            waitForEnter();
            break;
            
        case 2:
            // Charger une partie
            if (Sauvegarde::chargerPartie(joueur, cataloguePokemon)) {
                std::cout << "Partie chargée avec succès !" << std::endl;
            } else {
                std::cout << "Impossible de charger la partie. Fichier de sauvegarde non trouvé ou corrompu." << std::endl;
            }
            waitForEnter();
            break;
            
        case 0:
        default:
            break;
    }
}

// Menu principal amélioré
void menuPrincipal(Joueur* joueur, std::vector<Entraineur*> leaders, std::vector<Entraineur*> maitres, std::vector<Pokemon*>& cataloguePokemon) {
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
        std::cout << "3. Gestion de l'entraineur" << std::endl;
        std::cout << "4. Voir les statistiques" << std::endl;
        std::cout << "5. Combattre un leader" << std::endl;
        std::cout << "6. Interagir avec un Pokémon" << std::endl;
        std::cout << "7. Affronter un Maître Pokémon" << std::endl;
        std::cout << "8. Afficher les leaders battus" << std::endl;
        std::cout << "9. 💾 Sauvegarder la partie" << std::endl;

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
                menuGestionEntraineur(joueur, cataloguePokemon);
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
            case 9:
                menuSauvegardeChargement(*joueur, cataloguePokemon, leaders, maitres);
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
void menuGestionEntraineur(Joueur*& joueur, std::vector<Pokemon*>& cataloguePokemon) {
    bool retourMenu = false;
    
    while (!retourMenu) {
        clearScreen();
        std::cout << "+" << std::string(50, '=') << "+" << std::endl;
        std::cout << "|           GESTION DE L'ENTRAINEUR              |" << std::endl;
        std::cout << "+" << std::string(50, '=') << "+" << std::endl;
        
        std::cout << "Entraîneur actuel : " << joueur->getNom() << std::endl;
        std::cout << "Options disponibles :" << std::endl;
        std::cout << "1. Modifier l'ordre des Pokémon" << std::endl;
        std::cout << "2. Choisir un autre entraîneur depuis le CSV" << std::endl;
        std::cout << "3. Créer un nouvel entraîneur" << std::endl;
        std::cout << "0. Retour au menu principal" << std::endl;
        
        std::cout << "\nVotre choix : ";
        int choix;
        std::cin >> choix;
        
        switch (choix) {
            case 0:
                retourMenu = true;
                break;
                
            case 1: {
                // Modifier l'ordre des Pokémon
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
            
                if (i >= 1 && i <= joueur->getTailleEquipe() && 
                    j >= 1 && j <= joueur->getTailleEquipe()) {
                    joueur->echangerPokemon(i - 1, j - 1);
                    
                    std::cout << "\nNouvelle composition de l'équipe :\n";
                    joueur->afficherEquipe();
                } else {
                    std::cout << "\nNuméro(s) invalide(s). Veuillez choisir entre 1 et " 
                              << joueur->getTailleEquipe() << "." << std::endl;
                }
                
                waitForEnter();
                break;
            }
                
            case 2: {
                // Choisir un entraîneur depuis le CSV
                clearScreen();
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                std::cout << "|     CHOIX D'UN ENTRAINEUR           |" << std::endl;
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                
                // Charger la liste des entraîneurs depuis joueur.csv
                std::vector<std::string> nomsEntraineurs;
                std::ifstream fichier("joueur.csv");
                std::string ligne;
                
                // Ignorer l'en-tête
                std::getline(fichier, ligne);
                
                int index = 1;
                while (std::getline(fichier, ligne)) {
                    std::stringstream ss(ligne);
                    std::string nom;
                    std::getline(ss, nom, ',');  // Le nom est le premier champ
                    
                    nomsEntraineurs.push_back(nom);
                    std::cout << index << ". " << nom << std::endl;
                    index++;
                }
                
                fichier.close();
                
                if (nomsEntraineurs.empty()) {
                    std::cout << "Aucun entraîneur trouvé dans le fichier CSV." << std::endl;
                    waitForEnter();
                    break;
                }
                
                std::cout << "\nChoisissez un entraîneur (0 pour annuler) : ";
                int choixEntraineur;
                std::cin >> choixEntraineur;
                
                if (choixEntraineur > 0 && choixEntraineur <= static_cast<int>(nomsEntraineurs.size())) {
                    // Libérer l'entraîneur actuel et créer le nouveau
                    delete joueur;
                    joueur = creerJoueurDepuisCSV("joueur.csv", cataloguePokemon, choixEntraineur - 1);
                    
                    if (joueur) {
                        std::cout << "Vous êtes maintenant " << joueur->getNom() << "." << std::endl;
                    } else {
                        std::cerr << "Erreur lors du chargement de l'entraîneur. Création d'un entraîneur par défaut." << std::endl;
                        joueur = new Joueur("Dresseur");
                    }
                }
                
                waitForEnter();
                break;
            }
                
            case 3: {
                // Créer un nouvel entraîneur avec des Pokémon par numéro de Pokédex
                clearScreen();
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                std::cout << "|     CREATION D'UN ENTRAINEUR         |" << std::endl;
                std::cout << "+" << std::string(38, '=') << "+" << std::endl;
                
                std::string nouveauNom;
                std::cout << "Entrez le nom du nouvel entraîneur : ";
                std::cin.ignore();  // Pour ignorer le \n restant
                std::getline(std::cin, nouveauNom);
                
                // Créer le nouvel entraîneur
                Joueur* nouvelEntraineur = new Joueur(nouveauNom);
                
                // Afficher le catalogue des Pokémon disponibles
                std::cout << "\nCatalogue des Pokémon disponibles :" << std::endl;
                std::cout << "--------------------------------------" << std::endl;
                for (size_t i = 0; i < cataloguePokemon.size(); ++i) {
                    std::cout << (i + 1) << ". " << cataloguePokemon[i]->getNom() 
                              << " [" << cataloguePokemon[i]->getType1();
                    
                    if (!cataloguePokemon[i]->getType2().empty()) {
                        std::cout << "/" << cataloguePokemon[i]->getType2();
                    }
                    
                    std::cout << "]" << std::endl;
                }
                
                // Sélectionner jusqu'à 6 Pokémon
                std::cout << "\nSélectionnez jusqu'à 6 Pokémon par leur numéro Pokédex (0 pour terminer) :" << std::endl;
                
                for (int i = 0; i < 6; ++i) {
                    std::cout << "Pokémon " << (i + 1) << " (0 pour terminer) : ";
                    int numPokedex;
                    std::cin >> numPokedex;
                    
                    if (numPokedex == 0) break;
                    
                    if (numPokedex > 0 && numPokedex <= static_cast<int>(cataloguePokemon.size())) {
                        // Créer une copie du Pokémon et l'ajouter à l'équipe
                        Pokemon* pokemon = cataloguePokemon[numPokedex - 1];
                        Pokemon* copie = nullptr;
                        
                        // Créer la bonne instance en fonction du type
                        if (pokemon->getType1() == "Feu") {
                            copie = new Feu(pokemon->getNom(), pokemon->getType2(), 
                                        pokemon->getMaxHp(), pokemon->getAttaque(), 
                                        pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Eau") {
                            copie = new Eau(pokemon->getNom(), pokemon->getType2(), 
                                         pokemon->getMaxHp(), pokemon->getAttaque(), 
                                         pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Plante") {
                            copie = new Plante(pokemon->getNom(), pokemon->getType2(), 
                                           pokemon->getMaxHp(), pokemon->getAttaque(), 
                                           pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Electrik") {
                            copie = new Electrik(pokemon->getNom(), pokemon->getType2(), 
                                             pokemon->getMaxHp(), pokemon->getAttaque(), 
                                             pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Normal") {
                            copie = new Normal(pokemon->getNom(), pokemon->getType2(), 
                                           pokemon->getMaxHp(), pokemon->getAttaque(), 
                                           pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Psy") {
                            copie = new Psy(pokemon->getNom(), pokemon->getType2(), 
                                        pokemon->getMaxHp(), pokemon->getAttaque(), 
                                        pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Poison") {
                            copie = new Poison(pokemon->getNom(), pokemon->getType2(), 
                                           pokemon->getMaxHp(), pokemon->getAttaque(), 
                                           pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Insecte") {
                            copie = new Insecte(pokemon->getNom(), pokemon->getType2(), 
                                            pokemon->getMaxHp(), pokemon->getAttaque(), 
                                            pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Sol") {
                            copie = new Sol(pokemon->getNom(), pokemon->getType2(), 
                                        pokemon->getMaxHp(), pokemon->getAttaque(), 
                                        pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Roche") {
                            copie = new Roche(pokemon->getNom(), pokemon->getType2(), 
                                          pokemon->getMaxHp(), pokemon->getAttaque(), 
                                          pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Glace") {
                            copie = new Glace(pokemon->getNom(), pokemon->getType2(), 
                                          pokemon->getMaxHp(), pokemon->getAttaque(), 
                                          pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Dragon") {
                            copie = new Dragon(pokemon->getNom(), pokemon->getType2(), 
                                           pokemon->getMaxHp(), pokemon->getAttaque(), 
                                           pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Spectre") {
                            copie = new Spectre(pokemon->getNom(), pokemon->getType2(), 
                                            pokemon->getMaxHp(), pokemon->getAttaque(), 
                                            pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Combat") {
                            copie = new Combat(pokemon->getNom(), pokemon->getType2(), 
                                           pokemon->getMaxHp(), pokemon->getAttaque(), 
                                           pokemon->getPuissance());
                        } else if (pokemon->getType1() == "Fee" || pokemon->getType1() == "Fée") {
                            copie = new Fee(pokemon->getNom(), pokemon->getType2(), 
                                        pokemon->getMaxHp(), pokemon->getAttaque(), 
                                        pokemon->getPuissance());
                        } else {
                            // Type par défaut
                            copie = new Pokemon(pokemon->getNom(), pokemon->getType1(), 
                                            pokemon->getType2(), pokemon->getMaxHp(), 
                                            pokemon->getAttaque(), pokemon->getPuissance());
                        }
                        
                        nouvelEntraineur->ajouterPokemon(copie);
                        std::cout << "✅ " << pokemon->getNom() << " ajouté à l'équipe." << std::endl;
                    } else {
                        std::cout << "❌ Numéro invalide. Veuillez choisir entre 1 et " 
                                  << cataloguePokemon.size() << "." << std::endl;
                        --i;  // Réessayer pour ce slot
                    }
                }
                
                // Vérifier si l'équipe contient au moins un Pokémon
                if (nouvelEntraineur->getTailleEquipe() == 0) {
                    std::cout << "\nL'équipe doit contenir au moins un Pokémon. Création annulée." << std::endl;
                    delete nouvelEntraineur;
                } else {
                    // Remplacer l'entraîneur actuel par le nouveau
                    delete joueur;
                    joueur = nouvelEntraineur;
                    
                    std::cout << "\nNouvel entraîneur créé avec succès !" << std::endl;
                    std::cout << "Composition de l'équipe :" << std::endl;
                    joueur->afficherEquipe();
                    
                    // Sauvegarder le nouvel entraîneur dans le CSV
                    std::cout << "\nVoulez-vous sauvegarder ce nouvel entraîneur dans le fichier joueur.csv ? (1: Oui, 0: Non) : ";
                    int sauvegarder;
                    std::cin >> sauvegarder;
                    
                    if (sauvegarder == 1) {
                        // Ajouter l'entraîneur à la fin du fichier
                        std::ofstream fichier("joueur.csv", std::ios::app);
                        
                        if (fichier.is_open()) {
                            fichier << joueur->getNom();
                            
                            // Écrire les noms des Pokémon (jusqu'à 6)
                            for (int i = 0; i < 6; ++i) {
                                fichier << ",";
                                if (i < joueur->getTailleEquipe()) {
                                    fichier << joueur->pokemonActif(i)->getNom();
                                }
                            }
                            
                            fichier << std::endl;
                            fichier.close();
                            
                            std::cout << "✅ Entraîneur sauvegardé dans joueur.csv" << std::endl;
                        } else {
                            std::cerr << "❌ Erreur lors de l'ouverture du fichier joueur.csv" << std::endl;
                        }
                    }
                }
                
                waitForEnter();
                break;
            }
                
            default:
                std::cout << "Option invalide. Veuillez réessayer." << std::endl;
                waitForEnter();
                break;
        }
    }
}