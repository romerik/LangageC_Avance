#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void Object;
typedef struct Noeud* PNoeud;
typedef struct Noeud{
	Object* valeur;
	PNoeud filsGauche;
	PNoeud filsDroit;
}Arbre;

typedef struct  Cellule* PCellule;
typedef struct Cellule
{
	PNoeud valeur;
	PCellule suivant;
}Liste;

typedef struct
{
	Liste* tete;
	Liste* que;
}LFile;

int estFileVide(LFile* fl){
	if(fl->tete!=NULL && fl->que!=NULL)
		return 0;//file non vide
	else
		return 1;//file vide
}

void enfiler(LFile* fl, PNoeud noeud){
	PCellule nouveau = malloc(sizeof(PCellule));
	nouveau->valeur=noeud;
	nouveau->suivant=NULL;
	if(estFileVide(fl)!=1){
		fl->que->suivant = nouveau;
	}
	else{
		fl->tete = nouveau;
	}
	fl->que = nouveau;
}

PNoeud defiler(LFile* fl){
	PNoeud noeud = NULL;
	if(estFileVide(fl)!=1){
		noeud = fl->tete->valeur;
		fl->tete = fl->tete->suivant;
	}

	if(fl->tete==NULL){
		fl->que = NULL;
	}
	return noeud;
}

PNoeud creationNoeud(Object* obj, PNoeud gauche, PNoeud droit){
	PNoeud nouveau = malloc(sizeof(PNoeud));
	nouveau->valeur = obj;
	nouveau->filsGauche = gauche;
	nouveau->filsDroit = droit;
	return nouveau;
}

PNoeud creationFeuille(Object* obj){
	return creationNoeud(obj, NULL,NULL);
}

Object* renvoyerNoeud(PNoeud noeud){
	return noeud->valeur;
}

void parcoursPostfixe(PNoeud noeud){
	if(noeud!=NULL){
		parcoursPostfixe(noeud->filsGauche);
		parcoursPostfixe(noeud->filsDroit);
		printf("  %d  ",renvoyerNoeud(noeud));
	}
}

void parcoursPrefixe(PNoeud noeud){
	if(noeud!=NULL){
		printf("  %d  ",renvoyerNoeud(noeud));
		parcoursPrefixe(noeud->filsGauche);
		parcoursPrefixe(noeud->filsDroit);
	}
}

void parcoursInfixe(PNoeud noeud){
	if(noeud!=NULL){
		parcoursInfixe(noeud->filsGauche);
		printf("  %d  ",renvoyerNoeud(noeud));
		parcoursInfixe(noeud->filsDroit);
	}
}

void ajouterNoeud(PNoeud* arbre, PNoeud noeud){
	if(*arbre==NULL){
		*arbre = noeud;
	}
	else{
		if(noeud->valeur > (*arbre)->valeur){
			printf("Droit\n");
			ajouterNoeud(&(*arbre)->filsDroit, noeud);
		}
		else{
			printf("Gauche\n");
			ajouterNoeud(&(*arbre)->filsGauche, noeud);
		}
	}
}

void rechercheBinaire(PNoeud noeud, Object* elt, int* result){
	int trouver = 0;
	if(noeud!=NULL){
		if(renvoyerNoeud(noeud)==elt){
			*result = 1;
		}
		else{
			if(renvoyerNoeud(noeud)>elt){
				rechercheBinaire(noeud->filsGauche, elt, result);
			}
			else{
				rechercheBinaire(noeud->filsDroit, elt, result);
			}
		}
	}
}

