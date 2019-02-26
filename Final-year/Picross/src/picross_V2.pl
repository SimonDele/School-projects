
:- use_module(library(clpfd)).

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

%--------------------------------------------------------------------------------------------------------------------------------------------------------

/* creer_Ligne(IndicesColonnes,Ligne). On donne autant de variable au sein d'une ligne qu'il n'y a de colonnes */
creer_ligne([],[]).
creer_ligne([_| ICr],[_| Lr]) :- creer_ligne(ICr,Lr).

/* creer_grille(IndicesLignes,IndicesColonnes,Grille). Crée une grille de variable. On crée des lignes autant que l'on a d'indices sur les lignes */
grille([],_,[]).
grille([_|ILr],IC,[Ligne|Gr]) :- creer_ligne(IC,Ligne), grille(ILr,IC,Gr).

%--------------------------------------------------------------------------------------------------------------------------------------------------------

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

%genere_ligne(0,[],[]).% :- length(X,0).
%genere_ligne(N,[[]],L) :- genere_bloc(0,N,L).
%genere_ligne(N,LB,L) :- length(L,N),analyse_composante(L,LB).
genere_ligne([],[]).
genere_ligne([[]],[]).
genere_ligne(LB,L) :- analyse_composante(L,LB).
%--------------------------------------------------------------------------------------------------------------------------------------------------------
/* eval 0 donne un score S à la contrainte en "composante" CT pour la composante T */
eval0(T,[],N) :- length(T,N),!.
eval0(_,CT,S) :- /*length(T,N),*/ length(CT,M), M1 is M-2, sum_list([M1|CT], S).

eval0_composantes(Ts,CT,TScore) :- 
    maplist(eval0,Ts,CT,TScore),!.

eval0_grille(G,CL,CC,LScore,CScore) :- 
    eval0_composantes(G,CL,LScore), colonnes(G,Cols), eval0_composantes(Cols,CC,CScore).

/* supprime le nieme element d'une liste*/
suppr_nth_element(As,N1,Bs) :-
    same_length(As,[_|Bs]),
    append(Prefix,[_|Suffix],As),
    length([_|Prefix],N1),
    append(Prefix,Suffix,Bs).

range(End,Range) :- 
    E in 1..End,
    findall(E, indomain(E), Range).

/* Trier les composantes (index) selon leur score */
trierScore_composantes([],[],[]).
trierScore_composantes(TScore, IndexList, [IndexScoreMax|IndexScoreMaxR]) :- 
   % print_message(user_output, "--------------------"),
    max_list(TScore,ScoreMax), 
    nth1(Index,TScore,ScoreMax),
    nth1(Index,IndexList,IndexScoreMax),
    %print(IndexScoreMax),
    suppr_nth_element(TScore,Index,TRScore),
    suppr_nth_element(IndexList,Index,IndexListR),
    trierScore_composantes(TRScore,IndexListR,IndexScoreMaxR),!.



assign0_grille(_,_,_,[],[]).
assign0_grille(G,CLS,CCS,[ISL1|IndexSortedLgn],[]) :- 
   % length([ISL1|IndexSortedLgn],LRemains),atom_string(LRemains,LStr), print_message_lines(user_output, '=======> assign : remain lines ', [LStr] ),
   %print_message(user_output,"No more Cols"),

    ligne_n(ISL1,G,L),% colonne_n(ISC1,G,C),
    element_n(ISL1,CLS,CL1),% element_n(ISC1,CCS,CC1),
    genere_ligne(CL1,L), %genere_ligne(CC1,C),
    assign0_grille(G,CLS,CCS,IndexSortedLgn,[]),!.

assign0_grille(G,CLS,CCS,[],[ISC1|IndexSortedCols]) :- 

  %  length([ISC1|IndexSortedCols],CRemains),atom_string(CRemains,CStr), print_message_lines(user_output, '=======> assign : remain cols ',[CStr] ),
    %print_message(user_output,"No more Lines"),
    colonne_n(ISC1,G,C),
    element_n(ISC1,CCS,CC1),
    genere_ligne(CC1,C),
    assign0_grille(G,CLS,CCS,[],IndexSortedCols),!.

assign0_grille(G,CLS,CCS,[ISL1|IndexSortedLgn],[ISC1|IndexSortedCols]) :-

    %length([ISL1|IndexSortedLgn],LRemains),atom_string(LRemains,LStr), print_message_lines(user_output, '=======> assign : remain lines ', [LStr] ),
    %length([ISC1|IndexSortedCols],CRemains),atom_string(CRemains,CStr), print_message_lines(user_output, '=======> assign : remain cols ', [CStr] ),
   % !,
    ligne_n(ISL1,G,L), colonne_n(ISC1,G,C),
    element_n(ISL1,CLS,CL1), element_n(ISC1,CCS,CC1),
    genere_ligne(CL1,L), genere_ligne(CC1,C),
    assign0_grille(G,CLS,CCS,IndexSortedLgn,IndexSortedCols).


heuristique_grille(G,CLS,CCS) :-
    print_message_lines(user_output, '------ H:', ['Start evalutate']),
    eval0_grille(G,CLS,CCS,LScore,CScore), 
    print_message_lines(user_output, '%%%%%% H:', ['End evalutate']),
    length(CLS,N), range(N,InitILignes),
    length(CCS,P), range(P,InitICols), 
    print_message_lines(user_output, '###### H:', ['Sort Lines']),
    trierScore_composantes(LScore,InitILignes,IndexSortedLgn),
    print_message_lines(user_output, '###### H:', ['Sort Cols']),
    trierScore_composantes(CScore,InitICols,IndexSortedCols),
   % print(LScore),print(" "),print(IndexSortedLgn),nl,nl,
   % print(CScore),print(" "),print(IndexSortedCols),nl,
    %nl,print(CScore),
    print_message_lines(user_output, '------ H:', ['Start assign grid']),
    assign0_grille(G,CLS,CCS,IndexSortedLgn,IndexSortedCols),
    print_message_lines(user_output, '%%%%%% H:', ['End assign grid']),!.



/* genere_grille(N,BS,LS) qui permet de générer et d’unifier une liste de M lignes
de taille N (donnée) avec la variable LS de manière à ce que les lignes générées vérifient les contraintes de
bloc unifiées avec la liste de contraintes BS donnée (une par ligne et dans le même ordre) et où M est la taille
de la liste BS. Ce prédicat doit être capable de générer toutes les listes de lignes possibles.*/

genere_grille([],[]).
genere_grille([PBS|RBS],[PLS|RLS]) :- 
    genere_ligne(PBS,PLS),
    genere_grille(RBS,RLS).

/*solve_part_H(G,CL,CC) :-
    heuristique_grille(G,CL,CC),
    printNonogram(G), nl,
    print(-----------------------------), nl,nl,!.
*/
solve(CL,CC):- 
    grille(CL,CC,G),
    heuristique_grille(G,CL,CC),
    printNonogram(G),!.

t_solve(CL,CC) :- time(solve(CL,CC)).

nonogramSolve(CL,CC,_) :- t_solve(CL,CC).


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

/*solve_picross(CL,CC,G) :- length(CC,N), genere_grille(N,CL,G),colonnes(G,Cols),analyse_l_composantes(Cols,CC),printNonogram(G).

nonogramSolve(CL,CC,G) :- time(solve_picross(CL,CC,G)).
*/

