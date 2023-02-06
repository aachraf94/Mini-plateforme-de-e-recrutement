#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include "Display.h"
#include "EMPLOI_LLC_BIBLIO.h"
#include "Basic_Functions.h"
#include "Annonceurs.h"

//_____________________________________________________________________________________________________________________

/* La liste des Annonceurs est ordonnée par ordre croissant des IDs des annonceurs  */

//_____________________________________________________________________________________________________________________

/* De_normalize : changes spaces to _ to store the data in the file */

Annonceur De_Normalize_Ann ( Annonceur Personne , int command )
{
    /*
    The role of this function is to :
    - if command == 1 : Replace every space with _ in a string
    - if command == 0 : Replace every _ with space in a string
    This is helpful when saving info in a file, cuz without it reading a file would be very challenging  
    */
    Annonceur Someone = Personne;
    strcpy ( Someone.Nom , Norm(Personne.Nom,command) );
    strcpy ( Someone.Adresse , Norm(Personne.Adresse,command) );
    strcpy ( Someone.Num_Tel , Norm(Personne.Num_Tel,command) );
    return Someone;
}

/* Print_Annonceur : prints the information on an Annonceur */

void Print_Annonceur ( Annonceur Personne , int command_id , int command_nbr_annonces)
{
    /*
    The commands are for:
    -   command ID : to print id or not
    -   command nbr_annonces : to print nombre d'annonces or not
    */
    Annonceur Personne_moded;
    Personne_moded = De_Normalize_Ann ( Personne , 0 );
    if (command_id == 1) {printf("\t\t> ID                  : %d\n",Personne_moded.ID);}
    printf("\t\t> Nom                 : %s\n",Personne_moded.Nom);
    printf("\t\t> Adresse             : %s\n",Personne_moded.Adresse);
    printf("\t\t> Mail Professionnel  : %s\n",Personne_moded.Mail);
    printf("\t\t> Numero de Telephone : %s\n",Personne_moded.Num_Tel);
    if (command_nbr_annonces == 1) {printf("\t\t> Nombre d'Annonces   : %d\n",Personne_moded.Nbr_annonc);}
}

/* String_2_Annonceur : scans the information in a string " which is gonna be read from a file " and puts it in the annonceur */

Annonceur String_2_Annonceur ( char *info ) 
{
    Annonceur Guy;
    sscanf(info,"%i %s %s %s %s %i",&Guy.ID,Guy.Nom,Guy.Adresse,Guy.Mail,Guy.Num_Tel,&Guy.Nbr_annonc);
    return Guy;
}

/* Find_Annonceur : to look for an annonceur in the list : if he's there of not : returns the pointer to the maillons if he's there or NULL if he's not */

Ptr_Maillon_Annonceur Find_Annonceur ( Ptr_Maillon_Annonceur Head , int ID )
{
    Ptr_Maillon_Annonceur Temp = Head ;
    while ( (Temp != NULL) && ( Temp->Info.ID <=ID ) )
    {
        if ( Temp->Info.ID == ID )
        {
            return Temp;
        }
        Temp = Next_Annonceur ( Temp );
    }
    return 0;
}

/* Liberer_Liste_Annonceur : to fre all the memory allocated for the lists at the end of the execution of the program */

void Liberer_Liste_Annonceur ( Ptr_Maillon_Annonceur *Head )
{
    /* Frees all the nodes of the list */
    Ptr_Maillon_Annonceur Temp = *Head;
    Ptr_Maillon_Annonceur Temp_Next;
    while ( Temp != NULL )
    {
        Temp_Next = Next_Annonceur( Temp );
        Liberer_Annonceur( Temp );
        Temp = Temp_Next;
    }
    *Head = NULL;
}

/* Add_Annonceur_Liste : Adds the Annonceur to the list following the order of the ID */

