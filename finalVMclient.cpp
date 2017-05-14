#include <iostream>
#include "VMmain.cpp"
using namespace std;


int main(int argc, char *argv[])
{
    VM manager;

    string fileName;


	if(argc != 2) { //checks to make sure there is the correct amount of arguments
            cout << "Incorrect Number of Arguments.\n" << endl;
            return 1; }

	//fileName = argv[1]; //gets the file name

    manager.central(argv[1]); //passes file name to main function
}
