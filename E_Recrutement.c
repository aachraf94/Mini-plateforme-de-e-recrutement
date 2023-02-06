#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>
#include "Lib/Display.h"
#include "Lib/EMPLOI_LLC_BIBLIO.h"
#include "Lib/Basic_Functions.h"
#include "Lib/Annonceurs.h"
#include "Lib/Offres.h"
#include "Lib/Demandes.h"
#include "Lib/Standard_Library.h"
#include "Lib/Menus.h"

int main ( void )
{

    /*

    NOTE : The files are open here with "r" only because of the risk of deleting data if the execution of the program doesn't end
    
    the file is opened at the end with "w" to write on it "safely"
    
    */

    /* Start ouverture des fichiers */

    FILE *Ann_Act_R   = fopen("Data/Annonceurs_Active.txt","r") ;
    FILE *Ann_Arch_R  = fopen("Data/Annonceurs_Archive.txt","r");
    FILE *Dem_Act_R   = fopen("Data/Demandes_Active.txt","r")   ;
    FILE *Dem_Arch_R  = fopen("Data/Demandes_Archive.txt","r")  ;
    FILE *Off_Act_R   = fopen("Data/Offres_Active.txt","r")     ;
    FILE *Off_Sup_R   = fopen("Data/Offres_Supprimes.txt","r")  ;

    /* End ouverture des fichiers */
    
    /* Start Reading info from files */

    Ptr_Maillon_Annonceur List_Annonceurs_Active  = Read_Liste_Annonceur_file ( Ann_Act_R )  ;
    Ptr_Maillon_Annonceur List_Annonceurs_Archive = Read_Liste_Annonceur_file ( Ann_Arch_R ) ;
    Ptr_Maillon_Annonce   List_Demandes_Active    = Read_Liste_Demande_file   ( Dem_Act_R )  ;
    Ptr_Maillon_Annonce   List_Demandes_Archives  = Read_Liste_Demande_file   ( Dem_Arch_R ) ;
    Ptr_Maillon_Offre     List_Offres_Actives     = Read_Liste_Offre_file     ( Off_Act_R )  ;
    Ptr_Maillon_Offre     List_Offres_Suppr       = Read_Liste_Offre_file     ( Off_Sup_R )  ;

    /* End Reading info from files */

    /* Start Closing files */
    
    fclose(Ann_Act_R);
    fclose(Ann_Arch_R);
    fclose(Dem_Act_R);
    fclose(Dem_Arch_R);
    fclose(Off_Act_R);
    fclose(Off_Sup_R);
    
    /* End Closing files */

    Set_Color_Console();            /* Initialisation de la couleur */
    Set_Width_Console();    /* Initialisation de la largeur de l'executable */

    First_Interface();
    
    Disclaimer_Page();
    
    /*************************************************** Debut du programme ***************************************************/

Menu_Principal:

    int choice_1 = -1;
    int choice_2 = -1;
    choice_1 = Principal_Menu();
    switch ( choice_1 )
    {
    case 1: /* ********************** Menu Annonceur ********************** */
Menu_Ann:
                    choice_2 = Menu_Annonceur();
                    switch ( choice_2 )
                    {
                    case 1:
                        Ptr_Maillon_Annonceur Temp_Ann;
                        Annonceur New_Ann;
                        New_Ann = New_Annonceur ( List_Annonceurs_Active );
                        if ( New_Ann.ID != 0 )
                        {
                            Temp_Ann = Allouer_Annonceur ();
                            Aff_Annonceur_Info(Temp_Ann,New_Ann);
                            Add_Annonceur_Liste(&List_Annonceurs_Active,Temp_Ann);
                        }       
                        goto Menu_Ann;
                        break;
                    case 2:
                        Ptr_Maillon_Offre Temp_Off;
                        Offre New_Off;
                        New_Off = New_Offre(List_Annonceurs_Active,List_Offres_Actives);
                        if ( New_Off.ID_rec != 0 )
                        {
                            Temp_Off = Allouer_Offre();
                            Aff_Offre_Info(Temp_Off,New_Off);
                            Add_Offre_Liste(&List_Offres_Actives,Temp_Off);
                        }
                        goto Menu_Ann;
                        break;
                    case 3:
                        Clear_Screen();
                        Print_Liste_Demande(List_Demandes_Active);    
                        goto Menu_Ann;
                        break;
                    case 4:
                        Menu_Ann_4(&List_Offres_Actives,&List_Offres_Suppr,List_Annonceurs_Active);
                        goto Menu_Ann;
                        break;
                    case 5:
                        Menu_Ann_5(&List_Annonceurs_Active,&List_Annonceurs_Archive,&List_Offres_Actives,&List_Offres_Suppr);
                        goto Menu_Ann;
                        break;
                    case 6:
                        goto End; 
                        break;
                    default:
                        break;
                    }
    break;
    case 2: /* ********************** Menu Demandeur ********************** */
Menu_Dem:
                    choice_2 = Menu_Demandeur ();
                    switch ( choice_2 )
                    {
                    case 1:
                        Ptr_Maillon_Annonce Temp_Dem;
                        Demande New_Dem;
                        New_Dem = New_Demande(List_Demandes_Active);
                        if ( New_Dem.ID != 0 )
                        {
                            Temp_Dem = Allouer_Annonce();
                            Aff_Demande_Info(Temp_Dem,New_Dem);
                            Add_Demande_Liste(&List_Demandes_Active,Temp_Dem);
                        } 
                        goto Menu_Dem;
                        break;
                    case 2:
                        Clear_Screen();
                        print_Liste_Offres(List_Offres_Actives,1,List_Annonceurs_Active);
                        goto Menu_Dem;
                        break;
                    case 3:
                        Menu_Dem_3(&List_Demandes_Active,&List_Demandes_Archives);
                        goto Menu_Dem;
                        break;
                    case 4:
                        goto End;            
                        break;
                    
                    default:
                        goto Menu_Dem;
                        break;
                    }
    break;
    case 3: /* ********************** Menu Developpeur ********************** */
Menu_Developper:
                    choice_2 = Menu_Dev();
                    int choice_3 ;
                    switch ( choice_2 )
                    {
                    case 1:
Menu_Aff_Liste:
                    choice_3 = Choix_Dev_1 () ;
                    
                                switch ( choice_3 )
                                {
                                case 1:
                                    Clear_Screen();
                                    print_Liste_Annonceurs(List_Annonceurs_Active);
                                    goto Menu_Aff_Liste;
                                    break;
                                case 2:
                                    Clear_Screen();
                                    print_Liste_Annonceurs(List_Annonceurs_Archive);
                                    goto Menu_Aff_Liste;
                                    break;
                                case 3:
                                    Clear_Screen();
                                    print_Liste_Offres(List_Offres_Actives,0,NULL);                
                                    goto Menu_Aff_Liste;
                                    break;
                                case 4:
                                    Clear_Screen();
                                    print_Liste_Offres(List_Offres_Suppr,0,NULL);                
                                    goto Menu_Aff_Liste;
                                    break;
                                case 5:
                                    Clear_Screen();
                                    Print_Liste_Demande(List_Demandes_Active);
                                    goto Menu_Aff_Liste;
                                    break;
                                case 6:
                                    Clear_Screen();
                                    Print_Liste_Demande(List_Demandes_Archives);
                                    goto Menu_Aff_Liste;
                                    break;
                                case 7:
                                    goto Menu_Developper;
                                    break;
                                default:
                                    goto Menu_Developper;
                                    break;
                                }
                                break;
                    case 2:
                                Choix_Dev_2 (&List_Demandes_Active,&List_Demandes_Archives,&List_Annonceurs_Active,&List_Annonceurs_Archive,&List_Offres_Actives,&List_Offres_Suppr) ;
                                goto Menu_Developper;
                                break;
                    case 3:
                                Choix_Dev_3 ( List_Offres_Actives , List_Annonceurs_Active );
                                goto Menu_Developper;
                                break;
                    case 4:
                                Choix_Dev_4 ( List_Annonceurs_Active , List_Demandes_Active , List_Demandes_Archives , List_Offres_Actives , List_Offres_Suppr );
                                goto Menu_Developper;
                                break;
                    case 5:
                                Choix_Dev_5(List_Offres_Actives,List_Annonceurs_Active);
                                goto Menu_Developper;
                        break;
                    case 6: 
                                Choix_Dev_6 ( List_Demandes_Active );
                                goto Menu_Developper;
                        break;
                    case 7:
                                Choix_Dev_7(List_Offres_Actives,List_Annonceurs_Active);
                                goto Menu_Developper;
                        break;
                    case 8:  
                                Choix_Dev_8(List_Offres_Actives,List_Annonceurs_Active,List_Demandes_Active);
                                goto Menu_Developper;
                        break;
                    case 9: 
                                Choix_Dev_9(List_Offres_Actives);
                                goto Menu_Developper;
                        break;
                    case 0:
                        goto End;
                        break;
                
                    default:
                            goto Menu_Principal;
                            break;
                    }
                    break;
                    goto Menu_Developper;
    default:
        break;
    }

    /*************************************************** Fin du programme ***************************************************/

End:
    Supprimer_Annonceur_0_Ann(&List_Annonceurs_Active,&List_Annonceurs_Archive);
    
    int changes = Verify_changes();
    /* If the user wants to save the information into the database he presses yes and changes will be 1 and it's done, else nothing is saved */
    
    
    /* ********************** Changes = 1  ===> Sauvegarde des Informations dans les fichiers ********************** */

    if ( changes == 1 )
    {
        /* Start ouverture des fichiers */
    
        FILE *Ann_Act_W   = fopen("Data/Annonceurs_Active.txt","w") ;
        FILE *Ann_Arch_W  = fopen("Data/Annonceurs_Archive.txt","w");
        FILE *Dem_Act_W   = fopen("Data/Demandes_Active.txt","w")   ;
        FILE *Dem_Arch_W  = fopen("Data/Demandes_Archive.txt","w")  ;
        FILE *Off_Act_W   = fopen("Data/Offres_Active.txt","w")     ;
        FILE *Off_Sup_W   = fopen("Data/Offres_Supprimes.txt","w")  ;

        /* End ouverture des fichiers */

        /* Start printing in files */

        Print_Annonceurs_file   ( Ann_Act_W , List_Annonceurs_Active )   ;
        Print_Annonceurs_file   ( Ann_Arch_W , List_Annonceurs_Archive ) ;
        Print_Offres_file       ( Off_Act_W , List_Offres_Actives )      ;
        Print_Offres_file       ( Off_Sup_W , List_Offres_Suppr )        ;
        print_Demande_file      ( Dem_Act_W , List_Demandes_Active)      ;
        print_Demande_file      ( Dem_Arch_W , List_Demandes_Archives )  ;

        /* End printing in files */

        /* Start Closing files */
        
        fclose(Ann_Act_W);
        fclose(Ann_Arch_W);
        fclose(Dem_Act_W);
        fclose(Dem_Arch_W);
        fclose(Off_Act_W);
        fclose(Off_Sup_W);
        
        /* End Closing files */
    }


    /* Start Liberation des Listes */
    {
        Liberer_Liste_Annonceur(&List_Annonceurs_Active);
        Liberer_Liste_Annonceur(&List_Annonceurs_Archive);
        Liberer_Liste_Offres(&List_Offres_Actives);
        Liberer_Liste_Offres(&List_Offres_Suppr);
        Liberer_Liste_Annonce(&List_Demandes_Active);
        Liberer_Liste_Annonce(&List_Demandes_Archives);
    }
    /* End Liberation des Listes */

    BYE_BYE();

}