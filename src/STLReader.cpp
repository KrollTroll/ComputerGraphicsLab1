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
int total = 0;

float xFlo;
float yFlo;
float zFlo;

/**
 * This function prints to the console as well as checks min/max values
 * @return : nothing, not necessary for this method
 */
int printAndCheck(){

	//This upcoming large section is the check portion
	if(maxX == 0 || xFlo > maxX){
		maxX = xFlo;
	}
	if(minX == 0 || xFlo < minX){
		minX = xFlo;
	}
	if(maxY == 0 || yFlo > maxY){
		maxY = yFlo;
	}
	if(minY == 0 || yFlo < minY){
		minY = yFlo;
	}
	if(maxZ == 0 || zFlo > maxZ){
		maxZ = zFlo;
	}
	if(minZ == 0 || zFlo < maxZ){
		minZ = xFlo;
	}

	//This block is the print block
	cout << "Facet " << total << ": vertX " << xFlo << ", vertY " << yFlo << ", vertZ " << zFlo << "\n\r";
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
			cerr << "Unable to open file " << inFile << "\n\r";
			//loop back to the top at this point
		}
		else{

		string holder;
		string name;
		getline(myFile, name, ' ');
		getline(myFile, name);
		cout << "name:" << name << "\n\r";

		//as long as the input line is not "endsolid"
		while(getline(myFile, holder, ' ')){
			cout << holder << "\n\r";
			if(!holder.compare("outer")){
				total++;
			}
		}

		myFile.close();
		cout << "Total facets: " << total << "\n\r";
		}
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
	cout << "Made it past parseFile\n\r";
}




