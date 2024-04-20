#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define MAX_PATH_LENGTH 256
#define MAX_STRING_LENGTH 1024

void replaceString(char *filename, char *search, char *replace, FILE *log) {
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char temp[MAX_STRING_LENGTH];
    long pos;
    int found = 0; // Flag to indicate if string is found
    while (fgets(temp, MAX_STRING_LENGTH, fp) != NULL) {
        char *ptr = temp;
        while ((ptr = strstr(ptr, search)) != NULL) {
            found = 1;
            pos = ftell(fp) - strlen(ptr);
            fseek(fp, pos, SEEK_SET);
            strncpy(ptr, replace, strlen(replace)); // Overwrite with replacement string
            fputs(temp, fp);
            fflush(fp);

            // Adding timestamp to the log message
            time_t now = time(NULL);
            struct tm *tm_info = localtime(&now);
            char timestamp[MAX_STRING_LENGTH];
            strftime(timestamp, sizeof(timestamp), "[%d-%m-%Y][%H:%M:%S]", tm_info);
            printf("%s Suspicious string replaced at %s\n", timestamp, filename);
            fprintf(log, "%s Suspicious string replaced at %s\n", timestamp, filename);

            ptr += strlen(replace); // Move pointer past replaced string
        }
    }

    fclose(fp);

    if (found)
        printf("Checked and replaced in: %s\n", filename);
}

void checkAndReplace(char *path, FILE *log) {
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {
                char filename[MAX_PATH_LENGTH];
                snprintf(filename, MAX_PATH_LENGTH, "%s/%s", path, entry->d_name);
                replaceString(filename, "m4LwAr3", "[MALWARE]", log);
                replaceString(filename, "5pYw4R3", "[SPYWARE]", log);
                replaceString(filename, "R4nS0mWaR3", "[RANSOMWARE]", log);
            }
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *path = argv[1];

    FILE *log = fopen("virus.log", "a");
    if (log == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    checkAndReplace(path, log);

    fclose(log);

    exit(EXIT_SUCCESS);
}
