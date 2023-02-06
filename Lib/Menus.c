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
#include "Menus.h"

//_____________________________________________________________________________________________________________________

void BYE_BYE ( void )
{
    Clear_Screen();
    printf("\n");
    Green();
    printf("    _______________________________________________________________________________________________________________\n");
    printf("   /                                                                                                               \\\n");
    printf("  /                                                                                                                 \\\n");
    printf(" |___________________________________________________________________________________________________________________|\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |                                                                                                                   |\n");
    printf(" |___________________________________________________________________________________________________________________|\n");
    Go_up(13);
    Cyan();
    printf("\t\t\t\t\t   ");
    Animate_str("===== FIN DU PROGRAMME - Merci =====",0);
    printf("\n\n\n");
    printf("\t\t\t");
    Animate_str("Si vous rencontrez une erreur quelconque, n'hesitez pas a nous la signaler :",0);
    printf("\n\n");
    printf("\t\t\t\t");
    Animate_str("Merhab Abderraouf     : la_merhab@esi.dz",0);
    printf("\n\n");
    printf("\t\t\t\t");
    Animate_str("Abdelkebir Achraf     : la_abdelkebir@esi.dz",0);
    printf("\n\n\n");
    Green();
    printf("\t\t\t\t\t");
    Animate_str("Appuyez sur une touche pour quitter ...",0);
    fflush(stdin);
    getch();
}

int Verify_changes( void )
{
    Clear_Screen();
    Cyan();
    printf("                                           ___________________________________\n");
    printf("                                          /                                   \\\n");
    printf("                                          |                                   |\n");
    printf("   _______________________________________|___________________________________|______________________________________\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |                                                                                                                |\n");
    printf("   |________________________________________________________________________________________________________________|\n");
    Go_up(18);
    printf("\t\t\t\t\t\t     ");
    Animate_str("Verification ...",0);
    printf("\n\n\n\n");
    printf("\t\t\t");
    Red();
    Animate_str("> Tous les Annonceurs qui n'ont pas d'offres vont etre supprimes",0);
    printf("\n\n\n\t\t\t    ");
    Animate_str("> Toutes les Offres sans annonceur vont etre supprimes",0);
    Cyan();
    printf("\n\n\n");
    int did = 0;
    char ans[70];
    char rep;
Error:
    if ( did == 0 )
    {        
        printf("\t");
        Animate_str("Voulez vous enregistrer les modifications apportees dans les fichiers ?",0);
        sleep(1);
        printf("\n\n\t\t\t\t\t\t\t\t ");
        Animate_str("Saisissez O pour Oui et N pour Non : ",0);
    }
    else
    {
        Cyan();
        printf("   |                                                                                                                |");
        Red();
        printf("\r\t\t\t\t\t\t\t\t ");
        printf("Saisissez O pour Oui et N pour Non : ");
        Reset();
    } 
    strcpy(ans,"");
    fflush(stdin);
    fgets(ans,70,stdin);
    fflush(stdin);
    Remove_Entree(ans);
    rep = toupper(ans[0]);
    did = 1;
    if ( (strlen(ans) != 1 ) || ((rep != 'O') && ( rep != 'N' )) ) 
    {  
        Go_up(1);
        if ( strlen(ans) > 17 ) 
        {
            Clear_line();
            Cyan();
            printf("\r   |                                                                                                                |\n");
            Reset();
            Go_up(2);
        }
        Clear_line();
        goto Error;
    }
    if ( rep == 'O' )
    {
        Cyan();
        printf("\n");
        printf("\n\t\t\t________________________________________\r");
        for ( int i = 0 ; i<=200 ; i+=10 )
        {
            printf("\t\t\t\t\t\t\t\t\t%d%c   Chargement\r",i/2,'%');
            printf("\t\t\t");
            for ( int j = 0 ; j <= i/5 ; j++ )
            {
                printf("#");
            }
            usleep(300000);
            printf("\r");
        }
        Clear_line;
        printf("\t\t\t#########################################       100%c   ",'%');
        Animate_str("Enregistrement reussi ...",0);
        Reset();
        sleep(3);
        return 1;
    }    
    else
    {
        return 0;
    }
}

void First_Interface ( void )
{
    Clear_Screen();
    Cyan();
    printf(" _____________________________________________________________________________________________________________________\n");
    usleep(40000);
    for ( int i = 1 ; i<=23 ; i++ )
    {
        printf(" |                                                                                                                   |\n");
        usleep(40000);
    }
    printf(" |___________________________________________________________________________________________________________________|\n");
    usleep(40000);
    Go_up(23);
    printf("\t\t\t           ");
    Animate_str("================== [ Welcome ] ==================\n\n",30000);
    Blue();
    printf("\t\t\t\t      ##########       ##########     ###########\n");usleep(40000);
    printf("\t\t\t\t      #               #                    #\n");    usleep(40000);
    printf("\t\t\t\t      #               #                    #\n");    usleep(40000);
    printf("\t\t\t\t      ##########       #########           #\n");    usleep(40000);
    printf("\t\t\t\t      #                         #          #\n");    usleep(40000);
    printf("\t\t\t\t      #                         #          #\n");    usleep(40000);
    printf("\t\t\t\t      ##########      ##########      ###########\n\n");usleep(40000);
    Reset();
    printf("\t\t\t\t     ");
    Animate_str("TP1 ALSDD : Mini plateforme de e-recrutement",30000);
    printf("\n\n");
    printf("\t\t\t");
    Animate_str("Nom :",0);
    printf("\n");
    printf("\t\t\t");
    Animate_str("Prenom :",0);
    printf("\n");
    Go_up(2);
    printf("\t\t\t\t\t\t");
    Animate_str("Merhab",0);
    printf("\n");
    printf("\t\t\t\t\t      ");
    Animate_str("Abderraouf",0);
    printf("\n");
    Go_up(2);
    printf("\t\t\t\t\t\t\t\t\t      ");
    Animate_str("Abdelkebir",0);
    printf("\n");
    printf("\t\t\t\t\t\t\t\t\t\t");
    Animate_str("Achraf",0);
    printf("\n\n");
    printf("\t\t\t\t"); 
    Animate_str("Groupe :",0);
    printf("               ");
    Animate_str("1CPI  A-02",0);
    printf("\n\n");
    printf("\t\t\t\t    ");
    Animate_str("Sous la supervisation de Madame TEMGLIT Nacera",0);
    printf("\n\n");
    printf("\t\t\t\t   ");
    Cyan();
    Animate_str("=================================================",30000);
    printf("\n\n\t\t\t\t\t");
    Blue();
    Animate_str("Appuyer sur une touche pour continuer ...",0);
    Reset();
    fflush(stdin);
    getch();
}

void Disclaimer_Page ( void )
{
    Clear_Screen();
    Red();
    printf("\n");
    printf("\t########################################################################################################\n");
    printf("\t########################################################################################################\n");
    for ( int i = 1 ; i<=27 ; i++ )
    {
        printf("\t##\t\t\t\t\t\t\t\t\t\t\t\t      ##\n");
        usleep(10000);
    }
    printf("\t########################################################################################################\n");
    printf("\t########################################################################################################\r");
    Go_up(26);
    printf("\t\t\t\t\t\t            *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t           * *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t          *   *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t         *  #  *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t        *   #   *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t       *    #    *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t      *     #     *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t     *      #      *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t    *       @       *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t   *                 *");printf("\n");usleep(20000);
    printf("\t\t\t\t\t\t  * * * * * * * * * * *");printf("\n\n");usleep(20000);
    
    printf("\t\t\t\t\t\t");
    Animate_str("      ATTENTION !!! ",0);
    Reset();
    printf("\n\n\n\t\t\t    ");
    Animate_str("** Veuillez ne pas interrompre l'execution du programme **",0);
    printf("\n\n\t\t\t          ");
    Animate_str("tout progres ne sera pas enegistre dans ce cas",0);
    Cyan();
    printf("\n\n\n\n\n\n\t\t\t\t\t");    
    Animate_str("Appuyez sur une touche pour continuer...",0);
    Reset();
    fflush(stdin);
    getch();
}

