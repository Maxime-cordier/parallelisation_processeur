/*==============================================================================*/
/* Programme 	: CodeSequentiel.c												*/
/* Auteur 	: Daniel CHILLET													*/
/* Date 	: Decembre 2021														*/
/* 																				*/
/*==============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <immintrin.h>


#define MAX_CHAINE 100
#define MAX_HOSTS 100

#define CALLOC(ptr, nr, type) 		if (!(ptr = (type *) calloc((size_t)(nr), sizeof(type)))) {		\
						printf("Erreur lors de l'allocation memoire \n") ; 		\
						exit (-1);							\
					} 

#define FOPEN(fich,fichier,sens) 	if ((fich=fopen(fichier,sens)) == NULL) { 				\
						printf("Probleme d'ouverture du fichier %s\n",fichier);		\
						exit(-1);							\
					} 
				
#define MIN(a, b) 	(a < b ? a : b)
#define MAX(a, b) 	(a > b ? a : b)

#define MAX_VALEUR 	255
#define MIN_VALEUR 	0

#define NBPOINTSPARLIGNES 15

#define false 0
#define true 1
#define boolean int


#include <time.h>

#define InitClock    struct timespec start, stop
#define ClockStart   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start)
#define ClockEnd   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop)
#define BILLION  1000000000L
#define ClockMesureSec "%2.9f s\n",(( stop.tv_sec - start.tv_sec )+ (stop.tv_nsec - start.tv_nsec )/(double)BILLION) 




#define DEBUG (0)
#define TPSCALCUL (1)


int main(int argc, char **argv) {
	/*========================================================================*/
	/* Declaration de variables et allocation memoire */
	/*========================================================================*/

	int i, j, n;
	int info ;
	
	int LE_MIN = MAX_VALEUR;
	int LE_MAX = MIN_VALEUR;
	
	float ETALEMENT = 0.0;
	
	unsigned char *image;
	unsigned char *resultat;
	/*int **image;
	int **resultat;*/
	int X, Y, cpt;
	int TailleImage;

	int lignes;
	
	int P;
	
	FILE *Src, *Dst;

	char SrcFile[MAX_CHAINE];
	char DstFile[MAX_CHAINE+4];
	char ligne[MAX_CHAINE];
	
	
	boolean fin ;
	boolean inverse = false;
	
	char *Chemin;
	char *CheminTache;
	

InitClock;

	/*========================================================================*/
	/* Recuperation des parametres						*/
	/*========================================================================*/


	if (argc != 2){
		printf("Syntaxe : CodeSequentiel image.pgm \n");
		exit(-1);
	}
	sscanf(argv[1],"%s", SrcFile);
	
	sprintf(DstFile,"%s.new",SrcFile);
	
	/*========================================================================*/
	/* Recuperation de l'endroit ou l'on travail				*/
	/*========================================================================*/

	CALLOC(Chemin, MAX_CHAINE, char);
	CALLOC(CheminTache, MAX_CHAINE, char);
	Chemin = getenv("PWD");
	if DEBUG printf("Repertoire de travail : %s \n\n",Chemin);

	/*========================================================================*/
	/* Ouverture des fichiers						*/
	/*========================================================================*/

	if DEBUG printf("Operations sur les fichiers\n");

	FOPEN(Src, SrcFile, "r");
	if DEBUG printf("\t Fichier source ouvert (%s) \n",SrcFile);
		
	FOPEN(Dst, DstFile, "w");
	if DEBUG printf("\t Fichier destination ouvert (%s) \n",DstFile);
	
	/*========================================================================*/
	/* On effectue la lecture du fichier source */
	/*========================================================================*/
	
	if DEBUG printf("\t Lecture entete du fichier source ");
	
	for (i = 0 ; i < 2 ; i++) {
		fgets(ligne, MAX_CHAINE, Src);	
		fprintf(Dst,"%s", ligne);
	}	

	fscanf(Src," %d %d\n",&X, &Y);
	fprintf(Dst," %d %d\n", X, Y);
	
	fgets(ligne, MAX_CHAINE, Src);	/* Lecture du 255 	*/
	fprintf(Dst,"%s", ligne);
	
	if DEBUG printf(": OK \n");
	
	/*========================================================================*/
	/* Allocation m#include <immintrin.h>emoire pour l'image source et l'image resultat 		*/
	/*========================================================================*/
	
	TailleImage = X * Y;

	CALLOC(image, X*Y, unsigned char);
	CALLOC(resultat, X*Y, unsigned char);

