#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#define NAMA_USER 50
#define LOG_FILE ".log"

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
        if (proc_file != NULL)
        {
            fgets(process_name, sizeof(process_name), proc_file);
            fclose(proc_file);
            fprintf(log_file, "[%02d:%02d:%04d]-[%02d:%02d:%02d]-%d-%s_JALAN\n", 
                time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
                time_info->tm_hour, time_info->tm_min, time_info->tm_sec, pid, process_name);
        } else
        {
            fprintf(log_file, "[%02d:%02d:%04d]-[%02d:%02d:%02d]-%d-UNKNOWN_JALAN\n", 
                time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
                time_info->tm_hour, time_info->tm_min, time_info->tm_sec, pid);
        }
        fflush(log_file);
        sleep(1);
    }
    
    fclose(log_file);
}

void stop_monitoring(const char *username)
{
    // Menghentikan pemantauan untuk seorang pengguna
    char log_filename[NAMA_USER + sizeof(LOG_FILE)];
    sprintf(log_filename, "%s%s", username, LOG_FILE);
    remove(log_filename);
}

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

    // Mendapatkan waktu saat ini
    time_t raw_time;
    struct tm *time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);

    // Menambahkan pesan yang menandakan pemblokiran aktivitas pengguna
    pid_t pid = getpid();
    char process_name[256];
    sprintf(process_name, "/proc/%d/cmdline", pid);
    FILE *proc_file = fopen(process_name, "r");
    if (proc_file != NULL)
    {
        fgets(process_name, sizeof(process_name), proc_file);
        fclose(proc_file);
        fprintf(log_file, "[%02d:%02d:%04d]-[%02d:%02d:%02d]-%d-%s_GAGAL\n", 
            time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec, pid, process_name);
    } else
    {
        fprintf(log_file, "[%02d:%02d:%04d]-[%02d:%02d:%02d]-%d-UNKNOWN_GAGAL\n", 
            time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec, pid);
    }
    fflush(log_file);

    fclose(log_file);
}

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

    // Mendapatkan waktu saat ini
    time_t raw_time;
    struct tm *time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);

    // Menambahkan pesan yang menandakan membuka blokir aktivitas pengguna
    pid_t pid = getpid();
    char process_name[256];
    sprintf(process_name, "/proc/%d/cmdline", pid);
    FILE *proc_file = fopen(process_name, "r");
    if (proc_file != NULL)
    {
        fgets(process_name, sizeof(process_name), proc_file);
        fclose(proc_file);
        fprintf(log_file, "[%02d:%02d:%04d]-[%02d:%02d:%02d]-%d-%s_JALAN\n", 
            time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec, pid, process_name);
    } else
    {
        fprintf(log_file, "[%02d:%02d:%04d]-[%02d:%02d:%02d]-%d-UNKNOWN_JALAN\n", 
            time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec, pid);
    }
    fflush(log_file);

    fclose(log_file);
}

void handle_signal(int sig)
{
    // Menangani sinyal terminasi
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if (argc != 3) 
    {
        printf("Penggunaan: %s -m/-s/-c/-a <user>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *option = argv[1];
    char *username = argv[2];

    signal(SIGTERM, handle_signal);

    if (strcmp(option, "-m") == 0)
    {
        // Memulai pemantauan aktivitas pengguna
        pid_t pid = fork();
        if (pid == 0)
        {
            // Proses anak
            setsid(); // Membuat sesi baru
            aktivitas_user(username);
        }
    } 
    else if (strcmp(option, "-s") == 0) 
    {
        stop_monitoring(username);  // Menghentikan pemantauan aktivitas pengguna
    } 
    else if (strcmp(option, "-c") == 0) 
    {
        block_user_activity(username); // Mem blokir aktivitas pengguna
    } 
    else if (strcmp(option, "-a") == 0) 
    {
        unblock_user_activity(username); // Membuka blokir aktivitas pengguna
    } 
    else
    {
        printf("Opsi tidak valid\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
