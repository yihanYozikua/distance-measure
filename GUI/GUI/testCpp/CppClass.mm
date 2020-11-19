//
//  CppClass.m
//  GUI
//
//  Created by 蕭伊涵 on 2020/11/19.
//  Copyright © 2020 YIHAN HSIAO. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CppClass.h"

#import "CppClass.hpp"

@implementation OCClass

-(int) getYear {

    int y = CppClass(50).getYear();
    return y;

}

@end
