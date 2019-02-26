
:- use_module(library(clpfd)).
/*
grille(G, I, J, Valeur) :-
    nth1(I, G, Ligne),
    nth1(J, Ligne, Valeur).

ligne(N,G,L) :- findall(X,grille(G,N,_,X),L).
col(N,G,C) :- findall(X,grille(G,_,N,X), C).
cols(G,Cs) :- col(_,G,Cs). % fais purement de la merde ... ça met dans un tableau 1D
*/
/* element_n(N,L,X) unifie le N e élément (N donné) de la liste unifiée avec L
(donnée) avec la variable X. */

element_n(N,L, X) :- nth1(N,L,X)
			     .
/* ligne_n(N,G,L) unifie la N e ligne (N donné) de la grille unifiée avec G (donnée)
avec la variable L. */
ligne_n(N,G,L) :- nth1(N,G,L).

/* colonne_n(N,G,C) unifie la N e colonne (N donné) de la grille G (donnée) avec
la variable C. 
    
    Soit une grille G de taille PxM
    M=lg d'une ligne de G, par exemple A la première ligne de G, toutes les lignes sont de même longeurs.
    
    Si N in 1..M alors 
    |   on récupère le Neme élément de la ligne courante
    Sinon
    |   l'élément recherché n'existe pas ==> retourner []
    FinSi
*/

colonne_n(N,[A | R] , Cn):-  length(A,M),N in 1..M,!, element_n(N,A,X), colonne_n(N,R,C), append([X], C, Cn).
colonne_n(_,_,[]).

/* colonnes(G,C) unifie C avec la liste des colonnes de la grille unifiée avec G
(donnée). Cela revient à "trouver toutes" les colonnes (pour tout N). */ 
colonnes(G,Cs) :- findall(C,colonne_n(_,G,C),Cs).


/*passe_bloc(L,NL,T) La variable L est unifiée avec une liste (donnée) 
représentant une ligne ou une colonne (une composante) d’une grille de picross. Si L
commence par un bloc (c’est-à-direpar une suite de 1), ce prédicat unifie NL avec les 
éléments qui suivent le bloc et T est unifiée avec la taille du bloc qui a été passé. 
Si la liste L ne commence pas un bloc (c’est-à-dire L commence par 0), NL est unifié
avec L et T est unifiée avec la valeur 0.*/

passe_bloc([0|Lr],[0|Lr],0).
passe_bloc([],[],0).
passe_bloc([1|Lr],NL,T) :- passe_bloc(Lr,NL,T1), T is T1+1. 

/* analyse_composante analyse_composante(C,B). Ce prédicat s’efface si la composante (une liste
représentant une ligne ou une colonne) unifiée avec C (donnée) est valide par rapport à la contrainte de bloc
unifiée avec B (donnée) qui est la liste des tailles de bloc que l’on doit retrouver dans la composante (l’ordre
est important).*/
analyse_composante([],[]).
analyse_composante([0|R],B) :- analyse_composante(R,B).
analyse_composante([1|R],[P|B]) :- passe_bloc([1|R],NL,T),T==P,analyse_composante(NL,B).

/* analyse_l_composantes(LC,LB). Ce prédicat s’efface si la liste de composantes
(une liste de listes) unifiée avec LC (donnée) est valide par rapport à la liste de contraintes de blocs (qui est
aussi une liste de listes) unifiée avec LB (donnée); chaque contrainte de bloc de LB s’appliquant à une des
composantes de LC dans le même ordre */

analyse_l_composantes([],[]).
analyse_l_composantes([PC|RC],[PB|RB]) :- analyse_composante(PC,PB),analyse_l_composantes(RC,RB).

/* genere_bloc(X,T,B). qui unifie B avec une liste de taille T ne contenant que des
valeurs X (donnée qui sera unifié avec 0 ou 1).*/

genere_bloc(_,0,[]).
genere_bloc(X,T,B) :- T1 is T-1,append([X],B1,B), genere_bloc(X,T1,B1).
%genere_bloc(X,T,B) :- X in 0..1,T1 is T-1,append([X],B1,B), genere_bloc(X,T1,B1).

/* genere_ligne(N,LB,L) qui permet de générer et d’unifier une ligne avec la variable
L dont la taille a été unifiée avec N (donnée). La ligne générée doit vérifier la contrainte de bloc unifiée avec
LB (donnée). Ce prédicat doit être capable de générer tous les lignes possibles qui vérifie la contrainte de bloc. */

genere_ligne(0,[],[]).% :- length(X,0).
genere_ligne(N,[[]],L) :- genere_bloc(0,N,L).
genere_ligne(N,LB,L) :- length(L,N),analyse_composante(L,LB).

/* genere_grille(N,BS,LS) qui permet de générer et d’unifier une liste de M lignes
de taille N (donnée) avec la variable LS de manière à ce que les lignes générées vérifient les contraintes de
bloc unifiées avec la liste de contraintes BS donnée (une par ligne et dans le même ordre) et où M est la taille
de la liste BS. Ce prédicat doit être capable de générer toutes les listes de lignes possibles.*/

genere_grille(_,[],[]).
genere_grille(N,[PBS|RBS],[PLS|RLS]) :- genere_ligne(N,PBS,PLS),genere_grille(N,RBS,RLS).



/** print **/
printRow([]) :- nl, true.
printRow([X | T]) :- var(X), write('¿'), write(' '), printRow(T).
printRow([0 | T]) :- write('◼'), write(' '), printRow(T).
printRow([1 | T]) :- write('◻'), write(' '), printRow(T).

printNonogram([]).
printNonogram([H | T]) :- printRow(H), printNonogram(T).



/*solve_picross(CL,CC,G) qui permet de générer et d’unifier avec la variable G
une grille de picross qui vérifie les contraintes en ligne de la liste CL (donnée) et les contraintes en colonne
de la liste CC (donnée).*/

solve(CL,CC) :- length(CC,N), genere_grille(N,CL,G),colonnes(G,Cols),analyse_l_composantes(Cols,CC),printNonogram(G).
t_solve(CL,CC) :- time(solve(CL,CC)).

nonogramSolve(CL,CC,_) :- time(solve(CL,CC)).
