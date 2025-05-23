#include "entraineur.hpp"
#include <iostream>

Entraineur::Entraineur(const std::string& nom) : nom(nom), indexPokemonActif(0) {}
Entraineur::~Entraineur() {
    for (auto creature : equipe) {
        delete creature;
    }
}
void Entraineur::ajouterPokemon(Pokemon* nouveau) {
    equipe.push_back(nouveau);
}
Pokemon* Entraineur::pokemonActif(int index) const {
    if (equipe.empty()) return nullptr;
    if (index == -1) {
        return equipe[indexPokemonActif];
    } else if (index >= 0 && index < static_cast<int>(equipe.size())) {
        return equipe[index];
    }
    return nullptr;
}
bool Entraineur::touteEquipeKO() const {
    for (const auto& p : equipe) {
        if (!p->estKo()) return false;
    }
    return true;
}
void Entraineur::selectionnerPokemon(int nouvelIndex) {
    if (nouvelIndex >= 0 && nouvelIndex < static_cast<int>(equipe.size()) && !equipe[nouvelIndex]->estKo()) {
        indexPokemonActif = nouvelIndex;
    }
}
void Entraineur::soignerEquipe() {
    for (auto& p : equipe) {
        p->restaurerPV();
    }
    std::cout << "\nTous les Pokémon de l'équipe ont été soignés !\n";
}
void Entraineur::viderEquipe() {
    for (auto& p : equipe) {
        delete p;
    }
    equipe.clear();
    indexPokemonActif = 0;
}
void Entraineur::afficherEquipe() const {
    std::cout << "Composition de l'equipe de " << nom << " :\n";
    for (size_t i = 0; i < equipe.size(); ++i) {
        std::cout << (i + 1) << ". " << equipe[i]->getNom() << " ["
                  << equipe[i]->getType1();
        if (!equipe[i]->getType2().empty()) {
            std::cout << "/" << equipe[i]->getType2();
        }
        std::cout << "] HP: " << equipe[i]->getHp() << "/" << equipe[i]->getMaxHp()<< "\n";
    }
}
void Entraineur::echangerPokemon(int index1, int index2) {
    if (index1 >= 0 && index1 < static_cast<int>(equipe.size()) &&
        index2 >= 0 && index2 < static_cast<int>(equipe.size())) {
        std::swap(equipe[index1], equipe[index2]);
        std::cout << "✅ Les Pokémon ont été échangés avec succès.\n";
    } else {
        std::cout << "❌ Indices invalides. Aucun échange effectué.\n";
    }
}
Joueur::Joueur(const std::string& nom) : Entraineur(nom), nombreBadges(0), totalVictoires(0), totalDefaites(0) {}
void Joueur::incrementerBadge() {
    ++nombreBadges;
}
void Joueur::enregistrerVictoire() {
    ++totalVictoires;
}
void Joueur::enregistrerDefaite() {
    ++totalDefaites;
}
void Joueur::afficherStats() const {
    std::cout << "\nStatistiques de " << nom << " :\n"
              << "Badges obtenus     : " << nombreBadges << "\n"
              << "Victoires totales  : " << totalVictoires << "\n"
              << "Defaites totales   : " << totalDefaites << "\n";
}
LeaderGym::LeaderGym(const std::string& nom, const std::string& gym, const std::string& medaille)
    : Entraineur(nom), nomGym(gym), recompenseMedaille(medaille) {}
MaitrePokemon::MaitrePokemon(const std::string& nom) : Entraineur(nom) {}
int MaitrePokemon::appliquerBonusDegats(int degatsDeBase) const {
    return static_cast<int>(degatsDeBase * 1.25);
}
void Joueur::enregistrerVaincu(Entraineur* adversaire) {
    adversairesVaincus.push_back(adversaire);
}
void Joueur::interagirAvecVaincus() const {
    if (adversairesVaincus.empty()) {
        std::cout << "Vous n'avez vaincu aucun entraîneur pour le moment.\n";
        return;
    }
    std::cout << "Interactions avec les entraîneurs vaincus :\n";
    for (const auto& adv : adversairesVaincus) {
        std::cout << "- " << adv->interaction() << std::endl;
    }
}
std::string Entraineur::interaction() const {
    return nom + " vous observe calmement.";
}
std::string Joueur::interaction() const {
    return nom + " dit : \"Je suis prêt à tout pour devenir Maître Pokémon !\"";
}
std::string LeaderGym::interaction() const {
    return nom + " dit : \"Tu m'as battu, mais d'autres épreuves t'attendent.\"";
}
std::string MaitrePokemon::interaction() const {
    return nom + " dit : \"Félicitations, tu es digne de la Ligue Pokémon.\"";
}