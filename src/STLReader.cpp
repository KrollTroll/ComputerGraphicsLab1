/*
 * STLReader.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: ckroll
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

float maxX;
float minX;
float maxY;
float minY;
float maxZ;
float minZ;
int total = 0;

float xFlo;
float yFlo;
float zFlo;
bool initialized = false;
bool validFile = false;

/**
 * This function prints to the console as well as checks min/max values
 */
void printAndCheck(){

	//This upcoming large section is the check portion
	if(xFlo > maxX){
		maxX = xFlo;
	}
	else if(xFlo < minX){
		minX = xFlo;
	}

	if(yFlo > maxY){
		maxY = yFlo;
	}
	else if(yFlo < minY){
		minY = yFlo;
	}

	else if(zFlo > maxZ){
		maxZ = zFlo;
	}
	if(zFlo < maxZ){
		minZ = xFlo;
	}

	//This block is the print block
	cout << "Facet " << total << ": vertX = " << setw(9) << xFlo << ",\t vertY = " << setw(9) << yFlo << ", \tvertZ = " << zFlo << "\n";
}

/**
 * prints out the minimum and maximum vertices for the file
 */
void minMax(){
	cout << "\nMIN/MAX VERTICES:\n\n";
	cout << "MIN X: " << minX << "\nMAX X: " << maxX << "\n\n";
	cout << "MIN Y: " << minY << "\nMAX Y: " << maxY << "\n\n";
	cout << "MIN Z: " << minZ << "\nMAX Z: " << maxZ << "\n\n";
	cout << "TOTAL FACETS: " << total << "\n";

}

/**
 * This function parses through an input file and calls printAndCheck
 * @param inFile : the file to be parsed in a string format
 */
void parseFile(string inFile){
	ifstream myFile;
	myFile.open(inFile);

		if(!myFile){
			cerr << "\n**Unable to open file " << inFile << "**\n**File may be missing, incorrect format, or corrupted**\n\n";
			validFile = false;
		}
		else{

			validFile = true;

			string holder;
			int vertT = 0;
			bool vertComplete = false;

			//as long as there is more in the file
			while(getline(myFile, holder, ' ')){
				//cout << holder << "\n\r";
				if(!holder.compare("outer")){
					total++;
				}
				else if(!holder.compare("vertex")){
					string vertX;
					getline(myFile, vertX, ' ');
					getline(myFile, vertX, ' ');
					getline(myFile, vertX, ' ');
					xFlo = stof(vertX);
					string vertY;
					getline(myFile, vertY, ' ');
					yFlo = stof(vertY);
					string vertZ;
					getline(myFile, vertZ);
					zFlo = stof(vertZ);
					vertT++;

					if(vertT == 3){
						vertComplete = true;
					}

					if(!initialized){
						maxX = xFlo;
						minX = xFlo;
						maxY = yFlo;
						minY = yFlo;
						maxZ = zFlo;
						minZ = zFlo;
						initialized = true;
					}
				}

				if(vertComplete){
					printAndCheck();
					vertT = 0;
					vertComplete = false;
				}
		}

		myFile.close();
		}
}

/**
 * main funcion - executes complete file read and console output
 * @param argc : number of arguments passed
 * @param argv : array of arguments passed
 */
int main (int argc, char *argv[]){

	if(argc == 2){
		parseFile(argv[1]);

		if(validFile){
			minMax();
		}
	}
	else{
		cerr << "\n**      Invalid program arguments!      **\n**Please use a valid .stl file as input!**\n\n";
	}
	return 0;
}




