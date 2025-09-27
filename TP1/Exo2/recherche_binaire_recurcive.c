#include <stdio.h>
#include <stdlib.h>


int Recherche_binaire(int T[], int d, int f, int v); // signature de la fonction Recherche_binaire

int main(){
    int v=50;  // lal valeur a cherch

    int tab[]={10,20,30,40,50,60};  // tableu 

    int res= Recherche_binaire(tab,0, 6, v); // appel de la fonction 

    if(res<0){  // test si valeur exist?
        printf("Nop\n");
    }else{
        printf("la valeur existe, indice= %d\n",res);
    }

return 0;
}


// fonction prend comme parametre : un tableau T, l'indice du debut d, l'indice de fin f et la valeur cherche
int Recherche_binaire(int T[], int d, int f, int v){  

    int milieu; // pour stocke l'idice du milieu du tableau

   // printf(" d= %d, f=%d   ",d,f);

    if(d==f){  // si indice debut == indice fin, la valeur n'est pas trouve, 
        return -1;
    }else{

        milieu=(d+f)/2; // calcul de lindice du milieu
      //  printf("milieu= %d\n",milieu);

        if(T[milieu]==v){ // tester si la valeur au milieu est egale à valeur cherche v
            return milieu; // si oui, retourner l'indice milieu
        }else{

            // si non, on test sur la valeur, pour chercher soit dans le sous-tableu gauche ou droite
             if(T[milieu]>v){
                Recherche_binaire(T,  d, milieu,  v) ;
             } else{
                Recherche_binaire(T,  milieu+1, f,  v) ; 
             }  
        }
    }

}
