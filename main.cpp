//
//  main.cpp
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2020/11/16.
//  Copyright © 2020 - 2021 YIHAN HSIAO. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "tools.h"
#include "backend.h"

// include Python
#define PY_SSIZE_T_CLEAN
#include <cpy/Python.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

  // Create a new object
  Tools tool;
  Backend backend;

  // Camera init
  VideoCapture cap = VideoCapture(0);
  Mat frame, img;

  // Load cascade classifiers
  if (!backend.face_cascade.load(backend.face_cascade_name))
  {
    tool.ERROR_LOG("ERROR loading face cascade");
  }
  if (!backend.eyes_cascade.load(backend.eyes_cascade_name))
  {
    tool.ERROR_LOG("ERROR loading eyes cascade");
  }

  // Key in the user name
  string user_name;
  cout << "User Name: ";
  cin >> user_name;
  cout << "Hi " << user_name << endl;

  // Python Test
  // system("python3 ./python/py-db.py");
  // Python Test END

  // After the camera is open
  if (cap.isOpened())
  {
    cout << "Face Detection Start..." << endl;

    // INIT
    while (true)
    {
      // Get frames from camera
      cap >> frame;
      if (frame.empty())
      {
        tool.ERROR_LOG("ERROR capture frame");
      }
      imshow("Init", frame);

      // Init
      char pressKey = (char)waitKey(1);
      if (pressKey == 13) 
      {
        cout << "START INIT" << endl;
        backend.DistanceInit(frame);

        // Confirm by pressing the "ENTER" key
        if (pressKey == 13)
        {
          cout << "width: " << backend.obj_width << endl;
          cout << "Height: " << backend.obj_height << endl;
          cout << "END INIT" << endl;
          break;
        }
      }
    }
    destroyWindow("Init");

    // start timeing
    backend.start = clock();
    // ANALYZE in real-time
    while (true)
    {
      // Get frames from camera
      cap >> frame;
      if (frame.empty())
      {
        tool.ERROR_LOG("ERROR capture frame");
      }

      // Keep monitoring the usage duration
      backend.end = clock();
      backend.duration = backend.timeElapsed(backend.start, backend.end);
      // ALERT when the duration is larger than the init duration
      if (backend.duration >= backend.init_duration){
        cout << "OUT OF DURATION || OUT OF DURATION || OUT OF DURATION || OUT OF DURATION" << endl;
        // give user choices to choose what he or she would like to do next
        backend.duration_choice();
        break;
      }

      // Start the eyes detection function
      backend.Detection(frame);
      imshow("Eyes Detection", frame);

      // If press ESC/ q/ Q, the system will calculate the elapsed time, and the process will end
      char ch = (char)waitKey(10);
      if (ch == 27 || ch == 'q' || ch == 'Q')
      {
        // calculate time
        backend.end = clock();
        backend.duration = backend.timeElapsed(backend.start, backend.end);
        backend.duration = 0;
        // end timing
        break;
      }
    }
  }
  else
  {
    tool.ERROR_LOG("ERROR open camera");
  }

  // Record user's datas into JSON files
  struct user_data person1;
  person1 = {0, user_name, 60.7, 60.0, false};
  // person1 = { 0, user_name,  init_distance, measure_distance, analysis_result};
  tool.recordData(person1);

  // String to char*
  string dir_str = "./datas/";
  dir_str = dir_str.append(person1.name) + "/";
  int count = dir_str.length();
  char dir[count + 1];
  strcpy(dir, dir_str.c_str());

  // Pass char to mk_dir() function to find if the specific dir exists
  cout << "Existing or not: " << tool.mk_dir(dir) << endl;

  // Count directories
  // int exitStatus = 0;
  // auto result = tool.executeCommand( "ls | wc -l", exitStatus );

  destroyAllWindows();
  return 0;
}
