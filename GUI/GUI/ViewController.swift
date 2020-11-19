//
//  ViewController.swift
//  GUI
//
//  Created by 蕭伊涵 on 2020/11/19.
//  Copyright © 2020 YIHAN HSIAO. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {
    
    @IBOutlet weak var textField: NSTextField!
    @IBOutlet weak var textLabel: NSTextField!
    
        override func viewDidLoad() {
            super.viewDidLoad()

            // Do any additional setup after loading the view.
        }

        override var representedObject: Any? {
            didSet {
                // Update the view, if already loaded.
            }
        }
    
    
    @IBAction func pressBtn(_ sender: Any) {
        var text = textField.stringValue
        if text.isEmpty{
            text = "World!"
        }
        let greeting = "Hello \(text)!"
        textLabel.stringValue = greeting
    }
    
    @IBAction func btRun(_ sender: Any) {

        let oc = OCClass()
        let y = oc.getYear()
        textLabel.stringValue = "The Year is \(y)"

    }
}

