#include <iostream>

int algo1( char* S, char* T,const int &n)
{
   int mlsuff[n][n];
   int i,j,max=0;

  //Initialisation
   
  //n boucles
  for(i=0;i<n;i++)
  {
     mlsuff[i][0]= (S[i]==T[0])?1:0;
  }
  
  //n boucles
  for(j=0;j<n;j++)
  {
     mlsuff[0][j]= (S[0]==T[j])?1:0;
  }
   
   //Création de la matrice
   
   //n-1 boucles
   for(i=1;i<n;i++)
   {
     //n-1 boucles
     for(j=1;j<n;j++)
     {
       
        if(S[i]==T[i])
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
   return max;
}