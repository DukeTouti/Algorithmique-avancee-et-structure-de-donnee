#include <stdio.h>
#include <stdlib.h>
#include "recherche_max_divise_pour_regner.h"


// fonction qui recherche le max dans un tableau par la method diviser pour regner
//elle prend un tableau t , indice de debut d et indice de fin f comme parametres
int d_p_r(int t[], int d, int f){

	if (d == f) {  // si d==f alors on a un seul element
		return t[d];
	} else {

		int milieu = (d + f)/2; //calc de l'indice milieu

		int a = d_p_r(t, d, milieu);
		int b = d_p_r(t, milieu + 1, f);

		if (a > b) { // test si a > b ou non
			return a;
		} else {
			return b;
		}

	}
}












