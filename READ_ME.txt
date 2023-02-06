**********************************************************/* TP 1 ALSDD *\***********************************************************

*************************************************************************************************************************************

Ce TP a été réalisé par : 

	- Merhab Abderraouf	A-02
	- Abdelkebir Achraf		A-02

Sous la supervisation de Madame Temglit Nacéra

*************************************************************************************************************************************

Pour eviter des problemes d'Affichage, veuillez ne pas modifier la largeur de la fenetre.

*************************************************************************************************************************************

Ce dossier Contient : 
	-	Le programme Principal	: e_recrutement.exe
	-	Le code source		: e_recrutement.c

	-	Dossier Lib : contient Les bibliothéques utlisés :
		-	Annonceurs : Contient toutes les fonctions sur les Annonceurs
		-	Basic_Functions : Contient les fonctions de base et les fonctions sur les dates, langues, competences et diplomes
		-	Demandes : Contient toutes les fonctions sur les Demandes
		-	Display : Contient quelque fonctions sur l'affichage tels que les couleurs et les fonctions sur le curseur
		-	EMPLOI_LLC_BIBLIO : Contient les structures de donnees et leur machine abstraite
		-	Menus : Contient lles menus principaux et les secondaires, et l'affichage principale
		-	Offres : Contient toutes les fonctions sur les Offres
		-	Standard_Library : 

	-	Dossier Data : fichiers textes :
		-	Layout.txt : Organization des fichiers texte dont le programme va lire
		-	Annonceurs_Active.txt 	: Liste des Annonceurs Actives
		-	Annonceurs_Archive.txt	: Liste des Annonceurs Archives
		-	Offres_Active.txt		: Liste des Offres Actives
		-	Offres_Supprimes.txt	: Liste des Offres Supprimés
		-	Demandes_Active.txt	: Liste des Demandes Active
		-	Demandes_Archive.txt	: Liste des Demandes Archive

	-	README.txt : ce fichier

*************************************************************************************************************************************

pour compiler à nouveau le programme sur Windows et si vous disposez du compilateur gcc : 
1- Aller avec l'interpreteur de commande vers le dossier courant
2- Executer la commande : cd Resources\ & windres Res_Icon.rc -o Icon.o & cd .. & gcc *.c Lib\*.c Resources\*.o -o E_Recrutement

*************************************************************************************************************************************

Explication du menu :
1- Annonceur : toutes les fonctionnalites d'un annonceur
2- demandeur : toutes les fonctionnalites d'un demandeur
3- developpeur : les questions du tp only

*************************************************************************************************************************************

Pour des raisons "pedagogiques" : la date qui sera consideree pour dire si une offre est valide ou pas doit etre entree manuellement
	On aurait pu la lire du systeme mais l'essai donc ne sera pas tres "efficace"

*************************************************************************************************************************************
contactez nous : 
	-	Merhab Abderraouf 	: la_merhab@esi.dz
	-	AbdelkebirAchraf	: la_abdelkebir@esi.dz

*************************************************************************************************************************************