int Principal_Menu( void )
{
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t\t");
    Animate_str("=== Bienvenue ===",0);
    printf("\n\n\n");
    printf("\t_________________________________________________________________________________________________________");
    printf("\n");
    for ( int i = 1 ; i < 12 ; i++ )
    {
        printf("\t|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        usleep(40000);
    }
    printf("\t|_______________________________________________________________________________________________________|");
    Reset();
    printf("\n");
    Go_up(12);
    int did = 0;
Here:
    if ( did == 0 )
    {
        printf("\n\t\t\t");
        Animate_str("Vous etes ( 1 / 2 / 3 ) : ",0);
        printf("\n");
        printf("\n\n\t\t\t\t\t\t\t");
        Animate_str("1 --- Annonceur",0);
        printf("\n\n\t\t\t\t\t\t\t");
        Animate_str("2 --- Demandeur",0);
        printf("\n\n\t\t\t\t\t\t\t");
        Animate_str("3 --- developpeur",0); 
        Go_up(7);   
        Clear_line();
        Cyan();
        printf("\r\t|\t\t\t\t\t\t\t\t\t\t\t\t\t|\r");
        Reset();
        printf("\t\t\tVous etes ( 1 / 2 / 3 ) : ");
    }
    else
    {
        Cyan();
        printf("\t|\t\t\t\t\t\t\t\t\t\t\t\t\t|\r");
        Reset();
        printf("\t\t\tVous etes ");
        Red();
        printf("( 1 / 2 / 3 ) : ");
        Reset();
    }
    char Ans[100];
    char rep;
    fgets(Ans,100,stdin);
    Remove_Entree(Ans);
    did = 1 ;
    rep = toupper ( Ans[0] );
    if ( (strlen(Ans) != 1) || ( (rep != '1') && (rep != '2') && (rep != '3') ) )
    {
        Go_up_Clear_line(1);
        goto Here;
    }
    return atoi(Ans);
}

int Menu_Annonceur ( void )
{
    Clear_Screen();
    printf("\t\t\t\t\t ");
    Cyan();
    Animate_str("=== Vous etes un Annonceur ===",0);
    printf("\n\n\n");
    printf("\t__________________________________________________________________________________________________");
    for ( int i = 1 ; i<=8 ; i++ )
    {
        printf("\n\t|                                                                                                |");
        usleep(30000);
    }
    printf("\n\t|________________________________________________________________________________________________|");usleep(30000);
    printf("\n\t\t\t|                                     |");usleep(30000);
    printf("\n\t\t\t|                                     |");usleep(30000);
    printf("\n\t\t\t|_____________________________________|");usleep(30000);
    Reset();
    Go_up(11);
    printf("\n\t\t ");
    Animate_str("1 --- Vous enregistrer en tant que nouvel Annonceur",0);
    printf("\n\t\t ");
    Animate_str("2 --- Enregistrer une nouvelle Offre",0);
    printf("\n\t\t ");
    Animate_str("3 --- Afficher toutes les Demandes d'Emploi",0);
    printf("\n\t\t ");
    Animate_str("4 --- Supprimer une de mes offres",0);
    printf("\n\t\t ");
    Animate_str("5 --- Supprimer mon compte",0);
    printf("\n\t\t ");
    Animate_str("6 --- Quitter",0);
    printf("\n\n\n\n");
    int did = 0;
Here:
    if ( did == 0 )
    {
        printf("\r\t\t\t\t ");
        Animate_str("Choix : ",0);
        printf("\r\t\t\t\t\t ");
    }
    else
    {
        Go_up(1);
        Cyan();
        printf("\n\t\t\t|                                     |");
        Red();
        printf("\r\t\t\t\t Choix : ");
        Reset();
    }
    char Ans[100];
    char rep;
    fgets(Ans,100,stdin);
    rep = toupper(Ans[0]);
    Remove_Entree(Ans);
    did = 1;
    if ( (strlen(Ans) != 1) || ( ( rep != '1' ) && ( rep != '2' ) && ( rep != '3' ) && ( rep != '4' ) && ( rep != '5' ) && ( rep != '6' )  ) )
    {
        Go_up_Clear_line(1);
        goto Here;
    }
    return atoi(Ans);
}

void Menu_Ann_4 ( Ptr_Maillon_Offre *Liste_act_off , Ptr_Maillon_Offre *Liste_arch_off , Ptr_Maillon_Annonceur Liste_act )
{
    char Nom[50];
    char Ans[50];
    char rep;
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous Allez supprimer une offre ===",0);
    printf("\n\n\n");
    Reset();
    printf("\t\t");
    Animate_str("Entrez Votre Nom : ",0);
    strcpy(Nom,"");
    fgets(Nom,50,stdin);
    Remove_Entree(Nom);
    strcpy(Nom,Name(Nom));
    if ( Find_Annonceur(Liste_act,Nom_ID(Nom)) == NULL )
    {
        Red();
        Animate_str("\t\tVous ne Figurez pas qur la liste de nos Annonceurs...",0);
        fflush(stdin);
        getch();
        Reset();
    }
    else
    {
        int did = 0;
        int choice;
        print_Liste_Offres( Offres_of_an_annonceur( *Liste_act_off,Nom_ID(Nom) ) , 0 , Liste_act );
        printf("\n\n\n\tEntrez l'indexe de l'offre a supprimer : ");
        fgets(Ans,50,stdin);
        Remove_Entree(Ans);
        choice = atoi(Ans);
        if ( (choice<=0) || ( choice > Longueur_Liste_Offre( Offres_of_an_annonceur( *Liste_act_off,Nom_ID(Nom) )) ) )
        {
            printf("\n\n");
            Red();
            printf("\n \t\t\tCette offre n'existe pas !");
            Reset();
            getch();
        }
        else
        {
            Ptr_Maillon_Offre Temp =  Offres_of_an_annonceur( *Liste_act_off,Nom_ID(Nom) );
            for ( int i = 1 ; i < choice ; i++ )
            {
                Temp = Next_Offre(Temp);
            }
Check:
            if ( did == 0 )
            {
                printf("\n\t\tVoulez vous vraiment supprimer votre offre? Saisissez O pour Oui et N pour Non : ");
            }
            else
            {
                printf("\t\tVoulez vous vraiment supprimer votre offre? ");
                Red();
                printf("Saisissez O pour Oui et N pour Non : ");
                Reset();
            }
            fgets(Ans,50,stdin);
            Remove_Entree(Ans);
            did = 1;
            rep = toupper(Ans[0]);
            if ( (( rep != 'N' ) && ( rep != 'O' )) || ( Ans[1] != 0 ) )
            {
                Go_up_Clear_line(1);
                if ( strlen(Ans) > 29 ) 
                {
                    Go_up_Clear_line(1);
                }
                goto Check;
            }
            if ( rep == 'N' )
            {
                printf("\n\t\t\t");
                Cyan();
                Animate_str("Operation annulee ...",0);
                Reset("");
                getch();
            }
            else
            {
                Ptr_Maillon_Annonceur modify = Find_Annonceur(Liste_act,Temp->Info.ID_rec); 
                modify->Info.Nbr_annonc = modify->Info.Nbr_annonc - 1;
                Supprimer_Offre(Liste_act_off,Liste_arch_off,Temp->Info);
                printf("\n\t\t\t");
                Cyan();
                Animate_str("Operation reussie ...",0);
                Reset("");
                getch();
            } 
        }
    }
}

void Menu_Ann_5 ( Ptr_Maillon_Annonceur *Liste_ann_act , Ptr_Maillon_Annonceur *Liste_ann_arch , Ptr_Maillon_Offre *List_off_act , Ptr_Maillon_Offre *List_off_arch  )
{
    Clear_Screen();
    printf("\t\t\t\t\t ");
    Cyan();
    Animate_str("=== Vous allez supprimer votre compte ===",0);
    printf("\n\n\n");
    char Nom[50];
    Reset();
    printf("\t\tEntrez votre Nom : ");
    fgets(Nom,50,stdin);
    Remove_Entree(Nom);
    if ( Find_Annonceur(*Liste_ann_act,Nom_ID(Nom)) == NULL )
    {
        Red();
        printf("\n\tVous ne figurez pas sur la liste des demandeurs !\n");
        printf("\n\t\tverifiez votre Nom : ");
        Cyan();
        printf("%s",Nom);
        Reset();
        fflush(stdin);
        getch();
    }
    else
    {
        int did = 0;
        char ans[50];
        char rep;
        printf("\n");
        Print_Annonceur(Find_Annonceur(*Liste_ann_act,Nom_ID(Nom))->Info,1,1);
        printf("\n");
Check:
        if ( did == 0 )
        {
            printf("\t\tVoulez vous vraiment supprimer votre Compte? Saisissez O pour Oui et N pour Non : ");
        }
        else
        {
            printf("\t\tVoulez vous vraiment supprimer votre Compte? ");
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
        if ( rep == 'N' )
        {
            printf("\n\t\t\t");
            Cyan();
            Animate_str("Operation annulee ...",0);
            Reset("");
            getch();
        }
        else
        {
            int ID = Nom_ID(Nom);
            Delete_Offres_ID(List_off_act,List_off_arch,ID);
            Supprimer_Annonceur(Liste_ann_act,Liste_ann_arch,Nom_ID(Nom));
            printf("\n\t\t\t");
            Cyan();
            Animate_str("Operation reussie ...",0);
            Reset("");
            getch();
        }
    }
    
}

int Menu_Demandeur ( void )
{
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes un Demandeur ===",0);
    printf("\n\n\n");
    printf("\t__________________________________________________________________________________________________");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|________________________________________________________________________________________________|");
    printf("\n\t\t\t|                                     |");
    printf("\n\t\t\t|                                     |");
    printf("\n\t\t\t|_____________________________________|");
    Reset();
    Go_up(9);
    printf("\n\t\t ");
    Animate_str("1 --- Enregistrer une nouvelle Demande",0);
    printf("\n\t\t ");
    Animate_str("2 --- Afficher les offres d'emploi",0);
    printf("\n\t\t ");
    Animate_str("3 --- Supprimer ma demande",0);
    printf("\n\t\t ");
    Animate_str("4 --- Quitter",0);
    printf("\n\n\n\n");
    int did = 0;
Here:
    if ( did == 0 )
    {
        printf("\r\t\t\t\t Choix : ");
        printf("\r\t\t\t\t\t ");
    }
    else
    {
        Go_up(1);
        Cyan();
        printf("\n\t\t\t|                                     |");
        Red();
        printf("\r\t\t\t\t Choix : ");
        Reset();
    }
    char Ans[100];
    char rep;
    fgets(Ans,100,stdin);
    rep = toupper(Ans[0]);
    Remove_Entree(Ans);
    did = 1;
    if ( (strlen(Ans) != 1) || ( ( rep != '1' ) && ( rep != '2' ) && ( rep != '3' ) && ( rep != '4' ) ))
    {
        Go_up_Clear_line(1);
        goto Here;
    }
    return atoi(Ans);
}

void Menu_Dem_3 ( Ptr_Maillon_Annonce *List_act , Ptr_Maillon_Annonce *List_arch )
{
    Clear_Screen();
    printf("\t\t\t\t\t ");
    Cyan();
    Animate_str("== Vous allez supprimer votre demande ==",0);
    Reset();
    printf("\n\n\n\n");
    char Nom[50];
    printf("\t\tEntrez votre Nom : ");
    fgets(Nom,50,stdin);
    Remove_Entree(Nom);
    if ( Find_Demande(*List_act,Nom_ID(Nom)) == NULL )
    {
        Red();
        printf("\n\tVous ne figurez pas sur la liste des demandeurs !\n");
        printf("\n\t\tverifiez votre Nom : ");
        Cyan();
        printf("%s",Nom);
        Reset();
        fflush(stdin);
        getch();
    }
    else
    {
        int did = 0;
        char ans[50];
        char rep;
        printf("\n");
        Print_Demande(Find_Demande(*List_act,Nom_ID(Nom))->Info,1);
        printf("\n\n");
Check:
        if ( did == 0 )
        {
            printf("\t\tVoulez vous vraiment supprimer votre demande Demande d'emploi? Saisissez O pour Oui et N pour Non : ");
        }
        else
        {
            printf("\t\tVoulez vous vraiment supprimer votre demande Demande d'emploi? ");
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
        if ( rep == 'N' )
        {
            printf("\n\t\t\t");
            Cyan();
            Animate_str("Operation annulee ...",0);
            Reset("");
            getch();
        }
        else
        {
            Supprimer_Demande(List_act,List_arch,Nom_ID(Nom));
            printf("\n\t\t\t");
            Cyan();
            Animate_str("Operation reussie ...",0);
            Reset("");
            getch();
        }

    }
    
}

int Menu_Dev ( void )
{
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n");
    printf("\t__________________________________________________________________________________________________");usleep(30000);
    for ( int i = 1 ; i<=12 ;i++ )
    {
        printf("\n\t|                                                                                                |");
        usleep(30000);
    }    
    printf("\n\t|________________________________________________________________________________________________|");usleep(30000);
    printf("\n\t\t\t|                                     |");usleep(30000);
    printf("\n\t\t\t|                                     |");usleep(30000);
    printf("\n\t\t\t|_____________________________________|");usleep(30000);
    Reset();
    Go_up(15);
    printf("\n\t\t ");
    Animate_str("1  --- Afficher les listes",10000);
    printf("\n\t\t ");
    Animate_str("2  --- Enregistrer - Supprimer une donnee",10000); // add supprimer
    printf("\n\t\t ");
    Animate_str("3  --- Afficher les offres valables",10000);
    printf("\n\t\t ");
    Animate_str("4  --- Afficher les offres - Demandes entre deux dates donnees",10000);
    printf("\n\t\t ");
    Animate_str("5  --- Afficher les offres appartenant a un seul recruteur",10000);
    printf("\n\t\t ");
    Animate_str("6  --- Rechercher les demandeurs ayant 'x' competences et maitrisant une langue 'y'",10000);
    printf("\n\t\t ");
    Animate_str("7  --- Eclatement des listes - tri - fusionnement",10000);
    printf("\n\t\t ");
    Animate_str("8  --- tri des demandes selon des criteres donnees",10000);
    printf("\n\t\t ");
    Animate_str("9  --- Afficher les 'x' posts les plus demandes ( beta )",10000);
    printf("\n\t\t ");
    Animate_str("0  --- Quitter",10000);
    printf("\n\n\n\n");
    int did = 0;
Here:
    if ( did == 0 )
    {
        printf("\r\t\t\t\t ");
        Animate_str("Choix : ",10000);
        printf("\r\t\t\t\t\t ");
    }
    else
    {
        Go_up(1);
        Cyan();
        printf("\n\t\t\t|                                     |");
        Red();
        printf("\r\t\t\t\t Choix : ");
        Reset();
    }
    char Ans[100];
    char rep;
    fgets(Ans,100,stdin);
    rep = toupper(Ans[0]);
    Remove_Entree(Ans);
    did = 1;
    if ( (strlen(Ans) != 1) || ( (rep != '1') && (rep != '2') && (rep != '3') && (rep != '4') && (rep != '5') && (rep != '6') && (rep != '7') && (rep != '8') && (rep != '9') && (rep != '0')  ) )
    {
        Go_up_Clear_line(1);
        goto Here;
    }
    return atoi(Ans);
}

int Choix_Dev_1 ( void )
{
    Clear_Screen();
    printf("\t\t\t\t\t ");
    Cyan();
    Animate_str("== Affichage des Listes ==",0);
    printf("\n");
    printf("\t__________________________________________________________________________________________________");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|________________________________________________________________________________________________|");
    printf("\n\t\t\t|                                     |");
    printf("\n\t\t\t|                                     |");
    printf("\n\t\t\t|_____________________________________|");
    Reset();
    Go_up(11);
    printf("\n\t\t ");
    Animate_str("1 --- Liste des Annonceurs Active",10000);
    printf("\n\t\t ");
    Animate_str("2 --- Liste des Annonceurs Archive",10000);
    printf("\n\t\t ");
    Animate_str("3 --- Liste des Offres Active",10000);
    printf("\n\t\t ");
    Animate_str("4 --- Liste des Offres Supprimees",10000);
    printf("\n\t\t ");
    Animate_str("5 --- Liste des Demandes Active",10000);
    printf("\n\t\t ");
    Animate_str("6 --- Liste des Demandes Archive",10000);
    printf("\n\t\t ");
    Animate_str("7 --- Quitter",10000);
    printf("\n\n\n");
    int did = 0;
Here:
    if ( did == 0 )
    {
        printf("\r\t\t\t\t ");
        Animate_str("Choix : ",10000);
        printf("\r\t\t\t\t\t ");
    }
    else
    {
        Go_up(1);
        Cyan();
        printf("\n\t\t\t|                                     |");
        Red();
        printf("\r\t\t\t\t Choix : ");
        Reset();
    }
    char Ans[100];
    char rep;
    fgets(Ans,100,stdin);
    rep = toupper(Ans[0]);
    Remove_Entree(Ans);
    did = 1;
    if ( (strlen(Ans) != 1) || ( (rep != '1') && (rep != '2') && (rep != '3') && (rep != '4') && (rep != '5') && (rep != '6') && (rep != '7')  ) )
    {
        Go_up_Clear_line(1);
        goto Here;
    }
    return atoi(Ans);
}

void Choix_Dev_2 ( Ptr_Maillon_Annonce *List_dem_act, Ptr_Maillon_Annonce *List_dem_arch ,Ptr_Maillon_Annonceur *List_ann_act , Ptr_Maillon_Annonceur *List_ann_arch ,  Ptr_Maillon_Offre *List_off_act , Ptr_Maillon_Offre *List_off_arch )
{
Menu_New_Data:
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n");
    printf("\t__________________________________________________________________________________________________");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|                                                                                                |");
    printf("\n\t|________________________________________________________________________________________________|");
    printf("\n\t\t\t|                                     |");
    printf("\n\t\t\t|                                     |");
    printf("\n\t\t\t|_____________________________________|");
    Reset();
    Go_up(12);
    printf("\n\t\t ");
    Animate_str("1  --- Enregistrer un Annonceur",10000);
    printf("\n\t\t ");
    Animate_str("2  --- Enregistrer une Offre",10000);
    printf("\n\t\t ");
    Animate_str("3  --- Enregistrer une demande",10000);
    printf("\n\t\t ");
    Animate_str("4  --- Supprimer un Annonceur",10000);
    printf("\n\t\t ");
    Animate_str("5  --- Supprimer une Offre",10000);
    printf("\n\t\t ");
    Animate_str("6  --- Supprimer une demande",10000);
    printf("\n\t\t ");
    Animate_str("7  --- Quitter",10000);
    printf("\n\n\n\n");
    int did = 0;
Here:
    if ( did == 0 )
    {
        printf("\r\t\t\t\t ");
        Animate_str("Choix : ",10000);
        printf("\r\t\t\t\t\t ");
    }
    else
    {
        Go_up(1);
        Cyan();
        printf("\n\t\t\t|                                     |");
        Red();
        printf("\r\t\t\t\t Choix : ");
        Reset();
    }
    char Ans[100];
    char rep;
    fgets(Ans,100,stdin);
    rep = toupper(Ans[0]);
    Remove_Entree(Ans);
    did = 1;
    int choix ;
    if ( (strlen(Ans) != 1) || ( (rep != '1') && (rep != '2') && (rep != '3') && (rep != '4') && (rep != '5') && (rep != '6') && (rep != '7') ) )
    {
        Go_up_Clear_line(1);
        goto Here;
    }
    int choice = atoi(Ans);
    switch ( choice )
    {
                                        case 1:
                                            Ptr_Maillon_Annonceur Temp_Ann;
                                            Annonceur New_Ann;
                                            New_Ann = New_Annonceur ( *List_ann_act );
                                            if ( New_Ann.ID != 0 )
                                            {
                                                Temp_Ann = Allouer_Annonceur ();
                                                Aff_Annonceur_Info(Temp_Ann,New_Ann);
                                                Add_Annonceur_Liste(List_ann_act,Temp_Ann);
                                            }
                                            goto Menu_New_Data;
                                            break;
                                        case 2:
                                            Ptr_Maillon_Offre Temp_Off;
                                            Offre New_Off;
                                            New_Off = New_Offre(*List_ann_act,*List_off_act);
                                            if ( New_Off.ID_rec != 0 )
                                            {
                                                Temp_Off = Allouer_Offre();
                                                Aff_Offre_Info(Temp_Off,New_Off);
                                                Add_Offre_Liste(List_off_act,Temp_Off);
                                            }
                                            goto Menu_New_Data;
                                            break;
                                        case 3:
                                            Ptr_Maillon_Annonce Temp_Dem;
                                            Demande New_Dem;
                                            New_Dem = New_Demande(*List_dem_act);
                                            if ( New_Dem.ID != 0 )
                                            {
                                                Temp_Dem = Allouer_Annonce();
                                                Aff_Demande_Info(Temp_Dem,New_Dem);
                                                Add_Demande_Liste(List_dem_act,Temp_Dem);
                                            }
                                            goto Menu_New_Data;
                                            break;


                                        case 4: /* ****************************** Delete Annonceur ****************************** */
                                            Clear_Screen();
                                            Cyan();
                                            printf("\t\t\t\t\t ");
                                            Animate_str("=== Vous etes developpeur ===",0);
                                            printf("\n\n");
                                            printf("\t\t\t\t");
                                            Animate_str("=== Vous Allez supprimer un Annonceur ===",0);
                                            Reset();
                                            printf("\n\n\n\t\t");
                                            Animate_str("Gardez l'indexe de l'annonceur a supprimer ...",0);
                                            fflush(stdin);
                                            getch();
                                            Clear_Screen();
                                            print_Liste_Annonceurs(*List_ann_act);
                                            Clear_Screen();
                                            Cyan();
                                            printf("\t\t\t\t\t ");
                                            Animate_str("=== Vous etes developpeur ===",0);
                                            printf("\n\n");
                                            printf("\t\t\t\t");
                                            Animate_str("=== Vous Allez supprimer un Annonceur ===",0);
                                            Reset();
                                            printf("\n\n\n\tEntrez l'indexe de l'annonceur a supprimer : ");
                                            fflush(stdin);
                                            fgets(Ans,50,stdin);
                                            Remove_Entree(Ans);
                                            sscanf(Ans,"%d",&choix);
                                            if ( (Num_digits(choix)!=strlen(Ans)) || ( (choix <= 0) && ( choix > Longueur_Liste_Annonceurs(*List_ann_act) ) )  )
                                            {
                                                printf("\n\n");
                                                Red();
                                                printf("\n \t\t\tCet Annonceur n'existe pas !");
                                                Reset();
                                                getch();
                                            }
                                            else
                                            {
                                                did = 0;
                                                Ptr_Maillon_Annonceur Temp = *List_ann_act;
                                                for ( int i = 1 ; i < choix ; i++ )
                                                {
                                                    Temp = Next_Annonceur (Temp);
                                                }
Check_del_ann:
                                                if ( did == 0 )
                                                {
                                                    printf("\n\t\tVoulez vous vraiment supprimer cet Annonceur? Saisissez O pour Oui et N pour Non : ");
                                                }
                                                else
                                                {
                                                    printf("\t\tVoulez vous vraiment supprimer cet Annonceur? ");
                                                    Red();
                                                    printf("Saisissez O pour Oui et N pour Non : ");
                                                    Reset();
                                                }
                                                fgets(Ans,50,stdin);
                                                Remove_Entree(Ans);
                                                did = 1;
                                                rep = toupper(Ans[0]);
                                                if ( (( rep != 'N' ) && ( rep != 'O' )) || ( Ans[1] != 0 ) )
                                                {
                                                    Go_up_Clear_line(1);
                                                    if ( strlen(Ans) > 29 ) 
                                                    {
                                                        Go_up_Clear_line(1);
                                                    }
                                                    goto Check_del_ann;
                                                }
                                                if ( rep == 'N' )
                                                {
                                                    printf("\n\t\t\t");
                                                    Cyan();
                                                    Animate_str("Operation annulee ...",0);
                                                    Reset("");
                                                    getch();
                                                }
                                                else
                                                {
                                                    Delete_Offres_ID(List_off_act,List_off_arch,Temp->Info.ID);
                                                    Supprimer_Annonceur(List_ann_act,List_ann_arch,Temp->Info.ID);
                                                    printf("\n\t\t\t");
                                                    Cyan();
                                                    Animate_str("Operation reussie ...",0);
                                                    Reset("");
                                                    getch();
                                                } 
                                            }
                                            goto Menu_New_Data;
                                            break;



                                        case 5: /* ****************************** Delete Offre ****************************** */
                                            Clear_Screen();
                                            Cyan();
                                            printf("\t\t\t\t\t ");
                                            Animate_str("=== Vous etes developpeur ===",0);
                                            printf("\n\n\n");
                                            printf("\t\t\t\t");
                                            Animate_str("=== Vous Allez supprimer une offre ===",0);
                                            Reset();
                                            printf("\n\n\n\t\t");
                                            Animate_str("Gardez l'indexe de l'offre a supprimer ...",0);
                                            fflush(stdin);
                                            getch();
                                            Clear_Screen();
                                            print_Liste_Offres(*List_off_act,1,*List_ann_act);
                                            printf("\n\n\n\tEntrez l'indexe de l'offre a supprimer : ");
                                            fflush(stdin);
                                            fgets(Ans,50,stdin);
                                            Remove_Entree(Ans);
                                            sscanf(Ans,"%d",&choix);
                                            if ( (Num_digits(choix)!=strlen(Ans)) || ( (choix <=0) && ( choix > Longueur_Liste_Offre(*List_off_act) ) )  )
                                            {
                                                printf("\n\n");
                                                Red();
                                                printf("\n \t\t\tCette offre n'existe pas !");
                                                Reset();
                                                getch();
                                            }
                                            else
                                            {
                                                did = 0;
                                                Ptr_Maillon_Offre Temp = *List_off_act;
                                                for ( int i = 1 ; i < choix ; i++ )
                                                {
                                                    Temp = Next_Offre (Temp);
                                                }
Check_del_off:
                                                if ( did == 0 )
                                                {
                                                    printf("\n\t\tVoulez vous vraiment supprimer cette offre? Saisissez O pour Oui et N pour Non : ");
                                                }
                                                else
                                                {
                                                    printf("\t\tVoulez vous vraiment supprimer cette offre? ");
                                                    Red();
                                                    printf("Saisissez O pour Oui et N pour Non : ");
                                                    Reset();
                                                }
                                                fgets(Ans,50,stdin);
                                                Remove_Entree(Ans);
                                                did = 1;
                                                rep = toupper(Ans[0]);
                                                if ( (( rep != 'N' ) && ( rep != 'O' )) || ( Ans[1] != 0 ) )
                                                {
                                                    Go_up_Clear_line(1);
                                                    if ( strlen(Ans) > 29 ) 
                                                    {
                                                        Go_up_Clear_line(1);
                                                    }
                                                    goto Check_del_off;
                                                }
                                                if ( rep == 'N' )
                                                {
                                                    printf("\n\t\t\t");
                                                    Cyan();
                                                    Animate_str("Operation annulee ...",0);
                                                    Reset("");
                                                    getch();
                                                }
                                                else
                                                {
                                                    Ptr_Maillon_Annonceur Modify = Find_Annonceur(*List_ann_act,Temp->Info.ID_rec);
                                                    Modify->Info.Nbr_annonc -= 1;
                                                    Supprimer_Offre(List_off_act,List_off_arch,Temp->Info);
                                                    printf("\n\t\t\t");
                                                    Cyan();
                                                    Animate_str("Operation reussie ...",0);
                                                    Reset("");
                                                    getch();
                                                } 
                                            }
                                            goto Menu_New_Data;
                                            break;
                                        case 6: /* ****************************** Delete Annonce ****************************** */
                                            Clear_Screen();
                                            Cyan();
                                            printf("\t\t\t\t\t ");
                                            Animate_str("=== Vous etes developpeur ===",0);
                                            printf("\n\n\n");
                                            printf("\t\t\t\t");
                                            Animate_str("=== Vous Allez supprimer une demande ===",0);
                                            Reset();
                                            printf("\n\n\n\t\t");
                                            Animate_str("Gardez l'indexe de la demande  a supprimer ...",0);
                                            fflush(stdin);
                                            getch();
                                            Clear_Screen();
                                            Print_Liste_Demande(*List_dem_act);
                                            printf("\n\n\n\tEntrez l'indexe de la demande a supprimer : ");
                                            fflush(stdin);
                                            fgets(Ans,50,stdin);
                                            Remove_Entree(Ans);
                                            sscanf(Ans,"%d",&choix);
                                            if ( (Num_digits(choix)!=strlen(Ans)) || ( (choix <=0) && ( choix > Longueur_Liste_Demandes (*List_dem_act) ) )  )
                                            {
                                                printf("\n\n");
                                                Red();
                                                printf("\n \t\t\tCette demande n'existe pas !");
                                                Reset();
                                                getch();
                                            }
                                            else
                                            {
                                                did = 0;
                                                Ptr_Maillon_Annonce Temp = *List_dem_act;
                                                for ( int i = 1 ; i < choix ; i++ )
                                                {
                                                    Temp = Next_Annonce (Temp);
                                                }
Check_del_dem:
                                                if ( did == 0 )
                                                {
                                                    printf("\n\t\tVoulez vous vraiment supprimer cette demande? Saisissez O pour Oui et N pour Non : ");
                                                }
                                                else
                                                {
                                                    printf("\t\tVoulez vous vraiment supprimer cette demande? ");
                                                    Red();
                                                    printf("Saisissez O pour Oui et N pour Non : ");
                                                    Reset();
                                                }
                                                fgets(Ans,50,stdin);
                                                Remove_Entree(Ans);
                                                did = 1;
                                                rep = toupper(Ans[0]);
                                                if ( (( rep != 'N' ) && ( rep != 'O' )) || ( Ans[1] != 0 ) )
                                                {
                                                    Go_up_Clear_line(1);
                                                    if ( strlen(Ans) > 29 ) 
                                                    {
                                                        Go_up_Clear_line(1);
                                                    }
                                                    goto Check_del_dem;
                                                }
                                                if ( rep == 'N' )
                                                {
                                                    printf("\n\t\t\t");
                                                    Cyan();
                                                    Animate_str("Operation annulee ...",0);
                                                    Reset("");
                                                    getch();
                                                }
                                                else
                                                {
                                                    Supprimer_Demande(List_dem_act,List_dem_arch,Temp->Info.ID);   
                                                    printf("\n\t\t\t");
                                                    Cyan();
                                                    Animate_str("Operation reussie ...",0);
                                                    Reset("");
                                                    getch();
                                                } 
                                            }

                                            goto Menu_New_Data;
                                            break;
                                        default:
                                            break;
                                }
}

void Choix_Dev_3 ( Ptr_Maillon_Offre Liste , Ptr_Maillon_Annonceur Liste_Ann )
{
    int Date[3];
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();
    printf("\t\tEntrez la date de reference ( jj mm yyyy ) : ");
    Get_Date(0,Date,"\r\033[A\033[2K\t\tEntrez la date de reference \033[1;31m ( jj mm yyyy ) :                           Date invalide !\r\033[0m\t\tEntrez la date de reference \033[1;31m ( jj mm yyyy )\033[0m : ");
    Go_up_Clear_line(2);
    if ( Liste == NULL )
    {
        Cyan();
        printf("\n\tLa liste des Offres est Vide ...");
        fflush(stdin);
        getch();
        Reset();
        return;
    }
    Ptr_Maillon_Offre Temp = Liste;
    int i = 1 ;
    int done = 0;
    char test;
    while ( (Temp != NULL) && ( done == 0 ) )
    {
        if ( Compare_Dates(Date,Temp->Info.Delai_Condidature) != -1 )
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
            Print_Offre(Temp->Info,1,1,Liste_Ann);
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
        }
        
        Temp = Next_Offre(Temp);
    }
    if ( (Temp != NULL) && ( done != 1 ) )
    {
        Cyan();
        printf("\n\tVous avez attient la fin de la liste des Offres ...");
        fflush(stdin);
        getch();
        Reset();
    }
}

void Choix_Dev_4 ( Ptr_Maillon_Annonceur Liste_Ann , Ptr_Maillon_Annonce Liste_Dem_act , Ptr_Maillon_Annonce Liste_Dem_arch , Ptr_Maillon_Offre Liste_Off_Act , Ptr_Maillon_Offre Liste_Off_Acrh )
{
    int Date1[3];
    int Date2[3];
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();
Date:
    printf("\t\tEntrez la 1 ere date de reference ( jj mm yyyy ) : ");
    Get_Date(0,Date1,"\r\033[A\033[2K\t\tEntrez la 1 ere date de reference\033[1;31m ( jj mm yyyy ) :                           Date invalide !\r\033[0m\t\tEntrez la 1 ere date de reference \033[1;31m( jj mm yyyy )\033[0m : ");
    printf("\n\n");
    printf("\t\tEntrez la 2 eme date de reference ( jj mm yyyy ) : ");
    Get_Date(0,Date2,"\r\033[A\033[2K\t\tEntrez la 2 eme date de reference \033[1;31m( jj mm yyyy ) :                           Date invalide !\r\033[0m\t\tEntrez la 2 eme date de reference \033[1;31m( jj mm yyyy )\033[0m : ");
    if ( Compare_Dates(Date1,Date2) != 1 )
    {
        Go_up_Clear_line(5);
        Red();
        printf("\t\t\t\tDates incoherentes : \n");
        Reset();
        goto Date;
    }
    Clear_Screen();
    Cyan();
    printf("\nLa liste des demandeurs Active ...");
    fflush(stdin);
    getch();
    Reset();
    printf("\n");

    /******************************* Demandeurs active *******************************/
    Ptr_Maillon_Annonce Temp = Liste_Dem_act;
    int i = 1;
    int done = 0;
    int test;
    if ( Temp == NULL )
    {
        Cyan();
        printf("\n\tLa liste des Demandes actives est Vide ...");
        fflush(stdin);
        getch();
        Reset();
    }
    else
    {
        while ( (Temp != NULL) && ( done == 0 ) )
        {
            if ( (Compare_Dates(Date1,Temp->Info.Date_Publication) != -1) && ( Compare_Dates(Date2,Temp->Info.Date_Publication) != 1 )  )
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
                i++;
            }
            Temp = Next_Annonce(Temp);
        }
        if ( (Temp == NULL) && ( done != 1 ) )
        {
            Cyan();
            printf("\n\tVous avez attient la fin de la liste des Demandes ...");
            fflush(stdin);
            getch();
            Reset();
        }
    }
    
    /******************************* Demandes archive *******************************/
    Clear_Screen();
    Cyan();
    printf("\nLa liste des demandeurs Archive ...");
    fflush(stdin);
    getch();
    Reset();
    printf("\n");
    
    Temp = Liste_Dem_arch;
    i = 1;
    done = 0;
    if ( Temp == NULL )
    {
        Cyan();
        printf("\n\tLa liste des Demandes archives est Vide ...");
        fflush(stdin);
        getch();
        Reset();
    }
    else
    {
        while ( (Temp != NULL) && ( done == 0 ) )
        {
            if ( (Compare_Dates(Date1,Temp->Info.Date_Publication) != -1) && ( Compare_Dates(Date2,Temp->Info.Date_Publication) != 1 )  )
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
                i++;
            }
            Temp = Next_Annonce(Temp);
            
        }
        if ( (Temp == NULL) && ( done != 1 ) )
        {
            Cyan();
            printf("\n\tVous avez attient la fin de la liste des Demandes ...");
            fflush(stdin);
            getch();
            Reset();
        }
    }
    
    /***************************************** Offres actives *****************************************/    
    Clear_Screen();
    Cyan();
    printf("\nLa liste des Offres active ...");
    fflush(stdin);
    getch();
    Reset();
    printf("\n");
    Ptr_Maillon_Offre Temp_t = Liste_Off_Act;
    if ( Liste_Off_Act == NULL )
    {
        Cyan();
        printf("\n\tLa liste des Offres est Vide ...");
        fflush(stdin);
        getch();
        Reset();
    }
    else
    {
        i = 1 ;
        done = 0;
        while ( (Temp_t != NULL) && ( done == 0 ) )
        {
            if ( (Compare_Dates(Date1,Temp_t->Info.Date_Publication) != -1) && ( Compare_Dates(Date2,Temp_t->Info.Date_Publication) != 1 ) )
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
                Print_Offre(Temp_t->Info,1,1,Liste_Ann);
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
            }
            Temp_t = Next_Offre(Temp_t);
        }
        if ( (Temp_t == NULL) && ( done != 1 ) )
        {
            Cyan();
            printf("\n\tVous avez attient la fin de la liste des Offres ...");
            fflush(stdin);
            getch();
            Reset();
        }
    }
    

    /***************************************** Offres archives *****************************************/

    Clear_Screen();
    Cyan();
    printf("\nLa liste des Offres Archive ...");
    fflush(stdin);
    getch();
    Reset();
    printf("\n");
    if ( Liste_Off_Acrh == NULL )
    {
        Cyan();
        printf("\n\tLa liste des Offres est Vide ...");
        fflush(stdin);
        getch();
        Reset();
    }
    else
    {
        i = 1 ;
        done = 0;
        Temp_t = Liste_Off_Acrh;
        while ( (Temp_t != NULL) && ( done == 0 ) )
        {
            if ( (Compare_Dates(Date1,Temp_t->Info.Date_Publication) != -1) && ( Compare_Dates(Date2,Temp_t->Info.Date_Publication) != 1 ) )
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
                Print_Offre(Temp_t->Info,1,1,Liste_Ann);
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
            }
            Temp_t = Next_Offre(Temp_t);
        }
        if ( (Temp_t == NULL) && ( done != 1 ) )
        {
            Cyan();
            printf("\n\tVous avez attient la fin de la liste des Offres ...");
            fflush(stdin);
            getch();
            Reset();
        }
    }
    
}

