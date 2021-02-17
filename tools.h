//
//  tools.h
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2020/11/16.
//  Copyright © 2020 - 2021 YIHAN HSIAO. All rights reserved.
//

#ifndef TOOLS_h
#define TOOLS_h

#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

struct user_data{
  int userid; //the count of the user
  string name;
  float init_distance;
  float measure_distance;
  bool analysis_result;
  string timeStamp;
  double user_init_duration;
};

class Tools{

  public:
    void Video_Capture(); // to open camera and start the video stream
    void ERROR_LOG( char const *msg ); // to print error message
    string time_capture();
    void recordData( user_data person );
    bool mk_dir( char *dir );
    String executeCommand( const String cmd, int& out_exitStatus );
};

#endif /* TOOLS_h */