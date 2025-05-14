#include "sauvegarde.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <set>
using namespace std;

// Définir les constantes de chemins de fichiers
const string Sauvegarde::FICHIER_LEADERS_BATTUS = "save/leaders_battus.txt";
const string Sauvegarde::FICHIER_JOUEUR = "joueur.csv";
const string Sauvegarde::FICHIER_MAITRES_BATTUS = "save/maitres_battus.txt";
// Créer la fonction pour s'assurer que le dossier existe
void assurerDossierSauvegarde() {
#ifdef _WIN32
    system("mkdir save 2>nul");
#else
    system("mkdir -p save 2>/dev/null");
#endif
}
// Sauvegarde des leaders battus
void Sauvegarde::sauvegarderLeaderBattu(const Joueur& joueur, Entraineur* leader) {
    if (!leader) {
        cerr << "Erreur : Pointeur leader invalide" << endl;
        return;
    }
    
    assurerDossierSauvegarde();
    
    // Vérifier d'abord si ce leader n'a pas déjà été battu
    LeaderGym* gym_leader = dynamic_cast<LeaderGym*>(leader);
    if (gym_leader) {
        // Lire le fichier existant pour vérifier les doublons
        vector<string> leadersExistants = chargerLeadersBattus();
        
        // Vérifier si ce leader a déjà été battu
        string nomLeader = gym_leader->getNom();
        string nomGym = gym_leader->getNomGym();
        
        for (const auto& ligne : leadersExistants) {
            if (ligne.find("Leader " + nomLeader + " (Arène de " + nomGym + ")") != string::npos) {
                cout << "ℹ️  Le leader " << nomLeader << " a déjà été battu. Victoire enregistrée mais pas de nouveau badge." << endl;
                return;
            }
        }
    }
    
    ofstream fichier(FICHIER_LEADERS_BATTUS, ios::app);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << FICHIER_LEADERS_BATTUS << endl;
        return;
    }
    
    // Obtenir la date et heure actuelles
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    
    // Écrire dans le fichier avec vérifications
    if (gym_leader) {
        fichier << "Leader " << leader->getNom() 
                << " (Arène de " << gym_leader->getNomGym() << ")"
                << " battu par " << joueur.getNom() 
                << " le " << ss.str() << endl;
    } else {
        MaitrePokemon* maitre = dynamic_cast<MaitrePokemon*>(leader);
        if (maitre) {
            fichier << "Maître " << leader->getNom() 
                    << " battu par " << joueur.getNom() 
                    << " le " << ss.str() << endl;
        } else {
            fichier << leader->getNom() << " battu par " << joueur.getNom() 
                    << " le " << ss.str() << endl;
        }
    }
    
    fichier.close();
    cout << "✅ Première victoire contre ce leader sauvegardée !" << endl;
}
void Sauvegarde::sauvegarderMaitreBattu(const Joueur& joueur, Entraineur* maitre) {
    if (!maitre) {
        cerr << "Erreur : Pointeur maître invalide" << endl;
        return;
    }
    
    assurerDossierSauvegarde();
    
    // Vérifier d'abord si ce maître n'a pas déjà été battu
    MaitrePokemon* maitre_pokemon = dynamic_cast<MaitrePokemon*>(maitre);
    if (maitre_pokemon) {
        // Lire le fichier existant pour vérifier les doublons
        vector<string> maitresExistants = chargerMaitresBattus();
        
        // Vérifier si ce maître a déjà été battu
        string nomMaitre = maitre_pokemon->getNom();
        
        for (const auto& ligne : maitresExistants) {
            if (ligne.find("Maître " + nomMaitre + " battu") != string::npos) {
                cout << "ℹ️  Le maître " << nomMaitre << " a déjà été battu. Victoire enregistrée mais pas de doublon." << endl;
                return;
            }
        }
    }
    
    ofstream fichier(FICHIER_MAITRES_BATTUS, ios::app);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << FICHIER_MAITRES_BATTUS << endl;
        return;
    }
    
    // Obtenir la date et heure actuelles
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    
    // Vérifier si c'est bien un maître Pokemon
    if (maitre_pokemon) {
        fichier << "Maître " << maitre->getNom() 
                << " battu par " << joueur.getNom() 
                << " le " << ss.str() << endl;
    } else {
        fichier << maitre->getNom() << " battu par " << joueur.getNom() 
                << " le " << ss.str() << endl;
    }
    
    fichier.close();
    cout << "✅ Première victoire contre ce maître sauvegardée !" << endl;
}
vector<string> Sauvegarde::chargerLeadersBattus() {
    vector<string> leaders;
    ifstream fichier(FICHIER_LEADERS_BATTUS);
    
    if (!fichier.is_open()) {
        return leaders;
    }
    
    string ligne;
    while (getline(fichier, ligne)) {
        if (!ligne.empty()) {
            leaders.push_back(ligne);
        }
    }
    
    fichier.close();
    return leaders;
}
vector<string> Sauvegarde::chargerMaitresBattus() {
    vector<string> maitres;
    ifstream fichier(FICHIER_MAITRES_BATTUS);
    
    if (!fichier.is_open()) {
        return maitres;
    }
    
    string ligne;
    while (getline(fichier, ligne)) {
        if (!ligne.empty()) {
            maitres.push_back(ligne);
        }
    }
    
    fichier.close();
    return maitres;
}
vector<string> lireLignesJoueur() {
    vector<string> lignes;
    ifstream fichier(Sauvegarde::FICHIER_JOUEUR);
    string ligne;
    
    while (getline(fichier, ligne)) {
        lignes.push_back(ligne);
    }
    
    fichier.close();
    return lignes;
}
void ecrireLignesJoueur(const vector<string>& lignes) {
    ofstream fichier(Sauvegarde::FICHIER_JOUEUR);
    
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir " << Sauvegarde::FICHIER_JOUEUR << endl;
        return;
    }
    
    for (const auto& ligne : lignes) {
        fichier << ligne << endl;
    }
    
    fichier.close();
}
vector<string> Sauvegarde::extraireNomsLeadersBattus() {
    vector<string> noms;
    vector<string> lignes = chargerLeadersBattus();
    
    for (const auto& ligne : lignes) {
        // Format: "Leader NomLeader (Arène de NomGym) battu par NomJoueur le Date"
        size_t pos = ligne.find("Leader ");
        if (pos != string::npos) {
            pos += 7;
            size_t fin = ligne.find(" (Arène", pos);
            if (fin != string::npos) {
                string nom = ligne.substr(pos, fin - pos);
                noms.push_back(nom);
            }
        }
    }
    
    return noms;
}
vector<string> Sauvegarde::extraireNomsMaitresBattus() {
    vector<string> noms;
    vector<string> lignes = chargerMaitresBattus();
    
    for (const auto& ligne : lignes) {
        // Format: "Maître NomMaitre battu par NomJoueur le Date"
        size_t pos = ligne.find("Maître ");
        if (pos != string::npos) {
            pos += 7;
            size_t fin = ligne.find(" battu", pos);
            if (fin != string::npos) {
                string nom = ligne.substr(pos, fin - pos);
                noms.push_back(nom);
            }
        }
    }
    
    return noms;
}
void Sauvegarde::sauvegarderJoueur(const Joueur& joueur) {
    vector<string> lignes = lireLignesJoueur();
    
    // Si le fichier est vide ou n'existe pas, créer l'en-tête
    if (lignes.empty()) {
        lignes.push_back("nom,pokemon1,pokemon2,pokemon3,pokemon4,pokemon5,pokemon6,badges,victoires,defaites");
    }
    
    // Construire la nouvelle ligne pour ce joueur
    stringstream nouvelleLigne;
    nouvelleLigne << joueur.getNom();
    
    // Ajouter les Pokémon (jusqu'à 6)
    for (int i = 0; i < 6; ++i) {
        nouvelleLigne << ",";
        if (i < joueur.getTailleEquipe()) {
            Pokemon* pokemon = joueur.pokemonActif(i);
            if (pokemon) {
                nouvelleLigne << pokemon->getNom();
            }
        }
    }
    
    // Ajouter les statistiques
    nouvelleLigne << "," << joueur.getNombreBadges()
                 << "," << joueur.getVictoires()
                 << "," << joueur.getDefaites();
    
    // Chercher si le joueur existe déjà
    bool joueurTrouve = false;
    for (size_t i = 0; i < lignes.size(); ++i) {
        if (i == 0) continue;
        
        stringstream ss(lignes[i]);
        string nomExistant;
        getline(ss, nomExistant, ',');
        
        if (nomExistant == joueur.getNom()) {
            lignes[i] = nouvelleLigne.str();
            joueurTrouve = true;
            break;
        }
    }
    
    // Si le joueur n'existe pas, l'ajouter
    if (!joueurTrouve) {
        lignes.push_back(nouvelleLigne.str());
    }
    
    // Réécrire le fichier
    ecrireLignesJoueur(lignes);
}
void Sauvegarde::nettoyerDoublonsLeaders() {
    vector<string> lignes = chargerLeadersBattus();
    vector<string> lignesUniques;
    set<string> leadersVus;
    
    for (const auto& ligne : lignes) {
        // Extraire l'identifiant unique du leader
        size_t pos = ligne.find("Leader ");
        if (pos != string::npos) {
            size_t debut = pos + 7;
            size_t fin = ligne.find(" battu", debut);
            if (fin != string::npos) {
                string identifiant = ligne.substr(debut, fin - debut);
                
                // Si pas encore vu, l'ajouter
                if (leadersVus.find(identifiant) == leadersVus.end()) {
                    leadersVus.insert(identifiant);
                    lignesUniques.push_back(ligne);
                }
            }
        }
    }
    
    // Réécrire le fichier avec uniquement les entrées uniques
    assurerDossierSauvegarde();
    ofstream fichier(FICHIER_LEADERS_BATTUS, ios::trunc);
    if (fichier.is_open()) {
        for (const auto& ligne : lignesUniques) {
            fichier << ligne << endl;
        }
        fichier.close();
        cout << "🧹 Nettoyage terminé : " << (lignes.size() - lignesUniques.size()) 
                  << " doublons supprimés." << endl;
    }
}
// Fonction pour nettoyer les doublons des maîtres
void Sauvegarde::nettoyerDoublonsMaitres() {
    vector<string> lignes = chargerMaitresBattus();
    vector<string> lignesUniques;
    set<string> maitresVus;
    
    for (const auto& ligne : lignes) {
        // Extraire l'identifiant unique du maître
        size_t pos = ligne.find("Maître ");
        if (pos != string::npos) {
            size_t debut = pos + 7;
            size_t fin = ligne.find(" battu", debut);
            if (fin != string::npos) {
                string identifiant = ligne.substr(debut, fin - debut);
                
                if (maitresVus.find(identifiant) == maitresVus.end()) {
                    maitresVus.insert(identifiant);
                    lignesUniques.push_back(ligne);
                }
            }
        }
    }
    
    // Réécrire le fichier avec uniquement les entrées uniques
    assurerDossierSauvegarde();
    ofstream fichier(FICHIER_MAITRES_BATTUS, ios::trunc);
    if (fichier.is_open()) {
        for (const auto& ligne : lignesUniques) {
            fichier << ligne << endl;
        }
        fichier.close();
        cout << "🧹 Nettoyage terminé : " << (lignes.size() - lignesUniques.size()) 
                  << " doublons supprimés." << endl;
    }
}
bool Sauvegarde::chargerJoueur(Joueur& joueur, const vector<Pokemon*>& cataloguePokemon, int index) {
    if (cataloguePokemon.empty()) {
        cerr << "Erreur : Catalogue de Pokémon vide" << endl;
        return false;
    }
    
    ifstream fichier(FICHIER_JOUEUR);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir " << FICHIER_JOUEUR << endl;
        return false;
    }
    
    string ligne;
    int compteur = 0;
    
    if (!getline(fichier, ligne)) {
        fichier.close();
        return false;
    }
    
    string nomRecherche = joueur.getNom();
    cout << "🔍 Recherche du joueur : '" << nomRecherche << "'" << endl;
    
    // Trouver la ligne du joueur par index ou par nom
    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string nomLu;
        getline(ss, nomLu, ',');
        
        cout << "📝 Ligne " << compteur << " : nom trouvé = '" << nomLu << "'" << endl;
        
        bool ligneCorrecte = false;
        
        if (index == -1) {
            string nomLuClean = nomLu;
            nomLuClean.erase(0, nomLuClean.find_first_not_of(" \t\r\n"));
            nomLuClean.erase(nomLuClean.find_last_not_of(" \t\r\n") + 1);
            
            string nomRechercheClean = nomRecherche;
            nomRechercheClean.erase(0, nomRechercheClean.find_first_not_of(" \t\r\n"));
            nomRechercheClean.erase(nomRechercheClean.find_last_not_of(" \t\r\n") + 1);
            
            if (nomLuClean == nomRechercheClean) {
                ligneCorrecte = true;
                cout << "✅ Joueur trouvé par nom !" << endl;
            }
        } else {
            if (compteur == index) {
                ligneCorrecte = true;
                cout << "✅ Joueur trouvé par index !" << endl;
            }
        }
        
        if (ligneCorrecte) {
            stringstream ss2(ligne);
            string nom;
            vector<string> nomsPokemon(6);
            string temp;
            
            // Lire les données
            getline(ss2, nom, ',');
            
            // Lire les 6 Pokémon
            for (int i = 0; i < 6; ++i) {
                getline(ss2, nomsPokemon[i], ',');
            }
            
            // Lire les statistiques (nouvelles colonnes)
            int badges = 0, victoires = 0, defaites = 0;
            
            if (getline(ss2, temp, ',') && !temp.empty()) {
                badges = atoi(temp.c_str());
                cout << "📊 Badges trouvés : " << badges << endl;
            }
            if (getline(ss2, temp, ',') && !temp.empty()) {
                victoires = atoi(temp.c_str());
                cout << "📊 Victoires trouvées : " << victoires << endl;
            }
            if (getline(ss2, temp) && !temp.empty()) {
                defaites = atoi(temp.c_str());
                cout << "📊 Défaites trouvées : " << defaites << endl;
            }
            
            cout << "📊 Stats actuelles avant chargement :" << endl;
            cout << "   Badges : " << joueur.getNombreBadges() << endl;
            cout << "   Victoires : " << joueur.getVictoires() << endl;
            cout << "   Défaites : " << joueur.getDefaites() << endl;
            
            int badgesDiff = badges - joueur.getNombreBadges();
            int victoiresDiff = victoires - joueur.getVictoires();
            int defaitesDiff = defaites - joueur.getDefaites();
            
            cout << "💫 Différences à appliquer :" << endl;
            cout << "   Badges : +" << badgesDiff << endl;
            cout << "   Victoires : +" << victoiresDiff << endl;
            cout << "   Défaites : +" << defaitesDiff << endl;
            
            for (int i = 0; i < badgesDiff && badgesDiff > 0; ++i) {
                joueur.incrementerBadge();
            }
            
            for (int i = 0; i < victoiresDiff && victoiresDiff > 0; ++i) {
                joueur.enregistrerVictoire();
            }
            
            for (int i = 0; i < defaitesDiff && defaitesDiff > 0; ++i) {
                joueur.enregistrerDefaite();
            }
            
            cout << "📊 Stats finales après chargement :" << endl;
            cout << "   Badges : " << joueur.getNombreBadges() << endl;
            cout << "   Victoires : " << joueur.getVictoires() << endl;
            cout << "   Défaites : " << joueur.getDefaites() << endl;
            
            // Charger l'équipe
            cout << "🐾 Chargement de l'équipe..." << endl;
            joueur.viderEquipe();
            
            for (size_t i = 0; i < nomsPokemon.size(); ++i) {
                const string& nomPk = nomsPokemon[i];
                if (nomPk.empty()) continue;
                
                // Nettoyer les espaces
                string nomProprePk = nomPk;
                nomProprePk.erase(0, nomProprePk.find_first_not_of(" \t\r\n"));
                nomProprePk.erase(nomProprePk.find_last_not_of(" \t\r\n") + 1);
                
                if (nomProprePk.empty()) continue;
                
                cout << "   Recherche du Pokémon : '" << nomProprePk << "'" << endl;
                
                for (const auto& p : cataloguePokemon) {
                    if (p && p->getNom() == nomProprePk) {
                        cout << "   ✅ " << nomProprePk << " trouvé et ajouté !" << endl;
                        break;
                    }
                }
            }
            
            fichier.close();
            return true;
        }
        
        compteur++;
    }
    
    cout << "❌ Joueur '" << nomRecherche << "' non trouvé dans le fichier." << endl;
    fichier.close();
    return false;
}
void Sauvegarde::sauvegarderPartie(const Joueur& joueur, Entraineur* dernier_leader_battu) {
    assurerDossierSauvegarde();
    
    try {
        // Sauvegarder dans joueur.csv
        sauvegarderJoueur(joueur);
        
        // Sauvegarder le leader battu
        if (dernier_leader_battu) {
            sauvegarderLeaderBattu(joueur, dernier_leader_battu);
        }
    } catch (const exception& e) {
        cerr << "Erreur lors de la sauvegarde: " << e.what() << endl;
    }
}
// Fonction de chargement simplifiée
bool Sauvegarde::chargerPartie(Joueur& joueur, const vector<Pokemon*>& cataloguePokemon) {
    try {
        // Charger depuis joueur.csv
        return chargerJoueur(joueur, cataloguePokemon, -1);
    } catch (const exception& e) {
        cerr << "Erreur lors du chargement: " << e.what() << endl;
        return false;
    }
}
// Réinitialiser les fichiers pour une nouvelle partie
void Sauvegarde::reinitialisationNouvellePartie() {
    assurerDossierSauvegarde();
    
    try {
        ofstream fichierLeaders(FICHIER_LEADERS_BATTUS, ios::trunc);
        if (fichierLeaders.is_open()) {
            fichierLeaders.close();
        }
        ofstream fichierMaitres(FICHIER_MAITRES_BATTUS, ios::trunc);
        if (fichierMaitres.is_open()) {
            fichierMaitres.close();
        }
        vector<string> lignes = lireLignesJoueur();
        
        if (!lignes.empty()) {
            vector<string> lignesMises;
            lignesMises.push_back(lignes[0]);
            
            // Traiter chaque joueur (à partir de la ligne 1)
            for (size_t i = 1; i < lignes.size(); ++i) {
                stringstream ss(lignes[i]);
                string nom;
                vector<string> nomsPokemon(6);
                
                // Lire le nom et les Pokémon
                getline(ss, nom, ',');
                for (int j = 0; j < 6; ++j) {
                    getline(ss, nomsPokemon[j], ',');
                }
                
                // Reconstruire la ligne avec stats remises à zéro
                stringstream nouvelleLigne;
                nouvelleLigne << nom;
                
                // Réécrire les Pokémon
                for (int j = 0; j < 6; ++j) {
                    nouvelleLigne << "," << nomsPokemon[j];
                }
                
                // Ajouter les stats remises à zéro
                nouvelleLigne << ",0,0,0"; // badges,victoires,defaites = 0
                
                lignesMises.push_back(nouvelleLigne.str());
            }
            
            // Réécrire le fichier avec les stats remises à zéro
            ecrireLignesJoueur(lignesMises);
            
            cout << "✅ Toutes les statistiques des joueurs ont été remises à zéro." << endl;
        }
        
        cout << "Nouvelle partie : les fichiers de sauvegarde ont été réinitialisés." << endl;
    } catch (const exception& e) {
        cerr << "Erreur lors de la réinitialisation: " << e.what() << endl;
    }
}