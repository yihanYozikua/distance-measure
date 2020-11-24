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

int main( int argc, char *argv[] ){

  Tools tool; // create a new object

  // camera init
  VideoCapture cap = VideoCapture(0);
  Mat frame, img;

  // load cascade classifiers
  if( !tool.face_cascade.load(tool.face_cascade_name) ){ tool.ERROR_LOG( "ERROR loading face cascade" ); }
  if( !tool.eyes_cascade.load(tool.eyes_cascade_name) ){ tool.ERROR_LOG( "ERROR loading eyes cascade" ); }

  // after the camera is open
  if( cap.isOpened() ){
    cout << "Face Detection Start..." << endl;

    // INIT DISTANCE

    // ANALYZE
    while( true ){
      // get img from camera
      cap >> frame;
      if( frame.empty() ){ tool.ERROR_LOG( "ERROR capture frame" ); }

      // start the face detection function
      tool.FaceDetection( frame );
      
      // show processed img with detected faces
      imshow( "Eyes Detection", frame );

      // if press ESC, q, or Q, the process will end
      char ch = ( char )waitKey( 10 );
      if( ch == 27 || ch =='q' || ch == 'Q' ){ break; }
    }
  }

  else{ tool.ERROR_LOG( "ERROR open camera" ); }
  
  destroyAllWindows();

  return 0;
}