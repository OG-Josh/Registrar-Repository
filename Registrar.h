#ifndef REGISTRAR_H_
#define REGISTRAR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include "LinkedList.h"
#include "Student.h"
#include "Window.h"
#include "Queue.h"
using namespace std;

class Registrar {
public:
    Registrar(string fileName);
    ~Registrar();

    void run();

private:
    void fillWindows();
    void readFile(string fileName); // Read line to queue fileLine
    bool getNextStudents();
    bool hasMoreStudents();
    bool stillProcessingStudents();
    void calcStats();
    void timeStep();

private:
    unsigned int numFileLines;
    Queue<int>* fileLines;
    // Queue student waiting
    Queue<Student*>* studentLine;
    // The array window available
    unsigned short numWindows;
    Window* windowArray;
    //List student completed register
    LinkedList<Student*>* completedStudents;
    unsigned int currentTime;
};

/**
 * Constructor
 */
Registrar::Registrar(string fileName) {
    currentTime = 0;
    readFile(fileName);
    studentLine = new Queue<Student*>();
    completedStudents = new LinkedList<Student*>();
    // fileLines->printQueue();
    // The first line will be the number of windows open
    numWindows = fileLines->remove();
    //create the window array
    windowArray = new Window[numWindows];
}

/**
 * Destructor. TODO: Need to remove all memory allocate before
 */
Registrar::~Registrar() {

}

/**
 * Read all line in the input file. Push to queue for process
 */
void Registrar::readFile(string fileName) {
    fileLines = new Queue<int>();
    ifstream file;
    file.open(fileName);
    if (file.is_open() == false)
        throw runtime_error(
                "Can not open file: " + fileName
                        + ". Please check again. Exiting");
    string line = "";
    int lineCounter = 1;
    // read until get EOF
    while (getline(file, line)) {
        try {
            int num = stoi(line);
            //make sure all the numbers are greater than 0
            if (num < 1)
                throw runtime_error(
                        "Invalid value. The value can not smaller than 1");
            fileLines->insert(num);
        } catch (const invalid_argument& e) {
            throw runtime_error(
                    "File named " + fileName
                            + " is not only integers. Failed on line "
                            + to_string(lineCounter) + ".");
        }
        lineCounter++;
    }
    file.close();
}

/**
 * Get next student for register.
 * Return True: this is time have student need to register. Otherwise is false
 */
bool Registrar::getNextStudents() {
    if (hasMoreStudents() == false)
        return false;

    // Try to check time of system is the same with time need to register.
    try {
        if (currentTime != (unsigned int) fileLines->peak())
            return false;
    } catch (const runtime_error& e) {
        throw runtime_error(
                "The time the next batch of students arrives could not be determined.\nEnsure your file is in the correct format.");
    }
    // go here mean this time need to handle. Remove time from input first
    // The next line will be the time (or clock tick) at which the next students arrive
    try {
        fileLines->remove();
    } catch (const runtime_error& e) {
        throw runtime_error(
                "The time the next batch of students arrives could not be determined.\nEnsure your file is in the correct format.");
    }

    // The next line will be the number of students that arrive at that time
    int numNextStudents;
    try {
        numNextStudents = fileLines->remove();
    } catch (const runtime_error& e) {
        throw runtime_error(
                "The amount of students does not match the times provided.");
    }

    // The following lines will be the amount of time each student needs at a window
    try {
        for (int i = 0; i < numNextStudents; ++i) {
            unsigned int studentWindowTime = fileLines->remove();
            Student* nextStudent = new Student(studentWindowTime, currentTime);
            studentLine->insert(nextStudent);
        }
    } catch (const runtime_error& e) {
        throw runtime_error(
                "The amount of students does not match the times provided.");
    }
    return true;
}

/**
 * Check if have more student need to process
 */
bool Registrar::hasMoreStudents() {
    // Input file is not empty. Mean need process data
    return !fileLines->isEmpty();
}

/**
 * Fulfill to all window avaiable
 */
