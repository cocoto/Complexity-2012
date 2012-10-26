#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int algo2 ( char* S, char* T,const int& taille){
 
    int max = 0; // initialisation de variable maximum
    int l , i , j ; // déclaration des variables de compteurs
    
    for(l=1; l <= taille ; l++){ //traitement de toutes les tailles
        for( i=1 ; i+l-1 <= taille ; i++){ //choix de chaque chaine de taille l dans S
            for( j=1 ; j+l-1 <= taille; j++){ //choix de chaque chaine de taille l dans T
                if(strncmp(&S[i] , &T[j] , l) == 0){ // si les deux sous chaines sont identiques
                    max = l; //le max devient  l
                }
				//on passe à la paire suivante
            }
        }
    
    }
    return max; //on renvoie le max
 
}