#ifndef _ABALONE_H
	#define _ABALONE_H
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>

	#define True 1
	#define False 0
	#define L 9 // Nombre de lignes du plateau en mémoire
	#define C (9*2-1) // Nombre de colonnes du plateau en mémoire
	#define MAX_SELEC 3 // Nombre maximal de pions sélectionnnables
	#define MIN(X,Y) ((X) < (Y) ? (X) : (Y)) // Minimum entre deux nombres
	#define MAX(X,Y) ((X) > (Y) ? (X) : (Y)) // Maximum entre deux nombres
	#define WINDOW_W 1200
	#define WINDOW_H 675

	typedef struct {int x,y;} COORDS;
	typedef enum {B, N, VIDE, NDEF, R} CASE;
	typedef enum {BLANC, NOIR, ROUGE} JOUEUR;
	typedef enum {G, HG, HD, D, BD, BG} DIRECTION;
	typedef enum {J2, J3, IA} MODE;
	typedef enum {INLINE, BROADSIDE} MVTYPE;
	typedef enum {LIGNE, DIAGONALE_G, DIAGONALE_D} ORIENTATION;
	typedef enum {SUMITO2vs1, SUMITO3vs1, SUMITO3vs2} SUMITOTYPE;

	// Liste chainee de tableau de Coords

	typedef struct element element;
	struct element
	{
		COORDS tuple[3];
		struct element *next;
	};
	typedef element* liste;

#endif // _ABALONE_H
