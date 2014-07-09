#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



typedef struct employe{
    char code[50];
    char nom[50];
    char prenom[50];
    char embdate[50];
    int age;
    struct employe *suivant;
    struct employe *precedent;
}employe;


typedef struct liste{
    size_t taille;
    employe *debut;
    employe *fin;
} liste;


employe *saisie_employe(liste *l);
char *encrypt(char *s);
char *decrypt(char *s);

int verifier_nom(char nom[50]){
	int i, l = strlen(nom);
	for(i = 0; i < l; i++)
		if (isdigit(nom[i])) return 0;
	return 1;
}

liste *new_liste(void){
    liste *l = malloc(sizeof *l);
    if (l != NULL)
    {
        l->taille = 0;
        l->debut = NULL;
        l->fin = NULL;
    }
    return l;
}

liste *ajouter_fin(liste *emp_list, employe *emp){
    emp->suivant = NULL; /* On fait pointer suivant vers NULL */
    if (emp_list->fin == NULL) /* Cas où notre liste est vide (pointeur vers fin de liste à  NULL) */
    {
        emp->precedent = NULL; /* On fait pointer p_prev vers NULL */
        emp_list->debut = emp; /* On fait pointer la tête de liste vers le nouvel élément */
        emp_list->fin = emp; /* On fait pointer la fin de liste vers le nouvel élément */
    }
    else /* Cas où des éléments sont déjà présents dans notre liste */
    {
        emp_list->fin->suivant = emp; /* On relie le dernier élément de la liste vers notre nouvel élément (début du chaînage) */
        emp->precedent = emp_list->fin; /* On fait pointer p_prev vers le dernier élément de la liste */
        emp_list->fin = emp; /* On fait pointer la fin de liste vers notre nouvel élément (fin du chaînage: 3 étapes) */
    }
    emp_list->taille++; /* Incrémentation de la taille de la liste */
    ecrire_employe(emp);

    return emp_list; /* on retourne notre nouvelle liste */
}

char *get_date(){
    static char  a[10];
    char* p;
    char  c;
    int   x, sortie;
    p = a;
    x = 0;
    sortie = 0;

    do
    {
        c = getch();
        int i = c -'0';
        if (isdigit(c) && x < 10){
            if(i < 4 && x == 0){
                printf("%c", c);
                p[x++] = c;
            }else if((p[x-1] - '0' == 3 && x == 1 && i < 2) || (p[x-1] - '0' == 0 && x == 1 && i > 0) || (p[x-1] - '0' < 3 && p[x-1] - '0' != 0 && x == 1)
                     || (i <=1 && x == 3) || (p[x-1] - '0' == 1 && x == 4 && i <= 2)
                     || (p[x-1] - '0' == 0 && x == 4 && i > 0) || x > 5){
                printf("%c", c);
                p[x++] = c;
            }
            if (x == 2 || x == 5) {
                printf("/");
                p[x++] = '/';
            }
        }else if (c == '\r' && x == 10) sortie = 1;

        if (x == 2 || x == 5) {
            printf("%c", '\b');
            printf("%c", ' ');
            printf("%c", '\b');
            x= x--;
        }

        if(c == '\b' && x > 0){
            printf("%c", '\b');
            printf("%c", ' ');
            printf("%c", '\b');
            x--;
            if (x == 2 || x == 5) {
                printf("%c", '\b');
                printf("%c", ' ');
                printf("%c", '\b');
                x= x--;
            }
        }
    } while(sortie == 0);
    p[x] = '\0';  // rendre p une chaine de caractere

    return p; // retourner le mot de passe
}

char* getpass()
{
    static char  a[50];
    char* p;
    char  c; // Chaque caractere du mot de passe
    int   x; // position du caractere dans le mot de passe

    p = a;      // pointer le mot de passe
    c = getch(); // lecture du premier caractere
    x = 0;       // initialise l'index

    // boucle jusqu'a ce que l'utilisateur presse enter
    while (c != '\r')
    {
        if (c != '\b') {//ignorer le backspace
            putch('*');  // afficher * a la place de chaque caractere du mot de passe
            p[x++] = c;  // ajouter le caractere dans le mot de passe
        }

        if(c == '\b' && x > 0){
            printf("%c", '\b');
            printf("%c", ' ');
            printf("%c", '\b');
            x--;
        }
        c = getch(); // lecture du caractere suivant
    }
    p[x] = '\0';  // rendre p une chaine de caractere

    return p; // retourner le mot de passe
}

