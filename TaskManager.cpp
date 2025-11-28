#include "TaskManager.hpp"
#include "Task.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio> // For sscanf
#include <algorithm> 

using namespace std;

// ------------------------------------
// --- Helper Function for Date Check ---
// ------------------------------------
// Returns true if the dueDate is in the past or is today.
bool isDueDatePassed(const Date& dueDate, int currentDay, int currentMonth, int currentYear) {
    if (dueDate.year < currentYear) return true;
    if (dueDate.year == currentYear && dueDate.month < currentMonth) return true;
    if (dueDate.year == currentYear && dueDate.month == currentMonth && dueDate.day <= currentDay) return true;
    return false;
}

// ------------------------------------
// --- TaskManager Core Implementations ---
// ------------------------------------

// Constructor (Simplified JSON loading)
TaskManager::TaskManager() {
    taskCount = 0;
    ifstream inFile("iroha.json");
    if (!inFile) {
        cout << "iroha.json not found. Creating a fresh file! 💀\n";
        ofstream out("iroha.json");
        out << "{\n    \"tasks\": []\n}" << endl;
        out.close();
        return;
    }

    // Simplified JSON parsing logic...
    // In a real application, consider a robust JSON library.
    // ... (logic to load tasks from file is assumed and included here) ...
    string line;
    Task t;
    while (getline(inFile, line)) {
        if (line.find("\"id\":") != string::npos) {
            sscanf(line.c_str(), "        \"id\": %d,", &t.id);

            getline(inFile, line);
            size_t start = line.find(": \"") + 3;
            size_t end = line.find("\",");
            if (start != string::npos && end != string::npos) t.name = line.substr(start, end - start);

            getline(inFile, line);
            start = line.find(": \"") + 3;
            end = line.find("\",");
            if (start != string::npos && end != string::npos) t.description = line.substr(start, end - start);
            
            getline(inFile, line);
            sscanf(line.c_str(), "        \"priority\": %d,", &t.priority);

            getline(inFile, line);
            sscanf(line.c_str(), "        \"dueDate\": \"%d/%d/%d\",", &t.dueDate.day, &t.dueDate.month, &t.dueDate.year);

            getline(inFile, line); 
            start = line.find(": \"") + 3;
            end = line.find("\",");
            string status_str;
            if (start != string::npos && end != string::npos) {
                status_str = line.substr(start, end - start);
            }

            if (status_str == "Not Started") t.status = NOT_STARTED;
            else if (status_str == "In Progress") t.status = IN_PROGRESS;
            else if (status_str == "Completed") t.status = COMPLETED;
            else t.status = NOT_STARTED;
            
            tasks[taskCount++] = t;
        }
    }
    inFile.close();
}

// Save all tasks to iroha.json
void TaskManager::SaveTasks() {
    ofstream out("iroha.json");
    out << "{\n    \"tasks\": [\n";
    for (int i = 0; i < taskCount; i++) {
        out << "        {\n";
        out << "            \"id\": " << tasks[i].id << ",\n";
        out << "            \"name\": \"" << tasks[i].name << "\",\n";
        out << "            \"description\": \"" << tasks[i].description << "\",\n";
        out << "            \"priority\": " << tasks[i].priority << ",\n";
        out << "            \"dueDate\": \"" << tasks[i].dueDate.day << "/" << tasks[i].dueDate.month << "/" << tasks[i].dueDate.year << "\",\n";
        out << "            \"category\": \"" << tasks[i].category << "\",\n";
        out << "            \"status\": \"";
        switch(tasks[i].status){
            case NOT_STARTED: out << "Not Started"; break;
            case IN_PROGRESS: out << "In Progress"; break;
            case COMPLETED: out << "Completed"; break;
        }
        out << "\"\n";
        out << "        }";
        if (i < taskCount - 1) out << ",\n";
        else out << "\n";
    }
    out << "    ]\n}";
    out.close();
}

// Add a new task (Existing Logic)
void TaskManager::AddTask() {
    if (taskCount >= 100) {
        cout << "Task capacity reached (100). Cannot add more tasks. 🚫\n";
        return;
    }
    Task t;
    t.CreateTask();
    if (t.RetardPerson()) {
        tasks[taskCount++] = t;
        SaveTasks();
        cout << "Task added successfully! 🎉\n";
    } else {
        cout << "Invalid task data. Task not added. ❌\n";
    }
}

// Delete a task by ID (Existing Logic)
void TaskManager::DeleteTask(int id) {
    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            found = true;
            for (int j = i; j < taskCount - 1; j++)
                tasks[j] = tasks[j + 1];
            taskCount--;
            SaveTasks();
            cout << "Deleted task with ID " << id << " 💀\n";
            break;
        }
    }
    if (!found) cout << "No task found with ID " << id << " ❌\n";
}

// Display all tasks (Existing Logic)
void TaskManager::DisplayAllTasks() {
    if (taskCount == 0) {
        cout << "No tasks available. Go create one! 🌈\n";
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        tasks[i].PrintTask();
        cout << "----------------\n";
    }
}

// Display tasks by category (Existing Logic)
void TaskManager::DisplayTasksByCategory(string category) {
    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].category == category) {
            tasks[i].PrintTask();
            cout << "----------------\n";
            found = true;
        }
    }
    if (!found) cout << "No tasks found in category '" << category << "' 😔\n";
}

// Display tasks by priority (Existing Logic)
void TaskManager::DisplayPriority(int priority) {
    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].priority == priority) {
            tasks[i].PrintTask();
            cout << "----------------\n";
            found = true;
        }
    }
    if (!found) cout << "No tasks found with priority " << priority << " 😔\n";
}

// Search by ID or name (New CLI Logic)
void TaskManager::SearchTask(int id, string name) {
    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        // Search by ID (if ID is provided and not 0) or by name (partial match is OK)
        if ((id != 0 && tasks[i].id == id) || (!name.empty() && tasks[i].name.find(name) != string::npos)) {
            tasks[i].PrintTask();
            cout << "----------------\n";
            found = true;
        }
    }
    if (!found) cout << "No task found matching criteria. ❌\n";
}

// ------------------------------------
// --- New Thread Cleanup Logic ---
// ------------------------------------

void TaskManager::CheckAndCleanUpTasks(int currentDay, int currentMonth, int currentYear) {
    bool tasksDeleted = false;
    
    // Iterate backwards to safely delete tasks and update the array index
    for (int i = taskCount - 1; i >= 0; i--) {
        // Only consider tasks that are NOT completed
        if (tasks[i].status != COMPLETED && isDueDatePassed(tasks[i].dueDate, currentDay, currentMonth, currentYear)) {
            
            cout << "\n[Calendar Checker] AUTO-DELETE: Task '" << tasks[i].name << "' (ID: " << tasks[i].id << ") is past due or due today. Deleting... 💥" << endl;
            
            // Shift elements to the left to overwrite the current (deleted) task
            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            taskCount--;
            tasksDeleted = true;
        }
    }

    if (tasksDeleted) {
        SaveTasks(); // Persist changes to iroha.json
        cout << "[Calendar Checker] Task cleanup complete. Remaining tasks saved to iroha.json. 💾" << endl;
    }
}