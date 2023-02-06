#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>
#include "Display.h"
#include "EMPLOI_LLC_BIBLIO.h"
#include "Basic_Functions.h"
#include "Annonceurs.h"
#include "Offres.h"
#include "Demandes.h"
#include "Standard_Library.h"

//_____________________________________________________________________________________________________________________

Ptr_Maillon_Offre Offres_of_an_annonceur ( Ptr_Maillon_Offre Liste , int ID )
{
    Ptr_Maillon_Offre Temp = Liste ;
    while ( (Temp != NULL) && (Temp->Info.ID_rec < ID) )
    {
        Temp = Next_Offre( Temp ) ;
    }
    if ( Temp == NULL )
    {
        return NULL;
    }
    else
    {
        if ( Temp->Info.ID_rec > ID )
        {
            return NULL;
        }
        else
        {
            Ptr_Maillon_Offre Head = NULL ;
            Ptr_Maillon_Offre Temporary ;
            Ptr_Maillon_Offre Temporary_pr ;
            while ( (Temp != NULL) && ( Temp->Info.ID_rec == ID ) )
            {
                Temporary_pr = Temporary;
                Temporary = Allouer_Offre ();
                Aff_Offre_Info( Temporary , Temp->Info );
                if ( Head == NULL )
                {
                    Head = Temporary;
                }
                else
                {
                    Aff_Offre_Next(Temporary_pr,Temporary);
                }
                Temp = Next_Offre ( Temp );
            }
            return Head;
        }
    }
}

//_____________________________________________________________________________________________________________________

void Supprimer_Demande ( Ptr_Maillon_Annonce *Liste_act , Ptr_Maillon_Annonce *List_arch , int ID )
{
    if ( (*Liste_act) != NULL )
    {
        Ptr_Maillon_Annonce Temp = *Liste_act ;
        if ( (*Liste_act)->Info.ID >= ID )
        {
            (*Liste_act) = Next_Annonce( (*Liste_act) );
            Aff_Demande_Next(Temp,NULL);
            Add_Demande_Liste(List_arch,Temp);
        }
        else
        {
            Ptr_Maillon_Annonce Temp_pr;
            while ( (Temp != NULL ) && ( Temp->Info.ID < ID ) )
            {
                Temp_pr = Temp;
                Temp = Next_Annonce (Temp);
            }
            if ( Temp == NULL )
            {
                return;
            }
            else
            {
                if ( Temp->Info.ID == ID )
                {
                    Aff_Demande_Next(Temp_pr,Next_Annonce(Temp));
                    Add_Demande_Liste(List_arch,Temp);
                }
                else
                {
                    return;
                }
            }
        }
    }
}

//_____________________________________________________________________________________________________________________

void Supprimer_Offre ( Ptr_Maillon_Offre* tete_Offre_act , Ptr_Maillon_Offre* tete_offre_arch , Offre x )
{
    Ptr_Maillon_Offre q ;
    if ( *tete_Offre_act != NULL )
    {
        Ptr_Maillon_Offre p = *tete_Offre_act ;
        if ( Compare_Offer( (p->Info) , x ) == 0 ) 
        {
            *tete_Offre_act = Next_Offre(p) ;
            Add_Offre_Liste ( tete_offre_arch , p) ;
        }
        else
        {
            q = *tete_Offre_act ;
            p= Next_Offre (p) ;
            int trouve = 0 ;
            while ( (p != NULL) && (trouve==0) ) 
            {
                if ( Compare_Offer( (p->Info) , x ) == 0 )
                {
                    Aff_Offre_Next( q , Next_Offre (p) ) ;
                    Add_Offre_Liste( tete_offre_arch , p) ;
                    trouve = 1 ;
                }
                else 
                {
                    q = p ;
                    p = Next_Offre(p);
                }
            }
        }
    }
}

//_____________________________________________________________________________________________________________________