int get_age()
{
    static char  a[3];
    char* p;
    char  c; // Chaque caractere du mot de passe
    int   x; // position du caractere dans le mot de passe

    p = a;      // pointer le mot de passe
    c = getch(); // lecture du premier caractere
    x = 0;       // initialise l'index

    // boucle jusqu'a ce que l'utilisateur presse enter
    while (c != '\r')
    {
        if (isdigit(c) && x < 3) {//ignorer le backspace
            printf("%c", c);  // afficher * a la place de chaque caractere du mot de passe
            p[x++] = c;  // ajouter le caractere dans le mot de passe
        }

        if(c == '\b' && x > 0){
            printf("%c", '\b');
            printf("%c", ' ');
            printf("%c", '\b');
            x--;
        }
        c = getch(); // lecture du caractere suivant
    }
    p[x] = '\0';  // rendre p une chaine de caractere

    return atoi(p); // retourner le mot de passe
}


liste *ajouter_emp(liste *emp_list, employe *emp){
    emp->suivant = NULL; /* On fait pointer suivant vers NULL */
    if (emp_list->fin == NULL) /* Cas où notre liste est vide (pointeur vers fin de liste à  NULL) */
    {
        emp->precedent = NULL; /* On fait pointer p_prev vers NULL */
        emp_list->debut = emp; /* On fait pointer la tête de liste vers le nouvel élément */
        emp_list->fin = emp; /* On fait pointer la fin de liste vers le nouvel élément */
    }
    else /* Cas où des éléments sont déjà présents dans notre liste */
    {
        emp_list->fin->suivant = emp; /* On relie le dernier élément de la liste vers notre nouvel élément (début du chaînage) */
        emp->precedent = emp_list->fin; /* On fait pointer p_prev vers le dernier élément de la liste */
        emp_list->fin = emp; /* On fait pointer la fin de liste vers notre nouvel élément (fin du chaînage: 3 étapes) */
    }
    emp_list->taille++; /* Incrémentation de la taille de la liste */

    return emp_list; /* on retourne notre nouvelle liste */
}

liste *ajouter_debut(liste *emp_list, employe *nouveau_emp){
    nouveau_emp->precedent = NULL;
    if (emp_list->fin == NULL)
    {
        nouveau_emp->suivant = NULL;
        emp_list->debut = nouveau_emp;
        emp_list->fin = nouveau_emp;
    }
    else
    {
        emp_list->debut->precedent = nouveau_emp;
        nouveau_emp->suivant = emp_list->debut;
        emp_list->debut = nouveau_emp;
    }
    emp_list->taille++;
    ecrire_liste(emp_list);
    return emp_list;
}

liste *inserer_avant(liste *emp_list, char code_element[50]){
    employe *actual_emp = malloc(sizeof *actual_emp);
    actual_emp = emp_list->debut;
    int i;
    for (i = 0; i < emp_list->taille; i++)
    {
        if (strcmp(actual_emp->code, code_element) == 0)
        {
            employe *nouveau_emp = malloc(sizeof *nouveau_emp);
            nouveau_emp = saisie_employe(emp_list);
            if (actual_emp->precedent == NULL)
            {
               emp_list = ajouter_debut(emp_list, nouveau_emp);
               break;
            }
            else
            {
                nouveau_emp->precedent = actual_emp->precedent;
                nouveau_emp->suivant = actual_emp;
                actual_emp->precedent->suivant = nouveau_emp;
                actual_emp->precedent = nouveau_emp;
                emp_list->taille++;
                break;
            }
        }else{
            actual_emp = actual_emp->suivant;
        }

    }
    if (i == emp_list->taille) {
        printf("Ce code n'existe pas\n");
        return NULL;
    }else ecrire_liste(emp_list);
    return emp_list;
}

