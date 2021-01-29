//
//  main.cpp
//  Distance-Measure
//
//  Created by 蕭伊涵 on 2021/01/29.
//  Copyright © 2020 - 2021 YIHAN HSIAO. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "tools.h"

#include "firebase/app.h"
#include "firebase/auth.h"
#include "firebase/auth/user.h"
#include "firebase/firestore.h"
#include "firebase/util.h"

int main()
{
  firebase::firestore::Firestore *db;

  using firebase::Future;
  using firebase::firestore::DocumentReference;
  using firebase::firestore::Error;
  using firebase::firestore::FieldValue;

  Future<DocumentReference> user_ref =
      db->Collection("dmUsers").Add({
                                      {"id", FieldValue::Integer(5)},
                                      {"initDistance", FieldValue::Double(60.7)},
                                      {"name", FieldValue::String("test")}
                                    });

  user_ref.OnCompletion([](const Future<DocumentReference> &future) {
    if (future.error() == Error::kErrorOk)
    {
      std::cout << "DocumentSnapshot added with ID: " << future.result()->id()
                << '\n';
    }
    else
    {
      std::cout << "Error adding document: " << future.error_message() << '\n';
    }
  });
}