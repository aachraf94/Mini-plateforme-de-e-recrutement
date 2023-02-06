#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include "Display.h"
#include "EMPLOI_LLC_BIBLIO.h"
#include "Basic_Functions.h"

//_____________________________________________________________________________________________________________________

int Num_digits (int a)
{
    /* 
    Input   : Integer A
    Output  : Number of digits of the number A
    */
    int N=0;
    int Num=a;
    while (Num>0)
    {
        N++;
        Num=Num/10;
    }
    return N;   
}
int Frequ_dig (int N,int D)
{
    /*
    Input   : Intger A , Integer D
    Output  : The frequency of apparition of the digit D in the number A
    */
    int A=0;
    int Num=N;
    while (Num>0)
    {
        if (Num%10==D)
        {
            A++;
        }
        Num=Num/10;
    }
    return A;
}
int Power (int a,int b)
{
    /*
    Input   : Integer A , Integer B
    Outout  : Integer A to the power B
    */
    int P;
    P=1;
    for (int i = 1;i<=b;i++)
    {
        P=P*a;
    }
    return P;
}
int Which_Dig (int a,int P)
{
    /*
    Input   : Integer A , Integer P
    Output  : Integer : the digit in the position P in the digit A
    */
    int N=0;
    N=a/Power(10,P-1);
    N=N%10;
    return N;
}
int Uniqu_dig(int a)
{
    /*
    Input   : Integer A
    Output  : Integer composed with the digits of A with apparition frequency 1 and Increasing Order
    Ex      : 9658651 ==> 15689
    */
    int res = 0 ;
    int p = 1;
    for ( int i = 9 ; i>0 ; i-- )
    {
        if ( Frequ_dig(a,i) > 0 )
        {
            res += i*p;
            p *= 10;
        }
    }
    return res;
}
char *Uniqu_str ( char String [] )
{
    /*
    Input   : String "String"
    Output  : String composed with the characters of String with apparition frequency 1 and Increasing Order
    Ex      : regrag ==> aegr
    */
    int i = 0;
    static char Res[100];
    for (char a = 'a'; a <= 'z'; a++)
    {
        if (strchr(String,a) != NULL)
        {
            Res [i] = a;
            i++;
        }
    }
    Res[i] = '\0';
    return Res;
}
char max_char ( char *string )
{
    /*
    Input   : String string
    Output  : the character with the highest ascii code
    */
    int i = 0;
    char a = string [0];
    while ( string [i] != '\0' )
    {
        if ( string [i]>a )
        {
            a = string[i];
        }
        i++;
    }
    return a;
}
char min_char ( char *string )
{
    /*
    Input   : String string
    Output  : the character with the lowest ascii code
    */
    int i = 0;
    char a = string [0];
    while ( string [i] != '\0' )
    {
        if ( string [i]<a )
        {
            a = string[i];
        }
        i++;
    }
    return a;
}
void Remove_char_str ( char *string , int pos )
{
    /*
    Removes the position pos from the string String
    */
    int i = pos ;
    while ( string [i] != '\0' )
    {
        string [i] = string [i+1];
        i++;
    }
}
void Remove_Entree ( char *string )
{
    /*
    The function fgets used everywhere in this program :) fgets actually scans the \n in the end, so this is made to remove it cuz it bothers at the end when printing especially to files
    */
    int i = 0;
    while ( string [i] != '\0' )
    {
        if ( string [i] == 10 )
        {
            Remove_char_str( string , i );
        }
        i++;
    }   
}
void Lower_str ( char *str )
{
    /* The function strlwr causes some problems, this one has the same role */
    int i = 0;
    while ( str[i] != '\0' )
    {
        str[i] = tolower(str[i]);
        i++;
    }
}
int Nom_ID ( char nom[] )
{ 
    /* 
    - The role of this function is to generate the ID frome the name following a certain combination  
    - The scenario in which the user enters his name in lower cases or upper cases is handled : 
        The use of the function toupper makes the name always in upper cases before generaing ID and this is done for two reasons :
        - The ID of the user remains the same in all cases upper, lower cases or a mix of them
        - The function depends on the ASCII CODE, the use of the upper case is to make the ID a litlle bit smaller 
    */
    int id = 0 , i;
    char temp;
    for (i=0 ; i< strlen(nom) ; i++)
    {
        temp= toupper(nom[i]) ;
        id += (i+1) * temp ;
    }
    return id ;
}
char *Name ( char *Nom_A ) 
{
    /* The role of this function is to capitalize the first letter of the last, middle, first name in the string */
    /* This function is not used only for names, it's used also with other thigs for display and generalizing reasons */
    static char Result[60];
    strcpy(Result,""); 
    /*
    The declaration is static so that the function don't delete the name after the use, and strpy in case of the appending problem 
    */
    int i = 0;
    char Nom[60];
    strcpy(Nom,Nom_A);
    while ( Nom [i] != '\0' )
    {
        if ( (i==0) || ( Nom [i-1] == ' ' ) )
        {
            Result [i] = toupper(Nom [i]);
        }
        else
        {
            Result [i] = tolower(Nom [i]);
        }
        i++;
    }
    Result[i] = Nom[i];
    return Result;

}
char *Norm ( char *string , int command )
{
    /*
    The role of this function is to :
    - if command == 1 : Replace every space with _ in a string
    - if command == 0 : Replace every _ with space in a string
    This is helpful when saving info in a file, cuz without it reading a file would be very challenging and impossible in some cases 
    */
    static char Result [300] ;
    int i = 0;
    if ( command == 1 )
    {
        while ( string[i] != '\0' )
        {
            if ( string[i] == ' ' )
            {
                Result[i] = '_';
            }
            else
            {
                Result[i] = string [i];
            }
            i++;
        }
        Result[i] = string [i];
    }
    else if (command == 0)
    {
        while ( string[i] != '\0' )
        {
            if ( string[i] == '_' )
            {
                Result[i] = ' ';
            }
            else
            {
                Result[i] = string [i];
            }
            i++;
        }
        Result[i] = string [i];
    }
    return Result;
    
}
int Check_Mail ( char *Mail )
{
    /*
    returns 1 if mail is true; 0 if it's false
    -   checks if there's a .
    -   checks if there's a @
    -   checks if there's not a space
    */
    int at = 0;
    int dot = 0;
    int i = 0;
    while ( ( i<strlen(Mail) ) && ( (at == 0) || (dot == 0) ) )
    {
        if ( Mail[i] == '@' )
        {
            at = 1;
        }
        if ( Mail[i] == '.' )
        {
            dot = 1;
        }
        if ( Mail [i] == ' ' )
        {
            return 0;
        }
        i++;
    }
    if ( at + dot == 2 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Animate_str ( char* string , int time )
{
    /*
        This function animates a string :
        -   if time = 0 it uses the default sleeping timer value
        -   if time has a value other than 0 it uses that value as sleeping timer value
    */
    int num;
    if ( time == 0 )
    {
        num = 30000;
    }
    else
    {
        num = time;
    }
    for ( int i = 0 ; i<=strlen(string) ; i++ )
    {
        printf("%c",string[i]);
        usleep(num);
    }
}

//_____________________________________________________________________________________________________________________

/* Start Dealing With languages */

/* the Languages are used with an array of diplomas of 7 elements */

void Get_Langue ( Langue Languages [ 7 ] )
{
    /*
    This fills the Languages Table with the language and their index
    */
    Languages[0].Ind = 1;
    Languages[1].Ind = 2;
    Languages[2].Ind = 3;
    Languages[3].Ind = 4;
    Languages[4].Ind = 5;
    Languages[5].Ind = 6;
    Languages[6].Ind = 7;
    strcpy(Languages[0].Language,"Anglais");
    strcpy(Languages[1].Language,"Francais");
    strcpy(Languages[2].Language,"Arabe");
    strcpy(Languages[3].Language,"Espaniol");
    strcpy(Languages[4].Language,"Portugais");
    strcpy(Languages[5].Language,"Allemand");
    strcpy(Languages[6].Language,"Russe");
}
void Print_Languages_Box ( Langue *LG )
{
    /*
    This function prints the languages in a box : for the user to choose the languages 
    */
    printf("\n\t\t\t__________________________________\n");
    printf("\t\t\t| %s----------------------%d |\n",LG[0].Language,LG[0].Ind);
    printf("\t\t\t| %s---------------------%d |\n",LG[1].Language,LG[1].Ind);
    printf("\t\t\t| %s------------------------%d |\n",LG[2].Language,LG[2].Ind);
    printf("\t\t\t| %s---------------------%d |\n",LG[3].Language,LG[3].Ind);
    printf("\t\t\t| %s--------------------%d |\n",LG[4].Language,LG[4].Ind);
    printf("\t\t\t| %s---------------------%d |\n",LG[5].Language,LG[5].Ind);
    printf("\t\t\t| %s------------------------%d |\n",LG[6].Language,LG[6].Ind);
    printf("\t\t\t|________________________________|\n");
}
char *Print_Languages ( int LG )
{
    /*
    This function prints the languages that are contained in the code LG into a string, they are separated by ","
    */
    static char Res [100];
    strcpy(Res,"");
    Langue Languages [7];
    Get_Langue (Languages);
    for ( int i = 1 ; i<=7 ; i++ )
    {
        
        if ( Frequ_dig(LG,i) != 0 )
        {
            strcat( Res , Languages[i-1].Language);
            strcat( Res , " , ");
        }
    }
    Res [ strlen(Res) - 3 ] = '\0';
    return Res;
}

/* End Dealing with languages */

//_____________________________________________________________________________________________________________________

/* Start Dealing woth Diplomas */

/* the diplomas are used in an array of diplomas of 6 elements */

void Get_Diploma ( Diploma Diplomas [7] )
{
    /*
    This fills the Diplomas Table with the Diplomas and their index
    */
    Diplomas[0].Ind = 1;
    Diplomas[1].Ind = 2;
    Diplomas[2].Ind = 3;
    Diplomas[3].Ind = 4;
    Diplomas[4].Ind = 5;
    Diplomas[5].Ind = 6;
    Diplomas[6].Ind = 7;
    strcpy(Diplomas[0].Diploma,"Technicien Superieur");
    strcpy(Diplomas[1].Diploma,"Lissance");
    strcpy(Diplomas[2].Diploma,"Master");
    strcpy(Diplomas[3].Diploma,"Ingenieur");
    strcpy(Diplomas[4].Diploma,"Docteur");
    strcpy(Diplomas[5].Diploma,"Professeur");
    strcpy(Diplomas[6].Diploma,"Aucun");
}
void Print_Diploma_Box ( Diploma *DP )
{
    /*
    This function prints the Diplomas in a box : for the user to choose the diplomas 
    */
    printf("\n\t\t_______________________________________________\n");
    printf("\t\t| %s ---------------------%d |\n",DP[0].Diploma,DP[0].Ind);
    printf("\t\t| %s ---------------------------------%d |\n",DP[1].Diploma,DP[1].Ind);
    printf("\t\t| %s -----------------------------------%d |\n",DP[2].Diploma,DP[2].Ind);
    printf("\t\t| %s --------------------------------%d |\n",DP[3].Diploma,DP[3].Ind);
    printf("\t\t| %s ----------------------------------%d |\n",DP[4].Diploma,DP[4].Ind);
    printf("\t\t| %s -------------------------------%d |\n",DP[5].Diploma,DP[5].Ind);
    printf("\t\t|\t\t\t\t\t      |\n");
    printf("\t\t| %s ------------------------------------%d |\n",DP[6].Diploma,DP[6].Ind);
    printf("\t\t|_____________________________________________|\n");
}
char *Print_Diploma ( int D )
{
    /*
    This function prints the diplomas that are contained in the code DP into a string, they are separated by ","
    */
    static char Res [25];
    strcpy(Res,"");
    Diploma Diplomes [7];
    Get_Diploma(Diplomes);
    if ( D == 7 )
    {
        strcpy( Res , " Aucun " );
    }
    else
    {
        strcpy( Res , Diplomes[D-1].Diploma );
    }
    return Res;
}

/* End Dealing with Diplomas */

//_____________________________________________________________________________________________________________________

/* Start Dealing with Competences */

/* the Competences are used with an array of competences of 16 elements */

void Get_Competences ( Comptences Comp[17] )
{
    /*
    This fills the competences Table with the competences and their index
    */
    Comp[0].Ind = 'a';
    Comp[1].Ind = 'b';
    Comp[2].Ind = 'c';
    Comp[3].Ind = 'd';
    Comp[4].Ind = 'e';
    Comp[5].Ind = 'f';
    Comp[6].Ind = 'g';
    Comp[7].Ind = 'h';
    Comp[8].Ind = 'i';
    Comp[9].Ind = 'j';
    Comp[10].Ind = 'k';
    Comp[11].Ind = 'l';
    Comp[12].Ind = 'm';
    Comp[13].Ind = 'n';
    Comp[14].Ind = 'o';
    Comp[15].Ind = 'p';
    Comp[16].Ind = 'q';
    strcpy(Comp[0].Compet,"Developpement des Logiciels");
    strcpy(Comp[1].Compet,"Developpement Mobile");
    strcpy(Comp[2].Compet,"Developpement Web");
    strcpy(Comp[3].Compet,"Securite des Reseaux");
    strcpy(Comp[4].Compet,"Administration des Bases de Donnees");
    strcpy(Comp[5].Compet,"Administration Reseau");
    strcpy(Comp[6].Compet,"Systemes d'Information");
    strcpy(Comp[7].Compet,"Data Analysis");
    strcpy(Comp[8].Compet,"Cloud Computing");
    strcpy(Comp[9].Compet,"Genie Logiciel");
    strcpy(Comp[10].Compet,"Media Sociaux");
    strcpy(Comp[11].Compet,"Big Data");
    strcpy(Comp[12].Compet,"Machine Learning");
    strcpy(Comp[13].Compet,"Cybersicurite");
    strcpy(Comp[14].Compet,"Blockchain");
    strcpy(Comp[15].Compet,"Business Intelligence");
    strcpy(Comp[16].Compet,"Aucune");
}
void Print_Competences_Box ( Comptences *CP )
{
    /*
    This function prints the competences in a box : for the user to choose the competences 
    */
    printf("\n\t\t________________________________________________\n");
    printf("\t\t| %s ---------------%c |\n",CP[0].Compet,CP[0].Ind);
    printf("\t\t| %s ----------------------%c |\n",CP[1].Compet,CP[1].Ind);
    printf("\t\t| %s -------------------------%c |\n",CP[2].Compet,CP[2].Ind);
    printf("\t\t| %s ----------------------%c |\n",CP[3].Compet,CP[3].Ind);
    printf("\t\t| %s -------%c |\n",CP[4].Compet,CP[4].Ind);
    printf("\t\t| %s ---------------------%c |\n",CP[5].Compet,CP[5].Ind);
    printf("\t\t| %s --------------------%c |\n",CP[6].Compet,CP[6].Ind);
    printf("\t\t| %s -----------------------------%c |\n",CP[7].Compet,CP[7].Ind);
    printf("\t\t| %s ---------------------------%c |\n",CP[8].Compet,CP[8].Ind);
    printf("\t\t| %s ----------------------------%c |\n",CP[9].Compet,CP[9].Ind);
    printf("\t\t| %s -----------------------------%c |\n",CP[10].Compet,CP[10].Ind);
    printf("\t\t| %s ----------------------------------%c |\n",CP[11].Compet,CP[11].Ind);
    printf("\t\t| %s --------------------------%c |\n",CP[12].Compet,CP[12].Ind);
    printf("\t\t| %s -----------------------------%c |\n",CP[13].Compet,CP[13].Ind);
    printf("\t\t| %s --------------------------------%c |\n",CP[14].Compet,CP[14].Ind);
    printf("\t\t| %s ---------------------%c |\n",CP[15].Compet,CP[15].Ind);
    printf("\t\t|\t\t\t\t\t       |\n");
    printf("\t\t| %s ------------------------------------%c |\n",CP[16].Compet,CP[16].Ind);
    printf("\t\t|______________________________________________|\n");

}
char *Print_Competences ( char *List )
{
    /*
    This function prints the competences that are contained in the code List into a string, they are separated by ","
    */
    static char Res [ 200 ];
    strcpy(Res,"");
    Comptences Comp [17];
    char *Base = "abcdefghijklmnopq"; 
    Get_Competences (Comp);
    int i = 0;
    while ( List [i] != '\0' )
    {
        int j = 0;
        while ( (Base[j] != '\0') && (Base [j] != List[i]) )
        {
            j++;
        }
        strcat(Res,Comp[j].Compet);
        strcat(Res," , ");
        i++;
    }
    Res [ strlen(Res) - 3 ] = '\0';
    return Res;
}

/* End dealing with competences */

//_____________________________________________________________________________________________________________________

/* Start Dealing with Dates */

/*
Dates are represented like this : jj , mm , yyyy
In a array of integer of 3 elements : days , months , years
*/

void Get_Date ( int Aff  , int Dat[3] , char *Error ) 
{
    /*
    This function reads the date :
                                -   If Aff = 1 it displays : Entrez la date sous la forme jj mm aaaa :
                                -   In case of some error, it displays the Error String

    The loop is mastered by the variable bool; this variable is initialised in the beggining to value 0;
    if there's an error case, it receives the value 1;
    error cases treated here :
    - days or months have no negative values
    - the year is after 1950 and before 2100
    - Months : 1,3,5,7,8,10,12 have 31 days
    - Months : 4,6,9,11 have 30 days
    - february has 28 days
    - february has 29 days once in 4 years : the y%4 condition
    */
    int bool;
    int d = 0, m = 0 , y = 0 ;
    do
    {
        bool = 0;
        if ( Aff == 1 )
        {
            printf("Entrez la date sous la forme jj mm aaaa : ");
        }
        char Date [20];
        fgets(Date,20,stdin);
        sscanf(Date,"%d %d %d",&d,&m,&y);
        
        if ( ( d<1 ) || ( d>31 ) || ( m<1 ) || (m>12) || (y<1950) || (y>2100) )
        {
            bool = 1;
        }
        else
        {
            if ( ( m==2 ) && ( ( d>28 ) && ( ( d>29 ) || (  ( y%4 )!=0 ) ) ) ) 
            {
                bool = 1;
            }
            else
            {
                if ( ( d>30 ) && ( ( m==4 ) || ( m==6 ) || ( m==9 ) || ( m==11 ) ) )
                {
                    bool = 1;
                }
            }
        }

        if ( (bool == 1) && ( strcmp(Error,"") != 0 ) )
        {
            printf("%s",Error);
        }

    } while ( bool == 1 );
    Dat [0] = d ;
    Dat [1] = m ;
    Dat [2] = y ;
}
void print_date ( int Date[] )
{
    /*
    This function is to print the date : 
    the day     : if day < 10 print the zero next to the day
    the month   : prints the month January , February ...
    */
    if ( Date[ 0 ] < 10 )
    {
        printf("0%d",Date[0]);
    }
    else
    {
        printf("%d",Date[0]);
    }
    switch (Date [1])
    {
    case 1:
        printf(" Janvier ");
        break;
    case 2:
        printf(" Fevrier ");
        break;
    case 3:
        printf(" Mars ");
        break;
    case 4:
        printf(" Avril ");
        break;
    case 5:
        printf(" Mai ");
        break;
    case 6:
        printf(" Juin ");
        break;
    case 7:
        printf(" Juillet ");
        break;
    case 8:
        printf(" Aout ");
        break;
    case 9:
        printf(" Sepembre ");
        break;
    case 10:
        printf(" Octobre ");
        break;
    case 11:
        printf(" Novembre ");
        break;
    case 12:
        printf(" Decembre ");
        break;
    default:
        break;
    }
    printf("%d",Date[2]);
}
int Compare_Dates ( int Ref [3] , int Date [3] ) 
{
    /*
    Return  0 if dates are equal
            -1 if Date before Ref
            1 if Date after Ref 
    */
    if ( Date [ 2 ] > Ref [ 2 ] )
    {
        return 1;
    }
    else
    {
        if ( Date [ 2 ] < Ref [ 2 ] )
        {
            return -1;
        }
        else  // at this point years are the same
        {
            if ( Date [ 1 ] > Ref [ 1 ] )
            {
                return 1;
            }
            else
            {
                if ( Date [ 1 ] < Ref [ 1 ] )
                {
                    return -1;
                }
                else  // at this point both years and months are the same
                {
                    if ( Date [ 0 ] > Ref [ 0 ] )
                    {
                        return 1;
                    }
                    else
                    {
                        if ( Date [ 0 ] < Ref [ 0 ] )
                        {
                            return -1;
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

/* End dealing with dates */

//_____________________________________________________________________________________________________________________