liste *inserer_avant2(liste *emp_list, employe *nouveau_emp, char code_element[50]){
    employe *actual_emp = emp_list->debut;
    int i;
    for (i = 0; i < emp_list->taille; i++)
    {
        if (strcmp(actual_emp->code, code_element) == 0){
            if (actual_emp->precedent == NULL){
               emp_list = ajouter_debut(emp_list, nouveau_emp);
               break;
            }
            else{
                nouveau_emp->precedent = actual_emp->precedent;
                nouveau_emp->suivant = actual_emp;
                actual_emp->precedent->suivant = nouveau_emp;
                actual_emp->precedent = nouveau_emp;
                emp_list->taille++;
                break;
            }
        }else{
            actual_emp = actual_emp->suivant;
        }

    }
    if (i == emp_list->taille) {
        printf("Ce code n'existe pas\n");
        return NULL;
    }else ecrire_liste(emp_list);
    return emp_list;
}

liste *inserer_apres(liste *emp_list, char code_element[50]){
    employe *actual_emp = malloc(sizeof *actual_emp);
    actual_emp = emp_list->debut;
    int i;
    for (i = 0; i < emp_list->taille; i++)
    {
        if (strcmp(actual_emp->code, code_element) == 0)
        {
            employe *nouveau_emp = malloc(sizeof *nouveau_emp);
            nouveau_emp = saisie_employe(emp_list);
            if (actual_emp->suivant == NULL)
            {
               emp_list = ajouter_fin(emp_list, nouveau_emp);
               break;
            }
            else
            {
                nouveau_emp->suivant = actual_emp->suivant;
                nouveau_emp->precedent = actual_emp;
                actual_emp->suivant->precedent = nouveau_emp;
                actual_emp->suivant = nouveau_emp;
                emp_list->taille++;
                break;
            }
        }else{
            actual_emp = actual_emp->suivant;
        }

    }
    if (i == emp_list->taille) {
        printf("Ce code n'existe pas\n");
    } else ecrire_liste(emp_list);
    return emp_list;
}

liste *inserer_apres2(liste *emp_list, employe *nouveau_emp, char code_element[50]){
    employe *actual_emp = malloc(sizeof *actual_emp);
    actual_emp = emp_list->debut;
    int i;
    for (i = 0; i < emp_list->taille; i++)
    {
        if (strcmp(actual_emp->code, code_element) == 0)
        {
            if (actual_emp->suivant == NULL)
            {
               emp_list = ajouter_fin(emp_list, nouveau_emp);
               break;
            }
            else
            {
                nouveau_emp->suivant = actual_emp->suivant;
                nouveau_emp->precedent = actual_emp;
                actual_emp->suivant->precedent = nouveau_emp;
                actual_emp->suivant = nouveau_emp;
                emp_list->taille++;
                break;
            }
        }else{
            actual_emp = actual_emp->suivant;
        }
    }
    if (i == emp_list->taille) {
        printf("Ce code n'existe pas\n");
    }else ecrire_liste(emp_list);
    return emp_list;
}

employe *effacer_premier(liste *emp_list){
    if (emp_list->taille != 0){
		if (emp_list->debut->suivant == NULL){
			emp_list-> debut = NULL;
			emp_list->fin = NULL;
		}else{
			emp_list->debut->suivant->precedent = NULL;
			emp_list->debut = emp_list->debut->suivant;
		}
		emp_list->taille--;
		ecrire_liste(emp_list);
		printf("\nLe premier employe de la liste est supprime\n");
    }else
        printf("\nAucun n'employe n'est encore enregistre\n");
    return emp_list;
}

employe *effacer_dernier(liste *emp_list){
    if (emp_list->taille != 0){
		if (emp_list->fin->precedent == NULL){
			emp_list-> debut = NULL;
			emp_list->fin = NULL;
		}else{
			emp_list->fin->precedent->suivant = NULL;
			emp_list->fin = emp_list->fin->precedent;
		}
		emp_list->taille--;
		ecrire_liste(emp_list);
        printf("\nLe dernier employe de la liste est supprime\n");
    }else
        printf("\nAucun n'employe n'est encore enregistre\n");

    return emp_list;
}

liste *effacer_position(liste *emp_list, int position){
    if (emp_list != NULL)
    {
        employe *temp = emp_list->debut;
        int i = 1;
        while (temp != NULL && i <= position)
        {
            if (position == i)
            {
                if (temp->suivant == NULL)
                {
                    emp_list->fin = temp->precedent;
                    emp_list->fin->suivant = NULL;
                }
                else if (temp->precedent == NULL)
                {
                    emp_list->debut = temp->suivant;
                    emp_list->debut->precedent = NULL;
                }
                else
                {
                    temp->suivant->precedent = temp->precedent;
                    temp->precedent->suivant = temp->suivant;
                }
                free(temp);
                emp_list->taille--;
            }
            else
            {
                temp = temp->suivant;
            }
            i++;
        }
        ecrire_liste(emp_list);
    }
    return emp_list;
}