void Registrar::fillWindows() {
    if (studentLine->isEmpty())
        return;
    //If have window open. Using this for student
    for (int i = 0; i < numWindows; ++i) {
        if (windowArray[i].getOccupied() == false) {
            try {
                windowArray[i].takeInStudent(studentLine->remove(),
                        currentTime);
            } catch (const runtime_error& e) {
                break;
            }
        }
    }
}

/**
 * Check if student is processing.
 */
bool Registrar::stillProcessingStudents() {
    //if there are still students in the file
    if (hasMoreStudents())
        return true;
    //check if any windows are still occupied
    for (int i = 0; i < numWindows; ++i) {
        if (windowArray[i].getOccupied() == true)
            return true;
    }
    //if there are any students in the line
    if (studentLine->isEmpty() == false)
        return true;
    return false;
}

/**
 * Increase current time and check for all process
 */
void Registrar::timeStep() {
    // Time step for all window
    for (int i = 0; i < numWindows; ++i) {
        windowArray[i].timeStep();
    }
    // Check if this time is finished process for any student
    for (int i = 0; i < numWindows; ++i) {
        if (windowArray[i].isDoneWithStudent()) {
            Student* completedStudent = windowArray[i].removeStudent();
            completedStudents->insertFront(completedStudent);
        }
    }

    // Get next student for process
    getNextStudents();

    // Fill student to window if it avaliable
    fillWindows();

    // increase time
    currentTime++;
}

/**
 * Calculate all stats. And print them
 */
void Registrar::calcStats() {
    unsigned int totalStudentQueueWaitTime = 0;
    float meanWaitTime;
    unsigned int medianWaitTime = 0;
    unsigned int longestWaitTime = 0;
    unsigned int numWaitingOverTenMin = 0;
    unsigned int numStudents = completedStudents->getSize();
    unsigned int* queueWaitTimeArray = new unsigned int[numStudents];
    for (unsigned int i = 0; i < numStudents; ++i) {
        Student* currStudent = completedStudents->removeFront();
        unsigned int studentsWaitTime = currStudent->getTimeEnteredWindow()
                - currStudent->getTimeEnteredLine();
        totalStudentQueueWaitTime += studentsWaitTime;
        queueWaitTimeArray[i] = studentsWaitTime;
        if (studentsWaitTime > longestWaitTime)
            longestWaitTime = studentsWaitTime;
        if (studentsWaitTime > 10)
            numWaitingOverTenMin++;
        completedStudents->insertBack(currStudent);
    }
    meanWaitTime = totalStudentQueueWaitTime / numStudents;
    float meanIdleTime;
    unsigned int longestIdleTime = 0;
    unsigned int numIdleOverFiveMin = 0;
    unsigned int totalWindowIdleTime = 0;
    for (int i = 0; i < numWindows; ++i) {
        totalWindowIdleTime += windowArray[i].getIdleTime();
        if (longestIdleTime < windowArray[i].getIdleTime())
            longestIdleTime = windowArray[i].getIdleTime();
        if (windowArray[i].getIdleTime() > 5)
            numIdleOverFiveMin++;
    }
    meanIdleTime = totalWindowIdleTime / numWindows;
    sort(queueWaitTimeArray, queueWaitTimeArray + completedStudents->getSize());
    int medianIndex = completedStudents->getSize() / 2;
    medianWaitTime = queueWaitTimeArray[medianIndex];
    cout << "1. The mean student wait time: " << meanWaitTime << endl;
    cout << "2. The median student wait time: " << medianWaitTime << endl;
    cout << "3. The longest student wait time: " << longestWaitTime << endl;
    cout << "4. The number of students waiting over 10 minutes: "
            << numWaitingOverTenMin << endl;
    cout << "5. The mean window idle time: " << meanIdleTime << endl;
    cout << "6. The longest window idle time: " << longestIdleTime << endl;
    cout << "7. Number of windows idle for over 5 minutes: "
            << numIdleOverFiveMin << endl;
}

/**
 * The registrar until all finished
 */
void Registrar::run() {
    while (stillProcessingStudents()) {
        timeStep();
    }
    // Mean all finished. Print the statistic
    calcStats();
}
#endif /* REGISTRAR_H_ */
