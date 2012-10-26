int algo3 ( char* S, char* T,const int& taille){
 
    int i, j , a , b , sij;
    int max = 0; // initialisation de variable maximum
    bool boolres; 
    int* PMK; //Déclaration tableau PMK dynamique
    for(i=1;i<=taille;i++){ // variation de i de 1 à n
        for(j=i;j<=taille;j++){ //variation de j de i à n
            
            sij = j-i+1; //calcul de la taille traitée en fonction de i et j
            PMK = new int[sij + 1]; //Allocation de PMK indicé de 0 à sij
            a = 0; //initialisation de a
            b= -1; //initialisation de b
            PMK[0] = -1; //initialisation de la première case
            
            while( a < sij ){
                while( (b > -1) && (S[i+a] != S[i+b])){ // i+a donne la case a dans le tableau Sij 
				//ce qui évite de devoir déclarer et recopier Sij
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
            
            boolres = false; //flag à faux
            a= 0; // a à 0
            
            for(b= 1; b<=taille; b++){ //pour toutes les cases de T
                while( (a > -1) && (S[i+a] != T[b])){
                    a = PMK[a];
                }
                
                a++;
                
                if( a >= sij ){ // si l'indice a atteint sij
                    boolres = true; //flag à vrai
                    a = PMK[a];
                }
            }
            
            if(boolres){ // si le flag est passé à vrai
                if(sij > max){ // et que la taille est supérieur au max actuel
                    max = sij; // alors elle devient le nouveau max
                }
            }
            
            delete[] PMK; //on détruit l'instance de PMK
        }
    }
    
    return max;
 
 
 
}