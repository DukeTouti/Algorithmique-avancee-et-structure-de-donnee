#include <stdio.h>
#include <stdlib.h>


int d_p_r(int t[],int d, int f); //signature de la fonction


int main(){

    int tab[10]={10,8,5,50,6,3,1,54,23,12}; 

    printf("affichage du tableau\n");
    int i;
    for(i=0;i<10;i++)
        printf("tab[%d]= %d\n",i,tab[i]);
    

    // recheche du max
    //start
    int max=d_p_r(tab,0,10);
    //fin
    printf("le maximum par la method diviser pour regner est : %d \n",max);

    return 0;
}


// fonction qui recherche le max dans un tableau par la method diviser pour regner
//elle prend un tableau t , indice de debut d et indice de fin f comme parametres
int d_p_r(int t[],int d,int f){

    if(d==f){  // si d==f alors on a un seul element
        return t[d];
    }else{

        int milieu=(d+f)/2; //calc de l'indice milieu

        int a=d_p_r(t,d,milieu);
        int b=d_p_r(t,milieu+1,f);

        if(a>b) // test si a > b ou non
            return a;
        else
            return b;


    }



}
