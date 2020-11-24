//
//  tools.h
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2020/11/16.
//  Copyright © 2020 YIHAN HSIAO. All rights reserved.
//

#ifndef TOOLS_h
#define TOOLS_h

#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

class Tools{

  public:
    void Video_Capture(); // to open camera and start the video stream
    void ERROR_LOG( char const *msg ); // to print error message
    void DistanceInit( Mat frame );
    bool CompareWithInit( Rect coordinate );
    void FaceDetection( Mat frame );
    

    vector<Rect> faces, eyes;
    String face_cascade_name = "Source/haarcascade_eye_tree_eyeglasses.xml";
    String eyes_cascade_name = "Source/haarcascade_frontalface_default.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;

    int obj_width = 0, obj_height = 0;
};

#endif /* TOOLS_h */