void Choix_Dev_5 ( Ptr_Maillon_Offre List_Off , Ptr_Maillon_Annonceur List_Ann )
{
    int did = 0;
    Clear_Screen();
    char Nom[50];
    char String [50];
    char rep;
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();
Nom:
    did = 0;
    printf("\t\t");
    Animate_str("Entrez le nom de l'annonceur : ",0);
    fgets(Nom,50,stdin);
    Remove_Entree(Nom);
    if ( Find_Annonceur(List_Ann,Nom_ID(Nom)) == NULL )
    {
        printf("\n\t\tLe nom que vous avez entre ne figure pas sur la liste de nos annonceurs!\n");
        printf("\n");
check:
        printf("\tVerifiez votre Nom : ");
        Cyan();
        printf("%s",Nom);
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
            if ( strlen(String) >= 50 - strlen(Nom) )
            {
                Go_up_Clear_line(1);
            }
            goto check;

        }
        if  ( rep == 'F' )
        {
            Go_up_Clear_line(5);
            goto Nom;
        }
    }
    if ( Offres_of_an_annonceur(List_Off,Nom_ID(Nom)) != NULL )
    {
        print_Liste_Offres(Offres_of_an_annonceur(List_Off,Nom_ID(Nom)),1,List_Ann);
    }
    else
    {
        Go_up_Clear_line(3);
        Cyan();
        printf("\t\t\t\t");
        Animate_str("Cet Annonceur n'existe pas ou n'a pas d'offres !",0);
        fflush(stdin);
        getch();
        Reset();
    }
    
}

