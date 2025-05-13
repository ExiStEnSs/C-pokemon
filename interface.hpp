#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <string>
#include <vector>
#include "pokemon.hpp"
#include "entraineur.hpp"
#include "combat.hpp"

Joueur* creerJoueurDepuisCSV(const std::string& chemin, const std::vector<Pokemon*>& reference, int index);
namespace Color {
    extern const std::string RESET;
    extern const std::string RED;
    extern const std::string GREEN;
    extern const std::string YELLOW;
    extern const std::string BLUE;
    extern const std::string MAGENTA;
    extern const std::string CYAN;
    extern const std::string WHITE;
    extern const std::string BOLD;
}
void clearScreen();
void typingEffect(const std::string& text, int delayMs = 30);
void showDialogBox(const std::string& text);
void waitForEnter();
void showPokemonList(const Entraineur* entraineur);
void showTitleScreen();
void menuPrincipal(Joueur* joueur, std::vector<Entraineur*> leaders, std::vector<Entraineur*> maitres, std::vector<Pokemon*>& cataloguePokemon);
void menuCombat(Joueur& joueur, Entraineur& adversaire);
void menuChoixLeader(Joueur& joueur, std::vector<Entraineur*>& leaders);
void afficherLeadersBattus();
void menuSauvegardeChargement(Joueur& joueur, std::vector<Pokemon*>& cataloguePokemon, std::vector<Entraineur*>& leaders, std::vector<Entraineur*>& maitres);
void menuGestionEntraineur(Joueur*& joueur, std::vector<Pokemon*>& cataloguePokemon);
void menuInteraction(Joueur& joueur, std::vector<Entraineur*>& leaders, std::vector<Entraineur*>& maitres);
#endif