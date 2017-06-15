#include <stdio.h>
#include <stdlib.h>
#include "abalone.h"
#include "affichage.h"
#include "calculs.h"
#include "controles.h"
#include "main.h"

// Fonctions liste chainee
liste ajoutDebut(liste list, COORDS tableau[3]) //Ajout en début de liste d'un élément
{
	element* newelement = malloc(sizeof(element));
	
	newelement->tuple[0].x = tableau[0].x;
	newelement->tuple[0].y = tableau[0].y;

	newelement->tuple[1].x = tableau[1].x;
	newelement->tuple[1].y = tableau[1].y;
		
	newelement->tuple[2].x = tableau[2].x;
	newelement->tuple[2].y = tableau[2].y;

	newelement->next = list;
	return newelement;
}

void print_list(liste list) //Afficher la liste dans le terminal
{
	element *tmp = list;
	while(tmp != NULL)
	{
		printf("%dx", tmp->tuple[0].x);
		printf("%d\n", tmp->tuple[0].y);

		printf("%dx", tmp->tuple[1].x);
		printf("%d\n", tmp->tuple[1].y);

		printf("%dx", tmp->tuple[2].x);
		printf("%d\n", tmp->tuple[2].y);
		printf("\n");
		tmp = tmp -> next;
	}
}

int count_selected(COORDS tableau[3]) // Pour compter combien de pions sont séléctionnés
{
	int i;
	int cpt = 0;
	for (i = 0; i < 3; i++){
		if (tableau[i].x != -1 && tableau[i].y != -1)
			cpt++;
	}
	return cpt;
}

void annule_selected(COORDS tableau[3]) // Pour enlever les valeurs séléctionnées
{
    int i;
    for (i = 0; i<3; i++)
    {
        tableau[i].x = -1;
        tableau[i].y = -1;
    }
}

// Vérifie que le pion qu'on tente de séléctionner ne l'est pas déjà
int check_selected(COORDS tableau[3], COORDS position){
	int i;
	for (i = 0; i < 3; i++){
		if (tableau[i].x == position.x && tableau[i].y == position.y)
			return 0;
	}
	return 1;
}

/* Fonction qui vérifie si les coordonnées correspondent à un pion
du joueur */

int is_pion(CASE board[L][C], COORDS position, JOUEUR joueur)
{
	CASE selected = board[position.x][position.y];
	switch (selected){
		case NDEF : return 0; break;
		case VIDE : return 0; break;
		case B :
				if (joueur == BLANC)
					return 1;
				else
					return 0;
				break;
		case N : 
				if (joueur == NOIR)
					return 1;
				else
					return 0;
				break;
		case R : 
				if (joueur == ROUGE)
					return 1;
				else
					return 0;
				break;
		default : return 0;
	}
}

// Vérifie si le pion sélectionné est adjacent à un autre ou sur la continuité
// des autres pions déjà sélectionnés

int is_valid(COORDS tableau[3], COORDS position){
	int i, resultat, est_vide, deux_pions, x, y;
	resultat = 0;
	est_vide = 1;
	deux_pions = 0;
	
	for (i = 0; i < 3; i++)
	{
		if (tableau[i].x != -1){
			
			if(i == 1)
				deux_pions = 1;
				
			est_vide = 0;
			x = tableau[i].x - position.x;
			y = tableau[i].y - position.y;
			if (x == 0){ // les deux pions sont sur la même ligne
				if (y == 2 || y == -2)
					resultat = 1;
			}
			else if (x == -1 || x == 1){
				if (y == 1 || y == -1)
					resultat = 1;
			}
		}
	}

	/* Dans le cas où deux pions ont déjà été sélectionnés il faut
	 * s'assurer que le troisième soit placé dans la continuité */ 
	if (deux_pions){
		if (tableau[0].x == tableau[1].x){
			if (tableau[1].y - position.y == -2 || tableau[1].y - position.y == 2){
				if (position.x == tableau[0].x)
					return 1;
				else
					return 0;
			}
			return 0;
		}
		else{
			if (position.x != tableau[0].x && position.x != tableau[1].x){
				if (tableau[1].y - position.y == -1 || tableau[1].y - position.y == 1){
					if(tableau[1].x - position.x == 1 || tableau[1].x - position.x == -1)
						return 1;
					else
						return 0;
				}
			}
			return 0;
		}
	}

	if (est_vide)
		resultat = 1;

	return resultat;
}

//Selectionner un pion pour le déplacer ensuite
int select_pion(CASE board[L][C], COORDS position, COORDS tableau[3], JOUEUR joueur)
{
	int i;
	// Vérifie que le pion n'est pas déjà sélectionné et est valide
	if (check_selected(tableau, position) && is_pion(board, position, joueur) && is_valid(tableau, position)){
    // Recherche une place disponible dans le tableau
		for (i = 0; i < 3; i++){
			if (tableau[i].x == -1){
				tableau[i].x = position.x;
				tableau[i].y = position.y;
				return 1;
			}
		}
	}
    return 0; // Pas de place ou pion déjà séléctionné
}

//Affiche la liste des pions selectionnés
void affiche_selected(COORDS tableau[3])
{
    int i;
    for (i = 0; i < 3; i++){
        printf("%d", tableau[i].x);
        printf("%d", tableau[i].y);
        printf("\n");
    }
}

void affiche_plateau()
{
    unsigned int i, j; //Compteurs

	for(i = 0; i < L; i++) //Affichage du plateau de jeu
	{
		for(j = 0; j < C; j++)
		{
			if (plateau[i][j] == NDEF) //Pas une case
				printf(" ");
			else if(plateau[i][j] == VIDE) //Case vide
				printf(".");
			else if(plateau[i][j] == B) //Case occupée
				printf("B");
			else if(plateau[i][j] == R) //Case occupée
				printf("R");
			else
				printf("N");
		}
		printf("\n");
	}
}

void affiche_plateau2(CASE tab[L][C])
{
    unsigned int i, j; //Compteurs

	for(i = 0; i < L; i++) //Affichage du plateau de jeu
	{
		for(j = 0; j < C; j++)
		{
			if (tab[i][j] == NDEF) //Pas une case
				printf(" ");
			else if(tab[i][j] == VIDE) //Case vide
				printf(".");
			else if(tab[i][j] == B) //Case occupée
				printf("B");
			else if(tab[i][j] == R) //Case occupée
				printf("R");
			else
				printf("N");
		}
		printf("\n");
	}
}

/* 
 * Fonction qui renvoie la coordonnée qui suit celle passée
 * en paramètre dans la direction donnée
 */ 
