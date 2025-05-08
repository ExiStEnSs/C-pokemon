#ifndef ENTRAINEUR_HPP
#define ENTRAINEUR_HPP

#include "pokemon.hpp"
#include <vector>
#include <string>
#include <memory>
#include "interagir.hpp"

// Classe de base représentant un entraîneur de Pokémon
class Entraineur : public Interagir {
protected:
    std::string nom;
    std::vector<Pokemon*> equipe;
    int indexPokemonActif;

public:
    explicit Entraineur(const std::string& nom);
    virtual ~Entraineur();

    void ajouterPokemon(Pokemon* nouveau);
    Pokemon* pokemonActif() const;
    bool touteEquipeKO() const;
    void selectionnerPokemon(int nouvelIndex);
    void soignerEquipe();
    virtual void afficherEquipe() const;

    void echangerPokemon(int index1, int index2);
    
    // Ajout: méthode pour obtenir le nom de l'entraîneur
    std::string getNom() const { return nom; }

    // ✅ Ajout : interaction de base pour tout entraîneur
    virtual std::string interaction() const override;
};

// Classe représentant un joueur humain
class Joueur : public Entraineur {
private:
    int nombreBadges;
    int totalVictoires;
    int totalDefaites;
    std::vector<Entraineur*> adversairesVaincus;

public:
    explicit Joueur(const std::string& nom);

    void incrementerBadge();
    void enregistrerVictoire();
    void enregistrerDefaite();
    std::string getRank() const;
    void afficherStats() const;

    int getNombreBadges() const { return nombreBadges; }
    int getVictoires() const { return totalVictoires; } // Ajout: getter pour totalVictoires

    void enregistrerVaincu(Entraineur* adversaire);
    void interagirAvecVaincus() const;

    std::string interaction() const override; // ✅ Ajouté
};

// Classe représentant un leader de gymnase
class LeaderGym : public Entraineur {
private:
    std::string nomGym;
    std::string recompenseMedaille;

public:
    LeaderGym(const std::string& nom, const std::string& gym, const std::string& medaille);
    std::string getNomGym() const { return nomGym; } // Ajout: getter pour nomGym
    std::string getMedaille() const { return recompenseMedaille; } // Ajout: getter pour recompenseMedaille
    std::string interaction() const override; // ✅ Ajouté
};

// Classe représentant le maître Pokémon
class MaitrePokemon : public Entraineur {
public:
    explicit MaitrePokemon(const std::string& nom);
    int appliquerBonusDegats(int degatsDeBase) const;
    std::string interaction() const override; // ✅ Ajouté
};

#endif