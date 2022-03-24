#include <iostream>
#include <fstream>
#include "Image.h"
#include <vector>
using namespace std;

bool tester(vector<Pixel>& newImagePixels, string fileName); //used to test the results against the examples 
void taskOne(); //runs the code for task one
void taskTwo(); //runs the code for task two
void taskThree(); //runs the code for task three
void taskFour(); //runs the code for task four
void taskFive(); //runs the code for task five
void taskSix(); //runs the code for task six
void taskSeven(); //runs the code for task seven
void taskEight(); //runs the code for task eight
void taskNine(); //runs the code for task nine
void taskTen(); //runs the code for task ten
void extraCredit(); //runs the code for the extra credit portion 

int main() {

	taskOne(); //calls the methods and runs every task 
	taskTwo();
	taskThree();
	taskFour();
	taskFive();
	taskSix();
	taskSeven();
	taskEight();
	taskNine();
	taskTen();
	extraCredit(); //runs the extra credit
	cout << "All tasks have been completed!" << endl; 

	return 0;
};

bool tester(vector<Pixel>& newImagePixels, string fileName) { //takes in an array of pixels and the name of the file to compare what image has been created with the example to make sure the images are identical
	ifstream tempFile; //create a temporary file
	tempFile.open(fileName, ios_base::binary); //open a file to read from
	Header tempHeader; //creates a header 
	tempHeader.loadHeader(tempHeader, tempFile); //reads the header data
	vector<Pixel> tempPixels; //creates a pixel array for this image
	Image tempImage(tempHeader, tempPixels); //creates an image object
	tempImage.readImage(tempFile, tempPixels); //reads and gets all the image pixels from the example

	if (tempImage.is_same(newImagePixels, tempPixels)) { //uses the "is_same()" function to see if a grouping of pixels is the same in an image
		return true; 
	}
	else {
		return false; //if the images are not the same, return false 
	}

}

void taskOne() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/layer1.tga", ios_base::binary); //opens the top layer file

	ifstream bottomLayer; //creates the file that will be the bottom layer 
	bottomLayer.open("input/pattern1.tga", ios_base::binary); //opens the bottom layer file
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 

	Header bottomHeader;
	bottomHeader.loadHeader(bottomHeader, bottomLayer); //loads the data for the bottom layer
	vector<Pixel> bottomLayerPixels; //vector to represent the bottom layer's pixels 
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);

	Image bottomImage(bottomHeader, bottomLayerPixels); //creates an image object and stores it for further operations 
	bottomImage.readImage(bottomLayer, bottomLayerPixels);
	/*==============================================*/

	vector<Pixel> newImagePixels; //a vector storing all of the pixels for the new combines image 
	Image finalImage(topHeader, newImagePixels); //creates a new image object
	newImagePixels = finalImage.multiply(topLayerPixels, bottomLayerPixels); //gets a vector of pixels for the new image

	ofstream newFile; //used to represent the output file
	newFile.open("output/part1.tga", ios_base::binary);

	finalImage.writeImage(newFile, topHeader, newImagePixels); //writes to the newfile the image that has been multiplied together 

}

void taskTwo() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/layer2.tga", ios_base::binary); //opens the top layer file

	ifstream bottomLayer; //creates the file that will be the bottom layer 
	bottomLayer.open("input/car.tga", ios_base::binary); //opens the bottom layer file
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 

	Header bottomHeader;
	bottomHeader.loadHeader(bottomHeader, bottomLayer); //loads the data for the bottom layer
	vector<Pixel> bottomLayerPixels; //vector to represent the bottom layer's pixels 
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);

	Image bottomImage(bottomHeader, bottomLayerPixels); //creates an image object and stores it for further operations 
	bottomImage.readImage(bottomLayer, bottomLayerPixels);
	/*==============================================*/

	vector<Pixel> newImagePixels; //a vector storing all of the pixels for the new combines image 
	Image finalImage(topHeader, newImagePixels); //creates a new image object
	newImagePixels = finalImage.subtract(topLayerPixels, bottomLayerPixels);

	ofstream newFile; //used to represent the output file
	newFile.open("output/part2.tga", ios_base::binary);

	finalImage.writeImage(newFile, topHeader, newImagePixels); //writes to the newfile the image that has been multiplied together

}

