/*
 * DÉFINITION DES FONCTIONS D'AFFICHAGE
*/
#ifndef _AFFICHAGE_H
	#define _AFFICHAGE_H
	#include "abalone.h"

	SDL_Window* create_window_secure(); // Initialisation de la SDL, chargement du module vidéo et création sécurisée d'une fenêtre
	SDL_Renderer* create_renderer_secure(SDL_Window* window); // Création sécurisée d'un renderer (tampon), ce qui met en place le matériel graphique
	SDL_Texture* display_image_secure(SDL_Window* window, SDL_Renderer* rend, const char* path, SDL_Rect* part, SDL_Rect* destSprite, SDL_bool refreshScreen);
	void update_ballsprites(SDL_Window** window, SDL_Renderer** rend, CASE board[L][C]); // Affiche les billes sur le plateau de jeu
	//SDL_Texture* draw_board_secure(SDL_Window* window, SDL_Renderer* rend); // Génère le plateau de jeu et le renvoie sous forme de texture

	int graphics_test(SDL_Window* window, SDL_Renderer* rend);
#endif // _AFFICHAGE_H