void Supprimer_Annonceur ( Ptr_Maillon_Annonceur *tete_act , Ptr_Maillon_Annonceur *tete_arch , int ID )
{
    if ( *tete_act != NULL )
    {
        Ptr_Maillon_Annonceur Temp = *tete_act;
        Ptr_Maillon_Annonceur Temp_Pr;
        while ( (Temp != NULL) && ( Temp->Info.ID != ID ) )
        {
            Temp_Pr = Temp;
            Temp = Next_Annonceur(Temp);
        }
        if ( Temp == *tete_act )
        {
            *tete_act = Next_Annonceur(*tete_act);
        }
        else
        {
            Aff_Annonceur_Next(Temp_Pr,Next_Annonceur(Temp));
        }
        Add_Annonceur_Liste(tete_arch,Temp);
    }
}

//_____________________________________________________________________________________________________________________

int Longueur_Liste_Offre ( Ptr_Maillon_Offre tete )
{
    int cpt= 0 ;
    Ptr_Maillon_Offre p = tete ;
    while (p != NULL)
    {
        cpt++;
        p = Next_Offre(p) ;
    }
    return cpt;
} 

//_____________________________________________________________________________________________________________________

void Supprimer_Annonceur_0_Ann (Ptr_Maillon_Annonceur *Liste_act , Ptr_Maillon_Annonceur *Liste_arch )
{
    Ptr_Maillon_Annonceur Temp = *Liste_act;
    while ( Temp != NULL )
    {
        if ( Temp->Info.Nbr_annonc == 0 )
        {
            Supprimer_Annonceur( Liste_act , Liste_arch , Temp->Info.ID );
        }
        Temp = Next_Annonceur ( Temp ) ;
    }
}

//_____________________________________________________________________________________________________________________

Ptr_Maillon_Annonce Demandes_by_competences (Ptr_Maillon_Annonce Head , int num )
{
    Ptr_Maillon_Annonce New_Head = NULL ;
    Ptr_Maillon_Annonce Temp = Head ;
    Ptr_Maillon_Annonce New;
    while ( Temp != NULL )
    {
        if ( strlen(Temp->Info.Liste_Competence) >= num )
        {
            New = Allouer_Annonce();
            Aff_Demande_Info(New,Get_Demande_Maillon(Temp));
            Add_Demande_Liste(&New_Head,New);
        }
        Temp = Next_Annonce( Temp );
    }
    return New_Head ;
}

//_____________________________________________________________________________________________________________________

Ptr_Maillon_Annonce Demandes_by_langues ( Ptr_Maillon_Annonce Head , int num )
{
    Ptr_Maillon_Annonce New_Head = NULL ;
    Ptr_Maillon_Annonce Temp = Head;
    Ptr_Maillon_Annonce New;
    while ( Temp != NULL )
    {
        if ( Frequ_dig(Temp->Info.Langues,num) != 0 )
        {
            New = Allouer_Annonce();
            Aff_Demande_Info(New,Get_Demande_Maillon(Temp));
            Add_Demande_Liste(&New_Head,New);
        }
        Temp = Next_Annonce(Temp);
    }
    return New_Head;
}

//_____________________________________________________________________________________________________________________

Ptr_Maillon_Annonce Demandes_by_diplome ( Ptr_Maillon_Annonce Liste , int Diplome )
{
    Ptr_Maillon_Annonce New_List = NULL ;
    Ptr_Maillon_Annonce Temp = Liste;
    Ptr_Maillon_Annonce New;
    while ( Temp != NULL )
    {
        if ( (Temp->Info.Diplome >= Diplome) && ( Temp->Info.Diplome != 7 ) )
        {
            New = Allouer_Annonce();
            Aff_Demande_Info (New,Temp->Info);
            Add_Demande_Liste(&New_List,New);
        }
        Temp = Next_Annonce ( Temp );
    }
    return New_List ;
}

//_____________________________________________________________________________________________________________________

Ptr_Maillon_Annonce Demandes_by_langues_multiple ( Ptr_Maillon_Annonce Liste , int Langue )
{
    Ptr_Maillon_Annonce New_Head = NULL ;
    Ptr_Maillon_Annonce Temp_List = NULL;
    Ptr_Maillon_Annonce Temp = NULL;
    for ( int i = 1 ; i <= Num_digits(Langue) ; i++ )
    {
        Temp = NULL;
        Temp_List = Demandes_by_langues(Liste,Which_Dig(Langue,i));
        Temp = Temp_List;
        while ( Temp != NULL )
        {
            if ( Find_Demande(New_Head,Temp->Info.ID) == NULL )
            {
                Add_Demande_Liste(&New_Head,Temp);
            }
            Temp = Next_Annonce(Temp);
        }
    }
    return New_Head;
}   