void Choix_Dev_6 ( Ptr_Maillon_Annonce Liste )
{
    int langues , competences;
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();
compet:
    printf("\t\tEntrez le nombre de competences exigees : ");
    char Ans[50];
    strcpy(Ans,"");
    fgets(Ans,50,stdin);
    Remove_Entree(Ans);
    sscanf(Ans,"%d",&competences);
    if ( ( Num_digits(competences) != strlen(Ans) ) || ((competences < 1) || (competences > 16)) )
    {
        Red();
        Clear_line();
        Go_up_Clear_line(1);
        printf("\t\t\t\t\t\t\t\t\t\tNombre invlide ( entre 1 et 16 )");
        Reset();
        printf("\r");
        goto compet;
    }
    int did = 0;
    printf("\n\n");
    Langue Choix_Langue [7];
    Get_Langue ( Choix_Langue );
    Print_Languages_Box ( Choix_Langue );
Lang:
    printf("\n\t\tEntrez l'indexe de la langue exigee ");
    if ( did == 0 )
    {
        printf("( chiffre entre 1 et 7 ) : ");
    }  
    else
    {
        Red();
        printf("( chiffre entre 1 et 7 ) : ");
        Reset();
    }        
    strcpy(Ans,"");
    fgets(Ans,50,stdin);
    Remove_Entree(Ans);
    langues = -1 ;
    sscanf(Ans,"%d",&langues);
    langues = Uniqu_dig(langues);
    did = 1;
    if ( ( Num_digits(langues) != 1 ) || (langues<=0) || ( langues > 1234567 ) || ( Frequ_dig(langues,8) != 0 ) || ( Frequ_dig(langues,9) != 0 ) || ( Frequ_dig(langues,0) != 0 ) || ( strlen(Ans) != Num_digits(langues) ))
    {
        Go_up_Clear_line(2);
        goto Lang;
    }
    Ptr_Maillon_Annonce New_List = NULL;
    Ptr_Maillon_Annonce New_List_Final = NULL;
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();
    char String [300];
    strcpy(String,"");
    Cyan();
    sprintf(String,"\t\tLes demandes des personnes maitrisant : \n\t\t\t\t\t\t\t- la langue %s\n\t\t\t\t\t\t\t- au moins %d competences",Print_Languages(langues),competences);
    Reset();
    Animate_str(String,0);
    printf("\n\n");
    New_List = Demandes_by_langues(Liste,langues);
    New_List_Final = Demandes_by_competences(New_List,competences);
    Print_Liste_Demande(New_List_Final);


}

