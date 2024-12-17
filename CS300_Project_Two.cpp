/*
 * ProjectTwo.cpp
 *
 *  Date: December 10, 2024
 *  Author: Carlos Rodriguez
 *  Teacher: Professor Yurik
 *  Purpose: To help the department advisors to effectively communicate with students to let them see
 *  what is needed for their courses and if any prerequisites are required for that course they want to
 *  enroll in. By doing this, we develop a software they can use that uses the Hash Table method and 
 *  prints out the course list in alphanumerical order.
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Course structure for the course number, course title, and prerequisites
struct Course {
    string courseNumber;     // Course identifier
    string courseTitle;      // Full name of the course
    vector<string> prerequisites;  // List of prerequisites for the specified course
};

// Hash table for storing courses using courseNumber as the key identifier
unordered_map<string, Course> courses;

// Function declarations
void LoadData(const string& fileName);   // Loads course data from a file
void PrintCourseList();                  // Prints all courses in alphanumeric order
void PrintCourseInfo(const string& courseNumber); // Prints specific course details
void DisplayMenu();                      // Displays the main menu

int main() {
    int choice;                          // User menu selection
    string fileName, courseNumber;

    cout << "Welcome to the course planner." << endl;

    do {
        DisplayMenu();                   // Show the menu
        cin >> choice;                   // Read user input
        cin.ignore();                    // Clear input buffer

        switch (choice) {
            case 1:
                cout << "Enter the file name: ";
                getline(cin, fileName); // Prompt for file name
                LoadData(fileName);      // Load data from the specified file
                break;
            case 2:
                PrintCourseList();       // Print all courses
                break;
            case 3:
                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);   // Get course number from user
                PrintCourseInfo(courseNumber); // Display course details
                break;
            case 9:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;  // Invalid options message
                break;
        }
    } while (choice != 9);               // Repeat until user chooses to exit

    return 0;
}

// Loads data from the CSV file into the hash table
void LoadData(const string& fileName) {
    ifstream file(fileName);             // Open file
    if (!file) {
        cout << "Error opening file. Please check the file name and try again." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {       // Read file line by line
        stringstream ss(line);          // Parse line into a string stream
        Course course;
        getline(ss, course.courseNumber, ',');  // Extract course number
        getline(ss, course.courseTitle, ',');   // Extract course title

        string prereq;
        while (getline(ss, prereq, ',')) {      // Extract prerequisites
            course.prerequisites.push_back(prereq);
        }

        courses[course.courseNumber] = course;  // Store course in hash table
    }
    cout << "Data loaded successfully." << endl;
}

// Prints all courses in alphanumeric order
void PrintCourseList() {
    if (courses.empty()) {             // Check if data is loaded
        cout << "No courses available. Please load the data first." << endl;
        return;
    }

    vector<Course> courseList;
    for (const auto& pair : courses) {
        courseList.push_back(pair.second);   // Collect courses into a vector
    }

    // Sort courses by course number
    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
    });

    cout << "Here is a sample schedule:" << endl;
    for (const auto& course : courseList) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;  // Print course info
    }
}

// Prints details of a specific course
void PrintCourseInfo(const string& courseNumber) {
    auto it = courses.find(courseNumber);    // Search for course by number
    if (it == courses.end()) {
        cout << "Course not found." << endl;  // Handle missing course
        return;
    }

    const Course& course = it->second;
    cout << course.courseNumber << ", " << course.courseTitle << endl;  // Print course info
    if (course.prerequisites.empty()) {
        cout << "No prerequisites required." << endl;
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];  // Print each prerequisite
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Displays the main menu
void DisplayMenu() {
    cout << "\n1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}
