// interface.hpp
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>
#include <vector>
#include "pokemon.hpp"
#include "entraineur.hpp"
#include "combat.hpp"

// Namespace pour les couleurs ANSI
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

// Fonctions utilitaires
void clearScreen();
void typingEffect(const std::string& text, int delayMs = 30);
void showDialogBox(const std::string& text);
void waitForEnter();

// Affichage des Pokémon
void showHPBar(const std::string& name, int current, int max, int width = 20);
void showPokemonCard(const Pokemon* pokemon);
void showPokemonList(const Entraineur* entraineur);

// Écrans principaux
void showTitleScreen();
void showBattleScreen(const Pokemon* playerPokemon, const Pokemon* enemyPokemon);
void showAttackAnimation(const std::string& attackName, int damage, bool isSuperEffective);

// Interface utilisateur améliorée
void menuPrincipal(Joueur* joueur, std::vector<Entraineur*> leaders, std::vector<Entraineur*> maitres);
void menuCombat(Joueur& joueur, Entraineur& adversaire);

// 💥 Déclaration ajoutée ici pour résoudre l'erreur dans combat.cpp
void choisirPokemonActif(Joueur& joueur);

#endif
