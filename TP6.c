--------------------------------Exercice 1-------------------------------------
#include<stdio.h>

int main()
{
    FILE* fp;
    fp = fopen("donnees.txt","wt");
    /*I didn't specify the path because I'm already in a folder "C Files" , so the compiler will automatically recognize the path*/
    int age;
    float moy;
    char name[30];

    if(fp == NULL)
    {
        printf("Impossible d'ouvrir le fichier!\n");
        exit(1);/*if the 'fopen' function returned NULL it mains that it has failed to open the file , so no need to continue the program*/
    }

    printf("Tapez votre nom : ");
    scanf(" %s",name);
    printf("Tapez votre age : ");
    scanf("%d",&age);
    printf("La moyenne : ");
    scanf("%f",&moy);

    fprintf(fp,"%s\n%d\n%.2f\n",nom,age,moy);

    fclose(fp);
    return 0;
}

--------------------------------Exercice 2-------------------------------------
#include<stdio.h>

int main()
{
    FILE* fp;
    fp = fopen("donnees.txt","rt");
    char string[100];

    if(fp == NULL)
    {
        printf("Impossible d'ouvrir le fichier!\n");
        exit(1);
    }

    while( fgets(string,sizeof(string),fp) )
    printf("%s",string);

    fclose(fp);
    return 0;
}

--------------------------------Exercice 3-------------------------------------
#include<stdio.h>

int main()
{
    FILE* fsrc,*fdest;
    fsrc = fopen("source.txt","r");
    fdest = fopen("destination.txt","w");

    if(fp == NULL || fsrc == NULL || fdest == NULL )
    {
        printf("Impossible d'ouvrir le fichier!\n");
        exit(1);
    }

    char c;
    while( (c=fgetc(src)) != EOF )
    fputc(c,dest);

    fclose(fsrc);
    fclose(fdest);
    return 0;
}

--------------------------------Exercice 4-------------------------------------
#include<stdio.h>
#include<ctype.h>

int main()
{
    int caracteres=0,line=0,inWord=0,words=0;
    FILE* fp;
    fp = fopen("texte.txt","rt");

    strcpy(string,"Greatness");

    if(fp == NULL)
    {
        printf("Impossible d'ouvrir le fichier!\n");
        exit(1);
    }

    char c;
    while( (c=fgetc(fp)) != EOF )
    caracteres++;

    if(c == '\n')
    line++;

    if(isspace(c))
    inWord = 0;
    else if(!inWord)
    {
        inWord = 1;
        words++;
    }

    fclose(fp);
    return 0;
}