#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
     {
      pid_t child_pid;              //variabel untuk save child PID
      int status;                   //variabel untuk save status child

     if (argc < 2)                  //cek kondisi jumlah argumen
     {
       printf("Usage: %s -o <app1> <num1> <app2> <num2> ... <appN> <numN>\n", argv[0]);
       return 1;
     }

     if (strcmp(argv[1], "-o") != 0) {      //cek kondisi apakah argumen pertama merupakan "-o"
       printf("Perintah tidak valid. Gunakan -o untuk menentukan aplikasi dan jumlah window.\n");
       return 1;                            //print tanda kesalahan jika tidak sesuai
     }

     for (int i = 2; i < argc; i += 2) {    //dilakukan looping untuk aplikasi dan jumlah window
       int num_windows = atoi(argv[i + 1]);  //convert jumlah window menjadi integer
       for (int j = 0; j < num_windows; j++) {  //looping sebanyak window yang diinput
        child_pid = fork();                     //buat fork untuk child process
        if (child_pid == 0) {                   //cek kondisi jika berada pada child process
          if (strcmp(argv[i], "libreoffice") == 0) {   //pastikan aplikasi adalah libreoffice
            execlp("libreoffice", "libreoffice", "--calc", NULL);  //run libreoffice calc
          } else if (strcmp(argv[i], "firefox") == 0) {            //pastikan aplikasi merupakan firefox
            execlp("firefox", "firefox", NULL);                    //run firefox
          } else {
            printf("Masukkan aplikasi yang valid: %s\n", argv[i]);  //muncul kesalahan jika aplikasi tidak valid
            exit(1);                                                //exit child process
          }
          perror("execlp"); //jika ada error eksekusi, maka akan muncul pesan
          exit(1);          //exit process karena kesalahan
        } else if (child_pid < 0) {
           perror("fork");  //print eror karena gagal menjalankan fork
        }
      }
    }
    while (wait(&status) > 0);   //menunggu semua child process selesai
    return 0:
}
