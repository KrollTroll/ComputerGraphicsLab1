/*
 * STLReader.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: ckroll
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int maxX;
int minX;
int maxY;
int minY;
int maxZ;
int minZ;
int total;

float xFlo;
float yFlo;
float zFlo;

/**
 * This function prints to the console as well as checks min/max values
 * @return : nothing, not necessary for this method
 */
int printAndCheck(){

	if(maxX == NULL || xFlo > maxX){
		maxX = xFlo;
	}

	if(minX == NULL || xFlo < minX){
		minX = xFlo;
	}

	if(maxY == NULL || yFlo > maxY){
		maxY = yFlo;
	}

	if(minY == NULL || yFlo < minY){
		minY = yFlo;
	}

	if(maxZ == NULL || zFlo > maxZ){
		maxZ = zFlo;
	}

	if(minZ == NULL){
		minZ = xFlo;
	}

	return 0;
}

/**
 * This function parses through an input file and calls printAndCheck
 * @param inFile : the file to be parsed in a string format
 * @return : 0 upon completion
 */
int parseFile(string inFile){
	ifstream myFile;
	myFile.open(inFile);

		if(!myFile){
			cerr << "Unable to open file " << inFile;
			//loop back to the top at this point
		}

		string holder;
		//as long as the input line is not "endsolid"
		while(!holder.compare("endsolid")){
			//read in a line from the file
			getline(myFile, holder);
			//if entering an outer loop space
			if(holder.compare("outer loop")){
				//TODO: Scan one line, parse three digits, print to terminal
				string dummy;
				string vertX;
				string vertY;
				string vertZ;
				for (int i = 0; i < 3; i++){
					//get words/number with space delimiter
					getline(myFile, dummy, ' ');
					getline(myFile, vertX, ' ');
					getline(myFile, vertY, ' ');
					//last number should be new line delimited
					getline(myFile, vertZ);

					xFlo = stof(vertX);
					yFlo = stof(vertY);
					zFlo = stof(vertZ);

					printAndCheck();

				}
					//TODO: may want to make a separate function for this - easier
			}
			//increment total number of facets
			else if(holder.compare("endfacet")){
				total++;
			}
		}

		//close file - memory management.
		myFile.close();
		return 0;
}

/**
 * main funcion - executes complete file read and console output
 * @param argc : number of arguments passed
 * @param argv : array of arguments passed
 */
int main (int argc, char *argv[]){

	string greeting = "Input file to be parsed:";
	string fileToOpen;

	cout << greeting;
	cin >> fileToOpen;

	parseFile(fileToOpen);

}




