/** Definition of the class UGKWebCam. Base class for the management of any generic web camera
*	Prefix: UGKWEBCAM_H	for class Web Cam
*	@file	UGKWebCam.cpp
*	@brief	Base class for the management of any generic web camera
*	Prefix  UGKWC_
*	@author Javier Jorge
*	@date	2015-01-30
*/

#include <UGKWebCam.h>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace UGK;

UGKWebCam::UGKWebCam()		///<Constructor of the class
{
	TypeHW = CHW_IN_WEBCAM;		// Define Type Hardware
}

/**
* @brief Metodo de inicializacion de la camara
* @param initialize Obtener camara en este momento
*/
CHW_HW_STATUS UGKWebCam::Init(){

#ifdef UGKWC_OPENCV
	scale = 1;
	capture = 0;

	capture = cvCaptureFromCAM(CV_CAP_ANY);
	if (!capture){
		return CHW_HW_NOT_INITIALIZED;
	}
#elif defined UGKWC_DLIB
#endif
	return CHW_HW_INITIALIZED;
}


CHW_HW_STATUS UGKWebCam::findHardware(){
	/**
	* @brief Metodo para evaluar si la camara esta preparada
	* @return True si lo esta, False en caso contrario
	*/
	if (UGKWebCam::getCapture())
		 return CHW_HW_NOT_INITIALIZED;
	else return CHW_HW_NOT_FOUND;
}

/**
* @brief Detecta la cara y dibuja un circulo alrededor
*/

UGKWC_RESULT UGKWebCam::simpleDetectAndDraw(){

#ifdef UGKWC_OPENCV

	CascadeClassifier cascade, nestedCascade;
	if( !nestedCascade.load( "../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml"))
	{
			return UGKWC_ERROR;
	}
	if( !cascade.load( "../../data/haarcascades/haarcascade_frontalface_alt.xml"))
	{
		return UGKWC_ERROR;
	}

	cvNamedWindow( "result", 1 );
	
	capture = cvCaptureFromCAM( CV_CAP_ANY);
    if( capture )
    {
        //cout << "In capture ..." << endl;
        for(;;)
        {
            iplImg = cvQueryFrame( capture );
            frame = iplImg;

            if( frame.empty() )
                break;
            if( iplImg->origin == IPL_ORIGIN_TL )
                frame.copyTo( frameCopy );
            else
                flip( frame, frameCopy, 0 );

            detectAndDraw( frameCopy, cascade, nestedCascade, scale );
        }
        waitKey(0);
        cvReleaseCapture( &capture );
    }

    cvDestroyWindow("result");
#elif defined UGKWC_DLIB

#endif

    return UGKWC_OK;
}

/**
* @brief Detecta la cara y dibuja un circulo alrededor
* @param img La imagen de la camara
* @param cascade El clasificador
* @param nestedCascade El otro clasificador
* @param scale Escala de la captura
*/
#ifdef UGKWC_OPENCV
void UGKWebCam::detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale)
{
	int i = 0;
	double t = 0;

	vector<Rect> faces, faces2;
	Scalar colors[] = { CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255) };

	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

	cvtColor(img, gray, CV_BGR2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	t = (double)cvGetTickCount();

	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		| CV_HAAR_FIND_BIGGEST_OBJECT
		| CV_HAAR_SCALE_IMAGE
		//|CV_HAAR_DO_ROUGH_SEARCH
		,
		Size(30, 30));

	t = (double)cvGetTickCount() - t;
	//printf( "detection time (modificado) = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r->width / r->height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{

			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			//printf( "positition = %d, %d  ms\n", center.x , center.y );
			radius = cvRound((r->width + r->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
				cvPoint(cvRound((r->x + r->width - 1)*scale), cvRound((r->y + r->height - 1)*scale)),
				color, 3, 8, 0);
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(*r);
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			| CV_HAAR_FIND_BIGGEST_OBJECT
			| CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++)
		{
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
	}

	cv::imshow("result", img);
}
#elif defined UGKWC_DLIB

#endif


/**
* @brief Detecta la cara y devuelve su posición con respecto a las coordenadas de la pantalla
entre 0,0 y maxXres,maxYres
* @param img La imagen de la camara
* @param cascade Clasificadores
* @param nestedCascade Clasificadores anidados
* @return Las coordenadas mencionadas
*/


