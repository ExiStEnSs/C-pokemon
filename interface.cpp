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

void clearScreen() {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
}

void typingEffect(const std::string& text, int delayMs) {
    std::cout << text << std::endl;
}
void waitForEnter() {
    std::cout << "\nAppuyez sur Entree pour continuer...";
    std::cin.ignore(10000, '\n');
    std::cin.get();
}
void showDialogBox(const std::string& text) {
    int width = 60;
    std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
    std::cout << "| " << text << std::string(width - text.length() - 4, ' ') << " |" << std::endl;
    std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
}
void showPokemonList(const Entraineur* entraineur) {
    entraineur->afficherEquipe();
}
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
    std::cout << R"(
░█████╗░██╗░░██╗░█████╗░██╗██╗░░██╗  ██████╗░██╗░░░██╗  ██╗░░░░░███████╗░█████╗░██████╗░███████╗██████╗░
██╔══██╗██║░░██║██╔══██╗██║╚██╗██╔╝  ██╔══██╗██║░░░██║  ██║░░░░░██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
██║░░╚═╝███████║██║░░██║██║░╚███╔╝░  ██║░░██║██║░░░██║  ██║░░░░░█████╗░░███████║██║░░██║█████╗░░██████╔╝
██║░░██╗██╔══██║██║░░██║██║░██╔██╗░  ██║░░██║██║░░░██║  ██║░░░░░██╔══╝░░██╔══██║██║░░██║██╔══╝░░██╔══██╗
╚█████╔╝██║░░██║╚█████╔╝██║██╔╝╚██╗  ██████╔╝╚██████╔╝  ███████╗███████╗██║░░██║██████╔╝███████╗██║░░██║
░╚════╝░╚═╝░░╚═╝░╚════╝░╚═╝╚═╝░░╚═╝  ╚═════╝░░╚═════╝░  ╚══════╝╚══════╝╚═╝░░╚═╝╚═════╝░╚══════╝╚═╝░░╚═╝

