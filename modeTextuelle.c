#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "modeTextuelle.h"

/**
 * @brief Initialisation du plateau de jeu
 * 
 * @return PLATEAU 
 */
PLATEAU init(void) {
    PLATEAU p;
    for(unsigned short i=0;i<NB_RANGE;i++) {
        for(unsigned short j=0;j<NB_COLONNE;j++) {
            p.tab[i][j]= ' ';
        }
    }
    return p;
}

/**
 * @brief Permet de passer d'un joueur a un autre
 * 
 * @param[in] player Le joueur qui vient de jouer
 * 
 * @return joueur Le joueur qui va jouer prochainement
 */
joueur cjoueur(joueur player) {
    if(player==J1) {
        return J2;
    }
    else {
        return J1;
    }
}

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
bool verticalLine(PLATEAU p, char c, char l) {
    int cpt = 0;
    if(p.tab[l][c] == J1 || p.tab[l][c] == J2) {
        char sym = p.tab[l][c];
        while(l < 6 && p.tab[l][c] == sym) {
            cpt++;
            l++;
        }
        if(cpt >= 4) {
            return true;
        }
    }
    return false;
}

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
bool diagLineD(PLATEAU p, char c, char l) {
    int tl=l;
    int tc=c;
    int cpt = 0;

    if(p.tab[l][c] == J1 || p.tab[l][c] == J2) {

        char sym = p.tab[l][c];

        //test diagonal haut gauche vers bas droit
        while(tl+1 < 6 && tc+1 < 7 && p.tab[tl+1][tc+1] == sym) {
            tl++;
            tc++;
        }
        while(tl > -1 && tc > -1 && p.tab[tl][tc] == sym) {
            cpt++;
            tl--;
            tc--;
        }
        if(cpt >= 4) {
            return true;
        }
    }
    return false;
}


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
bool diagLineG(PLATEAU p, char c, char l) {
    int tl=l;
    int tc=c;
    int cpt = 0;

    if(p.tab[l][c] == J1 || p.tab[l][c] == J2) {
        joueur sym = p.tab[l][c];
        //test diagonal haut droit vers bas gauche
        while(tl+1 < 6 && tc-1 > -1 && p.tab[tl+1][tc-1] == sym) {
            tl++;
            tc--;
        }
        while(tl > -1 && tc > -1 && tc < 7 && tl < 6 && p.tab[tl][tc] == sym) {
            cpt++;
            tl--;
            tc++;
        }
        if(cpt >= 4) {
            return true;
        }
    }
    return false;
}

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
bool horizontalLine(PLATEAU p, char c, char l) {
    int cpt = 0;
    char tmp = 0;
    if (p.tab[l][c] == J1 || p.tab[l][c] == J2) {
        char sym = p.tab[l][c];
        if(c <= 6) {
            tmp = c + 1;
            while (c > -1 && p.tab[l][c] == sym) {
                cpt++;
                c--;
            }
        }
        while(tmp < 7 && p.tab[l][tmp] == sym) {
            cpt++;
            tmp++;
        }
        if(cpt >= 4) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Permet d'ajouter un pion dans le plateau
 * 
 * @param[in,out] p Un pointeur sur le plateau de jeu qui permet de modifier celui-ci
 * @param[in] player Le joueur a qui ont va ajouter son pion
 * 
 * @return pos corespond au coordonné du pion ajouter. Il permet de faciliter la recherche du gagnant
 */
coord ajouter(PLATEAU* p, joueur player) {
    coord pos;
    int colo;
    char * colot=malloc(sizeof(char)*20);
    char i=5;
    scanf("%s", colot);
    colo=atoi(colot);

    // si ca afficher 0 alors ce n'est pas un chiffre
    while(colo > 7 || colo < 1) {
        printf("La colonne n'existe pas, veuillez saisir un chiffre entre 1 et 7 : ");
        scanf("%s", colot);
        colo=atoi(colot);
        printf("\n");
    }
    while(i > -1 && p->tab[i][colo-1] != ' ') {
        while(colo > 7 || colo < 1) {
            printf("La colonne n'existe pas, veuillez saisir un chiffre entre 1 et 7 : ");
            scanf("%s", colot);
            colo=atoi(colot);
            printf("\n");
        }
        if(p->tab[0][colo-1] != ' ') {
            i = 5;
            printf("La colonne est complete, veuillez saisir un chiffre différent : ");
            scanf("%s", colot);
            colo=atoi(colot);
        } else {
            i--;
        }
    }
    p->tab[i][colo-1]=player;
    pos.y=i;
    pos.x=colo-1;
    free(colot);
    return pos;
}


/**
 * @brief Permet d'afficher le plateau de jeu en textuelle
 * 
 * @param[in] p Le plateau de jeu
 */
void affiche(PLATEAU p) {
    for(int x = 1; x < 8; x++) {
        printf("  %d ", x);
    }
    printf("\n");
    for(int i = 0; i < NB_RANGE; i++) {
        printf("\033[34m-----------------------------\n");
        for(int j = 0; j < NB_COLONNE; j++) {
            if(p.tab[i][j]==J1) {
                if (j == NB_COLONNE - 1) {
                    printf("| \033[31mO\033[34m |");
                }
                else {
                    printf("| \033[31mO\033[34m ");
                }
            }
            else if(p.tab[i][j]==J2) {
                if (j == NB_COLONNE - 1) {
                    printf("| \033[32mO\033[34m |");
                }
                else {
                    printf("| \033[32mO\033[34m ");
                }
            }
            else {
                if (j == NB_COLONNE - 1) {
                    printf("|   |");
                }
                else {
                    printf("|   ");
                }
            }
        }
        printf("\n");
    }
    printf("-----------------------------\033[00m\n");
}

/**
 * @brief Permet de relier toute les autres fonction qui verifie si 4 pions sont aligné. Elle sera appelé dans la fonction main
 * 
 * @param[in] p le plateau de jeu
 * @param[in] pion les coordoné du dernier pion ajouter
 * 
 * @return true lorsqu'il y a un gagnant
 * @return false lorsqu'il n'y a aucun gagant
 */
bool gagnant(PLATEAU p, coord pion) {
    if(verticalLine(p, pion.x, pion.y)) {
        return true;
    }
    if(horizontalLine(p, pion.x, pion.y)) {
        return true;
    }
    if(diagLineG(p, pion.x, pion.y)) {
        return true;
    }
    if(diagLineD(p, pion.x, pion.y)) {
        return true;
    }
    return false;
}

/**
 * @brief Permet d'afficher le menu global du puissance 4 et choisir le mode textuelle ou le mode graphique
 * 
 * @return int est le numero du mode. 1 pour le textuelle et 2 pour le mode graphique
 */
int menuGlobal(void) {
    int t;
    char * choix=malloc(sizeof(char)*20);
    printf("\tPuissance 4\n1.Mode textuelle\n2.Mode graphique\nVeuillez saisir le chiffre 1 ou 2 : ");
    scanf("%s", choix);
    t=atoi(choix);
    while(t > 2 || t < 1) {
        printf("Erreur de saisie, Veuillez saisir le chiffre 1 ou 2 : ");
        scanf("%s", choix);
        t = atoi(choix);
    }
    printf("\n\n");
    free(choix);
    return t;
}

/**
 * @brief Permet d'afficher le menu textuelle du puissance 4 et de choisir son mode parmi les 4.
 * 
 * @return int est le numéro du mode choisi.1 pour Human VS Human, 2 pour Human VS IA, 3 pour IA VS Human et 4 pour IA VS IA
 */
int menu(void) {
    int t;
    char * choix=malloc(sizeof(char)*20);
    printf("\tPuissance 4\n1.Human VS Human\n2.Human VS IA\n3.IA VS Human\n4.IA VS IA\nVeuillez saisir un chiffre entre 1 et 4 : ");
    scanf("%s", choix);
    t=atoi(choix);
    while(t > 4 || t < 1) {
        printf("Erreur de saisie, Veuillez saisir un chiffre entre 1 et 4 : ");
        scanf("%s", choix);
        t = atoi(choix);
    }
    printf("\n\n");
    free(choix);
    return t;
}

/**
 * @brief Permet de choisir la difficulté de l'IA parmis les 3 possibles
 * 
 * @param[in] IA permet de savoir si il y a 1 ou 2 IA dans la parti. 0 pour les mode comptant 1 IA et 1 pour le mode IA VS IA
 * 
 * @return int le numéro de difficulté de l'IA. 1 pour facile, 2 pour normal et 3 pour difficile
 */
int difficult(int IA) {
    char * diff = malloc(sizeof(char)*20);
    int d;
    system("clear");
    switch(IA) {
        case 0: printf("Choissisez le niveau de difficulté\n"); break;
        case 1: printf("Choissisez le niveau de l'IA 1 (\033[31mO\033[00m)\n"); break;
        case 2: printf("Choissisez le niveau de l'IA 2 (\033[32mO\033[00m)\n"); break;
    }
    printf("1.Facile\n2.Normal\n3.Difficile\nVeuillez saisir le chiffre 1 ou 2 ou 3 :");
    scanf("%s", diff);
    d = atoi(diff);
    while(d < 1 || d > 3) {
        printf("Erreur de saisie, veuillez resaisir une difficulté entre  1 et 3:");
        scanf("%s", diff);
        d = atoi(diff);
    }
    free(diff);
    return d;
}