#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
using namespace cv;
int n_boards = 0;
int board_w;
int board_h;

//void bird_eye();

int main(int argc, char* argv[]) {

	board_w = 9;//9//atoi(argv[1]);
	board_h = 6;//atoi(argv[2]);
	n_boards = 1;//atoi(argv[3]);
	Mat image = imread("cimg_cross.jpg", 1);
	imshow("org_img", image);
	Mat H;
	FileStorage fs("H8.10.xml", FileStorage::READ);
	fs["H"] >> H;
	fs.release();
	float z = 10;
	int key = waitKey();
	Mat birds_image = image.clone();
	int a = 0;
	while (a != 27) {
		H.at<double>(2, 2) = z;
		warpPerspective(image, birds_image, H, image.size(), WARP_INVERSE_MAP + INTER_LINEAR + WARP_FILL_OUTLIERS);//
		imshow("birds_image", birds_image);
		a = waitKey();
		if (a == 'd')z -= 0.5;
		else if (a == 'f')z += 0.5;
	}
//	bird_eye();
	return 0;
}

//void bird_eye() {
//	int board_n = board_w * board_h;
//	Size board_sz = Size(board_w, board_h);
//	Size imageSize;
//	Mat intrinsic, distortion;
//	FileStorage fs2("Intrinsics2.xml", FileStorage::READ);
//	fs2["Intrinsics"] >> intrinsic;
//	fs2.release();
//	FileStorage fs3("Distortion2.xml", FileStorage::READ);
//	fs3["Distortion"] >> distortion;
//	fs3.release();
//	Mat image = imread("./Resource/17.jpg", 1);
//	imshow("org_img", image);
//	imageSize = image.size();
//
//	//Mat gray_image;
//	//cvtColor(image, gray_image, CV_BGR2GRAY);
//
//	Mat map1, map2;
//	
//	//initUndistortRectifyMap(intrinsic, distortion, Mat(),
//	//	//getOptimalNewCameraMatrix(intrinsic, distortion, imageSize, 1, imageSize, 0), 
//	//	intrinsic,//Changed
//	//	imageSize, CV_16SC2, map1, map2);
//	
//	Mat t = image.clone();
//	
//	remap(t, image, map1, map2, INTER_LINEAR);
//	imshow("undistort View", image);
//	//cvtColor(image, gray_image, CV_BGR2GRAY);//-----
//
//	int c = cvWaitKey(-1);
//	//CvPoint2D32f* corners = new CvPoint2D32f[board_n];
//	
//	int corner_count = 0;
//	
//	vector<Point2f> corners;
//	bool found = findChessboardCorners(image, board_sz, corners,
//		CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS );//| CV_CALIB_CB_FAST_CHECK| CV_CALIB_CB_NORMALIZE_IMAGE
//	
//	if(!found){
//		printf("couldn't aquire chessboard!\n");
//		return;
//	}
//	
//	cornerSubPix(gray_image, corners, Size(11, 11),
//		Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
//
//	
//	Point2f objPts[4], imgPts[4];
//	objPts[0].x = 0;			objPts[0].y = 0;
//	objPts[1].x = board_w - 1;	objPts[1].y = 0;
//	objPts[2].x = 0;			objPts[2].y = board_h - 1;
//	objPts[3].x = board_w - 1;	objPts[3].y = board_h - 1;
//	imgPts[3]   = corners[0];
//	imgPts[2]	= corners[board_w - 1];
//	imgPts[1]	= corners[(board_h - 1) * board_w];
//	imgPts[0]	= corners[(board_h - 1) * board_w + board_w - 1];
//
//	vector<Point3f> objVtrPts;
//	Mat objVtrPtsM;
//	objVtrPts.push_back(Point3f(0, 0, 0));    //��ά����ĵ�λ�Ǻ���
//	objVtrPts.push_back(Point3f((board_w - 1), 0, 0));
//	objVtrPts.push_back(Point3f(0, (board_h - 1), 0));
//	objVtrPts.push_back(Point3f((board_w - 1), (board_h - 1), 0));
//	Mat(objVtrPts).convertTo(objVtrPtsM, CV_32F);
//
//	vector<Point2f> imgVtrPts;
//	imgVtrPts.push_back(Point2f(corners[(board_h - 1) * board_w + board_w - 1]));
//	imgVtrPts.push_back(Point2f(corners[(board_h - 1) * board_w]));
//	imgVtrPts.push_back(Point2f(corners[board_w - 1]));
//	imgVtrPts.push_back(Point2f(corners[0]));//0
//
//	Mat imgVtrPtsM;
//	Mat(imgVtrPts).convertTo(imgVtrPtsM, CV_32F);
//
//
//	
//	circle(image, cvPointFrom32f(imgVtrPts[0]),9, Scalar(0, 0, 255),3);
//	circle(image, cvPointFrom32f(imgVtrPts[1]), 9, Scalar(0, 255, 0), 3);
//	circle(image, cvPointFrom32f(imgVtrPts[2]), 9, Scalar(255, 0, 0), 3);
//	circle(image, cvPointFrom32f(imgVtrPts[3]), 9, Scalar(255, 255, 0), 3);
//
//	if (found)  drawChessboardCorners(image, board_sz, Mat(corners), found);//
//
//	vector<double> rv(3), tv(3);
//	Mat rvec(rv), tvec(tv);
//	double rm[9];
//	Mat rotM(3, 3, CV_64FC1, rm);
//	Rodrigues(rotM, rvec);
//	solvePnP(objVtrPtsM, Mat(imgVtrPts), intrinsic, distortion, rvec, tvec);
//	Rodrigues(rvec, rotM);
//
//	cout << "rotation_matrix: " << endl << rotM << endl;
//	cout << "translation_matrix: " << endl << tv[0] << " " << tv[1] << " " << tv[2] << endl;
//	FileStorage fs("Extrinsics.xml", FileStorage::WRITE);
//	fs << "rotation_matrix" << rotM;
//	fs << "translation_matrix" << tv;
//	fs.release();
//	imshow("Chessboard", image);
//	waitKey();
//	////CvMat *H = cvCreateMat(3, 3, CV_32F);
//	////cvGetPerspectiveTransform(objPts, imgPts, H);
//	Mat H;
//	H = getPerspectiveTransform(objPts, imgPts);//(objVtrPts, imgVtrPts);
//	float z = 10;
//	int key = waitKey();
//	Mat birds_image= image.clone();
//	int a=0;
//	while (a != 27) {
//		H.at<double>(2, 2) = z;
//		warpPerspective(image, birds_image, H, image.size(), WARP_INVERSE_MAP+ INTER_LINEAR + WARP_FILL_OUTLIERS);//
//		imshow("birds_image", birds_image);
//		a=waitKey();
//		if(a=='d')z -= 0.5;
//		else if(a == 'f')z += 0.5;
//	}
//
//}

