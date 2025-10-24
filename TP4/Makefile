# Makefile pour le projet Arbres Binaires de Recherche

CC = gcc
CFLAGS = -Wall -Wextra -g -O2
LDFLAGS = -lm
TARGET = abr
PYTHON = python3

# Fichiers sources
SOURCES = main.c types_abr.c abr_operations.c abr_parcours.c abr_affichage.c
HEADERS = types_abr.h abr_operations.h abr_parcours.h abr_affichage.h
OBJECTS = $(SOURCES:.c=.o)

# Couleurs pour l'affichage
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m # No Color

# Règle par défaut
all: $(TARGET)
	@echo "$(GREEN)✓ Compilation réussie : $(TARGET)$(NC)"

# Compilation de l'exécutable
$(TARGET): $(OBJECTS)
	@echo "$(BLUE)Linking...$(NC)"
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers objets
%.o: %.c $(HEADERS)
	@echo "$(BLUE)Compilation de $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

# Exécuter le programme
run: $(TARGET)
	@echo "$(GREEN)=== Exécution du programme ===$(NC)"
	./$(TARGET)

# Générer les graphiques
graphiques: resultats_abr.csv
	@echo "$(GREEN)=== Génération des graphiques ===$(NC)"
	$(PYTHON) generer_graphiques_abr.py

# Pipeline complet : compiler, exécuter, générer graphiques
full: clean all
	@echo "$(GREEN)=== Exécution complète ===$(NC)"
	./$(TARGET)
	@echo ""
	@echo "$(GREEN)=== Génération des graphiques ===$(NC)"
	$(PYTHON) generer_graphiques_abr.py

# Nettoyer les fichiers compilés
clean:
	@echo "$(RED)Nettoyage des fichiers objets et exécutable...$(NC)"
	rm -f $(OBJECTS) $(TARGET)
	@echo "$(GREEN)✓ Nettoyage terminé$(NC)"

# Nettoyer tout (y compris les résultats)
cleanall: clean
	@echo "$(RED)Suppression des résultats et graphiques...$(NC)"
	rm -f resultats_abr.csv *.png
	@echo "$(GREEN)✓ Tous les fichiers générés supprimés$(NC)"

# Vérifier les dépendances Python
check-python:
	@echo "$(BLUE)Vérification des dépendances Python...$(NC)"
	@$(PYTHON) -c "import pandas" 2>/dev/null || \
		(echo "$(RED)✗ pandas non installé$(NC)" && \
		 echo "  Installez avec: pip3 install pandas")
	@$(PYTHON) -c "import matplotlib" 2>/dev/null || \
		(echo "$(RED)✗ matplotlib non installé$(NC)" && \
		 echo "  Installez avec: pip3 install matplotlib")
	@$(PYTHON) -c "import numpy" 2>/dev/null || \
		(echo "$(RED)✗ numpy non installé$(NC)" && \
		 echo "  Installez avec: pip3 install numpy")
	@echo "$(GREEN)✓ Toutes les dépendances sont installées$(NC)"

# Afficher l'aide
help:
	@echo "$(BLUE)========================================$(NC)"
	@echo "$(GREEN)Commandes disponibles :$(NC)"
	@echo "$(BLUE)========================================$(NC)"
	@echo "  $(GREEN)make$(NC)              - Compiler le projet"
	@echo "  $(GREEN)make run$(NC)          - Compiler et exécuter"
	@echo "  $(GREEN)make graphiques$(NC)   - Générer les graphiques (nécessite resultats_abr.csv)"
	@echo "  $(GREEN)make full$(NC)         - Tout : compiler, exécuter, graphiques"
	@echo "  $(GREEN)make clean$(NC)        - Supprimer les fichiers compilés"
	@echo "  $(GREEN)make cleanall$(NC)     - Supprimer tous les fichiers générés"
	@echo "  $(GREEN)make check-python$(NC) - Vérifier les dépendances Python"
	@echo "  $(GREEN)make help$(NC)         - Afficher cette aide"
	@echo "$(BLUE)========================================$(NC)"

.PHONY: all run graphiques full clean cleanall check-python help
