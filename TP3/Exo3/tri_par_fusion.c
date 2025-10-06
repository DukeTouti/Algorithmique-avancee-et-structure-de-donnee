#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define lng(x)  (sizeof(x) )/ sizeof((x)[0])

//#define N 1000  // la taille du tableau

// les signatures des fonctions
void afficher(int *t,int n); // pour affichier un tableau
int getNumber(int min,int max); // genere un nombre aleatoir 
int * triParFusion(int *A,int taille); // la fonction du trie
int * fusion(int *tab1,int * tab2,int taille_g,int taille_d); // la fonction de fusion
int * copie(int *ts,int start,int end); // fonction pour copier les element d'un tableau dans un autre tableau


int main(){
	srand(time(0));

	//int tab[N], *tab_trie; // declaration des tableau

	clock_t debut,fin; // pour calculer le temps d'execution

       for(int N=100000;N<2000000;N+=100000){

          int tab[N], *tab_trie; // declaration des tableau

	//remplissage du tableau
	for(int i=0;i<N;i++){
		tab[i]=getNumber(0,100);
	}

	//affichage du tableau avant tri
	//printf("tableau non trié : ");
	//	afficher(tab,N);

	// tri du tableau
	debut=clock();

	int taille=N ;//=lng(tab);

	tab_trie=triParFusion(tab,taille); //trie du tableau

	fin=clock();

	//affichage du tableau après tri
//	printf("tableau trié : ");
//		afficher(tab_trie,N);

	double temp_execution=(double)(fin-debut)/CLOCKS_PER_SEC;

	printf("temp pour N=%d trié est : %f\n",N, temp_execution);

   }
return 0;

}

// fonction pour afficher un tableau, prend comme parametre le tableau t et sa taille n
void afficher(int *t,int n){
	printf("[ ");
	for(int i=0;i<n;i++){
		printf("%4d",t[i]);
	}
	printf(" ]\n");
}

// fonction pour generer un nobmbre aleatoire
int getNumber(int min, int max){

	return min+rand()%(max+1 - min);

}

// fonction de trie par fusion, cette fonction prend en parametre un tableau a et sa taille
// cette fonction retourne un tableau trie
int * triParFusion(int *a,int taille){


	if(taille<=1){ // tester si on a un seul element dans le tableau
		return a;
	}else{
		int m=taille/2; // calcule de l'indice du milieu

		int *g;  // table gauche
		int *d; // table droite

		g=copie(a,0,m-1); // copie les element du sous-tableau gauche a dans le tableau g
		d=copie(a,m,taille-1); // copie les elements du sous-tableau droite a dans le tableau d

		int taille_g=m; // taille du tableau gauhe g
		int taille_d=taille-m; // taille du tableau droite d

		int *tabA=triParFusion(g,taille_g); // sous-tablelau gauche
		int *tabB=triParFusion(d,taille_d); // sou-tableau droite

		int *res=fusion(tabA,tabB,taille_g,taille_d); // fuion du deux tableau

		return res;
	}

}

// fonction de fusion de deux tableau. prend en parmetre deux tableau: tab1 , tab2 et leurs taille taille_g et taille_d
int * fusion(int *tab1,int * tab2,int taille_g,int taille_d){

	int *res=malloc((taille_d+taille_g)*sizeof(int)); // allocation memoire pour le tabelu res qui va contenir les element des deux tableau trie
	//int res[taille_d+taille_g];

	int i_g=0,i_d=0,i; // les indices des tableau, i_g pour le tableau gauche (tab1), i_d pour le tableau droite (tab2)

	for( i=0;i_g<taille_g && i_d<taille_d;i++){ // on boucle sur les tableau tanque leurs indice et infirieur a leur taille

		if(tab1[i_g]<=tab2[i_d]) // on test pour inserer les elements d'une maniere trie dans le tableau res
				res[i]=tab1[i_g++];
		else
				res[i]=tab2[i_d++];
	}

	// on ajout les elelments restants danss le tableau res
	while(i_g<taille_g)
		res[i++]=tab1[i_g++];
	while(i_d<taille_d)
		res[i++]=tab2[i_d++];

		return res;
}

//fonction qui copie un tabeau dans un autre
int * copie(int *ts,int start,int end){
	int *rs= malloc((end-start+1)*sizeof(int));
	int n=0;
	for(int i=start;i<=end;i++){
		rs[n++]=ts[i];
	}

	return rs;
}