██████╗░███████╗  ░██████╗░██╗░░░██╗███╗░░░███╗
██╔══██╗██╔════╝  ██╔════╝░╚██╗░██╔╝████╗░████║
██║░░██║█████╗░░  ██║░░██╗░░╚████╔╝░██╔████╔██║
██║░░██║██╔══╝░░  ██║░░╚██╗░░╚██╔╝░░██║╚██╔╝██║
██████╔╝███████╗  ╚██████╔╝░░░██║░░░██║░╚═╝░██║
╚═════╝░╚══════╝  ░╚═════╝░░░░╚═╝░░░╚═╝░░░░░╚═╝
    )" << std::endl;
    if (leaders.empty()) {
        std::cout << "Aucun leader disponible." << std::endl;
        waitForEnter();
        return;
    }
    
    // Obtenir la liste des leaders déjà battus
    std::vector<std::string> nomsLeadersBattus = Sauvegarde::extraireNomsLeadersBattus();
    
    std::cout << "Leaders disponibles :" << std::endl;
    std::cout << std::string(45, '-') << std::endl;
    
    for (size_t i = 0; i < leaders.size(); ++i) {
        LeaderGym* leader = dynamic_cast<LeaderGym*>(leaders[i]);
        if (leader) {
            std::cout << (i + 1) << ". " << leader->getNom() << " (Arène de " << leader->getNomGym() << ")";
            
            // Vérifier si ce leader a déjà été battu
            bool dejaBattu = false;
            for (const auto& nomBattu : nomsLeadersBattus) {
                if (nomBattu == leader->getNom()) {
                    dejaBattu = true;
                    break;
                }
            }
            
            if (dejaBattu) {
                std::cout << " ✅ [BADGE OBTENU]";
            } else {
                std::cout << " 🏅 [BADGE DISPONIBLE]";
            }
            std::cout << std::endl;
        } else {
            std::cout << (i + 1) << ". " << leaders[i]->getNom() << std::endl;
        }
    }
    
    std::cout << std::string(45, '-') << std::endl;
    std::cout << "📊 Badges actuels : " << joueur.getNombreBadges() << "/4" << std::endl;
    std::cout << "\nVotre choix (0 pour revenir) : ";
    int choix;
    std::cin >> choix;
    
    if (choix > 0 && choix <= static_cast<int>(leaders.size())) {
        LeaderGym* gym_leader = dynamic_cast<LeaderGym*>(leaders[choix - 1]);
        
        // Vérifier si ce leader a déjà été battu AVANT le combat
        bool dejaBattuAvant = false;
        if (gym_leader) {
            for (const auto& nomBattu : nomsLeadersBattus) {
                if (nomBattu == gym_leader->getNom()) {
                    dejaBattuAvant = true;
                    break;
                }
            }
        }
        
        if (dejaBattuAvant) {
            std::cout << "\n⚠️  Attention : Vous avez déjà battu ce leader et obtenu son badge." << std::endl;
            std::cout << "Voulez-vous le défier à nouveau ? (1: Oui, 0: Non) : ";
            int refaire;
            std::cin >> refaire;
            if (refaire != 1) {
                return;
            }
        }
        
        int victoires_avant = joueur.getVictoires();
        int badges_avant = joueur.getNombreBadges();
        
        // Démarrer le combat
        menuCombat(joueur, *leaders[choix - 1]);
        
        // Vérifier si le combat a été gagné
        if (joueur.getVictoires() > victoires_avant) {
            if (gym_leader) {
                // Sauvegarder uniquement si c'est la première victoire
                if (!dejaBattuAvant) {
                    Sauvegarde::sauvegarderLeaderBattu(joueur, leaders[choix - 1]);
                    joueur.incrementerBadge();
                    std::cout << "\n🎖️ Vous avez obtenu le badge : " << gym_leader->getMedaille() << " !" << std::endl;
                    std::cout << "🌟 Badges obtenus : " << joueur.getNombreBadges() << "/4" << std::endl;
                    std::cout << "💪 Félicitations ! Première victoire contre ce leader !" << std::endl;
                } else {
                    std::cout << "\n✅ Victoire contre " << gym_leader->getNom() << " (déjà battu)" << std::endl;
                    std::cout << "📈 Expérience acquise, mais badge déjà obtenu." << std::endl;
                }
            } else {
                Sauvegarde::sauvegarderLeaderBattu(joueur, leaders[choix - 1]);
            }
            
            std::cout << "Félicitations ! N'oubliez pas que vous pouvez sauvegarder votre partie via le menu principal." << std::endl;
            waitForEnter();
        }
    }
}
void menuPrincipal(Joueur* joueur, std::vector<Entraineur*> leaders, std::vector<Entraineur*> maitres, std::vector<Pokemon*>& cataloguePokemon) {
    bool continuer = true;
    while (continuer) {
        clearScreen();
        std::cout << R"(
        
███╗░░░███╗███████╗███╗░░██╗██╗░░░██╗  ██████╗░██████╗░██╗███╗░░██╗░█████╗░██╗██████╗░░█████╗░██╗░░░░░
████╗░████║██╔════╝████╗░██║██║░░░██║  ██████╗░██╔══██╗██║████╗░██║██╔══██╗██║██╔══██╗██╔══██║██║░░░░░
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
        std::cout << "6. Menu d'interaction" << std::endl;
        std::cout << "7. Affronter un Maître Pokémon" << std::endl;
        std::cout << "8. 💾 Sauvegarder la partie" << std::endl;
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
                std::cout << R"(
██╗░░░██╗░█████╗░████████╗██████╗░███████╗  ███████╗░██████╗░██╗░░░██╗██╗██████╗░███████╗
██║░░░██║██╔══██╗╚══██╔══╝██╔══██╗██╔════╝  ██╔════╝██╔═══██╗██║░░░██║██║██╔══██╗██╔════╝
╚██╗░██╔╝██║░░██║░░░██║░░░██████╔╝█████╗░░  █████╗░░██║██╗██║██║░░░██║██║██████╔╝█████╗░░
░╚████╔╝░██║░░██║░░░██║░░░██╔══██╗██╔══╝░░  ██╔══╝░░╚██████╔╝██║░░░██║██║██╔═══╝░██╔══╝░░
░░╚██╔╝░░╚█████╔╝░░░██║░░░██║░░██║███████╗  ███████╗░╚═██╔═╝░╚██████╔╝██║██║░░░░░███████╗
░░░╚═╝░░░░╚════╝░░░░╚═╝░░░╚═╝░░╚═╝╚══════╝  ╚══════╝░░░╚═╝░░░░╚═════╝░╚═╝╚═╝░░░░░╚══════╝
                )" << std::endl;
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
                std::cout << R"(
██╗░░░██╗░█████╗░░██████╗
██║░░░██║██╔══██╗██╔════╝
╚██╗░██╔╝██║░░██║╚█████╗░
░╚████╔╝░██║░░██║░╚═══██╗
░░╚██╔╝░░╚█████╔╝██████╔╝
░░░╚═╝░░░░╚════╝░╚═════╝░

░██████╗████████╗░█████╗░████████╗██╗░██████╗████████╗██╗░██████╗░██╗░░░██╗███████╗░██████╗
██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔════╝╚══██╔══╝██║██╔═══██╗██║░░░██║██╔════╝██╔════╝
╚█████╗░░░░██║░░░███████║░░░██║░░░██║╚█████╗░░░░██║░░░██║██║██╗██║██║░░░██║█████╗░░╚█████╗░
░╚═══██╗░░░██║░░░██╔══██║░░░██║░░░██║░╚═══██╗░░░██║░░░██║╚██████╔╝██║░░░██║██╔══╝░░░╚═══██╗
██████╔╝░░░██║░░░██║░░██║░░░██║░░░██║██████╔╝░░░██║░░░██║░╚═██╔═╝░╚██████╔╝███████╗██████╔╝
╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░╚═╝╚═════╝░░░░╚═╝░░░╚═╝░░░╚═╝░░░░╚═════╝░╚══════╝╚═════╝░
                )" << std::endl;
                joueur->afficherStats();
                waitForEnter();
                break;
            case 5:
                menuChoixLeader(*joueur, leaders);
                break;
            case 6: {
                menuInteraction(*joueur, leaders, maitres);
                break;
            }
            case 7: {
                clearScreen();
                std::cout << R"(
███╗░░░███╗░█████╗░██╗████████╗██████╗░███████╗
████╗░████║██╔══██╗██║╚══██╔══╝██╔══██╗██╔════╝
██╔████╔██║███████║██║░░░██║░░░██████╔╝█████╗░░
██║╚██╔╝██║██╔══██║██║░░░██║░░░██╔══██╗██╔══╝░░
██║░╚═╝░██║██║░░██║██║░░░██║░░░██║░░██║███████╗
╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝

██████╗░░█████╗░██╗░░██╗███████╗███╗░░░███╗░█████╗░███╗░░██╗  ███████╗███╗░░██╗
██╔══██╗██╔══██╗██║░██╔╝██╔════╝████╗░████║██╔══██╗████╗░██║  ██╔════╝████╗░██║
██████╔╝██║░░██║█████═╝░█████╗░░██╔████╔██║██║░░██║██╔██╗██║  █████╗░░██╔██╗██║
██╔═══╝░██║░░██║██╔═██╗░██╔══╝░░██║╚██╔╝██║██║░░██║██║╚████║  ██╔══╝░░██║╚████║
██║░░░░░╚█████╔╝██║░╚██╗███████╗██║░╚═╝░██║╚█████╔╝██║░╚███║  ███████╗██║░╚███║
╚═╝░░░░░░╚════╝░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝  ╚══════╝╚═╝░░╚══╝

░█████╗░██████╗░██████╗░██████╗░░█████╗░░█████╗░██╗░░██╗███████╗
██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗██║░░██║██╔════╝
███████║██████╔╝██████╔╝██████╔╝██║░░██║██║░░╚═╝███████║█████╗░░
██╔══██║██╔═══╝░██╔═══╝░██╔══██╗██║░░██║██║░░██╗██╔══██║██╔══╝░░
██║░░██║██║░░░░░██║░░░░░██║░░██║╚█████╔╝╚█████╔╝██║░░██║███████╗
╚═╝░░╚═╝╚═╝░░░░░╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚═╝░░╚═╝╚══════╝
                )" << std::endl;
                if (joueur->getNombreBadges() < 4) {
                    std::cout << "⛔ Vous devez posséder les 4 badges pour affronter un Maître Pokémon !" << std::endl;
                    std::cout << "🏅 Badges actuels : " << joueur->getNombreBadges() << "/4" << std::endl;
                    waitForEnter();
                    break;
                }
                
                if (!maitres.empty()) {
                    // Afficher les maîtres disponibles et déjà battus
                    std::vector<std::string> nomsMaitresBattus = Sauvegarde::extraireNomsMaitresBattus();
                    
                    std::cout << "Maîtres Pokémon disponibles :" << std::endl;
                    std::cout << std::string(40, '-') << std::endl;
                    
                    for (size_t i = 0; i < maitres.size(); ++i) {
                        std::cout << (i + 1) << ". Maître " << maitres[i]->getNom();
                        
                        // Vérifier si déjà battu
                        bool dejaBattu = false;
                        for (const auto& nomBattu : nomsMaitresBattus) {
                            if (nomBattu == maitres[i]->getNom()) {
                                dejaBattu = true;
                                break;
                            }
                        }
                        
                        if (dejaBattu) {
                            std::cout << " ✅ [DÉJÀ BATTU]";
                        } else {
                            std::cout << " ⭐ [NOUVEAU DÉFI]";
                        }
                        std::cout << std::endl;
                    }
                    
                    std::cout << std::string(40, '-') << std::endl;
                    std::cout << "Choisissez un maître (1-" << maitres.size() << ", 0 pour aléatoire) : ";
                    int choixMaitre;
                    std::cin >> choixMaitre;
                    
                    Entraineur* maitre = nullptr;
                    if (choixMaitre == 0) {
                        // Sélection aléatoire
                        srand(static_cast<unsigned int>(time(0)));
                        int index = rand() % maitres.size();
                        maitre = maitres[index];
                        std::cout << "🎲 Sélection aléatoire : Maître " << maitre->getNom() << " !" << std::endl;
                    } else if (choixMaitre > 0 && choixMaitre <= static_cast<int>(maitres.size())) {
                        maitre = maitres[choixMaitre - 1];
                        std::cout << "⚔️ Vous avez choisi : Maître " << maitre->getNom() << " !" << std::endl;
                    } else {
                        std::cout << "Choix invalide." << std::endl;
                        waitForEnter();
                        break;
                    }
                    
                    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
                    
                    // Vérifier si déjà battu avant le combat
                    bool dejaBattuAvant = false;
                    for (const auto& nomBattu : nomsMaitresBattus) {
                        if (nomBattu == maitre->getNom()) {
                            dejaBattuAvant = true;
                            break;
                        }
                    }
                    
                    if (dejaBattuAvant) {
                        std::cout << "⚠️ Vous avez déjà battu ce maître auparavant." << std::endl;
                        std::cout << "Combat pour l'expérience..." << std::endl;
                    }
                    
                    int victoires_avant = joueur->getVictoires();
                    menuCombat(*joueur, *maitre);
                    
                    // Sauvegarder uniquement si c'est la première victoire
                    if (joueur->getVictoires() > victoires_avant && !dejaBattuAvant) {
                        Sauvegarde::sauvegarderMaitreBattu(*joueur, maitre);
                    }
                } else {
                    std::cout << "Aucun Maître Pokémon disponible." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 8:
                clearScreen();
                std::cout << R"(
██████╗░░█████╗░██████╗░████████╗██╗███████╗
██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔════╝
██████╔╝███████║██████╔╝░░░██║░░░██║█████╗░░
██╔═══╝░██╔══██║██╔══██╗░░░██║░░░██║██╔══╝░░
██║░░░░░██║░░██║██║░░██║░░░██║░░░██║███████╗
╚═╝░░░░░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝╚══════╝

░██████╗░█████╗░██╗░░░██╗██╗░░░██╗███████╗░██████╗░░█████╗░██████╗░██████╗░███████╗
██╔════╝██╔══██╗██║░░░██║██║░░░██║██╔════╝██╔════╝░██╔══██╗██╔══██╗██╔══██╗██╔════╝
╚█████╗░███████║██║░░░██║╚██╗░██╔╝█████╗░░██║░░██╗░███████║██████╔╝██║░░██║█████╗░░
░╚═══██╗██╔══██║██║░░░██║░╚████╔╝░██╔══╝░░██║░░╚██╗██╔══██║██╔══██╗██║░░██║██╔══╝░░
██████╔╝██║░░██║╚██████╔╝░░╚██╔╝░░███████╗╚██████╔╝██║░░██║██║░░██║██████╔╝███████╗
╚═════╝░╚═╝░░╚═╝░╚═════╝░░░░╚═╝░░░╚══════╝░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═════╝░╚══════╝
                )" << std::endl;
                std::cout << "Sauvegarde en cours..." << std::endl;
                Sauvegarde::sauvegarderPartie(*joueur);
                std::cout << "✅ Partie sauvegardée avec succès !" << std::endl;
                waitForEnter();
                break;
            default:
                std::cout << "Choix non valide, veuillez reessayer." << std::endl;
                waitForEnter();
            }
    }
}
void menuInteraction(Joueur& joueur, std::vector<Entraineur*>& leaders, std::vector<Entraineur*>& maitres) {
    bool retourMenu = false;
    
    while (!retourMenu) {
        clearScreen();
        std::cout << R"(
███╗░░░███╗███████╗███╗░░██╗██╗░░░██╗
████╗░████║██╔════╝████╗░██║██║░░░██║
██╔████╔██║█████╗░░██╔██╗██║██║░░░██║
██║╚██╔╝██║██╔══╝░░██║╚████║██║░░░██║
██║░╚═╝░██║███████╗██║░╚███║╚██████╔╝
╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░╚═════╝░

██████╗░██╗██╗███╗░░██╗████████╗███████╗██████╗░░█████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗
██╔══██╗╚█║██║████╗░██║╚══██╔══╝██╔════╝██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
██║░░██║░╚╝██║██╔██╗██║░░░██║░░░█████╗░░██████╔╝███████║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║
██║░░██║░░░██║██║╚████║░░░██║░░░██╔══╝░░██╔══██╗██╔══██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║
██████╔╝░░░██║██║░╚███║░░░██║░░░███████╗██║░░██║██║░░██║╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║
╚═════╝░░░░╚═╝╚═╝░░╚══╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝
        )" << std::endl;
        std::cout << "Avec qui voulez-vous interagir ?" << std::endl;
        std::cout << "1. 🐾 Avec un de vos Pokémon" << std::endl;
        std::cout << "2. 🏆 Avec un leader de gym vaincu" << std::endl;
        std::cout << "3. 🌟 Avec un maître Pokémon vaincu" << std::endl;
        std::cout << "4. 📜 Voir la liste des leaders battus" << std::endl;
        std::cout << "5. 📜 Voir la liste des maîtres battus" << std::endl;
        std::cout << "0. ◀️ Retour au menu principal" << std::endl;
        std::cout << "\nVotre choix : ";
        
        int choix;
        std::cin >> choix;
        
        switch (choix) {
            case 0: {
                retourMenu = true;
                break;
            }
            
            case 1: { // Interaction avec un Pokémon
                clearScreen();
                std::cout << R"(
██╗███╗░░██╗████████╗███████╗██████╗░░█████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗
██║████╗░██║╚══██╔══╝██╔════╝██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
██║██╔██╗██║░░░██║░░░█████╗░░██████╔╝███████║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║
██║██║╚████║░░░██║░░░██╔══╝░░██╔══██╗██╔══██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║
██║██║░╚███║░░░██║░░░███████╗██║░░██║██║░░██║╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║
╚═╝╚═╝░░╚══╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝

░█████╗░██╗░░░██╗███████╗░█████╗░  ██╗░░░██╗░█████╗░░██████╗
██╔══██╗██║░░░██║██╔════╝██╔══██╗  ██║░░░██║██╔══██╗██╔════╝
███████║╚██╗░██╔╝█████╗░░██║░░╚═╝  ╚██╗░██╔╝██║░░██║╚█████╗░
██╔══██║░╚████╔╝░██╔══╝░░██║░░██╗  ░╚████╔╝░██║░░██║░╚═══██╗
██║░░██║░░╚██╔╝░░███████╗╚█████╔╝  ░░╚██╔╝░░╚█████╔╝██████╔╝
╚═╝░░╚═╝░░░╚═╝░░░╚══════╝░╚════╝░  ░░░╚═╝░░░░╚════╝░╚═════╝░

██████╗░░█████╗░██╗░░██╗███████╗███╗░░░███╗░█████╗░███╗░░██╗░██████╗
██╔══██╗██╔══██╗██║░██╔╝██╔════╝████╗░████║██╔══██╗████╗░██║██╔════╝
██████╔╝██║░░██║█████═╝░█████╗░░██╔████╔██║██║░░██║██╔██╗██║╚█████╗░
██╔═══╝░██║░░██║██╔═██╗░██╔══╝░░██║╚██╔╝██║██║░░██║██║╚████║░╚═══██╗
██║░░░░░╚█████╔╝██║░╚██╗███████╗██║░╚═╝░██║╚█████╔╝██║░╚███║██████╔╝
╚═╝░░░░░░╚════╝░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░
                )" << std::endl;
                if (joueur.getTailleEquipe() == 0) {
                    std::cout << "Vous n'avez aucun Pokémon dans votre équipe." << std::endl;
                    waitForEnter();
                    break;
                }
                
                std::cout << "Choisissez un Pokémon avec lequel interagir :" << std::endl;
                std::cout << std::string(40, '-') << std::endl;
                
                // Afficher la liste des Pokémon
                for (int i = 0; i < joueur.getTailleEquipe(); ++i) {
                    Pokemon* pokemon = joueur.pokemonActif(i);
                    if (pokemon) {
                        std::cout << (i + 1) << ". " << pokemon->getNom() << " ["
                                  << pokemon->getType1();
                        if (!pokemon->getType2().empty()) {
                            std::cout << "/" << pokemon->getType2();
                        }
                        std::cout << "] ";
                        if (pokemon->estKo()) {
                            std::cout << "(K.O.)";
                        } else {
                            std::cout << "(" << pokemon->getHp() << "/" << pokemon->getMaxHp() << " HP)";
                        }
                        std::cout << std::endl;
                    }
                }
                
                std::cout << "\nChoisissez un Pokémon (1-" << joueur.getTailleEquipe() 
                          << ", 0 pour retour) : ";
                int choixPokemon;
                std::cin >> choixPokemon;
                
                if (choixPokemon > 0 && choixPokemon <= joueur.getTailleEquipe()) {
                    Pokemon* pokemon = joueur.pokemonActif(choixPokemon - 1);
                    if (pokemon) {
                        std::cout << "\n" << std::string(40, '=') << std::endl;
                        std::cout << "🗣️ " << pokemon->interaction() << std::endl;
                        std::cout << std::string(40, '=') << std::endl;
                    }
                }
                waitForEnter();
                break;
            }
            
            case 2: { // Interaction avec un leader de gym vaincu depuis fichier
                clearScreen();
                std::cout << R"(
██╗███╗░░██╗████████╗███████╗██████╗░░█████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗
██║████╗░██║╚══██╔══╝██╔════╝██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
██║██╔██╗██║░░░██║░░░█████╗░░██████╔╝███████║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║
██║██║╚████║░░░██║░░░██╔══╝░░██╔══██╗██╔══██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║
██║██║░╚███║░░░██║░░░███████╗██║░░██║██║░░██║╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║
╚═╝╚═╝░░╚══╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝

░█████╗░██╗░░░██╗███████╗░█████╗░  ██╗░░░░░███████╗░█████╗░██████╗░███████╗██████╗░░██████╗
██╔══██╗██║░░░██║██╔════╝██╔══██╗  ██║░░░░░██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝
███████║╚██╗░██╔╝█████╗░░██║░░╚═╝  ██║░░░░░█████╗░░███████║██║░░██║█████╗░░██████╔╝╚█████╗░
██╔══██║░╚████╔╝░██╔══╝░░██║░░██╗  ██║░░░░░██╔══╝░░██╔══██║██║░░██║██╔══╝░░██╔══██╗░╚═══██╗
██║░░██║░░╚██╔╝░░███████╗╚█████╔╝  ███████╗███████╗██║░░██║██████╔╝███████╗██║░░██║██████╔╝
╚═╝░░╚═╝░░░╚═╝░░░╚══════╝░╚════╝░  ╚══════╝╚══════╝╚═╝░░╚═╝╚═════╝░╚══════╝╚═╝░░╚═╝╚═════╝░

██╗░░░██╗░█████╗░██╗███╗░░██╗░█████╗░██╗░░░██╗░██████╗
██║░░░██║██╔══██╗██║████╗░██║██╔══██╗██║░░░██║██╔════╝
╚██╗░██╔╝███████║██║██╔██╗██║██║░░╚═╝██║░░░██║╚█████╗░
░╚████╔╝░██╔══██║██║██║╚████║██║░░██╗██║░░░██║░╚═══██╗
░░╚██╔╝░░██║░░██║██║██║░╚███║╚█████╔╝╚██████╔╝██████╔╝
░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚════╝░░╚═════╝░╚═════╝░
                )" << std::endl;
                
                // Obtenir les noms des leaders battus depuis le fichier
                std::vector<std::string> nomsLeadersBattus = Sauvegarde::extraireNomsLeadersBattus();
                
                if (nomsLeadersBattus.empty()) {
                    std::cout << "Vous n'avez vaincu aucun leader de gym." << std::endl;
                    waitForEnter();
                    break;
                }
                
                // Trouver les leaders correspondants dans la liste
                std::vector<LeaderGym*> leadersVaincus;
                for (const std::string& nomBattu : nomsLeadersBattus) {
                    for (Entraineur* entraineur : leaders) {
                        LeaderGym* leader = dynamic_cast<LeaderGym*>(entraineur);
                        if (leader && leader->getNom() == nomBattu) {
                            leadersVaincus.push_back(leader);
                            break;
                        }
                    }
                }
                
                std::cout << "Leaders de gym vaincus :" << std::endl;
                std::cout << std::string(40, '-') << std::endl;
                
                for (size_t i = 0; i < leadersVaincus.size(); ++i) {
                    std::cout << (i + 1) << ". " << leadersVaincus[i]->getNom()
                              << " (Arène de " << leadersVaincus[i]->getNomGym() << ")" << std::endl;
                }
                
                std::cout << "\nChoisissez un leader (1-" << leadersVaincus.size() 
                          << ", 0 pour retour) : ";
                int choixLeader;
                std::cin >> choixLeader;
                
                if (choixLeader > 0 && choixLeader <= static_cast<int>(leadersVaincus.size())) {
                    LeaderGym* leader = leadersVaincus[choixLeader - 1];
                    std::cout << "\n" << std::string(40, '=') << std::endl;
                    std::cout << "🗣️ " << leader->interaction() << std::endl;
                    std::cout << std::string(40, '=') << std::endl;
                }
                waitForEnter();
                break;
            }
            
            case 3: { 
                clearScreen();
                std::cout << R"(
██╗███╗░░██╗████████╗███████╗██████╗░░█████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗
██║████╗░██║╚══██╔══╝██╔════╝██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
██║██╔██╗██║░░░██║░░░█████╗░░██████╔╝███████║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║
██║██║╚████║░░░██║░░░██╔══╝░░██╔══██╗██╔══██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║
██║██║░╚███║░░░██║░░░███████╗██║░░██║██║░░██║╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║
╚═╝╚═╝░░╚══╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝

░█████╗░██╗░░░██╗███████╗░█████╗░  ███╗░░░███╗░█████╗░██╗████████╗██████╗░███████╗░██████╗
██╔══██╗██║░░░██║██╔════╝██╔══██╗  ████╗░████║██╔══██╗██║╚══██╔══╝██╔══██╗██╔════╝██╔════╝
███████║╚██╗░██╔╝█████╗░░██║░░╚═╝  ██╔████╔██║███████║██║░░░██║░░░██████╔╝█████╗░░╚█████╗░
██╔══██║░╚████╔╝░██╔══╝░░██║░░██╗  ██║╚██╔╝██║██╔══██║██║░░░██║░░░██╔══██╗██╔══╝░░░╚═══██╗
██║░░██║░░╚██╔╝░░███████╗╚█████╔╝  ██║░╚═╝░██║██║░░██║██║░░░██║░░░██║░░██║███████╗██████╔╝
╚═╝░░╚═╝░░░╚═╝░░░╚══════╝░╚════╝░  ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═════╝░

██╗░░░██╗░█████╗░██╗███╗░░██╗░█████╗░██╗░░░██╗░██████╗
██║░░░██║██╔══██╗██║████╗░██║██╔══██╗██║░░░██║██╔════╝
╚██╗░██╔╝███████║██║██╔██╗██║██║░░╚═╝██║░░░██║╚█████╗░
░╚████╔╝░██╔══██║██║██║╚████║██║░░██╗██║░░░██║░╚═══██╗
░░╚██╔╝░░██║░░██║██║██║░╚███║╚█████╔╝╚██████╔╝██████╔╝
░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚════╝░░╚═════╝░╚═════╝░
                )" << std::endl;
                std::vector<std::string> nomsMaitresBattus = Sauvegarde::extraireNomsMaitresBattus();
    
                if (nomsMaitresBattus.empty()) {
                std::cout << "Vous n'avez vaincu aucun maître Pokémon." << std::endl;
                waitForEnter();
                break;
            }
            std::cout << "Maîtres Pokémon vaincus :" << std::endl;
            std::cout << std::string(40, '-') << std::endl;
            for (size_t i = 0; i < nomsMaitresBattus.size(); ++i) {
                std::cout << (i + 1) << ". Maître " << nomsMaitresBattus[i] << std::endl;
            }
    
            std::cout << "\nChoisissez un maître (1-" << nomsMaitresBattus.size() << ", 0 pour retour) : ";
            int choixMaitre;
            std::cin >> choixMaitre;
    
            if (choixMaitre > 0 && choixMaitre <= static_cast<int>(nomsMaitresBattus.size())) {
            std::string nomMaitre = nomsMaitresBattus[choixMaitre - 1];
            MaitrePokemon* maitreTrouve = nullptr;
            for (Entraineur* entraineur : maitres) {
                MaitrePokemon* maitre = dynamic_cast<MaitrePokemon*>(entraineur);
                if (maitre && maitre->getNom() == nomMaitre) {
                    maitreTrouve = maitre;
                    break;
                }
            }
        
        if (maitreTrouve) {
            std::cout << "\n" << std::string(40, '=') << std::endl;
            std::cout << "🗣️ " << maitreTrouve->interaction() << std::endl;
            std::cout << std::string(40, '=') << std::endl;
        } else {
            // Si le maître n'est pas trouvé dans la liste, créer une interaction générique
            std::cout << "\n" << std::string(40, '=') << std::endl;
            std::cout << "🗣️ Maître " << nomMaitre << " dit : \"Félicitations, tu es digne de la Ligue Pokémon.\"" << std::endl;
            std::cout << std::string(40, '=') << std::endl;
        }
    }
    waitForEnter();
    break;
}
            
            case 4: { // Afficher la liste des leaders battus
                clearScreen();
                std::cout << R"(
██╗░░░░░███████╗░█████╗░██████╗░███████╗██████╗░  ██████╗░███████╗  ░██████╗░██╗░░░██╗███╗░░░███╗
██║░░░░░██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗  ██╔══██╗██╔════╝  ██╔════╝░╚██╗░██╔╝████╗░████║
██║░░░░░█████╗░░███████║██║░░██║█████╗░░██████╔╝  ██║░░██║█████╗░░  ██║░░██╗░░╚████╔╝░██╔████╔██║
██║░░░░░██╔══╝░░██╔══██║██║░░██║██╔══╝░░██╔══██╗  ██║░░██║██╔══╝░░  ██║░░╚██╗░░╚██╔╝░░██║╚██╔╝██║
███████╗███████╗██║░░██║██████╔╝███████╗██║░░██║  ██████╔╝███████╗  ╚██████╔╝░░░██║░░░██║░╚═╝░██║
╚══════╝╚══════╝╚═╝░░╚═╝╚═════╝░╚══════╝╚═╝░░╚═╝  ╚═════╝░╚══════╝  ░╚═════╝░░░░╚═╝░░░╚═╝░░░░░╚═╝

██████╗░░█████╗░████████╗████████╗██╗░░░██╗░██████╗
██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║░░░██║██╔════╝
██████╦╝███████║░░░██║░░░░░░██║░░░██║░░░██║╚█████╗░
██╔══██╗██╔══██║░░░██║░░░░░░██║░░░██║░░░██║░╚═══██╗
██████╦╝██║░░██║░░░██║░░░░░░██║░░░╚██████╔╝██████╔╝
╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░░░░╚═╝░░░░╚═════╝░╚═════╝░
                )" << std::endl;
                std::vector<std::string> leaders_battus = Sauvegarde::chargerLeadersBattus();
                if (leaders_battus.empty()) {
                    std::cout << "Aucun leader battu ou fichier introuvable." << std::endl;
                } else {
                    for (const auto& ligne : leaders_battus) {
                        std::cout << ligne << std::endl;
                    }
                }
                waitForEnter();
                break;
            }
            
            case 5: { // Afficher la liste des maîtres battus
                clearScreen();
                std::cout << R"(
███╗░░░███╗░█████╗░██╗████████╗██████╗░███████╗░██████╗  ██████╗░░█████╗░██╗░░██╗███████╗███╗░░░███╗░█████╗░███╗░░██╗
████╗░████║██╔══██╗██║╚══██╔══╝██╔══██╗██╔════╝██╔════╝  ██╔══██╗██╔══██╗██║░██╔╝██╔════╝████╗░████║██╔══██╗████╗░██║
██╔████╔██║███████║██║░░░██║░░░██████╔╝█████╗░░╚█████╗░  ██████╔╝██║░░██║█████═╝░█████╗░░██╔████╔██║██║░░██║██╔██╗██║
██║╚██╔╝██║██╔══██║██║░░░██║░░░██╔══██╗██╔══╝░░░╚═══██╗  ██╔═══╝░██║░░██║██╔═██╗░██╔══╝░░██║╚██╔╝██║██║░░██║██║╚████║
██║░╚═╝░██║██║░░██║██║░░░██║░░░██║░░██║███████╗██████╔╝  ██║░░░░░╚█████╔╝██║░╚██╗███████╗██║░╚═╝░██║╚█████╔╝██║░╚███║
╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═════╝░  ╚═╝░░░░░░╚════╝░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝

██████╗░░█████╗░████████╗████████╗██╗░░░██╗░██████╗
██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║░░░██║██╔════╝
██████╦╝███████║░░░██║░░░░░░██║░░░██║░░░██║╚█████╗░
██╔══██╗██╔══██║░░░██║░░░░░░██║░░░██║░░░██║░╚═══██╗
██████╦╝██║░░██║░░░██║░░░░░░██║░░░╚██████╔╝██████╔╝
╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░░░░╚═╝░░░░╚═════╝░╚═════╝░
                )" << std::endl;
                std::vector<std::string> maitres_battus = Sauvegarde::chargerMaitresBattus();
                if (maitres_battus.empty()) {
                    std::cout << "Aucun maître battu ou fichier introuvable." << std::endl;
                } else {
                    for (const auto& ligne : maitres_battus) {
                        std::cout << ligne << std::endl;
                    }
                }
                waitForEnter();
                break;
            }
            
            default: {
                std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
                waitForEnter();
                break;
            }
        }
    }
}
void menuCombat(Joueur& joueur, Entraineur& adversaire) {
    clearScreen();
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    std::cout << "|              COMBAT !                |" << std::endl;
    std::cout << "+" << std::string(38, '=') << "+" << std::endl;
    std::cout << "Un adversaire approche..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\n" << adversaire.getNom() << " envoie " << adversaire.pokemonActif()->getNom()<< " ! Préparez-vous !" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    std::cout << "\nVous envoyez : " << joueur.pokemonActif()->getNom() << " !" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\nLe combat commence ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    demarrerCombat(joueur, adversaire);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}
