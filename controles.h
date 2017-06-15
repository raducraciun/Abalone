/* EN-TÊTES DES FONCTIONS DE CONTROLE */


#ifndef _CONTROLES_H
	#define _CONTROLES_H
	#include "abalone.h"

	SDL_bool point_is_in_rectangle(SDL_Point point, SDL_Rect rectangle);
	void set_playmode_sprites(SDL_Rect playModeSprites[3]);
	void set_arrows_sprites(SDL_Rect arrowSprites[6]);
	
#endif // _CONTROLES_H
