#ifndef __Standard_Functions__
#define __Standard_Functions__

//_____________________________________________________________________________________________________________________

/* Offres_of_an_annonceur : returns a list with the offres of the annonceur with ID in input */

Ptr_Maillon_Offre Offres_of_an_annonceur ( Ptr_Maillon_Offre Liste , int ID );

/* Supprimer_Demande : Moves Demande with ID given from active list to archive one */

void Supprimer_Demande ( Ptr_Maillon_Annonce *Liste_act , Ptr_Maillon_Annonce *List_arch , int ID );

/* Supprimer_Offre : Moves Offre with its information given from active list to archive one */

void Supprimer_Offre ( Ptr_Maillon_Offre* tete_Offre_act , Ptr_Maillon_Offre* tete_offre_arch , Offre x );

/* Supprimer_Annonceur : Moves Annonceur with ID given from active list to archive one */

void Supprimer_Annonceur ( Ptr_Maillon_Annonceur *tete_act , Ptr_Maillon_Annonceur *tete_arch , int ID );

/* Longueur_Liste_Offre : returns the length of the list */

int Longueur_Liste_Offre ( Ptr_Maillon_Offre tete );

/* Supprimer_Annonceur_0_Ann : deletes all the Annonceurs with the 0 Annonces */

void Supprimer_Annonceur_0_Ann (Ptr_Maillon_Annonceur *Liste_act , Ptr_Maillon_Annonceur *Liste_arch );

/* Demandes_by_competences : Adds the demandes having at least "num" competences */

Ptr_Maillon_Annonce Demandes_by_competences (Ptr_Maillon_Annonce Head , int num );

/* Demandes_by_langues : Adds the demande that has the language given : num contains only one language */

Ptr_Maillon_Annonce Demandes_by_langues (Ptr_Maillon_Annonce Head , int num );

/* Demandes_by_diplome : Adds the demande having the diplome required orhigher one */

Ptr_Maillon_Annonce Demandes_by_diplome ( Ptr_Maillon_Annonce Liste , int Diplome );

/* Demandes_by_langues_multiple : Adds the demande having at least one of the languages given */

Ptr_Maillon_Annonce Demandes_by_langues_multiple ( Ptr_Maillon_Annonce Liste , int Langue );

/* Add_Demande_List_by_exp : Adds demande by years of experience in demande  */

void Add_Demande_List_by_exp ( Ptr_Maillon_Annonce *Head , Ptr_Maillon_Annonce Node );

/* Demandes_by_competences_multiple : Adds the demandes having at least two of the competences in the string */

Ptr_Maillon_Annonce Demandes_by_competences_multiple ( Ptr_Maillon_Annonce Liste , char *Str );

/* Add_offre_by_compet : Adds demande by number of competences in demande */

void Add_offre_by_compet ( Ptr_Maillon_Offre *Liste , Ptr_Maillon_Offre Node );

/* Delete_Offres_ID : deletes all the offres of an announcer */

void Delete_Offres_ID ( Ptr_Maillon_Offre *List_act , Ptr_Maillon_Offre *List_arch , int ID );

/* Longueur_Liste_Annonceurs : returns the length of the list */

int Longueur_Liste_Annonceurs ( Ptr_Maillon_Annonceur tete );

/* Longueur_Liste_Demandes : returns the length of the list */

int Longueur_Liste_Demandes ( Ptr_Maillon_Annonce tete );


//_____________________________________________________________________________________________________________________

/* New Type : List that containts A string ( nom du poste ) and its Frequency of apparition */

/* The list of Postes is ordered in a decreasing order following the frequency of apparition */

typedef struct liste_poste
{
    int Frequ ;
    char Nom [50];
    struct liste_poste *Next;
} liste_poste ;

typedef liste_poste* Maillon_Poste;

/* Add_liste_poste : Adds the Poste if it doesn't exist, if it does it adds it to its place and delete the last one so that the list won't be longer than asked for */

int Add_liste_poste ( Maillon_Poste *Head , Maillon_Poste Node , int size);

/* Create_List : Creates a list of postes containing X number of nodes */

Maillon_Poste Create_List ( int Num_Nodes );

//_____________________________________________________________________________________________________________________

#endif