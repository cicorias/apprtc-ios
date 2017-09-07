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
        return
    }
    
    func startSignalingIfReady() {
        print("This happened")
    }
    
//    - (void)startSignalingIfReady {
//    if (!_isTurnComplete || !self.isRegisteredWithRoomServer) {
//    return;
//    }
//    self.state = kARDAppClientStateConnected;
//    
//    // Create peer connection.
//    RTCMediaConstraints *constraints = [self defaultPeerConnectionConstraints];
//    _peerConnection = [_factory peerConnectionWithICEServers:_iceServers
//    constraints:constraints
//    delegate:self];
//    //RTCMediaStream *localStream = [self createLocalMediaStream];
//    //[_peerConnection addStream:localStream];
//    RTCDataChannelInit *datainit = [[RTCDataChannelInit alloc] init];
//    datainit.isNegotiated = YES;
//    datainit.isOrdered = YES;
//    datainit.maxRetransmits = 30;
//    datainit.maxRetransmitTimeMs = 30000;
//    datainit.streamId = 12;
//    self.dataChannel = [_peerConnection createDataChannelWithLabel:@"DataChannel-iphone" config:datainit];
//    self.dataChannel.delegate = self;
//    
//    if (_isInitiator) {
//    [self sendOffer];
//    } else {
//    [self waitForAnswer];
//    }
//    }

}
