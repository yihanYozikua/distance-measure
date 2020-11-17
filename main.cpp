//
//  main.cpp
//  OpenCV-test
//
//  Created by 蕭伊涵 on 2020/11/16.
//  Copyright © 2020 YIHAN HSIAO. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(  ){

  //============= INITIALIZE VIDEO CAPTURE =================
  Mat frame;
  VideoCapture cap(0);
  
  int deviceID = 0; // 0: open default camera
  int apiID = CAP_ANY; // 0: autodetect default API

  // check if succeed
  if( !cap.isOpened() ){
    cerr << "ERROR! Unable to open camera\n" ;
    return -1;
  }

  //============= GRAB AND WRITE LOOP =================
  cout << "Start grabbing" << endl
       << "Press any key to terminate;" << endl;

  while( true ){
    // check if succeed
    if( !cap.read( frame ) ){
      break;
    }
    Mat src = Mat( frame );

    // show live and wait for a key with timeout long enough to show images
    imshow( "Live", src );

    if( waitKey(30) >= 0 ){
      break;
    }

    // waitKey( 30 );
  }

  // Mat img = imread( "ttt.png" );
  // if( img.empty() ){
  //   cout << "Not a falid image file." << endl;
  // }
  // namedWindow( "Simple Demo", WINDOW_AUTOSIZE );
  // imshow( "Simple Demo", img );
  
  waitKey(0);
  destroyAllWindows();

  return 0;
}

// Open camera
void openCamera(){
  
  Mat frame;

  //============= INITIALIZE VIDEO CAPTURE =================
  VideoCapture cap; 
  
  int deviceID = 0; // 0: open default camera
  int apiID = CAP_ANY; // 0: autodetect default API

  // open selected camera using selected API
  cap.open( deviceID, apiID );

  // check if succeed
  if( !cap.isOpened() ){
    cerr << "ERROR! Unable to open camera\n" ;
    // return -1;
  }

  //============= GRAB AND WRITE LOOP =================
  cout << "Start grabbing" << endl
       << "Press any key to terminate;" << endl;

  while( 1 ){
    // wait for a new frame frame from camera and store it into 'frame'
    cap.read( frame );
    // check if succeed
    if( frame.empty() ){
      cerr << "ERROR! blank frame grabbed\n";
      break;
    }

    // show live and wait for a key with timeout long enough to show images
    imshow( "Live", frame );
    if( waitKey(5) >= 0 ){
      break;
    }
  }

}

