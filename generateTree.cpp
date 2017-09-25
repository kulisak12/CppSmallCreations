#include <iostream>
#include <fstream>
using namespace std;

string path;

int main() {
	void splitIntoHalves(int fromFrame, int toFrame);
	int firstFrame, lastFrame;
	
	// Promt the user to put in initial values
	cout << "Put in first and last frame numbers\n";
	cin >> firstFrame >> lastFrame;
	cout << "Put in function path including namespace\n";
	cin >> path;
	
	try {
		splitIntoHalves(firstFrame, lastFrame);
	}
	catch (int errorNumber) {
		return errorNumber;
	}
	return 0;
}

// Create one file which handes the set interval and activates other functions
void splitIntoHalves(int fromFrame, int toFrame) {
	// Open file for writing
	ofstream functionFile(to_string(fromFrame) + "az" + to_string(toFrame) + ".mcfunction", ios::trunc);
	
	if (!functionFile.is_open()) {
		cerr << "\nError opening file\nPress enter to continue";
		cin.get(); cin.get();
		throw 1;
	}
	
	if (toFrame - fromFrame < 3) {
		// Interval small enough to activate individual frames
		for (; fromFrame <= toFrame; fromFrame++) {
			functionFile << "execute if @s[score_Animation=" << fromFrame << "] function " << 
			path << "f" << fromFrame << endl;
			// execute if @s[score_Animation=3] function animace:starosta1-1/f3
		}
	} else {
		// Split interval into halves; activate function again
		int half = (fromFrame + toFrame) / 2;
		functionFile << "execute if @s[score_Animation=.." << half << "] function " << 
		path << fromFrame << "az" << half << endl;
		splitIntoHalves(fromFrame, half);
		
		functionFile << "execute if @s[score_Animation=" << half + 1 << "..] function " << 
		path << half + 1 << "az" << toFrame << endl;
		splitIntoHalves(half + 1, toFrame);
	}
	
	functionFile.close();
}