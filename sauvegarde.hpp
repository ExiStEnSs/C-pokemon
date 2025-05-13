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
    static const std::string FICHIER_MAITRES_BATTUS;

public:
    static const std::string FICHIER_JOUEUR;
    static void sauvegarderLeaderBattu(const Joueur& joueur, Entraineur* leader);
    static std::vector<std::string> chargerLeadersBattus();
    static void sauvegarderMaitreBattu(const Joueur& joueur, Entraineur* maitre);
    static std::vector<std::string> chargerMaitresBattus();
    static std::vector<std::string> extraireNomsLeadersBattus();
    static std::vector<std::string> extraireNomsMaitresBattus();
    static void sauvegarderJoueur(const Joueur& joueur);
    static bool chargerJoueur(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon, int index = 0);
    static void sauvegarderPartie(const Joueur& joueur, Entraineur* dernier_leader_battu = nullptr);
    static bool chargerPartie(Joueur& joueur, const std::vector<Pokemon*>& cataloguePokemon);
    static void reinitialisationNouvellePartie();
    static void nettoyerDoublonsLeaders();
    static void nettoyerDoublonsMaitres();
};

#endif