/*
	CALLOC(image, Y+1, int *);
	CALLOC(resultat, Y+1, int *);
	for (i=0;i<Y;i++) {
		CALLOC(image[i], X+1, int);
		CALLOC(resultat[i], X+1, int);
		for (j=0;j<X;j++) {
			image[i][j] = 0;
			resultat[i][j] = 0;
		}
	}
*/
	if DEBUG printf("\t\t Initialisation de l'image [%d ; %d] : Ok \n", X, Y);
			
	
	/*x = 0;
	y = 0;*/
	cpt = 0;
	
	//lignes = 0;
	
	/*========================================================================*/
	/* Lecture du fichier pour remplir l'image source 			*/
	/*========================================================================*/
	
	while (! feof(Src)) {
		n = fscanf(Src,"%d",&P);

		image[cpt] = (unsigned char)P;
		/*image[y][x] = P;*/
		
		//x ++;
		cpt ++;
		
		if (n == EOF || (cpt == X*Y)) {
			break;
		}


		/*if (x == X) {
			x = 0 ;
			y++;
		}*/
	}


	fclose(Src);
	if DEBUG printf("\t Lecture du fichier image : Ok \n\n");

	for (i=0; i<X*Y ; i++) {
		LE_MIN = MIN(LE_MIN, (int)image[i]);
		LE_MAX = MAX(LE_MAX, (int)image[i]);
	}

	/*
	for (i=0;i<Y;i++) {
		for (j=0;j<X;j++) {
			LE_MIN = MIN(LE_MIN, image[i][j]);
			LE_MAX = MAX(LE_MAX, image[i][j]);
		}
	}*/

	if DEBUG printf("\t Min %d ; Max %d \n\n", LE_MIN, LE_MAX);


	/*========================================================================*/
	/* Calcul du facteur d'etalement					*/
	/*========================================================================*/
	
	if (inverse) {
		ETALEMENT = 0.2;	
	} else {
		ETALEMENT = (float)(MAX_VALEUR - MIN_VALEUR) / (float)(LE_MAX - LE_MIN);	
	}
	
	/*========================================================================*/
	/* Calcul de cahque nouvelle valeur de pixel							*/
	/*========================================================================*/

	__m256i vec_LE_MIN = _mm256_set1_epi8((unsigned char) - LE_MIN);
	__m256i vec_ETALEMENT = _mm256_set1_epi16((short) ETALEMENT);

	
	
ClockStart;

	for (i = 0 ; i < X*Y ; i=i+16) {
		
		__m256i vec_image;
		memcpy(&vec_image, &image[i], sizeof(__m256i));
		
		__m256i vec_resultat = _mm256_mullo_epi16(_mm256_add_epi8(vec_image, vec_LE_MIN), vec_ETALEMENT);

		//_mm_storeu_si16(&resultat[i], vec_resultat);

		memcpy(&resultat[i], &vec_resultat, sizeof(__m256i));
	}

ClockEnd;

if TPSCALCUL printf(ClockMesureSec);

	/*========================================================================*/
	/* Sauvegarde de l'image dans le fichier resultat			*/
	/*========================================================================*/
	
	n = 0;

	for (i=0; i<X*Y ; i++) {
		fprintf(Dst,"%3d ",(int)resultat[i]);
		n++;
		if (n == NBPOINTSPARLIGNES) {
			n = 0;
			fprintf(Dst, "\n");
		}
	}

	/*
	for (i = 0 ; i < Y ; i++) {
		for (j = 0 ; j < X ; j++) {
			
			fprintf(Dst,"%3d ",resultat[i][j]);
			n++;
			if (n == NBPOINTSPARLIGNES) {
				n = 0;
				fprintf(Dst, "\n");
			}
		}
	}*/
				
	fprintf(Dst,"\n");
	fclose(Dst);
	
	printf("\n");

	/*========================================================================*/
	/* Fin du programme principal	*/
	/*========================================================================*/
	
	exit(0); 
	
}
