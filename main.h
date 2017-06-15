#include "abalone.h"

/* Variables globales */

COORDS selected[3]; // Tableau contenant les pions séléctionnés

CASE plateau[L][C] = 
{{3, 3, 3, 3, B, 3, B, 3, B, 3, B, 3, B, 3, 3, 3, 3},
{3, 3, 3, B, 3, B, 3, B, 3, B, 3, B, 3, B, 3, 3, 3},
{3, 3, 2, 3, 2, 3, B, 3, B, 3, B, 3, 2, 3, 2, 3, 3},
{3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3},
{2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2},
{3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3},
{3, 3, 2, 3, 2, 3, N, 3, N, 3, N, 3, 2, 3, 2, 3, 3},
{3, 3, 3, N, 3, N, 3, N, 3, N, 3, N, 3, N, 3, 3, 3},
{3, 3, 3, 3, N, 3, N, 3, N, 3, N, 3, N, 3, 3, 3, 3}};

CASE plateau_3v[L][C] = 
{{3, 3, 3, 3, B, 3, B, 3, 2, 3, N, 3, N, 3, 3, 3, 3},
{3, 3, 3, B, 3, B, 3, 2, 3, 2, 3, N, 3, N, 3, 3, 3},
{3, 3, B, 3, B, 3, 2, 3, 2, 3, 2, 3, N, 3, N, 3, 3},
{3, B, 3, B, 3, 2, 3, 2, 3, 2, 3, 2, 3, N, 3, N, 3},
{B, 3, B, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, N, 3, N},
{3, B, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, N, 3},
{3, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 3},
{3, 3, 3, R, 3, R, 3, R, 3, R, 3, R, 3, R, 3, 3, 3},
{3, 3, 3, 3, R, 3, R, 3, R, 3, R, 3, R, 3, 3, 3, 3}}; 

//Matrice de Poids pour l'IA
int position_weight[L][C] =
{
	{0, 0, 0, 0, 100, 0, 100, 0, 100, 0, 100, 0, 100, 0, 0, 0, 0},
	{0, 0, 0, 100, 0, 500, 0, 500, 0, 500, 0, 500, 0, 100, 0, 0, 0},
	{0, 0, 100, 0, 500, 0, 750, 0, 750, 0, 750, 0, 500, 0, 100, 0, 0},
	{0, 100, 0, 500, 0, 750, 0, 850, 0, 850, 0, 750, 0, 500, 0, 100, 0},
	{100, 0, 500, 0, 750, 0, 850, 0, 1000, 0, 850, 0, 750, 0, 500, 0, 100},
	{0, 100, 0, 500, 0, 750, 0, 850, 0, 850, 0, 750, 0, 500, 0, 100, 0},
	{0, 0, 100, 0, 500, 0, 750, 0, 750, 0, 750, 0, 500, 0, 100, 0, 0},
	{0, 0, 0, 100, 0, 500, 0, 500, 0, 500, 0, 500, 0, 100, 0, 0, 0},
	{0, 0, 0, 0, 100, 0, 100, 0, 100, 0, 100, 0, 100, 0, 0, 0, 0}
};

JOUEUR player = NOIR;


DIRECTION AlphaBeta(CASE board[L][C], int depth, int alpha, int beta, JOUEUR joueur, COORDS tableau[3]);
void add_tab(COORDS tab[3], COORDS pos);
void affiche_plateau();
void affiche_plateau2(CASE tab[L][C]);
void affiche_selected(COORDS tableau[3]);
void affiche_tableau(COORDS tab[3]);
liste ajoutDebut(liste list, COORDS tableau[3]);
void annule_selected(COORDS tableau[3]);
int broadside_move(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3]);
int check_selected(COORDS tableau[3], COORDS position);
void copy_tab(CASE new_tab[L][C], CASE tab[L][C]);
void copy_tab_coords(COORDS new_tab[3], COORDS tab[3]);
int count_neighbors(CASE board[L][C], COORDS pos, JOUEUR joueur);
int count_selected(COORDS tableau[3]);
int cpt_score(CASE board[L][C], JOUEUR joueur);
int diff_pions(CASE old_board[L][C],CASE board[L][C]);
void empty_tab(COORDS tab[3]);
int end_game(CASE board[L][C]);
int eval_board(CASE board[L][C], JOUEUR joueur);
liste get_ally_marble(CASE board[L][C], JOUEUR joueur);
liste get_case(CASE board[L][C], COORDS pos, liste list, JOUEUR joueur);
int has_ally_next(CASE board[L][C], COORDS p, DIRECTION d, JOUEUR j);
int has_next(CASE board[L][C], COORDS p, DIRECTION d);
int in_array(COORDS pos, COORDS tab[3]);
int inline_move(CASE board[L][C], DIRECTION d, JOUEUR joueur,COORDS tableau[3], SUMITOTYPE** sumito);
int is_in_board(CASE board[L][C], COORDS p);
int is_pion(CASE board[L][C], COORDS position, JOUEUR joueur);
int is_valid(COORDS tableau[3], COORDS position);
int main();
int max(int a, int b);
int maximize(CASE board[L][C], int depth, int alpha, int beta, JOUEUR joueur);
int min(int a, int b);
int minimize(CASE board[L][C], int depth, int alpha, int beta, JOUEUR joueur);
int mouvement(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3], SUMITOTYPE* sumito);
void mouvement_simple(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3]);
MVTYPE mouvement_type(DIRECTION d, COORDS tableau[3]);
void next_coord(COORDS* p, DIRECTION d);
COORDS next_coord2(COORDS p, DIRECTION d);
void play_IA(int level, int *turn);
void print_list(liste list);
void save_score2j(char joueur1[], int score1, char joueur2[], int score2);
void save_score3j(char joueur1[], int score1, char joueur2[], int score2, char joueur3[], int score3);
int select_pion(CASE board[L][C], COORDS position, COORDS tableau[3], JOUEUR joueur);
void simule_1v1_game(CASE board[L][C],char joueur1[], char joueur2[]);
void simule_1v1v1_game(CASE board[L][C], char joueur1[], char joueur2[], char joueur3[]);
void simule_game(JOUEUR joueur);
void sumito_2contre1(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3]);
void sumito_3contre1(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3]);
void sumito_3contre2(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tableau[3]);
void switch_player(MODE mode);
void undo_move(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tab[3], SUMITOTYPE sumito);
void undo_sumito_2vs1(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tab[3]);
void undo_sumito_3vs1(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tab[3]);
void undo_sumito_3vs2(CASE board[L][C], DIRECTION d, JOUEUR joueur, COORDS tab[3]);
