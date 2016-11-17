#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "lib2016BNSF.h"
#include "admin.h"

int main()
{
 char Choix ;
 char Tampon[80] ;
 int res ;
 struct Seance  UnRecord ;
 int Numero, reference ;

 while(1)
 {
  printf("----------------------\n") ;
  printf("1) Ajout              \n") ;
  printf("2) Seances              \n") ;
  printf("3) Recherche          \n") ;
  printf("4) Achat              \n") ;
  printf("5) Factures           \n") ;
  printf("6) A propos           \n") ;
  printf("7) exit               \n") ;
  printf("----------------------\n") ;
  fflush(stdin);
  Choix=ReadChar() ;
  switch(Choix)
  {
   case '1':
             {
              struct Seance  UnRecord ;
 	     FILE *sortie ;
             char Redo ;

             Redo='y' ;
 	    while ( Redo=='Y' || Redo=='y')
 	    {
  		SaiSieRecord(&UnRecord ) ;
  		CreationAjoutFichier("Seances",&UnRecord) ;
  		printf("Encoder un autre (Y/N) ?)") ;
  		Redo=ReadChar() ;
 	   }

	     break ;
             }
   case '2': Listing("Seances") ;
             break ;
   case '3':   printf("Entrez la reference du film: \t");
               scanf("%d", &reference);
               system("clear");
               RechercheBNSF("Seances",reference ,&UnRecord);
               break;

   case '5': ListingFacture("Facture") ;
	     break ;
   case '6': APropos("V 1","Bonemme","Nicolas", "Symar", "Floryan") ;
             break ;


   case '7': exit(0);
   break;
    }
  }
}
