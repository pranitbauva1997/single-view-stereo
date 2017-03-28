#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

float ratioTest = 0.70f;
int numKeyPoints = 1500;

int main() {
   char *debug = getenv("DEBUG");

	// Read the images as grayscale
	Mat left = imread("left.jpg", 0);
	Mat right = imread("right.jpg", 0);

	// Show the images
	if (debug) {
		namedWindow("Left", WINDOW_AUTOSIZE);
		namedWindow("Right", WINDOW_AUTOSIZE);
		imshow("Left", left);
		imshow("Right", right);
	}

	// Detect the keypoints using the SURF detector
	int minHessian = 400;
	vector<KeyPoint> left_keypoints, right_keypoints;
	OrbFeatureDetector detector(minHessian);

	detector.detect(left, left_keypoints);
	detector.detect(right, right_keypoints);

	if (debug) {
		Mat img_keypoints_left, img_keypoints_right;
		drawKeypoints(left, left_keypoints, img_keypoints_left, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
		drawKeypoints(right, right_keypoints, img_keypoints_right, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
		imshow("Left Keypoints", img_keypoints_left);
		imshow("Right keypoints", img_keypoints_right);
	}
	// Calculate descriptors (feature vectors)
	//OrbDescriptorExtractor extractor;

	Mat left_descriptors, right_descriptors;

	//extractor.compute(left, left_keypoints, left_descriptors);
	//extractor.compute(right, right_keypoints, right_descriptors);

	// Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	vector<DMatch> matches;

	//matcher.match(left_descriptors, right_descriptors, matches);

	double max_dist = 0, min_dist = 100;

	// Quick calculation of max and min distances between keypoints
	for (int i = 0; i < left_descriptors.rows; i++) {
		double dist = matches[i].distance;
		if (dist < min_dist)
			min_dist = dist;
		if (dist > max_dist)
			max_dist = dist;
	}

	if (debug) {
		printf("Max Dist: %f\n", max_dist);
		printf("Min Dist: %f\n", min_dist);
	}

	waitKey(0);
	return 0;
}
