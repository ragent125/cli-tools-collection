#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 256
#define MAX_BUFFER 4096
#define TAB_SIZE 100

// SD: Dictionnaire dynamique
typedef struct {
    char word[MAX_WORD_LENGTH];
    int occurrence;
} WordOccurrence;

int is_delimiter(char c) {
    return isspace(c) || ispunct(c);
}

void to_lowercase(char *word) {
    for(int i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);
    }
}

int find_word(WordOccurrence *tab, int tab_used, char *word) {
    for (int i = 0; i < tab_used; i++) {
        if (strcmp(tab[i].word, word) == 0)
            return i;
    }
    return -1;
}

void add_word(WordOccurrence **ptab, int *ptab_size, int *ptab_used, char *word) {
    // Déréférencement des pointeurs
    WordOccurrence *tab = *ptab;
    int tab_size = *ptab_size;
    int tab_used = *ptab_used;

    int index = find_word(tab, tab_used, word);

    if (index >= 0) {
        tab[index].occurrence++;
    } else {
        // Algorithme de redimensionnement dynamique, si nécessaire
        if (tab_used >= tab_size) {
            tab_size *= 2;
            tab = realloc(tab, tab_size * sizeof(WordOccurrence));
            if (tab == NULL) {
                printf("Erreur : mémoire insuffisante\n");
                exit(1);
            }
            // Mise à jour des pointeurs
            *ptab = tab;
            *ptab_size = tab_size;
        }

        // Ajout du nouveau mot + maj du pointeur
        strncpy(tab[tab_used].word, word, MAX_WORD_LENGTH);     // Tableau non assignable => strncpy
        tab[tab_used].word[MAX_WORD_LENGTH - 1] = '\0';
        tab[tab_used].occurrence = 1;
        *ptab_used = tab_used + 1;
    }
}

void extract_words(char *line, WordOccurrence **ptab, int *ptab_size, int *ptab_used) {
    char word[MAX_WORD_LENGTH];
    int word_index = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        char c = line[i];

        if (!is_delimiter(c)) {
            if (word_index < MAX_WORD_LENGTH - 1) {
                word[word_index] = c;
                word_index++;
            }
        } else {
            if (word_index > 0) {
                word[word_index] = '\0';  
                to_lowercase(word);        
                add_word(ptab, ptab_size, ptab_used, word);     // Ajout du mot au tableau
                word_index = 0;         
            }
        } 
    }

    // Dernier mot dans la ligne
    if (word_index > 0) {
        word[word_index] = '\0';
        to_lowercase(word);
        add_word(ptab, ptab_size, ptab_used, word);
    }
}

int main(int argc, char *argv[]) {

    // Vérification des arguments
    if (argc != 2) {
        printf("Usage: %s <fichier.txt>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    size_t file_len = strlen(filename);

    if (file_len < 4 || strcmp(filename + file_len - 4, ".txt") != 0) {
        printf("Erreur: Le fichier doit avoir l'extension .txt\n");
        return 1;
    }

    // Ouverture du fichier
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier '%s'\n", filename);
        return 1;
    }

    printf("\nStatistext - Les mots qui comptent !\n");
    printf("Version 0.3 - Comptage dynamique\n\n");

    int tab_size = TAB_SIZE;
    int tab_used = 0;

    WordOccurrence *tab = malloc(tab_size * sizeof(WordOccurrence));
    if (tab == NULL) {
        printf("Erreur : mémoire insuffisante\n");
        fclose(fp);
        return 1;
    }

    // Lecture du fichier ligne par ligne
    char buffer[MAX_BUFFER];
    while (fgets(buffer, MAX_BUFFER, fp) != NULL) {
        extract_words(buffer, &tab, &tab_size, &tab_used);
    }
    fclose(fp);

    // Tri par insertion (à la main)
    for (int i = 1; i < tab_used; i++) {
        WordOccurrence selected = tab[i];
        int j = i - 1;

        // Compare par occurrence décroissante, puis compare par mot croissant
        while (j >= 0 && (tab[j].occurrence < selected.occurrence || (tab[j].occurrence == selected.occurrence && strcmp(tab[j].word, selected.word) > 0))) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = selected;
    }

    // Affichage des résultats
    printf("Analyse du fichier : %s\n", filename);
    printf("==================================================\n\n");

    printf("|%-20s |%s\n", "Mot", "Occurrence");
    printf("%-20s %s\n", "|--------------------", "|----------");

    for (int i = 0; i < tab_used; i++) {
        if(tab[i].occurrence >= 1) {
            printf("|%-20s | %d\n", tab[i].word, tab[i].occurrence);
        }      
    }

    printf("\n==================================================\n");
    printf("Analyse terminée.\n");

    free(tab);
    
    return 0;
}