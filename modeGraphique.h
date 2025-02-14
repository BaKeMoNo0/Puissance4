/**
 * @file modeGraphique.h
 * 
 * @author Ugo Courché
 * 
 * @version 1.0
 * @date 2023-01-08
 * @copyright Copyright (c) 2023
 * 
 * Fichier contenant les fonction utilisé pour le mode graphique avec la bibliothèque SDL2
 */

/**
 * @brief Permet de relier toute les autres fonction qui verifie si 4 pions sont aligné. Elle sera appelé dans la fonction main
 * 
 * @param[in] p Le plateau de jeu
 * @param pion Les coordonné du dernier pion ajouté
 * 
 * @return int 
 */
int gagnantG(PLATEAU , coord );

/**
 * @brief Permet d'ajouter l'un des symboles suivants dans une case du plateau : O ou X 
 *        l'utilisateur va saisir un chiffre compris entre 1 et 7 correspondant à la colonne où le symbole sera positioné
 * 
 * @param[in,out] p Un pointeur sur le plateau de jeu qui permet de le modifier
 * @param[in] joueur le joueur a qui on va ajouter un pion
 * @param[in] colo La colonne dans laquel on va ajouter le pion
 * 
 * @return pos qui corespond au coordoné du pion ajouter
 */
coord ajouterG(PLATEAU* , char , int );

/**
 * @brief Permet de dessiner des lignes horizontale
 * 
 * @param renderer est un zone permettant de dessiner des figures ou mettre des images
 * @param[in] x1 abscisse du premier point
 * @param[in] y ordonnée des deux points
 * @param[in] x2 abscisse du deuxième point
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int ligneHorizontale(SDL_Renderer * , int , int , int );

/**
 * @brief Permet de créer un pion
 * 
 * @param renderer est un zone permettant de dessiner des figures ou mettre des images
 * @param[in] cx abscisse du centre du cercle
 * @param[in] cy ordonnée du centre du cercle
 * @param[in] rayon rayon du cercle
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int disque(SDL_Renderer * , int , int , int );

/**
 * @brief Permet d'afficher le plateau
 * 
 * @param renderer est un zone permettant de dessiner des figures ou mettre des images
 * @param[in] p Le plateau de jeu
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int affichePlateau(SDL_Renderer * , PLATEAU );

/**
 * @brief Permet de récupérer une image au format bmp et de la transformer en texture et de la copier dans le renderer
 * 
 * @param renderer est un zone permettant de dessiner des figures ou mettre des images
 * @param[in] nom Une str qui contient le nom du fichier de l'image
 * @param[in,out] texture Un pointeur sur la texture utilisable
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int ajoutImage(SDL_Renderer * , char * , SDL_Texture * );

/**
 * @brief Permet de faire une animation ou chaque pion d'une ligne gagnante est colorié en vert
 * 
 * @param renderer est un zone permettant de dessiner des figures ou mettre des images
 * @param[in] p Le plateau du jeu
 * @param[in] tpos //jsp c koi
 * @param[in] joueur Le joueur qui a gagné
 * @param[in,out] jeu un pointeur sur //jsp
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int winLine(SDL_Renderer * , PLATEAU , coord , char , bool * );

/**
 * @brief Permet de savoir si le plateau est rempli
 * 
 * @param[in] p Le plateau de jeu
 * 
 * @return 1 si le plateau est rempli sinon 0
 */
int platPlein(PLATEAU );

/**
 * @brief Permet de verifier dans quelle colonne le curseur se trouve et y ajoute un pion si il le peut
 * 
 * @param p Le plateau de jeu
 * @param renderer Zone dans laquel on peut dessisner
 * @param px position du curseur par rapport à l'abscisse
 * @param py position du curseur par rapport à l'ordonnée
 * @param coloPleine permet de savoir si une colonne du plateau est pleine 
 * tableau de int de taille 7(nb de colonne), qui est incrémenté à chaque fois qu'il y a un ajout de pion dans le plateau
 * @param player le joueur actuellement en train de jouer
 * @param tpos couple de int où est ajouté le pion dans le plateau
 * @param jeu un boleen qui sera modifié à false lorsque la partie se fini afin d'arrêter la boucle while dans le main
 * @return 1 si un problème est survenu avec des éléments de la SDL
 */
int deplacement(PLATEAU* , SDL_Renderer *, int , int , int *, joueur* , coord* , bool* ); 