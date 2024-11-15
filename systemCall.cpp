#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <cstdlib>

using namespace std;

void process_related() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) {
        cout << "Child Process ID: " << getpid() << endl;
        cout << "Exiting child process...\n";
        exit(0);
    } else {
        wait(NULL); // Parent waits for child to finish
        cout << "Child process finished. Parent Process ID: " << getpid() << endl;
    }
}

void file_related() {
    int fd = open("example.txt", O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        perror("File open failed");
        return;
    }

    const char *data = "My name is Pratik Mandalkar....\n";
    if (write(fd, data, strlen(data)) < 0) {
        perror("File write failed");
        close(fd);
        return;
    }
    lseek(fd, 0, SEEK_SET); // Move file pointer to the beginning

    char buffer[1024];

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead < 0) {
        perror("File read failed");
        close(fd);
        return;
    }

    buffer[bytesRead] = '\0'; // Null-terminate the string
    cout << "File content:\n" << buffer << endl;

    close(fd);

    // Link and unlink
    if (link("example.txt", "example_link.txt") < 0) {
        perror("Link failed");
    } else {
        cout << "File linked successfully.\n";
    }

    if (unlink("example_link.txt") < 0) {
        perror("Unlink failed");
    } else {
        cout << "File unlinked successfully.\n";
    }

    struct stat fileStat;
    if (stat("example.txt", &fileStat) < 0) {
        perror("Stat failed");
    } else {
        cout << "File Size: " << fileStat.st_size << " bytes\n";
        cout << "File Permissions: " << ((fileStat.st_mode & S_IRUSR) ? "r" : "-")
             << ((fileStat.st_mode & S_IWUSR) ? "w" : "-")
             << ((fileStat.st_mode & S_IXUSR) ? "x" : "-") << endl;
    }
}

void communication_related() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) {
        close(pipefd[0]); // Close reading end in child
        const char *msg = "Hello from child!";
        write(pipefd[1], msg, strlen(msg));
        close(pipefd[1]); // Close writing end in child
        exit(0);
    } else {
        close(pipefd[1]); // Close writing end in parent
        char buffer[128];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));
        if (bytesRead < 0) {
            perror("Pipe read failed");
        } else {
            buffer[bytesRead] = '\0';
            cout << "Parent received: " << buffer << endl;
        }
        close(pipefd[0]); // Close reading end in parent
        wait(NULL);
    }

    // FIFO (named pipe)

    const char *fifoName = "/tmp/my_fifo";

    mkfifo(fifoName, 0666);



    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) {
        int fd = open(fifoName, O_WRONLY);
        const char *msg = "Message from child via FIFO";
        write(fd, msg, strlen(msg));
        close(fd);
        exit(0);
    } else {
        int fd = open(fifoName, O_RDONLY);
        char buffer[128];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead < 0) {
            perror("FIFO read failed");
        } else {
            buffer[bytesRead] = '\0';
            cout << "Parent received via FIFO: " << buffer << endl;
        }
        close(fd);
        wait(NULL);
    }
    unlink(fifoName); // Remove the FIFO file
}

void information_related() {
    cout << "Process ID: " << getpid() << endl;
    cout << "Parent Process ID: " << getppid() << endl;
    cout << "User ID: " << getuid() << endl;
    cout << "Group ID: " << getgid() << endl;
}

int main() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Process related system calls (fork, exit, wait)\n";
        cout << "2. File related system calls (open, read, write, close, link, unlink, stat)\n";
        cout << "3. Communication related system calls (pipe, FIFO)\n";
        cout << "4. Information related system calls\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                process_related();
                break;
            case 2:
                file_related();
                break;
            case 3:
                communication_related();
                break;
            case 4:
                information_related();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
    return 0;
}


