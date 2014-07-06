#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "FonctionLDC.c"




int main(){
	int choix,p;
	char code[50];
	login();
	liste *l = lire_liste();
	do{
		menu();
		scanf("%d", &choix);
		nettoyer();
		system("cls");
		switch(choix){
			case 1:
				ajouter_debut(l, saisie_employe(l));
				printf("L'employe est ajouter avec success au debut de la liste\n");
				printf("Taper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 2:
				ajouter_fin(l, saisie_employe(l));
				printf("L'employe est ajouter avec success a la fin de liste\n");
				printf("Taper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 3:
				printf("Incertion d'un employe avant un autre.\nEntrer le code de l'autre employe : ");
				lirechaine(code, 50);
				if (inserer_avant(l, code) != NULL)
                    printf("\nL'employe est ajouter avec success avant l'employe au code : %s\n", code);
				printf("\nTaper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 4:
				printf("Incertion d'un employe apres un autre.\nEntrer le code de l'autre employe : ");
				lirechaine(code, 50);
				if (inserer_apres(l, code) != NULL)
                    printf("\nL'employe est ajouter avec success apres l'employe au code : %s\n", code);
				printf("\nTaper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 5:
				effacer_premier(l);
				printf("Le premier employe de la liste est supprime\n");
				printf("Taper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 6:
				effacer_dernier(l);
				printf("Le dernier employe de la liste est supprime\n");
				printf("Taper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 7:
				printf("Entrer la position de l'employe pour le supprimer : ");
				scanf("%d", &p);
				if (p < l->taille){
                    effacer_position(l, p);
                    printf("\nL'employe en position %d est supprime\n", p);
				} else printf("Cette position n'existe pas");
                printf("\nTaper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 8:
				afficher_liste_arr(l);
				printf("\nTaper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 9:
				printf("Entrer le code de l'employe pour l'afficher : ");
				lirechaine(code, 50);
				if (recherche_employe(l, code) != NULL) afficher_employe(recherche_employe(l, code));
				printf("\nTaper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 10:
				printf("Entrer le code de l'employe pour le modifier : ");
				lirechaine(code, 50);
				if (modifier_employe(l, code) != NULL)
                    printf("\nL'employe ayant pour code %s est modifier avec success\n", code);
				printf("\nTaper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 11:
				afficher_liste(l);
				printf("\nTaper n'importe quelle touche pour retourner au menu principal");
				getch();
			break;

			case 12:
				change_password();
			break;

			case 13:
				printf("Au revoir!\n\n\n\n\n");
				exit(0);
			break;

			default:
				printf("\nChoix non disponible!\nVeuiller choisir parmi les options disponibles dans le menu principale");
				printf("\n\nTaper n'importe quelle touche pour aller au menu principal");
				getch();
			break;
		}
	}while(choix != 13);

    return 0;
}
