all : fp4

# But principal gcc -g -o fp4 puissance4final.o modeTextuelle.o modeGraphique.o
fp4 : puissance4final.o modeTextuelle.o modeGraphique.o ia.o
	gcc -g -o fp4 puissance4final.o modeTextuelle.o modeGraphique.o ia.o -l SDL2main -l SDL2 -g
	


puissance4final.o : puissance4final.c modeTextuelle.h modeGraphique.h ia.h
	gcc -g -c puissance4final.c


modeTextuelle.o : modeTextuelle.c modeTextuelle.h
	gcc -g -c modeTextuelle.c

modeGraphique.o :modeGraphique.c modeTextuelle.h
	gcc -g -c modeGraphique.c

ia.o : ia.c ia.h
	gcc -g -c ia.c

	
# Le menage
clean :
	rm -f *.o *~ 