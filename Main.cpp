// AX & RJ's ILLIT Task Manager 🌸💀
// Date: 11-27-2025 ✨

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <functional> // For std::ref ✨
#include "Task.hpp"
#include "TaskManager.hpp"

using namespace std;

// Helper function to get the current date 🌼⏰
Date getCurrentDate(){
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    // tm_year is years since 1900, tm_mon is months since Jan (0-11)
    return{
        now->tm_mday,       // day 🌸
        now->tm_mon + 1,    // month 🌷
        now->tm_year + 1900 // year ✨
    };
}

// The magical calendar-checking thread 🧵✨
// Keeps an eye on your tasks so none get lonely or forgotten 💀💖
void calendarChecker(TaskManager& tm) {
    // This loop runs forever in a sparkly separate thread ✨
    while (true) {
        // Check every 60 seconds (aka every minute is a chance for love 💌)
        this_thread::sleep_for(chrono::seconds(60)); 

        Date current = getCurrentDate();
        // Call the manager's cleanup spell to tidy up expired tasks 🌸
        tm.CheckAndCleanUpTasks(current.day, current.month, current.year);
    }
}

// --- Main Stage of the ILLIT Task Manager Show 🎤✨ ---
int main(void){
    // Recommended practice for mixing cin and getline (so we don't break the kawaii flow 💖)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "Welcome to the ILLIT Task Manager! 🎤✨" << endl;
    
    // Create the magical TaskManager object 🧚‍♀️
    TaskManager manager; 

    // 1. START THE CALENDAR CHECKER THREAD 🔮
    // Pass the manager by reference (std::ref) and let it float freely 🌈
    thread checker_thread(calendarChecker, std::ref(manager));
    checker_thread.detach(); 
    
    cout << "[INFO] Calendar checker thread started! Watching your tasks every 60s ⏳✨\n";
    cout << "----------------------------------------------------------------" << endl;

    string command;
    int id, priority;
    string name, category;
    
    // 2. MAIN COMMAND-LINE INTERFACE LOOP 🎀
    while (true) {
        cout << "\nEnter command (add, delete, display, category, priority, search, help, exit): ";
        // Reads command, skipping leading whitespace 🌸
        if (!getline(cin >> ws, command)) break;

        if (command == "add") {
            manager.AddTask(); // Sprinkle a new task into existence 💖
        } else if (command == "delete") {
            cout << "Enter Task ID to delete: ";
            if (cin >> id) manager.DeleteTask(id); 
            else { 
                cout << "Invalid ID. ❌\n"; 
                cin.clear(); cin.ignore(10000, '\n'); 
            }
        } else if (command == "display") {
            cout << "\n--- All Tasks ---\n"; // Show your cute task collection 🌸
            manager.DisplayAllTasks();
        } else if (command == "category") {
            cout << "Enter category to display: ";
            getline(cin >> ws, category);
            cout << "\n--- Tasks in Category '" << category << "' ---\n";
            manager.DisplayTasksByCategory(category);
        } else if (command == "priority") {
            cout << "Enter priority level (1-5) to display: ";
            if (cin >> priority) manager.DisplayPriority(priority);
            else { cout << "Invalid priority. ❌\n"; cin.clear(); cin.ignore(10000, '\n'); }
        } else if (command == "search") {
            cout << "Enter Task ID (0 to search by name): ";
            cin >> id;
            if (id == 0) {
                cout << "Enter Task Name (partial match is OK): ";
                cin.ignore();
                getline(cin >> ws, name);
                manager.SearchTask(0, name); // Find your shiny task by name 💎
            } else {
                manager.SearchTask(id, ""); // Or find it by magical ID ✨
            }
        } else if (command == "help") {
            cout << "\nAvailable Commands (your task spells ✨):\n"
                 << "  add      - Create a new task 📝\n"
                 << "  delete   - Delete a task by ID 💀\n"
                 << "  display  - Show all tasks 🌸\n"
                 << "  category - Show tasks by category 🎀\n"
                 << "  priority - Show tasks by priority level 🔥\n"
                 << "  search   - Search for a task by ID or name 🔍\n"
                 << "  exit     - Close the magical task manager 👋\n";
        } else if (command == "exit") {
            cout << "Shutting down Task Manager. Goodbye! 👋✨\n";
            break;
        } else {
            cout << "Unknown command: " << command << ". Type 'help' for your spellbook 🧙‍♀️\n";
        }
    }

    // The calendar thread floats away peacefully when the program ends 🌈
    return 0;
}
