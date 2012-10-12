#!/usr/bin/swipl -q -s
%/Générateur de problèmes de taille n/
%/Entrez la Taille n suivit d'un "." et le scipt génère en sortie standard toutes les permutation de ATCG dans n/
go :- 
  T = ['A','T','C','G'],
  X=[],
  read(Taille),
 write(Taille),write('\n'),
 remplir(T,X,Taille);true.

remplir(_,Y,0):-
    !,forall(member(J,Y),write(J)),write('\n'),!,false.
remplir(T,X,N) :-
  N2 is N-1,!,
  member(A,T),
  append(X,[A],B),
  remplir(T,B,N2).

  
?- go.
?- halt.