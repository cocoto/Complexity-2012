#include "algo2.cpp"
#include "algo1.cpp"
#include "algo3.cpp"
#include "generateur.cpp"
#include "fonction_temps.cpp"
#include <fstream>

int main(int argc, char *argv[]){
  int taille=0;
  double min;
  double max;
  double sum;
  int value;
  double time;
  int cpt;
  char* S=NULL;
  char* T=NULL;
  int (*pfonction)(char*,char*,const int &);
  std::ifstream fichier;
  int ligne_courante=0;
  bool sortie;
  int cpt_argument=2;
  int facteur; //On répète facteur fois le même test entre le début et la fin du chronomètre, pour obtenir un temps >1ms
  
  //Attribution de l'algorithme en fonction du premier paramètre (1,2,3)
  switch (atoi(argv[1])){
    case 1 : pfonction=&algo1;break;
    case 2 : pfonction=&algo2;break;
    case 3 : pfonction=&algo3;break;
    default : std::cout<<"Algorithm "<<atoi(argv[1])<<" does not exist !\n"; return 0;break;
  }

  while(cpt_argument<argc)
	{
	  cpt=0;
	  min=200000000;
	  max=-1;
	  time=0;
	  sum=0;
	  sortie=false;
	  //Si la taille est passée en paramètre (aléatoire)
	  if(atoi(argv[cpt_argument])!=0)
	  {
	    taille=atoi(argv[cpt_argument]);


		//Génération aléatoire
		S=random_generate(taille,cpt);
		T=random_generate(taille,cpt+1);
		facteur=1;
		do{	
			crono_start();
			for(int i=0;i<facteur;i++)
			{
			 (*pfonction)(S,T,taille);
			}
			crono_stop();
			//std::cout<<"facteur="<<facteur<<" crono="<<crono_ms()<<"\n"; //@DEBUG
			if(crono_ms()<5)
			{
			    facteur*=10;
			}
		}
		while(crono_ms()<5);
	    //On génère des chaînes aléatoires jusqu'à 3 minutes de temps total de résolution
	      while(sum<180*1000)
	      {
		//Génération aléatoire
		S=random_generate(taille,cpt);
		T=random_generate(taille,cpt+1);

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
	
		//Décommenter pour débug
		//std::cout<< S <<" et "<< T <<"  =  "<< value << " en "<<time<<"ms total "<<sum/1000<<"s \n";
	
		//Libération de S et T (cf random_generate)
		free(S);
		free(T);
	  	}
	}
	  //Sinon, si un fichier est passé en paramètre
	  else
	  {
	    fichier.open(argv[cpt_argument]);
	    if(fichier)
	    {
	      fichier>>taille;
	      S=(char*)malloc(taille*sizeof(char));
	      S[0]=' ';
	      T=(char*)malloc(taille*sizeof(char));
	      T[0]=' ';
	      fichier>>&S[1];
	      ligne_courante=fichier.tellg();
	      strcpy(T,S);
		
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
		      //Décommenter pour débug
		      //std::cout<< S <<" et "<< T <<"  =  "<< value << " en "<<time<<"ms total "<<sum/1000<<"s \n";
		      fichier>>&T[1];
		}
		
		//On libère S et T uniquement à la fin
		free(S);
		free(T);
		fichier.close();
	    } 
	    else
	    {
	       std::cout<<"Wrong file input !\n";
	       return 0;
	    }    
	  }
	    
	    //Impression des statistiques
	    std::cout<<"******************\ntaille = "<<taille<<"\nminimum="<<min<<"ms \nmaximum="<<max<<"ms \nmoyen="<<sum/(cpt/2)<<"ms \ntotal="<<sum<<"ms \nnb_tests="<<cpt/2<<" \nfacteur="<<facteur<<"\n******************\n\n";
	    cpt_argument++;
	}
}
