# compilateur
CC := gcc

# flags du compilateur
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

# en-têtes
HDRS := abalone.h affichage.h calculs.h controles.h main.h

# sources
SRCS := main.c affichage.c calculs.c controles.c

# générer les nom des fichiers objet
OBJS := $(SRCS:.c=.o)

# nom de l'exécutable
EXEC := Abalone

# méthode par défaut
all: $(EXEC)

# créer l'exécutable final
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# créer les fichiers objet
$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# méthode pour nettoyer l'espace de travail
clean:
	rm -f $(EXEC) $(OBJS) 

.PHONY: all clean
