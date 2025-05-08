#include "sauvegarde.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <algorithm>

// Définir les constantes de chemins de fichiers
const std::string Sauvegarde::FICHIER_LEADERS_BATTUS = "save/leaders_battus.txt";
const std::string Sauvegarde::FICHIER_STATS_JOUEUR = "save/stats_joueur.csv";
const std::string Sauvegarde::FICHIER_EQUIPE_JOUEUR = "save/equipe_joueur.csv";

// Créer la fonction pour s'assurer que le dossier existe
void assurerDossierSauvegarde() {
    system("mkdir save 2>nul");  // Sur Windows, crée le dossier s'il n'existe pas déjà
}

// Sauvegarde des leaders battus
void Sauvegarde::sauvegarderLeaderBattu(const Joueur& joueur, Entraineur* leader) {
    assurerDossierSauvegarde();
    
    std::ofstream fichier(FICHIER_LEADERS_BATTUS, std::ios::app);
    if (!fichier) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << FICHIER_LEADERS_BATTUS << std::endl;
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

std::vector<std::string> Sauvegarde::chargerLeadersBattus() {
    std::vector<std::string> leaders;
    std::ifstream fichier(FICHIER_LEADERS_BATTUS);
    
    if (!fichier) {
        return leaders; // Retourne un vecteur vide si le fichier n'existe pas
    }
    
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        leaders.push_back(ligne);
    }
    
    fichier.close();
    return leaders;
}

// Sauvegarde des statistiques du joueur
void Sauvegarde::sauvegarderStatsJoueur(const Joueur& joueur) {
    assurerDossierSauvegarde();
    
    std::ofstream fichier(FICHIER_STATS_JOUEUR);
    if (!fichier) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << FICHIER_STATS_JOUEUR << std::endl;
        return;
    }
    
    // En-tête CSV
    fichier << "nom,badges,victoires,defaites" << std::endl;
    
    // Données du joueur
    fichier << joueur.getNom() << ","
            << joueur.getNombreBadges() << ","
            << joueur.getVictoires() << ","
            << joueur.getDefaites() << std::endl;
    
    fichier.close();
}

bool Sauvegarde::chargerStatsJoueur(Joueur& joueur) {
    std::ifstream fichier(FICHIER_STATS_JOUEUR);
    if (!fichier) {
        return false; // Fichier introuvable
    }
    
    std::string ligne, entete;
    std::getline(fichier, entete); // Ignorer l'en-tête
    
    if (std::getline(fichier, ligne)) {
        std::stringstream ss(ligne);
        std::string nom;
        int badges, victoires, defaites;
        
        std::getline(ss, nom, ',');
        ss >> badges;
        ss.ignore();
        ss >> victoires;
        ss.ignore();
        ss >> defaites;
        
        // Mettre à jour les statistiques du joueur
        // Réinitialiser d'abord les compteurs
        // Puis ajouter les valeurs chargées
        
        // Badges
        while (joueur.getNombreBadges() < badges) {
            joueur.incrementerBadge();
        }
        
        // Victoires et défaites
        while (joueur.getVictoires() < victoires) {
            joueur.enregistrerVictoire();
        }
        
        while (joueur.getDefaites() < defaites) {
            joueur.enregistrerDefaite();
        }
        
        fichier.close();
        return true;
    }
    
    fichier.close();
    return false;
}

// Sauvegarde de l'équipe du joueur
void Sauvegarde::sauvegarderEquipeJoueur(const Joueur& joueur) {
    assurerDossierSauvegarde();
    
    std::ofstream fichier(FICHIER_EQUIPE_JOUEUR);
    if (!fichier) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << FICHIER_EQUIPE_JOUEUR << std::endl;
        return;
    }
    
    // En-tête CSV
    fichier << "pokemon1,pokemon2,pokemon3,pokemon4,pokemon5,pokemon6" << std::endl;
    
    // Données de l'équipe
    for (int i = 0; i < 6; ++i) {
        Pokemon* pokemon = (i < joueur.getTailleEquipe()) ? joueur.pokemonActif(i) : nullptr;
        if (pokemon) {
            fichier << pokemon->getNom();
        }
        
        if (i < 5) {
            fichier << ",";
        }
    }
    
    fichier << std::endl;
    fichier.close();
}

bool Sauvegarde::chargerEquipeJoueur(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon) {
    std::ifstream fichier(FICHIER_EQUIPE_JOUEUR);
    if (!fichier) {
        return false; // Fichier introuvable
    }
    
    std::string ligne, entete;
    std::getline(fichier, entete); // Ignorer l'en-tête
    
    if (std::getline(fichier, ligne)) {
        std::stringstream ss(ligne);
        std::vector<std::string> nomsPokemon;
        std::string nom;
        
        // Lire les noms des Pokémon
        while (std::getline(ss, nom, ',')) {
            nomsPokemon.push_back(nom);
        }
        
        // Vider l'équipe actuelle
        joueur.viderEquipe();
        
        // Ajouter les nouveaux Pokémon
        for (const auto& nomPk : nomsPokemon) {
            if (!nomPk.empty()) {
                for (const auto& p : cataloguePokemon) {
                    if (p->getNom() == nomPk) {
                        joueur.ajouterPokemon(new Pokemon(*p));
                        break;
                    }
                }
            }
        }
        
        fichier.close();
        return true;
    }
    
    fichier.close();
    return false;
}

// Sauvegarde complète
void Sauvegarde::sauvegarderPartie(const Joueur& joueur, Entraineur* dernier_leader_battu) {
    assurerDossierSauvegarde();
    
    // Sauvegarder les statistiques
    sauvegarderStatsJoueur(joueur);
    
    // Sauvegarder l'équipe
    sauvegarderEquipeJoueur(joueur);
    
    // Sauvegarder le leader battu (si fourni)
    if (dernier_leader_battu) {
        sauvegarderLeaderBattu(joueur, dernier_leader_battu);
    }
    
    std::cout << "✅ Partie sauvegardée avec succès !" << std::endl;
}

bool Sauvegarde::chargerPartie(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon) {
    bool statsChargees = chargerStatsJoueur(joueur);
    bool equipeChargee = chargerEquipeJoueur(joueur, cataloguePokemon);
    
    return statsChargees && equipeChargee;
}

// Réinitialiser les fichiers de sauvegarde pour une nouvelle partie
void Sauvegarde::reinitialisationNouvellePartie() {
    assurerDossierSauvegarde();
    
    // Réinitialiser le fichier des leaders battus
    std::ofstream fichierLeaders(FICHIER_LEADERS_BATTUS, std::ios::trunc);
    if (fichierLeaders) {
        fichierLeaders.close();
    }
    
    // Réinitialiser les statistiques du joueur
    std::ofstream fichierStats(FICHIER_STATS_JOUEUR, std::ios::trunc);
    if (fichierStats) {
        fichierStats << "nom,badges,victoires,defaites" << std::endl;
        fichierStats.close();
    }
    
    // Réinitialiser l'équipe du joueur
    std::ofstream fichierEquipe(FICHIER_EQUIPE_JOUEUR, std::ios::trunc);
    if (fichierEquipe) {
        fichierEquipe << "pokemon1,pokemon2,pokemon3,pokemon4,pokemon5,pokemon6" << std::endl;
        fichierEquipe.close();
    }
    
    std::cout << "Nouvelle partie : les fichiers de sauvegarde ont été réinitialisés." << std::endl;
}