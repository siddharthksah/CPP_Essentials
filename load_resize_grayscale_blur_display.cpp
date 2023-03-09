// The provided code is a simple example of image processing using C++ and the OpenCV library. Image processing is a field of computer vision that deals with manipulating digital images to enhance their quality, extract information, or transform them into a new form.

// The code starts by loading an image from a file named "image.jpg" using the imread() function. If the image cannot be loaded, the code prints an error message and exits.

// The code then resizes the image to a new size of 640x480 using the resize() function. Resizing an image can be useful for reducing its size or changing its aspect ratio to fit a particular application or display.

// Next, the code converts the image to grayscale using the cvtColor() function. Grayscale images are often used in image processing because they can simplify the image data and reduce the amount of computation required for some tasks.

// The code then applies a Gaussian blur to the grayscale image using the GaussianBlur() function. Gaussian blur is a common image processing technique that can be used to reduce noise or smooth out details in an image. It works by convolving the image with a Gaussian kernel, which is a matrix that gives more weight to nearby pixels and less weight to distant pixels.

// Finally, the code displays the processed image in a new window named "Image" using the namedWindow(), imshow(), and waitKey() functions. The namedWindow() function creates a window with a specified name and display properties, while the imshow() function displays an image in the specified window. The waitKey() function waits for a keyboard event and returns the ASCII code of the pressed key.


#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    // Load an image
    Mat image = imread("image.jpg");

    // Check if the image was loaded successfully
    if (image.empty())
    {
        std::cout << "Error loading image" << std::endl;
        return -1;
    }

    // Resize the image
    Size newSize(640, 480);
    resize(image, image, newSize);

    // Convert the image to grayscale
    cvtColor(image, image, COLOR_BGR2GRAY);

    // Apply Gaussian blur
    GaussianBlur(image, image, Size(5, 5), 0);

    // Display the image
    namedWindow("Image", WINDOW_NORMAL);
    imshow("Image", image);
    waitKey(0);

    return 0;
}
