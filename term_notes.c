#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NOTES 100

typedef struct {
    int id;
    char content[100];
} Note;

void addNote() {
    fflush(stdin);

    printf("Enter the note: ");
    char content[100];
    fgets(content, sizeof(content), stdin);

    FILE *file = fopen("notes.txt", "a");
    if (file != NULL) {
        int id = 1;
        fseek(file, 0, SEEK_END);
        if (ftell(file) != 0) {
            fseek(file, -sizeof(Note), SEEK_END);
            Note lastNote;
            fread(&lastNote, sizeof(Note), 1, file);
            id = lastNote.id + 1;
        }

        Note newNote;
        newNote.id = id;
        strcpy(newNote.content, content);

        fwrite(&newNote, sizeof(Note), 1, file);
        fclose(file);
        printf("Note added successfully with ID: %d\n", id);
    } else {
        fprintf(stderr, "Unable to open the notes file.\n");
    }
}

void editNote() {
    fflush(stdin);

    int id;
    printf("Enter the note ID to edit: ");
    scanf("%d", &id);

    FILE *file = fopen("notes.txt", "r+");
    if (file != NULL) {
        Note note;
        int found = 0;
        while (fread(&note, sizeof(Note), 1, file) == 1) {
            if (note.id == id) {
                found = 1;
                char tempFileName[20];
                sprintf(tempFileName, "temp_note_%d.txt", id);
                FILE *tempFile = fopen(tempFileName, "w");
                if (tempFile != NULL) {
                    fprintf(tempFile, "%s", note.content);
                    fclose(tempFile);
                    char nanoCommand[50];
                    sprintf(nanoCommand, "nano %s", tempFileName);
                    system(nanoCommand);
                    FILE *updatedFile = fopen(tempFileName, "r");
                    if (updatedFile != NULL) {
                        fgets(note.content, sizeof(note.content), updatedFile);
                        fclose(updatedFile);
                        fseek(file, -sizeof(Note), SEEK_CUR);
                        fwrite(&note, sizeof(Note), 1, file);
                        fclose(file);
                        printf("Note updated successfully.\n");
                        remove(tempFileName);
                    } else {
                        fprintf(stderr, "Unable to open the temporary file.\n");
                    }
                } else {
                    fprintf(stderr, "Unable to create the temporary file.\n");
                }
                break;
            }
        }
        if (!found) {
            printf("Note with ID %d not found.\n", id);
        }
    } else {
        fprintf(stderr, "Unable to open the notes file.\n");
    }
}

void showNotes() {
    FILE *file = fopen("notes.txt", "r");
    if (file != NULL) {
        printf("**** Notes Menu ****\n");
        printf("1. Add a note\n");
        printf("2. Show all notes\n");
        printf("3. Edit a note\n");
        printf("4. Delete a note\n");
        printf("0. Exit\n");
        printf("*******************\n");

        Note notes[MAX_NOTES];
        int numNotes = 0;
        while (fread(&notes[numNotes], sizeof(Note), 1, file) == 1) {
            printf("%d. %s", notes[numNotes].id, notes[numNotes].content);
            numNotes++;
        }
        fclose(file);

        int option;
        printf("Enter an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addNote();
                break;
            case 2:
                // No additional action required to show the notes.
                break;
            case 3:
                editNote();
                break;
            case 4:
                // Implement deleteNote() function
                break;
            case 0:
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    } else {
        fprintf(stderr, "Unable to open the notes file.\n");
    }
}

int main() {
    printf("Welcome to the Notes Manager.\n");
    printf("2. Show all notes\n");
    printf("0. Exit\n");

    int option;
    scanf("%d", &option);

    switch (option) {
        case 2:
            showNotes();
            break;
        case 0:
            printf("Goodbye.\n");
            break;
        default:
            printf("Invalid option.\n");
            break;
    }

    return 0;
}
