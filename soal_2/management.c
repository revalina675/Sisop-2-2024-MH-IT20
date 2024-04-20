#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>

void download_file();
void unzip_file();
void rot19_decrypt();
void decrypt_file();

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini
    download_file();
    unzip_file();
    decrypt_file();

    sleep(30);
  }
}

void download_file() 
{
    pid_t child_id = fork();

    char download_path[1000] = "/home/revalina/m2s2";
    if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
        char *cmd = "/bin/wget";
        char *argv[7] = { "wget", "--content-disposition", "--no-check-certificate", "https://drive.google.com/uc?export=download&id=1rUIZmp10lXLtCIH3LAZJzRPeRks3Crup", "-P", download_path, NULL };
        execv(cmd, argv);
  } else {
    // this is parent

        int status;
        wait(&status);
  }
}

void unzip_file() 
{
    pid_t child_id = fork();

    char download_path[1000] = "/home/revalina/m2s2/library.zip";
    if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
        char *cmd = "/bin/unzip";
        char *argv[5] = { "unzip", "/home/revalina/m2s2/library.zip", "-d", "/home/revalina/m2s2", NULL };
        execv(cmd, argv);
  } else {
    // this is parent

        int status;
        wait(&status);
  }
}

void rot19_decrypt(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = (str[i] - 'a' - 19 + 26) % 26 + 'a';
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = (str[i] - 'A' - 19 + 26) % 26 + 'A';
        }
    }
}

void decrypt_file(){
    pid_t pid = fork();

    if (pid < 0) exit(EXIT_FAILURE);

    else if (pid == 0)
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir("/home/revalina/m2s2/library")) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                // Cek apakah file adalah file teratas 6 dan bukan direktori
                if (ent->d_type == DT_REG && strlen(ent->d_name) > 6) {
                    char new_name[256];
                    strcpy(new_name, ent->d_name);
                    rot19_decrypt(new_name);
                    printf("Rename %s to %s\n", ent->d_name, new_name);
                    // Ganti nama file di sini
                    rename(ent->d_name, new_name);
                }
            }
            closedir(dir);
        } else {
            perror("Could not open directory");
            exit(EXIT_FAILURE);
        }
    }

    else
    {
        int status;
        wait(&status);
    }
}
