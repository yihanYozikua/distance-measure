//
//  backend.cpp
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2021/02/17.
//  Copyright © 2020 - 2021 YIHAN HSIAO. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <sstream>
#include <ctime>
#include <time.h>

#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include "backend.h"

using namespace std;
using json = nlohmann::json;
using namespace cv;
namespace fs = std::experimental::filesystem;

// BKN
// init the user's distance
void Backend::DistanceInit( Mat frame ){
  // declare vector for faces and eyes
  vector<Rect> faces, eyes;
  Mat frame_gray, frame_resize;

  // convert to gray scale
  cvtColor( frame, frame_gray, COLOR_BGR2GRAY );

  // histogram equalization
  equalizeHist( frame_gray, frame_gray );

  // detect faces of different sizes using cascade classifier
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 5, CV_HAL_BORDER_CONSTANT, Size(30, 30) );

  // draw circles around the eyes
  for( size_t i = 0; i < faces.size(); i++ ){
    
    // draw rectangular on eyes
    rectangle( frame, faces[i], Scalar(255, 0, 0), 3, 8, 0 );
    obj_width = faces[i].width;
    obj_height = faces[i].height;
  }
}

// BKN
// compare thr analysis result to init distance
bool Backend::CompareWithInit( Rect coordinate ){
  if( ( coordinate.width > obj_width + 10 ) && ( coordinate.height > obj_height + 10 ) ){
    return true;
  }
  else{
    return false;
  }
}

// BKN
// Detect if the user gets too close to the screen
void Backend::Detection( Mat frame ){
  // declare vector for faces and eyes
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
    // draw rectangular on face
    rectangle( frame, faces[i], Scalar(255, 0, 0), 3, 8, 0 );
    if( CompareWithInit( faces[i] ) ){
      cout << "ALERRRRRRRRRRRRT" << endl;
    }
  }
}


// BKN
// Detect Screen Usage Time
double Backend::timeElapsed( clock_t start, clock_t end ){
  double duration;
  duration = (double)(end - start) / CLOCKS_PER_SEC / 2.5;
  cout << "Screen Usage: " << duration << " secs" << endl;
  return duration;
}


// BKN
// When the duration time up, give choices for user to choose next-step action
void Backend::duration_choice(){
  char duration_choice;
  cout << "Press 'R' to Remind me later" << endl
       << "or Press 'B' to have a break" << endl;

  cin >> duration_choice;
  // while( (duration_choice != 'R') || (duration_choice != 'B') ){
  //   cout << "Please press 'R' or 'B'." << endl;
  //   cin >> duration_choice;
  // }

  if(duration_choice == 'R'){
    cout << "How long would you like to have a break?" << endl
         << "This system takes 'minutes' for unit, please be awared when you key in the number. " << endl;
    int break_time = 0;
    cin >> break_time;
    cout << "You will take " << break_time << " mins break" << endl;
  }
  else if(duration_choice == 'B'){ 
    /* make the PC get into "sleep" status */ 
  }
}