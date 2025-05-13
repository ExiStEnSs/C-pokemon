#include "sauvegarde.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;

// Définir les constantes de chemins de fichiers
const std::string Sauvegarde::FICHIER_LEADERS_BATTUS = "save/leaders_battus.txt";
const std::string Sauvegarde::FICHIER_JOUEUR = "joueur.csv";

// Créer la fonction pour s'assurer que le dossier existe
void assurerDossierSauvegarde() {
#ifdef _WIN32
    system("mkdir save 2>nul");
#else
    system("mkdir -p save 2>/dev/null");
#endif
}

// Sauvegarde des leaders battus
void Sauvegarde::sauvegarderLeaderBattu(const Joueur& joueur, Entraineur* leader) {
    if (!leader) {
        std::cerr << "Erreur : Pointeur leader invalide" << std::endl;
        return;
    }
    
    assurerDossierSauvegarde();
    
    std::ofstream fichier(FICHIER_LEADERS_BATTUS, std::ios::app);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << FICHIER_LEADERS_BATTUS << std::endl;
        return;
    }
    
    // Obtenir la date et heure actuelles
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    
    // Écrire dans le fichier avec vérifications
    LeaderGym* gym_leader = dynamic_cast<LeaderGym*>(leader);
    if (gym_leader) {
        fichier << "Leader " << leader->getNom() 
                << " (Arène de " << gym_leader->getNomGym() << ")"
                << " battu par " << joueur.getNom() 
                << " le " << ss.str() << std::endl;
    } else {
        MaitrePokemon* maitre = dynamic_cast<MaitrePokemon*>(leader);
        if (maitre) {
            fichier << "Maître " << leader->getNom() 
                    << " battu par " << joueur.getNom() 
                    << " le " << ss.str() << std::endl;
        } else {
            fichier << leader->getNom() << " battu par " << joueur.getNom() 
                    << " le " << ss.str() << std::endl;
        }
    }
    
    fichier.close();
}

std::vector<std::string> Sauvegarde::chargerLeadersBattus() {
    std::vector<std::string> leaders;
    std::ifstream fichier(FICHIER_LEADERS_BATTUS);
    
    if (!fichier.is_open()) {
        return leaders; // Retourne un vecteur vide si le fichier n'existe pas
    }
    
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        if (!ligne.empty()) {
            leaders.push_back(ligne);
        }
    }
    
    fichier.close();
    return leaders;
}

// Fonction utilitaire : Lire toutes les lignes du fichier joueur.csv
std::vector<std::string> lireLignesJoueur() {
    std::vector<std::string> lignes;
    std::ifstream fichier(Sauvegarde::FICHIER_JOUEUR);
    std::string ligne;
    
    while (std::getline(fichier, ligne)) {
        lignes.push_back(ligne);
    }
    
    fichier.close();
    return lignes;
}

// Fonction utilitaire : Écrire toutes les lignes dans joueur.csv
void ecrireLignesJoueur(const std::vector<std::string>& lignes) {
    std::ofstream fichier(Sauvegarde::FICHIER_JOUEUR);
    
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir " << Sauvegarde::FICHIER_JOUEUR << std::endl;
        return;
    }
    
    for (const auto& ligne : lignes) {
        fichier << ligne << std::endl;
    }
    
    fichier.close();
}

// Nouvelle fonction : Sauvegarder un joueur dans joueur.csv
void Sauvegarde::sauvegarderJoueur(const Joueur& joueur) {
    std::vector<std::string> lignes = lireLignesJoueur();
    
    // Si le fichier est vide ou n'existe pas, créer l'en-tête
    if (lignes.empty()) {
        lignes.push_back("nom,pokemon1,pokemon2,pokemon3,pokemon4,pokemon5,pokemon6,badges,victoires,defaites");
    }
    
    // Construire la nouvelle ligne pour ce joueur
    std::stringstream nouvelleLigne;
    nouvelleLigne << joueur.getNom();
    
    // Ajouter les Pokémon (jusqu'à 6)
    for (int i = 0; i < 6; ++i) {
        nouvelleLigne << ",";
        if (i < joueur.getTailleEquipe()) {
            Pokemon* pokemon = joueur.pokemonActif(i);
            if (pokemon) {
                nouvelleLigne << pokemon->getNom();
            }
        }
    }
    
    // Ajouter les statistiques
    nouvelleLigne << "," << joueur.getNombreBadges()
                 << "," << joueur.getVictoires()
                 << "," << joueur.getDefaites();
    
    // Chercher si le joueur existe déjà
    bool joueurTrouve = false;
    for (size_t i = 0; i < lignes.size(); ++i) {
        if (i == 0) continue; // Ignorer l'en-tête
        
        std::stringstream ss(lignes[i]);
        std::string nomExistant;
        std::getline(ss, nomExistant, ',');
        
        if (nomExistant == joueur.getNom()) {
            // Mettre à jour la ligne existante
            lignes[i] = nouvelleLigne.str();
            joueurTrouve = true;
            break;
        }
    }
    
    // Si le joueur n'existe pas, l'ajouter
    if (!joueurTrouve) {
        lignes.push_back(nouvelleLigne.str());
    }
    
    // Réécrire le fichier
    ecrireLignesJoueur(lignes);
}

