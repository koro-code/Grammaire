#pragma once

#include <string>
using namespace std;

// On conserve votre énumération :
enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, ERREUR, E };

const string Etiquettes[] = { "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "ERREUR" };

class Symbole {
public:
   Symbole(int i) : ident(i) { }
   virtual ~Symbole() { }
   operator int() const { return ident; }
   virtual void Affiche();

protected:
   int ident;
};

class Entier : public Symbole {
public:
   Entier(int v) : Symbole(INT), valeur(v) { }
   ~Entier() { }
   virtual void Affiche();
   int valeur;  // Rendu public pour faciliter l'accès dans l'exemple
};

//////////////////////////////////////////////////////////////////////////
// Nouvelle classe pour le non-terminal E qui stocke la valeur calculée
//////////////////////////////////////////////////////////////////////////
class Expr : public Symbole {
public:
   Expr(int v) : Symbole(E), valeur(v) { }
   virtual ~Expr() { }
   
   int getValeur() const { return valeur; }

   // Si besoin, on peut avoir un setValeur(...)
   // void setValeur(int v) { valeur = v; }

protected:
   int valeur;
};
