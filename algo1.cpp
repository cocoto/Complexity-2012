#include <iostream>

int algo1( char* S, char* T,const int &n)
{
   int** mlsuff=(int**)malloc(n*sizeof(int*));
   int cpt;
   for(cpt=0;cpt<n;cpt++)
   {
	mlsuff[cpt]=(int*)malloc(n*sizeof(int));
   }
   int i,j,max=0;

  //============Initialisation============
   
  //n boucles
  for(i=0;i<n;i++)
  {
     mlsuff[i][0]= (S[i+1]==T[1])?1:0;
  }
  for(j=0;j<n;j++)
  {
     mlsuff[0][j]= (S[1]==T[j+1])?1:0;
  }
   
   //============Création de la matrice========
   
   //n-1 boucles
   for(i=1;i<n;i++)
   {
     //n-1 boucles
     for(j=1;j<n;j++)
     {
       
        if(S[i+1]==T[j+1])
	{
	   mlsuff[i][j]=mlsuff[i-1][j-1]+1;
	}
	else
	{
	   mlsuff[i][j]=0;
	}
     }
   }
   
   //Recherche du maximum
   
   //n boucles
   for(i=0;i<n;i++)
   {
     //n boucles
     for(j=0;j<n;j++)
     {
       if(max<mlsuff[i][j])
       {
	 max=mlsuff[i][j];
       }
     }
   }
   for(cpt=0;cpt<n;cpt++)
   {
	free(mlsuff[cpt]);
   }
   free(mlsuff);
   return max;
}