void taskThree() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/layer1.tga", ios_base::binary); //opens the top layer file

	ifstream bottomLayer; //creates the file that will be the bottom layer 
	bottomLayer.open("input/pattern2.tga", ios_base::binary); //opens the bottom layer file

	ifstream screenLayer;
	screenLayer.open("input/text.tga", ios_base::binary);
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 

	Header bottomHeader;
	bottomHeader.loadHeader(bottomHeader, bottomLayer); //loads the data for the bottom layer
	vector<Pixel> bottomLayerPixels; //vector to represent the bottom layer's pixels 

	Header screenHeader;
	screenHeader.loadHeader(screenHeader, screenLayer);
	vector<Pixel> screenPixels;
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);

	Image bottomImage(bottomHeader, bottomLayerPixels); //creates an image object and stores it for further operations 
	bottomImage.readImage(bottomLayer, bottomLayerPixels);

	Image screenImage(screenHeader, screenPixels);
	screenImage.readImage(screenLayer, screenPixels);
	/*==============================================*/

	vector<Pixel> newImagePixels; //a vector storing all of the pixels for the new combines image 
	Image finalImage(topHeader, newImagePixels); //creates a new image object
	newImagePixels = finalImage.multiply(topLayerPixels, bottomLayerPixels);
	newImagePixels = finalImage.screen(screenPixels, newImagePixels);


	ofstream newFile; //used to represent the output file
	newFile.open("output/part3.tga", ios_base::binary);

	finalImage.writeImage(newFile, topHeader, newImagePixels); //writes to the newfile the image that has been multiplied together

}

void taskFour() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/layer2.tga", ios_base::binary); //opens the top layer file

	ifstream bottomLayer; //creates the file that will be the bottom layer 
	bottomLayer.open("input/circles.tga", ios_base::binary); //opens the bottom layer file

	ifstream screenLayer;
	screenLayer.open("input/pattern2.tga", ios_base::binary);
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 

	Header bottomHeader;
	bottomHeader.loadHeader(bottomHeader, bottomLayer); //loads the data for the bottom layer
	vector<Pixel> bottomLayerPixels; //vector to represent the bottom layer's pixels 

	Header screenHeader;
	screenHeader.loadHeader(screenHeader, screenLayer);
	vector<Pixel> screenPixels;
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);

	Image bottomImage(bottomHeader, bottomLayerPixels); //creates an image object and stores it for further operations 
	bottomImage.readImage(bottomLayer, bottomLayerPixels);

	Image screenImage(screenHeader, screenPixels);
	screenImage.readImage(screenLayer, screenPixels);
	/*==============================================*/

	vector<Pixel> newImagePixels; //a vector storing all of the pixels for the new combines image 
	Image finalImage(topHeader, newImagePixels); //creates a new image object
	newImagePixels = finalImage.subtract(screenPixels, topLayerPixels, bottomLayerPixels);


	ofstream newFile; //used to represent the output file
	newFile.open("output/part4.tga", ios_base::binary);

	finalImage.writeImage(newFile, topHeader, newImagePixels); //writes to the newfile the image that has been multiplied together

}

