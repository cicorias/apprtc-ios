/*
 * libjingle
 * Copyright 2014, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>

//#import "RTCVideoTrack.h"
/*Start exposing imports*/
#import <AVFoundation/AVFoundation.h>

#import "ARDMessageResponse.h"
#import "ARDRegisterResponse.h"
#import "ARDSignalingMessage.h"
#import "ARDUtilities.h"
#import "ARDWebSocketChannel.h"
#import "RTCICECandidate+JSON.h"
#import "RTCICEServer+JSON.h"
#import "RTCMediaConstraints.h"
#import "RTCMediaStream.h"
#import "RTCPair.h"
#import "RTCPeerConnection.h"
#import "RTCPeerConnectionDelegate.h"
#import "RTCPeerConnectionFactory.h"
#import "RTCSessionDescription+JSON.h"
#import "RTCSessionDescriptionDelegate.h"
#import "RTCVideoCapturer.h"
#import "RTCVideoTrack.h"
/*not in implementation file */
#import "RTCDataChannel.h"
#import "RTCMediaConstraints.h"
/*in implementation file */
/*End exposing imports*/

typedef NS_ENUM(NSInteger, ARDAppClientState) {
  // Disconnected from servers.
  kARDAppClientStateDisconnected,
  // Connecting to servers.
  kARDAppClientStateConnecting,
  // Connected to servers.
  kARDAppClientStateConnected,
};

@class ARDAppClient;
@protocol ARDAppClientDelegate <NSObject>

- (void)appClient:(ARDAppClient *)client
    didChangeState:(ARDAppClientState)state;

- (void)appClient:(ARDAppClient *)client
    didReceiveLocalVideoTrack:(RTCVideoTrack *)localVideoTrack;

- (void)appClient:(ARDAppClient *)client
    didReceiveRemoteVideoTrack:(RTCVideoTrack *)remoteVideoTrack;

- (void)appClient:(ARDAppClient *)client
         didError:(NSError *)error;

@end

// Handles connections to the AppRTC server for a given room.
@interface ARDAppClient : NSObject

@property(nonatomic, readonly) ARDAppClientState state;
@property(nonatomic, weak) id<ARDAppClientDelegate> delegate;
@property(nonatomic, strong) NSString *serverHostUrl;

/*Start exposing private properties */
@property(nonatomic, strong) ARDWebSocketChannel *channel;
@property(nonatomic, strong) RTCPeerConnection *peerConnection;
@property(nonatomic, strong) RTCPeerConnectionFactory *factory;
@property(nonatomic, strong) NSMutableArray *messageQueue;

@property(nonatomic, assign) BOOL isTurnComplete;
@property(nonatomic, assign) BOOL hasReceivedSdp;
@property(nonatomic, readonly) BOOL isRegisteredWithRoomServer;

@property(nonatomic, strong) NSString *roomId;
@property(nonatomic, strong) NSString *clientId;
@property(nonatomic, assign) BOOL isInitiator;
@property(nonatomic, assign) BOOL isSpeakerEnabled;
@property(nonatomic, strong) NSMutableArray *iceServers;
@property(nonatomic, strong) NSURL *webSocketURL;
@property(nonatomic, strong) NSURL *webSocketRestURL;
@property(nonatomic, strong) RTCAudioTrack *defaultAudioTrack;
@property(nonatomic, strong) RTCVideoTrack *defaultVideoTrack;
@property(nonatomic, strong) RTCDataChannel *dataChannel;
/*End exposing private properties */

- (instancetype)initWithDelegate:(id<ARDAppClientDelegate>)delegate;

// Establishes a connection with the AppRTC servers for the given room id.
// TODO(tkchin): provide available keys/values for options. This will be used
// for call configurations such as overriding server choice, specifying codecs
// and so on.
- (void)connectToRoomWithId:(NSString *)roomId
                    options:(NSDictionary *)options;

// Mute and unmute Audio-In
//- (void)muteAudioIn;
//- (void)unmuteAudioIn;
//
//// Mute and unmute Video-In
//- (void)muteVideoIn;
//- (void)unmuteVideoIn;
//
//// Enabling / Disabling Speakerphone
//- (void)enableSpeaker;
//- (void)disableSpeaker;
//
//// Swap camera functionality
//- (void)swapCameraToFront;
//- (void)swapCameraToBack;
//
//// Disconnects from the AppRTC servers and any connected clients.
//- (void)disconnect;

