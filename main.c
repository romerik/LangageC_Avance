#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void Object;

typedef struct CelluleDbl* PCelluleDbl;

//Un element de la liste doublement chainée
typedef struct CelluleDbl{
    Object* valeur;
    PCelluleDbl suivant;
    PCelluleDbl precedent;

}ListeDbl;

void creerListe(PCelluleDbl l, int n){
    PCelluleDbl tete;
    PCelluleDbl p;
    int i;
    int donnee;
    printf("\n\nEntrer la valeur de l'élément 1 :");
    scanf("%d",&donnee);
    tete=l;
    tete->valeur=donnee;
    tete->suivant=NULL;
    tete->precedent=NULL;
    for(i=2; i<=n; i++){
        printf("\n\n");
        p=malloc(sizeof(PCelluleDbl));
        printf("Entrer la valeur de l'élément %d :",i);
        scanf("%d",&donnee);
        p->valeur = donnee;
        p->suivant =NULL;
        p->precedent = tete;
        tete->suivant = p;
        tete = p;
    }
}
void afficherListeDbl(PCelluleDbl l){
    PCelluleDbl p;
    p=l;
    if(p!=NULL){
    printf("\n\nLes éléments de la liste sont :\n\n\n");
    while(p!=NULL){
        printf("  %d   ", p->valeur);
        p = p->suivant;
    }
    printf("\n");
    }
}

int menu(PCelluleDbl l){
    int choix = 0;
        afficherListeDbl(l);
        printf("\n\n-------Programme des listes doublements chainées------------\n\n");
        printf("Choisissez un nombre pour faire une opération ");
        printf("\n\n1- Créer une liste chainée d'entier \n\n2- Ajouter un élément en tête de liste\n\n3- Ajouter un élément en queue de liste\n\n4- Trier votre liste\n\n5- Supprimer un élément donné de la liste\n\n6- Supprimer doublons de votre liste\n\n7- Rechercher un élément dans la liste  \n\n8- Fusionner deux listes\n\n9- Inverser une liste\n\n10- Vérifier si la liste est un palindrome \n\n11- Quitter\n\n");
     do{
         printf("Votre choix  :  ");
        scanf("%d", &choix);
        if(choix<1 || choix>11)
            printf(" \n\nChoisissez un bon nombre\n");
    }while(choix<1 || choix >11);
    system("clear"); //system("cls"); pour windows
    return choix;

}

void afficherListeDblInverse(PCelluleDbl l){
    PCelluleDbl p;
    p=l;
    
    while(p->suivant!=NULL)
        p = p->suivant;

     printf("\n\nLes éléments de votre liste de façon inverse sont :\n\n\n");
    while(p!=NULL){
        printf("  %d   ", p->valeur);
        p=p->precedent;
    }
    printf("\n");
}

PCelluleDbl ajoutTete(PCelluleDbl l, Object* donnee){
    PCelluleDbl nouveauListe;
    nouveauListe =malloc(sizeof(PCelluleDbl));
    l->precedent = nouveauListe;
    nouveauListe->precedent = NULL;
    nouveauListe->valeur = donnee;
    nouveauListe->suivant = l;
    return nouveauListe;
}


void ajoutQueuDbl(PCelluleDbl l, Object* donnee){
    PCelluleDbl p, que;
    que = malloc(sizeof(PCelluleDbl));
    que->valeur = donnee;
    que->suivant = NULL;
    p = l;
    if(p!=NULL)
        while(p->suivant!=NULL)
            p = p->suivant;
    p->suivant = que;
    que->precedent = p;

}

int rechercherListeDbl(PCelluleDbl l, Object* valeurRecherche, PCelluleDbl* addresseRechercher){
    int trouver = 0;
    PCelluleDbl p = l;
    while(trouver==0 && p!=NULL){
        if(p->valeur==valeurRecherche){
            trouver=1;
            *addresseRechercher = p;
        }
        p = p->suivant;
    }
    return trouver;
}

PCelluleDbl supprimerListeDbl(PCelluleDbl l, Object* donnee){
    PCelluleDbl p=NULL, preced= NULL;
    if(l->valeur == donnee){
        p = l;
        l = l->suivant;
        l->precedent = NULL;
        free(p);
        return l;
    }
    else{
        if(rechercherListeDbl(l,donnee,&p)){
            preced = p->precedent;
            preced->suivant = p->suivant;
            if(p->suivant!=NULL){
                p->suivant->precedent = preced;
            }
            free(p);
        }
        return l;
    }
}

