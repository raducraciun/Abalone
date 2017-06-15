/* DÉFINITION DES FONCTIONS DE CONTROLE */

#include "controles.h"


SDL_bool point_is_in_rectangle(SDL_Point point, SDL_Rect rectangle)
{
	return (((point.x >= rectangle.x) && (point.x <= rectangle.x + rectangle.w)
			 && (point.y >= rectangle.y) && (point.y <= rectangle.y + rectangle.h)) ? SDL_TRUE : SDL_FALSE);
}

void set_playmode_sprites(SDL_Rect playModeSprites[3])
{
	float horizScaleFactor = (float)WINDOW_W/1920, vertScaleFactor = (float)WINDOW_H/1080; //Facteurs de mise à l'échelle
	unsigned int i;

	for(i = 0; i < 3; i++) // Tous les sprites des flèches ont les mêmes dimensions
	{
		playModeSprites[i].w = 570 * horizScaleFactor;
		playModeSprites[i].h = 75 * vertScaleFactor;
	}
	
	playModeSprites[J2].x = 690 * horizScaleFactor; playModeSprites[J2].y = 480 * vertScaleFactor;
	playModeSprites[J3].x = 690 * horizScaleFactor; playModeSprites[J3].y = 600 * vertScaleFactor;
	playModeSprites[IA].x = 690 * horizScaleFactor; playModeSprites[IA].y = 720 * vertScaleFactor;

	return;
}

void set_arrows_sprites(SDL_Rect arrowSprites[6])
{
	float horizScaleFactor = (float)WINDOW_W/1920, vertScaleFactor = (float)WINDOW_H/1080; //Facteurs de mise à l'échelle
	unsigned int i;

	for(i = 0; i < 6; i++) // Tous les sprites des flèches ont les mêmes dimensions
	{
		arrowSprites[i].w = 85 * horizScaleFactor;
		arrowSprites[i].h = 85 * vertScaleFactor;
	}
	
	arrowSprites[HG].x 		= 1485 * horizScaleFactor; arrowSprites[HG].y 	 = 690 * vertScaleFactor;
	arrowSprites[HD].x 	= 1650 * horizScaleFactor; arrowSprites[HD].y 	 = 690 * vertScaleFactor;
	arrowSprites[G].x 			= 1420 * horizScaleFactor; arrowSprites[G].y 		 = 770 * vertScaleFactor;
	arrowSprites[D].x 		= 1710 * horizScaleFactor; arrowSprites[D].y 		 = 770 * vertScaleFactor;
	arrowSprites[BG].x 	= 1485 * horizScaleFactor; arrowSprites[BG].y  = 855 * vertScaleFactor;
	arrowSprites[BD].x = 1650 * horizScaleFactor; arrowSprites[BD].y = 855 * vertScaleFactor;

	return;
}
