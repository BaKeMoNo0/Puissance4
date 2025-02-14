/**
 * @file ia.h
 * 
 * @author Yanis Le Guilcher
 * 
 * @version 1.0
 * @date 2023-01-08
 * @copyright Copyright (c) 2023
 * 
 * Fichier contenant les fonction utilisé pour l'ia
 */

/**
 * @brief Permet d'ajouter dans le plateau pour une IA
 * 
 * @param[in,out] p Un pointeur sur le plateau de jeu qui permet de modifier celui-ci
 * @param player Le joueur a qui on va ajouter un pion
 * @param colo Le numéro de colonne ou l'on va ajouter un pion
 * 
 * @return les coordonnées corespondant au pion ajouté
 */
coord ajouterIA(PLATEAU * , joueur , int );

/**
 * @brief Permet de savoir le score des colonnes en fonction de leur taux de réussite
 * 
 * @param[in] p Le plateau de jeu
 * @param[in] diff le niveau de difficulté de l'IA. 2 pour facile, 4 pour normal et 6 pour difficile
 * @param[in] colo le numero de colonne ou on effectue le test
 * @param[in] coef le nombre de coup qu'il reste a anticipé inversement proportionel a la profondeur du test
 * @param[in] player le joueur qui va jouer
 * 
 * @return un entier qui est le score qu'obtient 
 */
int MinMax(PLATEAU , int , int , int , joueur );

/**
 * @brief La fonction appelée dans le main qui permet de choisir la colonne ou l'IA va jouer
 * 
 * @param[in] p Le plateau de jeu
 * @param[in] diff le niveau de difficulté des IA. 2 pour facile, 4 pour normal et 6 pour difficile
 * 
 * @return un entier corespondant a la colonne choisi
 */
int colochoiceIA(PLATEAU , int );

/**
 * @brief Permet de remettre le tableau colopleine a false lorsque l'on rejoue
 * 
 */
void settab(void);