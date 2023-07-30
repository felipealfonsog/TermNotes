/*************************************

▀▀█▀▀ █▀▀ █▀▀█ █▀▄▀█ ░░ ▒█▄░▒█ █▀▀█ ▀▀█▀▀ █▀▀ █▀▀ 
░▒█░░ █▀▀ █▄▄▀ █░▀░█ ▀▀ ▒█▒█▒█ █░░█ ░░█░░ █▀▀ ▀▀█ 
░▒█░░ ▀▀▀ ▀░▀▀ ▀░░░▀ ░░ ▒█░░▀█ ▀▀▀▀ ░░▀░░ ▀▀▀ ▀▀▀


 Terminal Notes Utility written in C
 *************************************
 *  Simple: Create and manage notes from the terminal
 *************************************
 * Developed and engineered by 
 * Felipe Alfonso Gonzalez <f.alfonso@res-ear.ch>
 * Computer Science Engineer
 * Chile
 *************************************
 * To create the term_notes binary:
 *
 * 1. Extract the source code if needed:
 *    tar -xf term_notes.tar.gz
 *
 * 2. Compile the source code:
 *    gcc -o term_notes term_notes.c
 *
 * 3. Elevate to superuser (if necessary):
 *    sudo su
 *
 * 4. Move the binary to the system bin directory:
 *    mv term_notes /usr/local/bin/
 *
 * 5. Exit superuser mode:
 *    exit
 *
 * 6. You can now run term_notes from the terminal:
 *    term_notes
 *
 *************************************
 * Please note that term_notes requires the following dependencies:
 * - Nano: A text editor (sudo apt-get install nano)
 * - Vim: A text editor (sudo apt-get install vim)
 *
 * If any of these dependencies are not installed, please install them
 * using the provided commands.
 *
 * For more information, please refer to the documentation.
 *************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libproc.h>
#include <mach-o/dyld.h>
#include <limits.h>


#define MAX_NOTES 100

typedef struct {
    int id;
    char content[100];
} Note;


void createFiles() {
    struct stat st;
    FILE *file = fopen("notes.txt", "r");
    if (file == NULL) {
        file = fopen("notes.txt", "w");
        if (file != NULL) {
            fclose(file);
            printf("Created notes.txt\n");
        } else {
            fprintf(stderr, "Unable to create notes.txt\n");
            return;
        }
    } else {
        fclose(file);
    }
}

void moveBinaryToDestination() {
    struct stat st; 
    char binaryPath[PROC_PIDPATHINFO_MAXSIZE];
    pid_t pid = getpid();
    int ret = proc_pidpath(pid, binaryPath, sizeof(binaryPath));
    if (ret <= 0) {
        fprintf(stderr, "Error retrieving binary path. Error code: %d\n", ret);
        return;
    }

    char destDirectory[100];
    #if defined(__linux__)
    if (stat("/etc/arch-release", &st) == 0) {
        snprintf(destDirectory, sizeof(destDirectory), "/usr/local/bin/");
    } else if (stat("/etc/debian_version", &st) == 0) {
        snprintf(destDirectory, sizeof(destDirectory), "/usr/bin/");
    } else {
        snprintf(destDirectory, sizeof(destDirectory), "/usr/local/bin/");
    }
    #elif defined(__APPLE__)
    snprintf(destDirectory, sizeof(destDirectory), "/usr/local/bin/");
    #else
    snprintf(destDirectory, sizeof(destDirectory), "."); 
    #endif

    char destPath[150];
    snprintf(destPath, sizeof(destPath), "%s/term-notes", destDirectory);

    if (rename(binaryPath, destPath) == 0) {
        printf("term-notes binary moved to %s\n", destDirectory);
    } else {
        fprintf(stderr, "Failed to move term-notes binary to %s\n", destDirectory);
    }
}


void addNote() {
    fflush(stdin);

    printf("Enter the note content: ");
    char content[100];
    fgets(content, sizeof(content), stdin);

    printf("Choose the editor (1. Nano, 2. Vim, 3. Neovim): ");
    int editorChoice;
    while (scanf("%d", &editorChoice) != 1 || editorChoice < 1 || editorChoice > 3) {
        while (getchar() != '\n');
        printf("Invalid editor choice. Please enter a valid number (1, 2, or 3).\n");
        printf("Choose the editor (1. Nano, 2. Vim, 3. Neovim): ");
    }

    char tempFileName[20];
    sprintf(tempFileName, "temp_note_%d.txt", getpid());

    FILE *tempFile = fopen(tempFileName, "w");
    if (tempFile == NULL) {
        fprintf(stderr, "Unable to create temporary file.\n");
        return;
    }
    fputs(content, tempFile);
    fclose(tempFile);

    char command[100];
    if (editorChoice == 1) {
        sprintf(command, "nano %s", tempFileName);
    } else if (editorChoice == 2) {
        sprintf(command, "vim %s", tempFileName);
    } else if (editorChoice == 3) {
        sprintf(command, "nvim %s", tempFileName);
    } else {
        fprintf(stderr, "Invalid editor choice.\n");
        remove(tempFileName);
        return;
    }

    system(command);

    FILE *file = fopen("notes.txt", "a");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        int id = ftell(file) / sizeof(Note) + 1;

        Note newNote;
        newNote.id = id;
        memset(newNote.content, 0, sizeof(newNote.content));

        tempFile = fopen(tempFileName, "r");
        if (tempFile == NULL) {
            fprintf(stderr, "Unable to open temporary file.\n");
            fclose(file);
            remove(tempFileName);
            return;
        }
        fgets(newNote.content, sizeof(newNote.content), tempFile);
        fclose(tempFile);

        fwrite(&newNote, sizeof(Note), 1, file);
        fclose(file);
        printf("Note added successfully with ID: %d\n", id);

        remove(tempFileName);
    } else {
        fprintf(stderr, "Unable to open the notes file.\n");
        remove(tempFileName);
    }


    char binaryPath[100];
    if (readlink("/proc/self/exe", binaryPath, sizeof(binaryPath)) == -1) {
        fprintf(stderr, "Error retrieving binary path.\n");
        remove(tempFileName);
        return;
    }

   
    char *lastSlash = strrchr(binaryPath, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }

  
    char notesFilePath[150];
    sprintf(notesFilePath, "%s/notes.txt", binaryPath);


    FILE *notesFile = fopen(notesFilePath, "a");
    if (notesFile == NULL) {
        fprintf(stderr, "Unable to open notes file.\n");
        remove(tempFileName);
        return;
    }


    tempFile = fopen(tempFileName, "r");
    if (tempFile == NULL) {
        fprintf(stderr, "Unable to open temporary file.\n");
        fclose(notesFile);
        remove(tempFileName);
        return;
    }
    
    char line[100];
    while (fgets(line, sizeof(line), tempFile)) {
        fputs(line, notesFile);
    }

    fclose(notesFile);
    fclose(tempFile);

    // Remove the temporary file
    remove(tempFileName);


}


void editNote() {
    fflush(stdin);

    FILE *file = fopen("notes.txt", "r+");
    if (file != NULL) {
        Note note;
        int count = 0;
        while (fread(&note, sizeof(Note), 1, file) == 1) {
            printf("%d. Note ID: %d\n", count + 1, note.id);
            count++;
        }
        rewind(file); 

        if (count == 0) {
            printf("No notes found.\n");
            fclose(file);
            return;
        }

        int choice;
        printf("Enter the note number to edit: ");
        while (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid note number. Please enter a number.\n");
            printf("Enter the note number to edit: ");
        }

        if (choice < 1 || choice > count) {
            printf("Invalid note number.\n");
            fclose(file);
            return;
        }

        int selectedID = 0;
        int currentIndex = 0;
        int found = 0;

        while (fread(&note, sizeof(Note), 1, file) == 1) {
            currentIndex++;
            if (currentIndex == choice) {
                selectedID = note.id;
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Choose the editor (1. Nano, 2. Vim, 3. Neovim): ");
            int editorChoice;
            while (scanf("%d", &editorChoice) != 1) {
                while (getchar() != '\n');
                printf("Invalid editor choice. Please enter a number.\n");
                printf("Choose the editor (1. Nano, 2. Vim, 3. Neovim): ");
            }

            char tempFileName[20];
            sprintf(tempFileName, "temp_note_%d.txt", getpid());

            FILE *tempFile = fopen(tempFileName, "w");
            if (tempFile == NULL) {
                fprintf(stderr, "Unable to create temporary file.\n");
                fclose(file);
                return;
            }
            fputs(note.content, tempFile);
            fclose(tempFile);

            char command[100];
            if (editorChoice == 1) {
                sprintf(command, "nano %s", tempFileName);
            } else if (editorChoice == 2) {
                sprintf(command, "vim %s", tempFileName);
            } else if (editorChoice == 3) {
                sprintf(command, "nvim %s", tempFileName);
            } else {
                fprintf(stderr, "Invalid editor choice.\n");
                remove(tempFileName);
                fclose(file);
                return;
            }

            system(command);

            fseek(file, (currentIndex - 1) * sizeof(Note), SEEK_SET); 
            Note updatedNote;
            updatedNote.id = note.id;
            memset(updatedNote.content, 0, sizeof(updatedNote.content));

            tempFile = fopen(tempFileName, "r");
            if (tempFile == NULL) {
                fprintf(stderr, "Unable to open temporary file.\n");
                fclose(file);
                remove(tempFileName);
                return;
            }
            fgets(updatedNote.content, sizeof(updatedNote.content), tempFile);
            fclose(tempFile);

            fwrite(&updatedNote, sizeof(Note), 1, file);
            fclose(file);
            printf("Note updated successfully.\n");

            remove(tempFileName);
        } else {
            printf("Note with ID %d not found.\n", selectedID);
            fclose(file);
        }
    } else {
        fprintf(stderr, "Unable to open the notes file.\n");
    }
}



void deleteNote() {
    fflush(stdin);

    int id;
    printf("Enter the note ID to delete: ");
    while (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("Invalid note ID. Please enter a number.\n");
        printf("Enter the note ID to delete: ");
    }

    // Getting the path to the binary
    char binaryPath[100];
#if defined(__linux__)
    if (readlink("/proc/self/exe", binaryPath, sizeof(binaryPath)) == -1) {
        fprintf(stderr, "Error retrieving binary path.\n");
        return;
    }
#elif defined(__APPLE__)
    uint32_t bufsize = sizeof(binaryPath);
    if (_NSGetExecutablePath(binaryPath, &bufsize) != 0) {
        fprintf(stderr, "Error retrieving binary path.\n");
        return;
    }
#endif


    char *lastSlash = strrchr(binaryPath, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }


    char notesFilePath[150];
    sprintf(notesFilePath, "%s/notes.txt", binaryPath);

    FILE *file = fopen(notesFilePath, "r");
    if (file != NULL) {
        FILE *tempFile = fopen("temp_notes.txt", "w");
        if (tempFile != NULL) {
            Note note;
            int found = 0;
            while (fread(&note, sizeof(Note), 1, file) == 1) {
                if (note.id != id) {
                    fwrite(&note, sizeof(Note), 1, tempFile);
                } else {
                    found = 1;
                }
            }
            fclose(file);
            fclose(tempFile);
            remove(notesFilePath);
            rename("temp_notes.txt", notesFilePath);
            if (found) {
                printf("Note deleted successfully.\n");
            } else {
                printf("Note with ID %d not found.\n", id);
            }
        } else {
            fclose(file);
            fprintf(stderr, "Unable to create the temporary file.\n");
        }
    } else {
        fprintf(stderr, "Unable to open the notes file.\n");
    }
}



void deleteAllNotes() {
    fflush(stdin);

    printf("Are you sure you want to delete all notes? (Y/N): ");
    char confirm;
    while (scanf(" %c", &confirm) != 1 || (tolower(confirm) != 'y' && tolower(confirm) != 'n')) {
        while (getchar() != '\n');
        printf("Invalid choice. Please enter 'Y' or 'N'.\n");
        printf("Are you sure you want to delete all notes? (Y/N): ");
    }

    if (tolower(confirm) == 'y') {
       
        char binaryPath[100];
#if defined(__linux__)
        if (readlink("/proc/self/exe", binaryPath, sizeof(binaryPath)) == -1) {
            fprintf(stderr, "Error retrieving binary path.\n");
            return;
        }
#elif defined(__APPLE__)
        uint32_t bufsize = sizeof(binaryPath);
        if (_NSGetExecutablePath(binaryPath, &bufsize) != 0) {
            fprintf(stderr, "Error retrieving binary path.\n");
            return;
        }
#endif


        char *lastSlash = strrchr(binaryPath, '/');
        if (lastSlash != NULL) {
            *lastSlash = '\0';
        }

    
        char notesFilePath[150];
        sprintf(notesFilePath, "%s/notes.txt", binaryPath);

        FILE *file = fopen(notesFilePath, "w");
        if (file != NULL) {
            fclose(file);
            printf("All notes deleted successfully.\n");
        } else {
            fprintf(stderr, "Unable to open the notes file.\n");
        }
    } else {
        printf("Deletion canceled.\n");
    }
}


void showAllNotes() {

    char binaryPath[100];
#if defined(__linux__)
    if (readlink("/proc/self/exe", binaryPath, sizeof(binaryPath)) == -1) {
        fprintf(stderr, "Error retrieving binary path.\n");
        return;
    }
#elif defined(__APPLE__)
    uint32_t bufsize = sizeof(binaryPath);
    if (_NSGetExecutablePath(binaryPath, &bufsize) != 0) {
        fprintf(stderr, "Error retrieving binary path.\n");
        return;
    }
#endif

   
    char *lastSlash = strrchr(binaryPath, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }

   
    char notesFilePath[150];
    sprintf(notesFilePath, "%s/notes.txt", binaryPath);

    FILE *file = fopen(notesFilePath, "r");
    if (file != NULL) {
        Note note;
        while (fread(&note, sizeof(Note), 1, file) == 1) {
            printf("Note ID: %d\n", note.id);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Unable to open the notes file.\n");
    }
}


void showNote() {
    fflush(stdin);

    int id;
    printf("Enter the note ID to show: ");
    while (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("Invalid note ID. Please enter a number.\n");
        printf("Enter the note ID to show: ");
    }


    char binaryPath[100];
#if defined(__linux__)
    if (readlink("/proc/self/exe", binaryPath, sizeof(binaryPath)) == -1) {
        fprintf(stderr, "Error retrieving binary path.\n");
        return;
    }
#elif defined(__APPLE__)
    uint32_t bufsize = sizeof(binaryPath);
    if (_NSGetExecutablePath(binaryPath, &bufsize) != 0) {
        fprintf(stderr, "Error retrieving binary path.\n");
        return;
    }
#endif

   
    char *lastSlash = strrchr(binaryPath, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }

    char notesFilePath[150];
    sprintf(notesFilePath, "%s/notes.txt", binaryPath);

    FILE *file = fopen(notesFilePath, "r");
    if (file != NULL) {
        Note note;
        int found = 0;
        while (fread(&note, sizeof(Note), 1, file) == 1) {
            if (note.id == id) {
                printf("Note ID: %d\nContent: %s\n", note.id, note.content);
                found = 1;
                break;
            }
        }
        fclose(file);
        if (!found) {
            printf("Note with ID %d not found.\n", id);
        }
    } else {
        fprintf(stderr, "Unable to open the notes file.\n");
    }
}




void showNotesMenu() {
    printf("**** Notes Menu ****\n");
    printf("1. Add a note\n");
    printf("2. Show all notes\n");
    printf("3. Show a note\n");
    printf("4. Edit a note\n");
    printf("5. Delete a note\n");
    printf("6. Delete all notes\n");
    printf("0. Back\n");
    printf("*******************\n");
}

void notesMenu() {
    int option;
    do {
        showNotesMenu();
        printf("Enter an option: ");
        while (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            printf("Invalid option. Please enter a number.\n");
            printf("Enter an option: ");
        }

        switch (option) {
            case 1:
                addNote();
                break;
            case 2:
                showAllNotes();
                break;
            case 3:
                showNote();
                break;
            case 4:
                editNote();
                break;
            case 5:
                deleteNote();
                break;
            case 6:
                deleteAllNotes();
                break;
            case 0:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    } while (option != 0);
}

void mainMenu() {
    int option;
    do {
      
        printf("**** Main Menu ****\n");
        printf("1. Notes\n");
        printf("0. Exit\n");
        printf("******************\n");
        printf("Enter an option: ");
        while (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            printf("Invalid option. Please enter a number.\n");
            printf("Enter an option: ");
        }

        switch (option) {
            case 1:
                notesMenu();
                break;
            case 0:
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    } while (option != 0);
}


void setFilePermissions(const char *filepath, mode_t permissions) {
    if (chmod(filepath, permissions) == 0) {
        printf("File permissions changed successfully.\n");
    } else {
        fprintf(stderr, "Failed to change file permissions.\n");
    }
}


int main() {

        printf("\n\n"
           "▀▀█▀▀ █▀▀ █▀▀█ █▀▄▀█ ░░ ▒█▄░▒█ █▀▀█ ▀▀█▀▀ █▀▀ █▀▀ \n"
           "░▒█░░ █▀▀ █▄▄▀ █░▀░█ ▀▀ ▒█▒█▒█ █░░█ ░░█░░ █▀▀ ▀▀█ \n"
           "░▒█░░ ▀▀▀ ▀░▀▀ ▀░░░▀ ░░ ▒█░░▀█ ▀▀▀▀ ░░▀░░ ▀▀▀ ▀▀▀ \n"
           "\n");
           /*
           printf("\n\n"
           "  ╔═══════════════════════════════════════╗\n"
           "  ║                                       ║\n"
           "  ║   ~ Term Notes ~                      ║\n"
           "  ║   Developed with ❤️ by                 ║\n"
           "  ║   Felipe Alfonso González L.          ║\n"
           "  ║   Computer Science Engineer           ║\n"
           "  ║   Chile                               ║\n"
           "  ║                                       ║\n"
           "  ║   Contact: f.alfonso@res-ear.ch       ║\n"
           "  ║   Licensed under GNU/GPL and MIT      ║\n"
           "  ║   GitHub: github.com/felipealfonsog   ║\n"
           "  ║   LinkedIn:                           ║\n"
           "  ║   linkedin.com/in/felipealfonsog      ║\n"
           "  ║                                       ║\n"
           "  ╚═══════════════════════════════════════╝\n"
           "\n");
*/

    printf("Welcome to the Notes Manager.\n");

    createFiles();
    moveBinaryToDestination();

    const char *notesFilePath = "notes.txt";

   
    chmod(notesFilePath, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);


    char binaryPath[PATH_MAX];
    uint32_t bufferSize = sizeof(binaryPath);
    if (_NSGetExecutablePath(binaryPath, &bufferSize) == 0) {
        printf("Binary path: %s\n", binaryPath);
  
        chmod(binaryPath, S_IRUSR | S_IXUSR);


        mainMenu();
    } else {
        fprintf(stderr, "Error retrieving binary path.\n");
        return 1;
    }

 

    return 0;
}
