#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COURSES 50
#define MAX_STUDENTS 50
#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    char schedule[MAX_NAME_LEN];
    int courseID;
    int registeredStudents[MAX_STUDENTS];
    int studentCount;
} Course;

typedef struct {
    char name[MAX_NAME_LEN];
    int studentID;
    int enrolledCourses[MAX_COURSES];
    int enrolledCount;
} Student;

Course courses[MAX_COURSES];
Student students[MAX_STUDENTS];
int courseCount = 0, studentCount = 0;

// Function declaration
void addCourse();
void assignSchedule();
void viewCourses();
void registerStudent();
void viewSchedule();

int main() {
    int choice;

    while (1) {
        printf("\nCourse Registration System:\n");
        printf("1. Register for Course (Students)\n");
        printf("2. View Courses (Students)\n");
        printf("3. View Course Schedule\n");
        printf("4. Add Course (Faculty)\n");
        printf("5. Assign Schedule (Faculty)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                viewCourses();
                break;
            case 3:
                viewSchedule();
                break;
            case 4:
                addCourse();
                break;
            case 5:
                assignSchedule();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


//Function Definitions

// Faculty: Add a new course
void addCourse() {
    if (courseCount >= MAX_COURSES) {
        printf("Course limit reached.\n");
        return;
    }

    printf("Enter course name: ");
    scanf(" %[^\n]", courses[courseCount].name);
    courses[courseCount].courseID = courseCount + 1;
    courses[courseCount].studentCount = 0;
    strcpy(courses[courseCount].schedule, "Not Assigned");
    printf("Course added successfully! Course ID: %d\n", courses[courseCount].courseID);
    courseCount++;
}

// Faculty: Assign schedule to a course
void assignSchedule() {
    int courseID;
    printf("Enter Course ID to assign schedule: ");
    scanf("%d", &courseID);

    if (courseID <= 0 || courseID > courseCount) {
        printf("Invalid Course ID.\n");
        return;
    }

    printf("Enter schedule for the course (e.g., Mon 10:00 AM): ");
    scanf(" %[^\n]", courses[courseID - 1].schedule);
    printf("Schedule assigned successfully!\n");
}

// Students: View all courses
void viewCourses() {
    printf("\nAvailable Courses:\n");
    for (int i = 0; i < courseCount; i++) {
        printf("Course ID: %d, Name: %s, Schedule: %s\n",
                courses[i].courseID, courses[i].name, courses[i].schedule);
    }
}

// Students: Register for a course
void registerStudent() {
    char studentName[MAX_NAME_LEN];
    int courseID;

    printf("Enter your name: ");
    scanf(" %[^\n]", studentName);

    // Check if the student already exists
    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, studentName) == 0) {
            studentIndex = i;
            break;
        }
    }

    // If student doesn't exist, create a new one
    if (studentIndex == -1) {
        strcpy(students[studentCount].name, studentName);
        students[studentCount].studentID = studentCount + 1;
        students[studentCount].enrolledCount = 0;
        studentIndex = studentCount;
        studentCount++;
    }

    printf("Enter Course ID to register: ");
    scanf("%d", &courseID);

    if (courseID <= 0 || courseID > courseCount) {
        printf("Invalid Course ID.\n");
        return;
    }

    // Register the student for the course
    Course *course = &courses[courseID - 1];
    course->registeredStudents[course->studentCount] = students[studentIndex].studentID;
    course->studentCount++;

    students[studentIndex].enrolledCourses[students[studentIndex].enrolledCount] = courseID;
    students[studentIndex].enrolledCount++;

    printf("Registered successfully for %s!\n", course->name);
}

// View the schedule of all courses
void viewSchedule() {
    printf("\nCourse Schedules:\n");
    for (int i = 0; i < courseCount; i++) {
        printf("Course ID: %d, Name: %s, Schedule: %s\n",
                courses[i].courseID, courses[i].name, courses[i].schedule);
    }
}