void next_coord(COORDS* p, DIRECTION d)
{
	switch(d)
	{
		case G: p->y-=2; break;
		case HG: p->x-=1; p->y-=1; break;
		case HD: p->x-=1; p->y+=1; break;
		case D: p->y+=2; break;
		case BD: p->x+=1; p->y+=1; break;
		case BG: p->x+=1; p->y-=1; break;
		default : break;
	}
}

COORDS next_coord2(COORDS p, DIRECTION d)
{
	switch(d)
	{
		case G: p.y-=2; break;
		case HG: p.x-=1; p.y-=1; break;
		case HD: p.x-=1; p.y+=1; break;
		case D: p.y+=2; break;
		case BD: p.x+=1; p.y+=1; break;
		case BG: p.x+=1; p.y-=1; break;
		default : break;
	}
	return p;
}

/*
 * Fonction qui renvoie true si la coordonnée donnée en paramètre
 * est dans le plateau. false sinon.
 */ 
int is_in_board(CASE board[L][C], COORDS p)
{
	if(p.x >= 0 && p.x < L && p.y >= 0 && p.y < C)
		if(board[p.x][p.y] != NDEF)
			return 1;
	return 0;
}

/* 
 * Fonction qui renvoie vrai si la case suivant le pion, dans la
 * direction donnée, contient un autre pion. Faux sinon.
 */
int has_next(CASE board[L][C], COORDS p, DIRECTION d)
{
	int next;
	if(!is_in_board(board, next_coord2(p, d)))
		return 0;

	switch (d){
		case G: next = board[p.x][p.y-2] == B || board[p.x][p.y-2] == N || board[p.x][p.y-2] == R ? 1 : 0; break;
		case HG: next = board[p.x-1][p.y-1] == B || board[p.x-1][p.y-1] == N || board[p.x-1][p.y-1] == R ? 1 : 0; break;
		case HD: next = board[p.x-1][p.y+1] == B || board[p.x-1][p.y+1] == N || board[p.x-1][p.y+1] == R ? 1 : 0; break;
		case D: next = board[p.x][p.y+2] == B || board[p.x][p.y+2] == N || board[p.x][p.y+2] == R ? 1 : 0; break;
		case BD: next = board[p.x+1][p.y+1] == B || board[p.x+1][p.y+1] == N || board[p.x+1][p.y+1] == R ? 1 : 0; break;
		case BG: next = board[p.x+1][p.y-1] == B || board[p.x+1][p.y-1] == N || board[p.x+1][p.y-1] == R ? 1 : 0; break;
		default : break;
	}
	return next;
}

/*
 * Fonction qui renvoie vrai si la case suivant le pion, dans la
 * direction donnée, contient un autre pion de la même couleur. Faux sinon
 */
int has_ally_next(CASE board[L][C], COORDS p, DIRECTION d, JOUEUR j)
{
	CASE ally;
	int next;
	if(!is_in_board(board, next_coord2(p, d)))
		return 0;
		
	//ally = j == NOIR ? N : B;
	if(j == NOIR) ally=N; 
	else if(j == BLANC) ally=B; 
	else if(j == ROUGE) ally=R; 
	
	switch (d){
		case G: next = board[p.x][p.y-2] == ally ? 1 : 0; break;
		case HG: next = board[p.x-1][p.y-1] == ally ? 1 : 0; break;
		case HD: next = board[p.x-1][p.y+1] == ally ? 1 : 0; break;
		case D: next = board[p.x][p.y+2] == ally ? 1 : 0; break;
		case BD: next = board[p.x+1][p.y+1] == ally ? 1 : 0; break;
		case BG: next = board[p.x+1][p.y-1] == ally ? 1 : 0; break;
		default : break;
	}
	return next;
}

//2 pions de même couleur poussent 1 pion ennemi
void sumito_2contre1(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3])
{
	COORDS pion;
	CASE couleur;
	CASE opponent;
	
	if(joueur==BLANC)
		couleur=B;
	else if(joueur==NOIR)
		couleur=N;
	else if(joueur==ROUGE)
		couleur=R;
	
	pion.x = tableau[0].x;
	pion.y = tableau[0].y;
	
	if(!has_ally_next(board, pion, d, joueur)){
		pion.x = tableau[1].x;
		pion.y = tableau[1].y;
	}
	board[pion.x][pion.y] = VIDE;
	pion = next_coord2(pion, d);
	board[pion.x][pion.y] = couleur;
	pion = next_coord2(pion, d);
	opponent = board[pion.x][pion.y];
	board[pion.x][pion.y] = couleur;
	pion = next_coord2(pion, d);
	if(is_in_board(board, pion)) //Si la prochaine case ne sort pas du plateau
		board[pion.x][pion.y] = opponent; //On déplace le pion ennemi
}

//3 pions de même couleur poussent 1 pion ennemi
void sumito_3contre1(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3])
{
	COORDS pion;
	CASE couleur;
	CASE opponent;
	
	if(joueur==BLANC)
		couleur=B;
	else if(joueur==NOIR)
		couleur=N;
	else if(joueur==ROUGE)
		couleur=R;
		
	pion.x = tableau[0].x;
	pion.y = tableau[0].y;
	
	if(!has_ally_next(board, pion, d, joueur)){
		pion.x = tableau[2].x;
		pion.y = tableau[2].y;
	}
	board[pion.x][pion.y] = VIDE;
	pion = next_coord2(pion, d);
	board[pion.x][pion.y] = couleur;
	pion = next_coord2(pion, d);
	board[pion.x][pion.y] = couleur;
	pion = next_coord2(pion, d);
	opponent = board[pion.x][pion.y];
	board[pion.x][pion.y] = couleur;
	pion = next_coord2(pion, d);
	if(is_in_board(board, pion)) //Si la prochaine case ne sort pas du plateau
		board[pion.x][pion.y] = opponent; //On déplace le pion ennemi
}

//3 pions de même couleur poussent 2 pions ennemis
void sumito_3contre2(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3])
{
	COORDS pion;
	CASE opponents[2];
	CASE couleur;
	
	if(joueur==BLANC)
		couleur=B;
	else if(joueur==NOIR)
		couleur=N;
	else if(joueur==ROUGE)
		couleur=R;
	
	pion.x = tableau[0].x;
	pion.y = tableau[0].y;
	
	if(!has_ally_next(board, pion, d, joueur)){
		pion.x = tableau[2].x;
		pion.y = tableau[2].y;
	}
	board[pion.x][pion.y] = VIDE;
	pion = next_coord2(pion, d);
	board[pion.x][pion.y] = couleur;
	pion = next_coord2(pion, d);
	board[pion.x][pion.y] = couleur;
	pion = next_coord2(pion, d);
	opponents[0] = board[pion.x][pion.y];
	board[pion.x][pion.y] = couleur;
	pion = next_coord2(pion, d);
	opponents[1] = board[pion.x][pion.y];
	board[pion.x][pion.y] = opponents[0];
	pion = next_coord2(pion, d);
	if(is_in_board(board, pion)) //Si la prochaine case ne sort pas du plateau
		board[pion.x][pion.y] = opponents[1]; //On déplace le pion ennemi
}

