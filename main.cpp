#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "pokemon.hpp"
#include "entraineur.hpp"
#include "combat.hpp"
#include "interface.hpp"
#include "sauvegarde.hpp"

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
            
            // Création des objets Pokémon en fonction du type1
            if (type1 == "Feu") p = new Feu(nom, type2, hp, attaque, puissance);
            else if (type1 == "Eau") p = new Eau(nom, type2, hp, attaque, puissance);
            else if (type1 == "Plante") p = new Plante(nom, type2, hp, attaque, puissance);
            else if (type1 == "Electrik") p = new Electrik(nom, type2, hp, attaque, puissance);
            else if (type1 == "Normal") p = new Normal(nom, type2, hp, attaque, puissance);
            else if (type1 == "Psy") p = new Psy(nom, type2, hp, attaque, puissance);
            else if (type1 == "Poison") p = new Poison(nom, type2, hp, attaque, puissance);
            else if (type1 == "Insecte") p = new Insecte(nom, type2, hp, attaque, puissance);
            else if (type1 == "Sol") p = new Sol(nom, type2, hp, attaque, puissance);
            else if (type1 == "Roche") p = new Roche(nom, type2, hp, attaque, puissance);
            else if (type1 == "Glace") p = new Glace(nom, type2, hp, attaque, puissance);
            else if (type1 == "Dragon") p = new Dragon(nom, type2, hp, attaque, puissance);
            else if (type1 == "Spectre") p = new Spectre(nom, type2, hp, attaque, puissance);
            else if (type1 == "Combat") p = new Combat(nom, type2, hp, attaque, puissance);
            else if (type1 == "Fee") p = new Fee(nom, type2, hp, attaque, puissance);
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
        if (nomPk.empty()) continue;  // Ignorer les emplacements vides
        
        for (const auto& p : reference) {
            string nomBase = p->getNom();
            nomBase.erase(nomBase.find_last_not_of(" \n\r\t") + 1);
            if (nomBase == nomPk) {
                // Créer une copie du Pokémon et l'ajouter à l'équipe
                Pokemon* copie = nullptr;
                
                // Créer la bonne instance en fonction du type
                if (p->getType1() == "Feu") {
                    copie = new Feu(p->getNom(), p->getType2(), 
                                p->getMaxHp(), p->getAttaque(), 
                                p->getPuissance());
                } else if (p->getType1() == "Eau") {
                    copie = new Eau(p->getNom(), p->getType2(), 
                                 p->getMaxHp(), p->getAttaque(), 
                                 p->getPuissance());
                } else if (p->getType1() == "Plante") {
                    copie = new Plante(p->getNom(), p->getType2(), 
                                   p->getMaxHp(), p->getAttaque(), 
                                   p->getPuissance());
                } else if (p->getType1() == "Electrik") {
                    copie = new Electrik(p->getNom(), p->getType2(), 
                                     p->getMaxHp(), p->getAttaque(), 
                                     p->getPuissance());
                } else if (p->getType1() == "Normal") {
                    copie = new Normal(p->getNom(), p->getType2(), 
                                   p->getMaxHp(), p->getAttaque(), 
                                   p->getPuissance());
                } else if (p->getType1() == "Psy") {
                    copie = new Psy(p->getNom(), p->getType2(), 
                                p->getMaxHp(), p->getAttaque(), 
                                p->getPuissance());
                } else if (p->getType1() == "Poison") {
                    copie = new Poison(p->getNom(), p->getType2(), 
                                   p->getMaxHp(), p->getAttaque(), 
                                   p->getPuissance());
                } else if (p->getType1() == "Insecte") {
                    copie = new Insecte(p->getNom(), p->getType2(), 
                                    p->getMaxHp(), p->getAttaque(), 
                                    p->getPuissance());
                } else if (p->getType1() == "Sol") {
                    copie = new Sol(p->getNom(), p->getType2(), 
                                p->getMaxHp(), p->getAttaque(), 
                                p->getPuissance());
                } else if (p->getType1() == "Roche") {
                    copie = new Roche(p->getNom(), p->getType2(), 
                                  p->getMaxHp(), p->getAttaque(), 
                                  p->getPuissance());
                } else if (p->getType1() == "Glace") {
                    copie = new Glace(p->getNom(), p->getType2(), 
                                  p->getMaxHp(), p->getAttaque(), 
                                  p->getPuissance());
                } else if (p->getType1() == "Dragon") {
                    copie = new Dragon(p->getNom(), p->getType2(), 
                                   p->getMaxHp(), p->getAttaque(), 
                                   p->getPuissance());
                } else if (p->getType1() == "Spectre") {
                    copie = new Spectre(p->getNom(), p->getType2(), 
                                    p->getMaxHp(), p->getAttaque(), 
                                    p->getPuissance());
                } else if (p->getType1() == "Combat") {
                    copie = new Combat(p->getNom(), p->getType2(), 
                                   p->getMaxHp(), p->getAttaque(), 
                                   p->getPuissance());
                } else if (p->getType1() == "Fee" || p->getType1() == "Fée") {
                    copie = new Fee(p->getNom(), p->getType2(), 
                                p->getMaxHp(), p->getAttaque(), 
                                p->getPuissance());
                } else {
                    // Type par défaut
                    copie = new Pokemon(p->getNom(), p->getType1(), 
                                    p->getType2(), p->getMaxHp(), 
                                    p->getAttaque(), p->getPuissance());
                }
                
                j->ajouterPokemon(copie);
                break;
            }
        }
    }
    return j;
}

