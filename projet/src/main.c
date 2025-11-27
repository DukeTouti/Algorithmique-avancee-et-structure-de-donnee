#include <stdio.h>
#include "modes.h"

int main(int argc, char* argv[]) {
	if (argc == 1) {
		/* Mode interactif */
		mode_interactif();
	} else if (argc == 2) {
		/* Mode fichier */
		mode_fichier(argv[1]);
	} else {
		/* Usage */
		printf("Usage:\n");
		printf("  %s              # Mode interactif\n", argv[0]);
		printf("  %s <fichier>    # Compresser un fichier\n", argv[0]);
		return 1;
	}
	
	return 0;
}