//_____________________________________________________________________________________________________________________

void Add_Demande_List_by_exp ( Ptr_Maillon_Annonce *Head , Ptr_Maillon_Annonce Node )
{
    Ptr_Maillon_Annonce To_add = Allouer_Annonce();
    Aff_Demande_Info(To_add,Get_Demande_Maillon(Node));
    if ( *Head == NULL )
    {
        *Head = To_add;
    }
    else
    {
        if ( (*Head)->Info.ExpYear >= Node->Info.ExpYear )
        {
            Aff_Demande_Next(To_add,*Head);
            *Head = To_add;
        }
        else
        {
            Ptr_Maillon_Annonce Temp = *Head ;
            Ptr_Maillon_Annonce Temp_pr;
            while ( (Temp != NULL) && ( Temp->Info.ExpYear < To_add->Info.ExpYear ) )
            {
                Temp_pr = Temp;
                Temp = Next_Annonce ( Temp );
            }
            Aff_Demande_Next(Temp_pr,To_add);
            Aff_Demande_Next(To_add,Temp);
        }
    }
}

//_____________________________________________________________________________________________________________________

Ptr_Maillon_Annonce Demandes_by_competences_multiple ( Ptr_Maillon_Annonce Liste , char *Str )
{
    Ptr_Maillon_Annonce New_Head = NULL;
    Ptr_Maillon_Annonce New = NULL;
    Ptr_Maillon_Annonce Temp = Liste ;
    int check = 0;
    while ( Temp != NULL )
    {
        check = 0;
        if ( Str[0] == 'q' )
        {
            check = 2;
        }
        else
        {
            if ( strlen(Str) == 1 )
            {
                if ( strchr(Temp->Info.Liste_Competence,Str[0]) != NULL )
                {
                    check = 2;
                }
            }
            else
            {
                int i = 0;
                while ( (check < 2) && ( Str[i] != 0 ) && ( Temp->Info.Liste_Competence[i] != 0 ) )
                {
                    if ( strchr(Temp->Info.Liste_Competence,Str[i]) != NULL )
                    {
                        check++ ;
                    }
                    i++;
                }
            }
        }
        if ( check > 1 )
        {
            New = Allouer_Annonce();
            Aff_Demande_Info(New,Get_Demande_Maillon(Temp));
            Aff_Demande_Next(New,NULL);
            Add_Demande_List_by_exp (&New_Head,New);
        }
        Temp = Next_Annonce ( Temp );   
    }
    return New_Head ;
}

//_____________________________________________________________________________________________________________________

void Add_offre_by_compet ( Ptr_Maillon_Offre *Liste , Ptr_Maillon_Offre Node )
{
    Ptr_Maillon_Offre ADD = Allouer_Offre();
    Aff_Offre_Info(ADD,Get_Offre_Maillon(Node));
    Aff_Offre_Next(ADD,NULL);  
    if ( *Liste == NULL )
    {
        *Liste = ADD;
    }
    else
    {
        int variable = strlen( Node->Info.Liste_Competence );
        Ptr_Maillon_Offre Temp = *Liste;
        if ( Node->Info.Liste_Competence[0] == 'q' )
        {
            *Liste = ADD;
            Aff_Offre_Next(*Liste,Temp);
        }
        else
        {
            Ptr_Maillon_Offre Temp_pr = *Liste ;
            while ( (Temp != NULL) && ( Temp->Info.Liste_Competence[0] == 'q' ) )
            {
                Temp_pr = Temp;
                Temp = Next_Offre(Temp);
            }
            if ( strlen(Node->Info.Liste_Competence) < strlen(Temp->Info.Liste_Competence) )
            {
                if ( Temp == Temp_pr )
                {
                    *Liste = ADD;
                    Aff_Offre_Next(*Liste,Temp);
                }
                else
                {
                    Aff_Offre_Next(Temp_pr,ADD);
                    Aff_Offre_Next(ADD,Temp);
                }
            }
            else
            {
                while (  (Temp != NULL) && (strlen(Node->Info.Liste_Competence) < strlen(Temp->Info.Liste_Competence)) )
                {
                    Temp_pr = Temp;
                    Temp = Next_Offre(Temp);
                }
                if ( Temp == Temp_pr )
                {
                    *Liste = ADD;
                    Aff_Offre_Next(*Liste,Temp);
                }
                else
                {
                    Aff_Offre_Next(Temp_pr,ADD);
                    Aff_Offre_Next(ADD,Temp);
                }
            }
        }
    }
}

