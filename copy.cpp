#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *source, *destination;
    char ch;
    char line[256];

    // Open the source file in read mode
    source = fopen("source.txt", "r");
    if (source == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    // Open the destination file in write mode
    destination = fopen("destination.txt", "w");
    if (destination == NULL) {
        printf("Error opening destination file.\n");
        fclose(source);
        return 1;
    }

    // Copying contents character by character
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }

    // Close the files after character-by-character copy
    fclose(source);
    fclose(destination);

    // Re-open the source file to copy line by line
    source = fopen("source.txt", "r");
    if (source == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    // Open the destination file in write mode again
    destination = fopen("destination.txt", "a");
    if (destination == NULL) {
        printf("Error opening destination file.\n");
        fclose(source);
        return 1;
    }

    // Copying contents line by line
    while (fgets(line, sizeof(line), source)) {
        fputs(line, destination);
    }

    // Close the files after line-by-line copy
    fclose(source);
    fclose(destination);

    printf("File copied successfully (character by character and line by line)!\n");
    return 0;
}
