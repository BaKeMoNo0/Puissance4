#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "modeTextuelle.h"


/**
 * @brief Permet de relier toute les autres fonction qui verifie si 4 pions sont aligné. Elle sera appelé dans la fonction main
 * 
 * @param[in] p Le plateau de jeu
 * @param pion 
 * 
 * @return int 
 */
int gagnantG(PLATEAU p, coord pion) {
    if(verticalLine(p, pion.x, pion.y)) {
        return 1;
    }
    if(horizontalLine(p, pion.x, pion.y)) {
        return 2;
    }
    if(diagLineD(p, pion.x, pion.y)) {
        return 3;
    }
    if(diagLineG(p, pion.x, pion.y)) {
        return 4;
    }
    return 0;
}


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
coord ajouterG(PLATEAU* p, char joueur, int colo) {
    coord pos;
    char i=5;
    while(i > -1 && p->tab[i][colo-1] != ' ') {
        i--;
    }
    p->tab[i][colo-1] = joueur;
    pos.y = i;
    pos.x = colo-1;
    return pos;
}


/**
 * @brief Permet de dessiner des lignes horizontale
 * 
 * @param renderer 
 * @param[in] x1 abscisse du premier point
 * @param[in] y ordonnée des deux points
 * @param[in] x2 abscisse du deuxième point
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int ligneHorizontale(SDL_Renderer *renderer, int x1, int y, int x2){
    x1 += (1920/25.5);
    x2 += (1920/25.5);
    y += (1080/14);
    if (SDL_RenderDrawLine(renderer, x1, y, x2, y)) {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return 1;
    }
    return 0;
}


/**
 * @brief Permet de créer un pion
 * 
 * @param renderer 
 * @param[in] cx abscisse du centre du cercle
 * @param[in] cy ordonnée du centre du cercle
 * @param[in] rayon rayon du cercle
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int disque(SDL_Renderer *renderer, int cx, int cy, int rayon) {
    int d, y, x;
    
    d = 3 - (2 * rayon);
    x = 0;
    y = rayon;
 
    while (y >= x) {
        if (ligneHorizontale(renderer, cx - x, cy - y, cx + x) || ligneHorizontale(renderer, cx - x, cy + y, cx + x) || 
            ligneHorizontale(renderer, cx - y, cy - x, cx + y) || ligneHorizontale(renderer, cx - y, cy + x, cx + y)) {
                fprintf(stderr, "Erreur ligneHorizontale : %s", SDL_GetError());
                return 1;
            }
    
        if (d < 0) {
            d = d + (4 * x) + 6;
        } else {
        d = d + 4 * (x - y) + 10;
        y--;
        }
        x++;
    }
    return 0;
}


/**
 * @brief Permet d'afficher le plateau
 * 
 * @param renderer 
 * @param[in] p Le plateau de jeu
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int affichePlateau(SDL_Renderer *renderer, PLATEAU p) {
    int k = 0, x = 0, y = 0;
    for(int v = 0; v < NB_RANGE; v++) {
        for(int u = 0; u < NB_COLONNE; u++) {
            x = 129 * u + (1920/3.85);
            y = 129 * v + (1080/5.5);
            if(p.tab[v][u] == J1) {
                if(SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0) {
                    fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
                    return 1;
                }
                if(disque(renderer, x, y, 58)) {
                    fprintf(stderr, "Erreur disque : %s", SDL_GetError());
                    return 1;
                }
            } else if(p.tab[v][u] == J2) {
                if(SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE) != 0) {
                    fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
                    return 1;
                }
                if(disque(renderer, x, y, 60)) {
                    fprintf(stderr, "Erreur disque : %s", SDL_GetError());
                    return 1;
                }
            } else if (p.tab[v][u] == 'G') {
                if(SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE) != 0) {
                    fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
                    return 1;
                }
                if(disque(renderer, x, y, 60)) {
                    fprintf(stderr, "Erreur disque : %s", SDL_GetError());
                    return 1;
                }
            }
            k++;
        }
    }
    SDL_RenderPresent(renderer);
    return 0;
}


/**
 * @brief Permet de récupérer une image au format bmp et de la transformer en texture et de la copier dans le renderer
 * 
 * @param renderer est un zone permettant de dessiner des figures ou mettre des images
 * @param[in] nom Une str qui contient le nom du fichier de l'image
 * @param[in,out] texture Un pointeur sur la texture utilisable
 * 
 * @return 1 si la fonction a eu une erreur et 0 si la fonction a belle et bien fonctionné
 */
