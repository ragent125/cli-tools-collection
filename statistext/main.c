#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 256
#define MAX_BUFFER 4096

int is_delimiter(char c) {
    return isspace(c) || ispunct(c);
}

void to_lowercase(char *word) {
    for(int i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);
    }
}

void extract_words(char *line) {
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
                printf("Mot trouvé: %s\n", word); 
                word_index = 0;         
            }
        } 
    }

    // Traiter le dernier mot s'il existe
    if (word_index > 0) {
        word[word_index] = '\0';
        to_lowercase(word);
        printf("Mot trouvé: %s\n", word);
    }
}

int main(int argc, char *argv[]) {
    printf("\nStatistext - Les mots qui comptent !\n");
    printf("Version 0.2 - Lecture de fichier et extraction des mots\n\n");

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

    printf("Analyse du fichier : %s\n", filename);
    printf("==================================================\n\n");

    char buffer[MAX_BUFFER];
    while (fgets(buffer, MAX_BUFFER, fp) != NULL) {
        extract_words(buffer);
    }
    
    printf("\n==================================================\n");
    printf("Analyse terminée.\n");

    fclose(fp);
    
    return 0;
}