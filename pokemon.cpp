#include "pokemon.hpp"
#include <algorithm>
#include <iostream>

Pokemon::Pokemon(const std::string& nom, const std::string& type1, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : nom(nom), typePrincipal(type1), typeSecondaire(type2), pointsDeVie(hp), pointsDeVieMax(hp), nomAttaque(attaque), degatsAttaque(puissance), niveau(1) {
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

int Pokemon::getNiveau() const {
    return niveau;
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
    // Implémentation par défaut, sera surchargée par les classes dérivées
    return 1.0;
}

// === Feu ===
Feu::Feu(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Feu", type2, hp, attaque, puissance) {}

double Feu::calculerMultiplicateur(const std::string& typeAttaque) const {
    // IMPORTANT: Ces valeurs sont basées sur le tableau fourni dans le projet
    
    // Faiblesses x2
    if (typeAttaque == "Eau" || typeAttaque == "Roche" || typeAttaque == "Sol") {
        std::cout << "DEBUG: " << getNom() << " est faible contre " << typeAttaque << " ! (x2)" << std::endl;
        return 2.0;
    }
    
    // Résistances x0.5
    if (typeAttaque == "Plante" || typeAttaque == "Glace" || 
        typeAttaque == "Insecte" || typeAttaque == "Acier" || 
        typeAttaque == "Fée") {
        std::cout << "DEBUG: " << getNom() << " résiste à " << typeAttaque << " ! (x0.5)" << std::endl;
        return 0.5;
    }
    
    // Aucun effet particulier
    return 1.0;
}

// === Eau ===
Eau::Eau(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Eau", type2, hp, attaque, puissance) {}

double Eau::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses x2
    if (typeAttaque == "Plante" || typeAttaque == "Électrik" || typeAttaque == "Electrik") {
        std::cout << "DEBUG: " << getNom() << " est faible contre " << typeAttaque << " ! (x2)" << std::endl;
        return 2.0;
    }
    
    // Résistances x0.5
    if (typeAttaque == "Feu" || typeAttaque == "Eau" || 
        typeAttaque == "Glace" || typeAttaque == "Acier") {
        std::cout << "DEBUG: " << getNom() << " résiste à " << typeAttaque << " ! (x0.5)" << std::endl;
        return 0.5;
    }
    
    // Aucun effet particulier
    return 1.0;
}

// === Plante ===
Plante::Plante(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Plante", type2, hp, attaque, puissance) {}

double Plante::calculerMultiplicateur(const std::string& typeAttaque) const {
    // Faiblesses x2
    if (typeAttaque == "Feu" || typeAttaque == "Glace" || 
        typeAttaque == "Poison" || typeAttaque == "Vol" || 
        typeAttaque == "Insecte") {
        std::cout << "DEBUG: " << getNom() << " est faible contre " << typeAttaque << " ! (x2)" << std::endl;
        return 2.0;
    }
    
    // Résistances x0.5
    if (typeAttaque == "Eau" || typeAttaque == "Sol" || typeAttaque == "Roche") {
        std::cout << "DEBUG: " << getNom() << " résiste à " << typeAttaque << " ! (x0.5)" << std::endl;
        return 0.5;
    }
    
    // Aucun effet particulier
    return 1.0;
}

std::string Pokemon::interaction() const {
    return nom + " vous regarde avec enthousiasme !";
}