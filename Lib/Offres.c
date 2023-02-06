#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>
#include "Display.h"
#include "EMPLOI_LLC_BIBLIO.h"
#include "Basic_Functions.h"
#include "Annonceurs.h"
#include "Offres.h"

//_____________________________________________________________________________________________________________________

/* La liste des Offres est ordonnée par ordre croissant des ID des annonceurs */

//_____________________________________________________________________________________________________________________

/* Empty_Offre : Initializes The Offer to false values to avoid the garbage values */

void Empty_Offre ( Offre *Smth )
{
    strcpy((*Smth).Nom,"");
    strcpy((*Smth).Nom_Poste,"");
    (*Smth).ID_rec = 0;
    (*Smth).ExpYear = -1;
    strcpy((*Smth).Liste_Competence,"");
    (*Smth).Langues = 0;
    (*Smth).Diplome = 0;
}

/* De_normalize : changes spaces to _ to store the data in the file */

Offre De_Normalize_Off (Offre Offer , int command)
{
    /*
    The role of this function is to :
    - if command == 1 : Replace every space with _ in a string
    - if command == 0 : Replace every _ with space in a string
    This is helpful when saving info in a file, cuz without it reading a file would be very challenging or impossible in some cases 
    */
    Offre N = Offer;
    strcpy(N.Nom,Norm(N.Nom,command));
    strcpy(N.Nom_Poste,Norm(N.Nom_Poste,command));
    return N;  
}

/* Print_Offre : prints the information on an Offre */

void Print_Offre ( Offre Two , int command_rec , int command_id , Ptr_Maillon_Annonceur Liste )
{
    /* When we print this offer, we suppose that the announcer already is subscribed and verifying that is done somewhere else */
    if ( Two.ID_rec != 0 )
    {
        Offre One = De_Normalize_Off ( Two , 0 );
        if ( command_rec == 1 )
        {
            Annonceur Guy ;
            Guy = Get_Annonceur_Maillon( Find_Annonceur( Liste , One.ID_rec ) );
            printf("\t\t\t== Voici Les Informations de l'Annonceur ==\n");
            Print_Annonceur ( Guy , 1 , 1 );
            printf("\n\t\t\t== Voici Les informations de l'Offre ==\n\n");
        }
        else
        {
            if ( command_id == 1 ) 
            {
                printf("\t\t> ID                              : %d\n",One.ID_rec);
            }
            printf("\t\t> Nom du recruteur                : %s\n",One.Nom);
        }    
        printf("\t\t> Intitule du poste               : %s\n",One.Nom_Poste);
        printf("\t\t> Diplome exige                   : %s\n",Print_Diploma(One.Diplome));
        printf("\t\t> Annees d'experience requises    : %d ans\n",One.ExpYear);
        printf("\t\t> Liste des competences requises  : ");
        
        /* Start printing the competences one by one : to avoid printing half of it in a lin and the other half in the other half */
        
        int i = 0;
        char Competences [ 500 ] = "";
        strcpy(Competences,Print_Competences(One.Liste_Competence));
        while( ( i<strlen( Competences ) ) && (Competences [i] != '\0') )
        {
            if ( strstr(One.Liste_Competence,"q") == NULL  )
            {
                printf("- ");
            }
            while ( (Competences[i] != ',') && ( i<strlen( Competences ) ) && (Competences [i] != '\0') )
            {
                printf("%c",Competences[i]);
                i++;
            }
            i+=2;
            if ( ( Competences [i-1] != '\0' ) || (Competences [i] != '\0') ) 
            {
                printf("\n");
                printf("\t\t\t\t\t\t    "); 
            }
        } 
        /* End printing the competences one by one */
        
        printf("\n\t\t> Langues requises                : %s\n",Print_Languages(One.Langues));
        printf("\t\t> Date de publication de l'offre  : ");
        print_date(One.Date_Publication);
        printf("\n");
        printf("\t\t> Delai de condidature            : ");
        print_date(One.Delai_Condidature);
        printf("\n");
    }
}

/* String_2_Offre : scans the information in a string " which is gonna be read from a file " and puts it in the Offre */

Offre String_2_Offre ( char *info )
{
    Offre One;
    sscanf(info,"%i %s %s %i %i %s %i %i %i %i %i %i %i",&One.ID_rec,&One.Nom,&One.Nom_Poste,&One.Diplome,&One.ExpYear,&One.Liste_Competence,&One.Langues,&One.Date_Publication[0],&One.Date_Publication[1],&One.Date_Publication[2],&One.Delai_Condidature[0],&One.Delai_Condidature[1],&One.Delai_Condidature[2]);
    return One;
}

/* Liberer_Liste_Offre : to free all the memory allocated for the lists at the end of the execution of the program */

