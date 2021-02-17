//
//  tools.cpp
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2020/11/16.
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
#include "tools.h"

using namespace std;
using json = nlohmann::json;
using namespace cv;
namespace fs = std::experimental::filesystem;

extern int errno;
#define MODE (S_IRWXU | S_IRWXG | S_IRWXO)


void Tools::Video_Capture(){
  //============= INITIALIZE VIDEO CAPTURE =================
  Mat frame;
  VideoCapture cap(0);

  int deviceID = 0;    // 0: open default camera
  int apiID = CAP_ANY; // 0: autodetect default API

  // check if succeed
  if (!cap.isOpened()){
    cerr << "ERROR! Unable to open camera\n";
  }

  //============= GRAB AND LOOP =================
  cout << "Start grabbing" << endl
       << "Press any key to terminate;" << endl;

  while (true){
    // check if succeed
    if (!cap.read(frame)){
      break;
    }

    // show live and wait for a key with timeout long enough to show images
    imshow("Demo", frame);

    if (waitKey(30) >= 0){
      break;
    }
  }
}

void Tools::ERROR_LOG( char const *msg ){
  perror( msg );
  exit( -1 );
}

void Tools::DistanceInit( Mat frame ){
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

bool Tools::CompareWithInit( Rect coordinate ){
  if( ( coordinate.width > obj_width + 10 ) && ( coordinate.height > obj_height + 10 ) ){
    return true;
  }
  else{
    return false;
  }
}

void Tools::Detection( Mat frame ){
  // declare vector for faces and eyes
  // vector<Rect> faces, eyes;
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
    
    // Point center;
    
    // draw rectangular on face
    rectangle( frame, faces[i], Scalar(255, 0, 0), 3, 8, 0 );
    if( CompareWithInit( faces[i] ) ){
      cout << "ALERRRRRRRRRRRRT" << endl;
    }
    
    // cout << "( " << faces[i].width << ", " << faces[i].height << " )  " << endl;
  
    // Mat faceROI = frame_gray( faces[i] );

    // // detection of eyes in the input image
    // eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 1, CV_HAL_BORDER_CONSTANT, Size(30, 30) );
    // // draw circles around eyes
    // for( size_t j = 0; j < eyes.size(); j++){
    //   center.x = cvRound( ( faces[i].x + eyes[j].x + eyes[j].width*0.5 ) );
    //   center.y = cvRound( ( faces[i].y + eyes[j].y + eyes[j].height*0.5 ) );
    //   radius = cvRound( ( eyes[j].width + eyes[j].height )*0.25 );
    //   circle( frame, center, radius, Scalar( 0, 255, 0 ), 3, 8, 0 );
    // }
  }
}

string Tools::time_capture(){

  // current date & time based on current system
  time_t now = time( 0 );

  // convert now to string form
  char* dt = ctime( &now );
  cout << "The local date & time is: " << dt << endl;

  return dt;

  // tm *ltm = localtime( &now );
  // cout << "Year: " << 1900 + ltm->tm_year << endl
  //      << "Month: " << 1 + ltm->tm_mon << endl
  //      << "Day: " << ltm->tm_mday << endl
  //      << "Time: " << 5 + ltm->tm_hour << ":"
  //      << 30 + ltm->tm_min << ":"
  //      << ltm->tm_sec << endl;

}

// Write into .json file
void Tools::recordData( user_data person ){

  json data;
  data["userid"] = person.userid;
  data["name"] = person.name;
  data["init_distance"] = person.init_distance;
  data["measure_distance"] = person.measure_distance;
  data["analysis_result"] = person.analysis_result;
  data["capture_time"] = time_capture();

  string JSON_file_name = "./datas/";
  JSON_file_name = JSON_file_name.append( data["name"] ) + "/";
  JSON_file_name = JSON_file_name.append( "1-2.json" );

  ofstream o( JSON_file_name );
  o << setw(2) << data << endl;

  cout << "SUCCESS writes into " << JSON_file_name << " file" << endl;

}

// Find if the directory exists
bool Tools::mk_dir( char *dir ){
  struct stat info;

  //NOT EXIST
  if( stat( dir, &info ) != 0 ){
    mkdir( dir, MODE );
    cout << "no exist";
    return false;
  }
  //EXIST
  else if( info.st_mode & S_IFDIR ){
    cout << "exist";
    return true;
  }
  //NO EXIST
  else{
    mkdir( dir, MODE );
    cout << "no exist";
    return false;
  }
}

// Execute Bash commands in c++ function
String executeCommand( const String cmd, int& out_exitStatus ){
  out_exitStatus = 0;
  auto pPipe = ::popen( cmd.c_str(), "r" );
  if( pPipe == nullptr ){
    throw runtime_error( "Cannot open pipe." );
  }

  array<char, 256> buffer;
  String result;

  while( not feof(pPipe) ){
    auto bytes = fread( buffer.data(), 1, buffer.size(), pPipe );
    result.append( buffer.data(), bytes );
  }

  auto rc = ::pclose( pPipe );
  if( WIFEXITED(rc) ){
    out_exitStatus = WEXITSTATUS(rc);
  }
  return result;
}

// Detect Screen Usage Time
double Tools::timeElapsed( clock_t start, clock_t end ){
  double duration;
  duration = (double)(end - start) / CLOCKS_PER_SEC;
  duration = duration/2;
  cout << "Screen Usage: " << duration << " secs" << endl;
  return duration;
}