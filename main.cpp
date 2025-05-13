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

// Fonction pour lister tous les joueurs disponibles
vector<string> listerJoueursDisponibles(const string& chemin) {
    vector<string> noms;
    ifstream fichier(chemin);
    string ligne;
    
    // Ignorer l'en-tête
    if (!getline(fichier, ligne)) return noms;
    
    // Lire chaque ligne et extraire le nom
    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string nom;
        getline(ss, nom, ',');
        
        // Nettoyer les espaces
        nom.erase(0, nom.find_first_not_of(" \t\r\n"));
        nom.erase(nom.find_last_not_of(" \t\r\n") + 1);
        
        if (!nom.empty()) {
            noms.push_back(nom);
        }
    }
    
    return noms;
}

// Fonction pour créer un joueur par index (modifiée)
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

            // Créer le joueur
            Joueur* j = new Joueur(nom);
            
            // Ajouter les Pokémon à l'équipe
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
                        
                        if (copie) {
                            j->ajouterPokemon(copie);
                        }
                        break;
                    }
                }
            }
            
            // Lire les statistiques (nouvelles colonnes)
            string temp;
            int badges = 0, victoires = 0, defaites = 0;
            
            if (getline(ss, temp, ',') && !temp.empty()) {
                badges = atoi(temp.c_str());
            }
            if (getline(ss, temp, ',') && !temp.empty()) {
                victoires = atoi(temp.c_str());
            }
            if (getline(ss, temp) && !temp.empty()) {
                defaites = atoi(temp.c_str());
            }
            
            // Appliquer les statistiques au joueur
            for (int i = 0; i < badges; ++i) {
                j->incrementerBadge();
            }
            for (int i = 0; i < victoires; ++i) {
                j->enregistrerVictoire();
            }
            for (int i = 0; i < defaites; ++i) {
                j->enregistrerDefaite();
            }
            
            return j;
        }
        ++compteur;
    }
    return nullptr;  // Si l'index n'existe pas
}