employe *recherche_employe(liste *emp_list, char code_element[50]){
    employe *actual_emp = emp_list->debut;
    int i;
    for (i = 0; i < emp_list->taille; i++)
    {
        if (strcmp(actual_emp->code, code_element) == 0)
        {
            return actual_emp;
        }else{
            actual_emp = actual_emp->suivant;
        }

    }
    if (i == emp_list->taille) {printf("\nCe code n'existe pas\n");}
    return NULL;
}

void afficher_liste(liste *l){
    if (l != NULL)
    {
        printf("\n=======================================================\n");
        employe *emp = l->debut;
        if(emp == NULL)
            printf("Aucun employe n'a ete encore enregistre\n");
        while (emp != NULL)
        {
            printf("Code : %s\n", emp->code);
            printf("Nom : %s\n", emp->nom);
            printf("Prenom : %s\n", emp->prenom);
            printf("Date d'embauche : %s\n", emp->embdate);
            printf("Age : %d\n", emp->age);
            emp = emp->suivant;
            if (emp != NULL)
                printf("-------------------------------------------------------\n");
        }
    }
    printf("\n=======================================================\n");
}

void afficher_liste_arr(liste *l){
    if (l->taille >= 1){
        liste *liste_arr = new_liste();

        employe *emp_temp1;

        employe *empl = l->debut;
        while (empl != NULL){
            employe *emp_arr = malloc(sizeof *emp_arr);
            memcpy(emp_arr, empl, sizeof *emp_arr);
            employe *emp_temp2 = malloc(sizeof *emp_temp2);
            if (liste_arr->debut == NULL){
                ajouter_debut(liste_arr, emp_arr);
                emp_temp1 = liste_arr->debut;
            }else{
                memcpy(emp_temp2, emp_arr, sizeof *emp_temp2);
                while(strcmp(emp_arr->nom, emp_temp1->nom)>=0 && emp_temp1->suivant != NULL){
                    emp_temp1 = emp_temp1->suivant;
                }
                if(strcmp(emp_arr->nom, emp_temp1->nom)<=0){
                    inserer_avant2(liste_arr, emp_temp2, emp_temp1->code);
                }else{
                    inserer_apres2(liste_arr, emp_temp2, emp_temp1->code);
                }
            }
            empl = empl->suivant;
        }
        afficher_liste(liste_arr);
    }
    afficher_liste(l);

}

void ecrire_employe(employe *emp){
    FILE *fichier = fopen("employes.doc", "a+");
    if (fichier != NULL){
        // On l'écrit dans le fichier
        fprintf(fichier, "%s;\t%s;\t%s;\t%s;\t%d\n", emp->code, emp->nom, emp->prenom, emp->embdate, emp->age);
        fclose(fichier);
    }

}

void ecrire_liste(liste *l){
    FILE *fichier = fopen("employes.doc", "w+");
    employe *emp = l->debut;
    if (fichier != NULL){
        // On l'écrit dans le fichier
        while(emp != NULL){
            ecrire_employe(emp);
            emp = emp->suivant;
        }
        fclose(fichier);
    }
}

liste *lire_liste(){
    char temp[500];
    FILE* fichier = fopen("employes.doc", "r");
    liste *l = new_liste();
    if (fichier != NULL)
    {
        while(fgets(temp, 500, fichier)){
            employe *emp = malloc(sizeof *emp);
            sscanf(temp, "%[^;]; %[^;]; %[^;]; %[^;]; %d", &emp->code, &emp->nom, &emp->prenom, &emp->embdate, &emp->age);
            ajouter_emp(l, emp);
        }
        fclose(fichier);
    }else{
        printf("\n\nVous n'aviez encore enregistre aucun employe\nTapez n'importe quelle touche pour continuer ");
        getch();
    }
    return l;
}

int nettoyer(){
    while (getchar()!='\n');
    return 1;
}

