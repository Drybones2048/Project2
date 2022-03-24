#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std; 

struct Pixel {
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;
};

struct Header { 
	char idLength; //variables that represent the data that is given in the header file
	char colorMapType;
	char dataTypeCode; 
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth; 
	short xOrigin; 
	short yOrigin; 
	short width; 
	short height; 
	char bitsPerPixel;
	char imageDescriptor; 

	Header() { //when first created, the header object has no values, and this constructor will reflect that fact
		idLength = '\0';
		colorMapType = '\0';
		dataTypeCode = '\0'; 
		colorMapOrigin = 0;
		colorMapLength = 0; 
		colorMapDepth = '\0';
		xOrigin = 0;
		yOrigin = 0; 
		width = 0; 
		height = 0;
		bitsPerPixel = '\0'; 
		imageDescriptor = '\0';
	}

	bool loadHeader(Header& headerObject, ifstream& file) {
		try { //uses a try catch so that if the file loading process errors in any way, it prints the that it did not work properly and returns false
			file.read((char*)&headerObject.idLength, sizeof(headerObject.idLength)); //goes through the file and reads each piece of data that is given in the header 
			file.read((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
			file.read((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
			file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
			file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
			file.read((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
			file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
			file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
			file.read((char*)&headerObject.width, sizeof(headerObject.width));
			file.read((char*)&headerObject.height, sizeof(headerObject.height));
			file.read((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
			file.read((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));


			return true; //if the file loading worked properly, then true is returned
		}
		catch (exception e) {
			cout << "\nFile loading was not completed!\n" << endl; //if there is an error in the file loading process, it says so in a print statement
			return false; //returns false that the loading did not work properly
		}
		
	}
};

struct Image {

	Header headerObject; //used to store the header data for an image
	vector<Pixel> allPixels; //vector used to store the pixels within an image
	int imageSize;

	Image(Header& headerObject, vector<Pixel>& allPixels) { //constructor used to construct the pixels and header that make up an image (no file though)
		this->headerObject = headerObject; 
		this->allPixels = allPixels; 
		imageSize = headerObject.height * headerObject.width;
	}

	void readImage(ifstream& file, vector<Pixel>& allPixels) { //used to read 
		 

		for (int i = 0; i < imageSize; i++) { //goes through every pixel of the image
			Pixel singlePixel; //creates a new pixel through each iteration


			file.read((char*)&singlePixel.blue, 1); //reads each color value in binary file, in blue, green, and red order respectively
			file.read((char*)&singlePixel.green, 1);
			file.read((char*)&singlePixel.red, 1);

			allPixels.push_back(singlePixel); //adds the pixel to the vector


		}

		file.close(); //closes the file once we are done reading from it
	}
	void writeImage(ofstream& newFile, Header& headerObject, vector<Pixel>& allPixels) {
		newFile.write((char*)&headerObject.idLength, sizeof(headerObject.idLength)); //goes through the file and writes each piece of data that is given in the header 
		newFile.write((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
		newFile.write((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
		newFile.write((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
		newFile.write((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
		newFile.write((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
		newFile.write((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
		newFile.write((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
		newFile.write((char*)&headerObject.width, sizeof(headerObject.width));
		newFile.write((char*)&headerObject.height, sizeof(headerObject.height));
		newFile.write((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
		newFile.write((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

		for (int i = 0; i < imageSize; i++) { //writes each pixel to the new file
			Pixel singlePixel = allPixels.at(i);

			newFile.write((char*)&singlePixel.blue, 1);
			newFile.write((char*)&singlePixel.green, 1);
			newFile.write((char*)&singlePixel.red, 1);
		}
	}

	vector<Pixel>& multiply(vector<Pixel>& topLayerPixels, vector<Pixel>& bottomLayerPixels) { //multipies the color values of each pixel for two images together
		
		for (int i = 0; i < imageSize; i++) {
			Pixel newPixel; //pixel that will be the new pixel from the multiplied values

			Pixel topPixel = topLayerPixels.at(i); //current pixel from the top image
			Pixel bottomPixel = bottomLayerPixels.at(i); //current pixel from the bottom image
			
			//adds the values together and assigns them to the current pixel value in the new image	
			newPixel.blue = (int) (((topPixel.blue) * (bottomPixel.blue)) / 255.0f + 0.5f); //assigns the new pixel the value of the pixel in both images 
			newPixel.green = (int) (((topPixel.green) * (bottomPixel.green)) / 255.0f + 0.5f);
			newPixel.red = (int) (((topPixel.red) * (bottomPixel.red)) / 255.0f + 0.5f);

			allPixels.push_back(newPixel); //adds the new pixel to the new vector 
		}
		return allPixels; //recturns the vector with all of the image data 
	}

	vector<Pixel>& subtract(vector<Pixel>& topLayerPixels, vector<Pixel>& bottomLayerPixels) { //subtracts pixels when two images are sent in 
		for (int i = 0; i < imageSize; i++) {
			Pixel newPixel; //pixel that will be the new pixel from the multiplied values

			Pixel topPixel = topLayerPixels.at(i); //current pixel from the top image
			Pixel bottomPixel = bottomLayerPixels.at(i); //current pixel from the bottom image

			//subtracts the pixel value of the top image from the bottom image, using the clamp utility function to make sure it cannot overflow or underflow 	
			newPixel.blue = clamp((bottomPixel.blue) - (topPixel.blue)); 
			newPixel.green = clamp((bottomPixel.green) - (topPixel.green));
			newPixel.red = clamp((bottomPixel.red) - (topPixel.red));

			allPixels.push_back(newPixel); //adds the new pixel to the new vector 
		}
		return allPixels; //recturns the vector with all of the image data
	}

	vector<Pixel>& subtract(vector<Pixel>& screenPixels, vector<Pixel>& topLayerPixels, vector<Pixel>& bottomLayerPixels) { //subtracts pixels when two images are sent in, overrided version for task 4 when the pixels have already been added to the vector 
		vector<Pixel> multipliedPixels = multiply(topLayerPixels, bottomLayerPixels); //represents the base layer and calls the multiply function
		
		for (int i = 0; i < imageSize; i++) {
			Pixel newPixel; //pixel that will be the new pixel from the multiplied values

			Pixel topPixel = screenPixels.at(i); //current pixel from the top image
			Pixel bottomPixel = multipliedPixels.at(i); //current pixel from the bottom image

			//subtracts the pixel value of the top image from the bottom image, using the clamp utility function to make sure it cannot overflow or underflow 	
			newPixel.blue = clamp((bottomPixel.blue) - (topPixel.blue));
			newPixel.green = clamp((bottomPixel.green) - (topPixel.green));
			newPixel.red = clamp((bottomPixel.red) - (topPixel.red));

			allPixels.at(i) = newPixel; //changes the current pixel to the new one because the pixels have already been added to the vector
		}
		return allPixels; //recturns the vector with all of the image data
	}

	vector<Pixel>& screen(vector<Pixel>& topLayerPixels, vector<Pixel>& bottomLayerPixels) {
		for (int i = 0; i < imageSize; i++) {
			//subtracts the pixel value of the top image from the bottom image, using the clamp utility function to make sure it cannot overflow or underflow 	
	
			Pixel basePixel = bottomLayerPixels.at(i); //pixel representing the bottom layer 
			Pixel textPixel = topLayerPixels.at(i);  //pixel representing the overlay text
			
			Pixel newPixel; //pixel representing the new combined image
			
			newPixel.blue = ((1.0f - (1.0f - (textPixel.blue) / 255.0f) * (1.0f - (basePixel.blue)/255.0f)) * 255.0f + 0.5f); //does the math needed to screen an image while clamped to avoid overflow
			newPixel.green = ((1.0f - (1.0f - (textPixel.green) / 255.0f) * (1.0f - (basePixel.green) / 255.0f)) * 255.0f + 0.5f);
			newPixel.red = ((1.0f - (1.0f - (textPixel.red) / 255.0f) * (1.0f - (basePixel.red) / 255.0f)) * 255.0f + 0.5f);
			
			allPixels.at(i) = newPixel; //changed the combined vector to the new pixel

		}
		return allPixels; //recturns the vector with all of the image data
	}

	vector<Pixel>& overlay(vector<Pixel>& topLayerPixels, vector<Pixel>& bottomLayerPixels) { //NOT FUNCTIONAL overlays image 2 over image 1
		
		for (int i = 0; i < imageSize; i++) { 	

			Pixel bottomPixel = bottomLayerPixels.at(i); //pixel representing the bottom layer 
			Pixel topPixel = topLayerPixels.at(i);  //pixel representing the overlay text

			Pixel newPixel; //pixel representing the new combined image

			if ((bottomPixel.blue / 255.0f) > 0.5f) { //checks to see if the bottom pixel value is greater than 0.5
				newPixel.blue = ((1.0f - (2.0f * (1.0f - (topPixel.blue) / 255.0f)) * (1.0f - (bottomPixel.blue) / 255.0f)) * 255.0f + 0.5f); //use the overlay formula to calculate the pixels
			}
			else {
				newPixel.blue = (2.0f * (topPixel.blue / 255.0f) * (bottomPixel.blue / 255.0f)) * 255.0f + 0.5f; //uses the overlay formula
			}

			if ((bottomPixel.green / 255.0f) > 0.5f) { //checks to see if the bottom pixel value is greater than 0.5
				newPixel.green = ((1.0f - (2.0f * (1.0f - (topPixel.green) / 255.0f)) * (1.0f - (bottomPixel.green) / 255.0f)) * 255.0f + 0.5f); //use the overlay formula to calculate the pixels
			}
			else {
				newPixel.green = (2.0f * (topPixel.green / 255.0f) * (bottomPixel.green / 255.0f)) * 255.0f + 0.5f; //uses the overlay formula
			}
			
			if ((bottomPixel.red / 255.0f) > 0.5f) { //checks to see if the red channel in the selected pixel is higher than 0.5
				newPixel.red = ((1.0f - (2.0f * (1.0f - (topPixel.red) / 255.0f)) * (1.0f - (bottomPixel.red) / 255.0f)) * 255.0f + 0.5f); //use the overlay formula to calculate the pixels
			}
			else {
				newPixel.red = (2.0f * (topPixel.red / 255.0f) * (bottomPixel.red / 255.0f)) * 255.0f + 0.5f; //uses the overlay formula 
			}
			
			allPixels.push_back(newPixel); //changed the combined vector to the new pixel

		}
		return allPixels; //recturns the vector with all of the image data
	}
	
	void addChannel(vector<Pixel>& imagePixels, int value, char color) { //used to add a value to a channel
		for (int i = 0; i < imageSize; i++) { //checks every pixel
			Pixel currentPixel = imagePixels.at(i); //pixel under investigation

			if (color == 'b') { //if we want to do operations on the blue channel, the char 'b' will be sent in
				if (currentPixel.blue + value <= 0) { //if the value sent in + the current blue pixel value is less than zero, set it to zero
					currentPixel.blue = 0; 
				}
				else if (currentPixel.blue + value >= 255) { //if the value is greater than 255, make it the max it can be
					currentPixel.blue = 255;
				}
				else {
					currentPixel.blue += value; //if the value is in the middle, add the value as normal
				}
			} else if (color == 'g') { //used to do operations on the green pixel 
				if (currentPixel.green + value <= 0) { //if the pixel goes below zero, set it at zero
					currentPixel.green = 0;
				}
				else if (currentPixel.green + value >= 255) { //if the value becomes greater than 255, set it to its max 
					currentPixel.green = 255;
				}
				else {
					currentPixel.green += value; //add the value if in the middle 
				}
			} else if (color == 'r') { //select the red channel to change
				if (currentPixel.red + value <= 0) { //sets the channel to zero if negative
					currentPixel.red = 0;
				}
				else if (currentPixel.red + value >= 255) { //sets the value to 255 if it is higher than 255 when added
					currentPixel.red = 255;
				}
				else {
					currentPixel.red += value; //adds if the value is in the middle
				}
			}

			imagePixels.at(i) = currentPixel; //sets the pixel in the vector to be this new value

		}
	}

	void scale(vector<Pixel>& imagePixels, int value, char color) {
		for (int i = 0; i < imageSize; i++) { //checks every pixel
			Pixel currentPixel = imagePixels.at(i); //pixel under investigation

			if (color == 'b') { //if we want to do operations on the blue channel, the char 'b' will be sent in
				if (currentPixel.blue * value <= 0) { //if the value sent in + the current blue pixel value is less than zero, set it to zero
					currentPixel.blue = 0;
				}
				else if (currentPixel.blue * value >= 255) { //if the value is greater than 255, make it the max it can be
					currentPixel.blue = 255;
				}
				else {
					currentPixel.blue *= value; //if the value is in the middle, add the value as normal
				}
			}
			else if (color == 'g') { //used to do operations on the green pixel 
				if (currentPixel.green * value <= 0) { //if the pixel goes below zero, set it at zero
					currentPixel.green = 0;
				}
				else if (currentPixel.green * value >= 255) { //if the value becomes greater than 255, set it to its max 
					currentPixel.green = 255;
				}
				else {
					currentPixel.green *= value; //add the value if in the middle 
				}
			}
			else if (color == 'r') { //select the red channel to change
				if (currentPixel.red * value <= 0) { //sets the channel to zero if negative
					currentPixel.red = 0;
				}
				else if (currentPixel.red * value >= 255) { //sets the value to 255 if it is higher than 255 when added
					currentPixel.red = 255;
				}
				else {
					currentPixel.red *= value; //adds if the value is in the middle
				}
			}

			imagePixels.at(i) = currentPixel; //sets the pixel in the vector to be this new value
		}
	}

	void oneColor(vector<Pixel>& imagePixels, char color) { //used to make only one color be present in an image and all other pixels have that value
		for (int i = 0; i < imageSize; i++) { //checks every pixel
			Pixel currentPixel = imagePixels.at(i); //pixel under investigation

			if (color == 'b') { //used if blue will be the only color used 
				currentPixel.green = currentPixel.blue; 
				currentPixel.red = currentPixel.blue;
			}
			else if (color == 'g') { //used if green will be the only color used
				currentPixel.blue = currentPixel.green;
				currentPixel.red = currentPixel.green;
			}
			else if (color == 'r') { //used if red will be the only color used
				currentPixel.blue = currentPixel.red; 
				currentPixel.green = currentPixel.red; 
			}

			imagePixels.at(i) = currentPixel; //sets the pixel in the vector to be this new value
		}
	}

	vector<Pixel>& combineChannels(vector<Pixel>& redPixels, vector<Pixel>& greenPixels, vector<Pixel>& bluePixels) {
		for (int i = 0; i < imageSize; i++) { //for loop to traverse every pixel
			Pixel currentPixel; //pixel at the current location
			Pixel redPixel = redPixels.at(i); //red pixel at the current location 
			Pixel greenPixel = greenPixels.at(i); //green pixel at the current location
			Pixel bluePixel = bluePixels.at(i); //blue pixel at the current location 

			currentPixel.red = redPixel.red; //sets the current pixel to be the one from the red vector
			currentPixel.green = greenPixel.green; //sets the current pixel green channel to be from the green channel 
			currentPixel.blue = bluePixel.blue; //sets the current pixel green channel to be from the blue channel

			allPixels.push_back(currentPixel); //adds the combined pixel to the vector
		}
		return allPixels; //returns the now complete vector
	}

	void writeUpsideDown(ofstream& newFile, Header& headerObject, vector<Pixel>& allPixels) {
		newFile.write((char*)&headerObject.idLength, sizeof(headerObject.idLength)); //goes through the file and writes each piece of data that is given in the header 
		newFile.write((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
		newFile.write((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
		newFile.write((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
		newFile.write((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
		newFile.write((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
		newFile.write((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
		newFile.write((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
		newFile.write((char*)&headerObject.width, sizeof(headerObject.width));
		newFile.write((char*)&headerObject.height, sizeof(headerObject.height));
		newFile.write((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
		newFile.write((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

		for (int i = imageSize - 1; i >= 0; i--) { //writes each pixel to the file in backwards order so that the image will be upside down
			Pixel singlePixel = allPixels.at(i);

			newFile.write((char*)&singlePixel.blue, 1);
			newFile.write((char*)&singlePixel.green, 1);
			newFile.write((char*)&singlePixel.red, 1);
		}
	}

	bool is_same(vector<Pixel>& firstPixels, vector<Pixel>& secondPixels) { //method to see if two images are the same by comparing pixels
		
		for (int i = 0; i < imageSize; i++) { //iterates pixel by pixel to check values
			Pixel firstPixel = firstPixels.at(i); //represents the pixel in the first image
			Pixel secondPixel = secondPixels.at(i); //represents the current pixel in the second image

			if (firstPixel.blue != secondPixel.blue || firstPixel.green != secondPixel.green || firstPixel.red != secondPixel.red) { //checks to see if the pixels are different at any point, even by one
				cout << "Not the same at Pixel #" << i + 1 << endl; //reports where the pixel is different and by how much
				cout << "With a difference of: " << endl;
				cout << "Red: " << abs(firstPixel.red - secondPixel.red) << endl; //uses absolule value method to get the raw difference in the values
				cout << "Green: " << abs(firstPixel.green - secondPixel.green) << endl;
				cout << "Blue: " << abs(firstPixel.blue - secondPixel.blue) << endl;


				return false; //returns false that the images are not the exact same
			}
		}

		return true; //returns true that the images are the same if no differences could be found
	}

	int clamp(float value) { //clamps the value to avoid overflow or underflow

		if (value > 255) { //if the value of the int is over 255 such as a number like 300, it will subtract 255 to get 45 as the proper value
			value -= 256;
		}
		else if (value < 0) { //if the value becomes negative due to underflow, negative numbers will get turned to 0
			value = 0; 
		}
		
		return value; //returns the clamped value
	}
};