void Add_Annonceur_Liste ( Ptr_Maillon_Annonceur *Head , Ptr_Maillon_Annonceur Guy )
{
    Ptr_Maillon_Annonceur Tempyy = Allouer_Annonceur();
    Aff_Annonceur_Info(Tempyy,Get_Annonceur_Maillon(Guy));
    if ( *Head == NULL )
    {
        *Head = Tempyy;
    }
    else
    {
        if ( (*Head)->Info.ID > Guy->Info.ID )
        {
            Ptr_Maillon_Annonceur Help = *Head ;
            *Head = Tempyy;
            Aff_Annonceur_Next(Tempyy,Help);
        }
        else
        {
            Ptr_Maillon_Annonceur Temp = *Head;
            int ID = Guy->Info.ID;
            int bool = 0;
            Ptr_Maillon_Annonceur Temp_Pr ;
            while ( ( Temp != NULL ) && ( bool == 0 ) )
            {
                if ( ( Temp->Info.ID > ID) )
                {
                    bool = 1;
                }
                else
                {
                    Temp_Pr = Temp;
                    Temp = Next_Annonceur ( Temp );
                }
            }
            Aff_Annonceur_Next( Temp_Pr , Tempyy );
            Aff_Annonceur_Next( Tempyy , Temp );
        }
    }
}

/* Print_Liste_Annonceurs : Prints the list 4 by 4 */

void print_Liste_Annonceurs ( Ptr_Maillon_Annonceur Head )
{
    if ( Head == NULL )
    {
        Cyan();
        printf("\n\tLa liste des Annonceurs est Vide ...");
        fflush(stdin);
        getch();
        Reset();
        return;
    }
    Ptr_Maillon_Annonceur Temp = Head;
    int i = 1 ;
    int done = 0;
    char test;
    while ( (Temp != NULL) && ( done == 0 ) )
    {
        if ( i == 1 )
        {
            printf("\t\t\t== Le %der Annonceur ==\n",i);
        }
        else
        {
            printf("\t\t\t== Le %deme Annonceur ==\n",i);
        }
        Print_Annonceur(Temp->Info,1,1);
        printf("\n");
        if ( (i%4) == 0 )
        {
            Cyan();
            printf("\t\tAppuyez sur une touche pour continuer L'affichage ou sur Echap pour quitter ... ");
            fflush(stdin);
            test = getch();
            Reset();
            if ( test == 27 )
            {
                done = 1;
                printf("\n");
            }
            if ( done != 1 )
            {
                Clear_Screen();
            }
        }
        i++;
        Temp = Next_Annonceur (Temp);
    }
    if ( Temp == NULL )
    {
        Cyan();
        printf("\n\tVous avez attient la fin de la liste de Annonceurs ...");
        fflush(stdin);
        getch();
        Reset();
    }
}

/* Read_Liste_Annonceur_file : Reads from the file the list of Annonceurs and returns the head of the list */

Ptr_Maillon_Annonceur Read_Liste_Annonceur_file ( FILE *file_name )
{
    /*
    The if checks if the file is empty, if it is it returns NULL, else it reads it
    Stoping Criteria of the loop :
        -   the string read from the file in the 'n'th time is equal to the string read from the file the 'n-1'th time : Main Stopping criteria
        -   the first character of the string is equal to :
            * start of the text : ascii code 2
            * line feef : ascii code 10
    */
    long size;
    fseek(file_name,0,SEEK_END);  /* check if the end IS the start so the file is empty */
    size = ftell (file_name);
    if ( size == 0 )
    {
        return NULL;
    }
    else
    {
        fseek(file_name,0,SEEK_SET);  /* go back to the start cuz we went to theend at first to check if the file is empty */
        Ptr_Maillon_Annonceur Head = Allouer_Annonceur () ;
        char Temp_str [350];    /* This is a temporary string which stores the value read from the the file */
        char Temp_str_pr [350]; /* This is a temporary string which stores the value read from the the file the last time, and it's here to chek if it's the same as the revious so it stops reading */
        fgets(Temp_str,350,file_name);
        Aff_Annonceur_Info ( Head , String_2_Annonceur ( Temp_str ) );
        Ptr_Maillon_Annonceur Temp_ptr_pr = Head;
        fgets(Temp_str,350,file_name);
        while ( (strcmp(Temp_str,Temp_str_pr) != 0) &&  (Temp_str[0] != 2) && ( Temp_str[0] != 10 ) )
        {
            Ptr_Maillon_Annonceur Temp_ptr = Allouer_Annonceur () ;
            Aff_Annonceur_Info( Temp_ptr , String_2_Annonceur ( Temp_str ) );
            Aff_Annonceur_Next( Temp_ptr_pr , Temp_ptr );
            Temp_ptr_pr = Temp_ptr;
            strcpy(Temp_str_pr,Temp_str);
            fgets(Temp_str,350,file_name);
        }
        return Head;
    }
}

