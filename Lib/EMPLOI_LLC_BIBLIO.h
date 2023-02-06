#ifndef _Data_Structures_
#define _Data_Structures_

//_____________________________________________________________________________________________________________________

/* Start Data Structures */

typedef struct Annonceur      // annonceur : poste des offres d'emploi
{
    int ID ; // ID est crée par une fonction déclrée ci apres, et qui utilise une equation mathematique avec le string du nom
    char Nom [ 50 ];
    char Adresse [ 200 ];
    char Mail [ 50 ];
    char Num_Tel [ 20 ];
    int Nbr_annonc ;
} Annonceur ;
typedef struct Offre          // offre d'emploi
{
    int ID_rec ; // to link offres with its annonceur via ID in a more optimized method 
    char Nom [ 50 ];
    char Nom_Poste [ 50 ];
    int Diplome ;
    int  ExpYear;
    char Liste_Competence [18] ;
    int Langues ;
    int Date_Publication [ 3 ];
    int Delai_Condidature [ 3 ];
} Offre;
typedef struct Demande        // annonce de demande d'emploi
{
    int ID;
    char Nom_Demandeur [ 50 ]; // Same way to get ID
    int Diplome ;
    int  ExpYear;
    char Liste_Competence [18] ;
    int Langues ;
    int Date_Publication [ 3 ];
} Demande;

/* End Data Structures */

//_____________________________________________________________________________________________________________________

/* Start Maillons */

typedef struct Maillon_Annonceur
{
    Annonceur Info;
    struct Maillon_Annonceur *Next ;
} Maillon_Annonceur ;
typedef Maillon_Annonceur* Ptr_Maillon_Annonceur;

typedef struct Maillon_Offre
{
    Offre Info;
    struct Maillon_Offre *Next ;
} Maillon_Offre ;
typedef Maillon_Offre* Ptr_Maillon_Offre;

typedef struct Maillon_Annonce
{
    Demande Info;
    struct Maillon_Annonce *Next ;
} Maillon_Annonce;
typedef Maillon_Annonce* Ptr_Maillon_Annonce;

/* End Maillons */

//_____________________________________________________________________________________________________________________

/* Start Machine Abstraite Annonceurs */

Ptr_Maillon_Annonceur Allouer_Annonceur (  );
void Liberer_Annonceur ( Ptr_Maillon_Annonceur Personne );
Ptr_Maillon_Annonceur Next_Annonceur ( Ptr_Maillon_Annonceur Personne );
Annonceur Get_Annonceur_Maillon ( Ptr_Maillon_Annonceur Personne );
void Aff_Annonceur_Info ( Ptr_Maillon_Annonceur Personne , Annonceur Data );
void Aff_Annonceur_Next ( Ptr_Maillon_Annonceur Personne , Ptr_Maillon_Annonceur Next_Personne );

/* End Machine Abstraite Annonceurs */

//_____________________________________________________________________________________________________________________

/* Start Machine Abstraite Offres */

Ptr_Maillon_Offre Allouer_Offre (  );
void Liberer_Offre ( Ptr_Maillon_Offre Offer );
Ptr_Maillon_Offre Next_Offre ( Ptr_Maillon_Offre Offer );
Offre Get_Offre_Maillon ( Ptr_Maillon_Offre Offer );
void Aff_Offre_Info ( Ptr_Maillon_Offre Offer , Offre Data );
void Aff_Offre_Next ( Ptr_Maillon_Offre Offer , Ptr_Maillon_Offre Next_Offer );

/* End Machine Abstraite Offres */

//_____________________________________________________________________________________________________________________

/* Start Machine Abstraite Annonces */

Ptr_Maillon_Annonce Allouer_Annonce (  );
void Liberer_Annonce ( Ptr_Maillon_Annonce Ann );
Ptr_Maillon_Annonce Next_Annonce ( Ptr_Maillon_Annonce Ann );
Demande Get_Demande_Maillon ( Ptr_Maillon_Annonce Ann );
void Aff_Demande_Info ( Ptr_Maillon_Annonce Ann , Demande Data );
void Aff_Demande_Next ( Ptr_Maillon_Annonce Ann , Ptr_Maillon_Annonce Next_Ann );

/* End Machine Abstraite Annonces */

//_____________________________________________________________________________________________________________________

#endif