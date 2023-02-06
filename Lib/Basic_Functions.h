#ifndef _Basic_Functions_
#define _Basic_Functions_

//_____________________________________________________________________________________________________________________

/* Start Basic Functions */

int Num_digits (int a);
int Frequ_dig (int N,int D);
int Power (int a,int b);
int Which_Dig (int a,int P);
int Uniqu_dig(int a);
char *Uniqu_str ( char String [] );
char max_char ( char *string );
char min_char ( char *string );
void Remove_char_str ( char *string , int pos );
void Remove_Entree ( char *string );
void Lower_str ( char *str ); 
int Nom_ID ( char nom[] );
char *Name ( char *Nom_A );
char *Norm ( char *string , int command );
int Check_Mail ( char *Mail );
void Animate_str ( char* string , int time );

/* End Basic Functions */

//_____________________________________________________________________________________________________________________

typedef struct Langue
{
    char Language [ 15 ];
    int Ind;
} Langue ;
typedef struct Diploma
{
    char Diploma [25];
    int Ind;
} Diploma ;
typedef struct Comptences
{
    char Compet [40];
    char Ind;
} Comptences ;

//_____________________________________________________________________________________________________________________

/* Start Dealing With languages */

void Get_Langue ( Langue Languages [ 7 ] );
void Print_Languages_Box ( Langue *LG );
char *Print_Languages ( int LG );

/* End Dealing with languages */

//_____________________________________________________________________________________________________________________

/* Start Dealing woth Diplomas */

void Get_Diploma ( Diploma Diplomas [7] );
void Print_Diploma_Box ( Diploma *DP );
char *Print_Diploma ( int D );

/* End Dealing with Diplomas */

//_____________________________________________________________________________________________________________________

/* Start Dealing with Competences */

void Get_Competences ( Comptences Comp[17] );
void Print_Competences_Box ( Comptences *CP );
char *Print_Competences ( char *List );

/* End dealing with competences */

//_____________________________________________________________________________________________________________________

/* Start Dealing with Dates */

void Get_Date ( int Aff  , int Dat[3] , char *Error );
void print_date ( int Date[] );
int Compare_Dates ( int Ref [3] , int Date [3] );

/* End dealing with dates */

//_____________________________________________________________________________________________________________________


#endif