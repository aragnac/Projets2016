/*---------------------------------------------------------------
   Vanstapel Herman
   ex02\cli.c

 Le client dit bonjour en utilisant un structure  et
 le serveur fait de même
------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "structure.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
 int rc ;
 int Desc;
 int reference; 
 
 u_long  IpSocket , IpServer;
 u_short PortSocket, PortServer ; 
 
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */
 struct Requete UneRequete ;

 memset(&sthis,0,sizeof(struct sockaddr_in)) ;
 memset(&sos,0,sizeof(struct sockaddr_in)) ; 
 memset(&sor,0,sizeof(struct sockaddr_in)) ; 
 
  if (argc!=5)
  {
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
  }
 
 /*
 *---------Récupération IP & port------------------ 
 */
 IpSocket= inet_addr(argv[1]);
 PortSocket = atoi(argv[2]);
 
 IpServer = inet_addr(argv[3]) ;
 PortServer = atoi(argv[4]);
 
 // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
 Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);
 
 if ( Desc == -1 )
    die("CreateSockets:") ; 
 else
    fprintf(stderr,"CreateSockets %d\n",Desc) ;
 
  sos.sin_family = AF_INET ;
  sos.sin_addr.s_addr= IpServer ;
  sos.sin_port = htons(PortServer) ;

 
 UneRequete.Type = Question ; 
 strncpy(UneRequete.Message , "LOG : Avec une structure: Bonjour" , sizeof(UneRequete.Message));


  /*----------------Demande du num de la seance-------------*/
  printf("Entrez le numero de la séance que vous cherchez:\t");
  scanf("%d",&reference);
  UneRequete.Reference = reference;
 
  /*
  *----------------------Envoie du Datagram----------------
  */
  rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sos ) ;

  if ( rc == -1 )
    die("SendDatagram");
  else
    fprintf(stderr,"LOG : Envoi de %d bytes\n",rc ) ;
 
  memset(&UneRequete,0,sizeof(struct Requete));
  printf("after memset");
 
  /*
  *----------------------Reception du Datagram----------------
  */
  rc = ReceiveDatagram( Desc, &UneRequete,sizeof(struct Requete), &sor);
  
  if ( rc == -1 )
    die("ReceiveDatagram");
  else
    fprintf(stderr,"LOG : bytes recus:%d:%s \n",rc,UneRequete.Message );
  if(UneRequete.Type = Fail)
  {
    printf("Ce numero de seance ne correspond à aucun film");
  }
  else
  {
    printf("Ce numero de seance correspond à la seance :\n");
    printf("Film : %s",UneRequete.Film);
  }
 
  close(Desc) ;
}
