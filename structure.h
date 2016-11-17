
enum TypeRequete {
   Question = 1 ,
   Reponse  = 2,
   Livraison= 3 ,
   OK = 4,
   Fail = 5,
   Achat = 2
} ;

struct Requete
{
   enum TypeRequete Type ;
   char Message[40] ;
   int Numero ;
   int NumeroFacture ;
   char Date[10] ;
   int Reference ;
   int Places ;
   int Prix ;
   int Salle;
   char Film[80] ;
   char NomClient[80] ;
   char Genre[40];
} ;
