#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;

static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program shows how to write video files."                                   << endl
        << "You can extract the R or G or B color channel of the input video."              << endl
        << "Usage:"                                                                         << endl
        << "./video-write inputvideoName [ R | G | B] [Y | N]"                              << endl
        << "------------------------------------------------------------------------------" << endl
        << endl;
}

int main(int argc, char *argv[])
{
    

    if (argc != 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    const string source      = argv[1];           // the source file name
    const string destinationVideo = argv[2];                // the output video

    VideoCapture inputVideo(source);              // Open input
    if (!inputVideo.isOpened())
    {
        cout  << "Could not open the input video: " << source << endl;
        return -1;
    }

    string::size_type pAt = source.find_last_of('.');                  // Find extension point
    const string NAME = destinationVideo;   // Form the new name with container
    int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form

    // Transform from int to char via Bitwise operators
    char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};

    Size S = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH)/2,    // Acquire input size
                  (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));

    VideoWriter outputVideo;                                        // Open the output
    
    outputVideo.open(NAME, ex, inputVideo.get(CV_CAP_PROP_FPS), S, true);

    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << source << endl;
        return -1;
    }

    cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    cout << "Input codec type: " << EXT << endl;

    
    Mat src, res;

    for(;;) //Show the image captured in the window and repeat
    {
        inputVideo >> src;              // read
        if (src.empty()) break;         // check if at end


        // get the image data
        int height = src.rows;
        int width = src.cols;

        //get the rect to crop the image
        cv::Rect roi; //(Rect.x,Rect.y) is (column,row)
        roi.x = 0;
        roi.y = 0;
        roi.width = width/2 ;
        roi.height = height;

        
        res = src(roi);

       //outputVideo.write(res); //save or
       outputVideo << res;
    }

    cout << "Finished writing" << endl;
    return 0;
}