void menuGestionEntraineur(Joueur*& joueur, std::vector<Pokemon*>& cataloguePokemon) {
    bool retourMenu = false;
    while (!retourMenu) {
        clearScreen();
        std::cout << R"(
░██████╗░███████╗░██████╗████████╗██╗░█████╗░███╗░░██╗  ██████╗░███████╗
██╔════╝░██╔════╝██╔════╝╚══██╔══╝██║██╔══██╗████╗░██║  ██╔══██╗██╔════╝
██║░░██╗░█████╗░░╚█████╗░░░░██║░░░██║██║░░██║██╔██╗██║  ██║░░██║█████╗░░
██║░░╚██╗██╔══╝░░░╚═══██╗░░░██║░░░██║██║░░██║██║╚████║  ██║░░██║██╔══╝░░
╚██████╔╝███████╗██████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║  ██████╔╝███████╗
░╚═════╝░╚══════╝╚═════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝  ╚═════╝░╚══════╝

██╗░░░░░██╗███████╗███╗░░██╗████████╗██████╗░░█████╗░██╗███╗░░██╗███████╗██╗░░░██╗██████╗░
██║░░░░░╚█║██╔════╝████╗░██║╚══██╔══╝██╔══██╗██╔══██╗██║████╗░██║██╔════╝██║░░░██║██╔══██╗
██║░░░░░░╚╝█████╗░░██╔██╗██║░░░██║░░░██████╔╝███████║██║██╔██╗██║█████╗░░██║░░░██║██████╔╝
██║░░░░░░░░██╔══╝░░██║╚████║░░░██║░░░██╔══██╗██╔══██║██║██║╚████║██╔══╝░░██║░░░██║██╔══██╗
███████╗░░░███████╗██║░╚███║░░░██║░░░██║░░██║██║░░██║██║██║░╚███║███████╗╚██████╔╝██║░░██║
╚══════╝░░░╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝╚══════╝░╚═════╝░╚═╝░░╚═╝
        )" << std::endl;
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
                clearScreen();
                std::cout << R"(
███╗░░░███╗░█████╗░██████╗░██╗███████╗██╗░█████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗  ██████╗░███████╗
████╗░████║██╔══██╗██╔══██╗██║██╔════╝██║██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║  ██╔══██╗██╔════╝
██╔████╔██║██║░░██║██║░░██║██║█████╗░░██║██║░░╚═╝███████║░░░██║░░░██║██║░░██║██╔██╗██║  ██║░░██║█████╗░░
██║╚██╔╝██║██║░░██║██║░░██║██║██╔══╝░░██║██║░░██╗██╔══██║░░░██║░░░██║██║░░██║██║╚████║  ██║░░██║██╔══╝░░
██║░╚═╝░██║╚█████╔╝██████╔╝██║██║░░░░░██║╚█████╔╝██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║  ██████╔╝███████╗
╚═╝░░░░░╚═╝░╚════╝░╚═════╝░╚═╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝  ╚═════╝░╚══════╝

██╗░░░░░██╗░█████╗░██████╗░██████╗░██████╗░███████╗
██║░░░░░╚█║██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔════╝
██║░░░░░░╚╝██║░░██║██████╔╝██║░░██║██████╔╝█████╗░░
██║░░░░░░░░██║░░██║██╔══██╗██║░░██║██╔══██╗██╔══╝░░
███████╗░░░╚█████╔╝██║░░██║██████╔╝██║░░██║███████╗
╚══════╝░░░░╚════╝░╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝
                )" << std::endl;
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
                clearScreen();
                std::cout << R"(
