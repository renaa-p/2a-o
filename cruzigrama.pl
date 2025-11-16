# Base para el ejercicio del crucigrama.
grama(V1,V2,V3,H1,H2,H3):-palabra(V1,_,A,_,D,_,G,_),
    palabra(V2,_,B,_,E,_,H,_),V2\=V1,
    palabra(V3,_,C,_,F,_,I,_),V3\=V2,V3\=V1,
    palabra(H1,_,A,_,B,_,C,_),H1\=V3,H1\=V2,H1\=V1,
    palabra(H2,_,D,_,E,_,F,_),
    palabra(H3,_,G,_,H,_,I,_).

palabra(abalone,a,b,a,l,o,n,e).
palabra(abandon,a,b,a,n,d,o,n).
palabra(anagram,a,n,a,g,r,a,m).
palabra(connect,c,o,n,n,e,c,t).
palabra(elegant,e,l,e,g,a,n,t).
palabra(enhance,e,n,h,a,n,c,e).

