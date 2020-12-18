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

  tool.time_capture();

  // load cascade classifiers
  if( !tool.face_cascade.load(tool.face_cascade_name) ){ tool.ERROR_LOG( "ERROR loading face cascade" ); }
  if( !tool.eyes_cascade.load(tool.eyes_cascade_name) ){ tool.ERROR_LOG( "ERROR loading eyes cascade" ); }

  // after the camera is open
  if( cap.isOpened() ){
    cout << "Face Detection Start..." << endl;

    // INIT
    while( true ){
      // get frames from camera
      cap >> frame;
      if( frame.empty() ){ tool.ERROR_LOG( "ERROR capture frame" ); }
      imshow( "Init", frame );

      // init
      char pressKey = ( char )waitKey( 1 );
      if( pressKey == 13 ){
        cout << "START INIT" << endl;
        tool.DistanceInit( frame );
        if( pressKey == 13 ){ // confirm by pressing the "SPACE" key
          cout << "width: " << tool.obj_width << endl;
          cout << "Height: "<< tool.obj_height << endl;
          cout << "END INIT" << endl;
          break;
        }
      }
    }

    destroyWindow( "Init" );


    // ANALYZE
    while( true ){
      // get frames from camera
      cap >> frame;
      if( frame.empty() ){ tool.ERROR_LOG( "ERROR capture frame" ); }

      // start the face detection function
      tool.Detection( frame );
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