/* Détermine si le mouvement est broadside ou inline */
MVTYPE mouvement_type(DIRECTION d, COORDS tableau[3])
{
	int i;

	int max_x = tableau[0].x;
	int min_x = tableau[0].x;
	int y_val1 = tableau[0].y;
	int y_val2 = tableau[0].y;

	MVTYPE type;
	ORIENTATION orientation;

	if(tableau[0].x == tableau[1].x){ // ligne
		orientation = LIGNE;
	}
	else{ // diagonale, il faut déterminer le sens (gauche ou droite)
		for (i = 1; i < 3; i++){
			if (tableau[i].x != -1){
				if (tableau[i].x > max_x){
					max_x = tableau[i].x;
					y_val1 = tableau[i].y;
				}
				if (tableau[i].x < min_x){
					min_x = tableau[i].x;
					y_val2 = tableau[i].y;
				}
			}
		}
		
		if (y_val1 > y_val2)
			orientation = DIAGONALE_G;
		else
			orientation = DIAGONALE_D;
	}
	switch (d){
		case G : 
			if(orientation == LIGNE)
				type = INLINE;
			else if (orientation == DIAGONALE_G)
				type = BROADSIDE;
			else
				type = BROADSIDE;
			break;
			
		case HG : 
			if(orientation == LIGNE)
				type = BROADSIDE;
			else if (orientation == DIAGONALE_G)
				type = INLINE;
			else
				type = BROADSIDE;
			break;
			
		case HD :
			if(orientation == LIGNE)
				type = BROADSIDE;
			else if (orientation == DIAGONALE_G)
				type = BROADSIDE;
			else
				type = INLINE;
			break;
			
		case D :
			if(orientation == LIGNE)
				type = INLINE;
			else if (orientation == DIAGONALE_G)
				type = BROADSIDE;
			else
				type = BROADSIDE;
			break;
			
		case BD :
			if(orientation == LIGNE)
				type = BROADSIDE;
			else if (orientation == DIAGONALE_G)
				type = INLINE;
			else
				type = BROADSIDE;
			break;
			
		case BG :
			if(orientation == LIGNE)
				type = BROADSIDE;
			else if (orientation == DIAGONALE_G)
				type = BROADSIDE;
			else
				type = INLINE;
			break;
			
		default : break;
	}
	return type;
}

/*
 * Fonction de déplacement simple (=sans sumito)
 */ 
void mouvement_simple(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3])
{
	COORDS pos;
	CASE couleur;
	int i;
	int compteur = 0;
	
	if(joueur == NOIR) couleur=N;
	else if(joueur == BLANC) couleur=B;
	else if(joueur == ROUGE) couleur=R;
	
	for (i = 0; i < 3; i++)
	{
		if(tableau[i].x != -1)
		{
			board[tableau[i].x][tableau[i].y] = VIDE;
			compteur++;
		}
	}
	
	for (i = 0; i < compteur; i++)
	{
		pos = next_coord2(tableau[i], d);
		//next_coord(&tableau[i], d);
		board[pos.x][pos.y] = couleur;
	}
}

/* Fonction pour les broadside moves */
int broadside_move(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3])
{
	int i;
	for(i = 0; i < 3; i++)
	{
		if(tableau[i].x != -1){
			if(has_next(board, tableau[i], d) || !is_in_board(board, next_coord2(tableau[i], d)))
				return 0;
		}
	}
	mouvement_simple(board, d, joueur, tableau);
	return 1;
}

/*
 * Fonction qui renvoie true si une coordonnée est contenu dans un
 * tableau de coordonnées.
 */
int in_array(COORDS pos, COORDS tab[3])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (pos.x == tab[i].x && pos.y == tab[i].y)
			return 1;
	}
	return 0;
}
/* Fonction pour les inline moves */
int inline_move(CASE board[L][C], DIRECTION d, JOUEUR joueur,COORDS tableau[3], SUMITOTYPE** sumito)
{
	int reach_enemy = 0;
	int next = 1;
	int compteur = 0;
	int nb_pions;
	COORDS p = tableau[0];
	
	while(next)
	{
		if(has_next(board, p, d))
		{
			if(has_ally_next(board, p, d, joueur)) 
			{
				if(reach_enemy || !in_array(next_coord2(p, d), tableau)) // Mouvement impossible
					return 0;
			}
			else // Si le suivant n'est pas de la même couleur
			{
				compteur++;
				if(!reach_enemy)
					reach_enemy = 1;
			}
		
			switch(d) // On passe au suivant dans la direction donnée
			{
				case G: 
					p.y -= 2;
					break;
					
				case HG:
					p.x -= 1; p.y -= 1;
					break;

				case HD:
					p.x -= 1; p.y += 1;
					break;
					
				case D: 
					p.y += 2;
					break;
				
				case BD:
					p.x += 1; p.y += 1;
					break;
					
				case BG: 
					p.x += 1; p.y -= 1;
					break;
					
				default : break;
			}
		}
		else{ // Plus de pion suivant
			if(!is_in_board(board, next_coord2(p, d)) && compteur == 0) // Prochaine case hors plateau (= suicide)
				return 0;
			next = 0;
		}
	}
	
	if (compteur > 0){
		nb_pions = count_selected(tableau);
		if(nb_pions > compteur) // Sumito
		{
			if (nb_pions == 3 && compteur == 1){ // Sumito 3vs1
				sumito_3contre1(board, d, joueur, tableau);
				**sumito = SUMITO3vs1;
			}
			else if (nb_pions == 2 && compteur == 1) {// Sumito 2vs1
				sumito_2contre1(board, d, joueur, tableau);
				**sumito = SUMITO2vs1;
			}
			else if(nb_pions == 3 && compteur == 2){
				sumito_3contre2(board, d, joueur, tableau); //Sumito 3vs2
				**sumito = SUMITO3vs2;
			}
			else
				return 0;

			return 1;
		}
		else // Pac = impossible
		{
			return 0;
		}
	}
	else{
		mouvement_simple(board, d, joueur, tableau);
		return 1;
	}

}