void Choix_Dev_8 ( Ptr_Maillon_Offre List_off , Ptr_Maillon_Annonceur List_ann , Ptr_Maillon_Annonce List_dem )
{
    char Ans[50];
    int rep;
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Animate_str("\t\t\tVoici Les Offres toujours actives ...\n\t\tGardez le numero de l'offre que voulez voir les demandes correspondantes ... ",0);
    Reset();
    fflush(stdin);
    getch();
    print_Liste_Offres(List_off,1,List_ann);
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();
Here:
    Animate_str("\tEntrez le numero de l'offre : ",0);
    strcpy(Ans,"");
    fgets(Ans,50,stdin);
    Remove_Entree(Ans);
    sscanf(Ans,"%d",&rep);
    if ( (Num_digits(rep) != strlen(Ans)) || ( rep > Longueur_Liste_Offre(List_off) ) )
    {
        Red();
        Clear_line();
        Go_up_Clear_line(1);
        printf("\t\t\t\t\t\t\t\t\t\tl'offre n'existe pas");
        Reset();
        printf("\r");
        goto Here;
    }
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Animate_str("\tLes demandes correspondantes a l'offre choisie : \n",0);
    Reset();
    Ptr_Maillon_Annonce List;
    Ptr_Maillon_Offre Temp_off = List_off;
    for ( int i = 1 ; i < rep ; i++ )
    {
        Temp_off = Next_Offre(Temp_off);
    }
    List = Demandes_by_diplome(List_dem,Temp_off->Info.Diplome);
    List = Demandes_by_langues_multiple(List,Temp_off->Info.Langues);
    List = Demandes_by_competences_multiple( List , Temp_off->Info.Liste_Competence );
    Print_Liste_Demande(List);

}

