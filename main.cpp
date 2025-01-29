#include <iostream>
#include <vector>
#include "automate.h"
#include "symbole.h" // Pour faire un cast si besoin

// need to put --std=c++11 when compiling with following command : g++ --std=c++11 main.cpp automate.cpp etats.cpp lexer.cpp symbole.cpp -o executeAutomate

int main()
{
   // Liste d'expressions à tester
   std::vector<std::string> expressions = {
       "(1+34)*123", // valide
       "(1+2)*3+4",  // valide
       "(1+2*3)",    // valide
       "((4+5)*6)",  // valide
       "(42)",       // valide
       "1+2*3",      // valide
       "1+*3",       // invalide (symbole * inattendu)
       "((1+2)",     // invalide (parenthèse fermante manquante)
       "(1+2))",     // invalide (parenthèse en trop)
       "(1+(2*3)"    // invalide (parenthèse fermante manquante)
   };

   for (auto &expr : expressions)
   {
      std::cout << "-------------------------------\n";
      std::cout << "Analyse de : " << expr << "\n";
      std::cout << "-------------------------------\n";

      // Construire et lancer l'automate
      Automate automate(expr);
      automate.run();

      if (automate.isAccepted())
      {
         // Le sommet de la pile contient l'expression finale
         std::stack<Symbole *> &pile = automate.getSymbolStack();
         if (!pile.empty())
         {
            Symbole *topSym = pile.top();
            if ((int)*topSym == E)
            {
               Expr *exprFinal = dynamic_cast<Expr *>(topSym);
               if (exprFinal)
               {
                  std::cout << "Resultat du calcul = "
                            << exprFinal->getValeur() << "\n";
               }
            }
         }
      }
      else
      {
         std::cout << "L'expression est invalide.\n";
      }

      std::cout << "Analyse terminee.\n\n";
   }

   return 0;
}