/* La fonction va déterminer quel type de mouvement
 * il faut faire ici.
 */
int mouvement(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3], SUMITOTYPE* sumito)
{
	int nb_pions;
	MVTYPE type;
	
	nb_pions = count_selected(tableau);
	if(nb_pions != 0){ // Au moins un pion est sélectionné
		if(nb_pions == 1){ // 1 pion
			if(!has_next(board, tableau[0], d) && is_in_board(board, next_coord2(tableau[0], d))){ // Si la position d'arrivée du pion est dispo et pas hors du plateau
				mouvement_simple(board, d, joueur, tableau);
			}
			else{
				return 0;
			}
		}
		else{ // + d'1 pion
			// Il faut savoir si c'est une ligne ou une diagonale
			// Pour déterminer si c'est un broadside ou inline move
			type = mouvement_type(d, tableau);
			if (type == INLINE){
				if(!inline_move(board, d, joueur, tableau, &sumito))
					return 0;
			}
			else{
				if(!broadside_move(board, d, joueur, tableau))
					return 0;
			}
		}
	}
	else{ // Aucun pion n'est sélectionné
		return 0;
	}
	return 1;
}

/* Fonction qui renvoie le true si la partie est terminée */
int end_game(CASE board[L][C])
{
	int i, j;
	int cpt_noir = 0;
	int cpt_blanc = 0;
	for(i = 0; i < L; i++) 
	{
		for(j = 0; j < C; j++)
		{
			if(board[i][j] == N)
				cpt_noir++;
			else if(board[i][j] == B)
				cpt_blanc++;
		}
	}
	if(cpt_noir == 8 || cpt_blanc == 8)
		return 1;
	return 0;
}

/*
 * ARTIFICIAL INTELLIGENCE
 */ 
int min(int a, int b)
{
	return a < b ? a : b;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

void empty_tab(COORDS tab[3])
{
	int i;
	for (i = 0; i < 3; i++){
			tab[i].x = -1;
			tab[i].y = -1;
	}
}

void add_tab(COORDS tab[3], COORDS pos)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (tab[i].x == -1){
			tab[i].x = pos.x;
			tab[i].y = pos.y;
			break;
		}
	} 
}

/*
 * Fonction qui ajoute les pions pouvant être joués ensemble
 * dans une liste.
 */
liste get_case(CASE board[L][C], COORDS pos, liste list, JOUEUR joueur) // BG BD D
{
	
	COORDS pos2, pos3;
	COORDS tab[3];
	empty_tab(tab); // On met bien toutes les valeurs à -1
	
	// Ajout du pion tout seul dans le tableau
	add_tab(tab, pos);
	list = ajoutDebut(list, tab); // Puis ajout du tableau dans la liste
	empty_tab(tab); // Et on vide le tableau
	
	// Bas gauche avec 2 et 3 pions si possible
	if (has_ally_next(board, pos, BG, joueur)){
		add_tab(tab, pos);
		pos2 = next_coord2(pos, BG);
		add_tab(tab, pos2);
		list = ajoutDebut(list, tab);
		empty_tab(tab);
		if (has_ally_next(board, pos2, BG, joueur)){
			add_tab(tab, pos);
			add_tab(tab, pos2);
			pos3 = next_coord2(pos2, BG);
			add_tab(tab, pos3);
			list = ajoutDebut(list, tab);
			empty_tab(tab);
		}
	}
	
	// Bas droite avec 2 et 3 pions si possible
	if (has_ally_next(board, pos, BD, joueur)){
		add_tab(tab, pos);
		pos2 = next_coord2(pos, BD);
		add_tab(tab, pos2);
		list = ajoutDebut(list, tab);
		empty_tab(tab);
		if (has_ally_next(board, pos2, BD, joueur)){
			add_tab(tab, pos);
			add_tab(tab, pos2);
			pos3 = next_coord2(pos2, BD);
			add_tab(tab, pos3);
			list = ajoutDebut(list, tab);
			empty_tab(tab);
		}
	}
	
	// Droite avec 2 et 3 pions si possible
	if (has_ally_next(board, pos, D, joueur)){
		add_tab(tab, pos);
		pos2 = next_coord2(pos, D);
		add_tab(tab, pos2);
		list = ajoutDebut(list, tab);
		empty_tab(tab);
		if (has_ally_next(board, pos2, D, joueur)){
			add_tab(tab, pos);
			add_tab(tab, pos2);
			pos3 = next_coord2(pos2, D);
			add_tab(tab, pos3);
			list = ajoutDebut(list, tab);
			empty_tab(tab);
		}
	}
	return list;
}

/* 
 * Récupère les pions d'un joueur pouvant être joués ensemble
 */
liste get_ally_marble(CASE board[L][C], JOUEUR joueur)
{
	int i, j;
	liste list = NULL;
	CASE ally = joueur == BLANC ? B : N;
	
	COORDS pos;
	for(i = 0; i < L; i++)
	{
		for(j = 0; j < C; j++)
		{
			if(board[i][j] == ally)
			{
				pos.x = i; pos.y = j;
				list = get_case(board, pos, list, joueur);
			}
		}
	}
	return list;
}

// Copier le contenu d'un tableau dans un autre
void copy_tab(CASE new_tab[L][C], CASE tab[L][C])
{
	int i, j;
	for (i = 0; i < L; i++){
		for (j = 0; j < C; j++){
			new_tab[i][j] = tab[i][j];
		}
	}
}

//Copier tableau de coordonnées dans un autre
void copy_tab_coords(COORDS new_tab[3], COORDS tab[3])
{
	int i;
	for (i = 0; i < 3; i++)
		new_tab[i] = tab[i];
}

//Annule un sumito de 2 pions contre 1
void undo_sumito_2vs1(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tab[3])
{
	CASE ally, enemy;
	COORDS pos;
	
	if(joueur == NOIR){
		ally = N;
		enemy = B;
	}
	else{
		ally = B;
		enemy = N;
	}
	pos = board[tab[0].x][tab[0].y] != VIDE ? tab[1] : tab[0];

	board[pos.x][pos.y] = ally;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = ally;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = enemy;
	if (is_in_board(board, next_coord2(pos, d))){
		pos = next_coord2(pos, d);
		board[pos.x][pos.y] = VIDE;
	}	
}