void taskFive() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/layer1.tga", ios_base::binary); //opens the top layer file

	ifstream bottomLayer; //creates the file that will be the bottom layer 
	bottomLayer.open("input/pattern1.tga", ios_base::binary); //opens the bottom layer file
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 

	Header bottomHeader;
	bottomHeader.loadHeader(bottomHeader, bottomLayer); //loads the data for the bottom layer
	vector<Pixel> bottomLayerPixels; //vector to represent the bottom layer's pixels 
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);

	Image bottomImage(bottomHeader, bottomLayerPixels); //creates an image object and stores it for further operations 
	bottomImage.readImage(bottomLayer, bottomLayerPixels);
	/*==============================================*/

	vector<Pixel> newImagePixels; //a vector storing all of the pixels for the new combines image 
	Image finalImage(topHeader, newImagePixels); //creates a new image object
	newImagePixels = finalImage.overlay(topLayerPixels, bottomLayerPixels);

	ofstream newFile; //used to represent the output file
	newFile.open("output/part5.tga", ios_base::binary);

	finalImage.writeImage(newFile, topHeader, newImagePixels); //writes to the newfile the image that has been multiplied together

}

void taskSix() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/car.tga", ios_base::binary); //opens the top layer file
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);
	/*==============================================*/

	Image finalImage(topHeader, topLayerPixels); //creates a new image object
	finalImage.addChannel(topLayerPixels, 200, 'g'); //adds 200 to the green channel

	ofstream newFile; //used to represent the output file
	newFile.open("output/part6.tga", ios_base::binary);

	finalImage.writeImage(newFile, topHeader, topLayerPixels); //writes to the newfile the image that has been multiplied together

}

void taskSeven() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/car.tga", ios_base::binary); //opens the top layer file
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);
	/*==============================================*/

	Image finalImage(topHeader, topLayerPixels); //creates a new image object
	finalImage.scale(topLayerPixels, 4, 'r'); //scales red channel by 4
	finalImage.scale(topLayerPixels, 0, 'b'); //scales blue channel by 0, making there be no blue

	ofstream newFile; //used to represent the output file
	newFile.open("output/part7.tga", ios_base::binary);

	finalImage.writeImage(newFile, topHeader, topLayerPixels); //writes to the newfile the image that has been multiplied together

}

void taskEight() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/car.tga", ios_base::binary); //opens the top layer file
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 
	vector<Pixel> secondLayerPixels; //vector to represent the top layer's pixels
	vector<Pixel> thirdLayerPixels; //vector to represent the top layer's pixels
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);
	secondLayerPixels = topLayerPixels; //makes a copy for the green image
	thirdLayerPixels = topLayerPixels; //makes a copy for the blue image
	/*==============================================*/

	/*================WRITE RED================*/
	Image redImage(topHeader, topLayerPixels); //creates a new image object
	redImage.oneColor(topLayerPixels, 'r'); //makes every channel the red pixel

	ofstream redFile; //used to represent the output file
	redFile.open("output/part8_r.tga", ios_base::binary);

	redImage.writeImage(redFile, topHeader, topLayerPixels); //writes to the newfile the image that has been multiplied together
	/*==========================================*/

	/*================WRITE GREEN================*/
	Image greenImage(topHeader, secondLayerPixels);
	greenImage.oneColor(secondLayerPixels, 'g'); //makes every channel the green pixel

	ofstream greenFile; //used to represent the output file
	greenFile.open("output/part8_g.tga", ios_base::binary);

	greenImage.writeImage(greenFile, topHeader, secondLayerPixels); //writes to the newfile the image that has been multiplied together
	/*==========================================*/

	/*================WRITE BLUE================*/
	Image blueImage(topHeader, thirdLayerPixels);
	blueImage.oneColor(thirdLayerPixels, 'b'); //makes every channel the blue pixel

	ofstream blueFile; //used to represent the output file
	blueFile.open("output/part8_b.tga", ios_base::binary);

	blueImage.writeImage(blueFile, topHeader, thirdLayerPixels); //writes to the newfile the image that has been multiplied together
	/*==========================================*/
}

