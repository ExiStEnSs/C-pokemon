#ifndef ENTRAINEUR_HPP
#define ENTRAINEUR_HPP
#include "pokemon.hpp"
#include <vector>
#include <string>
#include <memory>
#include "interagir.hpp"

class Entraineur : public Interagir {
protected:
    std::string nom;
    std::vector<Pokemon*> equipe;
    int indexPokemonActif;
public:
    explicit Entraineur(const std::string& nom);
    virtual ~Entraineur();
    void ajouterPokemon(Pokemon* nouveau);
    Pokemon* pokemonActif(int index = -1) const;
    bool touteEquipeKO() const;
    void selectionnerPokemon(int nouvelIndex);
    void soignerEquipe();
    virtual void afficherEquipe() const;
    int getTailleEquipe() const { return equipe.size(); }
    void viderEquipe();
    void echangerPokemon(int index1, int index2);
    std::string getNom() const { return nom; }
    virtual std::string interaction() const override;
};
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
    void afficherStats() const;
    int getNombreBadges() const { return nombreBadges; }
    int getVictoires() const { return totalVictoires; }
    int getDefaites() const { return totalDefaites; }
    void enregistrerVaincu(Entraineur* adversaire);
    void interagirAvecVaincus() const;
    std::string interaction() const override;
    const std::vector<Entraineur*>& getAdversairesVaincus() const { return adversairesVaincus; }
};
class LeaderGym : public Entraineur {
private:
    std::string nomGym;
    std::string recompenseMedaille;

public:
    LeaderGym(const std::string& nom, const std::string& gym, const std::string& medaille);
    std::string getNomGym() const { return nomGym; }
    std::string getMedaille() const { return recompenseMedaille; }
    std::string interaction() const override;
};
class MaitrePokemon : public Entraineur {
public:
    explicit MaitrePokemon(const std::string& nom);
    int appliquerBonusDegats(int degatsDeBase) const;
    std::string interaction() const override;
};
#endif