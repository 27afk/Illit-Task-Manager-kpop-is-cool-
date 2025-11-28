#include <iostream>
#include <cstdlib>
#include "Task.hpp"

using namespace std;

// sets to default values constructor
Task::Task() {
    id = 0;
    name = "";
    description = "";
    priority = 0;
    dueDate.day = 0;
    dueDate.month = 0;
    dueDate.year = 0;
    category = "";
    status = NOT_STARTED;
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
}
// initializes a task with user defined values
void Task::CreateTask(){
    id = (rand() % 10000) + 1;
    cout << "Enter task name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter task description: ";
    getline(cin, description);
    cout << "Enter task priority (1-5): ";
    // Basic input validation for priority
    while (!(cin >> priority) || priority < 1 || priority > 5) {
        cout << "Invalid priority. Enter a number between 1 and 5: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    cout << "Enter due date (DD MM YYYY): ";
    cin >> dueDate.day >> dueDate.month >> dueDate.year;

    cout << "Enter task category: ";
    cin.ignore();
    getline(cin, category);
    status = NOT_STARTED;
}

void Task::PrintTask(){
    cout << "Task ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Priority: " << priority << endl;
    cout << "Due Date: " << dueDate.day << "/" << dueDate.month << "/" << dueDate.year << endl;
    cout << "Category: " << category << endl;
    cout << "Status: ";
    switch(status){
        case NOT_STARTED:
            cout << "Not Started" << endl;
            break;
        case IN_PROGRESS:
            cout << "In Progress" << endl;
            break;
        case COMPLETED:
            cout << "Completed" << endl;
            break;
    }
}
// Errorhandling function for task creation - assumed basic date/priority validation
bool Task::SillyPerson(){
    // Basic checks
    if (dueDate.month < 1 || dueDate.month > 12) return false;
    if (dueDate.day < 1 || dueDate.day > 31) return false;
    if (priority < 1 || priority > 5) return false;
    return true;

}
