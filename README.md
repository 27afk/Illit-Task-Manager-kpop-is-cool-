# Illit-Task-Manager-kpop-is-cool
ILLIT Task Manager, is a command-line application built in C++ that combines Object-Oriented Programming, file persistence, and multithreading to manage user tasks.
It allows users to interact with the system via a simple CLI to Add, Display, Delete, and Search tasks, which are persistently stored in the local iroha.json file.
Upon startup, the application immediately launches a dedicated background std::thread that runs a Calendar Checker. This thread automatically evaluates the dueDate of all non-completed tasks every 60 seconds, ensuring that any task whose due date is up or passed is automatically deleted from the system and saved to the file, demonstrating a functional implementation of non-blocking automation.