//Annule un sumito de 3 pions contre 1
void undo_sumito_3vs1(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tab[3])
{
	CASE ally, enemy;
	COORDS pos;
	
	if(joueur == NOIR){
		ally = N;
		enemy = B;
	}
	else{
		ally = B;
		enemy = N;
	}
	pos = board[tab[0].x][tab[0].y] != VIDE ? tab[2] : tab[0];

	board[pos.x][pos.y] = ally;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = ally;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = ally;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = enemy;
	if (is_in_board(board, next_coord2(pos, d))){
		pos = next_coord2(pos, d);
		board[pos.x][pos.y] = VIDE;
	}
}

//Annule un sumito de 3 pions contre 2
void undo_sumito_3vs2(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tab[3])
{
	CASE ally, enemy;
	COORDS pos;
	
	if(joueur == NOIR){
		ally = N;
		enemy = B;
	}
	else{
		ally = N;
		enemy = B;
	}
	pos = board[tab[0].x][tab[0].y] != VIDE ? tab[2] : tab[0];

	board[pos.x][pos.y] = ally;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = ally;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = ally;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = enemy;
	pos = next_coord2(pos, d);
	board[pos.x][pos.y] = enemy;
	if (is_in_board(board, next_coord2(pos, d))){
		pos = next_coord2(pos, d);
		board[pos.x][pos.y] = VIDE;
	}
}

//Annule un déplacement 
void undo_move(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tab[3], SUMITOTYPE sumito){
	int nb_pion, i;
	COORDS pos;
	CASE ally;
	
	ally = joueur == NOIR ? N : B;
	nb_pion = count_selected(tab);

	if(nb_pion == 1){
		pos = next_coord2(tab[0], d);
		board[pos.x][pos.y] = VIDE;
		board[tab[0].x][tab[0].y] = ally;
	}
	else{
		if (sumito != -1){
			if(sumito == SUMITO2vs1)
				undo_sumito_2vs1(board, d, joueur, tab);
			else if (sumito == SUMITO3vs1)
				undo_sumito_3vs1(board, d, joueur, tab);
			else
				undo_sumito_3vs2(board, d, joueur, tab);			
		}
		else{
			for(i = 0; i < 3; i++)
			{
				if (tab[i].x != -1){
					pos = next_coord2(tab[i], d);
					board[pos.x][pos.y] = VIDE;
				}
			}
			for(i = 0; i < 3; i++)
			{
				if (tab[i].x != -1)
					board[tab[i].x][tab[i].y] = ally;
			}
		}
	}
}

// Fonction d'évaluation

// 
int count_neighbors(CASE board[L][C], COORDS pos, JOUEUR joueur)
{
	int nb_neighbors = 0;
	
	if(has_ally_next(board, pos, G, joueur))
		nb_neighbors++;
	if(has_ally_next(board, pos, HG, joueur))
		nb_neighbors++;
	if(has_ally_next(board, pos, HD, joueur))
		nb_neighbors++;
	if(has_ally_next(board, pos, D, joueur))
		nb_neighbors++;
	if(has_ally_next(board, pos, BD, joueur))
		nb_neighbors++;
	if(has_ally_next(board, pos, BG, joueur))
		nb_neighbors++;
	
	return nb_neighbors;	
}

int eval_board(CASE board[L][C], JOUEUR joueur)
{
	int i, j;
	int valeur_coup = 0;
	CASE ally, enemy;
	
	if (joueur == BLANC){
		ally = B;
		enemy = N;
	}
	else{
		ally = N;
		enemy = B;
	}
	
	for (i = 0; i < L; i++){
		for (j = 0; j < C; j++){
			if(board[i][j] == enemy){
				valeur_coup -= position_weight[i][j];
				valeur_coup -= 3000;
			//	valeur_coup -= 10 * count_neighbors(board, pos, joueur); // Pour inciter les billes à rester groupées
			}
			else if(board[i][j] == ally){
				valeur_coup += position_weight[i][j];
				valeur_coup += 3000;
			//	valeur_coup += 10 * count_neighbors(board, pos, joueur);
			}
		}
	}
	return valeur_coup;
}

int maximize(CASE board[L][C], int depth, int alpha, int beta, JOUEUR joueur)
{
	CASE temp_board[L][C];
	int i, val;
	liste possible_moves;
	DIRECTION dir;
	JOUEUR opponent;
	SUMITOTYPE sumito = -1;
	val = -100000; // - infini
	
	if(depth == 0 || end_game(board))
		return eval_board(board, joueur);
	
	opponent = joueur == BLANC ? NOIR : BLANC;
	copy_tab(temp_board, board);
	
	possible_moves = get_ally_marble(board, joueur);
	element *tmp = possible_moves;
	while(tmp != NULL) // Pour chaque coup possible
	{
		for(i = 0; i < 6; i++) // Pour les 6 mouvements
		{
			sumito = -1;
			if (i == 0){
				if(!mouvement(temp_board, G, joueur, tmp->tuple, &sumito)) //Si le mouvement ne marche pas
					continue;
				dir = G;
			}
			else if (i == 1){
				if(!mouvement(temp_board, HG, joueur, tmp->tuple, &sumito))
					continue;
				dir = HG;
			}
			else if (i == 2){
				if(!mouvement(temp_board, HD, joueur, tmp->tuple, &sumito))
					continue;
				dir = HD;
			}
			else if (i == 3){
				if(!mouvement(temp_board, D, joueur, tmp->tuple, &sumito))
					continue;
				dir = D;
			}
			else if (i == 4){
				if(!mouvement(temp_board, BD, joueur, tmp->tuple, &sumito))
					continue;
				dir = BD;
			}
			else{
				if(!mouvement(temp_board, BG, joueur, tmp->tuple, &sumito))
					continue;
				dir = BG;
			}

			val = max(val, minimize(temp_board, depth-1, val, beta, opponent)); // Appel récursif
			
			if(val >= beta)
				return val;
			
			alpha = max(alpha, val);
			//copy_tab(board, plateau_base); // Annule le coup
			undo_move(temp_board, dir, joueur, tmp->tuple, sumito);
			sumito = -1;
		}
		tmp = tmp -> next; // Passage au tuple de pions suivant
	}
	
	return val;		
}

