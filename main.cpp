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
#include "tools.h"

using namespace std;
using namespace cv;

int main(  ){

  Tools test;
  test.video_capture();

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