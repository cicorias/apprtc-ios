//
//  MyARDAppClient.swift
//  AppRTC
//
//  Created by Michael Perel on 9/7/17.
//  Copyright © 2017 ISBX. All rights reserved.
//

//import UIKit
//import AVFoundation
//
@objc
class MyARDAppClient: ARDAppClient, RTCDataChannelDelegate  {
    
    
    func channelDidChangeState(_ channel: RTCDataChannel!) {
        print("CHANNEL STATE CHANGED")
    }
    
    func channel(_ channel: RTCDataChannel!, didReceiveMessageWith buffer: RTCDataBuffer!) {
        print("HELLO")
        return
    }
    
    override func startSignalingIfReady() {
        if (!self.isTurnComplete || !self.isRegisteredWithRoomServer) {
            return
        }
        self.setState(.disconnected)
        
        let constraints = self.defaultPeerConnectionConstraints()
        self.peerConnection = self.factory.peerConnection(withICEServers: self.iceServers as! [Any]!, constraints: constraints, delegate: self as! RTCPeerConnectionDelegate)
        
        //RTCMediaStream *localStream = [self createLocalMediaStream];
        //[_peerConnection addStream:localStream];
        let localStream = self.createLocalMediaStream()
        self.peerConnection.add(localStream)
        
        let datainit = RTCDataChannelInit()
        datainit.isNegotiated = true;
        datainit.isOrdered = true;
        datainit.maxRetransmits = 30;
        datainit.maxRetransmitTimeMs = 30000;
        datainit.streamId = 12;
        self.dataChannel = self.peerConnection.createDataChannel(withLabel: "DataChannel-iphone", config: datainit)
        self.dataChannel.delegate = self;
        
        if self.isInitiator {
            self.sendOffer()
        } else {
            self.waitForAnswer()
        }
    }
}


//- (void)startSignalingIfReady {
//    if (!_isTurnComplete || !self.isRegisteredWithRoomServer) {
//        return;
//    }
//    self.state = kARDAppClientStateConnected;
//    
//    // Create peer connection.
//    RTCMediaConstraints *constraints = [self defaultPeerConnectionConstraints];
//    _peerConnection = [_factory peerConnectionWithICEServers:_iceServers
//        constraints:constraints
//        delegate:self];
//    RTCMediaStream *localStream = [self createLocalMediaStream];
//    [_peerConnection addStream:localStream];
//    if (_isInitiator) {
//        [self sendOffer];
//    } else {
//        [self waitForAnswer];
//    }
//}
