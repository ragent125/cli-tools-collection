#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Statistext - Les mots qui comptent !\n");
    printf("Version 0.1 - En développement\n\n");
    
    // Vérifier qu'un fichier est fourni en argument
    if (argc != 2) {
        printf("Usage: %s <fichier.txt>\n", argv[0]);
        return 1;
    }
    
    printf("Analyse du fichier : %s\n", argv[1]);
    printf("(Fonctionnalité à implémenter)\n");
    
    return 0;
}
