#pragma once
#include "Automate.h"
#include "symbole.h"
#include <iostream>
#include <string>

// ======================
// Forward declarations
// ======================
class Etat0;
class Etat1;
class Etat2;
class Etat3;
class Etat4;
class Etat5;
class Etat6;
class Etat7;
class Etat8;
class Etat9;

// ======================
//  Base class: Etat
// ======================
class Etat {
public:
   Etat(const std::string & name) : name(name) {}
   virtual ~Etat() {}

   virtual bool transition(Automate & automate, Symbole * s) = 0;
   std::string getName() const { return name; }

protected:
   std::string name;
};

// ======================
//  Definitions des Etats
// ======================
class Etat0 : public Etat {
public:
   Etat0() : Etat("E0") {}
   virtual ~Etat0() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat1 : public Etat {
public:
   Etat1() : Etat("E1") {}
   virtual ~Etat1() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat2 : public Etat {
public:
   Etat2() : Etat("E2") {}
   virtual ~Etat2() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat3 : public Etat {
public:
   Etat3() : Etat("E3") {}
   virtual ~Etat3() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat4 : public Etat {
public:
   Etat4() : Etat("E4") {}
   virtual ~Etat4() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat5 : public Etat {
public:
   Etat5() : Etat("E5") {}
   virtual ~Etat5() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat6 : public Etat {
public:
   Etat6() : Etat("E6") {}
   virtual ~Etat6() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat7 : public Etat {
public:
   Etat7() : Etat("E7") {}
   virtual ~Etat7() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat8 : public Etat {
public:
   Etat8() : Etat("E8") {}
   virtual ~Etat8() {}
   bool transition(Automate & automate, Symbole * s);
};

class Etat9 : public Etat {
public:
   Etat9() : Etat("E9") {}
   virtual ~Etat9() {}
   bool transition(Automate & automate, Symbole * s);
};
