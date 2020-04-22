/**
 * The Registrar's Office Simulator program
 */
#include <iostream>
#include "Registrar.h"
using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Invalid running." <<endl;
        cout << "Used: " << argv[0] << " <inputfile>" << endl;
        return 1;
    }

    Registrar *registrasOffice;
    // Try to read the input file and run the system
    try {
        registrasOffice = new Registrar(argv[1]);
    }catch (const runtime_error& e) {
        cout << e.what() << endl;
        return 1;
    }

    // Now run office until all finished
    registrasOffice->run();
    return 0;
}


