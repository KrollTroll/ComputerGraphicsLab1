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
	cout << "Facet " << total << ": vertX = " << xFlo << ", vertY = " << yFlo << ", vertZ = " << zFlo << "\n";
	return 0;
}

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
 * @return : 0 upon completion
 */
int parseFile(string inFile){
	ifstream myFile;
	myFile.open(inFile);

		if(!myFile){
			cerr << "Unable to open file " << inFile << "\n";
			//loop back to the top at this point
		}
		else{

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
				}

				if(vertComplete){
					printAndCheck();
					vertT = 0;
					vertComplete = false;
				}
		}

		myFile.close();
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

	minMax();
}




