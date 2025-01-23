// Automate.h
#pragma once
#include <stack>
#include <iostream>
#include "symbole.h"
#include "lexer.h"

// Déclaration de la classe Etat
class Etat;

// On peut se créer un petit enum pour identifier les différentes réductions
enum ReductionRule {
   R_E_VAL,      // E -> val
   R_E_PAR_E,    // E -> (E)
   R_E_E_PLUS_E, // E -> E + E
   R_E_E_MULT_E  // E -> E * E
};

class Automate {
public:
   Automate(const std::string & chaine) 
      : lexer(chaine), finished(false), accepted(false) {}

   ~Automate();

   // Lance l'analyse
   void run();

   // Méthodes invoquées par les Etats
   void decalage(Symbole * s, Etat * e);           // SHIFT
   void reduction(int nbSymboles, ReductionRule r); // REDUCE
   void accepter(); // ACCEPT → permet de sortir de run()

   // Accès au symbole courant du lexer
   Symbole* getNextSymbole() { return lexer.Consulter(); }
   void avancer() { lexer.Avancer(); }

   // Accès aux piles
   std::stack<Etat*> & getStateStack() { return stateStack; }
   std::stack<Symbole*> & getSymbolStack() { return symbolStack; }

   bool isAccepted() const { return accepted; }

private:
   Lexer lexer;
   std::stack<Symbole*> symbolStack;  
   std::stack<Etat*> stateStack;      
   bool finished;                     
   bool accepted; // pour distinguer une fin d'analyse réussie (ACCEPT) d'une erreur
};
