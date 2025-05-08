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

    if (getline(fichier, ligne)) {
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

    if (!getline(fichier, ligne)) return nullptr;
    if (!getline(fichier, ligne)) return nullptr;

    stringstream ss(ligne);
    string nom;
    getline(ss, nom, ',');

    vector<string> nomsPokemon(6);
    for (int i = 0; i < 6; ++i) getline(ss, nomsPokemon[i], ',');

    Joueur* j = new Joueur(nom);
    for (auto nomPk : nomsPokemon) {
        // Nettoyage des espaces invisibles
        nomPk.erase(nomPk.find_last_not_of(" \n\r\t") + 1);
        for (const auto& p : reference) {
            string nomBase = p->getNom();
            nomBase.erase(nomBase.find_last_not_of(" \n\r\t") + 1);
            if (nomBase == nomPk) {
                j->ajouterPokemon(new Pokemon(*p));
                break;
            }
        }
    }
    return j;
}

vector<Entraineur*> chargerEntraineursDepuisCSV(const string& chemin, const vector<Pokemon*>& reference, bool estMaitre) {
    vector<Entraineur*> entraineurs;
    ifstream fichier(chemin);
    string ligne;

    if (!getline(fichier, ligne)) return entraineurs;

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string nom, gym, badge;
        vector<string> nomsPokemon(6);

        getline(ss, nom, ',');

        if (!estMaitre) {
            getline(ss, gym, ',');
            getline(ss, badge, ',');
        }

        for (int i = 0; i < 6; ++i) getline(ss, nomsPokemon[i], ',');

        Entraineur* e = static_cast<Entraineur*>(
            estMaitre
                ? static_cast<Entraineur*>(new MaitrePokemon(nom))
                : static_cast<Entraineur*>(new LeaderGym(nom, gym, badge))
        );

        for (auto nomPk : nomsPokemon) {
            // Nettoyage des espaces invisibles
            nomPk.erase(nomPk.find_last_not_of(" \n\r\t") + 1);
            for (const auto& p : reference) {
                string nomBase = p->getNom();
                nomBase.erase(nomBase.find_last_not_of(" \n\r\t") + 1);
                if (nomBase == nomPk) {
                    e->ajouterPokemon(new Pokemon(*p));
                    break;
                }
            }
        }
        entraineurs.push_back(e);
    }
    return entraineurs;
}

void interfaceUtilisateur(Joueur* joueur, vector<Entraineur*> leaders, vector<Entraineur*> maitres) {
    showTitleScreen();
    menuPrincipal(joueur, leaders, maitres);
}

int main() {
    system("chcp 65001 > nul"); // For UTF-8 support in Windows terminal

    vector<Pokemon*> baseDeDonnees = importerPokemonDepuisCSV("pokemon.csv");
    Joueur* joueur = creerJoueurDepuisCSV("joueur.csv", baseDeDonnees);

    vector<Entraineur*> leaders = chargerEntraineursDepuisCSV("leaders.csv", baseDeDonnees, false);
    vector<Entraineur*> maitres = chargerEntraineursDepuisCSV("maitres.csv", baseDeDonnees, true);

    clearScreen();
    interfaceUtilisateur(joueur, leaders, maitres);

    for (auto& p : baseDeDonnees) delete p;
    for (auto& l : leaders) delete l;
    for (auto& m : maitres) delete m;
    delete joueur;

    return 0;
}
