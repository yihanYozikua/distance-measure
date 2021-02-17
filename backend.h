//
//  backend.h
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2021/02/17.
//  Copyright © 2020 - 2021 YIHAN HSIAO. All rights reserved.
//

#ifndef BACKEND_h
#define BACKEND_h

#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

class Backend{
  public:
    void DistanceInit( Mat frame );
    bool CompareWithInit( Rect coordinate );
    void Detection( Mat frame );
    double timeElapsed( clock_t start, clock_t end );
    void duration_choice();

    vector<Rect> faces, eyes;
    String face_cascade_name = "Source/haarcascade_eye_tree_eyeglasses.xml";
    String eyes_cascade_name = "Source/haarcascade_frontalface_default.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;

    int obj_width = 0, obj_height = 0;
    clock_t start, end;
    double init_duration = 15; // system default standard screen usage duration
    double duration; // duration to be calculated
};

#endif /* BACKEND_h */