// 💗🩷 ILLIT TASK MANAGER HEADER 🩷💗
// this file controls all the task management magic hehe
// like a little idol manager but for your goofy tasks 🎤✨

#pragma once
#include "Task.hpp"
#include <fstream>
#include <string>
#include <ctime> // Added for CheckAndCleanUpTasks arguments
using namespace std;

class TaskManager {
private:

    int taskCount;  
    // 💖 counts how many tasks we currently have in our tiny idol lineup
    // (max 100 because we're keeping it SMALL and CUTE)

    Task tasks[100];
    // 💖 an array of 100 Task objects
    // like a dorm where each task gets its own little room 🎀

    void SaveTasks();
    // 💖 writes all tasks back into iroha.json

public:

    TaskManager();
    // 💖 constructor

    void AddTask();
    // 💖 creates a new Task, validates it (RetardPerson()) and adds it

    void DeleteTask(int id);
    // 💖 deletes a task with matching id

    void DisplayAllTasks();
    // 💖 prints EVERY task in order of ID

    void DisplayTasksByCategory(string category);
    // 💖 prints tasks with matching category

    void DisplayPriority(int priority);
    // 💖 prints tasks with chosen priority

    // New methods for CLI and background thread
    void SearchTask(int id, string name); 
    // New: searches for a task by ID or name
    
    void CheckAndCleanUpTasks(int currentDay, int currentMonth, int currentYear);
    // New: function run by the thread to delete expired tasks
};