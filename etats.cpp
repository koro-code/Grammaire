#include "etats.h"
#include "Automate.h"
#include "symbole.h"
#include <iostream>

// ---------- Etat0 ----------
bool Etat0::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case INT:
         automate.decalage(s, new Etat3);
         return true;

      case OPENPAR:
         automate.decalage(s, new Etat2);
         return true;

      case E: // goto Etat1
         automate.getStateStack().push(new Etat1);
         return true;

      default:
         return false;
   }
}

// ---------- Etat1 ----------
bool Etat1::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case PLUS:
         automate.decalage(s, new Etat4);
         return true;
      case MULT:
         automate.decalage(s, new Etat5);
         return true;
      case FIN:
         // On accepte
         automate.accepter();
         return true;
      default:
         return false;
   }
}

// ---------- Etat2 ----------
bool Etat2::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case INT:
         automate.decalage(s, new Etat3);
         return true;
      case OPENPAR:
         automate.decalage(s, new Etat2);
         return true;
      case E:
         automate.getStateStack().push(new Etat6);
         return true;
      default:
         return false;
   }
}

// ---------- Etat3 ----------
bool Etat3::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case PLUS:
      case MULT:
      case CLOSEPAR:
      case FIN:
         // reduce E->val (taille 1)
         automate.reduction(1, R_E_VAL);
         return true;
      default:
         return false;
   }
}

// ---------- Etat4 ----------
bool Etat4::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case INT:
         automate.decalage(s, new Etat3);
         return true;
      case OPENPAR:
         automate.decalage(s, new Etat2);
         return true;
      case E:
         automate.getStateStack().push(new Etat7);
         return true;
      default:
         return false;
   }
}

// ---------- Etat5 ----------
bool Etat5::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case INT:
         automate.decalage(s, new Etat3);
         return true;
      case OPENPAR:
         automate.decalage(s, new Etat2);
         return true;
      case E:
         automate.getStateStack().push(new Etat8);
         return true;
      default:
         return false;
   }
}

// ---------- Etat6 ----------
bool Etat6::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case PLUS:
         automate.decalage(s, new Etat4); 
         return true;

      case MULT:
         automate.decalage(s, new Etat5);
         return true;

      case CLOSEPAR:
         automate.decalage(s, new Etat9);
         return true;

      default:
         return false;
   }
}

// ---------- Etat7 ----------
bool Etat7::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case PLUS:
      case CLOSEPAR:
      case FIN:
         // reduce E->E+E (3 symboles)
         automate.reduction(3, R_E_E_PLUS_E);
         return true;

      case MULT:
         // on SHIFT -> Etat5 (pour gérer la priorité du '*')
         automate.decalage(s, new Etat5);
         return true;
      default:
         return false;
   }
}

// ---------- Etat8 ----------
bool Etat8::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case PLUS:
      case MULT:
      case CLOSEPAR:
      case FIN:
         // reduce E->E*E (3 symboles)
         automate.reduction(3, R_E_E_MULT_E);
         return true;
      default:
         return false;
   }
}

// ---------- Etat9 ----------
bool Etat9::transition(Automate & automate, Symbole * s) {
   switch (*s) {
      case PLUS:
      case MULT:
      case CLOSEPAR:
      case FIN:
         // reduce E->(E) (3 symboles)
         automate.reduction(3, R_E_PAR_E);
         return true;
      default:
         return false;
   }
}