void Liberer_Liste_Offres ( Ptr_Maillon_Offre *Head )
{
    Ptr_Maillon_Offre Temp = *Head;
    Ptr_Maillon_Offre Temp_Next ;
    while ( Temp != NULL )
    {
        Temp_Next = Next_Offre ( Temp );
        Liberer_Offre( Temp );
        Temp = Temp_Next;
    }
    *Head = NULL;
}

/* Add_Offre_Liste : Adds the Offre in its place following the order of the ID, and then the publication date */

void Add_Offre_Liste ( Ptr_Maillon_Offre *Head , Ptr_Maillon_Offre Offer1 )
{
    Ptr_Maillon_Offre ADD = Allouer_Offre();
    Aff_Offre_Info(ADD,Get_Offre_Maillon(Offer1));
    Aff_Offre_Next(ADD,NULL);
    if ( *Head == NULL )
    {
        *Head = ADD;
    }
    else
    {
        Ptr_Maillon_Offre Temp = *Head;
        if ( (*Head)->Info.ID_rec > Offer1->Info.ID_rec )
        {
            *Head = ADD;
            Aff_Offre_Next(*Head,Temp);
        }
        else
        {
            Ptr_Maillon_Offre Temp_pr = *Head ;
            if ( ((*Head)->Info.ID_rec == Offer1->Info.ID_rec) )
            {
                if ( ( Compare_Dates((*Head)->Info.Date_Publication,Offer1->Info.Date_Publication) != 1 ) )
                {
                    *Head = ADD;
                    Aff_Offre_Next(*Head,Temp);
                }
                else
                {
                    while( (Temp != NULL) && ( Temp->Info.ID_rec == Offer1->Info.ID_rec ) && ( Compare_Dates(Temp->Info.Date_Publication,Offer1->Info.Date_Publication) == 1 ) )
                    {
                        Temp_pr = Temp;
                        Temp = Next_Offre (Temp);
                    }
                    Aff_Offre_Next(Temp_pr,ADD);
                    Aff_Offre_Next(ADD,Temp);
                }
            }
            else
            {
                while ( (Temp != NULL) && ( Temp->Info.ID_rec < Offer1->Info.ID_rec ) )
                {
                        Temp_pr = Temp;
                        Temp = Next_Offre(Temp);
                }
                if ( Temp != NULL )
                {
                    if ( ((Temp)->Info.ID_rec == Offer1->Info.ID_rec) )
                    {
                        if ( ( Compare_Dates((Temp)->Info.Date_Publication,Offer1->Info.Date_Publication) != 1 ) )
                        {
                            Aff_Offre_Next(Temp_pr,ADD);
                            Aff_Offre_Next(ADD,Temp);
                        }
                        else
                        {
                            while( (Temp != NULL) && ( Temp->Info.ID_rec == Offer1->Info.ID_rec ) && ( Compare_Dates(Temp->Info.Date_Publication,Offer1->Info.Date_Publication) == 1 ) )
                            {
                                Temp_pr = Temp;
                                Temp = Next_Offre (Temp);
                            }
                            Aff_Offre_Next(Temp_pr,ADD);
                            Aff_Offre_Next(ADD,Temp);

                        }
                    }
                    else
                    {
                        Aff_Offre_Next(Temp_pr,ADD);
                        Aff_Offre_Next(ADD,Temp);
                    }
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

/* print_Liste_Offres : prints the list of annonceurs One by one */

void print_Liste_Offres ( Ptr_Maillon_Offre Head , int command_info_rec , Ptr_Maillon_Annonceur Liste )
{
    if ( Head == NULL )
    {
        Cyan();
        printf("\n\tLa liste des Offres est Vide ...");
        fflush(stdin);
        getch();
        Reset();
        return;
    }
    Ptr_Maillon_Offre Temp = Head;
    int i = 1 ;
    int done = 0;
    char test;
    while ( (Temp != NULL) && ( done == 0 ) )
    {
        Clear_Screen();
        if ( i == 1 )
        {
            printf("\t\t\t\t== La 1 ere Offre : ==\n");
        }
        else
        {
            printf("\t\t\t\t== La %d eme Offre : ==\n",i);
        }
        Print_Offre(Temp->Info,command_info_rec,1,Liste);
        i++;
        Cyan();
        printf("\t\tAppuyez sur une touche pour continuer L'affichage ou sur ECHAP pour quitter...");
        Reset();
        fflush(stdin);
        test = getch();
        if ( test == 27 )
        {
            done = 1;
        }
        Temp = Next_Offre(Temp);
    }
    if ( (Temp == NULL) && ( done != 1 ) )
    {
        Cyan();
        printf("\n\tVous avez attient la fin de la liste des Offres ...");
        fflush(stdin);
        getch();
        Reset();
    }
}

/* Read_Liste_Offre_file : Reads from the file the list of offres and returns the head */

Ptr_Maillon_Offre Read_Liste_Offre_file ( FILE *file_name )
{
    long size;
    fseek(file_name,0,SEEK_END);  /* check if the end IS the start so the file is empty */
    size = ftell(file_name);
    if ( size == 0 )
    {
        return NULL;
    }
    else
    {
        fseek(file_name,0,SEEK_SET); /* go back to the start cuz we went to theend at first to check if the file is empty */
        Ptr_Maillon_Offre Head = Allouer_Offre();
        char Temp_str [350];    /* This is a temporary string which stores the value read from the the file */
        char Temp_str_pr [350]; /* This is a temporary string which stores the value read from the the file the last time, and it's here to chek if it's the same as the revious so it stops reading */
        fgets(Temp_str,350,file_name);
        Aff_Offre_Info( Head , String_2_Offre(Temp_str) );
        Ptr_Maillon_Offre Temp_ptr_pr = Head;
        fgets(Temp_str,350,file_name);
        while ( (strcmp(Temp_str,Temp_str_pr) != 0) &&  (Temp_str[0] != 2) && ( Temp_str[0] != 10 ) )
        {
            Ptr_Maillon_Offre Temp_ptr = Allouer_Offre () ;
            Aff_Offre_Info( Temp_ptr , String_2_Offre ( Temp_str ) );
            Aff_Offre_Next( Temp_ptr_pr , Temp_ptr );
            Temp_ptr_pr = Temp_ptr;
            strcpy(Temp_str_pr,Temp_str);
            fgets(Temp_str,350,file_name);
        }
        return Head;

    }
}

/* Offre_2_string : fills the string with the information of the offer following the layout */

char *Offre_2_string ( Offre Offer1 )
{
    static char string_to_print[350];
    strcpy(string_to_print,"");
    sprintf(string_to_print,"%d %s %s %d %d %s %d %d %d %d %d %d %d\n",Offer1.ID_rec,Offer1.Nom,Offer1.Nom_Poste,Offer1.Diplome,Offer1.ExpYear,Offer1.Liste_Competence,Offer1.Langues,Offer1.Date_Publication[0],Offer1.Date_Publication[1],Offer1.Date_Publication[2],Offer1.Delai_Condidature[0],Offer1.Delai_Condidature[1],Offer1.Delai_Condidature[2]);
    return string_to_print;
}

/* Print_Offres_file : prints the list to the file */

void Print_Offres_file ( FILE *file_name , Ptr_Maillon_Offre Head )
{
    Ptr_Maillon_Offre Temp = Head;
    while ( Temp != NULL )
    {
        fprintf(file_name,Offre_2_string(Temp->Info));
        Temp = Next_Offre(Temp);
    }
}

/* Compare_Offer : compraes all the fielsds of the offer, returns 1 if they're identically the same, 0 if at least there's one field different */

int Compare_Offer ( Offre Offer1 , Offre Offer2 )
{
    /*
    Return 1 if they're different, 0 if they are identically the same
    */
    
    if ( Offer1.ID_rec != Offer2.ID_rec )
    {
        return 1;
    }
    else
    {
        if ( Compare_Dates(Offer1.Date_Publication,Offer2.Date_Publication) != 0 )
        {
            return 1;
        }
        else
        {
            if ( Compare_Dates( Offer1.Delai_Condidature,Offer2.Delai_Condidature ) != 0 )
            {
                return 1;
            }
            else
            {
                if ( Offer1.Diplome != Offer2.Diplome )
                {
                    return 1;
                }
                else
                {
                    if ( Offer1.ExpYear != Offer2.ExpYear )
                    {
                        return 1;
                    }
                    else
                    {
                        if ( Offer1.Langues != Offer2.Langues )
                        {
                            return 1;
                        }
                        else
                        {
                            if ( strcmp( Offer1.Nom_Poste,Offer2.Nom_Poste ) != 0 )
                            {
                                return 1;
                            }
                            else
                            {
                                if ( strcmp(Offer1.Liste_Competence,Offer2.Liste_Competence) != 0 )
                                {
                                    return 1;
                                }
                                else
                                {
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/* Find_offre : Looks for the Offer in the List : if it's in there it returns its pointer else it returns NULL */

Ptr_Maillon_Offre Find_offre ( Ptr_Maillon_Offre Head , Offre Offer1 )
{
    /*
    returns NULL if nothing is found, the pointer of the node else
    */
    Ptr_Maillon_Offre Temp = Head ;
    while ( Temp != NULL )
    {
        if ( Compare_Offer( Temp->Info , Offer1 ) == 0 )
        {
            return Temp;
        }
        Temp = Next_Offre( Temp );
    }
    return NULL;
}

/* New_Offre : Reads new offer from the user */

Offre New_Offre ( Ptr_Maillon_Annonceur Liste_Ann , Ptr_Maillon_Offre Liste_Off )
{
    /*
    Increments number of annonces of an annonceur
    Returns an offer; if no offer is read: the ID is 0
    Errors handled : 
    - Dates :   valid dates only
                coherent dates only : can't enter a delai before publication date
    - Exp : betwenn 0 and 40
    - everything logical that can come to a human being's mind is handled
    */
    
    Offre New;
    Empty_Offre(&New);
    char ans[40];
    char rep;
    char ans1[40];
    char rep1;
    int did = 0;
    
    Clear_Screen();
    
    printf("\t=== Vous etes entrain d'enregistrer une nouvelle annonce ===\n\n");

Error1:
    if ( did == 0 )
    {
        printf("\t\tEtes vous deja un de nos annonceurs? Saisissez O pour Oui ou N pour Non : ");
    }
    else
    {
        printf("\t\tEtes vous deja un de nos annonceurs? ");
        Red();
        printf("Saisissez O pour Oui ou N pour Non : ");
        Reset();
    }
    fgets(ans1,40,stdin);
    Remove_Entree(ans1);
    rep1 = toupper(ans1[0]);
    did = 1;
    if (  ( ans1[1] != 0 ) || ((rep1 != 'O') && (rep1 != 'N')) ) 
    {
        Go_up_Clear_line(1);
        if ( strlen(ans1)>=30 )
        {
            Go_up_Clear_line(1);
        }
        goto Error1;
    }
    did = 0;
    if ( rep1 == 'N' )
    {
        Cyan();
        printf("\n\tVous n'etes pas un de nos Annonceurs, veuillez vous inscrire avant de poster une offre !\n");
        fflush(stdin);
        getch();
        Reset();
        goto End;
    }
    else
    {
        char String [50];
        int ID;
           
        Clear_Screen();
        printf("\t=== Vous etes entrain d'enregistrer une nouvelle annonce ===\n");
Nom:
        did = 0;
        printf("\n\t\t> Nom                        : ");
        fgets(String,50,stdin);
        strcpy(New.Nom,String);
        Remove_Entree(New.Nom);
        strcpy(New.Nom,Name(New.Nom));
        ID = Nom_ID (New.Nom);
        New.ID_rec = ID;
        if ( Find_Annonceur(Liste_Ann,ID) == NULL )
        {
            printf("\n\t\tVous ne figurez pas sur la liste de nos annonceurs!\n");
            printf("\n");
check:
            printf("\tVerifiez votre Nom : ");
            Cyan();
            printf("%s",New.Nom);
            Reset();
            printf(" ? ");
            if ( did == 0 )
            {
                printf("Saisissez V pour vrai et F pour faux : ");
            }
            else
            {
                Red();
                printf("Saisissez V pour vrai et F pour faux : ");
                Reset();
            }
            strcpy(String,"");
            fgets(String,100,stdin);
            Remove_Entree(String);
            rep = toupper(String[0]);
            did = 1 ;
            if ( (strlen(String) != 1 ) || (( rep != 'V' ) && ( rep != 'F' )) )
            {
                Go_up_Clear_line(1);
                if ( strlen(String) >= 50 - strlen(New.Nom) )
                {
                    Go_up_Clear_line(1);
                }
                goto check;
            }
            if ( rep == 'F' )
            {
                Go_up_Clear_line(6);
                goto Nom;
            }
            else
            {
                New.ID_rec = 0;
                Cyan();
                printf("\n\t\t\tVeuillez vous inscrire avant de poster une offre ! \n");
                fflush(stdin);
                getch();
                Reset();
                goto End;                    
            }
        }
        did = 0;       
Nom_poste:
        if ( did == 0 )
        {
            printf("\n\t\tEntrez le nom du poste : ");
        }
        else
        {
            printf("\t\tEntrez le nom du poste : ");
            Red();
            printf("\t\t\t\t\tNom du poste Invalide\r");
            Reset();
            printf("\t\t\t\t\t ");
        }
        fgets(New.Nom_Poste,50,stdin);
        Remove_Entree(New.Nom_Poste);
        strcpy(New.Nom_Poste,Name(New.Nom_Poste));
        did = 1;
        if ( strlen(New.Nom_Poste) < 5 )
        {
            Go_up_Clear_line(1);
            goto Nom_poste;
        }
        Go_up_Clear_line(1);
        printf("\t\t> Nom du poste : %s\n",New.Nom_Poste);
        did = 0;

Diplome:
        if ( did == 0 )
        {
            Diploma Choix_Diplome [7];
            Get_Diploma (Choix_Diplome);
            Print_Diploma_Box(Choix_Diplome);
        }
        printf("\n\t\tEntrez l'indexe du diplome exige ");
        if ( did == 0 )
        {
            printf("( indexe entre 1 et 7 ) : ");
        }
        else
        {
            Red();
            printf("( indexe entre 1 et 7 ) : ");
            Reset();
        }
        strcpy(String,"");
        fgets(String,50,stdin);
        Remove_Entree(String);
        New.Diplome = 0 ;
        sscanf(String,"%d",&New.Diplome);
        did = 1;
        if ( ( strlen(String) > 1 ) || ( New.Diplome>7 ) || ( New.Diplome<1 ) )
        {
            Go_up_Clear_line(1);
            Go_up(1);
            goto Diplome;
        }
        Go_up_Clear_line(12);
        printf("\t\t> Diplome exige              : %s\n",Print_Diploma(New.Diplome));
        printf("\n");
        did = 0; 

Exp:
        printf("\t\tEntrez le nombre d'annees d'experience exige ");
        if ( did == 0 )
        {
            printf("( entre 0 an et 40 ans ) : ");
        }
        else
        {
            Red();
            printf("( entre 0 an et 40 ans ) : ");
            Reset();
        }
        strcpy(String,"");
        fgets(String,50,stdin);
        Remove_Entree(String);
        sscanf(String,"%i",&New.ExpYear);
        did = 1;
        if ( (strlen(String) > 2) || (New.ExpYear < 0) )
        {
            // pas d'annees d'experience negative et logiquement pas plus de 40
            Go_up_Clear_line(1);
            goto Exp;
        }
        else
        {
            if ( (strlen(String) == 2) && (( New.ExpYear <10 ) || (New.ExpYear > 40) ) )
            {
                Go_up_Clear_line(1);
                goto Exp;
            }
        }

        Go_up_Clear_line(1);

        if ( New.ExpYear == 0 )
        {
            printf("\t\t> Annes d'Experience exigee  : %d\n", New.ExpYear );
        }
        else if (New.ExpYear == 1)
        {
            printf("\t\t> Annes d'Experience exigee  : %d an\n", New.ExpYear );
        }
        else
        {
            printf("\t\t> Annes d'Experience exigee  : %d ans\n", New.ExpYear );
        
        }                                      
        did = 0 ;

Compet:
        if ( did == 0 )
        {
            Comptences Choix_competences [17];
            Get_Competences ( Choix_competences );
            Print_Competences_Box (Choix_competences);
            printf("\n");
        }
        if ( did == 0 )
        {
            printf("\t\tEntrez la combinaison des indexes des competences exiges ( entre 'a' et 'p' ou 'q' ) : ");
        }
        else
        {
            printf("\t\tEntrez la combinaison des indexes des competences exiges ");
            Red();
            printf("( entre 'a' et 'p' ou 'q' ) : ");
            Reset();
        }
        int bool;
        char Str_temp [50] = "";
        strcpy(String,"");
        fgets(String,50,stdin);
        Remove_Entree(String);
        Lower_str(String);
        strcpy(Str_temp,Uniqu_str ( String ));
        strcpy(New.Liste_Competence, Str_temp );
        did = 1;
        if ( strlen(String) != strlen(New.Liste_Competence) )
        {
            bool = 0;
        }
        else
        {
            if ( (strlen(New.Liste_Competence) <= 1) || ( strlen(String) != strlen(New.Liste_Competence) ) )
            {
                if ( (max_char(New.Liste_Competence) <= 'q') && (min_char(New.Liste_Competence)>='a' ) )
                {
                    bool = 1;
                }
                else
                {
                    bool = 0;
                }
            }
            else if ( strlen( New.Liste_Competence ) > 1 )
            {
                if ( (strchr ( New.Liste_Competence , 'q' ) != NULL) || (max_char(New.Liste_Competence) > 'q') || (min_char(New.Liste_Competence)<'a' )  )
                {
                    bool = 0;
                }
                else
                {
                    bool = 1;
                }
            }
        }
        if ( bool == 0 )
        {
            Go_up_Clear_line(1);
            goto Compet;
        }

        Go_up_Clear_line(22);
        
        printf("\t\t> Competences exiges         : ");
        int i = 0;
        char Competences [ 200 ] = "";
        strcpy(Competences,Print_Competences(New.Liste_Competence));
        while( ( i<strlen( Competences ) ) && (Competences [i] != '\0') )
        {
            if ( strstr(New.Liste_Competence,"q") == NULL  )
            {
                printf("- ");
            }
            while ( (Competences[i] != ',') && ( i<strlen( Competences ) ) && (Competences [i] != '\0') )
            {
                printf("%c",Competences[i]);
                i++;
            }
            i+=2;
            if ( ( Competences [i-1] != '\0' ) || (Competences [i] != '\0') ) 
            {
                printf("\n");
                printf("\t\t\t\t\t       "); 
            }
        }
        did = 0;

Language:
        if ( did == 0 )
        {
            Langue Choix_Langue [7];
            Get_Langue ( Choix_Langue );
            Print_Languages_Box ( Choix_Langue );
        }
        printf("\n\t\tEntrez la combinaison des indexes des langues exigees ");
        if ( did == 0 )
        {
            printf("( chiffres entre 1 et 7 ) : ");
        }  
        else
        {
            Red();
            printf("( chiffres entre 1 et 7 ) : ");
            Reset();
        }    
        strcpy(String,"");
        fgets(String,50,stdin);
        Remove_Entree(String);
        sscanf(String,"%d",&New.Langues);
        New.Langues = Uniqu_dig(New.Langues );
        did = 1;
        if ((New.Langues<=0) || ( New.Langues > 1234567 ) || ( Frequ_dig(New.Langues,8) != 0 ) || ( Frequ_dig(New.Langues,9) != 0 ) || ( Frequ_dig(New.Langues,0) != 0 ) || ( strlen(String) != Num_digits(New.Langues) ))
        {
            Go_up_Clear_line(2);
            goto Language;
        }
        Go_up_Clear_line(11);
        printf("\n\t\t> Langues exiges             : %s\n",Print_Languages(New.Langues));
        did = 0;

Dates:            
        
        printf("\n\t\tEntrez la date de debut de votre offre de Travail (jj-mm-aaaa) : ");
        Get_Date(0,New.Date_Publication,"\033[1;31m\t\t\tDate Erronee! Entrez un date valide !\033[0m\033[A\033[2K\r\t\tEntrez la date de debut de votre offre de Travail (jj-mm-aaaa) : ");

        Clear_line();

        printf("\n\t\tEntrez le delai d'envoi de la condidature (jj-mm-aaaa) : ");
        Get_Date(0,New.Delai_Condidature,"\033[1;31m\t\t\tDate Erronee! Entrez un date valide !\033[0m\033[A\033[2K\r\t\tEntrez le delai d'envoi de la condidature (jj-mm-aaaa) : ");

        Clear_line();
        if ( Compare_Dates( New.Date_Publication,New.Delai_Condidature ) != 1 )
        {
            Go_up_Clear_line (4);
            if ( did == 1 )
            {
                Go_up_Clear_line (2);    
            }
            Red();
            printf("\n\tLes dates que vous avez entre sont incoherent, veuillez les introduire une nouvelle fois :\n");
            Reset();
            if ( did == 0 )
            {
                did = 1;
            }
            goto Dates;        
        }
     

check_end:
            /* Affichage des informations pour les verifier */
        Clear_Screen();
        did = 0;
        printf("\t=== Vous etes entrain d'enregistrer une nouvelle annonce ===\n\n");
        printf("\n\t\t\t\tVoici Les informations de votre offre : \n\n");
        Print_Offre(New,0,0,NULL);
        printf("\n");



            
Error2:            
        /* verification des informations */
         if ( did == 0 )
        {
            printf("\tLes informations de votre offre sont-elles correctes ? Saisissez V pour Vrai et F pour Faux : ");
        }
        else
        {
            printf("\tLes informations de votre offre sont-elles correctes ? ");
            Red();
            printf("Saisissez V pour Vrai et F pour Faux : ");
            Reset();
        }       

        strcpy(ans,"");
        fgets(ans,40,stdin);
        Remove_Entree(ans);
        rep = toupper(ans[0]);
        did = 1;
        if ( (strlen(ans) != 1 ) || ((rep != 'V') && ( rep != 'F' )) ) 
        {
            Go_up(1);
            if ( strlen(ans) >18 ) 
            {
                Clear_line();
                Go_up(1);
            }
            Clear_line();
            goto Error2;
        }
        did = 0;
        if ( rep == 'F' )
        {
            int pr;
            printf("\n\t\tEntrez l'indexe du camp errone");
            printf("\n\t\t\t\t\t\t\tNom du poste ------------------- 1");
            printf("\n\t\t\t\t\t\t\tDiplome ------------------------ 2");
            printf("\n\t\t\t\t\t\t\tExperience --------------------- 3");
            printf("\n\t\t\t\t\t\t\tCompetences -------------------- 4");
            printf("\n\t\t\t\t\t\t\tLangues ------------------------ 5");
            printf("\n\t\t\t\t\t\t\tDate du debut de l'offre ------- 6");
            printf("\n\t\t\t\t\t\t\tDelai de condidature ----------- 7");
False:            
            if ( did == 0 )
            {
                printf("\n\t\t\t\t\t\t\t\tchoix : ");
            }
            else
            {
                Red();
                printf("\t\t\t\t\t\t\t\tchoix : ");
                Reset();
            }
            fgets(String,50,stdin);
            Remove_Entree(String);
            did = 1;
            sscanf(String,"%d",&pr);
            if ( (pr < 1 ) || ( pr > 7 ) || ( strlen(String) != 1  ) )
            {
                Go_up_Clear_line(1);
                goto False;
            }
            /* The choice he entered is true */
            did = 0;
            int print = 0;
            switch ( pr )
            {
            case 1 :
                Go_up(18+strlen(New.Liste_Competence));
                Clear_line();
Nom_poste_check:
                if ( did == 0 )
                {
                    printf("\t\t> Intitule du poste               : ");
                }
                else
                {
                    printf("\t\t> Intitule du poste               : ");
                    Red();
                    printf("\t\t\tNom du poste invalide");
                    Reset();
                    printf("\r\t\t\t\t\t\t  : ");
                }
                fgets(New.Nom_Poste,50,stdin);
                Remove_Entree(New.Nom_Poste);
                strcpy(New.Nom_Poste,Name(New.Nom_Poste));
                did = 1;
                if ( strlen( New.Nom_Poste ) < 5 )
                {
                    Go_up_Clear_line(1);
                    goto Nom_poste_check;
                }
                break;
            case 2 : 
Diplome_check:
                if ( print == 0 )
                {
                    Diploma Choix_Diplome [7];
                    Get_Diploma (Choix_Diplome);
                    Print_Diploma_Box(Choix_Diplome);
                    print = 1;
                    Cyan();
                    printf("\t\t\tEntrez l'indexe du diplome exige ( chiffre entre 1 et 7 ) : ");
                    Reset();
                }
                New.Diplome = 0;
                if ( did == 1 )
                {
                    Cyan();
                    printf("\t\t\tEntrez l'indexe du diplome exige ");
                    Red();
                    printf("( chiffre entre 1 et 7 ) : ");
                    Reset();
                }
                fgets(String,50,stdin);
                did = 1 ;
                sscanf(String,"%d",&New.Diplome);
                if ( ( New.Diplome>7 ) || ( New.Diplome<1 ) )
                {
                    Clear_line();
                    Go_up_Clear_line(1);
                    goto Diplome_check;
                }
                break;
            case 3 :  
                Go_up(16+strlen(New.Liste_Competence));
                Clear_line();
Exp_check:        
                if ( print == 1 )
                {
                    Red();
                    printf("\r\t\t\t\t\t\t\t\t ( Annees entre 0 et 40 )\r");
                    Reset();
                }
                if ( print == 0 )
                {
                    print = 1;
                }
                printf("\t\t> Annees d'experience requises    : ");
                strcpy(String,"");
                fgets(String,50,stdin);
                Remove_Entree(String);
                New.ExpYear = -1;
                sscanf(String,"%d",&New.ExpYear);
                if ( (strlen(String) > 2) || (New.ExpYear < 0) )
                {
                    // pas d'annees d'experience negative et logiquement pas plus de 40
                    Go_up_Clear_line(1);
                    goto Exp_check;
                }
                else
                {
                    if ( (strlen(String) == 2) && (( New.ExpYear <10 ) || (New.ExpYear > 40) ) )
                    {
                        Go_up_Clear_line(1);
                        goto Exp_check;
                    }
                }
                break;
            case 4 :
Compet_check:
                if ( print == 0 )
                {
                    Comptences Choix_competences [17];
                    Get_Competences ( Choix_competences );
                    Print_Competences_Box (Choix_competences);
                    print = 1;
                }
                strcpy(New.Liste_Competence,"");
                
                if ( did == 0 )
                {
                    Cyan();
                    printf("\t\tEntrez la combinaison des indexes des competences exiges ( entre 'a' et 'p' ou 'q' ) : ");
                    Reset();
                }
                else
                {
                    Cyan();
                    printf("\t\tEntrez la combinaison des indexes des competences exiges ");
                    Red();
                    printf("( entre 'a' et 'p' ou 'q' ) : ");
                    Reset();
                }
                int bool = 1;
                char Str_temp [50] = "";
                strcpy(String,"");
                fgets(String,50,stdin);
                Remove_Entree(String);
                Lower_str(String);
                strcpy(Str_temp,Uniqu_str ( String ));
                strcpy(New.Liste_Competence, Str_temp );
                did = 1;
                if ( strlen(String) != strlen(New.Liste_Competence) )
                {
                    bool = 0;
                }
                else
                {
                    if ( (strlen(New.Liste_Competence) <= 1) || ( strlen(String) != strlen(New.Liste_Competence) ) )
                    {
                        if ( (max_char(New.Liste_Competence) <= 'q') && (min_char(New.Liste_Competence)>='a' ) )
                        {
                            bool = 1;
                        }
                        else
                        {
                            bool = 0;
                        }
                    }
                    else if ( strlen( New.Liste_Competence ) > 1 )
                    {
                        if ( (strchr ( New.Liste_Competence , 'q' ) != NULL) || (max_char(New.Liste_Competence) > 'q') || (min_char(New.Liste_Competence)<'a' )  )
                        {
                            bool = 0;
                        }
                        else
                        {
                            bool = 1;
                        }
                    }
                }
                if ( bool == 0 )
                {
                    Go_up_Clear_line(1);
                    goto Compet_check;
                }
                
                break;
            case 5 :
Langue_check:
                if ( print == 0 )
                {
                    Langue Choix_Langue [7];
                    Get_Langue ( Choix_Langue );
                    Print_Languages_Box ( Choix_Langue );
                    print = 1;
                }
                New.Langues = 0;
                Cyan();
                printf("\n\t\tEntrez la combinaison des indexes des langues exigees ");
                Reset();
                if ( did == 0 )
                {
                    Cyan();
                    printf("( chiffres entre 1 et 7 ) : ");
                    Reset();
                }  
                else
                {
                    Red();
                    printf("( chiffres entre 1 et 7 ) : ");
                    Reset();
                }    
                fgets(String,50,stdin);
                Remove_Entree(String);
                sscanf(String,"%d",&New.Langues);
                New.Langues = Uniqu_dig(New.Langues );
                did = 1;
                if ((New.Langues<=0) || ( New.Langues > 1234567 ) || ( Frequ_dig(New.Langues,8) != 0 ) || ( Frequ_dig(New.Langues,9) != 0 ) || ( Frequ_dig(New.Langues,0) != 0 ) || ( strlen(String) != Num_digits(New.Langues) ))
                {
                    Go_up_Clear_line(2);
                    goto Langue_check;
                }
                break;
            case 6 :
                Go_up(14);
                did = 0;
check_date:
                Clear_line();
                if ( did == 0 )
                {
                    printf("\t\t> Date de publication de l'offre  : ");
                }
                else
                {
                    printf("\t\t> Date de publication de l'offre  :                           \033[1;31m( dates incoherentes )\033[0m\r\t\t\t\t\t\t  : ");
                }
                Get_Date(0,New.Date_Publication,"\033[A\033[2K\r\t\t> Date de publication de l'offre  : \t\t\t\033[1;31mDate invalide ( jj-mm-aaaa )\033[0m\r\t\t\t\t\t\t  : ");
                if ( Compare_Dates( New.Date_Publication , New.Delai_Condidature ) != 1 )
                {
                    Go_up(1);
                    did = 1;
                    goto check_date; 
                }
                break;
            case 7 :
                Go_up(13);
                did = 0;
check_delai:           
                Clear_line();
                if ( did == 0 )
                {
                    printf("\t\t> Delai de condidature            : ");
                }
                else
                {
                    printf("\t\t> Delai de condidature            :                           \033[1;31m( dates incoherentes )\033[0m\r\t\t\t\t\t\t  : ");
                }
                Get_Date(0,New.Delai_Condidature,"\033[A\033[2K\r\t\t> Delai de condidature            : \t\t\t\033[1;31mDate invalide ( jj-mm-aaaa )\033[0m\r\t\t\t\t\t\t  : ");
                if ( Compare_Dates( New.Date_Publication , New.Delai_Condidature ) != 1 )
                {
                    Go_up(1);
                    did = 1;
                    goto check_delai;
                }
                break;
            
            default:
                break;
            }
            goto check_end;

        }
    }
    New = De_Normalize_Off(New,1);
    if ( Find_offre( Liste_Off , New ) == NULL ) /* If the offer exists already, it will not */
    {
        Cyan();
        printf("\n\t\t\tEnregistrement de l'offre reussie !\n");    
        fflush(stdin);
        getch();
        Reset();
        Ptr_Maillon_Annonceur T;
        T = Find_Annonceur ( Liste_Ann , New.ID_rec );
        T->Info.Nbr_annonc += 1;    
    }
    else
    {
        Empty_Offre(&New);
        Cyan();
        printf("\n\t\tVotre Offre existe Deja ! Vous ne pouvez pas poster la meme offre deux fois !");
        fflush(stdin);
        getch();
        Reset();
    }
    
End:
    return New;
}

//_____________________________________________________________________________________________________________________