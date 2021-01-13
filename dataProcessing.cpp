//
//  dataProcessing.cpp
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2020/12/23.
//  Copyright © 2020 YIHAN HSIAO. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <sstream>
#include <ctime>

#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include "dataProcessing.h"

using namespace std;
using json = nlohmann::json;
using namespace cv;

