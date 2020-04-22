#ifndef WINDOW_H_
#define WINDOW_H_

#include "Student.h"
class Window {
public:
    Window();
    ~Window();
    void timeStep();
    void takeInStudent(Student* student, unsigned int currTime);
    bool isDoneWithStudent();
    Student* removeStudent();
    string toString();
    // Getter
    bool getOccupied();
    unsigned int getIdleTime();
    unsigned int getCurrentTime();
    unsigned int getTimeWithCurrentStudent();
    Student* getCurrentStudent();

    // Setter
    void setOccupied(bool val);
    void setIdleTime(unsigned int val);
    void setCurrentTime(unsigned int val);
    void setTimeWithCurrentStudent(unsigned int val);
    void setCurrentStudent(Student* std);
private:
    bool occupied;
    unsigned int idleTime;
    unsigned int currentTime;
    unsigned int timeWithCurrentStudent;
    Student* currentStudent;
};

/**
 * Constructor
 */
Window::Window() {
    occupied = false;
    idleTime = 0;
    currentTime = 0;
    timeWithCurrentStudent = 0;
}

/**
 * Destructor
 */
Window::~Window() {

}

// Getter
bool Window::getOccupied() {
    return occupied;
}

unsigned int Window::getIdleTime() {
    return idleTime;
}

unsigned int Window::getCurrentTime() {
    return currentTime;
}

unsigned int Window::getTimeWithCurrentStudent() {
    return timeWithCurrentStudent;
}

Student* Window::getCurrentStudent() {
    return currentStudent;
}

// Setter
void Window::setOccupied(bool val) {
    occupied = val;
}

void Window::setIdleTime(unsigned int val) {
    idleTime = val;
}

void Window::setCurrentTime(unsigned int val) {
    currentTime = val;
}

void Window::setTimeWithCurrentStudent(unsigned int val) {
    timeWithCurrentStudent = val;
}

void Window::setCurrentStudent(Student* student) {
    currentStudent = student;
}

/**
 * Handle time step
 */
void Window::timeStep() {
    if (occupied == true) {
        timeWithCurrentStudent++;
    } else {
        idleTime++;
    }
    currentTime++;
}

/**
 * Take student to this window
 */
void Window::takeInStudent(Student* student, unsigned int currTime) {
    occupied = true;
    currentStudent = student;
    currentStudent->setIsAtWindow(true);
    currentStudent->setTimeEnteredWindow(currTime);
}

/**
 * Check student is done with this current time
 * @return: True if have student need at this time. Otherwise is false
 */
bool Window::isDoneWithStudent() {
    // No student here
    if (occupied == false)
        return false;
    // Have student need at this time
    if (currentStudent->getTimeNeededAtWindow() == timeWithCurrentStudent)
        return true;
    return false;
}

/**
 * Remove the student from the window. And reset all info of window
 * @return: Student removed.
 */
Student* Window::removeStudent() {
    Student* tmp = currentStudent;
    currentStudent->setTimeLeftWindow(currentTime);
    currentStudent = nullptr;
    timeWithCurrentStudent = 0;
    occupied = false;
    return tmp;
}

/**
 * Print the window. Using for debuging
 */
string Window::toString() {
    string outputStr = "Occupied: " + to_string(occupied);
    if (occupied) {
        outputStr = outputStr + " Current Student: "
                + currentStudent->toString();
        outputStr = outputStr + " Time Spent at Window: "
                + to_string(timeWithCurrentStudent);
    }
    return outputStr;
}
#endif /* WINDOW_H_ */
