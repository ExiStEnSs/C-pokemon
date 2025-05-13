#ifndef SAUVEGARDE_HPP
#define SAUVEGARDE_HPP

#include "entraineur.hpp"
#include "pokemon.hpp"
#include <string>
#include <vector>
#include <fstream>

class Sauvegarde {
private:
    static const std::string FICHIER_LEADERS_BATTUS;

public:
    // 🔧 Déplacer FICHIER_JOUEUR vers public pour pouvoir y accéder
    static const std::string FICHIER_JOUEUR;
    
    // Sauvegarde des leaders battus
    static void sauvegarderLeaderBattu(const Joueur& joueur, Entraineur* leader);
    static std::vector<std::string> chargerLeadersBattus();
    
    // Sauvegarde complète du joueur (équipe + stats dans joueur.csv)
    static void sauvegarderJoueur(const Joueur& joueur);
    static bool chargerJoueur(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon, int index = 0);
    
    // Utilitaires
    static void sauvegarderPartie(const Joueur& joueur, Entraineur* dernier_leader_battu = nullptr);
    static bool chargerPartie(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon);
    static void reinitialisationNouvellePartie();
};

#endif