#ifndef __Demandes__
#define __Demandes__

//_____________________________________________________________________________________________________________________

/* La liste des Demandes est ordonnée par ordre croissant des ID des annonceurs  */

//_____________________________________________________________________________________________________________________


/* De_normalize : changes spaces to _ to store the data in the file */

Demande De_Normalize_Dem ( Demande Demande1 , int command );

/* Print_Demande : prints all the informatio of the demande */

void Print_Demande ( Demande Something , int command_ID );

/* String_2_Demande : scans the information in a string " which is gonna be read from a file " and puts it in the demande */

Demande String_2_Demande ( char *info );

/* Find_Demande : to look for an demande in the list : if he's there of not : returns the pointer to the maillons if he's there or NULL if he's not */

Ptr_Maillon_Annonce Find_Demande ( Ptr_Maillon_Annonce Head , int ID );

/* Liberer_Liste_Annonce : to free all the memory allocated for the lists at the end of the execution of the program */

void Liberer_Liste_Annonce ( Ptr_Maillon_Annonce *Head );

/* Add_Demande_Liste : Adds he demande in its place following the ID */

void Add_Demande_Liste ( Ptr_Maillon_Annonce *Head , Ptr_Maillon_Annonce Something );

/* Print_Liste_Demande : prints the list 2 by 2 */

void Print_Liste_Demande ( Ptr_Maillon_Annonce Head );

/* Read_Liste_Demande_file :  */

Ptr_Maillon_Annonce Read_Liste_Demande_file ( FILE *file_name );

/* Demande_2_string : prints all the information of a Demande to a string to be printed to the file */

char *Demande_2_string ( Demande Demande1 );

/* print_Demande_file : prints the list to the file */

void print_Demande_file ( FILE *file_name , Ptr_Maillon_Annonce Head );

/* New_Demande : Reads new demande from the user */

Demande New_Demande ( Ptr_Maillon_Annonce Head );

//_____________________________________________________________________________________________________________________

#endif