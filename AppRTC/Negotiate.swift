//
//  Negotiate.swift
//  AppRTC
//
//  Created by Shawn Cicoria on 9/8/17.
//  Copyright © 2017 ISBX. All rights reserved.
//



import Foundation


class NegotiateHelper {
  func checkUrl(urlString: String, peerName: String, finished: @escaping
    ( _ isSuccess: Bool, _ body: String?) -> Void )
  {
    let urlPath: String = urlString.appending(peerName)
    let url: URL = URL(string: urlPath)!
    let request: URLRequest = URLRequest(url: url as URL)
    
    let session = Foundation.URLSession.shared
    
    var body: String?
    let task = session.dataTask(with: request as URLRequest, completionHandler:
    { (data, response, error) in
      if let error = error {
        print(error)
      }
      
      if let data = data {
        body = String(data: data, encoding: String.Encoding.utf8)
      }
      if let response = response {
        let httpResponse = response as! HTTPURLResponse
        if httpResponse.statusCode == 200 {
          finished(true, body)
        } else {
          finished(false, body)
        }
      }
    })
    task.resume()
  }
  
}
