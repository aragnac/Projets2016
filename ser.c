/*--------------------------------------
  Herman Vanstapel

  ex02\ser.c

  Un serveur recevant une structure
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "structure.h"
#include "data.h"
#include "lib2016BNSF.h"
#include "admin.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc,char *argv[])
{
  int rc ;
  int Desc ;
  int trouve;
  struct sockaddr_in sthis; /* this ce programme */
  struct sockaddr_in sos; /* s = serveur */
  struct sockaddr_in sor; /* r = remote */
  struct Requete UneRequete;
  struct Seance Rec;
  u_long  IpSocket;
  u_short PortSocket;

  memset(&sthis,0,sizeof(struct sockaddr_in)) ;
  memset(&sos,0,sizeof(struct sockaddr_in)) ;
  memset(&sor,0,sizeof(struct sockaddr_in)) ;

  printf("Ceci est le serveur\n") ;
  if ( argc!=3)
  {
    printf("ser ser port cli\n") ;
    exit(1) ;
  }

  /* 
  *----------------Récupération IP & port------------------- 
  */
  IpSocket= inet_addr(argv[1]);
  PortSocket = atoi(argv[2]);
  // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
  Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);

   if ( Desc == -1 )
      die("Log CreateSockets:");
   else
      fprintf(stderr,"CreateSockets %d\n",Desc);

  /*
  *----------------------Reception du Datagram----------------
  */
  rc = ReceiveDatagram(Desc,&UneRequete ,sizeof(struct Requete), &sor ) ;
  if ( rc == -1 )
  {
    die("ReceiveDatagram");
    printf("data mort \n");
  }
  else
    fprintf(stderr,"bytes recus:%d:%s\n",rc,UneRequete.Message ) ;

  printf("Type recu %d\n", UneRequete.Type) ;
  /* attention l'enum peut être codé en short */
  /* reponse avec psos */
  UneRequete.Type = Reponse ;
  strcat(UneRequete.Message," Client") ;

  /*
  *----------------------Envoie du Datagram----------------
  */
  rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
  if ( rc == -1 )
    die("SendDatagram:") ;
  else
    fprintf(stderr,"bytes envoyes:%d\n",rc ) ;


  /*
  *------------------------RECHERCHE-----------------------
  */
  trouve = RechercheBNSF("Seances", UneRequete.Reference, &Rec);
  //system("clear");
  if(trouve == 0)
  {
    printf("Cette article est actuellement indisponible !\n\n");
    UneRequete.Type = Fail;
  }
  else
  {
    printf("Ce numero correspond à la séance:\n\n");
    AfficheRecord(&Rec);

   	strcpy(UneRequete.Film, Rec.Film);
   	//strcpy(UneRequete.Genre, Rec.Genre);
   	strcpy(UneRequete.Date, Rec.Date);
   	UneRequete.Places = Rec.Places;
   	UneRequete.Salle = Rec.Salle;

   	UneRequete.Type = Question;
  }
   //UneRequete.Type = Reponse ;
   strcat(UneRequete.Message," Client") ;
   rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
   if ( rc == -1 )
      die("SendDatagram:") ;
   else
     fprintf(stderr,"bytes envoyes:%d\n",rc ) ;

     Rec.Reference = UneRequete.Reference;

   close(Desc) ;
}
