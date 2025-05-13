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

    void subirDegats(int quantite);
    bool estKo() const;
    void restaurerPV();
    
    // Calcule le multiplicateur de dégâts en fonction du type d'attaque
    virtual double calculerMultiplicateur(const std::string& typeAttaque) const;

    // Interaction avec le joueur
    std::string interaction() const override;
};

// Classes pour chaque type de Pokémon
// 1. Type Feu
class Feu : public Pokemon {
public:
    Feu(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 2. Type Eau
class Eau : public Pokemon {
public:
    Eau(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 3. Type Plante
class Plante : public Pokemon {
public:
    Plante(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 4. Type Électrik
class Electrik : public Pokemon {
public:
    Electrik(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 5. Type Normal
class Normal : public Pokemon {
public:
    Normal(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 6. Type Psy
class Psy : public Pokemon {
public:
    Psy(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 7. Type Poison
class Poison : public Pokemon {
public:
    Poison(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 8. Type Insecte
class Insecte : public Pokemon {
public:
    Insecte(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 9. Type Sol
class Sol : public Pokemon {
public:
    Sol(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 10. Type Roche
class Roche : public Pokemon {
public:
    Roche(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 11. Type Glace
class Glace : public Pokemon {
public:
    Glace(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 12. Type Dragon
class Dragon : public Pokemon {
public:
    Dragon(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 13. Type Spectre
class Spectre : public Pokemon {
public:
    Spectre(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 14. Type Combat
class Combat : public Pokemon {
public:
    Combat(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

// 15. Type Fée
class Fee : public Pokemon {
public:
    Fee(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance);
    double calculerMultiplicateur(const std::string& typeAttaque) const override;
};

#endif