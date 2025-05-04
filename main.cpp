#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "pokemon.hpp"
#include "entraineur.hpp"
#include "combat.hpp"
#include "interface.hpp"

using namespace std;

vector<Pokemon*> importerPokemonDepuisCSV(const string& cheminFichier) {
    vector<Pokemon*> catalogue;
    ifstream fichier(cheminFichier);
    string ligne;

    if (getline(fichier, ligne)) { // lire l'en-tête
        while (getline(fichier, ligne)) {
            stringstream flux(ligne);
            string nom, type1, type2, attaque;
            int hp, puissance;

            getline(flux, nom, ',');
            getline(flux, type1, ',');
            getline(flux, type2, ',');
            flux >> hp;
            flux.ignore();
            getline(flux, attaque, ',');
            flux >> puissance;

            Pokemon* p = nullptr;
            if (type1 == "Feu") p = new Feu(nom, type2, hp, attaque, puissance);
            else if (type1 == "Eau") p = new Eau(nom, type2, hp, attaque, puissance);
            else if (type1 == "Plante") p = new Plante(nom, type2, hp, attaque, puissance);
            else p = new Pokemon(nom, type1, type2, hp, attaque, puissance);

            if (p) catalogue.emplace_back(p);
        }
    }
    return catalogue;
}

Joueur* creerJoueurDepuisCSV(const string& chemin, const vector<Pokemon*>& reference) {
    ifstream fichier(chemin);
    string ligne;

    if (!getline(fichier, ligne)) return nullptr; // ignorer en-tête
    if (!getline(fichier, ligne)) return nullptr;

    stringstream ss(ligne);
    string nom;
    getline(ss, nom, ',');

    vector<string> nomsPokemon(6);
    for (int i = 0; i < 6; ++i) getline(ss, nomsPokemon[i], ',');

    Joueur* j = new Joueur(nom);
    for (const auto& nomPk : nomsPokemon) {
        for (const auto& p : reference) {
            if (p->getNom() == nomPk) {
                j->ajouterPokemon(new Pokemon(*p));
                break;
            }
        }
    }
    return j;
}

void interfaceUtilisateur(Joueur* joueur, vector<Entraineur*> leaders, vector<Entraineur*> maitres) {
    showTitleScreen();
    menuPrincipal(joueur, leaders, maitres);
}

int main() {
    vector<Pokemon*> baseDeDonnees = importerPokemonDepuisCSV("pokemon.csv");
    Joueur* joueur = creerJoueurDepuisCSV("joueur.csv", baseDeDonnees);

    vector<Entraineur*> leaders; // chargement futur
    vector<Entraineur*> maitres; // chargement futur

    clearScreen(); // Ajoutez cette ligne
    interfaceUtilisateur(joueur, leaders, maitres);

    for (auto& p : baseDeDonnees) delete p;
    delete joueur;

    return 0;
}
