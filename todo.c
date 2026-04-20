#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char tasks[MAX][100];
int count = 0;

// Load tasks from file
void loadTasks() {
    FILE *fp = fopen("tasks.txt", "r");
    if (fp == NULL) return;

    while (fgets(tasks[count], 100, fp)) {
        tasks[count][strcspn(tasks[count], "\n")] = '\0';
        count++;
    }
    fclose(fp);
}

// Save tasks to file
void saveTasks() {
    FILE *fp = fopen("tasks.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", tasks[i]);
    }
    fclose(fp);
}

// Add task
void addTask() {
    if (count >= MAX) {
        printf("Task list full!\n");
        return;
    }
    printf("Enter task: ");
    getchar(); // clear buffer
    fgets(tasks[count], 100, stdin);
    tasks[count][strcspn(tasks[count], "\n")] = '\0';
    count++;
    saveTasks();
}

// View tasks
void viewTasks() {
    if (count == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\nYour Tasks:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
}

// Delete task
void deleteTask() {
    int num;
    viewTasks();
    if (count == 0) return;

    printf("Enter task number to delete: ");
    scanf("%d", &num);

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
        scanf("%d", &choice);

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