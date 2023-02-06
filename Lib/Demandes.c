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

//_____________________________________________________________________________________________________________________

/* La liste des Demandes est ordonnée par ordre croissant des ID des annonceurs  */

//_____________________________________________________________________________________________________________________

/* De_normalize : changes spaces to _ to store the data in the file */

Demande De_Normalize_Dem ( Demande Demande1 , int command )
{
    /*
    The role of this function is to :
    - if command == 1 : Replace every space with _ in a string
    - if command == 0 : Replace every _ with space in a string
    This is helpful when saving info in a file, cuz without it reading a file would be very challenging  
    */
   Demande Something = Demande1;
   strcpy(Something.Nom_Demandeur,Norm(Something.Nom_Demandeur,command));
   return Something;
}

/* Print_Demande : prints all the informatio of the demande */

void Print_Demande ( Demande Something , int command_ID )
{
    Demande Moded = De_Normalize_Dem(Something,0);
    if ( command_ID == 1 ) { printf("\t\t> ID                      : %d\n",Moded.ID); }
    printf("\t\t> Nom                     : %s\n",Moded.Nom_Demandeur);
    printf("\t\t> Diplome                 : %s\n",Print_Diploma(Moded.Diplome));
    if ( Moded.ExpYear == 0 )
    {
        printf("\t\t> Experience              : %d\n",Moded.ExpYear);
    }
    else
    {
        if ( Moded.ExpYear == 1 )
        {
            printf("\t\t> Experience              : %d an\n",Moded.ExpYear);
        }
        else
        {
            printf("\t\t> Experience              : %d ans\n",Moded.ExpYear);
        }
    }
        
    printf("\t\t> Competences acquises    : ");
    /* Start printing the competences one by one : to avoid printing half of it in a lin and the other half in the other half */    
    int i = 0;
    char Competences [ 500 ] = "";
    strcpy(Competences,Print_Competences(Moded.Liste_Competence));
    while( ( i<strlen( Competences ) ) && (Competences [i] != '\0') )
    {
        if ( strstr(Moded.Liste_Competence,"q") == NULL  )
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
            printf("\t\t\t\t\t    "); 
        }
    } 
    printf("\n");
    /* End printing the competences one by one */
    
    printf("\t\t> Langues maitrises       : %s\n",Print_Languages(Moded.Langues));
    printf("\t\t> Date de publication     : ");
    print_date(Moded.Date_Publication);
    printf("\n");
}

/* String_2_Demande : scans the information in a string " which is gonna be read from a file " and puts it in the demande */

Demande String_2_Demande ( char *info )
{
    Demande Something;
    sscanf(info,"%d %s %d %d %d %s %d %d %d",&Something.ID,Something.Nom_Demandeur,&Something.Diplome,&Something.ExpYear,&Something.Langues,Something.Liste_Competence,&Something.Date_Publication[0],&Something.Date_Publication[1],&Something.Date_Publication[2]);
    return Something;
}

/* Find_Demande : to look for an demande in the list : if he's there of not : returns the pointer to the maillons if he's there or NULL if he's not */

Ptr_Maillon_Annonce Find_Demande ( Ptr_Maillon_Annonce Head , int ID )
{
    Ptr_Maillon_Annonce Temp = Head;
    while ( (Temp != NULL) && ( Temp->Info.ID <= ID ) )
    {
        if ( Temp->Info.ID == ID )
        {
            return Temp;
        }
        Temp = Next_Annonce(Temp);
    }
    return NULL;
}

/* Liberer_Liste_Annonce : to free all the memory allocated for the lists at the end of the execution of the program */

void Liberer_Liste_Annonce ( Ptr_Maillon_Annonce *Head )
{
    /* Frees all the nodes of the list */
    Ptr_Maillon_Annonce Temp = *Head;
    Ptr_Maillon_Annonce Temp_Next;
    while ( Temp != NULL )
    {
        Temp_Next = Next_Annonce( Temp );
        Liberer_Annonce( Temp );
        Temp = Temp_Next;
    }
    *Head = NULL;
}

/* Add_Demande_Liste : Adds he demande in its place following the ID */