int ajoutImage(SDL_Renderer *renderer, char *nom, SDL_Texture *texture) {
    SDL_Surface *surf = NULL;

    surf = SDL_LoadBMP(nom);
    if(surf == NULL) {
        fprintf(stderr, "Erreur impossible de charger l'image : %s", SDL_GetError());
        return 1;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    if(texture == NULL) {
        fprintf(stderr, "Erreur impossible de créer la texture : %s", SDL_GetError());
        return 1;
    }
    SDL_Rect rect;

    if(SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) != 0) {
        fprintf(stderr, "Erreur impossible de charger la texture : %s", SDL_GetError());
        return 1;
    }
    
    rect.x = (1920 - rect.w)  / 2;
    rect.y = (1080 - rect.h) / 2;

    if(SDL_RenderCopy(renderer, texture, NULL, &rect) != 0) {
        fprintf(stderr, "Erreur impossible d'afficher la texture : %s", SDL_GetError());
        return 1;
    }

    SDL_RenderPresent(renderer);
    return 0;
}


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
int winLine(SDL_Renderer *renderer, PLATEAU p, coord tpos, char joueur, bool *jeu) {
    int g = gagnantG(p, tpos);
    if(g == 1) {
        coord tmp = tpos;
        for(int a = 0; a < 4; a++) {
            p.tab[tmp.y][tmp.x] = 'G';
            tmp.y++;
            if(affichePlateau(renderer, p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            }
            SDL_Delay(300);
        }
        *jeu = false;
        return 0;
    } else if (g == 2) {
        coord tmp = tpos;
        while(tmp.x -1 >= 0 && p.tab[tmp.y][tmp.x-1] == joueur) {
            tmp.x--;
        }
        while(tmp.x < 7 && p.tab[tmp.y][tmp.x] == joueur) {
            p.tab[tmp.y][tmp.x] = 'G';
            tmp.x++;
            if(affichePlateau(renderer, p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            }
            SDL_Delay(400);
        }
        *jeu = false;
        return 0;
    } else if (g == 3) {
        coord tmp = tpos;
        while(tmp.y > -1 && tmp.x > -1 && p.tab[tmp.y][tmp.x] == joueur) {
            tmp.y--;
            tmp.x--;
        }
        while(tmp.y + 1 < 6 && tmp.x + 1 < 7 && p.tab[tmp.y+1][tmp.x+1] == joueur) {
            p.tab[tmp.y+1][tmp.x+1] = 'G';
            tmp.y++;
            tmp.x++;
            if(affichePlateau(renderer, p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            }
            SDL_Delay(400);
        }
        *jeu = false;
        return 0;
    } else if (g == 4) {
        coord tmp = tpos;
        while(tmp.y + 1 < 6 && tmp.x - 1 > -1 && p.tab[tmp.y+1][tmp.x-1] == joueur) {
            tmp.y++;
            tmp.x--;
        }
        while(tmp.y > -1 && tmp.x > -1 && p.tab[tmp.y][tmp.x] == joueur) {
            p.tab[tmp.y][tmp.x] = 'G';
            tmp.y--;
            tmp.x++;
            if(affichePlateau(renderer, p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            }
            SDL_Delay(400);
        }
        *jeu = false;
        return 0;
    }
}


/**
 * @brief Permet de savoir si le plateau est rempli
 * 
 * @param[in] p Le plateau de jeu
 * 
 * @return 1 si le plateau est rempli sinon 0
 */
int platPlein(PLATEAU p) {
    for(int i = 0; i < NB_RANGE; i++) {
        for(int j = 0; j < NB_COLONNE; j++) {
            if(p.tab[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

 
/**
 * @brief 
 * 
 * @param p 
 * @param renderer 
 * @param px position du curseur par rapport à l'abscisse
 * @param py position du curseur par rapport à l'ordonnée
 * @param coloPleine permet de savoir si une colonne du plateau est pleine 
 * tableau de int de taille 7(nb de colonne), qui est incrémenté à chaque fois qu'il y a un ajout de pion dans le plateau
 * @param player le joueur actuellement en train de jouer
 * @param tpos couple de int où est ajouté le pion dans le plateau
 * @param jeu un boleen qui sera modifié à false lorsque la partie se fini afin d'arrêter la boucle while dans le main
 * @return 1 si un problème est survenu avec des éléments de la SDL
 */
int deplacement(PLATEAU *p, SDL_Renderer *renderer, int px, int py, int *coloPleine, joueur *player, coord *tpos, bool *jeu) {
    if (px > 512  && px < 625 && py >199 && py < 990){   
        if(coloPleine[0] != 6) {
            coloPleine[0]++;
            *tpos=ajouterG(p,*player, 1);
            if(affichePlateau(renderer, *p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            } 
            if(winLine(renderer, *p, *tpos, *player, jeu)) {
                fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                return 1;
            } 
            if (gagnantG(*p, *tpos) == 0) {
                *player = cjoueur(*player);
            }
            if(platPlein(*p)) {
                *jeu = false;
            }
        }
    }

    if(px > 644 && px < 755  && py > 199 && py < 990) {
        if(coloPleine[1] != 6) {
            coloPleine[1]++;
            *tpos=ajouterG(p,*player, 2);
            if(affichePlateau(renderer, *p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            } 
            if(winLine(renderer, *p, *tpos, *player, jeu)) {
                fprintf(stderr, "Erreur winLine : %s", SDL_GetError());
                return 1;
            } 
            if (gagnantG(*p, *tpos) == 0) {
                *player = cjoueur(*player);
            }
            if(platPlein(*p)) {
                *jeu = false;
            }
        }
    }

    if(px > 777 && px < 887  && py > 199 && py < 990) {
        if(coloPleine[2] != 6) {
            coloPleine[2]++;
            *tpos=ajouterG(p,*player, 3);
            if(affichePlateau(renderer, *p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            } 
            if(winLine(renderer, *p, *tpos, *player, jeu)) {
                fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                return 1;
            } 
            if (gagnantG(*p, *tpos) == 0) {
                *player = cjoueur(*player);
            }
            if(platPlein(*p)) {
                *jeu = false;
            }
        }
    }

    if(px > 909 && px < 1018  && py > 199 && py < 990) {
        if(coloPleine[3] != 6) {
            coloPleine[3]++;
            *tpos=ajouterG(p,*player, 4);
            if(affichePlateau(renderer, *p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            } 
            if(winLine(renderer, *p, *tpos, *player, jeu)) {
                fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                return 1;
            } 
            if (gagnantG(*p, *tpos) == 0) {
                *player = cjoueur(*player);
            }
            if(platPlein(*p)) {
                *jeu = false;
            }
        }
    }
    if(px > 1039 && px < 1147  && py > 199 && py < 990) {
        if(coloPleine[4] != 6) {
            coloPleine[4]++;
            *tpos=ajouterG(p,*player, 5);
            if(affichePlateau(renderer, *p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            } 
            if(winLine(renderer, *p, *tpos, *player, jeu)) {
                fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                return 1;
            } 
            if (gagnantG(*p, *tpos) == 0) {
                *player = cjoueur(*player);
            }
            if(platPlein(*p)) {
                *jeu = false;
            }
        }
    }

    if(px > 1171 && px < 1279  && py > 199 && py < 990) {
        if(coloPleine[5] != 6) {
            coloPleine[5]++;
            *tpos=ajouterG(p,*player, 6);
            if(affichePlateau(renderer, *p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            } 
            if(winLine(renderer, *p, *tpos, *player, jeu)) {
                fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                return 1;
            } 
            if (gagnantG(*p, *tpos) == 0) {
                *player = cjoueur(*player);
            }
            if(platPlein(*p)) {
                *jeu = false;
            }
        }
    }
    if(px > 1302 && px < 1411  && py > 199 && py < 990) {
        if(coloPleine[6] != 6) {
            coloPleine[6]++;
            *tpos=ajouterG(p,*player, 7);
            if(affichePlateau(renderer, *p)) {
                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                return 1;
            } 
            if(winLine(renderer, *p, *tpos, *player, jeu)) {
                fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                return 1;
            } 
            if (gagnantG(*p, *tpos) == 0) {
                *player= cjoueur(*player);
            }
            if(platPlein(*p)) {
                *jeu = false;
            }
        }
    } 
    return 0; 
}