void Choix_Dev_7 ( Ptr_Maillon_Offre Liste , Ptr_Maillon_Annonceur List_Ann )
{
    Clear_Screen();

    /* Eclatement selon annes d'experience et ajout selon competences */
    
    Ptr_Maillon_Offre Temp = Liste;
    Ptr_Maillon_Offre List_u5 = NULL ;
    Ptr_Maillon_Offre List_o5 = NULL ;
    Ptr_Maillon_Offre New ;
    
    while ( Temp != NULL )
    {
        New = Allouer_Offre();
        Aff_Offre_Info(New,Get_Offre_Maillon(Temp));    
        if ( Temp->Info.ExpYear >= 5 )
        {
            Add_offre_by_compet ( &List_o5 , New );
        }
        else
        {
            Add_offre_by_compet ( &List_u5 , New );
        }
        Temp = Next_Offre(Temp);
    }
    
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();

    Animate_str("\tAppuyez sur une touche pour afficher La liste des offres exigeant moins de 5 ans d'experience",0);
    printf("\n");
    Animate_str("\t\t\tLa liste est triee selon le nombre de competences exigee ...",0);
    fflush(stdin);
    getch();
    print_Liste_Offres(List_u5,1,List_Ann);

    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();

    Animate_str("\tAppuyez sur une touche pour afficher La liste des offres exigeant plus de 5 ans d'experience",0);
    printf("\n");
    Animate_str("\t\t\tLa liste est triee selon le nombre de competences exigee ...",0);
    fflush(stdin);
    getch();
    print_Liste_Offres(List_o5,1,List_Ann);



    /* Fusion  */

    Ptr_Maillon_Offre New_List = NULL ;
    Ptr_Maillon_Offre Temp_New ;
    Ptr_Maillon_Offre Temp_u = List_u5;
    Ptr_Maillon_Offre Temp_o = List_o5 ;

    while ( (Temp_u != NULL) && (Temp_o != NULL) )
    {
        if ( strlen(Temp_o->Info.Liste_Competence) < strlen(Temp_u->Info.Liste_Competence) )
        {
            Temp_New = Allouer_Offre();
            Aff_Offre_Info(Temp_New,Get_Offre_Maillon(Temp_o));
            Add_offre_by_compet(&New_List,Temp_New);
            Temp_o = Next_Offre ( Temp_o );
        }
        else
        {
            Temp_New = Allouer_Offre();
            Aff_Offre_Info(Temp_New,Get_Offre_Maillon(Temp_u));
            Add_offre_by_compet(&New_List,Temp_New);
            Temp_u = Next_Offre ( Temp_u );
        }
    }
    while ( Temp_o != NULL )
    {
        Temp_New = Allouer_Offre();
        Aff_Offre_Info(Temp_New,Get_Offre_Maillon(Temp_o));
        Add_offre_by_compet(&New_List,Temp_New);
        Temp_o = Next_Offre ( Temp_o );
    }
    while ( Temp_u != NULL )
    {
        Temp_New = Allouer_Offre();
        Aff_Offre_Info(Temp_New,Get_Offre_Maillon(Temp_o));
        Add_offre_by_compet(&New_List,Temp_New);
        Temp_o = Next_Offre ( Temp_o );        
    }
    
    
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();

    Animate_str("\tAppuyez sur une touche pour afficher La liste des offres fusionnee",0);
    printf("\n");
    Animate_str("\t\t\tLa liste est triee selon le nombre de competences exigee ...",0);
    fflush(stdin);
    getch();
    print_Liste_Offres(New_List,1,List_Ann);

}