PNoeud creationDynamique(PNoeud arbre){
	int donnee,i, valeurOne, valeurTwo, filsVrai = 0;
	LFile* fl = malloc(sizeof(LFile*));
	PNoeud extrait, temp;
	fl->tete = NULL;
	fl->que = NULL;
	printf("Entrer le premier élément de votre arbre qui sera la racine : ");
	scanf("%d", &donnee);
	arbre = creationFeuille(donnee);
	temp = arbre;
	enfiler(fl, arbre);
	while(estFileVide(fl)!=1){
		filsVrai = 1;
		extrait = defiler(fl);
		printf("\n Entrer les deux fils de %d (ou 0 pour spécifier qu'un fils est NULL): ", extrait->valeur);
		do{
			scanf("%d %d",&valeurOne,&valeurTwo);
			if(valeurOne!=0 || valeurTwo!=0){
			if((valeurOne < extrait->valeur && valeurTwo < extrait->valeur) || (valeurOne > extrait->valeur && valeurTwo > extrait->valeur)){
				filsVrai=0;
				printf("\nUn des fils doit être plus grand que son parent et le second plus petit que son parent\nRemettez les fils : ");
			}
			else{
				filsVrai = 1;
			}
			}
			else{
				filsVrai = 1;
			}
		}while(filsVrai==0);
		if(valeurOne!=0){
			if(valeurOne > extrait->valeur){
				extrait->filsDroit = creationFeuille(valeurOne);
				if(valeurTwo == 0){
					extrait->filsGauche = NULL;
				}
			}
			else{
				extrait->filsGauche = creationFeuille(valeurOne);
				if(valeurTwo==0){
					extrait->filsDroit = NULL;
				}
			}
		}
		if(valeurTwo!=0){
			if(valeurTwo > extrait->valeur){
				extrait->filsDroit = creationFeuille(valeurTwo);
				if(valeurOne==0){
					extrait->filsGauche = NULL;
				}
			}
			else{
				extrait->filsGauche = creationFeuille(valeurTwo);
				if(valeurOne == 0){
					extrait->filsDroit = NULL;
				}
			}
		}
		if(extrait->filsGauche!=NULL){
			enfiler(fl, extrait->filsGauche);
		}
		if(extrait->filsDroit!=NULL){
			enfiler(fl, extrait->filsDroit);
		}
	}
	return temp;
}

void parcoursLargeur(PNoeud noeud){
	LFile* fl = malloc(sizeof(LFile*));
	fl->tete = NULL;
	fl->que = NULL;
	enfiler(fl, noeud);
	PNoeud extrait;
	while(estFileVide(fl)!=1){
		extrait  = defiler(fl);
		printf("   %d   ", extrait->valeur);
		if(extrait->filsGauche!=NULL){
			enfiler(fl, extrait->filsGauche);
		}
		if(extrait->filsDroit!=NULL){
			enfiler(fl, extrait->filsDroit);
		}
	}
}
int main(){

	PNoeud arbre = malloc(sizeof(PNoeud));
	int nbreElement;
	printf("\n\nBienvenue dans le programme des arbres binaires de recherche\n\n");
	/*printf("Entrer le nombre d'élémént de votre arbre : ");
	scanf("%d", &nbreElement);*/

	//Création de l'arbre

	//PNoeud arbre = creationNoeud(8, creationNoeud(3,creationFeuille(1),creationNoeud(6,creationFeuille(4),creationFeuille(7))), creationNoeud(10,creationNoeud(14,NULL,creationFeuille(13)), NULL));
	arbre = creationDynamique(arbre);

	printf("\nLes éléments de votre arbre en parcours postfixé sont : ");
	parcoursPostfixe(arbre);
	printf("\n");
	//Parcours de l'arbre

	printf("\nLes éléments de votre arbre en parcours en largeur sont : ");
	parcoursLargeur(arbre);
	printf("\n");
	//Parcours PostFixé
/*	printf("Parcours PostFixé\n");
	parcoursPostfixe(arbre);
	printf("\n");

	//Parcours PréFixé
	printf("Parcours PreFixé\n");
	parcoursPrefixe(arbre);
	printf("\n");

	//Parcours InFixé
	printf("Parcours InFixé\n");
	parcoursInfixe(arbre);
	printf("\n");*/

	return 0;
}
