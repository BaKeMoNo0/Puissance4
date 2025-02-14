/**
 * @file modeTextuelle.h
 * 
 * @author Yanis Le Guilcher et Ugo Courché
 * 
 * @version 1.0
 * @date 2023-01-08
 * @copyright Copyright (c) 2023
 * 
 * fichier contenant la plupart des fonctions utilisé pour le puissance 4 textuelle et le mode graphique
 */

/**
* @def J1
* @brief Caractère désignant le joueur 1
*/
#define J1 'X'
/**
* @def J2
* @brief Caractère désignant le joueur 2
*/
#define J2 'O'
/**
* @def NB_COLONNE
* @brief Le nombre de colonne du plateau
*/
#define NB_COLONNE 7
/**
* @def NB_RANGE
* @brief Le nombre de ligne du plateau
*/
#define NB_RANGE 6

typedef char joueur;

/**
* @struct PLATEAU
* @brief represente le plateau
*/
typedef struct {
    joueur tab[NB_RANGE][NB_COLONNE];
}PLATEAU;

/**
* @struct coord
* @brief repésente un couple de int
*/
typedef struct{
    int y;
    int x;
}coord;

/**
 * @brief Initialisation du plateau de jeu
 * 
 * @return PLATEAU 
 */
PLATEAU init(void);

/**
 * @brief Permet de passer d'un joueur a un autre
 * 
 * @param[in] player Le joueur qui vient de jouer
 * 
 * @return joueur Le joueur qui va jouer prochainement
 */
joueur cjoueur(joueur);

/**
 * @brief Permet de verifier si un joueur a gagné sur une ligne vertical
 * 
 * @param[in] p Le plateau du jeu
 * @param[in] c Le numero de colonne du dernier pion placé
 * @param[in] l Le numéro de ligne du dernier pion placé
 * 
 * @return true lorsque 4 pion sont aligné
 * @return false lorsque personne n'a gagné
 */
bool verticalLine(PLATEAU , char , char );

/**
 * @brief Permet de verifier si il y a une ligne en diagonal (haut gauche vers bas droit)
 * 
 * @param[in] p Le plateau de jeu
 * @param[in] c Le numero de colonne du dernier pion placé
 * @param[in] l Le numéro de ligne du dernier pion placé
 * 
 * @return true lorsque 4 pion sont aligné
 * @return false lorsque personne n'a gagné 
 */
bool diagLineD(PLATEAU , char , char );

/**
 * @brief Permet de verifier si il y a une ligne en diagonal (haut droit vers bas gauche)
 * 
 * @param[in] p Le plateau de jeu
 * @param[in] c Le numero de colonne du dernier pion placé
 * @param[in] l Le numéro de ligne du dernier pion placé
 * 
 * @return true lorsque 4 pion sont aligné
 * @return false lorsque personne n'a gagné
 */
bool diagLineG(PLATEAU , char , char );

/**
 * @brief Permet de verifier si une ligne horizontal est faite
 * 
 * @param[in] p Le plateau de jeu
 * @param[in] c Le numero de colonne du dernier pion placé
 * @param[in] l Le numéro de ligne du dernier pion placé
 * 
 * @return true lorsque 4 pion sont aligné
 * @return false lorsque personne n'a gagné
 */
bool horizontalLine(PLATEAU , char, char );

/**
 * @brief Permet d'ajouter un pion dans le plateau
 * 
 * @param[in,out] p Un pointeur sur le plateau de jeu qui permet de modifier celui-ci
 * @param[in] player Le joueur a qui ont va ajouter son pion
 * 
 * @return pos corespond au coordonné du pion ajouter. Il permet de faciliter la recherche du gagnant
 */
coord ajouter(PLATEAU* , char );

/**
 * @brief Permet d'afficher le plateau de jeu en textuelle
 * 
 * @param[in] p Le plateau de jeu
 */
void affiche(PLATEAU );

/**
 * @brief Permet de relier toute les autres fonction qui verifie si 4 pions sont aligné. Elle sera appelé dans la fonction main
 * 
 * @param[in] p le plateau de jeu
 * @param[in] pion les coordoné du dernier pion ajouter
 * 
 * @return true lorsqu'il y a un gagnant
 * @return false lorsqu'il n'y a aucun gagant
 */
bool gagnant(PLATEAU , coord );

/**
 * @brief Permet d'afficher le menu global du puissance 4 et choisir le mode textuelle ou le mode graphique
 * 
 * @return int est le numero du mode. 1 pour le textuelle et 2 pour le mode graphique
 */
int menuGlobal(void);

/**
 * @brief Permet d'afficher le menu textuelle du puissance 4 et de choisir son mode parmi les 4.
 * 
 * @return int est le numéro du mode choisi.1 pour Human VS Human, 2 pour Human VS IA, 3 pour IA VS Human et 4 pour IA VS IA
 */
int menu(void);

/**
 * @brief Permet de choisir la difficulté de l'IA parmis les 3 possibles
 * 
 * @param[in] IA permet de savoir si il y a 1 ou 2 IA dans la parti. 0 pour les mode comptant 1 IA et 1 pour le mode IA VS IA
 * 
 * @return int le numéro de difficulté de l'IA. 1 pour facile, 2 pour normal et 3 pour difficile
 */
int difficult(int); 