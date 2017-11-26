// Prevadec 2.0 for Minecraft Java 1.13
// by kulisak12
#include <iostream>
#include <string>
#include <fstream>
#include "readLine.cpp"
#include "addBackslashes.cpp"
#include "endAll.cpp"
#define INPUT "input.ezop"
#define DEFAULT_OUTPUT "output.txt"
using namespace std;

const string genericError = "Error on line ";
const string openingError = "Error opening file ";
int lineNumber = 0;

// allocate memory for strings taken from input
string *instructions = new string;
string *command = new string;
string *finalOutput = new string;
ifstream inputFile;
ofstream outputFile;

int main() {
	string readLine();
	void addBackslashes(string *f_command, int newBackslashesPerOld);
	void endAll();

	size_t brackets[3]; // "(", ")", "{"
	size_t blockStateAttributes[3]; // "f=", "c=", ","
	size_t space;
	string outputFileName = DEFAULT_OUTPUT;
	string blockType, blockStates, blockNbt;
	string coordinates;
	
	try {
		inputFile.open(INPUT);
		if (!inputFile.is_open()) {
			cout << openingError << INPUT << " for reading\n";
			throw 301;
		}

		*instructions = readLine();
		// end of file reached (file empty)
		if (*instructions == "#EOF") {
			cout << genericError << lineNumber << ": Input file empty\n";
			throw 311;
			// if output filename is defined
		}
		else if (instructions->substr(0, 6) == "output") {
			outputFileName = instructions->substr(7);
			*instructions = readLine();
		}

		outputFile.open(outputFileName, ios::trunc);
		if (!outputFile.is_open()) {
			cout << openingError << outputFileName << " for writing\n";
			throw 302;
		}
		*finalOutput = "summon falling_block ~ ~0.5 ~ {Time:1,BlockState:{Name:\"activator_rail\",Properties:{powered:\"true\"}},Passengers:[";

		while (*instructions != "#EOF") {
			// load the command
			*command = readLine();
			if (*command == "#EOF") {
				cout << genericError << lineNumber << ": End of file reached before a command was found\n";
				throw 312;
			}

			// remove the unnecessary slash preceding the command
			if ((*command)[0] == '/') {
				command->erase(0, 1);
			}

			// case 1: run
			if (instructions->substr(0, 3) == "run") {
				addBackslashes(command, 1);
				*finalOutput += " {id:\"commandblock_minecart\",Command:\"" + *command + "\"},";

				// case 2: command block
			}
			else {
				// mark the position of parenthesis
				brackets[0] = instructions->find_first_of('(');
				if (brackets[0] == string::npos) {
					cout << genericError << lineNumber - 1 << ": Expected to find '('\n";
					throw 322;
				}

				brackets[1] = instructions->find_first_of(')');
				if (brackets[1] == string::npos) {
					cout << genericError << lineNumber - 1 << ": Expected to find ')'\n";
					throw 323;
				}

				// set block id
				if (instructions->substr(0, brackets[0]) == "impulse") {
					blockType = "command_block";
				}
				else if (instructions->substr(0, brackets[0]) == "chain") {
					blockType = "chain_command_block";
				}
				else if (instructions->substr(0, brackets[0]) == "repeat") {
					blockType = "repeating_command_block";
				}
				else {
					cout << genericError << lineNumber - 1 << ": Expected run, impulse, chain or repeat as first word, but got \"" << instructions->substr(0, brackets[0]) << "\"\n";
					throw 321;
				}

				// set block states
				blockStateAttributes[0] = instructions->find("f=", brackets[0]);
				if (blockStateAttributes[0] == string::npos) {
					cout << genericError << lineNumber - 1 << ": Expected to find \"f=\" in blockstates\n";
					throw 324;
				}
				blockStateAttributes[1] = instructions->find("c=", brackets[0]);
				blockStateAttributes[2] = instructions->find_first_of(',', brackets[0]);
				// if conditional is specified before facing
				// also if unspecified, then it has a value of string::npos == -1
				if (blockStateAttributes[1] < blockStateAttributes[0]) {
					blockStates = instructions->substr(blockStateAttributes[0] + 2, brackets[1] - blockStateAttributes[0] - 2);
				}
				else {
					// conditional specified after facing
					blockStates = instructions->substr(blockStateAttributes[0] + 2, blockStateAttributes[2] - blockStateAttributes[0] - 2);
				}

				// check if blockstate is valid
				if (!(blockStates == "up" || blockStates == "down" || blockStates == "north" || blockStates == "south" || blockStates == "west" || blockStates == "east")) {
					cout << genericError << lineNumber - 1 << ": Expected up, down, north, south, west or east as a blockstate value, but got \"" << blockStates << "\"\n";
					throw 325;
				}

				// c=1
				if ((*instructions)[blockStateAttributes[1] + 2] == '1') {
					blockStates += ",conditional=true";
				}

				// try to find the beginning of block nbt
				brackets[2] = instructions->find_first_of('{');
				blockNbt = "";

				// block nbt omitted
				if (brackets[2] == string::npos) {
					coordinates = instructions->substr(brackets[1] + 1);

					// block nbt specified
				}
				else {
					coordinates = instructions->substr(brackets[1] + 1, brackets[2] - brackets[1] - 2);
					blockNbt = ',' + instructions->substr(brackets[2] + 1);
					blockNbt.pop_back(); // delete last "}"
					addBackslashes(&blockNbt, 1);
				}

				// make coordinates relative
				space = -1;
				coordinates.push_back(' '); // needed for replacement of 0 by ~
				for (int i = 0; i < 3; i++) {
					space = coordinates.find_first_of(' ', space + 1);
					if (space == string::npos) {
						cout << genericError << lineNumber - 1 << ": Expected 3 coordinates, but got " << i << endl;
						throw 326;
					}
					else if (coordinates.substr(space, 3) == " 0 ") {
						coordinates.replace(space + 1, 1, "~");
					}
					else {
						coordinates.insert(space + 1, "~");
					}
				}
				if (coordinates.find_first_of(' ', coordinates.find_first_of(' ', space + 1) + 1) != string::npos) {
					cout << genericError << lineNumber - 1 << ": Expected only 3 coordinates. Did you put in an extra space?\n";
					throw 327;
				}

				addBackslashes(command, 3);
				*finalOutput += "{id:\"commandblock_minecart\",Command:\"setblock" + coordinates + blockType + "[facing=" + blockStates + "]{Command:\\\"" + *command + "\\\"" + blockNbt + "}\"},";
			}

			*instructions = readLine();
		}
		*finalOutput += "{id:\"commandblock_minecart\",Command:\"/setblock ~ ~2 ~ command_block{Command:\\\"/fill ~ ~ ~ ~ ~-2 ~ air\\\",auto:1b}\"},{id:\"commandblock_minecart\",Command:\"/kill @e[type=commandblock_minecart,distance=..1]\"}]}";
		// cout << *finalOutput;
		outputFile << *finalOutput;
	}
	catch (int errorCode) {
		outputFile << "An error occured";
		endAll();
		cin.get(); // keep the console open
		return errorCode;
	}

	endAll();
	return 0;
}