/* Annonceur_2_String : prints all the information of an Annonceur to a string to be printed to the file */

char *Annonceur_2_String ( Annonceur Guy )
{
    static char string_to_print[350];
    strcpy(string_to_print,"");
    sprintf(string_to_print,"%d %s %s %s %s %d\n",Guy.ID,Guy.Nom,Guy.Adresse,Guy.Mail,Guy.Num_Tel,Guy.Nbr_annonc);
    return string_to_print;
}

/* Print_Annonceurs_file : prints the list to the file */

void Print_Annonceurs_file ( FILE *file_name , Ptr_Maillon_Annonceur Head )
{
    Ptr_Maillon_Annonceur Temp = Head ;
    while ( Temp != NULL )
    {
        fprintf(file_name,Annonceur_2_String(Temp->Info));
        Temp = Next_Annonceur(Temp);
    }
}

/* New_Annonceur : gets new annonceur */

Annonceur New_Annonceur ( Ptr_Maillon_Annonceur Head )
{
    /* 
    - This function tells the user he's a member if we already have his info, but the handling of inserting it in the list will be done outside in the inserting module 
    - The goto labels are used to send him again to the specific information he entered wrong not to make him enter all his information again 
    - The ans string and rep char are the answers of the qestion : are your information correct
    - The integers did, done and problem are for printing in colorsand stuff...
    - The string problem_str and problem_int are the answers of the question : what is the wrong choice
    - The function returns the ID 0 if he's a member, or the real ID else
    */
    Annonceur New;
    char ans[50];
    char rep;
    int did = 0;
    int done = 0;
    
    Clear_Screen();  
    printf("\t=== Vous etes entrain de vous inscrire en tant que nouveau annonceur ===");
    printf("\n");
Check:
    if ( did == 0 )
    {
        printf("\t\tEtes vous deja un de nos Annonceurs? Saisissez O pour Oui et N pour Non : ");
    }
    else
    {
        printf("\t\tEtes vous deja un de nos Annonceurs? ");
        Red();
        printf("Saisissez O pour Oui et N pour Non : ");
        Reset();
    }
    fgets(ans,50,stdin);
    Remove_Entree(ans);
    did = 1;
    rep = toupper(ans[0]);
    if ( (( rep != 'N' ) && ( rep != 'O' )) || ( ans[1] != 0 ) )
    {
        Go_up_Clear_line(1);
        if ( strlen(ans) > 29 ) 
        {
            Go_up_Clear_line(1);
        }
        goto Check;
    }
    if ( rep == 'O' )
    {
        Cyan();
        printf("\n\n\t\t\tVous ne pouvez pas vous inscrire plusieures fois ! \n");
        fflush(stdin);
        getch();
        Reset();
        New.ID = 0 ;
        goto End;
    }
    else
    {
Nom:
        printf("\t\t> Nom                 : ");
        fgets(New.Nom,49,stdin);
        strcpy(New.Nom,Name(New.Nom));
        Remove_Entree(New.Nom);
        did = 0;
        if ( strlen(New.Nom) <= 7 )
        {
            Go_up_Clear_line(1);
            Red();
            printf("\t\t\t\t\t\t\t\t\tNom trop court !\r");
            Reset();
            goto Nom;
        }
        if ( Find_Annonceur(Head,Nom_ID(New.Nom)) != NULL )
        {
            Clear_Screen();
            printf("\t=== Vous etes entrain de vous inscrire en tant que nouveau annonceur ===\n\n");
            Cyan();
            printf("\n\n\t\tVous etes deja inscrits ! Vous ne pouvez pas vous insrire plusieurs fois ! ");
            fflush(stdin);
            getch();
            Reset();
            New.ID = 0;
            goto End;
        }
        if ( done == 1 )
        {
            goto Check_End;
        }    
Adresse:
        printf("\t\t> Adresse             : ");
        fgets(New.Adresse,199,stdin); // pas d'adresse vide
        strcpy(New.Adresse,Name(New.Adresse));
        Remove_Entree(New.Adresse);
        did = 0;
        if ( strlen(New.Adresse) <=15 )
        {
            Go_up_Clear_line(1);
            Red();
            printf("\t\t\t\t\t\t\t\t\tAdresse trop courte\r");
            Reset();
            goto Adresse;
        }
        if ( done == 1 )
        {
            goto Check_End;
        }
Mail:
        printf("\t\t> Mail Professionnel  : ");
        fgets(New.Mail,49,stdin);
        Remove_Entree(New.Mail);
        did = 0;
        if ( Check_Mail( New.Mail ) != 1 )
        {
            Go_up_Clear_line(1);
            Red();
            printf("\t\t\t\t\t\t\t\t\tMail Invalide\r");
            Reset();
            goto Mail;
        }

        if ( done == 1 )
        {
            goto Check_End;
        }
    
Num_Tel:
        printf("\t\t> Numero de Telephone : ");
        fgets(New.Num_Tel,20,stdin);
        Remove_Entree(New.Num_Tel);
        if ( ( min_char(New.Num_Tel) < 32 ) || ( max_char(New.Num_Tel) > '9' ) )
        {
            Go_up_Clear_line(1);
            Red();
            printf("\t\t\t\t\t\t\t\t\tNumero de Telephone Invalide\r");
            Reset();
            goto Num_Tel;
            //printf("")
        }
        did = 0;
        if ( done == 1 )
        {
            goto Check_End;
        }
    
        New.Nbr_annonc = 0;
Check_End:
        Clear_Screen();
        /* Affichage des informations pour les verifier */
        Clear_Screen();
        printf("\t=== Vous etes entrain de vous inscrire en tant que nouveau annonceur ===\n");
        printf("\t\t\t\tVoici Vos informations : \n");
        Print_Annonceur(New,0,0);
        printf("\n");

Error:   
        /* verification des informations */
        if ( did == 0 )
        {
            printf("\r\tVos informations sont-elles correctes ? Saisissez V pour Vrai et F pour Faux : ");
        }
        else
        {
            printf("\r\tVos informations sont-elles correctes ? ");
            Red();
            printf("Saisissez V pour Vrai et F pour Faux : ");
            Reset();

        }
        if ( did == 0 )
        {
            did = 1;
        }
        fgets(ans,50,stdin);
        rep = toupper(ans[0]);
        Remove_Entree(ans);
        if ( (( rep != 'V' ) && ( rep != 'F' )) || ( ans[1] != 0 ) ) 
        {
            Go_up_Clear_line(1);
            if ( strlen(ans) > 32 )
            {
                Go_up_Clear_line(1);
            }
            goto Error;
        }
        done = 1;
        if ( rep == 'F' )
        {
            char problem_str [50];
            int problem_int;
            int problem = 0;
            printf("\n\t\tEntrez l'indexe du champ errone : ");
            printf("\n\t\t\t\t\t\t\tNom ------------------- 1");
            printf("\n\t\t\t\t\t\t\tAdresse --------------- 2");
            printf("\n\t\t\t\t\t\t\tMail ------------------ 3");
            printf("\n\t\t\t\t\t\t\tNumero de Telephone --- 4");
Problem:            
            if ( problem == 0 )
            {
                printf("\n\t\t\t\t\t\t\t\tChoix : ");
            }
            else
            {
                Red();
                printf("\t\t\t\t\t\t\t\tChoix : ");
                Reset();
            }
            fgets(problem_str,50,stdin);
            Remove_Entree(problem_str);
            problem_int = 0;
            sscanf(problem_str,"%d",&problem_int);
            if ( strlen(problem_str) != 1 )
            {
                problem_int = 0;
            }
            switch (problem_int)
            {
            case 1 :
                Go_up(13);
                Clear_line();
                goto Nom;
                break;
            case 2 :
                Go_up(12);
                Clear_line();
                goto Adresse;
                break;
            case 3 :
                Go_up(11);
                Clear_line();
                goto Mail;
                break;
            case 4 :
                Go_up(10);
                Clear_line();
                goto Num_Tel;
                break;
            default:
                problem = 1;
                Go_up_Clear_line(1);
                goto Problem;
                break;
            }

        }
        New.ID = Nom_ID(New.Nom);
        New = De_Normalize_Ann ( New , 1 );
        Cyan();
        printf("\n\t\t\t\tEnregistrement reussi, Bienvenue !\n");
        fflush(stdin);
        getch();
        Reset();
    }
End:
    return New; 
}     

//_____________________________________________________________________________________________________________________