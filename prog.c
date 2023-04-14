#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 1024
#define UNIT_TIME 10 // in seconds

void record_wasted_blocks(int wasted_blocks);
void rename_file();
void move_file();

int main() {
    char filename[50];
    FILE *fp;
    char ch;
    int choice;
    int total_wasted_blocks = 0;
    int wasted_blocks = 0;
    int time_elapsed = 0;

    printf("File System Manager\n");
    printf("1. Create a new file\n");
    printf("2. Write to a file\n");
    printf("3. Read from a file\n");
    printf("4. Rename a file\n");
    printf("5. Move a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");

    while(1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nEnter filename to create: ");
                scanf("%s", filename);
                fp = fopen(filename, "w");
                if(fp == NULL) {
                    printf("\nError creating file");
                    exit(1);
                }
                printf("\nFile created successfully!");
                fclose(fp);
                wasted_blocks++;
                break;
            case 2:
                printf("\nEnter filename to write to: ");
                scanf("%s", filename);
                fp = fopen(filename, "a");
                if(fp == NULL) {
                    printf("\nError opening file");
                    exit(1);
                }
                printf("\nEnter text to write: ");
                while((ch=getchar()) != '\n' && ch != EOF);
                fgets(filename, MAX_FILE_SIZE, stdin);
                fputs(filename, fp);
                fclose(fp);
                printf("\nText written successfully!");
                wasted_blocks++;
                break;
            case 3:
                printf("\nEnter filename to read from: ");
                scanf("%s", filename);
                fp = fopen(filename, "r");
                if(fp == NULL) {
                    printf("\nError opening file");
                    exit(1);
                }
                printf("\nFile contents:\n");
                while((ch = fgetc(fp)) != EOF) {
                    putchar(ch);
                }
                fclose(fp);
                break;
            case 4:
                rename_file();
                break;
            case 5:
                move_file();
                break;
            case 6:
                printf("\nEnter filename to delete: ");
                scanf("%s", filename);
                if(remove(filename) == 0) {
                    printf("\nFile deleted successfully!");
                } else {
                    printf("\nError deleting file");
                }
                wasted_blocks++;
                break;
            case 7:
                printf("\nExiting the program...");
                exit(0);
            default:
                printf("\nInvalid choice");
        }

        time_elapsed++;
        if(time_elapsed == UNIT_TIME) {
            record_wasted_blocks(wasted_blocks);
            total_wasted_blocks += wasted_blocks;
            wasted_blocks = 0;
            time_elapsed = 0;
        }
    }

    return 0;
}

void record_wasted_blocks(int wasted_blocks) {
    FILE *fp = fopen("wasted_blocks.log", "a");
    if(fp == NULL) {
        printf("\nError opening file");
        exit(1);
    }
    fprintf(fp, "Wasted blocks: %d\n", wasted_blocks);
    fclose(fp);
}


void rename_file() {
    char old_filename[50];
    char new_filename[50];
    printf("\nEnter filename to rename: ");
    scanf("%s", old_filename);
    printf("\nEnter new filename: ");
    scanf("%s", new_filename);
    if(rename(old_filename, new_filename) == 0) {
        printf("\nFile renamed successfully!");
    } else {
        printf("\nError renaming file");
    }
}
void move_file() {
    char filename[50];
    char source_path[100];
    char dest_path[100];
    printf("\nEnter filename to move: ");
    scanf("%s", filename);
    printf("\nEnter source directory path: ");
    scanf("%s", source_path);
    printf("\nEnter destination directory path: ");
    scanf("%s", dest_path);
    if(rename(strcat(source_path, filename), strcat(dest_path, filename)) == 0) {
        printf("\nFile moved successfully!");
    } else {
        printf("\nError moving file");
    }
}