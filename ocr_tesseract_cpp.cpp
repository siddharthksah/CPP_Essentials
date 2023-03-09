// This code uses the OpenCV library and the Tesseract OCR library to perform optical character recognition (OCR) on a scanned document image. It first loads the image from a file named "document.jpg" using the imread() function. If the image cannot be loaded, the code prints an error message and exits.

// The code then converts the image to grayscale using the cvtColor() function and thresholds the grayscale image using Otsu's method, which automatically determines an optimal threshold value to separate the foreground and background pixels. This is necessary to preprocess the image before performing OCR.

// The code then creates a Tesseract OCR engine using the TessBaseAPI class and sets its language to English and page segmentation mode to automatic using the Init() and SetPageSegMode() methods, respectively.

// The code then sets the image data and performs OCR using the SetImage() and GetUTF8Text() methods, respectively. The SetImage() method takes as input the image data, width, height, number of channels, and stride, while the GetUTF8Text() method returns the recognized text as a UTF-8 encoded string.

// Finally, the recognized text is printed to the console using the std::cout statement.

#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <iostream>

using namespace cv;

int main()
{
    // Load a scanned document image
    Mat image = imread("document.jpg");
    if (image.empty())
    {
        std::cout << "Error loading image" << std::endl;
        return -1;
    }

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Threshold the image using Otsu's method
    Mat binaryImage;
    threshold(grayImage, binaryImage, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // Create a Tesseract OCR engine and set its language and page segmentation mode
    tesseract::TessBaseAPI ocr;
    ocr.Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
    ocr.SetPageSegMode(tesseract::PSM_AUTO);

    // Set the image data and perform OCR
    ocr.SetImage(binaryImage.data, binaryImage.cols, binaryImage.rows, 1, binaryImage.step);
    std::string text = ocr.GetUTF8Text();

    // Print the recognized text
    std::cout << "Recognized text:" << std::endl;
    std::cout << text << std::endl;

    return 0;
}
