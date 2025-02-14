#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "modeTextuelle.h"
#include "ia.h"


/**
 * @brief Une variable permettant de restreindre les colonnes pleines
 */
int colopleine[7]={false};


/**
 * @brief Permet de remettre le tableau colopleine a false lorsque l'on rejoue
 * 
 */
void settab(void) {
    for(int i=0;i<7;i++) {
        colopleine[i]=false;
    }
}


/**
 * @brief Permet d'ajouter dans le plateau pour une IA
 * 
 * @param[in,out] p Un pointeur sur le plateau de jeu qui permet de modifier celui-ci
 * @param player Le joueur a qui on va ajouter un pion
 * @param colo Le numéro de colonne ou l'on va ajouter un pion
 * 
 * @return les coordonnées corespondant au pion ajouté
 */
coord ajouterIA(PLATEAU * p, joueur player, int colo) {
    coord pos;
    char i = 5;
    while(i > -1 && p->tab[i][colo] != ' ') {
        i--;
        if(i < 0) {
            pos.y=i;
            pos.x=colo;
            return pos;
        }
    }
    p->tab[i][colo]=player;
    pos.y = i;
    pos.x = colo;
    return pos;
}


/**
 * @brief Fonction puissance
 * 
 * @param[in] n Le nombre sur lequel on applique la puissance p
 * @param[in] p l'exposant
 * 
 * @return un entier est égale a n puissance p
 */
int mpow(int n, int p) {
    int r=1;
    for(int i=0;i<p;i++) {
        r*=n;
    }
    return r;
}


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
int MinMax(PLATEAU p, int diff,int colo, int coef, joueur player) {
    int res=0;
    coord pos=ajouterIA(&p, player, colo);
    if(pos.y < 0 && coef==diff) {
        colopleine[colo]=true;
        return -1000000;
    }

    if(gagnant(p,pos)) {
        if(player == J2) {
            return mpow(7,coef);
        }
        else {
            return -mpow(7, coef+1);
        }
    }
    coef--;
    if(coef > 0) {
        for(int i=0;i<7;i++) {   
            res+=MinMax(p,diff,i, coef, cjoueur(player));
        }
        return res;
    } 
    return 0;
}


/**
 * @brief La fonction appelée dans le main qui permet de choisir la colonne ou l'IA va jouer
 * 
 * @param[in] p Le plateau de jeu
 * @param[in] diff le niveau de difficulté des IA. 2 pour facile, 4 pour normal et 6 pour difficile
 * 
 * @return un entier corespondant a la colonne choisi
 */
int colochoiceIA(PLATEAU p, int diff) {
    int l[7];
    int t, cont=-1;
    int max=-1000000;
    for(int i=0;i<7;i++) {
        if(!colopleine[i]) {
            t=MinMax(p, diff, i, diff, J2);

            if(t >= max) {
                if(t == max) {
                    cont++;
                }
                else {
                    max=t;
                    cont=0;
                }
                l[cont]=i;
            }
            t=0;
        }
    }
    if(cont > -1) {
        if(cont == 0) {
            return l[0];
        }
        else {
            t=rand()%cont;
            return l[t];
        }
    }
    else {
        t=rand()%7;
        while(colopleine[t]) {
            t=rand()%7;
        }
        return t;
    }
}