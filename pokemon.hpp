#ifndef POKEMON_HPP
#define POKEMON_HPP

#include "interagir.hpp"
#include <string>
#include <vector>

// Classe de base generique pour tous les Pokemon
class Pokemon : public Interagir {
protected:
    std::string nom;
    std::string typePrincipal;
    std::string typeSecondaire;
    int pointsDeVie;
    int pointsDeVieMax;
    std::string nomAttaque;
    int degatsAttaque;
    int niveau; // ✅ Ajout pour la V5

public:
    Pokemon(const std::string& nom, const std::string& type1, const std::string& type2, int hp, const std::string& attaque, int puissance);
    virtual ~Pokemon() = default;

    std::string getNom() const;
    std::string getType1() const;
    std::string getType2() const;
    int getHp() const;
    int getMaxHp() const;
    std::string getAttaque() const;
    int getPuissance() const;
    int getNiveau() const;           // ✅ Ajouté
    void gagnerExperience();         // ✅ Ajouté

    void subirDegats(int quantite);
    bool estKo() const;
    virtual double calculerMultiplicateur(const std::string& typeAttaque) const;

    // ✅ Interaction avec le joueur
    std::string interaction() const override;
};

// Classe pour les Pokemon de type Feu
class Feu : public Pokemon {
public:
    Feu(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// Classe pour les Pokemon de type Eau
class Eau : public Pokemon {
public:
    Eau(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// Classe pour les Pokemon de type Plante
class Plante : public Pokemon {
public:
    Plante(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

#endif
