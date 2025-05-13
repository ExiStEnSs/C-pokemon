#include "pokemon.hpp"
#include <algorithm>
#include <iostream>

Pokemon::Pokemon(const std::string& nom, const std::string& type1, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : nom(nom), typePrincipal(type1), typeSecondaire(type2), pointsDeVie(hp), pointsDeVieMax(hp), nomAttaque(attaque), degatsAttaque(puissance){
}

std::string Pokemon::getNom() const {
    return nom;
}

std::string Pokemon::getType1() const {
    return typePrincipal;
}

std::string Pokemon::getType2() const {
    return typeSecondaire;
}

int Pokemon::getHp() const {
    return pointsDeVie;
}

int Pokemon::getMaxHp() const {
    return pointsDeVieMax;
}

std::string Pokemon::getAttaque() const {
    return nomAttaque;
}

int Pokemon::getPuissance() const {
    return degatsAttaque;
}

void Pokemon::subirDegats(int quantite) {
    int nouveauxPV = pointsDeVie - quantite;
    pointsDeVie = (nouveauxPV < 0) ? 0 : nouveauxPV;
}

bool Pokemon::estKo() const {
    return pointsDeVie <= 0;
}

void Pokemon::restaurerPV() {
    pointsDeVie = pointsDeVieMax;
}

double Pokemon::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Cas de base: aucune faiblesse ni résistance spécifique
    return 1.0;
}

std::string Pokemon::interaction() const {
    return nom + " vous regarde avec enthousiasme !";
}

// ========== IMPLÉMENTATIONS DES TYPES ==========

// 1. Feu
Feu::Feu(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Feu", type2, hp, attaque, puissance) {}

double Feu::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Eau" || typeAttaque == "Roche" || typeAttaque == "Sol") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Plante" || typeAttaque == "Glace" || 
        typeAttaque == "Insecte" || typeAttaque == "Fee" || typeAttaque == "Fée") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 2. Eau
Eau::Eau(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Eau", type2, hp, attaque, puissance) {}

double Eau::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Plante" || typeAttaque == "Electrik") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Feu" || typeAttaque == "Eau" || typeAttaque == "Glace") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 3. Plante
Plante::Plante(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Plante", type2, hp, attaque, puissance) {}

double Plante::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Feu" || typeAttaque == "Glace" || 
        typeAttaque == "Poison" || typeAttaque == "Insecte") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Eau" || typeAttaque == "Sol" || typeAttaque == "Roche") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 4. Électrik
Electrik::Electrik(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Electrik", type2, hp, attaque, puissance) {}

double Electrik::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Sol") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Electrik") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 5. Normal
Normal::Normal(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Normal", type2, hp, attaque, puissance) {}

double Normal::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Combat") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Immunités (×0)
    if (typeAttaque == "Spectre") {
        std::cout << "DEBUG: " << this->getNom() << " est immunisé contre " << typeAttaque << " (×0)" << std::endl;
        return 0.0;
    }
    // Normal
    return 1.0;
}

// 6. Psy
Psy::Psy(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Psy", type2, hp, attaque, puissance) {}

double Psy::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Insecte" || typeAttaque == "Spectre") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Combat" || typeAttaque == "Psy") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 7. Poison
Poison::Poison(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Poison", type2, hp, attaque, puissance) {}

double Poison::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Sol" || typeAttaque == "Psy") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Plante" || typeAttaque == "Combat" || 
        typeAttaque == "Poison" || typeAttaque == "Insecte") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 8. Insecte
Insecte::Insecte(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Insecte", type2, hp, attaque, puissance) {}

double Insecte::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Feu" || typeAttaque == "Roche") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Plante" || typeAttaque == "Combat" || typeAttaque == "Sol") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 9. Sol
Sol::Sol(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Sol", type2, hp, attaque, puissance) {}

double Sol::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Eau" || typeAttaque == "Plante" || typeAttaque == "Glace") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Poison" || typeAttaque == "Roche") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Immunités (×0)
    if (typeAttaque == "Electrik") {
        std::cout << "DEBUG: " << this->getNom() << " est immunisé contre " << typeAttaque << " (×0)" << std::endl;
        return 0.0;
    }
    // Normal
    return 1.0;
}

// 10. Roche
Roche::Roche(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Roche", type2, hp, attaque, puissance) {}

double Roche::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Eau" || typeAttaque == "Plante" || 
        typeAttaque == "Combat" || typeAttaque == "Sol") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Feu" || typeAttaque == "Poison" || 
        typeAttaque == "Normal") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 11. Glace
Glace::Glace(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Glace", type2, hp, attaque, puissance) {}

double Glace::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Feu" || typeAttaque == "Combat" || 
        typeAttaque == "Roche") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Glace") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 12. Dragon
Dragon::Dragon(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Dragon", type2, hp, attaque, puissance) {}

double Dragon::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Glace" || typeAttaque == "Dragon" || 
        typeAttaque == "Fee" || typeAttaque == "Fée") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Feu" || typeAttaque == "Eau" || 
        typeAttaque == "Electrik"|| 
        typeAttaque == "Plante") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 13. Spectre
Spectre::Spectre(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Spectre", type2, hp, attaque, puissance) {}

double Spectre::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Spectre") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Poison" || typeAttaque == "Insecte") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Immunités (×0)
    if (typeAttaque == "Normal" || typeAttaque == "Combat") {
        std::cout << "DEBUG: " << this->getNom() << " est immunisé contre " << typeAttaque << " (×0)" << std::endl;
        return 0.0;
    }
    // Normal
    return 1.0;
}

// 14. Combat
Combat::Combat(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Combat", type2, hp, attaque, puissance) {}

double Combat::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Psy" || typeAttaque == "Fee" || typeAttaque == "Fée") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Roche" || typeAttaque == "Insecte") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}

// 15. Fée
Fee::Fee(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Fee", type2, hp, attaque, puissance) {}

double Fee::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses (×2)
    if (typeAttaque == "Poison") {
        std::cout << "DEBUG: " << this->getNom() << " est faible contre " << typeAttaque << " (×2)" << std::endl;
        return 2.0;
    }
    // Résistances (×0.5)
    if (typeAttaque == "Combat" || typeAttaque == "Insecte" || typeAttaque == "Dragon") {
        std::cout << "DEBUG: " << this->getNom() << " résiste à " << typeAttaque << " (×0.5)" << std::endl;
        return 0.5;
    }
    // Normal
    return 1.0;
}