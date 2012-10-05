#include "algo2.cpp"
#include "algo1.cpp"

int main(int argc, char *argv[]){
    char* test1 = new char[10+1];
    char* test2 = new char[10+1];
    char* test3 = new char[10+1];
    char* test4 = new char[10+1];
    
    test1[1] = A;
    test1[2] = A;
    test1[3] = T;
    test1[4] = C;
    test1[5] = G;
    test1[6] = G;
    test1[7] = T;
    test1[8] = A;
    test1[9] = C;
    test1[10] = G;
    
    test2[1] = A;
    test2[2] = A;
    test2[3] = T;
    test2[4] = C;
    test2[5] = G;
    test2[6] = G;
    test2[7] = T;
    test2[8] = A;
    test2[9] = C;
    test2[10] = G;
    
    test3[1] = C;
    test3[2] = C;
    test3[3] = C;
    test3[4] = C;
    test3[5] = G;
    test3[6] = G;
    test3[7] = T;
    test3[8] = A;
    test3[9] = G;
    test3[10] = G;
    
    
    test4[1] = T;
    test4[2] = A;
    test4[3] = C;
    test4[4] = G;
    test4[5] = C;
    test4[6] = C;
    test4[7] = C;
    test4[8] = C;
    test4[9] = C;
    test4[10] = C;
    
    std::cout << algo1(test1,test2,10); << std::endl;
    std::cout << algo1(test1,test3,10); << std::endl;
    std::cout << algo1(test1,test4,10); << std::endl;
    std::cout << algo1(test2,test3,10); << std::endl;
    std::cout << algo1(test2,test4,10); << std::endl;
    std::cout << algo1(test3,test4,10); << std::endl;
    
    std::cout << algo2(test1,test2,10); << std::endl;
    std::cout << algo2(test1,test3,10); << std::endl;
    std::cout << algo2(test1,test4,10); << std::endl;
    std::cout << algo2(test2,test3,10); << std::endl;
    std::cout << algo2(test2,test4,10); << std::endl;
    std::cout << algo2(test3,test4,10); << std::endl;
    
    delete[] test1;
    delete[] test2;
    delete[] test3;
    delete[] test4;
    
}