#include <stdio.h>
#include <stdlib.h>
#include "tri_insertion.h"

void tri_insertion(int[] tab, int size) {
	int i,j;
	int Clef;

	for(i = 1 ; i < n ; i++) {

		Clef = t[i];
		j = i - 1;

    		/* Decalage des valeurs du tableau */
		while((j >= 0) && comp(t[j], Clef)) {
			// cmp++ ;
			t[j+1] = t[j];
			j = j - 1;
		}
		// cmp += 2 ;

		/* insertion de la clef */
		t[j+1] = Clef;
	}
	// cmp++ ;
//	printf("%d comparaisons ont été faites\n", cmp) ;
}