employe *saisie_employe(liste *l){
    employe *emp = malloc(sizeof *emp);

    char code_temp[50]; int i, existe;
    if (emp != NULL){
		//saisie du code de l'employe
        do{
            existe = 0;
            printf("\nEntrer le code de l'employe\n");
            printf("\tCode : ");
            scanf("%s", &code_temp);
            nettoyer();

            //verifier si le code existe deja
            employe *employe_temp = l->debut;
            if(l->taille >0){
                for (i = 0; i < l->taille; i++){
                    if(strcmp(code_temp, employe_temp->code) == 0){
                        existe = 1;
                        printf("Ce code existe deja\n");
                        break;
                    }
                    employe_temp = employe_temp->suivant;
                }
            }
        }while(existe == 1);
        strcpy(emp->code, code_temp);

		printf("\nSaisie du nom complet de l'employe\n");
        //saisie du nom
        printf("\tNom : ");
        lirechaine(emp->nom, sizeof emp->nom);
		while(verifier_nom(emp->nom) == 0){
			printf("\tLe nom ne doit pas contenir de chiffre\n");
			printf("\tNom : ");
			lirechaine(emp->nom, sizeof emp->nom);
		}

        //saisie du prenom
        printf("\tPrenom : ");
        lirechaine(emp->nom, sizeof emp->nom);
		while(verifier_nom(emp->prenom) == 0){
			printf("Le prenom ne doit pas contenir de chiffre\n");
			printf("\tPrenom : ");
			lirechaine(emp->prenom, sizeof emp->prenom);
		}

        //saisie de la date d'embauche
        printf("\nEntrer la date d'embauche en tenant compte du format ci-dessous.\n\t\tJJ/MM/AAAA\n");
		printf("\tDate :\t");
        strcpy(emp->embdate, get_date());

        //saisie de l'age de l'employe
        printf("\n\nEntrer l'age de l'employe\n");
		printf("\tAge : ");
        emp->age = get_age();
    }

    return emp;
}

employe *modifier_employe(liste *l, char code[50]){
    employe *emp = recherche_employe(l, code);

    int i, existe;
    if (emp != NULL){
		//copie du code de l'employe
        strcpy(emp->code, code);

        printf("\nSaisie du nom complet de l'employe\n");
        //saisie du nom
        printf("\tNom : ");
        lirechaine(emp->nom, sizeof emp->nom);
		while(verifier_nom(emp->nom) == 0){
			printf("\tLe nom ne doit pas contenir de chiffre\n");
			printf("\tNom : ");
			lirechaine(emp->nom, sizeof emp->nom);
		}

        //saisie du prenom
        printf("\tPrenom : ");
        lirechaine(emp->prenom, sizeof emp->prenom);
		while(verifier_nom(emp->prenom) == 0){
			printf("\tLe prenom ne doit pas contenir de chiffre\n");
			printf("\tPrenom : ");
			lirechaine(emp->prenom, sizeof emp->prenom);
		}

        //saisie de la date d'embauche
        printf("\nEntrer la date d'embauche de l'employe\n");
		printf("Date d'embauche : ");
        lirechaine(emp->embdate, sizeof emp->embdate);

        //saisie de l'age de l'employe
        printf("\nEntrer l'age de l'employe\n");
		printf("Age : ");
        scanf("%d", &emp->age);
        nettoyer();
        ecrire_liste(l);
    }

    return emp;
}

void afficher_employe(employe *emp){
    printf("Code : %s\n", emp->code);
    printf("Nom : %s\n", emp->nom);
    printf("Prenom : %s\n", emp->prenom);
    printf("Date d'embauche : %s\n", emp->embdate);
    printf("Age : %d\n", emp->age);
}

void lirechaine(char chaine[], int size) {
    fgets(chaine, size, stdin);
    chaine[strlen(chaine) - 1] = '\0';
}