#ifdef UGKWC_OPENCV
Point UGKWebCam::detectAndGetPosition(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale)
{
	int i = 0;
	double t = 0;
	vector<Rect> faces, faces2;
	const static Scalar colors[] = { CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255) };
	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

	cvtColor(img, gray, CV_BGR2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	t = (double)cvGetTickCount();
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		| CV_HAAR_FIND_BIGGEST_OBJECT
		| CV_HAAR_SCALE_IMAGE
		//|CV_HAAR_DO_ROUGH_SEARCH

		,
		Size(30, 30));

	t = (double)cvGetTickCount() - t;
	//printf( "detection time (modificado) = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
	Point center;
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;

		Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r->width / r->height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{

			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			//printf( "positition = %d, %d  ms\n", center.x , center.y );
			radius = cvRound((r->width + r->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
				cvPoint(cvRound((r->x + r->width - 1)*scale), cvRound((r->y + r->height - 1)*scale)),
				color, 3, 8, 0);
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(*r);
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			| CV_HAAR_FIND_BIGGEST_OBJECT
			| CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++)
		{
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
	}

	return center;
}
#elif defined UGKWC_DLIB

#endif

/**
* @brief Metodo para acceder a la posicion de la cara del usuario
* @see detectAndGetPosition()
* @return El punto donde se encuentra el usuario con respecto a la camara
*/
#ifdef UGKWC_OPENCV

Point UGKWebCam::getPosition()
{
	CascadeClassifier cascade, nestedCascade;
	if( !nestedCascade.load( "../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml") ){
		return NULL;
	}
	if( !cascade.load( "../../data/haarcascades/haarcascade_frontalface_alt.xml" ) )
		return NULL;
	//cout << "In capture ..." << endl;
	iplImg = cvQueryFrame( capture );
	frame = iplImg;
	if( !frame.empty() ){
		//cout << "Inside frame ..." << endl;	
	
		if( iplImg->origin == IPL_ORIGIN_TL )
			frame.copyTo( frameCopy );
		else
			flip( frame, frameCopy, 0 );
		
		////*******////
		Point center = Point(0,0);
		center = detectAndGetPosition( frame, cascade, nestedCascade,scale);
		//printf( "positition(WB_Real) = %d, %d  ms\n", center.x , center.y );
		////*******////
		return center;
	}
	return NULL;	//By default no point observed
}
#elif defined UGKWC_DLIB
#endif

/**
* @brief Muestra en pantalla la ultima imagen capturada almacenada en disco
* 
*/
void UGKWebCam::showPicture(){
#ifdef UGKWC_OPENCV

	Mat image;
	image = imread( "test.jpg", 1 );
    if(! image.data ) // Check for invalid input
    {
        printf("Could not open or find the image");
        //return -1;
	}else{

		namedWindow("Display window", WINDOW_AUTOSIZE ); // Create a window for display.
		imshow( "Display window", image ); // Show our image inside it.

		waitKey(0); // Wait for a keystroke in the window
    }
	cvDestroyWindow( "mywindow" );
#elif defined UGKWC_DLIB
#endif
}

/**
* @brief Muestra en pantalla y captura la imagen de la camara, almacenandola en disco
*/
void UGKWebCam::takePicture(){
#ifdef UGKWC_OPENCV

	CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 352); 
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 288);


	// Get one frame
	IplImage* frame;

	for (int i = 0; i < 25; i++) 
	{
	frame = cvQueryFrame( capture );
	}


	printf( "Image captured \n" );  
	//IplImage* RGB_frame = frame;
	//cvCvtColor(frame,RGB_frame,CV_YCrCb2BGR);
	//cvWaitKey(1000);
	
	cvNamedWindow( "Picture", CV_WINDOW_AUTOSIZE );
	cvShowImage("Picture", frame );
	
	cvSaveImage("test.jpg" ,frame);
	cvWaitKey(-1);

	//cvSaveImage("cam.jpg" ,RGB_frame);

	printf( "Image Saved \n" );

	//cvWaitKey(10);

	// Release the capture device housekeeping
	cvReleaseCapture( &capture );
	//capture = cvCaptureFromCAM( 0 );
	cvDestroyWindow( "Picture" );
#elif defined UGKWC_DLIB
#endif
}

/**
* @brief Metodo para evaluar si la camara esta preparada
* @return True si lo esta, False en caso contrario
*/
bool UGKWebCam::getCapture(){
#ifdef UGKWC_OPENCV
	return capture != 0;
#elif defined UGKWC_DLIB
#endif
	return false;
}