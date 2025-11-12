#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Statistext - Les mots qui comptent !\n");
    printf("Version 0.1 - Initialisation\n\n");
    
    /*
    - Un seul et unique fichier analysé
    - Extension <.txt>
    */

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
    
    printf("Analyse du fichier : %s\n", filename);
    printf("(Fonctionnalité à implémenter)\n");
    
    return 0;
}