void Choix_Dev_9 ( Ptr_Maillon_Offre List )
{
    Clear_Screen();
    Cyan();
    printf("\t\t\t\t\t ");
    Animate_str("=== Vous etes developpeur ===",0);
    printf("\n\n\n");
    Reset();
    if ( List != NULL )
    {
        int did = 0;
        char Ans[50];
        int Number = 0;
Check:
        printf("\n\t\tCombien de poste (s) les plus demandes voulez-vous voir ");
        if ( did == 0 )
        {
            printf("( maximum : %d ) : ",Longueur_Liste_Offre(List));
        }  
        else
        {
            Red();
            printf("( maximum : %d ) : ",Longueur_Liste_Offre(List));
            Reset();
        }        
        strcpy(Ans,"");
        fgets(Ans,50,stdin);
        Remove_Entree(Ans);
        sscanf(Ans,"%d",&Number);
        did = 1;
        if ( ( Num_digits(Number) > Num_digits(Longueur_Liste_Offre(List)) ) || ( strlen(Ans)!= Num_digits(Number) ) || ( Number <1 ) || ( Number > Longueur_Liste_Offre(List) ) )
        {
            Go_up_Clear_line(2);
            goto Check;
        }
        int min = 0;
        int Fr = 0;
        char Temporary[50];
        
        Maillon_Poste Liste_postes = Create_List ( Number ) ;
        
        Ptr_Maillon_Offre Temp = List ;
        
        Ptr_Maillon_Offre Under_Temp;
        
        while ( Temp != NULL )
        {
            Under_Temp = Temp;
            strcpy(Temporary,Temp->Info.Nom_Poste);
            Fr = 0 ;
            while ( Under_Temp != NULL )
            {
                if (strcmp(Temporary,Under_Temp->Info.Nom_Poste) == 0 )
                {
                    Fr ++ ;
                }
                Under_Temp = Next_Offre ( Under_Temp );
            }
            if ( Fr > min )
            {
                Maillon_Poste New = (liste_poste*)malloc(sizeof(liste_poste));
                New->Frequ = Fr ;
                strcpy(New->Nom,Temporary);
                min = Add_liste_poste(&Liste_postes,New,Number);
            }
            Temp = Next_Offre(Temp);
        }
        Clear_Screen();
        Cyan();
        printf("\t\t\t\t\t ");
        printf("=== Vous etes developpeur ===");
        printf("\n\n\n\n");
        Reset();
        char String[200];
        if ( Number == 1 )
        {
            sprintf(String,"\t\tLe poste les plus demande est : ");
        }
        else
        {
            sprintf(String,"\t\tLes %d postes les plus demandes sont : ",Number);
        }
        Animate_str(String,0);
        printf("\n\n");
        char String2[30];
        Maillon_Poste Temp_new = Liste_postes ;
        int cpt = 0;
        for ( int i = 0 ; i < Number ; i++ )
        {
            printf("\n\t\t\t\t");
            sprintf(String,"- %s",Norm(Temp_new->Nom,0));
            sprintf(String2,"%d Offres",Temp_new->Frequ);
            Animate_str(String,0);
            printf("    ");
            for ( int j = 0 ; j < 70-strlen(String) ; j++  ) printf("-");
            printf("    ");
            Animate_str(String2,0);
            Temp_new = Temp_new->Next;
            cpt++;
            if ( (Temp_new == NULL) || ( Temp_new->Frequ == 0 ) )
            {
                break;
            }
        }
        printf("\n\n");
        if ( cpt != Number )
        {
            Animate_str("\t\t\tOn trouve ",0);
            printf("%d",cpt);
            Animate_str(" postes dans ",0);
            printf("%d",Longueur_Liste_Offre(List));
            Animate_str(" Offres !",0);
        }
        printf("\n");
        printf("\n\n\t\t");
        Cyan();
        Animate_str("Appuyez sur une touche pour retourner au menu ...",0);
        Reset();
        fflush(stdin);
        getch();
    } 
    else
    {
        printf("\n\t\t");
        Animate_str("La liste des offres est vide !",0);
        fflush(stdin);
        getch();
    } 
    
    
}

//__________________________________________________________________________________________________________