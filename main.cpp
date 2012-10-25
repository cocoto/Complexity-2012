#include "algo2.cpp"
#include "algo1.cpp"
#include "algo3.cpp"
#include "generateur.cpp"
#include "fonction_temps.cpp"
#include <fstream>

int main(int argc, char *argv[]){
  
  //Déclaration des variables
  
  int taille=0; //Taille des chaînes (change à chaque paramètre)
  double min; //Temps minimum observé
  double max; //Temps maximum observé
  double sum; //Temps total depuis le début de l'execution (par paramètre)
  double time;//Temps d'une execution
  int cpt;    //Compteur de génération
  char* S=NULL; //Chaîne à comparer
  char* T=NULL; //Idem
  int (*pfonction)(char*,char*,const int &); //Pointeur de fonction (algo1,2,3)
  std::ifstream fichier;	//Pointeur du fichier en cour de lecture (paramètre)
  int ligne_courante=0;		//Second curseur (virtuel) dans le fichier
  bool sortie;			//Condition de sortie de boucle en lecture de fichier
  int cpt_argument=2;		//Compteur de l'argument en cours de lecture
  int facteur;       		//On répète facteur fois le même test entre le début et la fin du chronomètre, pour obtenir un temps >1ms
  
  //Attribution de l'algorithme en fonction du premier paramètre (1,2,3)
  switch (atoi(argv[1])){
    case 1 : pfonction=&algo1;break;
    case 2 : pfonction=&algo2;break;
    case 3 : pfonction=&algo3;break;
    default : std::cout<<"Algorithm "<<atoi(argv[1])<<" does not exist !\n"; return 0;break;
  }

  //On parcourt chaque argument (demande de jeux de tests)
  while(cpt_argument<argc)
	{
	  
	  //INITIALISATION DES VARIABLES
	  cpt=0;
	  min=200000000; //min doit être plus grand que 3minutes (en ms)
	  max=-1;	//Valeur impossible (min=0)
	  time=0;
	  sum=0;
	  sortie=false;
	  //Si la taille est passée en paramètre (génération aléatoire)
	  if(atoi(argv[cpt_argument])!=0)
	  {
	    taille=atoi(argv[cpt_argument]);
		
	    //Génération aléatoire
	    S=random_generate(taille,cpt);
	    T=random_generate(taille,cpt+1);
	    facteur=1;
	    
	    /*
	     * Boucle déterminant le facteur minimum à appliquer pour obtenir des chronométrages >1ms
	     */
	    do{	
		    //Lancement du chronomètre
		    crono_start();
		    for(int i=0;i<facteur;i++)
		    {
		      //On effectue facteur fois la résolution
		      (*pfonction)(S,T,taille);
		    }
		    crono_stop();
		    //Si le temps de résolution est inférieur à 5ms, on multiplie par 10 le facteur
		    if(crono_ms()<5)
		    {
			facteur*=10;
		    }
	    }
	    while(crono_ms()<5);
	    /*
	     * Fin de la boucle de recherche de facteur
	     */
	    
	    
	    
	    //On génère des chaînes aléatoires jusqu'à 3 minutes de temps total de résolution
	      while(sum<180*1000)
	      {
		//Génération aléatoire
		S=random_generate(taille,cpt);
		T=random_generate(taille,cpt+1);

		//Lancement du chronomètre
		crono_start();
		for(int i=0;i<facteur;i++)
		{
		 (*pfonction)(S,T,taille);
		}
		crono_stop();

	
		//Mise à jour des statistiques
		time=crono_ms();
		sum+=time;
		if(time>max)
		{
		  max=time;
		}
		if(time<min)
		{
		  min=time;
		}
		cpt+=2; //Voir fonction random_generate pour plus de détails
	
		//Libération de S et T (cf random_generate)
		free(S);
		free(T);
	  	}
	}//boucle d'argument===taille
	
	
	  //Sinon, si un fichier est passé en paramètre
	  else
	  {
	    //Ouverture du fichier
	    fichier.open(argv[cpt_argument]);
	    //Contrôle de l'ouverture
	    if(fichier)
	    {
	      //Récupération de la taille des chaînes en première ligne
	      fichier>>taille;
	      
	      
	      S=(char*)malloc(taille*sizeof(char));
	      S[0]=' ';
	      T=(char*)malloc(taille*sizeof(char));
	      T[0]=' ';
	      
	      //Récupération de la première chaine
	      fichier>>&S[1];
	      
	      //Sauvegarde de la position (curseur virtuel)
	      ligne_courante=fichier.tellg();
	      
	      //Recopie de S dans T pour la première comparaison
	      strcpy(T,S);
		
	      
	      /*
	       * Détermination du facteur minimum
	       */
		facteur=1;
		do{	
			crono_start();
			for(int i=0;i<facteur;i++)
			{
			 (*pfonction)(S,T,taille);
			}
			crono_stop();
			//std::cout<<"facteur="<<facteur<<" crono="<<crono_ms()<<"\n";//@DEBUG
			if(crono_ms()<5)
			{
			    facteur*=10;
			}
		}
		while(crono_ms()<5);
		
		
		//Tant que toutes les chaînes n'ont pas été parcourues
		while(!sortie)
		{
		    //On résoud toutes les paires possibles du fichier
		    //Si le pointeur de "T" arrive à la fin du fichier
		    if(fichier.eof())
		    {
		      //On avance S d'une ligne
		      fichier.clear();
		      fichier.seekg(ligne_courante);
		      fichier>>&S[1];
		      strcpy(T,S);
		      //Condition d'arrêt du programme : les pointeurs S et T sont à la fin du fichier
		      if(fichier.eof())
		      {
			sortie=true;break;
		      }
		      //On repart à partir de la ligne suivante
		      ligne_courante=fichier.tellg();
		    }
			
		      //Résolution
		      crono_start();
			for(int i=0;i<facteur;i++)
			{
		          (*pfonction)(S,T,taille);
			}
		      crono_stop();
		      
		      
		      //Mise à jour des statistiques
		      time=crono_ms();
		      sum+=time;
		      if(time>max)
		      {
			max=time;
		      }
		      if(time<min)
		      {
			min=time;
		      }
		      cpt+=2;
		      fichier>>&T[1];
		}
		
		//On libère S et T uniquement à la fin
		free(S);
		free(T);
		fichier.close();
	    } 
	    else //ERREUR D'OUVERTURE DE FICHIER
	    {
	       std::cout<<"Wrong file input !\n";
	       return 0;
	    }    
	  }//boucle d'argument===fichier
	    
	    //Impression des statistiques
	    std::cout<<"******************\ntaille = "<<taille<<"\nminimum="<<min<<"ms \nmaximum="<<max<<"ms \nmoyen="<<sum/(cpt/2)<<"ms \ntotal="<<sum<<"ms \nnb_tests="<<cpt/2<<" \nfacteur="<<facteur<<"\n******************\n\n";
	    cpt_argument++;
	
	  
	}//Boucle sur les arguments
	
	return 0;
}//main
