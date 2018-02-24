// Generator for a function which spawns a sphere made of blocks in minecarts
// by kulisak12
#include <iostream>
#include <fstream>

int main() {
	std::ofstream outputFile;
	int xRot, yRot;
	int step; // to be inserted
	
	// open file
	outputFile.open("spawn_sphere.mcfunction", std::ios::trunc);
	if (!outputFile.is_open()) {
		std::cerr << "Error writing output\n";
		
		// keep the console open
		std::cout << "Press enter to exit";
		std::cin.clear();
		std::cin.sync();
		std::cin.get();
		return 1;
	}
	
	// get step
	std::cin >> step;
	
	// create output
	for (xRot = 0; xRot < 360; xRot += step) {
		for (yRot = 0; yRot <= 180; yRot += step) {
			outputFile << "summon minecart ~ ~ ~ {CustomDisplayTile:1b,DisplayOffset:64,DisplayState:{Name:\"minecraft:quartz_block\"},Rotation:[" << std::to_string(xRot) << "f," << std::to_string(yRot) << "f],NoGravity:1b}\n";
		}
	}
	
	// close files
	outputFile.close();
	return 0;
}