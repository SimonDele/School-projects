Mini - Projet de programmation logique GM5
--------------------------------------
pics/ Répertoire contenant des picross au bon format que l'on peut résoudre :
	- en utilisant le script run.sh :
		./run.sh picrossV<n>.pl pics/<picross>.pic
	où <n> correspond au numéro de version et picross le nom du puzzle
	- directement depuis prologue en consultant le fichier de la version puis le picross.

-------------------------------
Utilisation du  script trad.sh :

Le script permet de traduire des picross enregistré au format : "Format for version 1 of Kyle Keen's Python solver". 

Le script peut avoir plusieurs argument :
	-r 	résout le picross avec la version 3
	-r<n> 	résout le picross avec la version <n>
	-a	(Pour version 2 et 3) abort la résolution : Ne pas utiliser force brute (V2)/Ne pas label (V3)


Utilisation n°1 :

- Pour lancer la résolution d'un picross <p> au format "Kyle Keen's Python Solver V1" : (on peut en obtenir ici https://webpbn.com/export.cgi)
		./trad.sh -r "<p>"

Utilisation n°2 :

			/!\ Nécessite le navigateur sur terminal lynx ==> sudo apt-get install lynx
- Pour aller chercher un picross stocké dans la base de donnée du site https://webpbn.com/export.cgi , il sufffit de connaitre l'id du puzzle et de lancer la commande suivante :
		./trad.sh <id> [-r|-r -a] 

	=> Ne pas spécifier d'argument -r ou -r -a donnera juste la traduction à un format compréhensible par prolog (qu'on pourra copier-coller)
