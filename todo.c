#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char tasks[MAX][100];
int count = 0;

// NEW: Robustly clears the input buffer to fix online compiler issues
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void loadTasks() {
    FILE *fp = fopen("tasks.txt", "r");
    if (fp == NULL) return;

    count = 0; 
    while (count < MAX && fgets(tasks[count], 100, fp)) {
        tasks[count][strcspn(tasks[count], "\n")] = '\0';
        if (strlen(tasks[count]) > 0) count++;
    }
    fclose(fp);
}

void saveTasks() {
    FILE *fp = fopen("tasks.txt", "w");
    if (fp == NULL) return;
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", tasks[i]);
    }
    fclose(fp);
}

void addTask() {
    if (count >= MAX) {
        printf("Task list full!\n");
        return;
    }
    printf("Enter task: ");
    if (fgets(tasks[count], 100, stdin)) {
        tasks[count][strcspn(tasks[count], "\n")] = '\0';
        if (strlen(tasks[count]) > 0) {
            count++;
            saveTasks();
            printf("Task added!\n");
        }
    }
}

void viewTasks() {
    if (count == 0) {
        printf("\nNo tasks available.\n");
        return;
    }
    printf("\nYour Tasks:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
}

void deleteTask() {
    if (count == 0) {
        printf("\nNo tasks to delete.\n");
        return;
    }
    viewTasks();
    int num;
    printf("Enter task number to delete: ");
    if (scanf("%d", &num) != 1) {
        clearBuffer();
        return;
    }
    clearBuffer(); 

    if (num < 1 || num > count) {
        printf("Invalid number!\n");
        return;
    }

    for (int i = num - 1; i < count - 1; i++) {
        strcpy(tasks[i], tasks[i + 1]);
    }
    count--;
    saveTasks();
    printf("Task deleted!\n");
}

int main() {
    int choice;
    loadTasks();

    while (1) {
        printf("\n--- TO-DO LIST ---\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearBuffer();
            continue;
        }
        clearBuffer(); // This is the key fix for the menu loop

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTask(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
