//
//  ContentView.swift
//  dm-GUI
//
//  Created by 蕭伊涵 on 2021/02/25.
//

import SwiftUI

struct ContentView: View {
  @State private var timeElapsed = 30.0; // set initial time elapsed to 30 minutes
  
    var body: some View {
      VStack(alignment: .center) {
        Button(action: {
          print("click 'user1'")
        }) {
          Text("User")
        }
        HStack {
          Toggle(isOn: /*@START_MENU_TOKEN@*//*@PLACEHOLDER=Is On@*/.constant(true)/*@END_MENU_TOKEN@*/) {
            /*@START_MENU_TOKEN@*//*@PLACEHOLDER=Label@*/Text("Label")/*@END_MENU_TOKEN@*/
          }
          Text("時間提醒")
        }
        HStack {
          Text("每")
          Stepper(
            value: $timeElapsed, in: 10...60,
            step: 1){
            Text("\(timeElapsed, specifier:"%g")minutes")
          }
          Text("提醒我休息")
        }
        HStack {
          Toggle(isOn: /*@START_MENU_TOKEN@*//*@PLACEHOLDER=Is On@*/.constant(true)/*@END_MENU_TOKEN@*/) {
            /*@START_MENU_TOKEN@*//*@PLACEHOLDER=Label@*/Text("Label")/*@END_MENU_TOKEN@*/
          }
          Text("距離提醒")
        }
        Button(action: {
          print("click '重新設定與螢幕的距離'")
        }) {
          Text("重新設定與螢幕的距離")
        }
        Button(action: {
          print("click '重新設定臉'")
        }) {
          Text("重新設定臉")
        }
        .frame(minWidth: 300, maxWidth: .infinity, minHeight: 400, maxHeight: .infinity)
      }
      .padding(1.0)
        
    }
}


struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
