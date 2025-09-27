#include <stdio.h>
#include <stdlib.h>
#include "recherche_binaire_recursive.h"

// fonction prend comme parametre : un tableau T, l'indice du debut d, l'indice de fin f et la valeur cherche

int recherche_binaire_recursive(int tab[], int d, int f, int v) {  
	
	int milieu; // pour stocke l'indice du milieu du tableau

	//printf(" d= %d, f=%d   ",d,f);
	
	if (d == f) {  // si indice debut == indice fin, la valeur n'est pas trouve, 
		return -1;
	} else {

		milieu = (d + f) / 2; // calcul de lindice du milieu
		//  printf("milieu= %d\n",milieu);
	
		if (tab[milieu] == v) { // tester si la valeur au milieu est egale à valeur cherche v
			return milieu; // si oui, retourner l'indice milieu
		} else if (tab[milieu] > v) {
			return recherche_binaire_recursive(tab, d, milieu, v) ;
		} else {
			return recherche_binaire_recursive(tab, milieu + 1, f, v) ; 
		}  
	}
}
	