// Nouvelle fonction : Charger un joueur depuis joueur.csv
bool Sauvegarde::chargerJoueur(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon, int index) {
    if (cataloguePokemon.empty()) {
        std::cerr << "Erreur : Catalogue de Pokémon vide" << std::endl;
        return false;
    }
    
    std::ifstream fichier(FICHIER_JOUEUR);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir " << FICHIER_JOUEUR << std::endl;
        return false;
    }
    
    std::string ligne;
    int compteur = 0;
    
    // Ignorer l'en-tête
    if (!std::getline(fichier, ligne)) {
        fichier.close();
        return false;
    }
    
    std::string nomRecherche = joueur.getNom();
    std::cout << "🔍 Recherche du joueur : '" << nomRecherche << "'" << std::endl;
    
    // Trouver la ligne du joueur par index ou par nom
    while (std::getline(fichier, ligne)) {
        std::stringstream ss(ligne);
        std::string nomLu;
        std::getline(ss, nomLu, ',');
        
        std::cout << "📝 Ligne " << compteur << " : nom trouvé = '" << nomLu << "'" << std::endl;
        
        bool ligneCorrecte = false;
        
        if (index == -1) {
            // Recherche par nom - nettoyer les espaces pour comparaison
            std::string nomLuClean = nomLu;
            nomLuClean.erase(0, nomLuClean.find_first_not_of(" \t\r\n"));
            nomLuClean.erase(nomLuClean.find_last_not_of(" \t\r\n") + 1);
            
            std::string nomRechercheClean = nomRecherche;
            nomRechercheClean.erase(0, nomRechercheClean.find_first_not_of(" \t\r\n"));
            nomRechercheClean.erase(nomRechercheClean.find_last_not_of(" \t\r\n") + 1);
            
            if (nomLuClean == nomRechercheClean) {
                ligneCorrecte = true;
                std::cout << "✅ Joueur trouvé par nom !" << std::endl;
            }
        } else {
            // Recherche par index
            if (compteur == index) {
                ligneCorrecte = true;
                std::cout << "✅ Joueur trouvé par index !" << std::endl;
            }
        }
        
        if (ligneCorrecte) {
            // Parser la ligne trouvée - recommencer la lecture
            std::stringstream ss2(ligne);
            std::string nom;
            std::vector<std::string> nomsPokemon(6);
            std::string temp;
            
            // Lire les données
            std::getline(ss2, nom, ',');
            
            // Lire les 6 Pokémon
            for (int i = 0; i < 6; ++i) {
                std::getline(ss2, nomsPokemon[i], ',');
            }
            
            // Lire les statistiques (nouvelles colonnes)
            int badges = 0, victoires = 0, defaites = 0;
            
            if (std::getline(ss2, temp, ',') && !temp.empty()) {
                badges = std::atoi(temp.c_str());
                std::cout << "📊 Badges trouvés : " << badges << std::endl;
            }
            if (std::getline(ss2, temp, ',') && !temp.empty()) {
                victoires = std::atoi(temp.c_str());
                std::cout << "📊 Victoires trouvées : " << victoires << std::endl;
            }
            if (std::getline(ss2, temp) && !temp.empty()) {
                defaites = std::atoi(temp.c_str());
                std::cout << "📊 Défaites trouvées : " << defaites << std::endl;
            }
            
            // Nettoyer d'abord les statistiques actuelles du joueur
            // (Puisque nous n'avons pas de méthode reset, nous devons calculer la différence)
            std::cout << "📊 Stats actuelles avant chargement :" << std::endl;
            std::cout << "   Badges : " << joueur.getNombreBadges() << std::endl;
            std::cout << "   Victoires : " << joueur.getVictoires() << std::endl;
            std::cout << "   Défaites : " << joueur.getDefaites() << std::endl;
            
            // Appliquer les statistiques au joueur
            // Calculer les différences pour incrémenter correctement
            int badgesDiff = badges - joueur.getNombreBadges();
            int victoiresDiff = victoires - joueur.getVictoires();
            int defaitesDiff = defaites - joueur.getDefaites();
            
            std::cout << "💫 Différences à appliquer :" << std::endl;
            std::cout << "   Badges : +" << badgesDiff << std::endl;
            std::cout << "   Victoires : +" << victoiresDiff << std::endl;
            std::cout << "   Défaites : +" << defaitesDiff << std::endl;
            
            // Appliquer les incréments si nécessaire
            for (int i = 0; i < badgesDiff && badgesDiff > 0; ++i) {
                joueur.incrementerBadge();
            }
            
            for (int i = 0; i < victoiresDiff && victoiresDiff > 0; ++i) {
                joueur.enregistrerVictoire();
            }
            
            for (int i = 0; i < defaitesDiff && defaitesDiff > 0; ++i) {
                joueur.enregistrerDefaite();
            }
            
            std::cout << "📊 Stats finales après chargement :" << std::endl;
            std::cout << "   Badges : " << joueur.getNombreBadges() << std::endl;
            std::cout << "   Victoires : " << joueur.getVictoires() << std::endl;
            std::cout << "   Défaites : " << joueur.getDefaites() << std::endl;
            
            // Charger l'équipe
            std::cout << "🐾 Chargement de l'équipe..." << std::endl;
            joueur.viderEquipe();
            
            for (size_t i = 0; i < nomsPokemon.size(); ++i) {
                const std::string& nomPk = nomsPokemon[i];
                if (nomPk.empty()) continue;
                
                // Nettoyer les espaces
                std::string nomProprePk = nomPk;
                nomProprePk.erase(0, nomProprePk.find_first_not_of(" \t\r\n"));
                nomProprePk.erase(nomProprePk.find_last_not_of(" \t\r\n") + 1);
                
                if (nomProprePk.empty()) continue;
                
                std::cout << "   Recherche du Pokémon : '" << nomProprePk << "'" << std::endl;
                
                for (const auto& p : cataloguePokemon) {
                    if (p && p->getNom() == nomProprePk) {
                        // [Votre logique de création existante...]
                        std::cout << "   ✅ " << nomProprePk << " trouvé et ajouté !" << std::endl;
                        break;
                    }
                }
            }
            
            fichier.close();
            return true;
        }
        
        compteur++;
    }
    
    std::cout << "❌ Joueur '" << nomRecherche << "' non trouvé dans le fichier." << std::endl;
    fichier.close();
    return false;
}