// Fonction pour choisir un joueur au début
Joueur* choisirJoueur(const string& chemin, const vector<Pokemon*>& reference) {
    clearScreen();
    std::cout << "+" << std::string(50, '=') << "+" << std::endl;
    std::cout << "|           SÉLECTION DU DRESSEUR POKÉMON            |" << std::endl;
    std::cout << "+" << std::string(50, '=') << "+" << std::endl;
    
    // Lister tous les joueurs disponibles
    vector<string> nomsJoueurs = listerJoueursDisponibles(chemin);
    
    if (nomsJoueurs.empty()) {
        std::cout << "❌ Aucun joueur trouvé dans le fichier " << chemin << std::endl;
        return nullptr;
    }
    
    std::cout << "\nJoueurs disponibles :" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    for (size_t i = 0; i < nomsJoueurs.size(); ++i) {
        std::cout << (i + 1) << ". 👤 " << nomsJoueurs[i] << std::endl;
    }
    
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "\nChoisissez votre dresseur (1-" << nomsJoueurs.size() << ") : ";
    
    int choix;
    std::cin >> choix;
    
    if (choix >= 1 && choix <= static_cast<int>(nomsJoueurs.size())) {
        // Créer le joueur choisi
        Joueur* joueur = creerJoueurDepuisCSV(chemin, reference, choix - 1);
        
        if (joueur) {
            clearScreen();
            std::cout << "✅ Vous avez choisi : " << joueur->getNom() << std::endl;
            std::cout << "\nVotre équipe :" << std::endl;
            joueur->afficherEquipe();
            waitForEnter();
            return joueur;
        } else {
            std::cout << "❌ Erreur lors du chargement du joueur." << std::endl;
            waitForEnter();
            return nullptr;
        }
    } else {
        std::cout << "❌ Choix invalide. Retour au premier joueur." << std::endl;
        waitForEnter();
        return creerJoueurDepuisCSV(chemin, reference, 0);
    }
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
                    
                    if (copie) {
                        e->ajouterPokemon(copie);
                    }
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
    system("chcp 65001 > nul");

    vector<Pokemon*> baseDeDonnees = importerPokemonDepuisCSV("pokemon.csv");
    
    // Choisir le joueur
    Joueur* joueur = choisirJoueur("joueur.csv", baseDeDonnees);
    
    if (!joueur) {
        std::cerr << "❌ Erreur fatale : Impossible de charger un joueur." << std::endl;
        return -1;
    }

    // 🔍 Vérification importante : l'équipe est-elle déjà chargée ?
    std::cout << "👤 Joueur sélectionné : " << joueur->getNom() << std::endl;
    std::cout << "📊 Équipe actuelle : " << joueur->getTailleEquipe() << " Pokémon" << std::endl;

    // Si l'équipe est vide, c'est normal, sinon c'est déjà chargé
    if (joueur->getTailleEquipe() > 0) {
        std::cout << "✅ Équipe déjà chargée depuis le CSV !" << std::endl;
        std::cout << "Premier Pokémon : " << joueur->pokemonActif()->getNom() << std::endl;
    }

    // Gestion de la sauvegarde/chargement
    clearScreen();
    std::cout << "+" << std::string(50, '=') << "+" << std::endl;
    std::cout << "|      SIMULATEUR DE COMBAT POKÉMON - C++ EDITION     |" << std::endl;
    std::cout << "+" << std::string(50, '=') << "+" << std::endl;
    std::cout << "\nJoueur sélectionné : " << joueur->getNom() << std::endl;
    std::cout << "\nVoulez-vous charger une partie sauvegardée ?\n" << std::endl;
    std::cout << "1. 📂 Oui, charger ma partie sauvegardée" << std::endl;
    std::cout << "0. 🆕 Non, commencer une nouvelle partie" << std::endl;
    std::cout << "\nVotre choix : ";
    int charger;
    std::cin >> charger;
    
    if (charger == 1) {
        // IMPORTANT : Ne pas recharger si l'équipe est déjà correcte
        if (joueur->getTailleEquipe() == 0) {
            bool chargementReussi = Sauvegarde::chargerPartie(*joueur, baseDeDonnees);
            
            if (chargementReussi) {
                std::cout << "✅ Partie chargée avec succès !" << std::endl;
                std::cout << "📊 Équipe après chargement : " << joueur->getTailleEquipe() << " Pokémon" << std::endl;
            } else {
                std::cout << "❌ Impossible de charger la partie." << std::endl;
            }
        } else {
            std::cout << "✅ Partie chargée avec succès !" << std::endl;
        }
        
        // Afficher les statistiques
        joueur->afficherStats();
        waitForEnter();
    } else {
        std::cout << "🔄 Réinitialisation en cours..." << std::endl;
    
    // 1. Sauvegarder l'index du joueur actuel
    string nomJoueurActuel = joueur->getNom();
    vector<string> nomsJoueurs = listerJoueursDisponibles("joueur.csv");
    int indexJoueur = 0;
    
    for (size_t i = 0; i < nomsJoueurs.size(); ++i) {
        if (nomsJoueurs[i] == nomJoueurActuel) {
            indexJoueur = i;
            break;
        }
    }
    
    // 2. Réinitialiser le fichier
    Sauvegarde::reinitialisationNouvellePartie();
    
    // 3. Supprimer et recréer le joueur
    delete joueur;
    joueur = creerJoueurDepuisCSV("joueur.csv", baseDeDonnees, indexJoueur);
    
    if (joueur) {
        std::cout << "✅ Nouvelle partie initialisée !" << std::endl;
        std::cout << "📊 Statistiques remises à zéro :" << std::endl;
        joueur->afficherStats();
    } else {
        std::cerr << "❌ Erreur lors de la création d'une nouvelle partie." << std::endl;
        return -1;
    }
    
    waitForEnter();
    }

    vector<Entraineur*> leaders = chargerEntraineursDepuisCSV("leaders.csv", baseDeDonnees, false);
    vector<Entraineur*> maitres = chargerEntraineursDepuisCSV("maitres.csv", baseDeDonnees, true);

    clearScreen();
    interfaceUtilisateur(joueur, leaders, maitres, baseDeDonnees);

    for (auto& l : leaders) {
        if (l != nullptr) {
            delete l;
            l = nullptr;
        }
    }
    leaders.clear();
    
    for (auto& m : maitres) {
        if (m != nullptr) {
            delete m;
            m = nullptr;
        }
    }
    maitres.clear();
    
    for (auto& p : baseDeDonnees) {
        if (p != nullptr) {
            delete p;
            p = nullptr;
        }
    }
    baseDeDonnees.clear();
    
    if (joueur != nullptr) {
        delete joueur;
        joueur = nullptr;
    }    
    return 0;
}