int minimize(CASE board[L][C], int depth, int alpha, int beta, JOUEUR joueur)
{
	CASE temp_board[L][C];
	int i, val;
	liste possible_moves;
	DIRECTION dir;
	JOUEUR opponent;
	SUMITOTYPE sumito = -1;
	val = 100000; // + infini
	opponent = joueur == BLANC ? NOIR : BLANC;
	
	if(depth == 0 || end_game(board))
		return eval_board(board, opponent);
	
	copy_tab(temp_board, board);
	
	possible_moves = get_ally_marble(board, joueur);
	element *tmp = possible_moves;
	while(tmp != NULL) // Pour chaque coup possible
	{
		for(i = 0; i < 6; i++) // Pour les 6 mouvements
		{
			sumito = -1;
			if (i == 0){
				if(!mouvement(temp_board, G, joueur, tmp->tuple, &sumito)) // Si le mouvement ne marche pas
					continue;
				dir = G;
			}
			else if (i == 1){
				if(!mouvement(temp_board, HG, joueur, tmp->tuple, &sumito))
					continue;
				dir = HG;
			}
			else if (i == 2){
				if(!mouvement(temp_board, HD, joueur, tmp->tuple, &sumito))
					continue;
				dir = HD;
			}
			else if (i == 3){
				if(!mouvement(temp_board, D, joueur, tmp->tuple, &sumito))
					continue;
				dir = D;
			}
			else if (i == 4){
				if(!mouvement(temp_board, BD, joueur, tmp->tuple, &sumito))
					continue;
				dir = BD;
			}
			else{
				if(!mouvement(temp_board, BG, joueur, tmp->tuple, &sumito))
					continue;
				dir = BG;
			}
			
			val = min(val, maximize(temp_board, depth-1, alpha, val, opponent)); // Appel récursif
			
			if(val <= alpha)
				return val;
			
			beta = min(beta, val);
		//	copy_tab(board, plateau_base); // Annule le coup
			undo_move(temp_board, dir, joueur, tmp->tuple, sumito);
			sumito = -1;
		}
		tmp = tmp -> next; // Passage au tuple de pions suivant
	}
	
	return val;	
}

void affiche_tableau(COORDS tab[3])
{
	int i;
	printf("\n");
	for (i = 0; i < 3; i++)
	{
		printf("%d x %d", tab[i].x, tab[i].y);
		printf("\n");
	}
}

DIRECTION AlphaBeta(CASE board[L][C], int depth, int alpha, int beta, JOUEUR joueur, COORDS tableau[3])
{
	int i, val;
	liste possible_moves;
	DIRECTION type, best_move;
	JOUEUR opponent;
	CASE temp_board[L][C];
	SUMITOTYPE sumito = -1;
	int max_val = -100000; // - infini

	opponent = joueur == BLANC ? NOIR : BLANC;
	copy_tab(temp_board, board);
	
	possible_moves = get_ally_marble(board, joueur);
	
	element *tmp = possible_moves;
	while(tmp != NULL) // Pour chaque coup possible
	{
		for(i = 0; i < 6; i++) // Pour les 6 mouvements
		{
			switch(i){
				case 0 : 
					if(!mouvement(temp_board, G, joueur, tmp->tuple, &sumito)) //Si le mouvement ne marche pas
						continue;
					type = G; break;
				case 1 : 
					if(!mouvement(temp_board, HG, joueur, tmp->tuple, &sumito))
						continue;
					type = HG; break;
				case 2 :
					if(!mouvement(temp_board, HD, joueur, tmp->tuple, &sumito))
						continue;
					type = HD; break;
				case 3 :
					if(!mouvement(temp_board, D, joueur, tmp->tuple, &sumito))
						continue;
					type = D; break;
				case 4 :
					if(!mouvement(temp_board, BD, joueur, tmp->tuple, &sumito))
						continue;
					type = BD; break;
				case 5 :
					if(!mouvement(temp_board, BG, joueur, tmp->tuple, &sumito))
						continue;
					type = BG; break;
			}
			
			val = minimize(temp_board, depth, alpha, beta, opponent);
			
			if(val > max_val){
				max_val = val;
				best_move = type;
				copy_tab_coords(tableau, tmp->tuple);
			}

			//copy_tab(board, plateau_base); // Annuler le coup
			undo_move(temp_board, type, joueur, tmp->tuple, sumito); // Annuler le coup
			
			sumito = -1;

		}
		
		tmp = tmp -> next; // Passage au tuple de pions suivant
	}
	return best_move;
}

//simule une partie IA contre IA
void simule_game(JOUEUR joueur)
{
	DIRECTION dir;
	COORDS tab[3];
	JOUEUR opponent;
	SUMITOTYPE sumito = -1;
	printf("Joueur : %d\n", joueur);
	opponent = joueur == NOIR ? BLANC : NOIR;
	
	dir = AlphaBeta(plateau, 2, -100000, 100000, joueur, tab);
	//dir = getBestMove(plateau, 2, joueur, tab);
	mouvement(plateau, dir, joueur, tab, &sumito);
	affiche_plateau();
	//printf("Simuler la suite de la partie ? (OUI : 1 NON : 0)\n");
	//scanf("%d", &rep);
	
	if(end_game(plateau)){
		printf("Partie terminée");
		return;
	}/*
	else{
		if(rep)
			simule_game(opponent);
		else
			return;
	}*/
	simule_game(opponent);
}

int cpt_score(CASE board[L][C], JOUEUR joueur)
{
	int i, j, black=14, white=14;
	
	for (i = 0; i < L; i++){
		for (j = 0; j < C; j++){
			if(board[i][j] == B)
				black -= 1;
			if(board[i][j] == N)
				white -= 1;
		}
	}
	if (joueur == NOIR){
		return black;
	}
	else if (joueur == BLANC){
		return white;
	}
	return 0;
}

//Simule une partie 1 contre 1 dans le terminal
void simule_1v1_game(CASE board[L][C],char joueur1[], char joueur2[]){
	DIRECTION dir = -1;
	COORDS pion;
	SUMITOTYPE s=-1;
	int tour=0,i=1,j;	
	JOUEUR p[2]={BLANC,NOIR};//tableau des joueurs
	
	do{
		if(i==1){
			i=0;
			tour++;
		}
		else{
			i++;
			
		}
		affiche_plateau();
		printf("tour: %d %d\n",tour,i);
		
		do{
		annule_selected(selected);
		for(j=0;j<3;j++){			
			printf("coords x %d: ",j+1);
			scanf("%d",&pion.x);
			printf("coords y %d: ",j+1);
			scanf("%d",&pion.y);
			select_pion(board,pion,selected,p[i]);
		}
		printf("mouvement: ");
		//scanf("%d",&dir); 	à décommenter pour tester
		}while(!mouvement(board,dir,p[i],selected,&s));
		
	}while(!end_game(board));
	
	printf("Fin de la partie");
	save_score2j(joueur1,cpt_score(board,BLANC),joueur2,cpt_score(board,NOIR));
}

