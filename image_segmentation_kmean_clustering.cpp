// This code uses the OpenCV library to perform image segmentation using k-means clustering. It first loads an image from a file named "image.jpg" using the imread() function. If the image cannot be loaded, the code prints an error message and exits.

// The code then reshapes the image into a 2D array of pixels using the reshape() function and converts the pixel values to floating-point format using the convertTo() function. This is necessary because the kmeans() function in OpenCV only works with floating-point data.

// The code sets the number of clusters to 3 and defines a termination criteria for k-means clustering using the TermCriteria class. The termination criteria specifies that k-means clustering should stop after 10 iterations or when the centroid positions move less than 1.0 units between iterations.

// The code then performs k-means clustering on the pixels using the kmeans() function. This function takes as input the pixel data, the number of clusters, the output labels, the termination criteria, and some other parameters. The output labels indicate which cluster each pixel belongs to, and the output centers indicate the position of the centroids of each cluster.

// The labels and centers are then reshaped back into an image using the reshape() function and converted back to 8-bit integer format using the convertTo() function. The resulting image is the segmented image, where each pixel is assigned to one of the k clusters based on its color.

// Finally, the original and segmented images are displayed in separate windows using the namedWindow(), imshow(), and waitKey() functions. The namedWindow() function creates a window with a specified name and display properties, while the imshow() function displays an image in the specified window. The waitKey() function waits for a keyboard event and returns the ASCII code of the pressed key.


#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    // Load an image
    Mat image = imread("image.jpg");
    if (image.empty())
    {
        std::cout << "Error loading image" << std::endl;
        return -1;
    }

    // Reshape the image into a 2D array of pixels
    Mat reshapedImage = image.reshape(1, image.cols * image.rows);
    reshapedImage.convertTo(reshapedImage, CV_32F);

    // Set the number of clusters
    int k = 3;

    // Define the termination criteria for k-means clustering
    TermCriteria criteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0);

    // Perform k-means clustering on the pixels
    Mat labels, centers;
    kmeans(reshapedImage, k, labels, criteria, 3, KMEANS_PP_CENTERS, centers);

    // Reshape the labels and centers back into an image
    Mat segmented = labels.reshape(0, image.rows);
    segmented.convertTo(segmented, CV_8U);

    // Display the original and segmented images
    namedWindow("Original Image", WINDOW_NORMAL);
    imshow("Original Image", image);
    namedWindow("Segmented Image", WINDOW_NORMAL);
    imshow("Segmented Image", segmented);
    waitKey(0);

    return 0;
}
