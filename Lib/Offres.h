#ifndef __Offres__
#define __Offres__

//_____________________________________________________________________________________________________________________

/* La liste des Offres est ordonnée par ordre croissant des ID des annonceurs */

//_____________________________________________________________________________________________________________________

/* Empty_Offre : Initializes The Offer to false values to avoid the garbage values */

void Empty_Offre ( Offre *Smth );

/* De_normalize : changes spaces to _ to store the data in the file */

Offre De_Normalize_Off (Offre Offer , int command);

/* Print_Offre : prints the information on an Offre */

void Print_Offre ( Offre Two , int command_rec , int command_id , Ptr_Maillon_Annonceur Liste );

/* String_2_Offre : scans the information in a string " which is gonna be read from a file " and puts it in the Offre */

Offre String_2_Offre ( char *info );

/* Liberer_Liste_Offre : to free all the memory allocated for the lists at the end of the execution of the program */

void Liberer_Liste_Offres ( Ptr_Maillon_Offre *Head );

/* Add_Offre_Liste : Adds the Offre in its place following the order of the ID, and then the publication date */

void Add_Offre_Liste ( Ptr_Maillon_Offre *Head , Ptr_Maillon_Offre Offer1 );

/* print_Liste_Offres : prints the list of annonceurs One by one */

void print_Liste_Offres ( Ptr_Maillon_Offre Head , int command_info_rec , Ptr_Maillon_Annonceur Liste );

/* Read_Liste_Offre_file : Reads from the file the list of offres and returns the head */

Ptr_Maillon_Offre Read_Liste_Offre_file ( FILE *file_name );

/* Offre_2_string : fills the string with the information of the offer following the layout */

char *Offre_2_string ( Offre Offer1 );

/* Print_Offres_file : prints the list to the file */

void Print_Offres_file ( FILE *file_name , Ptr_Maillon_Offre Head );

/* Compare_Offer : compraes all the fielsds of the offer, returns 1 if they're identically the same, 0 if at least there's one field different */

int Compare_Offer ( Offre Offer1 , Offre Offer2 );

/* Find_offre : Looks for the Offer in the List : if it's in there it returns its pointer else it returns NULL */

Ptr_Maillon_Offre Find_offre ( Ptr_Maillon_Offre Head , Offre Offer1 );

/* New_Offre : Reads new offer from the user */

Offre New_Offre ( Ptr_Maillon_Annonceur Liste_Ann , Ptr_Maillon_Offre Liste_Off );

//_____________________________________________________________________________________________________________________

#endif