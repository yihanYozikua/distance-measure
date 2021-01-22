//
//  main.cpp
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2020/11/16.
//  Copyright © 2020 YIHAN HSIAO. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include "tools.h"

using namespace std;
using namespace cv;

// Print error message
void PANIC( char *msg );
#define PANIC( msg ){ perror(msg); exit(-1); }

// Function for face detection
void FaceDetection( Mat frame );

// Global variables
String face_cascade_name = "Source/haarcascade_eye_tree_eyeglasses.xml";
String eyes_cascade_name = "Source/haarcascade_frontalface_default.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Face Detection";

int main( int argc, char *argv[] ){

  // Tools test; // init the object
  // test.video_capture();

  // camera init
  VideoCapture cap = VideoCapture(0);
  Mat frame, img;

  // load cascade classifiers
  if( !face_cascade.load(face_cascade_name) ){
    PANIC( "ERROR loading face cascade" );
  }
  if( !eyes_cascade.load(eyes_cascade_name) ){
    PANIC( "ERROR loading eyes cascade" );
  }

  // after the camera is open
  if( cap.isOpened() ){
    cout << "Face Detection Start..." << endl;

    while( true ){
      // get img from camera
      cap >> frame;
      if( frame.empty() ){
        PANIC( "ERROR capture frame" );
      }

      // start the face detection function
      FaceDetection( frame );

      // if press ESC, q, or Q, the process will end
      char ch = ( char )waitKey( 10 );
      if( ch == 27 || ch =='q' || ch == 'Q' ){
        break;
      }

    }
  }

  else{
    PANIC( "ERROR open camera" );
  }
  
  destroyAllWindows();

  return 0;
}


void FaceDetection( Mat frame ){
  
  // declare vector for faces and eyes
  vector<Rect> faces, eyes;
  Mat frame_gray, frame_resize;
  int radius;

  // convert to gray scale
  cvtColor( frame, frame_gray, COLOR_BGR2GRAY );

  // histogram equalization
  equalizeHist( frame_gray, frame_gray );

  // detect faces of different sizes using cascade classifier
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 5, CV_HAL_BORDER_CONSTANT, Size(30, 30) );

  // draw circles around the faces
  for( size_t i = 0; i < faces.size(); i++ ){
    
    Point center;
    
    // draw rectangular on face
    rectangle( frame, faces[i], Scalar(255, 0, 0), 3, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );

    // detection of eyes in the input image
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 1, CV_HAL_BORDER_CONSTANT, Size(30, 30) );

    // draw circles around eyes
    for( size_t j = 0; j < eyes.size(); j++){
      center.x = cvRound( ( faces[i].x + eyes[j].x + eyes[j].width*0.5 ) );
      center.y = cvRound( ( faces[i].y + eyes[j].y + eyes[j].height*0.5 ) );
      radius = cvRound( ( eyes[j].width + eyes[j].height )*0.25 );
      circle( frame, center, radius, Scalar( 0, 255, 0 ), 3, 8, 0 );
    }
  }

  // show processed img with detected faces
  imshow( "Face Detection", frame );

}