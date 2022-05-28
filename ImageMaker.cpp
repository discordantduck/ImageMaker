#include "ImageMaker.h"

ImageMaker::ImageMaker()
{
    SetWidth(0);
    SetHeight(0);

    SetPenRed(0);
    SetPenGreen(0);
    SetPenBlue(0);

    for(int y = 0; y < MAX_HEIGHT; y++)
    {
        for(int x = 0; x < MAX_WIDTH; x++)
        {
            image[x][y][RED] = 255;
            image[x][y][GREEN] = 255;
            image[x][y][BLUE] = 255;
        }
    }
}

ImageMaker::ImageMaker(string filename)
{
    for(int y = 0; y < MAX_HEIGHT; y++)
    {
        for(int x = 0; x < MAX_WIDTH; x++)
        {
            image[x][y][RED] = 255;
            image[x][y][GREEN] = 255;
            image[x][y][BLUE] = 255;
        }
    }

    LoadImage(filename);

    // LoadImage() changes the pen color, so they're changed to black here
    SetPenRed(0);
    SetPenGreen(0);
    SetPenBlue(0);
}

void ImageMaker::LoadImage(string filename)
{
    ifstream inputFile;
    string magicNum;
    int temp;

    inputFile.open(filename);
    if(!inputFile.is_open())
    {
        throw "File failed to open";
    }

    inputFile >> magicNum;
    if(magicNum != "P3")
    {
        throw "Bad magic number";
    }

    inputFile >> temp;
    SetWidth(temp);
    inputFile >> temp;
    SetHeight(temp);

    inputFile >> temp;
    if(temp != MAX_COLOR)
    {
        throw "Max color range not 255";
    }

    // loops through the image column by row and set the color value at (x, y) on the canvas based on it
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            inputFile >> temp;
            SetPenRed(temp);

            inputFile >> temp;
            SetPenGreen(temp);

            inputFile >> temp;
            SetPenBlue(temp);

            DrawPixel(x, y);
        }
    }

    inputFile.close();
}

void ImageMaker::SaveImage(string filename)
{
    ofstream outputFile;
    outputFile.open(filename);

    outputFile << "P3" << endl;

    if(width == 0 || height == 0)
    {
        throw "Image must have non-zero dimensions";
    }
    outputFile << width << ' ' << height << endl;
    outputFile << MAX_COLOR << endl;

    // writes out the image's color values column by row
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            outputFile << image[x][y][RED] << ' ' << image[x][y][GREEN] << ' ' << image[x][y][BLUE] << ' ';
        }
        outputFile << endl;
    }

    outputFile.close();
}

int ImageMaker::GetWidth()
{
    return width;
}

int ImageMaker::GetHeight()
{
    return height;
}

void ImageMaker::SetWidth(int width)
{
    if(width < 0 || width > MAX_WIDTH)
    {
        throw "Width out of bounds";
    }

    this->width = width;
}

void ImageMaker::SetHeight(int height)
{
    if(height < 0 || height > MAX_HEIGHT)
    {
        throw "Height out of bounds";
    }

    this->height = height;
}

int ImageMaker::GetPenRed()
{
    return pen_red;
}

int ImageMaker::GetPenGreen()
{
    return pen_green;
}

int ImageMaker::GetPenBlue()
{
    return pen_blue;
}

void ImageMaker::SetPenRed(int newR)
{
    if(newR < 0 || newR > MAX_COLOR)
    {
        throw "Color value invalid";
    }

    pen_red = newR;
}

void ImageMaker::SetPenGreen(int newG)
{
    if(newG < 0 || newG > MAX_COLOR)
    {
        throw "Color value invalid";
    }

    pen_green = newG;
}

void ImageMaker::SetPenBlue(int newB)
{
    if(newB < 0 || newB > MAX_COLOR)
    {
        throw "Color value invalid";
    }

    pen_blue = newB;
}

void ImageMaker::DrawPixel(int x, int y)
{
    if(width == 0 || height == 0 || !PointInBounds(x, y))
    {
        throw "Point out of bounds";
    }

    image[x][y][RED] = GetPenRed();
    image[x][y][GREEN] = GetPenGreen();
    image[x][y][BLUE] = GetPenBlue();
}

void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2)
{
    DrawLine(x1, y1, x2, y1);
    DrawLine(x1, y2, x2, y2);
    DrawLine(x1, y1, x1, y2);
    DrawLine(x2, y1, x2, y2);
}

void ImageMaker::DrawLine(int x1, int y1, int x2, int y2)
{
    if(!PointInBounds(x1, y1) || !PointInBounds(x2, y2))
    {
        throw "Point out of bounds";
    }

    // if the line's vertical, the x value doesn't change, loop in terms of y, starting at the smaller of the two given
    // y values and ending at the larger, call DrawPixel() at every point
    if(x1 == x2)
    {
        int startY = y1 < y2 ? y1 : y2;
        int endY = startY == y1 ? y2 : y1;

        for(int y = startY; y <= endY; y++)
        {
            DrawPixel(x1, y);
        }
    }
    // otherwise, calculate the slope & intercept and instead loop in terms of x, calling DrawPixel() at every point
    else
    {
        int startX = x1 < x2 ? x1 : x2;
        int endX = startX == x1 ? x2 : x1;

        int m = (y2 - y1) / (x2 - x1);
        int b = 0;

        // the calculation for b changes based on the starting value for x
        if(startX == x1)
        {
            b = y1 - m * x1;
        }
        else
        {
            b = y2 - m * x2;
        }

        for(int x = startX; x <= endX; x++)
        {
            DrawPixel(x, round(m * x + b));
        }
    }
}

// checks if the given (x, y) is non-negative and between the width x height area
bool ImageMaker::PointInBounds(int x, int y)
{
    if(x < 0 || x > width || y < 0 || y > height)
    {
        return false;
    }

    return true;
}