░█████╗░██╗░░██╗░█████╗░██╗██╗░░██╗  ██████╗░██╗██╗░░░██╗███╗░░██╗
██╔══██╗██║░░██║██╔══██╗██║╚██╗██╔╝  ██╔══██╗╚█║██║░░░██║████╗░██║
██║░░╚═╝███████║██║░░██║██║░╚███╔╝░  ██║░░██║░╚╝██║░░░██║██╔██╗██║
██║░░██╗██╔══██║██║░░██║██║░██╔██╗░  ██║░░██║░░░██║░░░██║██║╚████║
╚█████╔╝██║░░██║╚█████╔╝██║██╔╝╚██╗  ██████╔╝░░░╚██████╔╝██║░╚███║
░╚════╝░╚═╝░░╚═╝░╚════╝░╚═╝╚═╝░░╚═╝  ╚═════╝░░░░░╚═════╝░╚═╝░░╚══╝

███████╗███╗░░██╗████████╗██████╗░░█████╗░██╗███╗░░██╗███████╗██╗░░░██╗██████╗░
██╔════╝████╗░██║╚══██╔══╝██╔══██╗██╔══██╗██║████╗░██║██╔════╝██║░░░██║██╔══██╗
█████╗░░██╔██╗██║░░░██║░░░██████╔╝███████║██║██╔██╗██║█████╗░░██║░░░██║██████╔╝
██╔══╝░░██║╚████║░░░██║░░░██╔══██╗██╔══██║██║██║╚████║██╔══╝░░██║░░░██║██╔══██╗
███████╗██║░╚███║░░░██║░░░██║░░██║██║░░██║██║██║░╚███║███████╗╚██████╔╝██║░░██║
╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝╚══════╝░╚═════╝░╚═╝░░╚═╝
                )" << std::endl;
                std::vector<std::string> nomsEntraineurs;
                std::ifstream fichier("joueur.csv");
                std::string ligne;
                std::getline(fichier, ligne);
                int index = 1;
                while (std::getline(fichier, ligne)) {
                    std::stringstream ss(ligne);
                    std::string nom;
                    std::getline(ss, nom, ',');
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
                clearScreen();
                std::cout << R"(
░█████╗░██████╗░███████╗░█████╗░████████╗██╗░█████╗░███╗░░██╗  ██████╗░██╗██╗░░░██╗███╗░░██╗
██╔══██╗██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║  ██╔══██╗╚█║██║░░░██║████╗░██║
██║░░╚═╝██████╔╝█████╗░░███████║░░░██║░░░██║██║░░██║██╔██╗██║  ██║░░██║░╚╝██║░░░██║██╔██╗██║
██║░░██╗██╔══██╗██╔══╝░░██╔══██║░░░██║░░░██║██║░░██║██║╚████║  ██║░░██║░░░██║░░░██║██║╚████║
╚█████╔╝██║░░██║███████╗██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║  ██████╔╝░░░╚██████╔╝██║░╚███║
░╚════╝░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝  ╚═════╝░░░░░╚═════╝░╚═╝░░╚══╝

███████╗███╗░░██╗████████╗██████╗░░█████╗░██╗███╗░░██╗███████╗██╗░░░██╗██████╗░
██╔════╝████╗░██║╚══██╔══╝██╔══██╗██╔══██╗██║████╗░██║██╔════╝██║░░░██║██╔══██╗
█████╗░░██╔██╗██║░░░██║░░░██████╔╝███████║██║██╔██╗██║█████╗░░██║░░░██║██████╔╝
██╔══╝░░██║╚████║░░░██║░░░██╔══██╗██╔══██║██║██║╚████║██╔══╝░░██║░░░██║██╔══██╗
███████╗██║░╚███║░░░██║░░░██║░░██║██║░░██║██║██║░╚███║███████╗╚██████╔╝██║░░██║
╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝╚══════╝░╚═════╝░╚═╝░░╚═╝
                )" << std::endl;
                std::string nouveauNom;
                std::cout << "Entrez le nom du nouvel entraîneur : ";
                std::cin.ignore();
                std::getline(std::cin, nouveauNom);
                Joueur* nouvelEntraineur = new Joueur(nouveauNom);
                std::cout << "\nCatalogue des Pokémon disponibles :" << std::endl;
                std::cout << "--------------------------------------" << std::endl;
                for (size_t i = 0; i < cataloguePokemon.size(); ++i) {
                    std::cout << (i + 1) << ". " << cataloguePokemon[i]->getNom() << " [" << cataloguePokemon[i]->getType1();
                    if (!cataloguePokemon[i]->getType2().empty()) {
                        std::cout << "/" << cataloguePokemon[i]->getType2();
                    }
                    std::cout << "]" << std::endl;
                }
                std::cout << "\nSélectionnez jusqu'à 6 Pokémon par leur numéro Pokédex (0 pour terminer) :" << std::endl;
                for (int i = 0; i < 6; ++i) {
                    std::cout << "Pokémon " << (i + 1) << " (0 pour terminer) : ";
                    int numPokedex;
                    std::cin >> numPokedex;
                    if (numPokedex == 0) break;
                    if (numPokedex > 0 && numPokedex <= static_cast<int>(cataloguePokemon.size())) {
                        Pokemon* pokemon = cataloguePokemon[numPokedex - 1];
                        Pokemon* copie = nullptr;
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
                            copie = new Pokemon(pokemon->getNom(), pokemon->getType1(), 
                                            pokemon->getType2(), pokemon->getMaxHp(), 
                                            pokemon->getAttaque(), pokemon->getPuissance());
                        }
                        nouvelEntraineur->ajouterPokemon(copie);
                        std::cout << "✅ " << pokemon->getNom() << " ajouté à l'équipe." << std::endl;
                    } else {
                        std::cout << "❌ Numéro invalide. Veuillez choisir entre 1 et " 
                                  << cataloguePokemon.size() << "." << std::endl;
                        --i;
                    }
                }
                if (nouvelEntraineur->getTailleEquipe() == 0) {
                    std::cout << "\nL'équipe doit contenir au moins un Pokémon. Création annulée." << std::endl;
                    delete nouvelEntraineur;
                } else {
                    delete joueur;
                    joueur = nouvelEntraineur;
                    std::cout << "\nNouvel entraîneur créé avec succès !" << std::endl;
                    std::cout << "Composition de l'équipe :" << std::endl;
                    joueur->afficherEquipe();
                    std::cout << "\nVoulez-vous sauvegarder ce nouvel entraîneur dans le fichier joueur.csv ? (1: Oui, 0: Non) : ";
                    int sauvegarder;
                    std::cin >> sauvegarder;
                    if (sauvegarder == 1) {
                        std::ofstream fichier("joueur.csv", std::ios::app);
                        if (fichier.is_open()) {
                            fichier << joueur->getNom();
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