void Add_Demande_Liste ( Ptr_Maillon_Annonce *Head , Ptr_Maillon_Annonce Something )
{
    Ptr_Maillon_Annonce New = Allouer_Annonce();
    Aff_Demande_Info(New,Get_Demande_Maillon(Something));
    if ( *Head == NULL )
    {
        *Head = New;
    }
    else
    {
        Ptr_Maillon_Annonce Temp = *Head ;
        if ( (*Head)->Info.ID > Something->Info.ID )
        {
            Ptr_Maillon_Annonce Help = *Head ;
            *Head = New ;
            Aff_Demande_Next ( New , Help ) ;
        }
        else
        {
            Ptr_Maillon_Annonce Temp_pr = *Head;
            while ( (Temp != NULL) && ( Temp->Info.ID < New->Info.ID ) )
            {
                Temp_pr = Temp;
                Temp = Next_Annonce ( Temp );
            }
            Aff_Demande_Next(Temp_pr,New);
            Aff_Demande_Next(New,Temp);
        }
    }
}

/* Print_Liste_Demande : prints the list 2 by 2 */

void Print_Liste_Demande ( Ptr_Maillon_Annonce Head )
{
    Ptr_Maillon_Annonce Temp = Head;
    int i = 1;
    int done = 0;
    int test;
    if ( Head == NULL )
    {
        Cyan();
        printf("\n\tLa liste des Demandes est Vide ...");
        fflush(stdin);
        getch();
        Reset();
        return;
    }
    while ( (Temp != NULL) && ( done == 0 ) )
    {
        if ( i == 1 )
        {
            printf("\t\t\t== La %dere Demande ==\n",i);
        }
        else
        {
            printf("\n\t\t\t== La %deme Demande ==\n",i);
        }
        Print_Demande(Temp->Info,1);
        if ( (i%2) == 0 )
        {
            Cyan();
            printf("\n\t\tAppuyez sur une touche pour continuer L'affichage ou sur Echap pour quitter ... ");
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
        Temp = Next_Annonce(Temp);
        i++;
    }
    if ( Temp == NULL )
    {
        Cyan();
        printf("\n\tVous avez attient la fin de la liste des Demandes ...");
        fflush(stdin);
        getch();
        Reset();
    }
}

/* Read_Liste_Demande_file :  */

Ptr_Maillon_Annonce Read_Liste_Demande_file ( FILE *file_name )
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
        Ptr_Maillon_Annonce Head = Allouer_Annonce ();
        char Temp_str [350];    /* This is a temporary string which stores the value read from the the file */
        char Temp_str_pr [350]; /* This is a temporary string which stores the value read from the the file the last time, and it's here to chek if it's the same as the revious so it stops reading */
        fgets(Temp_str,350,file_name);
        Aff_Demande_Info(Head,String_2_Demande(Temp_str));
        Ptr_Maillon_Annonce Temp_ptr_pr = Head;
        fgets(Temp_str,350,file_name);
        while ( (strcmp(Temp_str,Temp_str_pr) != 0) &&  (Temp_str[0] != 2) && ( Temp_str[0] != 10 ) )
        {
            Ptr_Maillon_Annonce Temp_ptr = Allouer_Annonce () ;
            Aff_Demande_Info( Temp_ptr , String_2_Demande ( Temp_str ) );
            Aff_Demande_Next( Temp_ptr_pr , Temp_ptr );
            Temp_ptr_pr = Temp_ptr;
            strcpy(Temp_str_pr,Temp_str);
            fgets(Temp_str,350,file_name);
        }
        return Head;
    }
}

/* Demande_2_string : prints all the information of a Demande to a string to be printed to the file */

char *Demande_2_string ( Demande Demande1 )
{
    static char string_to_print[350];
    strcpy(string_to_print,"");
    sprintf(string_to_print,"%d %s %d %d %d %s %d %d %d\n",Demande1.ID,Demande1.Nom_Demandeur,Demande1.Diplome,Demande1.ExpYear,Demande1.Langues,Demande1.Liste_Competence,Demande1.Date_Publication[0],Demande1.Date_Publication[1],Demande1.Date_Publication[2]);
    return string_to_print;
}

/* print_Demande_file : prints the list to the file */

void print_Demande_file ( FILE *file_name , Ptr_Maillon_Annonce Head )
{
    Ptr_Maillon_Annonce Temp = Head;
    while ( Temp != NULL )
    {
        fprintf(file_name,Demande_2_string(Temp->Info));
        Temp = Next_Annonce(Temp);
    }
}

/* New_Demande : Reads new demande from the user */

