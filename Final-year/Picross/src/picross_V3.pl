
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
grille([_|ILr],IC,[Ligne|Gr]) :-  creer_ligne(IC,Ligne), grille(ILr,IC,Gr).

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

/* genere_ligne(N,LB,L) qui permet de générer et d’unifier une ligne avec la variable
L dont la taille a été unifiée avec N (donnée). La ligne générée doit vérifier la contrainte de bloc unifiée avec
LB (donnée). Ce prédicat doit être capable de générer tous les lignes possibles qui vérifie la contrainte de bloc. */

genere_ligne([],[]).
genere_ligne([[]],[]).
genere_ligne(LB,L) :- L ins 0..1, analyse_composante(L,LB).
%--------------------------------------------------------------------------------------------------------------------------------------------------------
/* eval 0 donne un score S à la contrainte en "composante" CT pour la composante T */
eval0(T,[],N) :- length(T,N),!.
eval0(_,CT,S) :- /*length(T,N),*/ length(CT,M), M1 is M-2, sum_list([M1|CT], S).

/* On donne un score pour les Lignes/Colonnes */
eval0_composantes(Ts,CT,TScore) :- 
    maplist(eval0,Ts,CT,TScore),!.

/* On donne un score pour chaque Ligne et chaque colonne de la grille */
eval0_grille(G,CL,CC,LScore,CScore) :- 
    eval0_composantes(G,CL,LScore), colonnes(G,Cols), eval0_composantes(Cols,CC,CScore).

/* supprime le nieme element d'une liste*/
suppr_nth_element(As,N1,Bs) :-
    same_length(As,[_|Bs]),
    append(Prefix,[_|Suffix],As),
    length([_|Prefix],N1),
    append(Prefix,Suffix,Bs).

/* Génère une liste enumérée par pas de 1 : Range=[1,2,3,..., End] */
range(End,Range) :- 
    E in 1..End,
    findall(E, indomain(E), Range).

/* Trier les composantes (index) selon leur score */
trierScore_composantes([],[],[]).
trierScore_composantes(TScore, IndexList, [IndexScoreMax|IndexScoreMaxR]) :- 
    max_list(TScore,ScoreMax), 
    nth1(Index,TScore,ScoreMax),
    nth1(Index,IndexList,IndexScoreMax),
    suppr_nth_element(TScore,Index,TRScore),
    suppr_nth_element(IndexList,Index,IndexListR),
    trierScore_composantes(TRScore,IndexListR,IndexScoreMaxR),!.

/* On essaye d'unifier des élèments de la grille, en tenant compte de l'heuristique*/
assign0_grille(_,_,_,[],[]).
    /* Cas où la grille n'est pas carré et qu'il ne reste à parcourir que des lignes */
assign0_grille(G,CLS,CCS,[ISL1|IndexSortedLgn],[]) :- 
   ligne_n(ISL1,G,L),% colonne_n(ISC1,G,C),
    element_n(ISL1,CLS,CL1),% element_n(ISC1,CCS,CC1),
    generer_automate(CL1,L), %genere_ligne(CL1,L),
    assign0_grille(G,CLS,CCS,IndexSortedLgn,[]),!.
    
    /* Cas où la grille n'est pas carré et qu'il ne reste à parcourir que des colonnes */
assign0_grille(G,CLS,CCS,[],[ISC1|IndexSortedCols]) :- 
    colonne_n(ISC1,G,C),
    element_n(ISC1,CCS,CC1),
    generer_automate(CC1,C),%genere_ligne(CC1,C),
    assign0_grille(G,CLS,CCS,[],IndexSortedCols),!.

    /* Cas où il reste à parcourir des lignes et des colonnes */
assign0_grille(G,CLS,CCS,[ISL1|IndexSortedLgn],[ISC1|IndexSortedCols]) :-
    ligne_n(ISL1,G,L), colonne_n(ISC1,G,C),
    element_n(ISL1,CLS,CL1), element_n(ISC1,CCS,CC1),
    %genere_ligne(CL1,L), genere_ligne(CC1,C),
    generer_automate(CL1,L), generer_automate(CC1,C),
    assign0_grille(G,CLS,CCS,IndexSortedLgn,IndexSortedCols).

/* Met en oeuvre l'heuristique : On évalue un score pour chaque ligne/Colonne, on trie et on affecte */ 
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
    print_message_lines(user_output, '------ H:', ['Start assign grid']),
    assign0_grille(G,CLS,CCS,IndexSortedLgn,IndexSortedCols),
    print_message_lines(user_output, '%%%%%% H:', ['End assign grid']).%,!.



/* genere_grille(N,BS,LS) qui permet de générer et d’unifier une liste de M lignes
de taille N (donnée) avec la variable LS de manière à ce que les lignes générées vérifient les contraintes de
bloc unifiées avec la liste de contraintes BS donnée (une par ligne et dans le même ordre) et où M est la taille
de la liste BS. Ce prédicat doit être capable de générer toutes les listes de lignes possibles.*/

genere_grille([],[]).
genere_grille([PBS|RBS],[PLS|RLS]) :- 
    genere_ligne(PBS,PLS),
    genere_grille(RBS,RLS).


