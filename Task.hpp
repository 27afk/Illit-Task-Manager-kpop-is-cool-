#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
using namespace std;

struct Date
{
    int day;
    int month;
    int year;
};

enum Status{
    NOT_STARTED,
    IN_PROGRESS,
    COMPLETED
};

class Task{
    public:
        int id;
        string name;
        string description;
        int priority;
        Date dueDate;
        string category; 
        Status status; 
    public:
        Task();
        void CreateTask();
        void PrintTask();
        bool SillyPerson();

};
