#include "pokemon.hpp"
#include <algorithm>

Pokemon::Pokemon(const std::string& nom, const std::string& type1, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : nom(nom), typePrincipal(type1), typeSecondaire(type2), pointsDeVie(hp), pointsDeVieMax(hp), nomAttaque(attaque), degatsAttaque(puissance), niveau(1) {}

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

void Pokemon::gagnerExperience() {
    niveau++;
    pointsDeVieMax += 5;
    degatsAttaque += 2;
    pointsDeVie = pointsDeVieMax; // restaure la vie après level up
}

double Pokemon::calculerMultiplicateur(const std::string& typeAttaque) const {
    return 1.0;
}

// === Feu ===
Feu::Feu(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Feu", type2, hp, attaque, puissance) {}

double Feu::calculerMultiplicateur(const std::string& typeAttaque) const {
    if (typeAttaque == "Eau" || typeAttaque == "Roche" || typeAttaque == "Sol") {
        return 2.0;
    }
    if (typeAttaque == "Plante" || typeAttaque == "Glace" || typeAttaque == "Insecte" || typeAttaque == "Acier" || typeAttaque == "Fée") {
        return 0.5;
    }
    return 1.0;
}

// === Eau ===
Eau::Eau(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Eau", type2, hp, attaque, puissance) {}

double Eau::calculerMultiplicateur(const std::string& typeAttaque) const {
    if (typeAttaque == "Plante" || typeAttaque == "Electrik") {
        return 2.0;
    }
    if (typeAttaque == "Feu" || typeAttaque == "Eau" || typeAttaque == "Glace" || typeAttaque == "Acier") {
        return 0.5;
    }
    return 1.0;
}

// === Plante ===
Plante::Plante(const std::string& nom, const std::string& type2, int hp, const std::string& attaque, int puissance)
    : Pokemon(nom, "Plante", type2, hp, attaque, puissance) {}

double Plante::calculerMultiplicateur(const std::string& typeAttaque) const {
    static const std::vector<std::string> faiblesses = {"Feu", "Glace", "Poison", "Vol", "Insecte"};
    static const std::vector<std::string> resistances = {"Eau", "Sol", "Roche"};

    if (std::find(faiblesses.begin(), faiblesses.end(), typeAttaque) != faiblesses.end()) return 2.0;
    if (std::find(resistances.begin(), resistances.end(), typeAttaque) != resistances.end()) return 0.5;
    return 1.0;
}
