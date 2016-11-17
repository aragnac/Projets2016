#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "lib2016BNSF.h"

void APropos(char *Version,char *Nom1,char* prenom1, char* Nom2, char* prenom2)
{
 printf("Version : %s \n",Version ) ;
 printf("Nom1 Prenom1 : %s %s\n",Nom1, prenom1 ) ;
 printf("Nom2 Prenom2: %s %s\n",Nom2, prenom2 ) ;
}

int RechercheBNSF(char* NomFichier,int Reference ,struct Seance *UneSeance)
{
   FILE *fp ;
   int trouve = 0;
   int i = 1;

   fp = fopen(NomFichier,"r") ;
   if ( fp == NULL )
   {
      fprintf(stderr,"Log: Echec Ouverture fichier\n") ;
      return(0);
   }
   else fprintf(stderr,"Log: Ouverture fichier reussie \n") ;

   while(trouve !=1 && fread(UneSeance, sizeof(struct Seance), 1, fp) != 0){
      if(UneSeance->Reference == Reference){
         printf("Log: Record lu 1 et position actuelle dans le fichier %ld\n",ftell(fp));
         printf("%d \t Terminator%d \t\t\t 100 \t %s\n", i, i, UneSeance->Genre);
         trouve = 1;
      }
   }
   if(trouve != 0)
   {
      fclose(fp);
      return 1;
   }
   else
   {
      fclose(fp) ;
      return 0;
   }
}
