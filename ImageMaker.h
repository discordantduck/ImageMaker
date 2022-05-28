//
// Assignment Created by Varick Erickson
//

#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <cmath>
#include <fstream>

// the max. width & height for the image matrix
const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 800;
// the max. color range
const int MAX_COLOR = 255;
enum COLOR { RED, GREEN, BLUE };

using namespace std;

//  Please put your pre and post comments in this file. See page 139 in the textbook.

class ImageMaker
{
public:
    // function: default constructor
    // preconditions: none
    // postconditions: width & height are set to 0, the pen's color is set to black, and the entire image matrix is set
    //                 to white
    ImageMaker();
    // function: normal constructor
    // preconditions: same as LoadImage()
    // postconditions: similar to the default constructor, except the width & height are set based on the given file
    //                 and the image is loaded into the image matrix
    ImageMaker(string filename);

    // Opens image with filename and stores information into

    // function: loads the given image
    // preconditions: valid file name, magic number is "P3", width & height are between 0 & MAX_WIDTH/ MAX_HEIGHT,
    //                inclusive, max. color range is equal to MAX_COLOR, and the color values are between 0 & MAX_COLOR,
    //                inclusive
    // postconditions: the image is loaded into the image matrix
    void LoadImage(string filename);
    // function: saves the image matrix
    // preconditions: width & height are non-zero
    // postconditions: saves the magic number as P3, width & height, MAX_COLOR, and a width x height area of the image
    //                 matrix to a file with the given name
    void SaveImage(string filename);

    // Size functions

    // function: returns width
    // preconditions: none
    // postconditions: width is returned
    int GetWidth();
    // function: returns height
    // preconditions: none
    // postconditions: height is returned
    int GetHeight();
    // function: sets the width
    // preconditions: new width is between 0 & MAX_WIDTH, inclusive
    // postconditions: sets the width to its new value
    void SetWidth(int width);
    // function: sets the height
    // preconditions: new height is between 0 & MAX_HEIGHT, inclusive
    // postconditions: sets the height to its new value
    void SetHeight(int height);

    // Color functions
    // function: returns the pen's red value
    // preconditions: none
    // postconditions: returns the pen's red value
    int GetPenRed();
    // function: returns the pen's green value
    // preconditions: none
    // postconditions: returns the pen's green value
    int GetPenGreen();
    // function: returns the pen's blue value
    // preconditions: none
    // postconditions: returns the pen's blue value
    int GetPenBlue();
    // function: sets the pen's red value
    // preconditions: new red value is between 0 & MAX_COLOR, inclusive
    // postconditions: sets the pen's red value to its new value
    void SetPenRed(int newR);
    // function: sets the pen's green value
    // preconditions: new green value is between 0 & MAX_COLOR, inclusive
    // postconditions: sets the pen's green value to its new value
    void SetPenGreen(int newG);
    // function: sets the pen's blue value
    // preconditions: new blue value is between 0 & MAX_COLOR, inclusive
    // postconditions: sets the pen's blue value to its new value
    void SetPenBlue(int newB);

    // Drawing methods
    // These methods will use the current red, green, blue values of the pen

    // function: draws a pixel with the pen's color values at the given coordinate
    // preconditions: width & height are non-zero and PointInBound() validated the given coordinate
    // postconditions: a pixel with the pen's color is drawn at (x, y) on the image matrix
    void DrawPixel(int x, int y);
    // function: draws a rectangle with the pen's color with the given coordinates
    // preconditions: PointInBound() validated the given coordinate
    // postconditions: a rectangle is drawn from four lines with the pen's color based on the given coordinates on the
    //                 image matrix
    void DrawRectangle(int x1, int y1, int x2, int y2);
    // function: draws a line with the pen's color with the given coordinates
    // preconditions: PointInBound() validated the given coordinates
    // postconditions: a line with the pen's color is drawn from (x1, y1) to (x2, y2) on the image matrix
    void DrawLine(int x1, int y1, int x2, int y2);

private:
    // the width & height of the image
    int width;
    int height;

    // the color values of the pen
    int pen_red;    // Used by draw functions
    int pen_green;  // Used by draw functions
    int pen_blue;   // Used by draw functions

    // function: validates x & y
    // preconditions: x & y are between 0 & MAX_WIDTH/ MAX_HEIGHT, inclusive
    // postconditions: returns true if the precondition is met, false otherwise
    bool PointInBounds(int x, int y);

    // the image matrix holding the image
    short image[MAX_WIDTH][MAX_HEIGHT][3];
};

#endif //IMAGEMAKER_H