// Surcharge de la fonction pour créer un joueur par index
Joueur* creerJoueurDepuisCSV(const string& chemin, const vector<Pokemon*>& reference, int index) {
    ifstream fichier(chemin);
    string ligne;
    int compteur = 0;

    // Ignorer l'en-tête
    if (!getline(fichier, ligne)) return nullptr;
    
    // Parcourir le fichier jusqu'à l'index demandé
    while (getline(fichier, ligne)) {
        if (compteur == index) {
            stringstream ss(ligne);
            string nom;
            getline(ss, nom, ',');

            vector<string> nomsPokemon(6);
            for (int i = 0; i < 6; ++i) getline(ss, nomsPokemon[i], ',');

            Joueur* j = new Joueur(nom);
            for (auto nomPk : nomsPokemon) {
                // Nettoyage des espaces invisibles
                nomPk.erase(nomPk.find_last_not_of(" \n\r\t") + 1);
                if (nomPk.empty()) continue;  // Ignorer les emplacements vides
                
                for (const auto& p : reference) {
                    string nomBase = p->getNom();
                    nomBase.erase(nomBase.find_last_not_of(" \n\r\t") + 1);
                    if (nomBase == nomPk) {
                        // Créer une copie du Pokémon et l'ajouter à l'équipe
                        Pokemon* copie = nullptr;
                        
                        // Créer la bonne instance en fonction du type
                        if (p->getType1() == "Feu") {
                            copie = new Feu(p->getNom(), p->getType2(), 
                                        p->getMaxHp(), p->getAttaque(), 
                                        p->getPuissance());
                        } else if (p->getType1() == "Eau") {
                            copie = new Eau(p->getNom(), p->getType2(), 
                                         p->getMaxHp(), p->getAttaque(), 
                                         p->getPuissance());
                        } else if (p->getType1() == "Plante") {
                            copie = new Plante(p->getNom(), p->getType2(), 
                                           p->getMaxHp(), p->getAttaque(), 
                                           p->getPuissance());
                        } else if (p->getType1() == "Electrik") {
                            copie = new Electrik(p->getNom(), p->getType2(), 
                                             p->getMaxHp(), p->getAttaque(), 
                                             p->getPuissance());
                        } else if (p->getType1() == "Normal") {
                            copie = new Normal(p->getNom(), p->getType2(), 
                                           p->getMaxHp(), p->getAttaque(), 
                                           p->getPuissance());
                        } else if (p->getType1() == "Psy") {
                            copie = new Psy(p->getNom(), p->getType2(), 
                                        p->getMaxHp(), p->getAttaque(), 
                                        p->getPuissance());
                        } else if (p->getType1() == "Poison") {
                            copie = new Poison(p->getNom(), p->getType2(), 
                                           p->getMaxHp(), p->getAttaque(), 
                                           p->getPuissance());
                        } else if (p->getType1() == "Insecte") {
                            copie = new Insecte(p->getNom(), p->getType2(), 
                                            p->getMaxHp(), p->getAttaque(), 
                                            p->getPuissance());
                        } else if (p->getType1() == "Sol") {
                            copie = new Sol(p->getNom(), p->getType2(), 
                                        p->getMaxHp(), p->getAttaque(), 
                                        p->getPuissance());
                        } else if (p->getType1() == "Roche") {
                            copie = new Roche(p->getNom(), p->getType2(), 
                                          p->getMaxHp(), p->getAttaque(), 
                                          p->getPuissance());
                        } else if (p->getType1() == "Glace") {
                            copie = new Glace(p->getNom(), p->getType2(), 
                                          p->getMaxHp(), p->getAttaque(), 
                                          p->getPuissance());
                        } else if (p->getType1() == "Dragon") {
                            copie = new Dragon(p->getNom(), p->getType2(), 
                                           p->getMaxHp(), p->getAttaque(), 
                                           p->getPuissance());
                        } else if (p->getType1() == "Spectre") {
                            copie = new Spectre(p->getNom(), p->getType2(), 
                                            p->getMaxHp(), p->getAttaque(), 
                                            p->getPuissance());
                        } else if (p->getType1() == "Combat") {
                            copie = new Combat(p->getNom(), p->getType2(), 
                                           p->getMaxHp(), p->getAttaque(), 
                                           p->getPuissance());
                        } else if (p->getType1() == "Fee" || p->getType1() == "Fée") {
                            copie = new Fee(p->getNom(), p->getType2(), 
                                        p->getMaxHp(), p->getAttaque(), 
                                        p->getPuissance());
                        } else {
                            // Type par défaut
                            copie = new Pokemon(p->getNom(), p->getType1(), 
                                            p->getType2(), p->getMaxHp(), 
                                            p->getAttaque(), p->getPuissance());
                        }
                        
                        j->ajouterPokemon(copie);
                        break;
                    }
                }
            }
            return j;
        }
        ++compteur;
    }
    return nullptr;  // Si l'index n'existe pas
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
            if (nomPk.empty()) continue;  // Ignorer les emplacements vides
            
            for (const auto& p : reference) {
                string nomBase = p->getNom();
                nomBase.erase(nomBase.find_last_not_of(" \n\r\t") + 1);
                if (nomBase == nomPk) {
                    // Créer une copie du Pokémon et l'ajouter à l'équipe
                    Pokemon* copie = nullptr;
                    
                    // Créer la bonne instance en fonction du type
                    if (p->getType1() == "Feu") {
                        copie = new Feu(p->getNom(), p->getType2(), 
                                    p->getMaxHp(), p->getAttaque(), 
                                    p->getPuissance());
                    } else if (p->getType1() == "Eau") {
                        copie = new Eau(p->getNom(), p->getType2(), 
                                     p->getMaxHp(), p->getAttaque(), 
                                     p->getPuissance());
                    } else if (p->getType1() == "Plante") {
                        copie = new Plante(p->getNom(), p->getType2(), 
                                       p->getMaxHp(), p->getAttaque(), 
                                       p->getPuissance());
                    } else if (p->getType1() == "Electrik") {
                        copie = new Electrik(p->getNom(), p->getType2(), 
                                         p->getMaxHp(), p->getAttaque(), 
                                         p->getPuissance());
                    } else if (p->getType1() == "Normal") {
                        copie = new Normal(p->getNom(), p->getType2(), 
                                       p->getMaxHp(), p->getAttaque(), 
                                       p->getPuissance());
                    } else if (p->getType1() == "Psy") {
                        copie = new Psy(p->getNom(), p->getType2(), 
                                    p->getMaxHp(), p->getAttaque(), 
                                    p->getPuissance());
                    } else if (p->getType1() == "Poison") {
                        copie = new Poison(p->getNom(), p->getType2(), 
                                       p->getMaxHp(), p->getAttaque(), 
                                       p->getPuissance());
                    } else if (p->getType1() == "Insecte") {
                        copie = new Insecte(p->getNom(), p->getType2(), 
                                        p->getMaxHp(), p->getAttaque(), 
                                        p->getPuissance());
                    } else if (p->getType1() == "Sol") {
                        copie = new Sol(p->getNom(), p->getType2(), 
                                    p->getMaxHp(), p->getAttaque(), 
                                    p->getPuissance());
                    } else if (p->getType1() == "Roche") {
                        copie = new Roche(p->getNom(), p->getType2(), 
                                      p->getMaxHp(), p->getAttaque(), 
                                      p->getPuissance());
                    } else if (p->getType1() == "Glace") {
                        copie = new Glace(p->getNom(), p->getType2(), 
                                      p->getMaxHp(), p->getAttaque(), 
                                      p->getPuissance());
                    } else if (p->getType1() == "Dragon") {
                        copie = new Dragon(p->getNom(), p->getType2(), 
                                       p->getMaxHp(), p->getAttaque(), 
                                       p->getPuissance());
                    } else if (p->getType1() == "Spectre") {
                        copie = new Spectre(p->getNom(), p->getType2(), 
                                        p->getMaxHp(), p->getAttaque(), 
                                        p->getPuissance());
                    } else if (p->getType1() == "Combat") {
                        copie = new Combat(p->getNom(), p->getType2(), 
                                       p->getMaxHp(), p->getAttaque(), 
                                       p->getPuissance());
                    } else if (p->getType1() == "Fee" || p->getType1() == "Fée") {
                        copie = new Fee(p->getNom(), p->getType2(), 
                                    p->getMaxHp(), p->getAttaque(), 
                                    p->getPuissance());
                    } else {
                        // Type par défaut
                        copie = new Pokemon(p->getNom(), p->getType1(), 
                                        p->getType2(), p->getMaxHp(), 
                                        p->getAttaque(), p->getPuissance());
                    }
                    
                    e->ajouterPokemon(copie);
                    break;
                }
            }
        }
        entraineurs.push_back(e);
    }
    return entraineurs;
}