void triBulleDbl(PCelluleDbl l){
    int permut;
    PCelluleDbl p, q;
    Object* temp;
    do{
        p=l;
        permut = 0;
        while(p!=NULL){
            q = p->suivant;
            while(q!=NULL){
                if(p->valeur > q->valeur){
                    permut = 1;
                    temp = p->valeur;
                    p->valeur = q->valeur;
                    q->valeur =temp;
                }
                q = q->suivant;
            }
            p = p->suivant;
        }
    }while(permut==1);
}

PCelluleDbl supprimerDoublons(PCelluleDbl l){
    PCelluleDbl p;
    p = l;
    if(p->suivant!=NULL){
        while(p->suivant!=NULL && p->valeur!=p->suivant->valeur)
            p = p->suivant;
        if(p->suivant==NULL)
            return l;
        l = supprimerListeDbl(l,p->valeur);
        l = supprimerDoublons(l);
    }
    else{
        return l;
    }

}

PCelluleDbl fusionnerDeuxListe(PCelluleDbl l){
    PCelluleDbl p, q,listeFusion, deuxiemeListe, temp;
    int nbreElement = 1;
    temp = malloc(sizeof(PCelluleDbl));
    deuxiemeListe = malloc(sizeof(PCelluleDbl));
    listeFusion = malloc(sizeof(PCelluleDbl));
    listeFusion->precedent = NULL;
    listeFusion->suivant = NULL;
    listeFusion->valeur = 0;
    printf("\n\nVous devez d'abord créer une deuxième liste pour faire la fusion\n\nEntrer le nombre d'élément de votre deuxième liste : ");
    do{
        if(nbreElement<=0)
            printf("Entrer un nombre supérieur à 0 : ");
        scanf("%d", &nbreElement);
    }while(nbreElement<=0);
    creerListe(deuxiemeListe, nbreElement);
    system("clear");//system("cls"); pour windows
    printf("\n1-------La première liste principale--------\n");
    afficherListeDbl(l);
    printf("\n2-------Deuxième liste bien créer--------\n");
    afficherListeDbl(deuxiemeListe);
    triBulleDbl(l);
    triBulleDbl(deuxiemeListe);
    p = l;
    q = deuxiemeListe;
    while(p!=NULL && q!=NULL){
        if(p->valeur < q->valeur){
            if(rechercherListeDbl(listeFusion, p->valeur, &temp)==0){
                ajoutQueuDbl(listeFusion, p->valeur);
            }
            p = p->suivant;
            continue;
        }
        else if(p->valeur > q->valeur){
            if(rechercherListeDbl(listeFusion, q->valeur, &temp)==0){
                ajoutQueuDbl(listeFusion, q->valeur);
            }
            q = q->suivant;
            continue;
            
        }
        else{
            if(rechercherListeDbl(listeFusion, p->valeur, &temp)==0){
                ajoutQueuDbl(listeFusion, p->valeur);
            }
            p = p->suivant;
            q = q->suivant;
        }
    }
    if(p==NULL){
        while(q!=NULL){
            ajoutQueuDbl(listeFusion, q->valeur);
            q = q->suivant;
        }
    }
    if(q==NULL){
        while(p!=NULL){
            ajoutQueuDbl(listeFusion, p->valeur);
            p = p->suivant;
        }
    }
    l = supprimerListeDbl(listeFusion,0);
    return l;
}

PCelluleDbl inverserListe(PCelluleDbl l){
    PCelluleDbl inverse, p, temp;
    inverse = malloc(sizeof(PCelluleDbl));
    p = l;
    if(p==NULL)
        return l;
    temp = inverse;
    while(p->suivant!=NULL)
        p = p->suivant;
    inverse->precedent = NULL;
    inverse->suivant = NULL;
    inverse->valeur = p->valeur;
    p = p->precedent;
    while(p!=NULL){
        ajoutQueuDbl(inverse, p->valeur);
        p = p->precedent;
    }
    return temp;
}