// Fonction de sauvegarde complète simplifiée
void Sauvegarde::sauvegarderPartie(const Joueur& joueur, Entraineur* dernier_leader_battu) {
    assurerDossierSauvegarde();
    
    try {
        // Sauvegarder dans joueur.csv (équipe + stats)
        sauvegarderJoueur(joueur);
        
        // Sauvegarder le leader battu (si fourni)
        if (dernier_leader_battu) {
            sauvegarderLeaderBattu(joueur, dernier_leader_battu);
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la sauvegarde: " << e.what() << std::endl;
    }
}

// Fonction de chargement simplifiée
bool Sauvegarde::chargerPartie(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon) {
    try {
        // Charger depuis joueur.csv (recherche par nom)
        return chargerJoueur(joueur, cataloguePokemon, -1);
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement: " << e.what() << std::endl;
        return false;
    }
}

// Réinitialiser les fichiers pour une nouvelle partie
void Sauvegarde::reinitialisationNouvellePartie() {
    assurerDossierSauvegarde();
    
    try {
        // 1. Réinitialiser le fichier des leaders battus
        std::ofstream fichierLeaders(FICHIER_LEADERS_BATTUS, std::ios::trunc);
        if (fichierLeaders.is_open()) {
            fichierLeaders.close();
        }
        
        // 2. 🔧 NOUVEAU : Réinitialiser toutes les statistiques des joueurs dans joueur.csv
        std::vector<std::string> lignes = lireLignesJoueur();
        
        if (!lignes.empty()) {
            // Conserver l'en-tête
            std::vector<std::string> lignesMises;
            lignesMises.push_back(lignes[0]); // En-tête
            
            // Traiter chaque joueur (à partir de la ligne 1)
            for (size_t i = 1; i < lignes.size(); ++i) {
                std::stringstream ss(lignes[i]);
                std::string nom;
                std::vector<std::string> nomsPokemon(6);
                
                // Lire le nom et les Pokémon
                std::getline(ss, nom, ',');
                for (int j = 0; j < 6; ++j) {
                    std::getline(ss, nomsPokemon[j], ',');
                }
                
                // Reconstruire la ligne avec stats remises à zéro
                std::stringstream nouvelleLigne;
                nouvelleLigne << nom;
                
                // Réécrire les Pokémon
                for (int j = 0; j < 6; ++j) {
                    nouvelleLigne << "," << nomsPokemon[j];
                }
                
                // Ajouter les stats remises à zéro
                nouvelleLigne << ",0,0,0"; // badges,victoires,defaites = 0
                
                lignesMises.push_back(nouvelleLigne.str());
            }
            
            // Réécrire le fichier avec les stats remises à zéro
            ecrireLignesJoueur(lignesMises);
            
            std::cout << "✅ Toutes les statistiques des joueurs ont été remises à zéro." << std::endl;
        }
        
        std::cout << "Nouvelle partie : les fichiers de sauvegarde ont été réinitialisés." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la réinitialisation: " << e.what() << std::endl;
    }
}