void taskNine() {
	/*================IMAGE LOADING================*/
	ifstream redFile; //opens the file with the red channel
	redFile.open("input/layer_red.tga", ios_base::binary);

	ifstream greenFile; //opens the file with the green channel 
	greenFile.open("input/layer_green.tga", ios_base::binary);

	ifstream blueFile; //opens the file with the blue channel
	blueFile.open("input/layer_blue.tga", ios_base::binary);
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header redHeader; //loads the header data for the top layer 
	redHeader.loadHeader(redHeader, redFile);
	vector<Pixel> redLayerPixels; //vector to represent the top layer's pixels

	Header greenHeader;
	greenHeader.loadHeader(greenHeader, greenFile);
	vector<Pixel> greenLayerPixels; //vector to represent the top layer's pixels

	Header blueHeader;
	blueHeader.loadHeader(blueHeader, blueFile);
	vector<Pixel> blueLayerPixels; //vector to represent the top layer's pixels
	/*==============================================*/

	/*================IMAGE READING================*/
	Image redImage(redHeader, redLayerPixels); //creates an image object and reads the data and stores it
	redImage.readImage(redFile, redLayerPixels);

	Image blueImage(blueHeader, blueLayerPixels); //creates an image object and stores it for further operations 
	blueImage.readImage(blueFile, blueLayerPixels);

	Image greenImage(greenHeader, greenLayerPixels); //creates an image object and stores it for further operations 
	greenImage.readImage(greenFile, greenLayerPixels);
	/*==============================================*/

	vector<Pixel> finalPixels; //creates a vector for the final pixels of the final image
	Image finalImage(redHeader, finalPixels); //creates the final image
	finalPixels = finalImage.combineChannels(redLayerPixels, greenLayerPixels, blueLayerPixels); //sets the vector equal to what will be returned from this method 

	ofstream newFile; //used to represent the output file

	newFile.open("output/part9.tga", ios_base::binary); //outputs the result to the proper file

	finalImage.writeImage(newFile, redHeader, finalPixels); //writes to the newfile the image that has been multiplied together
}

void taskTen() {
	/*================IMAGE LOADING================*/
	ifstream topLayer; //creates the file that will be the top layer
	topLayer.open("input/text2.tga", ios_base::binary); //opens the top layer file
	/*=============================================*/

	/*================HEADER LOADING================*/
	Header topHeader; //loads the header data for the top layer 
	topHeader.loadHeader(topHeader, topLayer);
	vector<Pixel> topLayerPixels; //vector to represent the top layer's pixels 
	/*==============================================*/

	/*================IMAGE READING================*/
	Image topImage(topHeader, topLayerPixels); //creates an image object and reads the data and stores it
	topImage.readImage(topLayer, topLayerPixels);
	/*==============================================*/

	Image finalImage(topHeader, topLayerPixels); //creates a new image object

	ofstream newFile; //used to represent the output file
	newFile.open("output/part10.tga", ios_base::binary);

	finalImage.writeUpsideDown(newFile, topHeader, topLayerPixels); //writes to the newfile the image that has been multiplied together

}

