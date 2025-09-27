#include <stdio.h>
#include <stdlib.h>
#include "recherche_binaire_iterative.h"


int recherche_binaire_iterative(int tab[],int v,int n){
	int debut = 0;
	int fin = n - 1;
	
	while (debut <= fin) {
		int milieu = (debut + fin) / 2;
		// printf("milieu= %d t= %d v=%d \n",milieu,t[milieu],v);
		if (tab[milieu] == v) {
			return milieu;
		} else if(tab[milieu] > v) {
			fin = milieu - 1;
		} else {
			debut = milieu + 1;
		}
	}
	
	return -1 ;
}

