#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *mon_fichier;
char curr_char = '\0';

void amorcer()
{
    mon_fichier = fopen("test1.txt", "r");
    if (mon_fichier == NULL)
    {
        printf("Probleme de fichier\nLe creer ?\n");
        int test = 0;
        (scanf("%d", &test) ? mon_fichier = fopen("test1.txt", "w") : 0);
        exit(-1);
    }
    lire_caractere();
}

void lire_caractere()
{
    curr_char = fgetc(mon_fichier);
    printf("%c", curr_char);
}


void consommer_terminal(char terminal)
{
  if (terminal != curr_char)
  {
    fprintf(stderr, "Erreur : caractere attendu : %c, caractere trouve : %c\n", terminal, curr_char);
    exit(1);
  }
  lire_caractere();
}

void passer_espaces()
{
  while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
  {
    lire_caractere();
  }
}

void lire_balise(char *nom_balise)
{
  consommer_terminal('<');
  // Utilisation de  size_t au lieu de int pour l'avertissement.
  for (size_t i = 0; i < strlen(nom_balise); i++)
  {
    consommer_terminal(nom_balise[i]);
  }
  consommer_terminal('>');
}

void lire_balise_partielle(char *nom_balise)
{
  // pareil qu'au-dessus
  for (size_t i = 0; i < strlen(nom_balise); i++)
  {
    consommer_terminal(nom_balise[i]);
  }
  consommer_terminal('>');
}

void annexes()
{
  while (curr_char != EOF)
  {
    lire_balise("annexe");
    contenu();
    passer_espaces();
    lire_balise("/annexe");
  }
}

void document()
{
  lire_balise("document");
  contenu();
  passer_espaces();
  lire_balise("/document");
}
void texte_enrichi()
{
  passer_espaces();
  document();
  passer_espaces();
  annexes();
}

/*
char* stocker_balise(){
  char buffer[81];
  consommer_terminal('<');
  size_t cpt = 0;
  while(curr_char != '>'){
    buffer[cpt++] = curr_char;
  }
  consommer_terminal('>');
  buffer[cpt] = '\0';
  return buffer;
}
*/

void contenu()
{
  char* buffer[81];
  while(strcmp(buffer, "/annexe") && strcmp(buffer, "/document")){
    strcpy(buffer, "");
    passer_espaces();
    // On lit et stocke la balise
    if(curr_char == '<'){
      consommer_terminal('<');
      size_t cpt = 0;
      while(curr_char != '>'){
        buffer[cpt++] = curr_char;
        lire_caractere();
      }
      consommer_terminal('>');
      if(!strcmp(buffer, "section")){
        section();
      }
      else if(!strcmp(buffer, "titre")){
        titre();
      }
      else if (!strcmp(buffer, "liste")){
        liste();
      }
    }else{
      mot_enrichi();
    }
  }
}

void section()
{
  lire_balise("section");
  passer_espaces();
  contenu();
  lire_balise("/section");
}

void titre()
{
  lire_balise("titre");
  passer_espaces();
  texte();
  lire_balise("/titre");
}

void liste()
{
  lire_balise("liste");
  passer_espaces();

  while (curr_char != EOF && curr_char != '<') // pas certain de l'autre condition m'enfin
  {
    item();
    passer_espaces();
  }

  lire_balise("/liste");
}

void item()
{
  lire_balise("item");
  passer_espaces();
  //  texte_liste();
  lire_balise("/item");
}

void liste_texte()
{
  if (curr_char == '<')
  {
    liste();
    texte_liste();
  }
  // epsilon
}

void texte_liste()
{
  texte();
  passer_espaces();
  if (curr_char == '<')
  {
    liste_texte();
  }
  // epsilon
}

void texte()
{
  while (curr_char != EOF && curr_char != '<')
  {
    /* mot_enrichi(); */
    passer_espaces();
  }
}

void mot_enrichi()
{
  // aucune idée
}



void mot_important()
{
  // aucune idée
}

int main()
{

  amorcer();
  texte_enrichi();
  fclose(mon_fichier);

  return 0;
}