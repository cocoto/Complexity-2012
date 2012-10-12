#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int algo2 ( char* S, char* T,const int& taille){
 
    int max = 0;
    int l , i , j ;
    
    for(l=1; l <= taille ; l++){
        for( i=1 ; i+l-1 <= taille ; i++){
            for( j=1 ; j+l-1 <= taille; j++){
                if(strncmp(&S[i] , &T[j] , l) == 0){
                    max = l;
                }
            }
        }
    
    }
    return max;
 
}