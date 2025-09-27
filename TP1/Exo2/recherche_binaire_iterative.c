#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Recherche_binaire(int t[],int v,int n);
void main(){

    int n=10;
    int tab[]={1,2,3,4,5,6,7,8,9,10};
    int v=10;
   // for (int iter=1000;iter<10000000;iter+1000) { 
  //	for(int i=0;i<iter;i++)
//	{
//	  tab[i]=i;
//	}

    clock_t start=clock();
    int res=Recherche_binaire(tab,v,n);
    clock_t end=clock();

    double exec_time=(double)(end-start)/CLOCKS_PER_SEC;

    if(res<0)
        printf("la valuer %d n'exist pas \n",v);
    else
        printf("la valeur %d exist, et à comme indice %d \n",v,res);

    printf("exec_time = %f\n",exec_time);

//}
}

int Recherche_binaire(int t[],int v,int n){

    int i=0;
    int res=-1;
    while(i<n){
        int milieu=(i+n)/2;
       // printf("milieu= %d t= %d v=%d \n",milieu,t[milieu],v);
        if(t[milieu]==v)
            return milieu;
        else
            if( t[milieu]>v)
                n=milieu-1;
            else
                i=milieu+1;

    }

    return res;

}
