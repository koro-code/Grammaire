#include "symbole.h"
#include <iostream>

void Symbole::Affiche() {
   // Si le symbole est dans la plage de Etiquettes, on affiche son étiquette
   if (ident >= 0 && ident < 7) {
      cout << Etiquettes[ident];
   } else if (ident == E) {
      cout << "E";
   } else {
      cout << "UNKNOWN";
   }
}

void Entier::Affiche() {
   Symbole::Affiche();
   cout << "(" << valeur << ")";
}
