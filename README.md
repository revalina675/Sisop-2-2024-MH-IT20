# PRAKTIKUM MODUL 02 SISTEM OPERASI
## Kelompok IT20
### Anggota Kelompok :
|             Nama              |     NRP    |
|-------------------------------|------------|
| Revalina Fairuzy Azhari Putri | 5027231001 |
| Farida Qurrotu 'Ayuna         | 5027231015 |
| Gallant Damas Hayuaji         | 5027231037 |

## Soal 1

Gavriel adalah seorang cyber security enthusiast. Suatu hari, ia dikontrak oleh sebuah perusahaan ternama untuk membuat sebuah program yang cukup rumit dengan bayaran jutaan rupiah. Karena tergoda dengan nominal bayaran tersebut, Gavriel langsung menerima tawaran tersebut. Setelah mencoba membuat dan mengembangkan program tersebut selama seminggu, laptop yang digunakan Gavriel mengalami overheat dan mati total sehingga harus dilarikan ke tukang servis terdekat. Karena keterbatasan waktu dalam pembuatan program dan tidak ingin mengecewakan perusahaan, Gavriel meminta bantuan kalian untuk membuat program tersebut dengan ketentuan sebagai berikut:

a. Program dapat menerima input path berupa ‘argv’ untuk mengatur folder dimana file akan dieksekusi
      
b. Program tersebut berfungsi untuk mereplace string dengan ketentuan sebagai berikut:

        String m4LwAr3 direplace dengan string [MALWARE]
        String 5pYw4R3 direplace dengan string [SPYWARE]
        String R4nS0mWaR3 direplace dengan string [RANSOMWARE]
        
c. Program harus berjalan secara daemon, dan tidak diperbolehkan menggunakan command system() dalam pembuatan program

d. Program akan secara terus menerus berjalan di background dengan jeda 15 detik

e. Catat setiap penghapusan string yang dilakukan oleh program pada sebuah file bernama virus.log dengan format: [dd-mm-YYYY][HH:MM:SS] Suspicious string at <file_name> successfully replaced!

Contoh penggunaan: ./virus /home/user/virus

