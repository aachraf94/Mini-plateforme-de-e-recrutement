#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include "Display.h"
#include "EMPLOI_LLC_BIBLIO.h"


//_____________________________________________________________________________________________________________________

/* Start Machine Abstraite */

//_____________________________________________________________________________________________________________________

/* Start Machine Abstraite Annonceur  */

Ptr_Maillon_Annonceur Allouer_Annonceur (  )
{
    Ptr_Maillon_Annonceur Maillon ;
    Maillon = ( Ptr_Maillon_Annonceur ) malloc(sizeof(Maillon_Annonceur));
    Maillon->Next = NULL;
    return Maillon;
}
void Liberer_Annonceur ( Ptr_Maillon_Annonceur Personne )
{
    free(Personne);
}
Ptr_Maillon_Annonceur Next_Annonceur ( Ptr_Maillon_Annonceur Personne ) 
{
    return (Personne->Next);
}
Annonceur Get_Annonceur_Maillon ( Ptr_Maillon_Annonceur Personne )
{
    return Personne->Info;
}
void Aff_Annonceur_Info ( Ptr_Maillon_Annonceur Personne , Annonceur Data )
{
    Personne->Info = Data;
}
void Aff_Annonceur_Next ( Ptr_Maillon_Annonceur Personne , Ptr_Maillon_Annonceur Next_Personne )
{
    Personne->Next = Next_Personne;
}

/* End Machine Abstraite Annonceur  */

//_____________________________________________________________________________________________________________________

/* Start Machine Abstraite Offre  */

Ptr_Maillon_Offre Allouer_Offre (  )
{
    Ptr_Maillon_Offre Maillon;
    Maillon = (Ptr_Maillon_Offre) malloc(sizeof(Maillon_Offre));
    Maillon->Next = NULL;
    return Maillon;
}
void Liberer_Offre ( Ptr_Maillon_Offre Offer )
{
    free(Offer);
}
Ptr_Maillon_Offre Next_Offre ( Ptr_Maillon_Offre Offer )
{
    return (Offer->Next);
}
Offre Get_Offre_Maillon ( Ptr_Maillon_Offre Offer )
{
    return Offer->Info;
}
void Aff_Offre_Info ( Ptr_Maillon_Offre Offer , Offre Data )
{
    Offer->Info = Data;
}
void Aff_Offre_Next ( Ptr_Maillon_Offre Offer , Ptr_Maillon_Offre Next_Offer )
{
    Offer->Next = Next_Offer;
}

/* End Machine Abstraite Offre  */

//_____________________________________________________________________________________________________________________

/* Start Machine Abstraite Annonce  */

Ptr_Maillon_Annonce Allouer_Annonce (  )
{
    Ptr_Maillon_Annonce Maillon;
    Maillon = (Ptr_Maillon_Annonce) malloc (sizeof(Maillon_Annonce));
    Maillon->Next = NULL;
    return Maillon;
}
void Liberer_Annonce ( Ptr_Maillon_Annonce Ann )
{
    free(Ann);
}
Ptr_Maillon_Annonce Next_Annonce ( Ptr_Maillon_Annonce Ann )
{
    return Ann->Next;
}
Demande Get_Demande_Maillon ( Ptr_Maillon_Annonce Ann )
{
    return Ann->Info;
}
void Aff_Demande_Info ( Ptr_Maillon_Annonce Ann , Demande Data )
{
    Ann->Info = Data;
}
void Aff_Demande_Next ( Ptr_Maillon_Annonce Ann , Ptr_Maillon_Annonce Next_Ann )
{
    Ann->Next = Next_Ann;
}

/* End Machine Abstraite Annonce  */

//_____________________________________________________________________________________________________________________

/* End Machine Abstraite */

//_____________________________________________________________________________________________________________________