/*Start exposing private methods*/
//- (RTCMediaConstraints *)defaultPeerConnectionConstraints;
//- (instancetype)initWithDelegate:(id<ARDAppClientDelegate>)delegate;

- (void)dealloc;

- (void)orientationChanged:(NSNotification *)notification;
- (void)setState:(ARDAppClientState)state;

//- (void)connectToRoomWithId:(NSString *)roomId
//                    options:(NSDictionary *)options;
- (void)disconnect;

- (void)channel:(ARDWebSocketChannel *)channel
didReceiveMessage:(ARDSignalingMessage *)message;

- (void)channel:(ARDWebSocketChannel *)channel
 didChangeState:(ARDWebSocketChannelState)state;

- (void)peerConnection:(RTCPeerConnection *)peerConnection
 signalingStateChanged:(RTCSignalingState)stateChanged;

- (void)peerConnection:(RTCPeerConnection *)peerConnection
           addedStream:(RTCMediaStream *)stream;

- (void)peerConnection:(RTCPeerConnection *)peerConnection
         removedStream:(RTCMediaStream *)stream;

- (void)peerConnectionOnRenegotiationNeeded:
(RTCPeerConnection *)peerConnection;

- (void)peerConnection:(RTCPeerConnection *)peerConnection
  iceConnectionChanged:(RTCICEConnectionState)newState;

- (void)peerConnection:(RTCPeerConnection *)peerConnection
   iceGatheringChanged:(RTCICEGatheringState)newState;

- (void)peerConnection:(RTCPeerConnection *)peerConnection
       gotICECandidate:(RTCICECandidate *)candidate;

- (void)peerConnection:(RTCPeerConnection*)peerConnection
    didOpenDataChannel:(RTCDataChannel*)dataChannel;

#pragma mark - RTCSessionDescriptionDelegate

- (void)peerConnection:(RTCPeerConnection *)peerConnection
didCreateSessionDescription:(RTCSessionDescription *)sdp
                 error:(NSError *)error;

- (void)peerConnection:(RTCPeerConnection *)peerConnection
didSetSessionDescriptionWithError:(NSError *)error;

- (BOOL)isRegisteredWithRoomServer;
- (void)startSignalingIfReady;

- (void)sendOffer;
- (void)waitForAnswer;
- (void)drainMessageQueueIfReady;
- (void)processSignalingMessage:(ARDSignalingMessage *)message;
- (void)sendSignalingMessage:(ARDSignalingMessage *)message;
- (RTCVideoTrack *)createLocalVideoTrack;
- (RTCMediaStream *)createLocalMediaStream;

- (void)requestTURNServersWithURL:(NSURL *)requestURL
                completionHandler:(void (^)(NSArray *turnServers))completionHandler;

- (void)registerWithRoomServerForRoomId:(NSString *)roomId
                      completionHandler:(void (^)(ARDRegisterResponse *))completionHandler;
- (void)sendSignalingMessageToRoomServer:(ARDSignalingMessage *)message
                       completionHandler:(void (^)(ARDMessageResponse *))completionHandler;
- (void)unregisterWithRoomServer;

- (NSError *)roomServerNetworkError;
- (void)registerWithColliderIfReady;

- (void)sendSignalingMessageToCollider:(ARDSignalingMessage *)message;
- (RTCMediaConstraints *)defaultMediaStreamConstraints;

- (RTCMediaConstraints *)defaultAnswerConstraints;
- (RTCMediaConstraints *)defaultOfferConstraints;
- (RTCMediaConstraints *)defaultPeerConnectionConstraints;
- (RTCICEServer *)defaultSTUNServer;
- (void)muteAudioIn;
- (void)unmuteAudioIn;
- (void)muteVideoIn;
- (void)unmuteVideoIn;
- (RTCVideoTrack *)createLocalVideoTrackBackCamera;
- (void)swapCameraToFront;
- (void)swapCameraToBack;
- (void)enableSpeaker;
- (void)disableSpeaker;
/*End exposing private methods*/

@end