//Calcule la différence de pions après un coup avec l'ancien plateau
int diff_pions(CASE old_board[L][C],CASE board[L][C]){
	int i,j,cpt_old=0,cpt=0;
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(old_board[i][j] == B || old_board[i][j] == N || old_board[i][j] == R)
				cpt_old++;
			if(board[i][j] == B || board[i][j] == N || board[i][j] == R)
				cpt++;
		}
	}
	return cpt_old-cpt;
}

//Simule une partie 1 contre 1 contre 1 en terminal
void simule_1v1v1_game(CASE board[L][C], char joueur1[], char joueur2[], char joueur3[]){
	DIRECTION dir = -1;
	COORDS pion;
	SUMITOTYPE s=-1;
	int tour=0,i=2,j;
	int score[3]={0,0,0};
	JOUEUR p[3]={BLANC,NOIR,ROUGE};
	CASE save[L][C];
	
	do{
		if(i==2){
			i=0;
			tour++;
		}
		else{
			i++;
		}
		affiche_plateau2(board);
		printf("tour: %d %d\n",tour,i);
		
		do{
		annule_selected(selected);
		for(j=0;j<3;j++){			
			printf("coords x %d: ",j+1);
			scanf("%d",&pion.x);
			printf("coords y %d: ",j+1);
			scanf("%d",&pion.y);
			select_pion(board,pion,selected,p[i]);
		}
		copy_tab(save,board);
		printf("mouvement: ");
		//scanf("%d", &dir);	 à décommenter pour tester
		}while(!mouvement(board,dir,p[i],selected,&s));
		
		score[i]+=diff_pions(save,board);
		printf("%d\n",score[i]);
	}while(score[i]<6);
	
	printf("Fin de la partie");
	save_score3j(joueur1,score[0],joueur2,score[1],joueur3,score[2]);
}

//Sauvegarde du score d'une partie 1 contre 1 dans le fichier "scores.txt"
void save_score2j(char joueur1[], int score1, char joueur2[], int score2){
	FILE* fichier = NULL;
	
	fichier=fopen("scores.txt","r+");
	
	if (fichier!=NULL){
		char chaine[100]="";
		char nb[50];
		strcat(chaine,joueur1);
		sprintf(nb,"-%d : ",score1);
		strcat(chaine,nb);
		strcat(chaine,joueur2);
		sprintf(nb,"-%d\n",score2);
		strcat(chaine,nb);
		fseek(fichier,0,SEEK_END);
		fputs(chaine,fichier);
		fclose(fichier);
	}
}

//Sauvegarde du score d'une partie 1 contre 1 contre 1 dans le fichier "scores.txt"
void save_score3j(char joueur1[], int score1, char joueur2[], int score2, char joueur3[], int score3){
	FILE* fichier = NULL;
	
	fichier=fopen("scores.txt","r+");
	
	if (fichier!=NULL){
		char chaine[100]="";
		char nb[50];
		strcat(chaine,joueur1);
		sprintf(nb,"-%d : ",score1);
		strcat(chaine,nb);
		strcat(chaine,joueur2);
		sprintf(nb,"-%d : ",score2);
		strcat(chaine,nb);
		strcat(chaine,joueur3);
		sprintf(nb,"-%d\n",score3);
		strcat(chaine,nb);
		fseek(fichier,0,SEEK_END);
		fputs(chaine,fichier);
		fclose(fichier);
	}
}

void switch_player(MODE mode)
{
	if(mode == J2){
		if (player == BLANC)
			player = NOIR;
		else
			player = BLANC;
	}
	else{
		if (player == BLANC)
			player = ROUGE;
		else if (player == NOIR)
			player = BLANC;
		else
			player = NOIR;
	}
}

void play_IA(int level, int *turn)
{
	int depth;
	if (level == 1)
		depth = 1;
	else if(level == 2)
		depth = 2;
	else if(level == 3)
		depth = 3;
		
	JOUEUR ia;
	ia = player == NOIR ? BLANC : NOIR;
	*turn = 0; // Pour bloquer les actions du joueur
	DIRECTION dir;
	COORDS tab[3];
	SUMITOTYPE ndef =-1;
	dir = AlphaBeta(plateau, depth, -100000, 100000, ia, tab);
	mouvement(plateau, dir, ia, tab, &ndef);
	*turn = 1; // Débloquage des actions du joueur
}

