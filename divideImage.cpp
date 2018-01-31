#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

if(argc != 3){
	cout<<"program needs image path and destination path(to save result) as command line argument";
	cout<< argc;
	}

string destinationPath = argv[2];

Mat image;

image = imread(argv[1],1);

if(image.empty())
{
cout << "Could not open or find the image" << std::endl ;
return -1;
}


//namedWindow("Image", CV_WINDOW_AUTOSIZE );
//imshow("Image", image);


   // get the image data
 int height = image.rows;
 int width = image.cols;

//get the rect to crop the image
 cv::Rect roi;
 roi.x = 0;
 roi.y = 0;
 roi.width = width/2 ;
 roi.height = height;

 printf("Processing a %dx%d image\n",height,width);


//crop original image into its half
Mat crop = image(roi);

//flip the cropped image
Mat mirror;               
flip(crop, mirror, 1); 

// final image is the result of concatenation between cropped image and flipped cropped image
Mat FinalImage;

hconcat(crop,mirror,FinalImage);

//imshow("mirror", FinalImage);

//save final image
imwrite(destinationPath ,FinalImage);


//waitKey(0);
return 0;
}