solve(CL,CC):- 
    grille(CL,CC,G),
    heuristique_grille(G,CL,CC),% solve_part_H(G,CL,CC),
    print_message_lines(user_output, '------ S:', ['Start Labelling']),
    term_variables(G, Vars), label(Vars),
    print_message_lines(user_output, '%%%%%% S:', ['End Labelling']),
    printNonogram(G),!.

t_solve(CL,CC) :- time(solve(CL,CC)).

nonogramSolve(CL,CC) :- t_solve(CL,CC).

abort_solve(CL,CC):- 
    grille(CL,CC,G),
    heuristique_grille(G,CL,CC),
    printNonogram(G).

t_abort_solve(CL,CC) :- time(abort_solve(CL,CC)).

/** print **/
printRow([]) :- nl, true.
printRow([X | T]) :- var(X), write('¿'), write(' '), printRow(T).
printRow([0 | T]) :- write('◼'), write(' '), printRow(T).
printRow([1 | T]) :- write('◻'), write(' '), printRow(T).

printNonogram([]).
printNonogram([H | T]) :- printRow(H), printNonogram(T).


/* generer_automate(Ks, Row) : Génere un automate X, tel que X tel que |X|=TReg(KS)
avec TReg la transformation de la contrainte en language régulier. On impose que Row soit reconnu par l'automate
*/
    generer_automate(Ks, Row) :-
        sum(Ks, #=, Ones),
        sum(Row, #=, Ones),
        generer_arcs_contraintes(Ks,start,Final,Arcs),
        automaton(Row, [source(start), sink(Final)], Arcs).
/* generer_arcs_contraintes([DerniereContrainte],Precedent,Final, Arcs) : gère le cas du dernier c_i 
==> pas de 0+ mais 0*
*/
    generer_arcs_contraintes([DerniereContrainte],Precedent,Final, Arcs) :-
        generer_arcs_derniere_contrainte(DerniereContrainte, Precedent, Final, Arcs1 ),
        append([arc(Precedent,0,Precedent)],Arcs1,Arcs),
        !.
/* generer_arcs_contraintes([DerniereContrainte],Precedent,Final, Arcs) : génère les arcs de l'automate 
pour tous les c_i. A chaque c_i le premier état peut boucler sur 0.
*/  
    generer_arcs_contraintes([Contrainte1|ContraintesR], Precedent, Final, Arcs) :-
        generer_arcs_contrainte(Contrainte1,Precedent, EtatFinalContrainte1, ArcsContrainte1),
        generer_arcs_contraintes(ContraintesR, EtatFinalContrainte1, Final, ArcsR),
        append([arc(Precedent,0,Precedent)|ArcsContrainte1], ArcsR, Arcs).


/* generer_arcs_contrainte(0,Etat,EtatFinalContrainte,ArcsContrainte) : génère l'arc d'une composante ci de contrainte, 
on stocke ci* qui est une version modifié de ci, ci* agit comme un compteur décrémental ici ci*=0 donc 
on vient de finaliser de générer les arcs qui correspondent à un ci il faut donc forcer un 0 après la contrainte*/
generer_arcs_contrainte(0,Etat,EtatFinalContrainte,ArcsContrainte) :- % Fin de la contrainte ==> 0 après.
    gensym(Etat,EtatFinalContrainte),
    ArcsContrainte = [arc(Etat,0,EtatFinalContrainte)],!.

/* generer_arcs_contrainte(0,Etat,EtatFinalContrainte,ArcsContrainte) : génère l'arc d'une composante ci de contrainte, 
on stocke ci* qui est une version modifié de ci, ci* agit comme un compteur décrémental ici ci*!=0 donc on ajoute un arc 
avec la valeur 1 et on appelle recursivement la fonction avec ci*-1 */ 
generer_arcs_contrainte(Contrainte,Etat,EtatFinalContrainte,ArcsContrainte) :-
    gensym(Etat,EtatSuivant),
    ContrainteMoins1 #= Contrainte-1,
    generer_arcs_contrainte(ContrainteMoins1,EtatSuivant,EtatFinalContrainte,SuiteArcsContrainte),
    append([arc(Etat,1,EtatSuivant)],SuiteArcsContrainte,ArcsContrainte).

/*generer_arcs_derniere_contrainte(0,Etat,Etat,[arc(Etat,0,Etat)]).
pour le dernier ci d'une contrainte, il ne faut pas un 0+ mais un 0*.
L'état final de l'automate et l'état courant.
*/
generer_arcs_derniere_contrainte(0,Etat,Etat,[arc(Etat,0,Etat)]).

/*generer_arcs_derniere_contrainte(Contrainte,Etat,Etat,[arc(Etat,0,Etat)]).
idem que generer_arc_contrainte mais sert traiter le cas particulier du dernier état
*/
generer_arcs_derniere_contrainte(Contrainte,Etat,EtatFinalContrainte,ArcsContrainte) :-
    gensym(Etat,EtatSuivant),
    ContrainteMoins1 #= Contrainte-1,
    generer_arcs_derniere_contrainte(ContrainteMoins1,EtatSuivant,EtatFinalContrainte,SuiteArcsContrainte),
    append([arc(Etat,1,EtatSuivant)],SuiteArcsContrainte,ArcsContrainte).
