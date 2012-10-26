int algo3 ( char* S, char* T,const int& taille){
 
    int i, j , a , b , sij;
    int max = 0; // initialisation de variable maximum
    bool boolres; 
    int* PMK; //D�claration tableau PMK dynamique
    for(i=1;i<=taille;i++){ // variation de i de 1 � n
        for(j=i;j<=taille;j++){ //variation de j de i � n
            
            sij = j-i+1; //calcul de la taille trait�e en fonction de i et j
            PMK = new int[sij + 1]; //Allocation de PMK indic� de 0 � sij
            a = 0; //initialisation de a
            b= -1; //initialisation de b
            PMK[0] = -1; //initialisation de la premi�re case
            
            while( a < sij ){
                while( (b > -1) && (S[i+a] != S[i+b])){ // i+a donne la case a dans le tableau Sij 
				//ce qui �vite de devoir d�clarer et recopier Sij
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
            
            boolres = false; //flag � faux
            a= 0; // a � 0
            
            for(b= 1; b<=taille; b++){ //pour toutes les cases de T
                while( (a > -1) && (S[i+a] != T[b])){
                    a = PMK[a];
                }
                
                a++;
                
                if( a >= sij ){ // si l'indice a atteint sij
                    boolres = true; //flag � vrai
                    a = PMK[a];
                }
            }
            
            if(boolres){ // si le flag est pass� � vrai
                if(sij > max){ // et que la taille est sup�rieur au max actuel
                    max = sij; // alors elle devient le nouveau max
                }
            }
            
            delete[] PMK; //on d�truit l'instance de PMK
        }
    }
    
    return max;
 
 
 
}