int palindrome(PCelluleDbl l){
    PCelluleDbl temp, p;
    int booleen = 1;
    p = l;
    temp = l;
    while(temp->suivant!=NULL)
        temp = temp->suivant;
    while(temp!=p && temp->precedent!=p){
        if(temp->valeur != p->valeur){
            return 0;
        }
        temp = temp->precedent;
        p = p->suivant;
    }
    if(temp->precedent == p && temp->valeur  != p->valeur)
        return 0;
    return 1;
}

int main(){

    PCelluleDbl MaListe = NULL;
    int nbreElement=1;
    int donnee;
  int choix = -1;
  int continuer = 1;
  do{
    do{
        choix = menu(MaListe);
        if(choix!=1 && MaListe==NULL)
            printf("\nVous devez dabord créer une liste\n");
    }while(choix!=1 && choix!=0 && MaListe==NULL);
   switch(choix){
        case 1:
                MaListe = malloc(sizeof(PCelluleDbl));
                printf("Entrer le nombre d'élément de la liste :");
                do{
                    if(nbreElement<=0)
                        printf("Entrer un nombre supérieur à 0 : ");
                    scanf("%d", &nbreElement);
                }while(nbreElement<=0);
                creerListe(MaListe, nbreElement);
                afficherListeDbl(MaListe);
            break;
        case 2:
            afficherListeDbl(MaListe);
            printf("\n\nEntrer l'élément à ajouter en tête de votre liste : ");
            scanf("%d", &donnee);
            MaListe = ajoutTete(MaListe, donnee);
            afficherListeDbl(MaListe);
            break;
        case 3:
            afficherListeDbl(MaListe);
            printf("\n\nEntrer l'élément à ajouter en queu de votre liste : ");
            scanf("%d", &donnee);
            ajoutQueuDbl(MaListe, donnee);
            afficherListeDbl(MaListe);
            break;
        case 4:
            printf("Avant le tri \n");
            afficherListeDbl(MaListe);
            triBulleDbl(MaListe);
            printf("\nAprès le tri \n");
            afficherListeDbl(MaListe);
            break;
        case 5:
            afficherListeDbl(MaListe);
            printf("\n\nEntrer l'élément à supprimer dans votre liste : ");
            scanf("%d", &donnee);
            MaListe = supprimerListeDbl(MaListe, donnee);
            afficherListeDbl(MaListe);
            break;
        case 6:
            printf("Avant la suppression des doublons\n");
            afficherListeDbl(MaListe);
            triBulleDbl(MaListe);
            MaListe = supprimerDoublons(MaListe);
            printf("Après la suppression des doublons\n");
            afficherListeDbl(MaListe);
            break;
        case 7:
            afficherListeDbl(MaListe);
            printf("\n\nEntrer l'élément à rechercher dans votre liste : ");
            scanf("%d", &donnee);
            PCelluleDbl AdressRechercher = NULL;
            int trouver =rechercherListeDbl(MaListe, donnee,&AdressRechercher) ;
            if(trouver==1){
                printf("\n\nElement trouvé\n");
            }
            else{
                 printf("\n\nElement non trouvé dans la liste\n");
            }
            break;
        case 8:
            MaListe = fusionnerDeuxListe(MaListe);
            printf("\n\nLa liste est maintenant fusionné, votre nouveau liste est :\n\n");
            afficherListeDbl(MaListe);
            break;
        case 9:
            printf("\nAvant inversion de la liste\n");
            afficherListeDbl(MaListe);
            MaListe = inverserListe(MaListe);
            printf("\nAprès inversion de la liste\n");
            afficherListeDbl(MaListe);
            break;
        case 10:
            if(palindrome(MaListe)==0)
                printf("\nLa liste n'est pas un palindrome\n");
            else
                printf("\nLa liste est un palindrome\n");
            break;
        default:
            afficherListeDbl(MaListe);
            printf("\n\n\n***********PROGRAMME TERMINEE**************\n\n\n");
            return 0;
    }
    do{
        printf("\n\nVoulez vous continuez ? \n0-Non\n1-Oui\nVotre choix: ");
        scanf("%d", &continuer);
    }while(continuer!=0 && continuer!=1);
     system("clear");//system("cls"); pour windows
}while(continuer==1);

    return 0;
}