//_____________________________________________________________________________________________________________________

void Delete_Offres_ID ( Ptr_Maillon_Offre *List_act , Ptr_Maillon_Offre *List_arch , int ID )
{
    Ptr_Maillon_Offre Temp = *List_act;
    while ( Temp != NULL )
    {
        if ( Temp->Info.ID_rec == ID )
        {
            Supprimer_Offre(List_act,List_arch,Temp->Info);
        }
        Temp = Next_Offre( Temp );
    }
}

//_____________________________________________________________________________________________________________________

int Longueur_Liste_Annonceurs ( Ptr_Maillon_Annonceur tete )
{
    int cpt= 0 ;
    Ptr_Maillon_Annonceur p = tete ;
    while (p != NULL)
    {
        cpt++;
        p = Next_Annonceur(p) ;
    }
    return cpt;
} 

//_____________________________________________________________________________________________________________________

int Longueur_Liste_Demandes ( Ptr_Maillon_Annonce tete )
{
    int cpt= 0 ;
    Ptr_Maillon_Annonce p = tete ;
    while (p != NULL)
    {
        cpt++;
        p = Next_Annonce (p) ;
    }
    return cpt;
} 

//_____________________________________________________________________________________________________________________

int Add_liste_poste ( Maillon_Poste *Head , Maillon_Poste Node , int size )
{
    Maillon_Poste To_add = (liste_poste*)malloc(sizeof(liste_poste));
    To_add->Frequ = Node->Frequ ;
    strcpy(To_add->Nom,Node->Nom);
    To_add->Next = NULL ;
    
    if ( *Head == NULL )
    {
        *Head = To_add;
        return Node->Frequ;
    }
    else
    {
        Maillon_Poste Temp = *Head;
        if ( (*Head)->Frequ < To_add->Frequ )
        {
            *Head = To_add ;
            (*Head)->Next = Temp ;
        }
        else
        {
            Maillon_Poste Temp_pr ;
            while ( (Temp != NULL) && ( Temp->Frequ >= To_add->Frequ ) )
            {
                if ( strcmp(Temp->Nom,Node->Nom) == 0 )
                {
                    goto End;
                }
                Temp_pr = Temp ;
                Temp = Temp->Next ;
            }
            if ( strcmp( Temp->Nom,Node->Nom )!=0 )
            {
                Temp_pr->Next = To_add ;
                To_add->Next = Temp ;
            }
        }
End:
        Temp = *Head;
        for ( int i = 1 ; i < size ; i++ )
        {
            Temp = Temp->Next;
        }
        Temp->Next = NULL ;
        return Temp->Frequ ;
    }
    
}

//_____________________________________________________________________________________________________________________

Maillon_Poste Create_List ( int Num_Nodes )
{
    Maillon_Poste Head = NULL ;
    Maillon_Poste Temp ;
    Maillon_Poste Previous ;
    for ( int i = 0 ; i < Num_Nodes ; i++ )
    {
        Maillon_Poste New = (liste_poste*)malloc(sizeof(liste_poste));
        strcpy(New->Nom,"");
        New->Frequ = 0 ;
        if ( Head == NULL )
        {
            Head = New ;
            Head->Next = NULL ;
            Previous = Head ;
        }
        else
        {
            Temp = New ;
            Previous->Next = Temp ;
            Previous = Temp ;
            Temp->Next = NULL ;
        }
    }
    
    return Head;
}

//_____________________________________________________________________________________________________________________