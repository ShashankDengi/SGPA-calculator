#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define USER_DATA_FILE "userdata.txt"
#define MAX_TEXT_LENGTH 1000

// Structure to represent a user
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Function prototypes
void loadUserData();
void saveUserData();
void registerUser();
int authenticateUser();

// Array to store user data
User users[MAX_USERS];
int numUsers = 0;

struct Subject {
    char name[50];
    int credits;
    int totalMarks;
    int marksObtained;
};

int calculateGradePoint(int marks);

float calculateSGPA(struct Subject *subjects, int numSubjects);

int main() {

    int numSubjects;
    char pername[50],usn[30],uni[70];


    FILE *reportFile = fopen("report.txt", "w"); // Open file for writing

    if (reportFile == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }


    char text[MAX_TEXT_LENGTH];
    char check;
    char fileName[100];
    FILE *file;
    int choice;
    int currentUserIndex = -1;

    // Load user data from the file when the program starts
    loadUserData();

    printf("\t\t------------\n");
    printf("\t\tSGPA calculator\n");
    printf("\t\t------------\n");


    while (1) {
        if (currentUserIndex == -1) {
            printf("\n1. Login\n");
            printf("2. Register\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    currentUserIndex = authenticateUser();
                    if (currentUserIndex != -1) {
                        printf("Login successful! Welcome, %s.\n", users[currentUserIndex].username);
                    } else {
                        printf("Login failed. Invalid username or password.\n");
                    }
                    break;
                case 2:
                    registerUser();
                    break;
                case 3:
                    // Save user data to the file when exiting
                    saveUserData();
                    printf("Exiting...\n");
                    exit(0);
                    break; // Added break here
                default:
                    printf("Invalid choice. Please try again.\n");
                    break; // Added break here
            }
        } else {

    printf("Enter your name: ");
    scanf("\n");
    scanf("%[^\n]%*c", &pername);

    printf("Enter your USN: ");
    scanf("\n");
    scanf("%s", &usn);

    printf("Name of college/university : ");
    scanf("\n");
    scanf("%[^\n]%*c", &uni);




    printf("Enter the number of subjects: ");
    scanf("%d", &numSubjects);

    struct Subject *subjects = (struct Subject *)malloc(numSubjects * sizeof(struct Subject));

    for (int i = 0; i < numSubjects; i++)
    {
        printf("\nEnter details for subject %d:\n", i + 1);
        printf("Subject Name: ");
        scanf("\n");
        scanf("%[^\n]%*c", &subjects[i].name);
        printf("Credits: ");
        scanf("%d", &subjects[i].credits);
        printf("Marks Obtained: ");
        scanf("%d", &subjects[i].marksObtained);
    }

    float sgpa = calculateSGPA(subjects, numSubjects);


    fprintf(reportFile, "PROGRESS REPORT:\n\n");
    fprintf(reportFile, "Name: %s\n",pername);
    fprintf(reportFile, "USN: %s \n",usn);
    fprintf(reportFile, "College: %s \n\n",uni);
    fprintf(reportFile, "Total Subjects: %d\n", numSubjects);

    for (int i = 0; i < numSubjects; i++) {
        fprintf(reportFile, "\nSubject %d:\n", i + 1);
        fprintf(reportFile, "Name: %s\n", subjects[i].name);
        fprintf(reportFile, "Credits: %d\n", subjects[i].credits);
        fprintf(reportFile, "Marks Obtained: %d\n", subjects[i].marksObtained);
        fprintf(reportFile, "Total Marks: %d\n", subjects[i].totalMarks);
        fprintf(reportFile, "Grade Points: %d\n", calculateGradePoint(subjects[i].marksObtained));
    }

    fprintf(reportFile, "\nSGPA: %.2f\n", sgpa);

    fclose(reportFile); // Close the file

    if (sgpa != -1)
    {
        printf("\nYour SGPA for the semester: %.2f\n", sgpa);
    }

    printf("A detailed report as been created named report.txt\n");

    free(subjects); // Free allocated memory
    return 0;

            exit(0);
            }
        }
    }

// Function to calculate grade points based on marks
int calculateGradePoint(int marks)
{
    if (marks >= 90 && marks <= 100)
        return 10;
    else if (marks >= 80 && marks <= 89)
        return 9;
    else if (marks >= 70 && marks <= 79)
        return 8;
    else if (marks >= 60 && marks <= 69)
        return 7;
    else if (marks >= 55 && marks <= 59)
        return 6;
    else if (marks >= 50 && marks <= 54)
        return 5;
    else if (marks >= 40 && marks <= 49)
        return 0;
    else
        return -1; // Invalid marks
}

// Function to calculate SGPA
float calculateSGPA(struct Subject *subjects, int numSubjects)
{
    int totalCredits = 0;
    float totalSGPA = 0.0;

    for (int i = 0; i < numSubjects; i++)
    {
        int gradePoint = calculateGradePoint(subjects[i].marksObtained);
        if (gradePoint == -1)
        {
            printf("Invalid marks entered for subject %d. Exiting.\n", i + 1);
            return -1;
        }

        totalCredits += subjects[i].credits;
        totalSGPA += (float) (gradePoint * subjects[i].credits);
    }

    if (totalCredits == 0)
    {
        printf("Total credits cannot be zero. Exiting.\n");
        return -1;
    }

    return totalSGPA / totalCredits;
}

// Function to load user data from a file
void loadUserData() {
    FILE* file1 = fopen(USER_DATA_FILE, "r");
    if (file1 == NULL) {
        return; // No user data file exists yet
    }

    while (fscanf(file1, "%s %s", users[numUsers].username, users[numUsers].password) != EOF) {
        numUsers++;
    }

    fclose(file1);
}

// Function to save user data to a file
void saveUserData() {
    FILE* file = fopen(USER_DATA_FILE, "w");
    if (file == NULL) {
        printf("Error: Unable to save user data.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

// Function to register a new user
void registerUser() {
    if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached. Cannot register more users.\n");
        return;
    }

    printf("Enter a username (up to %d characters): ", MAX_USERNAME_LENGTH - 1);
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);

    // Check if the username is already taken
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists. Please choose a different one.\n");
            return;
        }
    }

    printf("Enter a password (up to %d characters): ", MAX_PASSWORD_LENGTH - 1);
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    // Add the new user
    strcpy(users[numUsers].username, username);
    strcpy(users[numUsers].password, password);
    numUsers++;

    printf("Registration successful.\n");

    // Save user data to the file
    saveUserData();
}

// Function to authenticate a user
int authenticateUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i; // User authenticated, return user index
        }
    }

    return -1; // Authentication failed
}
