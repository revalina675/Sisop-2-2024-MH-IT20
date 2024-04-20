include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <syslog.h>
#include <time.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void rot19_decrypt(char *str) {
    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            char base = isupper(str[i]) ? 'A' : 'a';
            str[i] = (str[i] - base - 19 + 26) % 26 + base;
        }
    }
}

void decrypt_and_rename_files(const char *directory) {
    struct dirent *entry;
    DIR *dir = opendir(directory);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Check if it's a regular file
            char old_name[PATH_MAX];
            char new_name[PATH_MAX];

            // Construct the full path to the file
            snprintf(old_name, sizeof(old_name), "%s/%s", directory, entry->d_name);

            // Decrypt the file name
            strncpy(new_name, entry->d_name, sizeof(new_name));
            rot19_decrypt(new_name);

            // Rename the file
            char rename_path[PATH_MAX];
            snprintf(rename_path, sizeof(rename_path), "%s/%s", directory, new_name);
            if (rename(old_name, rename_path) != 0) {
                perror("rename");
           }
        }
    }

    closedir(dir);
}

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
    // URL untuk file yang akan diunduh
    const char *url = "https://drive.google.com/uc?export=download&id=1rUIZmp10lXLtCIH3LAZJzRPeRks3Crup";
    
    // File untuk menyimpan hasil unduhan
    const char *filename = "library.zip";

    // Fork proses baru
    pid = fork();

    if (pid == -1) {
        // Gagal melakukan fork
        perror("fork");
        return 1;
 } else if (pid == 0) {
        // Ini adalah proses anak
        // Lakukan unduhan dengan wget
        execlp("wget", "wget", "-O", filename, url, NULL);
        // Jika execv gagal, keluar dengan kode error
        perror("execv");
        return 1;
    } else {
        // Ini adalah proses induk
        // Tunggu hingga proses anak selesai
        int status;
        waitpid(pid, &status, 0);

        // Periksa status keluaran proses anak
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // Ekstrak file ZIP
            execlp("unzip", "unzip", filename, NULL);
        } else {
            printf("Gagal mengunduh file\n");
        }
    }

    return 0;
}

