/*
 * DÉFINITION DES FONCTIONS D'AFFICHAGE
*/

#include "affichage.h"

SDL_Window* create_window_secure()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) // Tentative d'initialisation du système graphique
	{
			printf("error initializing SDL: %s\n", SDL_GetError());
			exit(0);
	}

	// Création de la fenêtre de jeu
	Uint32 WINDOW_FLAGS = 0;
	SDL_Window* window = SDL_CreateWindow("ABALONE",
																		 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
																		 WINDOW_W, WINDOW_H, WINDOW_FLAGS);
	if (!window) // Si la fenêtre de jeu n'est pas créée, on renvoie une erreur et on quitte
	{
		printf("error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(0);
	}

	return window;
}
	
SDL_Renderer* create_renderer_secure(SDL_Window* window)
{
	Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* rend = SDL_CreateRenderer(window, -1, renderFlags);
	if (!rend) // Si le renderer n'est pas créé, on renvoie une erreur et on quitte
	{
		printf("error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	return rend;
}

SDL_Texture* display_image_secure(SDL_Window* window, SDL_Renderer* rend, const char* path, SDL_Rect* part, SDL_Rect* destSprite, SDL_bool refreshScreen)
{
	// Chargement des images en mémoire, gâce à la bibliothèque SDL_Image
	SDL_Surface* surface = IMG_Load(path);
	if(!surface)
	{
		printf("error creating surface\n");
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(0);
	}
	
	// Chargement des images dans la mémoire du matériel graphique
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
	if (!texture) // Si la création de textures échoue, on renvoie une erreur et on quitte
	{
			printf("error creating texture: %s\n", SDL_GetError());
			SDL_DestroyRenderer(rend);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);
	}
	SDL_FreeSurface(surface); // Libération des surfaces, car on ne travaille que sur les textures

	//SDL_RenderClear(rend);
	SDL_RenderCopy(rend, texture, part, destSprite);
	if(refreshScreen)
		SDL_RenderPresent(rend);

	return texture;
}



void update_ballsprites(SDL_Window** window, SDL_Renderer** rend, CASE board[L][C])
{
	SDL_Rect gameScreenSprite, ballSprite;
	unsigned int xOffset = (float)278*WINDOW_W/1920, yOffset = (float)185*WINDOW_H/1080, i, j; // Décalages horzintal et vertical, et indices
	ballSprite.h = ballSprite.w = 45;
	ballSprite.x = xOffset;
	ballSprite.y = yOffset;
	gameScreenSprite.w = WINDOW_W;
	gameScreenSprite.h = WINDOW_H;
	gameScreenSprite.x = gameScreenSprite.y = 0;
	
	display_image_secure(*window, *rend, "images/ecran_jeu.png", NULL, &gameScreenSprite, SDL_FALSE);
	const char* ballImagePath = NULL;
	for(i = 0; i < L; i++)
	{
		for (j = 0; j < C; j++)
		{
			if (board[i][j] != NDEF && board[i][j] != VIDE)
			{
				switch (board[i][j])
				{
					case N :
						ballImagePath = "images/bille_noire.png";
						break;
					case R :
						ballImagePath = "images/bille_rouge.png";
						break;
					case B :
						ballImagePath = "images/bille_blanche.png";
						break; 
					default :
						break;
				}
				ballSprite.x = xOffset + 28*j; // L'abscisse correspond à la colonne
				ballSprite.y = yOffset + 50*i; // L'ordonnée correspond à la ligne
				display_image_secure(*window, *rend, ballImagePath, NULL, &ballSprite, SDL_FALSE); // Affichage de la bille sans mettre à jour l'écran
			}
		}
	}

	SDL_RenderPresent(*rend); // Changement de tampon (mise à jour de l'écran)

	return;
}

/*
SDL_Texture* draw_board_secure(SDL_Window* window, SDL_Renderer* rend)
{
	// Chargement des images en mémoire, gâce à la bibliothèque SDL_Image
	SDL_Surface* cellSurface = IMG_Load("images/cellule.png"),
						 * bgSurface = IMG_Load("images/fond_plateau.png");
	if(!cellSurface || !bgSurface)
	{
		printf("error creating surface\n");
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	
	// Chargement des images dans la mémoire du matériel graphique
	SDL_Texture* cellTexture = SDL_CreateTextureFromSurface(rend, cellSurface),
						 * bgTexture = SDL_CreateTextureFromSurface(rend, bgSurface);
	if (!cellTexture || !bgTexture) // Si la création de textures échoue, on renvoie une erreur et on quitte
	{
			printf("error creating texture: %s\n", SDL_GetError());
			SDL_DestroyRenderer(rend);
			SDL_DestroyWindow(window);
			SDL_Quit();
	}
	SDL_FreeSurface(cellSurface); // Libération des surfaces, car on ne travaille que sur les textures
	SDL_FreeSurface(bgSurface);

	// Structures qui contiendront les positions et tailles des sprites
	SDL_Rect cellSprite, boardSprite;
	// Le sprite du plateau et le nombre de cases détermineront la taille de chaque sprite cellule
	boardSprite.w = 800;
	boardSprite.h = 600;
	boardSprite.x = boardSprite.y = 0;
	
	cellSprite.w = 400;
	cellSprite.h = 400;
	cellSprite.x = cellSprite.y = 0;

	// Dessin (affichage) du plateau dans la fenêtre de jeu
	SDL_RenderClear(rend); // Nettoie (noircit) la fenêtre
	SDL_RenderCopy(rend, bgTexture, NULL, &boardSprite);
	SDL_RenderCopy(rend, cellTexture, NULL, &cellSprite);
	cellSprite.x = 200; // Décalage du sprite ver la droite de la fenêtre
	cellSprite.y = 346; // Décalage du sprite vers le bas de la fenêtre
	SDL_RenderCopy(rend, cellTexture, NULL, &cellSprite);
	SDL_RenderPresent(rend); // Bascule le tampon en cours
	

	unsigned int i, j; // Compteurs
	for(j = 0; j < 9; j++)
	{
		for(i = 0; i < 9; i++)
		{
			SDL_RenderCopy(rend, cellTexture, NULL, &cellSprite);
			cellSprite.x += (float)69.5/100 * cellSprite.w; // Décalage du sprite ver la droite de la fenêtre
		}
		SDL_RenderPresent(rend); // Bascule le tampon en cours
		cellSprite.x = 50 + cellSprite.w/2;
		cellSprite.y += cellSprite.h/2; // Décalage du sprite vers le bas de la fenêtre
	}

	return cellTexture;
}
*/
