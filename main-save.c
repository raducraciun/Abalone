#include "abalone.h"
#include "affichage.h"
#include "calculs.h"
#include "controles.h"

int main()
{
	CASE board[L][C] = {
	{NDEF, NDEF, NDEF, NDEF, B, NDEF, B, NDEF, B, NDEF, B, NDEF, B, NDEF, NDEF, NDEF, NDEF},
	{NDEF, NDEF, NDEF, B, NDEF, B, NDEF, B, NDEF, B, NDEF, B, NDEF, B, NDEF, NDEF, NDEF},
	{NDEF, NDEF, VIDE, NDEF, VIDE, NDEF, B, NDEF, B, NDEF, B, NDEF, VIDE, NDEF, VIDE, NDEF, NDEF},
	{NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF},
	{R, NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF, R, NDEF, R},
	{NDEF, VIDE, NDEF, VIDE, NDEF, VIDE, NDEF, VIDE, NDEF, VIDE, NDEF, VIDE, NDEF, VIDE, NDEF, VIDE, NDEF},
	{NDEF, NDEF, VIDE, NDEF, VIDE, NDEF, N, NDEF, N, NDEF, N, NDEF, VIDE, NDEF, VIDE, NDEF, NDEF},
	{NDEF, NDEF, NDEF, N, NDEF, N, NDEF, N, NDEF, N, NDEF, N, NDEF, N, NDEF, NDEF, NDEF},
	{NDEF, NDEF, NDEF, NDEF, N, NDEF, N, NDEF, N, NDEF, N, NDEF, N, NDEF, NDEF, NDEF, NDEF}};
	
	SDL_Window* gameWindow = create_window_secure();
	SDL_Renderer* rend = create_renderer_secure(gameWindow);

	SDL_Rect homeScreenSprite, gameScreenSprite, arrowSprites[6], selectionRingSprite;
	homeScreenSprite.h = WINDOW_H;
	homeScreenSprite.w = WINDOW_W;
	homeScreenSprite.x = homeScreenSprite.y = 0;
	gameScreenSprite.w = WINDOW_W;
	gameScreenSprite.h = WINDOW_H;
	gameScreenSprite.x = gameScreenSprite.y = 0;
	set_arrowsprites(arrowSprites);
	selectionRingSprite.h = selectionRingSprite.w = 50;
	
	SDL_RenderClear(rend); // Nettoie (noircit) la fenêtre
	SDL_Texture* backgroundTexture = display_image_secure(gameWindow, rend, "images/fond_plateau.png", NULL, &homeScreenSprite, SDL_FALSE),
						 * homeScreenTexture = display_image_secure(gameWindow, rend, "images/ecran_accueil.png", NULL, &homeScreenSprite, SDL_FALSE),
						 * gameScreenTexture = display_image_secure(gameWindow, rend, "images/ecran_jeu.png", NULL, &gameScreenSprite, SDL_TRUE),
						 * ballTexture;

	update_ballsprites(&gameWindow, &rend, board);

	int mouseX, mouseY;// Position de la souris relativement à la fenêtre
	SDL_Event event;
	SDL_bool closeRequested = SDL_FALSE; // Passe à Vrai lorsqu'on ferme la fenêtre
	while (!closeRequested)
	{
		// Gestion d'évènements
		while (SDL_PollEvent(&event)) // Fonction non blocante
		{
			switch(event.type)
			{
				case SDL_QUIT:
					closeRequested = SDL_TRUE;
					break;
					
				case SDL_MOUSEBUTTONDOWN: // Au changement d'un boouton sur la souris
					if(SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) // Si c'est le bouton gauche qui est cliqué
					{
						// Disque de sélection autour de la bille à sélectionner
						selectionRingSprite.x = mouseX - selectionRingSprite.w/2;
						selectionRingSprite.y = mouseY - selectionRingSprite.h/2;
						printf("i = %d\n"
									 "j = %d\n", (mouseX - 278*WINDOW_W/1920)/28, (mouseY - 185*WINDOW_H/1080)/50);
						display_image_secure(gameWindow, rend, "images/anneau_vert.png", NULL, &selectionRingSprite, SDL_TRUE);
					}
					break;
					
				default :
					break;
			}
		}
	}

	SDL_DestroyTexture(gameScreenTexture);
	SDL_DestroyTexture(homeScreenTexture);
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
	
	return EXIT_SUCCESS;
}

