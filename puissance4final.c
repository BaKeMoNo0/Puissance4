#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "modeTextuelle.h"
#include "modeGraphique.h"
#include "ia.h"
#include <unistd.h>



int main(void) {
    system("clear");
    joueur player;
    int colo, diff;
    PLATEAU p;
    coord nplacement;

    switch(menuGlobal()) {
        /**
         * @brief Debut du puissance 4 textuelle
         */
        case 1:
        Textuelle:
            bool win=false;
            settab();
            system("clear");
            player = J1;
            p = init();
            switch (menu()) {

                case 1:
                    p = init();
                    player = J1;
                    affiche(p);
                    for(int i=0;i<NB_COLONNE*NB_RANGE;i++) {
                    //Choix de la colonne
                        if(player==J1) {
                            printf("Joueur 1 choississez une colonne : ");
                        }
                        else {
                            printf("Joueur 2 choississez une colonne : ");
                        }
                        nplacement = ajouter(&p, player);

                        //affichage du plateau
                        system("clear");
                        affiche(p);

                        //verification d'une ligne
                        if(gagnant(p, nplacement)) {
                            if(player == J1) {
                                printf("Le vainqueur est le joueur 1 (\033[31mO\033[00m)\n");
                            }
                            else {
                                printf("Le vainqueur est le joueur 2 (\033[32mO\033[00m)\n");
                            }
                            i=NB_COLONNE*NB_RANGE;
                            win=true;
                        }

                    
                        //changement de joueur
                        player = cjoueur(player);
                    }
                    //affiche egalite si le plateau est rempli
                    if(!win) {
                        printf("EGALITE\n");
                    }
                    break;


                case 2:
                    switch(difficult(0)) {
                        case 1: printf("partie contre IA Facile\n\n"); diff=2; break;
                        case 2: printf("partie contre IA Normal\n\n"); diff=4; break;
                        case 3: printf("partie contre IA Difficile\n\n"); diff=6; break;
                        default: printf("Error\n"); return EXIT_FAILURE;
                    } 
                    affiche(p);
                    for(char i=0; i < NB_COLONNE * NB_RANGE; i++) {
                        if(player==J1) {
                            printf("Joueur 1 choississez une colonne : ");
                            nplacement = ajouter(&p,player);
                        }
                        else {
                            sleep(1);
                            colo=colochoiceIA(p,diff);
                            nplacement = ajouterIA(&p, J2, colo);
                        }
                        //affichage du plateau
                        system("clear");
                        affiche(p);

                        //verification d'une ligne
                        if(gagnant(p, nplacement)) {
                            if(player == J1) {
                                printf("Le vainqueur est le joueur 1 (\033[31mO\033[00m)\n");
                            }
                            else {
                                printf("Le vainqueur est l'ordinateur (\033[32mO\033[00m)\n");
                            }
                            i=NB_COLONNE*NB_RANGE;
                            win=true;
                        }
                        //changement de joueur
                        player = cjoueur(player);
                    }
                    //affiche egalite si le plateau est rempli
                    if(!win) {
                        printf("EGALITE\n");
                    }
                    break;


                case 3:
                    //Choix de la difficulté de l'IA
                    switch(difficult(0)) {
                        case 1: printf("partie contre IA Facile\n\n"); diff=2; break;
                        case 2: printf("partie contre IA Normal\n\n"); diff=4; break;
                        case 3: printf("partie contre IA Difficile\n\n"); diff=6; break;
                        default: printf("Error\n"); return EXIT_FAILURE;
                    } 
                    affiche(p);
                    for(char i=0; i < NB_COLONNE * NB_RANGE; i++) {
                        if(player==J2) {
                            printf("Choississez une colonne (\033[32mO\033[00m) : ");
                            nplacement = ajouter(&p,player);
                        }
                        else {
                            sleep(1);
                            colo=colochoiceIA(p,diff);
                            nplacement = ajouterIA(&p, J1, colo);
                        }
                        //affichage du plateau
                        system("clear");
                        affiche(p);

                        //verification d'une ligne
                        if(gagnant(p, nplacement)) {
                            if(player == J1) {
                                printf("Le vainqueur est l'IA (\033[31mO\033[00m)\n");
                            }
                            else {
                                printf("Vous avez gagner (\033[32mO\033[00m)\n");
                            }
                            i=NB_COLONNE*NB_RANGE;
                            win=true;
                        }
                        //changement de joueur
                        player = cjoueur(player);
                    }
                    //affiche egalite si le plateau est rempli
                    if(!win) {
                        printf("EGALITE\n");
                    }
                    break;

                case 4:
                    int diff2;
                    //Choix du niveau des IA
                    switch(difficult(1)) {
                        case 1: printf("IA Facile\n\n"); diff=2; break;
                        case 2: printf("Normal\n\n"); diff=4; break;
                        case 3: printf("Difficile\n\n"); diff=6; break;
                        default: printf("Error\n"); return EXIT_FAILURE;
                    }
                    switch(difficult(2)) {
                        case 1: printf("IA Facile\n\n"); diff2=2; break;
                        case 2: printf("Normal\n\n"); diff2=4; break;
                        case 3: printf("Difficile\n\n"); diff2=6; break;
                        default: printf("Error\n"); return EXIT_FAILURE;
                    } 
                    affiche(p);
                    for(char i=0; i < NB_COLONNE * NB_RANGE; i++) {
                        if(player==J1) {
                            colo=colochoiceIA(p,diff);
                            nplacement = ajouterIA(&p, J1, colo);
                        }
                        else {
                            colo=colochoiceIA(p,diff2);
                            nplacement = ajouterIA(&p, J2, colo);
                        }
                        //affichage du plateau
                        system("clear");
                        affiche(p);
                        sleep(1);

                        //verification d'une ligne
                        if(gagnant(p, nplacement)) {
                            if(player == J1) {
                                printf("Le vainqueur est l'IA 1 (\033[31mO\033[00m)\n");
                            }
                            else {
                                printf("Le vainqueur est l'IA 2 (\033[32mO\033[00m)\n");
                            }
                            i=NB_COLONNE*NB_RANGE;
                            win=true;
                        }
                        //changement de joueur
                        player = cjoueur(player);
                    }
                    //affiche egalite si le plateau est rempli
                    if(!win) {
                        printf("EGALITE\n");
                    }
                    break;
                    
                default:
                    printf("Vous avez choisi un mode inexistante.\n");
                    break;
            }
            char * cjouer=malloc(sizeof(char)*20);
            int jouer;
            printf("\tVoulez vous rejouez?\n1.Oui\n2.Non\n");
            scanf("%s", cjouer);
            jouer=atoi(cjouer);
            while(jouer > 2 || jouer < 1) {
                printf("Erreur de saisie, Veuillez saisir 1 ou 2 : ");
                scanf("%s", cjouer);
                jouer = atoi(cjouer);
            }
            free(cjouer);

            if(jouer==1) {
                goto Textuelle;
            }
            break;




        //Puissance 4 Graphique
        case 2:
            bool jeu = false, menu = true, mode = false, rejouer, hIa = false, play = false, ia = false, test = false, combat = false;
            int colo, px, py;
            coord tpos;
            SDL_Window *window = NULL;
            SDL_Renderer *renderer = NULL;
            SDL_Texture *texture = NULL;
            SDL_Event event;
            p = init();
            int coloPleine[7];
            player = J1;

            if(0 != SDL_Init(SDL_INIT_VIDEO)) {
                fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
                goto Quit;
            }

            //Creation de la fenetre et du renderer
            if (SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_SHOWN, &window, &renderer)) {
                fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
                goto Quit;
            }

            if(ajoutImage(renderer, "img/bouton.bmp", texture)) {
                fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                goto Quit;
            }

            //AFFICHER MENU
            while(menu) {
                while (SDL_PollEvent (&event)) {
                    switch(event.type) {
                        case SDL_QUIT:
                            goto Quit;
                        case SDL_MOUSEMOTION :
                            px = event.motion.x;
                            py = event.motion.y;
                            break;
                        case  SDL_MOUSEBUTTONDOWN:   
                            if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
                                if (px > 782  && px < 1136 && py > 478 && py < 562){
                                    mode = true; 
                                    menu = false;
                                }
                                if (px > 782  && px < 1136 && py > 622 && py < 705){ 
                                    goto Quit;
                                }
                            }
                    }
                }
            }

        Rejouer:
            settab();
            rejouer = true;
            for(int q = 0; q < NB_COLONNE; q++) {
                coloPleine[q] = 0;
            }

            if(mode && ajoutImage(renderer, "img/mode.bmp", texture)) {
                fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                goto Quit;
            }


            //Choix du mode de jeu
            while(mode) {
                while(SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_QUIT:
                            goto Quit;
                        case SDL_MOUSEMOTION :
                            px = event.motion.x;
                            py = event.motion.y;
                            break;
                        case SDL_MOUSEBUTTONDOWN :
                            if (px > 744  && px < 1178 && py > 367 && py < 467){
                                jeu = true;
                                mode = false;        
                            }
                            if (px > 744  && px < 1178 && py > 498 && py < 596){
                                hIa = true;
                                play =  true;
                                mode = false;
                            }
                            if (px > 744  && px < 1178 && py > 629 && py < 728){
                                hIa = true;
                                ia = true;
                                play = true;
                                mode = false;        
                            }
                            if (px > 744  && px < 1178 && py > 747 && py < 858){
                                hIa = true;
                                test = true;
                                combat = true;
                                mode = false;  
                            }
                    }
                }
            }

            //mode de jeu avec l'Ia
            if(hIa) {
                if(ajoutImage(renderer, "img/niveau.bmp", texture)) {
                    fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                    goto Quit;
                }
            Ia2:
                while(hIa) {
                    while(SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_QUIT:
                                goto Quit;
                            case SDL_MOUSEMOTION :
                                px = event.motion.x;
                                py = event.motion.y;
                                break;
                            case SDL_MOUSEBUTTONDOWN :
                                if (px > 744  && px < 1178 && py > 464 && py < 561){
                                    diff = 2;
                                    hIa = false;        
                                }
                                if (px > 744  && px < 1178 && py > 594 && py < 691){
                                    diff = 4;
                                    hIa = false;
                                }
                                if (px > 744  && px < 1178 && py > 723 && py < 820){
                                    diff = 6;
                                    hIa = false;
                                }
                        }
                    }
                }
                if(test) {
                    if(ajoutImage(renderer, "img/niveau2.bmp", texture)) {
                        fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                        goto Quit;
                    }
                    hIa = true;
                    test = false;
                    goto Ia2;
                }

                if(ajoutImage(renderer, "img/menuGrille.bmp", texture)) {
                    fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                    goto Quit;
                }

                //ia vs ia
                while (combat) {
                    if (player == J1) {
                        colo=colochoiceIA(p,diff);
                        tpos = ajouterIA(&p, J1, colo);
                    } else if(player == J2) {
                        colo=colochoiceIA(p,diff);
                        tpos = ajouterIA(&p, J2, colo);
                    }
                    if(affichePlateau(renderer, p)) {
                        fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                        goto Quit;
                    }
                    SDL_Delay(1000);
                    if(winLine(renderer, p, tpos, player, &combat)) {
                        fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                        goto Quit;
                    } 
                    if (gagnantG(p, tpos) == 0) {
                        player = cjoueur(player);
                    } 
                    if(platPlein(p)) {
                        combat = false;
                    }
                }
                
                //human vs ia et ia vs human
                while (play) {
                    while (SDL_PollEvent (&event)) {
                        if (ia && player == J1) {
                            colo=colochoiceIA(p,diff);
                            tpos = ajouterIA(&p, J1, colo);
                            if(affichePlateau(renderer, p)) {
                                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                                goto Quit;
                            }
                            if(winLine(renderer, p, tpos, player, &play)) {
                                fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                                goto Quit;
                            } 
                            if (gagnantG(p, tpos) == 0) {
                                player = cjoueur(player);
                            }
                            if(platPlein(p)) {
                                play = false;
                            }
                        }
                        else if(ia == false && player == J2) {
                            colo=colochoiceIA(p,diff);
                            tpos = ajouterIA(&p, J2, colo);
                            if(affichePlateau(renderer, p)) {
                                fprintf(stderr, "Erreur affichePlateau : %s", SDL_GetError());
                                goto Quit;
                            }
                            if(winLine(renderer, p, tpos, player, &play)) {
                                fprintf(stderr, "Erreur wineLine : %s", SDL_GetError());
                                goto Quit;
                            } 
                            if (gagnantG(p, tpos) == 0) {
                                player = cjoueur(player);
                            }
                            if(platPlein(p)) {
                                play = false;
                            }
                        }
                        switch (event.type) {
                            case SDL_QUIT :
                                goto Quit;
                            case SDL_MOUSEMOTION :
                                px = event.motion.x;
                                py = event.motion.y;
                                break;
                            case  SDL_MOUSEBUTTONDOWN:   
                                if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
                                    if(deplacement(&p, renderer, px, py, coloPleine, &player, &tpos, &play)) {
                                        fprintf(stderr, "Erreur Deplacement: %s", SDL_GetError());
                                        goto Quit;
                                    }
                                }
                        }
                    }
                }

            }


            //human vs human
            if (jeu) {
                if(ajoutImage(renderer, "img/menuGrille.bmp", texture)) {
                    fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                    goto Quit;
                }
            }
            
            //boucle jusqu'a ce que toute les cases soient rempli ou qu'il y ai une ligne gagnante
            while (jeu) {
                while (SDL_PollEvent (&event)) {
                    switch (event.type) {
                        case SDL_QUIT :
                            goto Quit;
                        case SDL_MOUSEMOTION :
                            px = event.motion.x;
                            py = event.motion.y;
                            break;
                        case  SDL_MOUSEBUTTONDOWN:   
                            if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
                                if(deplacement(&p, renderer, px, py, coloPleine, &player, &tpos, &jeu)) {
                                    fprintf(stderr, "Erreur Deplacement: %s", SDL_GetError());
                                    goto Quit;
                                } 
                            }
                    }
                }
            }

            //affichage fin de partie
            if(platPlein(p)) {
                if(ajoutImage(renderer, "img/egalite.bmp", texture)) {
                    fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                    goto Quit;
                }
                SDL_Delay(2000);
            }

            if (player == J1 && gagnantG(p, tpos) != 0) {
                if(ajoutImage(renderer, "img/ggr.bmp", texture)) {
                    fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                    goto Quit;
                }
                SDL_Delay(2000);
            } else if (player == J2 && gagnantG(p, tpos) != 0) {
                if(ajoutImage(renderer, "img/ggj.bmp", texture)) {
                    fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                    goto Quit;
                }
                SDL_Delay(2000);
            }


            //rejouer
            if(ajoutImage(renderer, "img/rejouer.bmp", texture)) {
                fprintf(stderr, "Erreur ajoutImage: %s", SDL_GetError());
                goto Quit;
            }

            while (rejouer) {
                while(SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_QUIT:
                            goto Quit;
                        case SDL_MOUSEMOTION :
                            px = event.motion.x;
                            py = event.motion.y;
                            break;
                        case SDL_MOUSEBUTTONDOWN :
                            if (px > 745  && px < 1178 && py > 481 && py < 579){
                                mode = true;
                                ia = false;
                                player = J1;
                                p = init();
                                goto Rejouer;       
                            }
                            if (px > 745  && px < 1178 && py > 612 && py < 709){
                                goto Quit;        
                            }
                    }
                }
            }

        //Quitter le jeu
        Quit:
            if (NULL != texture) {
                SDL_DestroyTexture(texture);
            }
            if(NULL != renderer) {
                SDL_DestroyRenderer(renderer);
            }
            if(NULL != window) {
                SDL_DestroyWindow(window);
            }
            SDL_Quit();
            break;
    }
    return EXIT_SUCCESS;
}
