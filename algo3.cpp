int algo3 ( char* S, char* T,const int& taille){
 
    int i, j , a , b , sij;
    int max = 0;
    bool boolres;
    char* PMK;
    for(i=1;i<=taille;i++){
        for(j=i;j<=taille;j++){
            
            sij = j-i+1;
            PMK = new int[sij];       
            a = 0;
            b= -1;
            PMK[0] = -1;
            
            while( a < sij ){
                while( (b > -1) && (S[i+a] != S[i+b])){
                    b = PMK[b];
                }
                
                a++;
                b++;
                
                if( (a < sij) && (S[i+a] == S[i+b])){
                    PMK[a] = PMK[b];
                }else{
                    PMK[a] = b;
                }
            }
            
            boolres = false;
            a= 0;
            
            for(b= 1; b<=taille; b++){
                while( (a > -1) && (S[i+a] != T[b])){
                    a = PMK[a];
                }
                
                a++;
                
                if( a >= sij ){
                    boolres = true;
                    a = PMK[a];
                }
            }
            
            if(boolres){
                if(sij > max){
                    max = sij;
                }
            }
            
            delete[] PMK;
        }
    }
    
    return max;
 
 
 
}