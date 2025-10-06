#include <stdio.h>
#include <stdlib.h>
#include "tri_insertion.h"

void tri_insertion(int *tab, int size) {
	int i,j;
	int Clef;

	for(i = 1 ; i < size ; i++) {

		Clef = tab[i];
		j = i - 1;

    		/* Decalage des valeurs du tableau */
		while((j >= 0) && (tab[j] > clef)) {
			// cmp++ ;
			tab[j+1] = tab[j];
			j = j - 1;
		}
		// cmp += 2 ;

		/* insertion de la clef */
		tab[j+1] = Clef;
	}
	// cmp++ ;
//	printf("%d comparaisons ont été faites\n", cmp) ;
}
