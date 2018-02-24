// A calculator which converts an angle to its base value
// Basically a modulo calculator
#include <iostream>

int main() {
	std::string input, angle;
	float angleValue, fractionBase = 1, fullAngleValue;
	size_t slash;
	
	std::cin >> input;
	// split the line into angle and fullAngle
	angle = input.substr(0, input.find("%"));
	fullAngleValue = std::stof(input.substr(input.find("%") + 1));
	
	// calculate the angle if it is in the form of a fraction
	slash = angle.find("/");
	if (slash == std::string::npos) {
		angleValue = std::stof(angle);
	} else {
		angleValue = std::stof(angle.substr(0, angle.find("/")));
		fractionBase = std::stof(angle.substr(angle.find("/") + 1));
		fullAngleValue *= fractionBase;
	}
	
	// get the base angle
	while (angleValue > fullAngleValue) {
		angleValue -= fullAngleValue;
	}
	while (angleValue < 0) {
		angleValue += fullAngleValue;
	}
	
	if (fractionBase == 1) {
		std::cout << angleValue << std::endl;
	} else {
		std::cout << angleValue << "/" << fractionBase << "=" << angleValue / fractionBase << std::endl;
	}
	
	// keep the console open
    std::cout << "Press enter to exit";
	std::cin.clear();
	std::cin.sync();
	std::cin.get();
	return 0;
}