int main()
{
	int turn = 1; // Sécurité lorsque l'IA joue
	MODE playMode = -1; // Mode de jeu par défaut
	int level_IA = 0; // Niveau de l'IA par défaut
	COORDS ball;
	CASE save[L][C]; // Pour le mode 3 joueurs
	DIRECTION direction;
	int score[3]={0,0,0}; // Idem
	int indice_joueur=0; // Idem
	float horizScaleFactor = (float)WINDOW_W/1920; // Facteurs d'échelle
	unsigned int xOffset = (float)278*WINDOW_W/1920,
							 yOffset = (float)185*WINDOW_H/1080, // Décalages horizontal et vertical utiles à l'affichage
							 i, j, // Indices de tableau
							 selectedBalls = 0; // Nombre de billes sélectionnées
	SDL_Rect windowSprite, playModeSprites[3], selectionRingSprite, arrowSprites[6];
	windowSprite.h = WINDOW_H;
	windowSprite.w = WINDOW_W;
	windowSprite.x = windowSprite.y = 0;
	selectionRingSprite.h = selectionRingSprite.w = 45; // Sprite du disque de sélection
	set_playmode_sprites(playModeSprites); // Initialise les bouton de l'accueil : choix du mode de jeu
	set_arrows_sprites(arrowSprites); // Initialise les flèches de contrôle
	
	SDL_Event event;
	SDL_bool closeRequested = SDL_FALSE; // Passe à VRAI lorsqu'on décide de fermer la fenêtre
	SDL_Point clickedPoint;

	SDL_Window* gameWindow = create_window_secure();
	SDL_Renderer* rend = create_renderer_secure(gameWindow);
	SDL_RenderClear(rend); // Nettoie (noircit) la fenêtre
	
	//Choix du mode de jeu, et éventuellement de la difficulté contre l'IA
	SDL_Texture* homeScreenTexture = display_image_secure(gameWindow, rend, "images/ecran_choix_mode.png", NULL, &windowSprite, SDL_TRUE);
	while ((playMode == -1) && !closeRequested) // Tant que l'on n'a pas choisi un mode de jeu
	{
		SDL_WaitEvent(&event);
		if ((event.type == SDL_MOUSEBUTTONDOWN) && (SDL_GetMouseState(&clickedPoint.x, &clickedPoint.y) & SDL_BUTTON(SDL_BUTTON_LEFT)))
		{
			if 			(point_is_in_rectangle(clickedPoint, playModeSprites[J2])) playMode = J2;
			else if (point_is_in_rectangle(clickedPoint, playModeSprites[J3]))
			{
				printf("J3\n");
				playMode = J3;
				copy_tab(plateau, plateau_3v); // Initialisation du tableau pour 3 joueurs
			}
			else if (point_is_in_rectangle(clickedPoint, playModeSprites[IA])) // Dans le cas où on souhaite jouer contre l'ordinateur
			{
				playMode = IA;
				printf("IA\n");
				homeScreenTexture = display_image_secure(gameWindow, rend, "images/ecran_choix_mode_IA.png", NULL, &windowSprite, SDL_TRUE);
				while (!level_IA && !closeRequested) // Tant que l'on n'a as choisi une difficulté contre l'ordinateur
				{
					SDL_WaitEvent(&event);
					if ((event.type == SDL_MOUSEBUTTONDOWN) && (SDL_GetMouseState(&clickedPoint.x, &clickedPoint.y) & SDL_BUTTON(SDL_BUTTON_LEFT)))
					{
						// Les écrans sont quasiment identiques, on utilise donc les rectangles du tableau du mode de jeu
						if 			(point_is_in_rectangle(clickedPoint, playModeSprites[J2])) level_IA = 1;
						else if (point_is_in_rectangle(clickedPoint, playModeSprites[J3])) level_IA = 2;
						else if (point_is_in_rectangle(clickedPoint, playModeSprites[IA])) level_IA = 3;
					}
					else if (event.type == SDL_QUIT)
					{
						closeRequested = SDL_TRUE;
					}
				}
			}
		}
		else if (event.type == SDL_QUIT)
		{
			closeRequested = SDL_TRUE;
		}
	}
	
	update_ballsprites(&gameWindow, &rend, plateau); // Affichage de l'écran du jeu
	
	if (closeRequested)
	{
		SDL_DestroyTexture(homeScreenTexture);
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(gameWindow);
		SDL_Quit();
		
		return EXIT_SUCCESS;
	}
	
	while (!closeRequested)
	{
		SDL_WaitEvent(&event);
		if ((event.type == SDL_MOUSEBUTTONDOWN) && (SDL_GetMouseState(&clickedPoint.x, &clickedPoint.y) & SDL_BUTTON(SDL_BUTTON_LEFT)))
		// S'il y a eu clic gauche
		{
			if (clickedPoint.x <= 1300 * horizScaleFactor) // Si on a clqué du côté du plateau
			{
				j = (clickedPoint.x - xOffset)/28;
				i = (clickedPoint.y - yOffset)/50;
				if((i >= 0) && (i < L) && (j >= 0) && (j < C)) // Si on a cliqué dans le plateau
				{
					if(turn && (plateau[i][j] != NDEF) && (plateau[i][j] != VIDE)) // Si la case choisie contient une bille
					{
						ball.x = i; ball.y = j;
						if(select_pion(plateau, ball, selected, player)) // Si le pion peut être sélectionné
						{
							selectedBalls++;
							// Affichage du disque de sélection
							selectionRingSprite.x = xOffset + 28*j;
							selectionRingSprite.y = yOffset + 50*i;
							display_image_secure(gameWindow, rend, "images/anneau_vert.png", NULL, &selectionRingSprite, SDL_TRUE);
						}
						else // si ce pion n'est pas sélectionnable
						{
							printf("Selection annulee\n");
							annule_selected(selected); // La fonction devra aussi refresh l'affichage pour enlever les cercles verts
							update_ballsprites(&gameWindow, &rend, plateau);
						}
					}
				}
			}
			else //if (currentPoint.x >= 1300 * horizScaleFactor && currentPoint.y >= 1175 * vertScaleFactor) // Si on a cliqué du côté des contrôles
			{
				if (selectedBalls > 0) // Si au moins une bille est sélectionnée
				{
					// On attribue la valeur correspondante à direction
					if (point_is_in_rectangle(clickedPoint, arrowSprites[HG]))
						direction = HG;
					else if (point_is_in_rectangle(clickedPoint, arrowSprites[HD]))
						direction = HD;
					else if (point_is_in_rectangle(clickedPoint, arrowSprites[G]))
						direction = G;
					else if (point_is_in_rectangle(clickedPoint, arrowSprites[D]))
						direction = D;
					else if (point_is_in_rectangle(clickedPoint, arrowSprites[BG]))
						direction = BG;
					else if (point_is_in_rectangle(clickedPoint, arrowSprites[BD]))
						direction = BD;
					else
						printf("aucune fleche selectionnee\n");
				}
				
				if (direction != -1)
				{
					// déplacement en fonction de la direction
					SUMITOTYPE sumito = -1;
					if(playMode == J3){
						copy_tab(save,plateau);
					}
					if(mouvement(plateau, direction, player, selected, &sumito)){ // Mouvement réussi => Tour terminé, changement de joueur
						update_ballsprites(&gameWindow, &rend, plateau);
						
						direction = -1; // On annule la direction
						selectedBalls = 0;
						
						if(playMode == J2 || playMode == IA){							
							if(end_game(plateau)){
								printf("Partie terminée");
								save_score2j("NOIR",cpt_score(plateau,NOIR),"BLANC",cpt_score(plateau,BLANC));
								return 0;
							}
						}
						if(playMode == J3){
							if(player==NOIR){
								indice_joueur=0;
								score[indice_joueur]+=diff_pions(save,plateau);
							}
							if(player==BLANC){
								indice_joueur=1;
								score[indice_joueur]+=diff_pions(save,plateau);
							}
							if(player==ROUGE){
								indice_joueur=2;
								score[indice_joueur]+=diff_pions(save,plateau);
							}
							if(score[indice_joueur]==6){
								printf("Partie terminée");
								save_score3j("NOIR",score[0],"BLANC",score[1],"ROUGE",score[2]);
								return 0;
							}
						}
						
						if (playMode == J2){
							switch_player(playMode); // Changement de joueur
						}
						else if(playMode == J3){
							switch_player(playMode);
						}
						else{ // Mode IA
							play_IA(level_IA, &turn);
							update_ballsprites(&gameWindow, &rend, plateau);
						}
						
					}
				}
			}
		}
		else if (event.type == SDL_QUIT)
		{
			closeRequested = SDL_TRUE;
		}
	}

	SDL_DestroyTexture(homeScreenTexture);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