int login(){
    FILE* fichier = fopen("account.txt", "r");
    char temp[500];
    char username[50], password[50];
    char u[50], p[50];
    int essaie = 0;
    if (fichier != NULL)
    {
        fgets(temp, 500, fichier);
        sscanf(temp, "%[^;]; %[^;]", &username, &password);
        fclose(fichier);
    }
    decrypt(username);
    decrypt(password);
	printf("\n*** CE PROGRAMME GERE DES INFORMATIONS D'UNE LISTE D'EMPLOYES ***\n");
	printf("\nConnecter pour acceder au informations sur les employes\n");
    do{
        printf("\nUsername : ");
        lirechaine(u, 50);
        printf("Password : ");
        strcpy(p, getpass());
        essaie++;
        system("cls");
        if(strcmp(u,username) != 0 || strcmp(p, password)!= 0){
            printf("\n*** CE PROGRAMME GERE DES INFORMATIONS D'UNE LISTE D'EMPLOYES ***\n");
            printf("\nConnecter pour acceder aux informations sur les employes\n");
            printf("\nMot de Passe ou nom d'utilisateur incorrect!\nIl vous reste %d essaie(s)\n", 4 - essaie);
        }
        if (essaie == 4){
            printf("Vous avez excede le nombre d'essais\n");
            printf("Au revoir");
            exit(0);
        }

    } while(strcmp(u,username) != 0 || strcmp(p, password)!= 0);
    printf("Connection effectuer avec success!\n\nPresser n'importe quelle touche pour acceder au menu");
    getch();
    return 0;
}

int change_password(){
    FILE* fichier = fopen("account.txt", "r");
    char temp[500];
    char username[50], password[50];
    char newu[50], newp[50], oldp[50];
    int essaie =0;
    if (fichier != NULL)
    {
        fgets(temp, 500, fichier);
        fclose(fichier);
        sscanf(temp, "%[^;]; %[^;]", &username, &password);
        decrypt(username);
        decrypt(password);
        printf("CHANGEMENT DE MOT DE PASSE\n\n");
        printf("\nNouveau Username : ");
        lirechaine(newu, 50);
        printf("Nouveau Password : ");
        strcpy(newp, getpass());
        printf("\nAncien Password : ");
        strcpy(oldp, getpass());
        essaie++;
        while(strcmp(oldp, password)!= 0  && essaie < 4){
                system("cls");
                printf("CHANGEMENT DE MOT DE PASSE\n\n");
                printf("Mot de Passe incorrect!\nVeuiller reentrer l'ancien mot de passe.\n");
                printf("Il vous reste %d essaies", 4-essaie);
                printf("\n\nNouveau Username : %s", newu);
                printf("\nAncien Password : ");
                strcpy(oldp, getpass());
                essaie++;
        }
        if(essaie == 4){
            printf("\nMot de passe ou nom d'utilisateur non change!\n\nPresser n'importe quelle touche pour retourner au menu principal");
            getch();
        }else{
            FILE* fichier = fopen("account.txt", "w+");
            fprintf(fichier, "%s; %s", encrypt(newu), encrypt(newp));
            printf("\n\nMot de passe ou nom d'utilisateur change avec success!\n\nPresser n'importe quelle touche pour retourner au menu principal");
            fclose(fichier);
            getch();
        }
    }
return 0;
}

void menu(){
    system("cls");
    printf("\t            *****   MENU PRINCIPAL *****\n\n");
    printf("Choississez une action a effectuer en entrant son numero correspondant\n");
    printf(" ------------------------------------------------------------------------\n");
    printf("|  NO\tACTION                                                           |\n");
    printf("|  1\tInsertion d'un employe au debut de la liste d'employes           |\n");
    printf("|  2\tInsertion d'un employe a la fin de la liste d'employes           |\n");
    printf("|  3\tInsertion d'un employe avant un autre dans la liste d'employes   |\n");
    printf("|  4\tInsertion d'un employe apres un autre dans la liste d'employes   |\n");
    printf("|  5\tSuppression du premier employe de la liste d'employes            |\n");
    printf("|  6\tSuppression du dernier employe de la liste d'employes            |\n");
    printf("|  7\tSuppression d'un employe selon sa position dans liste d'employes |\n");
    printf("|  8\tAffichage de l'ensemble des employes par ordre alphabetique      |\n");
    printf("|  9\tRecherche d'un employe dans la liste à partir de son code        |\n");
    printf("|  10\tModification des informations d’un employe dans la liste         |\n");
    printf("|  11\tAffichage des employes dans l'ordre de saisie de la liste        |\n");
    printf("|  12\tChangement du nom d'utilisateur et du mot de passe               |\n");
    printf("|  13\tSortie du programme                                              |\n");
    printf(" ------------------------------------------------------------------------\n\n");
	printf("Votre choix : ");
}

char *encrypt(char *s){
	int i, l = strlen(s);
	for(i = 0; i < l; i++)
		s[i] += 14;
	return s;
}

char *decrypt(char *s){
	int i, l = strlen(s);
	for(i = 0; i < l; i++)
		s[i] -= 14;
	return s;
}



