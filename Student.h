#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
using namespace std;
class Student {
public:
    Student(unsigned int timeNeeded, unsigned int currentTime);
    ~Student();
    string toString();

    // Getter
    bool getIsAtWindow() {
        return isAtWindow;
    }

    unsigned int getTimeEnteredLine() {
        return timeEnteredLine;
    }

    unsigned int getTimeEnteredWindow() {
        return timeEnteredWindow;
    }

    unsigned int getTimeNeededAtWindow() {
        return timeNeededAtWindow;
    }

    unsigned int getTimeLeftWindow() {
        return timeLeftWindow;
    }

    // Setter
    void setIsAtWindow(bool val) {
        isAtWindow = val;
    }
    void setTimeEnteredLine(unsigned int val) {
        timeEnteredLine = val;
    }
    void setTimeEnteredWindow(unsigned int val) {
        timeEnteredWindow = val;
    }
    void setTimeNeededAtWindow(unsigned int val) {
        timeNeededAtWindow = val;
    }
    void setTimeLeftWindow(unsigned int val) {
        timeLeftWindow = val;
    }
private:
    bool isAtWindow;
    unsigned int timeEnteredLine;
    unsigned int timeEnteredWindow;
    unsigned int timeNeededAtWindow;
    unsigned int timeLeftWindow;

};

Student::Student(unsigned int timeNeeded, unsigned int currentTime) {
    isAtWindow = false;
    timeEnteredLine = currentTime;
    timeEnteredWindow = 0;
    timeNeededAtWindow = timeNeeded;
    timeLeftWindow = 0;
}

string Student::toString() {
    return ("Time Entered: " + to_string(timeEnteredLine)
            + "\tTime needed at window: " + to_string(timeNeededAtWindow));
}
#endif /* STUDENT_H_ */
