#include <stdio.h>
#include <stdlib.h>
#include "chercher.h"

int chercher_recursif(int A[], int s, int f, int a, int b) {

	if (s == f) {
		if (A[s] >= a && A[s] <= b) {
			return s;
		} else {
			return -1;
		}
	}
    
	int m = (s + f) / 2;
    
	if (A[m] < a) {
		return chercher_recursif(A, m + 1, f, a, b);
	} else if (A[m] >= a && A[m] <= b) {
		return m;
	} else {
		return chercher_recursif(A, s, m, a, b);
	}
}

int chercher_lineaire(int A[], int n, int a, int b) {
	for (int i = 0; i < n; i++) {
		if (A[i] >= a && A[i] <= b) {
			return i;
		}
	}
	return -1;
}