Contoh isi file sebelum program dijalankan:

        pU=-JWQ$5$)D-[??%AVh]$cB6bm4LwAr3jEQC2p3R{HV]=-AUaxj:Qe+h
        !aNX,i:!z3W=2;.tHc3&S+}6F)CFf%tfZLP1*w5m1PAzZJUux(
        Pd&f8$F5=E?@#[6jd{TJKj]5pYw4R3{KK1?hz384$ge@iba5GAj$gqB41
        #C&&a}M9C#f64Eb.?%c)dGbCvJXtU[?SE4h]BY4e1PR4nS0mWaR3{]S/{w?*

Contoh isi file setelah setelah program dijalankan:

        pU=-JWQ$5$)D-[??%AVh]$cB6b[MALWARE]jEQC2p3R{HV]=-AUaxj:Qe+h
        !aNX,i:!z3W=2;.tHc3&S+}6F)CFf%tfZLP1*w5m1PAzZJUux(
        Pd&f8$F5=E?@#[6jd{TJKj][SPYWARE]{KK1?hz384$ge@iba5GAj$gqB41
        #C&&a}M9C#f64Eb.?%c)dGbCvJXtU[?SE4h]BY4e1P[RANSOMWARE]{]S/{w?*

## Jawab

### soal 1a

Pada soal ini diminta agar dapat menerima input path berupa ‘argv’ untuk mengatur folder dimana file akan dieksekusi

        int main(int argc, char *argv[]) {
                if (argc != 2) {
                printf("Usage: %s <path>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

`if (argc != 2)` digunakan untuk memberikan keterangan jika format untuk menjalankan program berjumlah dua argumen yaitu argumen pertama (argv[0]) adalah nama program dan  argumen kedua (argv[1]) adalah path direktori yang akan dieksekusi

`printf("Usage: %s <path>\n", argv[0]);` digunakan untuk format argumen yang digunakan untuk menjalankan program

### soal 1b

pada soal ini diminta agar program berfungsi untuk mereplace string sesuai permintaan 

                replaceString(filename, "m4LwAr3", "[MALWARE]", log);
                replaceString(filename, "5pYw4R3", "[SPYWARE]", log);
                replaceString(filename, "R4nS0mWaR3", "[RANSOMWARE]", log);
            
`replaceString(...` digunakan untuk memanggil fungsi replaceString

`...filename,...` digunakan untuk nama file yang ingin diganti stringnya

`..."m4LwAr3",...` digunakan untuk string yang ingin diganti

`..."[MALWARE]",...` digunakan untuk string pengganti (menggantikan string yang ingin diganti)

`...log);` digunakan untuk mencatat semua perubahan yang terjadi selama proses (penggantian string) berjalan

### soal 1c 

pada soal ini diminta agar berjalan secara daemon, dan tidak diperbolehkan menggunakan command system() dalam pembuatan program

        // Forking to daemon
        pid_t pid = fork();
        if (pid < 0) {
                perror("Error forking");
                exit(EXIT_FAILURE);
        }
        if (pid > 0) {
                // Exiting from parent process
                exit(EXIT_SUCCESS);
        }
        
        // Changing working directory
        if (chdir("/") < 0) {
                perror("Error changing directory");
                exit(EXIT_FAILURE);
        }
        
        // Closing standard file descriptors
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        
`pid_t pid = fork();` digunakan untuk membuat proses baru (child process)

`if (pid < 0) {...` digunakan untuk kondisi ketika fork gagal maka akan mencetak pesan yang ada pada fungsi tersebut

`if (pid > 0) {...` digunakan untuk kondisi ketika fork berhasil maka akan mencetak pesan yang ada pada fungsi tersebut

`if (chdir("/") < 0) {...` digunakan untuk kondisi ketika daemon  gagal memastikan bahwa tidak tidak ada ketergantungan pada direktori spesifik saat berjalan sekaligus mencegah terjadinya masalah ketika direktori asal mungkin dihapus atau diganti

`close(STDIN_FILENO);` digunakan untuk menutup standar file deskriptor agar daemon tidak menerima input atau memunculkan output ke terminal

### soal 1d

pada soal ini diminta agar program dapat berjalan terus menerus di background dengan jeda 15 detik

        // Daemon main loop
        while (1) {
            checkAndReplace(path, log);
            fflush(log);
            sleep(15); // Delay for 15 seconds
        }

`while (1) {...` digunakan untuk perulangan tanpa henti

`checkAndReplace(path, log);` digunakan untuk memanggil fungsi checkAndReplace setiap perulangan untuk mengecek apakah ada pola string (seperti string malware) dalam direktori, jika iya maka akan menjalankan program sesuai ketentuan

`fflush(log);` digunakan untuk memastikan bahwa data ditulis ke log secara benar

`sleep(15);}` digunakan untuk menidurkan program setelah melakukan iterasi tiap 15 detik

### soal 1e

pada soal ini diminta agar setiap penggantian string yang dilakukan oleh program akan disimpan pada file virus.log dengan format: [dd-mm-YYYY][HH:MM:SS] Suspicious string at <file_name> successfully replaced!

        // Adding timestamp to the log message
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char timestamp[MAX_STRING_LENGTH];
        strftime(timestamp, sizeof(timestamp), "[%d-%m-%Y][%H:%M:%S]", tm_info);
        printf("%s Suspicious string replaced at %s\n", timestamp, filename);
        fprintf(log, "%s Suspicious string at %s successfully replaced!\n", timestamp, filename);

`struct tm *tm_info = localtime(&now);` digunakan untuk mengonversi nilai waktu ke dalam struktur tm yang menyimpan informasi waktu terperinci, seperti tahun, bulan, tanggal, jam, menit, dan detik yang kemudian disimpan dalam variabel tm_info

`char timestamp[MAX_STRING_LENGTH];` digunakan untuk menyimpan string format waktu yang akan dicetak

`strftime(timestamp, sizeof(timestamp), "[%d-%m-%Y][%H:%M:%S]", tm_info);` digunakan untuk mengambil informasi waktu dari tm_info dan mengonversinya menjadi string dengan format yang ditentukan, lalu disimpan ke dalam array timestamp

`printf("%s Suspicious string replaced at %s\n", timestamp, filename);` digunakan untuk mencetak informasi waktu dan nama file di mana string yang ingin diganti telah berhasil diganti

`fprintf(log, "%s Suspicious string at %s successfully replaced!\n", timestamp, filename);` digunakan untuk mencetak informasi yang tersimpan dalam file.log berisikan format sesuai yang diminta dalam soal

## Revisi

pada code di github belum terdapat fungsi untuk menjalankan daemon nya di background setiap 15 detik, sehingga saya memperbaiki kode program ini dengan menambahkan code ini setelah fungsi yang digunakan untuk membuka virus.log

            // Forking to daemon
            pid_t pid = fork();
            if (pid < 0) {
                perror("Error forking");
                exit(EXIT_FAILURE);
            }
            if (pid > 0) {
                // Exiting from parent process
                exit(EXIT_SUCCESS);
            }
        
            // Changing working directory
            if (chdir("/") < 0) {
                perror("Error changing directory");
                exit(EXIT_FAILURE);
            }
        
            // Closing standard file descriptors
            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);
        
            // Daemon main loop
            while (1) {
                checkAndReplace(path, log);
                fflush(log);
                sleep(15); // Delay for 15 seconds
            }
        
            fclose(log);
        
            exit(EXIT_SUCCESS);
            }

code diatas bertujuan agar jika program dijalankan maka daemon akan terus berjalan tiap 15 detik di backgroun hal ini dapat dicek dengan membuat stringfile.txt kedua dan string pada file tersebut juga tetap akan ikut diganti seperti tampilan dibawah ini

gambar stringfile1.txt

## Hasil output

gambar

gambar

gambar

`gcc virus.c -o virus` digunakan untuk mengcompiler file virus.c dan menyimpannya ke dalam file virus

`./virus /home/farida/virus` digunakan untuk menjalankan file virus dan memeriksa string aneh yang terdapat di file pada direktori yang ditunjuk (virus)

`cat virus.log` digunakan untuk menampilkan format jika pengubahan string berhasil dijalankan dan disimpan dalam virus.log

`cat string1.txt` digunakan untuk menampilkan isi file yang telah diubah stringnya

`cat string2.txt` digunakan untuk menunjukkan bahwa program daemon terus berjalan tiap 15 detik

## SOAL 2

Paul adalah seorang mahasiswa semester 4 yang diterima magang di perusahaan XYZ. Pada hari pertama magang, ia diberi tugas oleh atasannya untuk membuat program manajemen file sederhana. Karena kurang terbiasa dengan bahasa C dan environment Linux, ia meminta bantuan kalian untuk mengembangkan program tersebut.

a. Atasannya meminta agar program tersebut dapat berjalan secara daemon dan dapat mengunduh serta melakukan unzip terhadap file berikut. Atasannya juga meminta program ini dibuat tanpa menggunakan command system()

b. Setelah ditelusuri, ternyata hanya 6 file teratas yang nama filenya tidak dienkripsi. Oleh karena itu, bantulah Paul untuk melakukan dekripsi terhadap nama file ke-7 hingga terakhir menggunakan algoritma ROT19

c. Setelah dekripsi selesai, akan terlihat bahwa setiap file memuat salah satu dari kode berikut: r3N4mE, d3Let3, dan m0V3. Untuk setiap file dengan nama yang memuat kode d3Let3, hapus file tersebut. Sementara itu, untuk setiap file dengan nama yang memuat kode r3N4mE, lakukan hal berikut:

    i. Jika ekstensi file adalah “.ts”, rename filenya menjadi “helper.ts”
    ii. Jika ekstensi file adalah “.py”, rename filenya menjadi “calculator.py”
    iii. Jika ekstensi file adalah “.go”, rename filenya menjadi “server.go”
    iv. Jika file tidak memuat salah satu dari ekstensi diatas, rename filenya menjadi “renamed.file”

d. Atasan Paul juga meminta agar program ini dapat membackup dan merestore file. Oleh karena itu, bantulah Paul untuk membuat program ini menjadi 3 mode, yaitu:

    i .default: program berjalan seperti biasa untuk me-rename dan menghapus file. Mode ini dieksekusi ketika program dijalankan tanpa argumen tambahan, yaitu dengan command ./management saja
    ii. backup: program memindahkan file dengan kode m0V3 ke sebuah folder bernama “backup”
    iii. restore: program mengembalikan file dengan kode m0V3 ke folder sebelum file tersebut dipindahkan
    iv. Contoh penggunaan: ./management -m backup

    
e. Terkadang, Paul perlu mengganti mode dari program ini tanpa menghentikannya terlebih dahulu. Oleh karena itu, bantulan Paul untuk mengintegrasikan kemampuan untuk mengganti mode ini dengan mengirim sinyal ke daemon, dengan ketentuan:

    i. SIGRTMIN untuk mode default
    ii. SIGUSR1 untuk mode backup
    iii. SIGUSR2 untuk mode restore
    iv. Contoh penggunaan: kill -SIGUSR2 <pid_program>

f. Program yang telah dibuat ini tidak mungkin akan dijalankan secara terus-menerus karena akan membebani sistem. Maka dari itu, bantulah Paul untuk membuat program ini dapat dimatikan dengan aman dan efisien

g. Terakhir, program ini harus berjalan setiap detik dan mampu mencatat setiap peristiwa yang terjadi ke dalam file .log yang bernama “history.log” dengan ketentuan:

    i .Format: [nama_user][HH:MM:SS] - <nama_file> - <action>
    ii. nama_user adalah username yang melakukan action terhadap file
    iii. Format action untuk setiap kode:
      1. kode r3N4mE: Successfully renamed.
      2. kode d3Let3: Successfully deleted.
      3. mode backup: Successfully moved to backup.
      4. mode restore: Successfully restored from backup.
    iv. Contoh pesan log:
      1. [paul][00:00:00] - r3N4mE.ts - Successfully renamed.
      2. [paul][00:00:00] - m0V3.xk1 - Successfully restored from backup.

Berikut adalah struktur folder untuk pengerjaan nomor 2:
    soal_2/
    
    ├── history.log
    ├── management.c
    └── library/
        └── backup/

## Jawab
Dalam pengerjaan soal ini, saya merealisasikan code pada konfigurasi 
> management.c

ini adalah tampilan code saya secara keseluruhan :

```
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
```

a. Atasannya meminta agar program tersebut dapat berjalan secara daemon dan dapat mengunduh serta melakukan unzip terhadap file berikut. Atasannya juga meminta program ini dibuat tanpa menggunakan command system()

Untuk command download file, ditunjukkan dalam section ini :

```
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
```

pada command tersebut saya menggunakan perintah `wget` yang biasanya digunakan untuk mendownload url link.

Untuk mengunzip file saya menggunakan command pada section :
```
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
```

Untuk konfigurasi code kurang lebih sama seperti pada command mendownload file. Namun, kita hanya mengubah pada beberapa section yang dapat mempengaruhi kondisi pula.

dan untuk menjalankan program secara daemon, ada pada section code :

```
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
```

b. Setelah ditelusuri, ternyata hanya 6 file teratas yang nama filenya tidak dienkripsi. Oleh karena itu, bantulah Paul untuk melakukan dekripsi terhadap nama file ke-7 hingga terakhir menggunakan algoritma ROT19

ROT19 adalah suatu algoritma dimana dia akan melooping huruf yang ada pada nama file sebanyak 19x untuk melakukan decrypt file

```
void rot19_decrypt(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = (str[i] - 'a' - 19 + 26) % 26 + 'a';
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = (str[i] - 'A' - 19 + 26) % 26 + 'A';
        }
    }
}
```

Berikut adalah implementasi code saya untuk melakukan perintah decrypt dengan algoritma ROT19 sesuai yang diminta pada soal :

```
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
```

setelah meng-save code tersebut, saya kembali pada terminal linux dan mengaktifkan code dengan command 

`gcc -o management management.c`

dan mulai menjalankan program tersebut dengan command 

`./management`

Untuk mengecek, apakah program sudah berjalan secara daemon, saya menggunakan command

`ps aux | grep management`

Pada program tertera seperti ini, yang menandakan bahwa program sudah berjalan secara daemon.
![WhatsApp Image 2024-04-27 at 12 37 03 AM](https://github.com/revalina675/Sisop-2-2024-MH-IT20/assets/150936800/abdfa829-b14f-48c2-9beb-06c3c414ede4)

Lalu, saya masuk ke dalam file manager untuk memeriksa apakah url link yang ditautkan pada soal sudah terinstall dan terunzip. Hasilnya, url tersebut sudah terinstall dan terunzip sesuai yang diinginkan soal

![WhatsApp Image 2024-04-27 at 12 37 37 AM](https://github.com/revalina675/Sisop-2-2024-MH-IT20/assets/150936800/a07d622c-7c98-4ece-aac4-94c51140f9e2)

Namun, saat saya ingin memeriksa apakah file sudah terdecrypt dengan algoritma ROT19, ternyata program masih belum bisa melakukannya. Terbukti pada nama file-file yang ada disini

![WhatsApp Image 2024-04-27 at 12 37 49 AM](https://github.com/revalina675/Sisop-2-2024-MH-IT20/assets/150936800/6993c3c1-dbfb-433c-90d4-a9d5a0ae553f)

## SOAL 3

Pak Heze adalah seorang admin yang baik. Beliau ingin membuat sebuah program admin yang dapat memantau para pengguna sistemnya. Bantulah Pak Heze untuk membuat program  tersebut!

a. Namai program tersebut dengan nama admin.cvoid unzip_file() 

b. Program tersebut memiliki fitur menampilkan seluruh proses yang dilakukan oleh seorang user dengan menggunakan command:
./admin <user>

c. Program dapat memantau proses apa saja yang dilakukan oleh user. Fitur ini membuat program berjalan secara daemon dan berjalan terus menerus. Untuk menjalankan fitur ini menggunakan command: 
./admin -m <user>
Dan untuk mematikan fitur tersebut menggunakan: 
./admin -s <user>
Program akan mencatat seluruh proses yang dijalankan oleh user di file <user>.log dengan format:
[dd:mm:yyyy]-[hh:mm:ss]-pid_process-nama_process_GAGAL/JALAN

d. Program dapat menggagalkan proses yang dijalankan user setiap detik secara terus menerus dengan menjalankan: 
./admin -c user
sehingga user tidak bisa menjalankan proses yang dia inginkan dengan baik. Fitur ini dapat dimatikan dengan command:
./admin -a user

e. Ketika proses yang dijalankan user digagalkan, program juga akan melog dan menset log tersebut sebagai GAGAL. Dan jika di log menggunakan fitur poin c, log akan ditulis dengan JALAN

## Jawab

### soal 3a

pada soal ini diminta untuk menamai program dengan nama admin.c

![Screenshot from 2024-04-27 02-37-50](https://github.com/revalina675/Sisop-2-2024-MH-IT20/assets/150933246/2f741481-b1fd-4a56-add8-25986f6ea881)

### soal 3b

pada soal ini diminta agar program memiliki fitur untuk menampilkan seluruh proses yang dilakukan oleh seorang user dengan menggunakan command ./admin <user>

      //fungsi kegiatan yang dilakukan oleh user
      void aktivitas_user(const char *username) 
          {
          // Mendefinisikan nama file log
          char log_filename[NAMA_USER + sizeof(LOG_FILE)];
          sprintf(log_filename, "%s%s", username, LOG_FILE);
          
          // Membuka file log
          FILE *log_file = fopen(log_filename, "a");
          if (log_file == NULL)
          {
              perror("Gagal membuka file log");
              exit(EXIT_FAILURE);
          }
      
          while (1) {
              // Mendapatkan waktu saat ini
              time_t raw_time;
              struct tm *time_info;
              time(&raw_time);
              time_info = localtime(&raw_time);
      
              // Memantau aktivitas pengguna
              pid_t pid = getpid();
              char process_name[256];
              sprintf(process_name, "/proc/%d/cmdline", pid);
              FILE *proc_file = fopen(process_name, "r");

### soal 3c

pada soal ini diminta untuk menjalankan fitur program ini menggunakan command ./admin -m <user> dan untuk mematikannya menggunakan ./admin -s <user> sekaligus program akan mencatat seluruh proses yang dijalankan oleh user dalam file.log

fungsi untuk menjalankan program:

    //fungsi kegiatan yang dilakukan oleh user
    void aktivitas_user(const char *username) 
    {
    // Mendefinisikan nama file log
    char log_filename[NAMA_USER + sizeof(LOG_FILE)];
    sprintf(log_filename, "%s%s", username, LOG_FILE);
    
    // Membuka file log
    FILE *log_file = fopen(log_filename, "a");
    if (log_file == NULL)
    {
        perror("Gagal membuka file log");
        exit(EXIT_FAILURE);
    }

fungsi untuk memnghentikan program:
      
      void stop_monitoring(const char *username)
      {
          // Menghentikan pemantauan untuk seorang pengguna
          char log_filename[NAMA_USER + sizeof(LOG_FILE)];
          sprintf(log_filename, "%s%s", username, LOG_FILE);
          remove(log_filename);
      }
      
` remove(log_filename);` digunakan untuk menghentikan segala proses dengan menghaouskan semua data pada log_filename

### soal 3d

pada soal ini diminta agar terdapat fitur menggagalkan proses yang dijalankan user setiap detik secara terus menerus dengan menjalankan ./admin -c user dan fitur ini dapat dimatikan dengan menjalankan ./admin -a user

fungsi untuk memblock aktivitas user:

      void block_user_activity(const char *username)
      {
          // Memblokir aktivitas pengguna
          // Implementasi pemblokiran aktivitas pengguna ada di sini
          
    // Membuka file log
    char log_filename[NAMA_USER + sizeof(LOG_FILE)];
    sprintf(log_filename, "%s%s", username, LOG_FILE);
    FILE *log_file = fopen(log_filename, "a");
    if (log_file == NULL)
    {
        perror("Gagal membuka file log");
        exit(EXIT_FAILURE);
    }
      ...


fungsi untuk membuka block aktivitas user:

      void unblock_user_activity(const char *username)
      {
          // Membuka blokir aktivitas pengguna
          // Implementasi membuka blokir aktivitas pengguna ada di sini

    // Membuka file log
    char log_filename[NAMA_USER + sizeof(LOG_FILE)];
    sprintf(log_filename, "%s%s", username, LOG_FILE);
    FILE *log_file = fopen(log_filename, "a");
    if (log_file == NULL)
    {
        perror("Gagal membuka file log");
        exit(EXIT_FAILURE);
    }



### soal 3e

pada soal bagian ini diminta agar ketika proses yang digagalkan tercetak GAGAL dan jika di log dengan fitur -c akan tercetak JALAN

    if (proc_file != NULL)
    {
        fgets(process_name, sizeof(process_name), proc_file);
        fclose(proc_file);
        fprintf(log_file, "[%02d:%02d:%04d]-[%02d:%02d:%02d]-%d-%s_GAGAL\n", 
            time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec, pid, process_name);
    }

` fgets(process_name, sizeof(process_name), proc_file);` digunakan untuk membaca satu baris file yang ditunjuk dan kemudian disimpan dalam array process name

`time_info->tm_mday,...` digunakan untuk mencatat waktu ketika menjalankan program
    
## HASIL OUTPUT

![Screenshot from 2024-04-27 02-34-57](https://github.com/revalina675/Sisop-2-2024-MH-IT20/assets/150933246/40569c52-5253-4469-ac56-d8aa9b36b5f7)

![Screenshot from 2024-04-27 02-35-17](https://github.com/revalina675/Sisop-2-2024-MH-IT20/assets/150933246/3c60e147-fe60-4a64-bbe5-33bbbdb8ef06)

`gcc admin.c -o admin` digunakan untuk mengcompile file admin.c 

`./admin -m/-s/-c/-a farida` digunakan untuk menjalankan program sesuai dengan fitur yang ingin dijalankan

`cat farida.log` digunakan untuk mencatat kegiatan yang dilakukan oleh user (sesuai dengan format di soal)


## SOAL 4

Salomo memiliki passion yang sangat dalam di bidang sistem operasi. Saat ini, dia ingin mengotomasi kegiatan-kegiatan yang ia lakukan agar dapat bekerja secara efisien. Bantulah Salomo untuk membuat program yang dapat mengotomasi kegiatan dia!
(NB: Soal di uji coba dan berhasil di sistem yang menggunakan MacOS dan linux yang menggunakan dual boot dan VM. Untuk teman-teman yang menggunakan WSL bisa mengerjakan soal yang lain ya)

a. Salomo ingin dapat membuka berbagai macam aplikasi dengan banyak jendela aplikasi dalam satu command. Namai file program tersebut setup.c

b. Program dapat membuka berbagai macam aplikasi dan banyak jendela aplikasi sekaligus (bisa membuka 1 atau lebih aplikasi dengan 1 atau lebih window (kecuali aplikasi yang tidak bisa dibuka dengan banyak window seperti discord)) dengan menjalankan: 
./setup -o <app1> <num1> <app2> <num2>.....<appN> <numN>
Contoh penggunaannya adalah sebagai berikut: 
./setup -o firefox 2 wireshark 2 Program akan membuka 2 jendela aplikasi firefox dan 2 jendela aplikasi wireshark.

c. Program juga dapat membuka aplikasi dengan menggunakan file konfigurasi dengan menggunakan 
./setup -f file.conf 
Format file konfigurasi dibebaskan, namun pastikan dapat menjalankan fitur dari poin 2.
Contoh isi file.conf:
Firefox 2
Wireshark 3
Ketika menjalankan command contoh, program akan membuka 2 jendela aplikasi firefox dan 3 jendela aplikasi wireshark.

d. Program dapat mematikan semua aplikasi yg dijalankan oleh program tersebut dengan: 
./setup -k

e. Program juga dapat mematikan aplikasi yang dijalankan sesuai dengan file konfigurasi. 
Contohnya: 
./setup -k file.conf 
Command ini hanya mematikan aplikasi yang dijalankan dengan 
./setup -f file.conf

## Jawab
