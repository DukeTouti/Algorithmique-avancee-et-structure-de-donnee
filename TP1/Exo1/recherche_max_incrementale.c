#include <stdio.h>
#include <stdlib.h>
#include "recherche_max_incrementale.h"

int recherche_max_incrementale (int t[], int n) {
	int max = t[0];
	
	for (int i = 0 ; i < n ; i++) {
		if (t[i] > max) {
			max = t[i];
		}
	}
	return max;
}
