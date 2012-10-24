#include "algo2.cpp"
#include "algo1.cpp"
#include "algo3.cpp"
#include "generateur.cpp"
#include "fonction_temps.cpp"
#include <fstream>

int main(int argc, char *argv[]){
  (void) argc;
  int taille=0;
  double min=9000;
  double max=-1;
  double sum=0;
  int value;
  double time=0;
  int cpt=0;
  char* S=NULL;
  char* T=NULL;
  int (*pfonction)(char*,char*,const int &);
  int ligne_courante=0;
  bool sortie=false;
  std::ifstream fichier(argv[2]);
  
  //Attribution de l'algorithme en fonction du premier paramètre (1,2,3)
  switch (atoi(argv[1])){
    case 1 : pfonction=&algo1;break;
    case 2 : pfonction=&algo2;break;
    case 3 : pfonction=&algo3;break;
    default : std::cout<<"Algorithm "<<atoi(argv[1])<<" does not exist !\n"; return 0;break;
  }
  //Si la taille est passée en paramètre (aléatoire)
  if(atoi(argv[2])!=0)
  {
    taille=atoi(argv[2]);
  }
  //Sinon, si un fichier est passé en paramètre
  else
  {
    if(fichier)
    {
      fichier>>taille;
      S=(char*)malloc(taille*sizeof(char));
      S[0]=' ';
      T=(char*)malloc(taille*sizeof(char));
      T[0]=' ';
      fichier>>&S[1];
      strcpy(T,S);
      ligne_courante=fichier.tellg();
    } 
    else
    {
       std::cout<<"Wrong file input !\n";
       return 0;
    }    
  }
    //Si le second argument est un chiffre (n)
   if(atoi(argv[2])!=0)
    {
      //On génère des chaînes aléatoires jusqu'à 3 minutes de temps total de résolution
      while(sum<180*1000)
      {
	//Génération aléatoire
	S=random_generate(taille,cpt);
	T=random_generate(taille,cpt+1);
	
	//Résolution
	crono_start();
	//for(int i=0;i<50000;i++)
	//{
	value=(*pfonction)(S,T,taille);
	//}
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
    else
    {
	//Si nous passons un fichier en paramètre
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
		//for(int i=0;i<100000;i++)
		//{
		  value=(*pfonction)(S,T,taille);
		//}
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
	      std::cout<< S <<" et "<< T <<"  =  "<< value << " en "<<time<<"ms total "<<sum/1000<<"s \n";
	      fichier>>&T[1];
	}
	
	//On libère S et T uniquement à la fin
	free(S);
	free(T);
    }
    
    //Impression des statistiques
    std::cout<<"minimum="<<min<<"ms maximum="<<max<<"ms moyen="<<sum/(cpt/2)<<"ms total="<<sum<<"ms nb_tests="<<cpt/2<<"\n";
  }
