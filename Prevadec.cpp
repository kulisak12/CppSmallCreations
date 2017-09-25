#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

#define VSTUP "vstup.txt"
#define VYSTUP "vystup.txt"

int main(void)
{
	FILE *fvstup;
	FILE *fvystup;
	char x[8];
	char y[8];
	char z[8];
	char souradky[64];
	char run[10000];
	char tagy[10000];
	char cmd[10000];
	char cmd2[10000];
	char typ_run[64];
	string s1;
	int dv = 0;
	int last = 0;
	bool notfound = 1;
	size_t c;
	size_t d;
	size_t space1;
	size_t space2;
	size_t sour1;
	size_t sour;
	size_t zavorka1;
	size_t zavorka2;
	size_t zavorka3;
	size_t zavorky;
	string str_d;
	string str_c;
	string str_souradky;
	string str_tagy;
	string str_x;
	string str_y;
	string str_z;
	string str_typ_run;
	string odzavorky;

	//otevreni VSTUPU
	if ((fvstup = fopen(VSTUP, "r")) == NULL) {
		fprintf(stderr, "Chyba otevreni souboru %s pro cteni\n",
			VSTUP);
		return errno;
	}

	//otevru soubor VYSTUP
	fvystup = fopen(VYSTUP, "w+");

	//zapis zacatku do VYSTUPU
	fprintf(fvystup, "/summon falling_block ~ ~0.5 ~ {Time:1,Block:\"activator_rail\",Passengers:[");



	//while cyklus dokud neni konec soub
	do {
		last = 0;
		s1 = "";
		dv = 0;
		notfound = 1;
		str_d = "";
		str_c = "";

		//nacte
		fgets(run, sizeof(run), fvstup);
		fgets(cmd, sizeof(cmd), fvstup);

		if (strcmp(run, "run") == 1) {
			//prida do cmd lomitka
			for (int i = 0; i < 10000; i++) {
				if (cmd[i] == '\"' || cmd[i] == '\\') { //hleda lomitka a uvozovky
					for (last; last < i; last++) { //od posledniho lomitka do novyho zkopci cast textu
						s1 = s1 + cmd[last];
					}
					s1 = s1 + "\\";
					notfound = 0;
				}

				//konec radku
				if (cmd[i] == '\0') {
					for (last; last < i; last++) { //od posledniho lomitka do novyho zkopci cast textu
						s1 = s1 + cmd[last];
					}
				}
			};

			//pokud je potreba pridavat lomitka
			if (notfound == 1) {
				string s1(cmd);
				if (!s1.empty() && s1[s1.size() - 1] == '\n')
					s1.erase(s1.size() - 1);
				strcpy(cmd2, s1.c_str());
			}
			else {
				if (!s1.empty() && s1[s1.size() - 1] == '\n')
					s1.erase(s1.size() - 1);
				strcpy(cmd2, s1.c_str());
			}
		}
		else {
			for (int i = 0; i < 10000; i++) {
				if (cmd[i] == '\"' || cmd[i] == '\\') { //hleda lomitka a uvozovky
					for (last; last < i; last++) { //od posledniho lomitka do novyho zkopci cast textu
						s1 = s1 + cmd[last];
					}
					s1 = s1 + "\\\\\\";
					notfound = 0;
				}

				//konec radku
				if (cmd[i] == '\0') {
					for (last; last < i; last++) { //od posledniho lomitka do novyho zkopci cast textu
						s1 = s1 + cmd[last];
					}
				}
			};

			//pokud je potreba pridavat
			if (notfound == 1) {
				string s1(cmd);
				if (!s1.empty() && s1[s1.size() - 1] == '\n')
					s1.erase(s1.size() - 1);
				strcpy(cmd2, s1.c_str());
			}
			else {
				if (!s1.empty() && s1[s1.size() - 1] == '\n')
					s1.erase(s1.size() - 1);
				strcpy(cmd2, s1.c_str());
			}
		}


		string str_run(run);

		//pokud je run
		if (strcmp(run, "run") == 1) {
			fprintf(fvystup, "{id:\"commandblock_minecart\",Command:\"%s\"},", cmd2);
		}
		else {

			//tagy a souradky
			sour1 = str_run.find(" ");
			zavorka1 = str_run.find("{");
			zavorka2 = str_run.find_last_of("}");

			if (zavorka1 != string::npos) {
				//souradky
				sour = zavorka1 - 1 - sour1;
				str_souradky = str_run.substr(sour1 + 1, sour - 1);
				space1 = str_souradky.find(" ");
				space2 = str_souradky.find_last_of(" ");

				str_x = str_souradky.substr(0, space1);
				str_y = str_souradky.substr(space1 + 1, space2 - space1 - 1);
				str_z = str_souradky.substr(space2 + 1);
				//tagy
				zavorky = zavorka2 - zavorka1 - 1;
				str_tagy = "," + str_run.substr(zavorka1 + 1, zavorky);
				strcpy(tagy, str_tagy.c_str());
				
				str_tagy = "";
				last = 0;

				//prida do tagu lomitka
				notfound = 1;
				for (int i = 0; i < 10000; i++) {
					if (tagy[i] == '\"' || tagy[i] == '\\') { //hleda lomitka a uvozovky
						for (last; last < i; last++) { //od posledniho lomitka do novyho zkopci cast textu
							str_tagy = str_tagy + tagy[last];
						}
						str_tagy = str_tagy + "\\";
						notfound = 0;
					}

					//konec radku
					if (tagy[i] == '\0') {
						for (last; last < i; last++) { //od posledniho lomitka do novyho zkopci cast textu
							str_tagy = str_tagy + tagy[last];
						}
					}
				};

				//pokud je potreba pridavat lomitka
				if (notfound == 1) {
					string str_tagy(tagy);
					if (!str_tagy.empty() && str_tagy[str_tagy.size() - 1] == '\n')
						str_tagy.erase(str_tagy.size() - 1);
					strcpy(tagy, str_tagy.c_str());
				}
				else {
					if (!str_tagy.empty() && str_tagy[str_tagy.size() - 1] == '\n')
						str_tagy.erase(str_tagy.size() - 1);
					strcpy(tagy, str_tagy.c_str());
				}
				
			}
			else {
				//souradky
				str_souradky = str_run.substr(sour1 + 1);
				if (!str_souradky.empty() && str_souradky[str_souradky.size() - 1] == '\n')
					str_souradky.erase(str_souradky.size() - 1);

				space1 = str_souradky.find(" ");
				space2 = str_souradky.find_last_of(" ");

				str_x = str_souradky.substr(0, space1);
				str_y = str_souradky.substr(space1 + 1, space2 - space1 - 1);
				str_z = str_souradky.substr(space2 + 1);
				//tagy
				strcpy(tagy, "");
			}

			//prevod na char			
			strcpy(souradky, str_souradky.c_str());
			if (str_x == "0")
				str_x = "~";
			else str_x = "~" + str_x;
			if (str_y == "0")
				str_y = "~";
			else str_y = "~" + str_y;
			if (str_z == "0")
				str_z = "~";
			else str_z = "~" + str_z;

			strcpy(x, str_x.c_str());
			strcpy(y, str_y.c_str());
			strcpy(z, str_z.c_str());

			//typ command blocku
			zavorka3 = str_run.find("(");
			str_typ_run = str_run.substr(0, zavorka3);


			//conditional
			odzavorky = str_run.substr(zavorka3, 4);
			c = odzavorky.find("c") + 2;
			str_c = odzavorky.at(c);
			if (str_c == "1") {
				dv = dv + 8;
			}

			//direction
			d = str_run.find("d") + 2; //najde v stringu
			str_d = str_run.at(d); //vypise hodnotu ze stringu
			if (str_d == "d") {
				dv = dv + 0;
			}
			else if (str_d == "u") {
				dv = dv + 1;
			}
			else if (str_d == "n") {
				dv = dv + 2;
			}
			else if (str_d == "s") {
				dv = dv + 3;
			}
			else if (str_d == "w") {
				dv = dv + 4;
			}
			else if (str_d == "e") {
				dv = dv + 5;
			}

			if (str_typ_run == "repeat")
				strcpy(typ_run, "repeating_command_block");
			else if (str_typ_run == "chain")
				strcpy(typ_run, "chain_command_block");
			else strcpy(typ_run, "command_block");

			//Vypis
			fprintf(fvystup, "{id:\"commandblock_minecart\",Command:\"/setblock %s %s %s %s %i ", x, y, z, typ_run, dv);
			fprintf(fvystup, "replace {Command:\\\"%s\\\"%s}\"},", cmd2, tagy);
		}

	} while (feof(fvstup) == 0);

	fprintf(fvystup, "{id:\"commandblock_minecart\",Command:\"/setblock ~ ~1 ~ command_block 0 replace {Command:\\\"/fill ~ ~ ~ ~ ~-1 ~ air\\\",auto:1b}\"},{id:\"commandblock_minecart\",Command:\"/kill @e[type=commandblock_minecart,r=1]\"}]}");
	fclose(fvstup);
	fclose(fvystup);
	return 0;
}