void interfaceUtilisateur(Joueur* joueur, vector<Entraineur*> leaders, vector<Entraineur*> maitres, vector<Pokemon*>& cataloguePokemon) {
    showTitleScreen();
    menuPrincipal(joueur, leaders, maitres, cataloguePokemon);
}

int main() {
    system("chcp 65001 > nul"); // For UTF-8 support in Windows terminal

    vector<Pokemon*> baseDeDonnees = importerPokemonDepuisCSV("pokemon.csv");
    Joueur* joueur = creerJoueurDepuisCSV("joueur.csv", baseDeDonnees);

    // Ajout de la possibilité de charger une partie sauvegardée
    clearScreen();
    std::cout << "+" << std::string(50, '=') << "+" << std::endl;
    std::cout << "|      SIMULATEUR DE COMBAT POKÉMON - C++ EDITION     |" << std::endl;
    std::cout << "+" << std::string(50, '=') << "+" << std::endl;
    std::cout << "\nAvez-vous une sauvegarde que vous souhaitez charger ?\n" << std::endl;
    std::cout << "1. 📂 Oui, charger ma partie sauvegardée" << std::endl;
    std::cout << "0. 🆕 Non, commencer une nouvelle partie, ATTENTION COMMENCER UNE NOUVELLE PARTIE ECRASE LA SAUVEGARDE PRECEDENTE" << std::endl;
    std::cout << "\nVotre choix : ";
    int charger;
    std::cin >> charger;
    
    if (charger == 1) {
        bool chargementReussi = Sauvegarde::chargerPartie(*joueur, baseDeDonnees);
        if (chargementReussi) {
            std::cout << "Partie chargée avec succès !" << std::endl;
        } else {
            std::cout << "Impossible de charger la partie. Fichier de sauvegarde non trouvé ou corrompu." << std::endl;
        }
        waitForEnter();
    } else {
        // Si le joueur choisit de ne pas charger une partie, c'est une nouvelle partie
        // Réinitialisons les fichiers de sauvegarde
        Sauvegarde::reinitialisationNouvellePartie();
        waitForEnter();
    }

    vector<Entraineur*> leaders = chargerEntraineursDepuisCSV("leaders.csv", baseDeDonnees, false);
    vector<Entraineur*> maitres = chargerEntraineursDepuisCSV("maitres.csv", baseDeDonnees, true);

    clearScreen();
    interfaceUtilisateur(joueur, leaders, maitres, baseDeDonnees);

    for (auto& p : baseDeDonnees) delete p;
    for (auto& l : leaders) delete l;
    for (auto& m : maitres) delete m;
    delete joueur;

    return 0;
}