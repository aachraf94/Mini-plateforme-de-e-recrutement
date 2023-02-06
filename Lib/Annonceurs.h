#ifndef __Annonceurs__
#define __Annonceurs__


/* La liste des Annonceurs est ordonnée par ordre croissant des ID des annonceurs  */

//_____________________________________________________________________________________________________________________

/* De_normalize : changes spaces to _ to store the data in the file */

Annonceur De_Normalize_Ann ( Annonceur Personne , int command );

/* Print_Annonceur : prints the information on an Annonceur */

void Print_Annonceur ( Annonceur Personne , int command_id , int command_nbr_annonces);

/* String_2_Annonceur : scans the information in a string " which is gonna be read from a file " and puts it in the annonceur */

Annonceur String_2_Annonceur ( char *info );

/* Find_Annonceur : to look for an annonceur in the list : if he's there of not : returns the pointer to the maillons if he's there or NULL if he's not */

Ptr_Maillon_Annonceur Find_Annonceur ( Ptr_Maillon_Annonceur Head , int ID );

/* Liberer_Liste_Annonceur : to free all the memory allocated for the lists at the end of the execution of the program */

void Liberer_Liste_Annonceur ( Ptr_Maillon_Annonceur *Head );

/* Add_Annonceur_Liste : Adds the Annonceur to the list following the order of the ID */

void Add_Annonceur_Liste ( Ptr_Maillon_Annonceur *Head , Ptr_Maillon_Annonceur Guy );

/* Print_Liste_Annonceurs : Prints the list 4 by 4 */

void print_Liste_Annonceurs ( Ptr_Maillon_Annonceur Head );

/* Read_Liste_Annonceur_file : Reads from the file the list of Annonceurs and returns the head of the list */

Ptr_Maillon_Annonceur Read_Liste_Annonceur_file ( FILE *file_name );

/* Annonceur_2_String : prints all the information of an Annonceur to a string to be printed to the file */

char *Annonceur_2_String ( Annonceur Guy );

/* Print_Annonceurs_file : prints the list to the file */

void Print_Annonceurs_file ( FILE *file_name , Ptr_Maillon_Annonceur Head );

/* New_Annonceur : gets new annonceur */

Annonceur New_Annonceur ( Ptr_Maillon_Annonceur Head );     

//_____________________________________________________________________________________________________________________

#endif