Demande New_Demande ( Ptr_Maillon_Annonce Head )
{
    /* 
    - This function tells the user he's a member if we already have his info, but the handling of inserting it in the list will be done outside in the inserting module 
    - The goto labels are used to send him again to the specific information he entered wrong not to make him enter all his information again 
    - The ans string and rep char are the answers of the qestion : are your information correct
    - The integers did, done and problem are for printing in colorsand stuff...
    - The string problem_str and problem_int are the answers of the question : what is the wrong choice
    - The function returns the ID 0 if he's a member, or the real ID else
    */
    Demande New;
    char ans[50];
    char rep;
    int did = 0;
    int done = 0;

    Clear_Screen();  
    printf("\t\t\t=== Vous etes entrain de poster une nouvlle Demande d'emploi ===\n");
    printf("\n");
Check:
    if ( did == 0 )
    {
        printf("\t\tAvez vous deja poste une demande Demande d'emploi? Saisissez O pour Oui et N pour Non : ");
    }
    else
    {
        printf("\t\tAvez vous deja poste une demande Demande d'emploi? ");
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
        printf("\n\n\t\t\t  Vous ne pouvez pas pas poster plusieures fois ! ");
        printf("\n\n\t\t\tPensez a supprimer la premiere pour poster a nouveau ");
        fflush(stdin);
        getch();
        Reset();
        New.ID = 0 ;
        goto End;
    }
    else
    {
        char String [50];
        printf("\n");
Nom:
        printf("\t\t> Nom                     : ");
        fgets(New.Nom_Demandeur,49,stdin);
        strcpy(New.Nom_Demandeur,Name(New.Nom_Demandeur));
        Remove_Entree(New.Nom_Demandeur);
        did = 0;
        if ( strlen(New.Nom_Demandeur) <= 7 )
        {
            Go_up_Clear_line(1);
            Red();
            printf("\t\t\t\t\t\t\t\t\tNom trop court !\r");
            Reset();
            goto Nom;
        }
        if ( Find_Demande(Head,Nom_ID(New.Nom_Demandeur)) != NULL )
        {
            Clear_Screen();
            printf("\t\t\t=== Vous etes entrain de poster une nouvlle Demande d'emploi ===\n\n");
            Cyan();
            printf("\n\n\t\tVous avez deja poste une demande ! Vous ne pouvez pas poster plusieurs fois ! ");
            printf("\n\n\t\t            Pensez a supprimer la premiere pour poster a nouveau ");
            Reset();
            New.ID = 0;
            goto End;
        }
        if ( done == 1 )
        {
            goto check_end;
        }
        did = 0 ;
Diplome:
        if ( did == 0 )
        {
            Diploma Choix_Diplome [7];
            Get_Diploma (Choix_Diplome);
            Print_Diploma_Box(Choix_Diplome);
        }
        printf("\n\t\tEntrez l'indexe du diplome acquis ");
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
        printf("\t\t> Diplome acquis          : %s\n",Print_Diploma(New.Diplome));
        printf("\n");
        did = 0; 
Exp:
        if ( done == 0 )
        {
            printf("\t\tCombien d'annees d'experience avez vous dans le domaine  : ");
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
        }
        else
        {
            printf("\t\t> Experience              : ");
            if ( did != 0 )
            {
                Red();
                printf("\t\t\t( entre 0 an et 40 ans )");
                Reset();
                printf("\r\t\t\t\t\t  : ");
            }
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
            else
            {
                if ( (String[0]<'0') || (String[0]>'9') )
                {
                    Go_up_Clear_line(1);
                    goto Exp;
                }
            }
        }
    
        Go_up_Clear_line(1);

        if ( New.ExpYear == 0 )
        {
            printf("\t\t> Experience               : %d\n", New.ExpYear );
        }
        else if (New.ExpYear == 1)
        {
            printf("\t\t> Experience                : %d an\n", New.ExpYear );
        }
        else
        {
            printf("\t\t> Experience              : %d ans\n", New.ExpYear );
        
        }                                      
        did = 0 ;
        if ( done == 1 )
        {
            goto check_end;
        }
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

        printf("\t\t> competences maitrisees  : ");
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
                printf("\t\t\t\t\t    "); 
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
        printf("\n\t\tEntrez la combinaison des indexes des langues maitrisees ");
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
        printf("\n\t\t> Langues maitrisees      : %s\n",Print_Languages(New.Langues));
        did = 0;
Dates:            
        if ( done == 0 )
        {
            printf("\n\t\tEntrez la date de debut de votre demande (jj-mm-aaaa) : ");
            Get_Date(0,New.Date_Publication,"\033[1;31m\t\t\tDate Erronee! Entrez un date valide !\033[0m\033[A\033[2K\r\t\tEntrez la date de debut de votre demande (jj-mm-aaaa) : ");
        }
        else
        {
            Clear_line();
            printf("\t\t> Date de publication     : ");
            Get_Date(0,New.Date_Publication,"\033[A\033[2K\t\t> Date de publication     : \t\t\t\t\033[1;31mEntrez un date valide ! (jj-mm-aaaa)\033[0m\r\t\t> Date de publication     : ");
        }
        
        done = 1;

check_end:

            /* Affichage des informations pour les verifier */
        Clear_Screen();
        did = 0;
        printf("\t\t=== Vous etes entrain de poster une nouvlle Demande d'emploi ===\n");
        printf("\n\t\t\t\tVoici Les informations de votre demande : \n\n");
        Print_Demande(New,0);
        printf("\n");

            
Error2:            
        /* verification des informations */
         if ( did == 0 )
        {
            printf("\tLes informations de votre demande sont-elles correctes ? Saisissez V pour Vrai et F pour Faux : ");
        }
        else
        {
            printf("\tLes informations de votre demande sont-elles correctes ? ");
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
            int pr ;
            printf("\n\t\tEntrez l'indexe du camp errone");
            printf("\n\t\t\t\t\t\t\tNom ---------------------------- 1");
            printf("\n\t\t\t\t\t\t\tDiplome ------------------------ 2");
            printf("\n\t\t\t\t\t\t\tExperience --------------------- 3");
            printf("\n\t\t\t\t\t\t\tCompetences -------------------- 4");
            printf("\n\t\t\t\t\t\t\tLangues ------------------------ 5");
            printf("\n\t\t\t\t\t\t\tDate de publication ------------ 6");
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
            pr = 0;
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
            switch (pr)
            {
            case 1:  // done
                Go_up(16+strlen(New.Liste_Competence));
                Clear_line();
                goto Nom;
                break;
            case 2: //done
Diplome_check:
                if ( did == 0 )
                {
                    Diploma Choix_Diplome [7];
                    Get_Diploma (Choix_Diplome);
                    Print_Diploma_Box(Choix_Diplome);
                }
                printf("\n\t\tEntrez l'indexe du diplome acquis ");
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
                    goto Diplome_check;
                }
                break;
            case 3:  // done
                Go_up(14+strlen(New.Liste_Competence));
                New.ExpYear = -1;
                Clear_line();
                goto Exp;
                break;
            case 4:
Compet_check:
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
                    goto Compet_check;
                }

                break;
            case 5: //done
check_langue:
                if ( did == 0 )
                {
                    Langue Choix_Langue [7];
                    Get_Langue ( Choix_Langue );
                    Print_Languages_Box ( Choix_Langue );
                }
                printf("\n\t\tEntrez la combinaison des indexes des langues maitrisees ");
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
                New.Langues = 0 ; 
                strcpy(String,"");
                fgets(String,50,stdin);
                Remove_Entree(String);
                sscanf(String,"%d",&New.Langues);
                New.Langues = Uniqu_dig(New.Langues );
                did = 1;
                if ((New.Langues<=0) || ( New.Langues > 1234567 ) || ( Frequ_dig(New.Langues,8) != 0 ) || ( Frequ_dig(New.Langues,9) != 0 ) || ( Frequ_dig(New.Langues,0) != 0 ) || ( strlen(String) != Num_digits(New.Langues) ))
                {
                    Go_up_Clear_line(2);
                    goto check_langue;
                }
                break;
            case 6: //done
                Go_up(12);
                Clear_line();
                goto Dates;
                break;
            
            default:
                break;
            }
            goto check_end;
        }
        Cyan();
        printf("\n\t\t\tEnregistrement de la demande est termine avec succes !");
        fflush(stdin);
        getch();
        Reset();
        New.ID = Nom_ID(New.Nom_Demandeur);
        New = De_Normalize_Dem ( New , 1 );
    }
End:
    return New;   
}

//_____________________________________________________________________________________________________________________