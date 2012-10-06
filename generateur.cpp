#include <iostream>

//Generate a random ADM sequence (size = n)
// O(n) - Need to free the result
char* random_generate(const int &n,int randomvalue)
{
  srand(time(NULL)+randomvalue);
  char ADN[4]={'A','T','C','G'};
  char* result=(char*) malloc((n+1)*sizeof(char));
  int i;
  for(i=0;i<n;i++)
  {
    result[i+1]=ADN[rand()%4];
  }
  return result;
}