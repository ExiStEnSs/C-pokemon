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
    static const std::string FICHIER_STATS_JOUEUR;
    static const std::string FICHIER_EQUIPE_JOUEUR;

public:
    // Sauvegarde des leaders battus
    static void sauvegarderLeaderBattu(const Joueur& joueur, Entraineur* leader);
    static std::vector<std::string> chargerLeadersBattus();
    
    // Sauvegarde des statistiques du joueur
    static void sauvegarderStatsJoueur(const Joueur& joueur);
    static bool chargerStatsJoueur(Joueur& joueur);
    
    // Sauvegarde de l'équipe du joueur
    static void sauvegarderEquipeJoueur(const Joueur& joueur);
    static bool chargerEquipeJoueur(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon);
    
    // Sauvegarde complète (tout-en-un)
    static void sauvegarderPartie(const Joueur& joueur, Entraineur* dernier_leader_battu = nullptr);
    static bool chargerPartie(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon);
    
    // Réinitialisation pour une nouvelle partie
    static void reinitialisationNouvellePartie();
};

#endif