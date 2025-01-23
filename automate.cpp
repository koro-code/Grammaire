// Automate.cpp
#include "Automate.h"
#include "Etats.h"
#include <iostream>
#include <vector>
#include <cassert>

Automate::~Automate() {
   // Nettoyage des états
   while (!stateStack.empty()) {
      delete stateStack.top();
      stateStack.pop();
   }
   // Nettoyage des symboles
   while (!symbolStack.empty()) {
      delete symbolStack.top();
      symbolStack.pop();
   }
}

void Automate::run() {
   // On empile l'état initial (Etat0)
   stateStack.push(new Etat0);

   while (!finished) {
      // Symbole courant lu par le lexer
      Symbole * s = getNextSymbole();

      // On appelle la méthode transition de l'état au sommet
      Etat * e = stateStack.top();
      bool res = e->transition(*this, s);

      if (!res) {
         // Erreur de parsing
         std::cerr << "[ERREUR] Symbole inattendu : ";
         s->Affiche(); 
         std::cerr << std::endl;
         finished = true; // On stoppe
      }
   }
}

void Automate::decalage(Symbole* s, Etat* e) {
   std::cout << "[SHIFT] ";
   s->Affiche(); 
   std::cout << " -> " << e->getName() << std::endl;

   // Empilage du symbole
   symbolStack.push(s);
   // Avancer le lexer
   avancer();
   // Empilage de l'état
   stateStack.push(e);
}

void Automate::reduction(int nbSymboles, ReductionRule r) {
   std::cout << "[REDUCE] Règle ";
   switch(r) {
      case R_E_VAL:      std::cout << "E->val";    break;
      case R_E_PAR_E:    std::cout << "E->(E)";    break;
      case R_E_E_PLUS_E: std::cout << "E->E+E";    break;
      case R_E_E_MULT_E: std::cout << "E->E*E";    break;
   }
   std::cout << std::endl;

   // On récupère les symboles à dépiler
   std::vector<Symbole*> symbolsToReduce;
   // On dépile nbSymboles
   for (int i = 0; i < nbSymboles; i++) {
      Symbole* topSym = symbolStack.top();
      symbolStack.pop();
      Etat* topState = stateStack.top();
      stateStack.pop();
      delete topState; // on libère l'état

      symbolsToReduce.push_back(topSym);
   }

   // Calcul du nouveau symbole de type E (avec la valeur calculée)
   Symbole* newSymbol = nullptr;

   switch(r) {
      case R_E_VAL:
      {
         // E -> val (INT)
         // Il y a exactement 1 symbole : l'Entier
         Entier* val = dynamic_cast<Entier*>(symbolsToReduce[0]);
         assert(val != nullptr);
         newSymbol = new Expr(val->valeur);
         break;
      }
      case R_E_PAR_E:
      {
         // E -> ( E ) : 3 symboles : ')' 'E' '(' en ordre de dépilement
         // Or dans la pile, l'ordre est l'inverse de l'entrée : topSym = ')', puis E, puis '('
         // On veut la valeur de E
         Expr* exprInterne = dynamic_cast<Expr*>(symbolsToReduce[1]);
         assert(exprInterne != nullptr);
         newSymbol = new Expr(exprInterne->getValeur());
         break;
      }
      case R_E_E_PLUS_E:
      {
         // E -> E + E : on a dépilé dans l'ordre E (droite), +, E (gauche)
         Expr* right = dynamic_cast<Expr*>(symbolsToReduce[0]);
         Symbole* plus = symbolsToReduce[1]; // on n'a pas forcément besoin du plus
         Expr* left  = dynamic_cast<Expr*>(symbolsToReduce[2]);
         assert(left != nullptr && right != nullptr);

         int res = left->getValeur() + right->getValeur();
         newSymbol = new Expr(res);
         break;
      }
      case R_E_E_MULT_E:
      {
         // E -> E * E : on a dépilé dans l'ordre E (droite), *, E (gauche)
         Expr* right = dynamic_cast<Expr*>(symbolsToReduce[0]);
         Symbole* mult = symbolsToReduce[1];
         Expr* left  = dynamic_cast<Expr*>(symbolsToReduce[2]);
         assert(left != nullptr && right != nullptr);

         int res = left->getValeur() * right->getValeur();
         newSymbol = new Expr(res);
         break;
      }
   }

   // On supprime les anciens symboles
   for (auto sym : symbolsToReduce) {
      delete sym;
   }

   // On empile le nouveau symbole
   symbolStack.push(newSymbol);

   // On déclenche la transition sur l'état courant
   stateStack.top()->transition(*this, newSymbol);
}

void Automate::accepter() {
   finished = true;
   accepted = true;
}