void extraCredit() {
	/*================IMAGE LOADING================*/
	ifstream bottomLeft; 
	bottomLeft.open("input/text.tga", ios_base::binary); //loads all of the input files to be used to form the grand image

	ifstream bottomRight; 
	bottomRight.open("input/pattern1.tga", ios_base::binary); 
	
	ifstream topLeft; 
	topLeft.open("input/car.tga", ios_base::binary);
	
	ifstream topRight; 
	topRight.open("input/circles.tga", ios_base::binary);
	/*==============================================*/
	
	/*================HEADER LOADING================*/
	Header bottomLeftHeader; 
	bottomLeftHeader.loadHeader(bottomLeftHeader, bottomLeft); //loads the bottom left header 
	vector<Pixel> bottomLeftPixels;
	
	Header bottomRightHeader; 
	bottomRightHeader.loadHeader(bottomRightHeader, bottomRight); //loads the bottom left header 
	vector<Pixel> bottomRightPixels;
	
	Header topLeftHeader; 
	topLeftHeader.loadHeader(topLeftHeader, topLeft); //loads the top left header 
	vector<Pixel> topLeftPixels;
	
	Header topRightHeader;
	topRightHeader.loadHeader(topRightHeader, topRight); //loads the top right header
	vector<Pixel> topRightPixels; 
	/*==============================================*/
	
	/*================IMAGE READING================*/
	Image bottomLeftImage(bottomLeftHeader, bottomLeftPixels); //creates an image object for each file and connects a vector for all of their pixels to them and loads them
	bottomLeftImage.readImage(bottomLeft, bottomLeftPixels);
	
	Image bottomRightImage(bottomRightHeader, bottomRightPixels);
	bottomRightImage.readImage(bottomRight, bottomRightPixels); 
	
	Image topLeftImage(topLeftHeader, topLeftPixels); 
	topLeftImage.readImage(topLeft, topLeftPixels); 
	
	Image topRightImage(topRightHeader, topRightPixels); 
	topRightImage.readImage(topRight, topRightPixels); 
	/*==============================================*/
	
	Header newFileHeader = bottomLeftHeader; //creates a header that represents the one for the new image 
	vector<Pixel> newImagePixels; //creates an array that represents all of the pixels in the new image
	newFileHeader.width = bottomLeftHeader.width + bottomRightHeader.width; //adjusts the width of the new image
	newFileHeader.height = bottomLeftHeader.height + bottomRightHeader.height; //adjusts the height of the new image

	int smallImageWidth = bottomLeftHeader.width; //represents the width of one of the small images
	int smallImageHeight = bottomLeftHeader.height; //represents the height of one of the small images

	int elevator = 0; //used to move the image up a row every time

	for (int j = 0; j < smallImageHeight; j++) { //loads the bottom two images' pixels into the total array
		for (int i = 0; i < smallImageWidth; i++) { //goes through until hitting the end of the row on the right side when the width max is reached 
			Pixel smallCurrentPixel = bottomLeftPixels.at(i + elevator); //adds the pixel in the current position + if it is in any row above the first one

			newImagePixels.push_back(smallCurrentPixel); //adds these pixels as they go along
		}
		for (int i = 0; i < smallImageWidth; i++) { //goes through until hitting the end of the row on the right side when the width max is reached 
			Pixel smallCurrentPixel = bottomRightPixels.at(i + elevator); //adds the pixel in the current position + if it is in any row above the first one

			newImagePixels.push_back(smallCurrentPixel); //adds these pixels to the full image as they go along
		}
		elevator += smallImageWidth; //once complete with a full row, increment the elevator for the total number of pixels in the bottom row of a small image to get the next one
	}

	elevator = 0; 
	
	for (int j = 0; j < smallImageHeight; j++) { //loads the top two images' pixels into the total array
		for (int i = 0; i < smallImageWidth; i++) { //goes through until hitting the end of the row on the right side when the width max is reached
			Pixel smallCurrentPixel = topLeftPixels.at(i + elevator); //adds the pixel in the current position + if it is in any row above the first one

			newImagePixels.push_back(smallCurrentPixel); //adds these pixels as they go along
		}
		for (int i = 0; i < smallImageWidth; i++) { //goes through until hitting the end of the row on the right side when the width max is reached 
			Pixel smallCurrentPixel = topRightPixels.at(i + elevator); //adds the pixel in the current position + if it is in any row above the first one

			newImagePixels.push_back(smallCurrentPixel); //adds these pixels to the full image as they go along
		}
		elevator += smallImageWidth; //once complete with a full row, increment the elevator for the total number of pixels in the bottom row of a small image to get the next one
	}

	Image finalImage(newFileHeader, newImagePixels); //creates the final image

	ofstream newFile; //used to represent the output file
	newFile.open("output/extracredit.tga", ios_base::binary); //opens/creates an output file to write to

	finalImage.writeImage(newFile, newFileHeader, newImagePixels); //writes to the newfile the image that has been combined

}