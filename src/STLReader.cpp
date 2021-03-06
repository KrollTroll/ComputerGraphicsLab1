/*
 * STLReader.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: ckroll
 *
 *      This is a lab for computer graphics that parses STL files
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

bool initialized = false;
bool validFile = false;

/**
 * This function checks min/max values
 */
void checkMax(float xFlo, float yFlo, float zFlo){

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

	if(zFlo > maxZ){
		maxZ = zFlo;
	}
	else if(zFlo < maxZ){
		minZ = xFlo;
	}
}

/**
 * This method prints the min/max
 */
void printVert(float xFlo, float yFlo, float zFlo, int vertT){
	//This block is the print block
	cout << "Facet " << total << " Vertex " << vertT;
	cout << ": vertX=" << setw(8) << xFlo;
	cout << ",\tvertY=" << setw(8) << yFlo;
	cout << ",   vertZ=" << zFlo << "\n";
}

/**
 * prints out the minimum and maximum vertices for the file
 */
void printMinMax(){
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
	float xFlo;
	float yFlo;
	float zFlo;
	int vertT = 0;
	ifstream myFile;
	myFile.open(inFile);

		//Print error if file does not open for whatever reason
		if(!myFile){
			cerr << "\n**Unable to open file " << inFile;
			cout << "**\n**File may be missing, incorrect format, or corrupted**\n\n";
			validFile = false;
		}
		//If the file is valid
		else{
			//boolean switch for later logic
			validFile = true;

			string holder;
			bool vertComplete = false;

			//as long as there is more in the file
			while(getline(myFile, holder, ' ')){
				//if entering an outer loop
				if(!holder.compare("outer")){
					//increment the total number of facets
					total++;
				}
				//if entering a vertex range
				if(!holder.compare("vertex")){
					string vertX;
					getline(myFile, vertX, ' ');
					while(!vertX.compare("")){
						getline(myFile, vertX, ' ');
					}
					xFlo = stof(vertX);
					string vertY;
					getline(myFile, vertY, ' ');
					while(!vertY.compare("")){
						getline(myFile, vertY, ' ');
					}
					yFlo = stof(vertY);
					string vertZ;
					getline(myFile, vertZ, ' ');
					while(!vertZ.compare("")){
						getline(myFile, vertZ, ' ');
					}
					zFlo = stof(vertZ);

					//it's screwing up here, this is causing it to only print every third
					vertT++;
					vertComplete = true;

					//initialize min and max if they haven't been
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

				//output once all vertices found
				if(vertComplete){
					checkMax(xFlo, yFlo, zFlo);
					printVert(xFlo, yFlo, zFlo, vertT);
					vertComplete = false;
					if(vertT == 3){
						vertT = 0;
					}
				}
		}

		//close file to save memory
		myFile.close();
		}
}

/**
 * main funcion - executes complete file read and console output
 * @param argc : number of arguments passed
 * @param argv : array of arguments passed
 */
int main (int argc, char *argv[]){

	//as long as two arguments are entered
	if(argc == 2){
		//pass in second argument as file name
		parseFile(argv[1]);

		//if the file is valid
		if(validFile){
			//output min/max once done parsing
			printMinMax();
		}
	}
	//otherwise print error
	else{
		cerr << "\n**      Invalid program arguments!      **";
		cout << "\n**Please use a valid .stl file as input!**\n\n";
	}
	return 0;
}




