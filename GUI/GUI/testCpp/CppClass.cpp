//
//  CppClass.cpp
//  GUI
//
//  Created by 蕭伊涵 on 2020/11/19.
//  Copyright © 2020 YIHAN HSIAO. All rights reserved.
//

#include "CppClass.hpp"

CppClass::CppClass(int i){
    age = i;
}

int CppClass::getYear(){
    return age + 2000;
}
