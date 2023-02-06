#ifndef __Menus__
#define __Menus__

//_____________________________________________________________________________________________________________________

void BYE_BYE ( void );

int Verify_changes( void );

void First_Interface ( );

void Disclaimer_Page ( void );

int Principal_Menu( void );

int Menu_Annonceur ( void );

void Menu_Ann_4 ( Ptr_Maillon_Offre *Liste_act_off , Ptr_Maillon_Offre *Liste_arch_off , Ptr_Maillon_Annonceur Liste_act );

void Menu_Ann_5 ( Ptr_Maillon_Annonceur *Liste_ann_act , Ptr_Maillon_Annonceur *Liste_ann_arch , Ptr_Maillon_Offre *List_off_act , Ptr_Maillon_Offre *List_off_arch  );

int Menu_Demandeur ( void );

void Menu_Dem_3 ( Ptr_Maillon_Annonce *List_act , Ptr_Maillon_Annonce *List_arch );

int Menu_Dev ( void );

int Choix_Dev_1 ( void );

void Choix_Dev_2 ( Ptr_Maillon_Annonce *List_dem_act, Ptr_Maillon_Annonce *List_dem_arch ,Ptr_Maillon_Annonceur *List_ann_act , Ptr_Maillon_Annonceur *List_ann_arch ,  Ptr_Maillon_Offre *List_off_act , Ptr_Maillon_Offre *List_off_arch );

void Choix_Dev_3 ( Ptr_Maillon_Offre Liste , Ptr_Maillon_Annonceur Liste_Ann );

void Choix_Dev_4 ( Ptr_Maillon_Annonceur Liste_Ann , Ptr_Maillon_Annonce Liste_Dem_act , Ptr_Maillon_Annonce Liste_Dem_arch , Ptr_Maillon_Offre Liste_Off_Act , Ptr_Maillon_Offre Liste_Off_Acrh );

void Choix_Dev_5 ( Ptr_Maillon_Offre List_Off , Ptr_Maillon_Annonceur List_Ann );

void Choix_Dev_6 ( Ptr_Maillon_Annonce Liste );

void Choix_Dev_8 ( Ptr_Maillon_Offre List_off , Ptr_Maillon_Annonceur List_ann , Ptr_Maillon_Annonce List_dem );

void Choix_Dev_7 ( Ptr_Maillon_Offre Liste , Ptr_Maillon_Annonceur List_Ann );

void Choix_Dev_9 ( Ptr_Maillon_Offre List );

//_____________________________________________________________________________________________________________________

#endif