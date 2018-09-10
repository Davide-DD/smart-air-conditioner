//
//  ViewController.swift
//  SmartHome
//
//  Created by Davide Di Donato on 03/08/18.
//

import UIKit
import Alamofire

class ViewController: UIViewController {
    
    let address : String = "http://192.168.43.28:5000"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    @IBAction func toggle(_ sender: Any) {
        let parameters: Parameters = [
            "command": 3
        ]
        Alamofire.request(address + "/command", method: .post, parameters: parameters)
    }
    

}

