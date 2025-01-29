# Variables
CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -g
SRC = main.cpp automate.cpp etats.cpp lexer.cpp symbole.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = lalr

# Règle principale
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Compilation des fichiers objets
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)

# Nettoyage complet
mrproper: clean
	rm -f *~
