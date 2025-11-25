# DAI Plugin for Brightcove Player SDK for iOS, version 7.2.0.8

## Installation

DAI Plugin for Brightcove Player SDK provides a dynamic library framework for installation.

The DAI plugin supports version 3.27.4 of the Google IMA SDK for iOS and version 4.15.1 of the Google IMA SDK for tvOS.

### CocoaPods

You can use [CocoaPods][cocoapods] to add the DAI Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-DAI` podspec [here][podspecs]. The pod will incorporate the correct version of IMA automatically.

CocoaPod Podfile example:

```bash
source 'https://github.com/CocoaPods/Specs'
source 'https://github.com/brightcove/BrightcoveSpecs.git'

platform :ios, '14.0'
use_frameworks!

target 'MyDAIPlayer' do
  pod 'Brightcove-Player-DAI'
end
```

### Manual

To add the DAI Plugin for Brightcove Player SDK to your project manually:

1. Download the [Brightcove Player SDK][bcovsdkrelease] framework.
1. Download the [DAI Plugin for Brightcove Player SDK][bcovedairelease] framework.
1. Download the [Google IMA][googleima] framework.
1. On the "General" tab of your application target, add the **dynamic** framework, `BrightcovePlayerSDK.framework` or `BrightcovePlayerSDK.xcframework`, from the Brightcove Player SDK download to the list of **Frameworks, Libraries, and Embedded Content**. The universal Framework and XCFramework are found in the ios directory of the download. The _Embed_ setting must be "_Embed & Sign_".
1. On the "General" tab of your application target, add `BrightcoveDAI.framework` or `BrightcoveDAI.xcframework` from the DAI Plugin for Brightcove Player SDK download to the list of **Frameworks, Libraries, and Embedded Content**. The _Embed_ setting must be "_Embed & Sign_".
1. On the "General" tab of your application target, add `GoogleInteractiveMediaAds.xcframework` from the Google IMA download to the list of **Frameworks, Libraries, and Embedded Content**. The _Embed_ setting for the XCFrameworks must be "_Embed & Sign_".
1. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the paths to the frameworks. This should have been done automatically unless the framework is stored under a different root directory than your project.
1. On the "Build Settings" tab of your application target:
    * Ensure that `-ObjC` has been added to the "Other Linker Flags" build setting.
1. (**Universal Framework** only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcoveDAI.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission.
1. (**Apple Silicon** only) On the "Build Settings" tab of your application target:
    * Ensure that `arm64` has been added to your "Excluded Architectures" build setting for `Any iOS Simulator SDK`.

### Swift Package Manager

To add the DAI Plugin for Brightcove Player SDK to your project with Swift Package Manager:

1. First [follow the steps][corespm] to add the Core XCFramework with Swift Package Mananger.
1. Add the DAI package to Swift Package Manager using `https://github.com/brightcove/brightcove-player-sdk-ios-dai.git`.
1. Download the [Google IMA][googleima] framework.
1. On the "General" tab of your application target, add `GoogleInteractiveMediaAds.xcframework` to the list of **Frameworks, Libraries, and Embedded Content**. The _Embed_ setting for the XCFrameworks must be "_Embed & Sign_".
1. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the paths to the frameworks. This should have been done automatically unless the framework is stored under a different root directory than your project.

[corespm]: https://github.com/brightcove/brightcove-player-sdk-ios#swift-package-manager

### Imports

The DAI Plugin for Brightcove Player SDK can be imported using:

```swift
import BrightcoveDAI
```

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/brightcove/BrightcoveSpecs/tree/master/Brightcove-Player-DAI
[bcovsdkrelease]: https://github.com/brightcove/brightcove-player-sdk-ios/tags
[bcovedairelease]: https://github.com/brightcove/brightcove-player-sdk-ios-dai/tags

## Quick Start

The BrightcoveDAI plugin is a bridge between [Google IMA iOS SDK v3][googleima] and the [Brightcove Player SDK for iOS][bcovsdk]. This snippet shows its basic usage with SourceID.

```swift
[1] let imaSettings = IMASettings()
    if let languageCode = NSLocale.current.languageCode {
        imaSettings.language = languageCode
    }

    let adsRenderingSettings = IMAAdsRenderingSettings()
    adsRenderingSettings.linkOpenerDelegate = self
    adsRenderingSettings.linkOpenerPresentingController = self

[2] let adsRequestPolicy = BCOVDAIAdsRequestPolicy.videoProperties()

    let sdkManager = BCOVPlayerSDKManager.sharedManager()
[3] let playbackController = sdkManager.createDAIPlaybackController(with: imaSettings,
                                                                    adsRenderingSettings: adsRenderingSettings,
                                                                    adsRequestPolicy: adsRequestPolicy,
                                                                    adContainer: playerView.contentOverlayView,
                                                                    viewController: self,
                                                                    companionSlots: nil,
                                                                    viewStrategy: nil)

    playbackController.delegate = self

    videoView.addSubview(playerView)

    let policyKey = "<your-policy-key>"
    let accountID = "<your-account-id>"
    let videoID = "<your-video-id>"
    let playbackService = BCOVPlaybackService(withAccountId: accountID,
                                              policyKey: policyKey)
    let configuration = [
        BCOVPlaybackService.ConfigurationKeyAssetID: videoID
    ]
    playbackService.findVideo(withConfiguration: configuration,
                              queryParameters: nil) { (video: BCOVVideo?,
                                                       jsonResponse: Any?,
                                                       error: Error?) in
        if let video {
            playbackController.setVideos([video])
            playbackController.play()
        }
    }
```

Breaking the code down into steps:

1. Create the same IMA settings, ads rendering settings that you would create if you were using Google's IMA iOS SDK directly.
1. BCOVDAIAdsRequestPolicy provides methods to specify DAI Streams for VOD and Live. Select the appropriate method to select your ads policy.
1. BrightcoveDAI adds some category methods to BCOVPlaybackManager. The first of these is `createDAIPlaybackController(with:adsRenderingSettings:adsRequestPolicy:adContainer:viewController:companionSlots:viewStrategy:)`. Use this method to create your playback controller.

[googleima]: https://developers.google.com/interactive-media-ads/docs/sdks/ios/download
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios

## Play and Pause

The Brightcove DAI Plugin implements custom play and pause logic to ensure the smoothest possible ad experience. Therefore, you will need to make sure that you use the play method on the `BCOVPlaybackController` or the `-[BCOVSessionProviderExtension dai_play]` or `-[BCOVSessionProviderExtension dai_pause]` ([BCOVSessionProviderExtension][BCOVDAIComponent]), and not the AVPlayer.

[BCOVDAIComponent]: https://github.com/brightcove/brightcove-player-sdk-ios-dai/blob/master/ios/BrightcoveDAI.framework/Headers/BCOVDAIComponent.h

## Seek Without Ads

Use `playbackController.seekWithoutAds(_,completionHandler:)` to resume playback at a specific time without forcing the user to watch ads scheduled before `seekToTime`.

In preparation for `seekWithoutAds(_,completionHandler:)`, disable `autoPlay` when setting up the `BCOVPlaybackController`.

Apple recommends waiting for the status of an AVPlayerItem to change to ready-to-play before using the AVPlayerItem. Therefore, call `seekWithoutAds(_,completionHandler:)` in the `kBCOVPlaybackSessionLifecycleEventReady` handler of the `playbackController:playbackSession:didReceiveLifecycleEvent` method of your `BCOVPlaybackControllerDelegate`.

```swift
func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didReceive lifecycleEvent: BCOVPlaybackSessionLifecycleEvent) {

    if kBCOVPlaybackSessionLifecycleEventReady == lifecycleEvent.eventType {

        // self.resumePlayback is a hypothetical instance variable used here for illustration.
        if resumePlayback {
            // seek without playing ads which are scheduled before the seek time, i.e. resume playback.
            controller.seekWithoutAds(seekWithoutAdsValue) { [weak playbackController, weak self] finished in
                if !finished {
                    print("seekWithoutAds failed to finish")
                }

                // fade out the shutter to reveal the player view.
                playbackController?.shutterFadeTime = 0.25
                playbackController?.shutter = false

                // turn off seek without ads - especially important if this player is being used with a playlist
                self?.resumePlayback = false
            }
        }

    }
}
```

The `shutter` and `shutterFadeTime` properties of the `BCOVPlaybackController` can be used along with `seekWithoutAds:completionHandler:` to hide frame-flicker which can occur as the AVPlayer loads assets. In your BCOVPlaybackController set-up code, enable the shutter to hide the player view:

```swift
let sdkManager = BCOVPlayerSDKManager.sharedManager()
let playbackController = sdkManager.createDAIPlaybackController(with: imaSettings,
                                                                adsRenderingSettings: adsRenderingSettings,
                                                                adsRequestPolicy: adsRequestPolicy,
                                                                adContainer: playerView.contentOverlayView,
                                                                viewController: self,
                                                                companionSlots: nil,
                                                                viewStrategy: nil)



playbackController.delegate = self

if resumePlayback {
    // set the shutter fade time to zero to hide the player view immediately.
    playbackController.shutterFadeTime = 0
    playbackController.shutter = true
    
    // disable autoPlay when resuming playback.
    playbackController.isAutoPlay = false
}
```

Note that when Seek Without Ads is used in your app, you might observe network traffic which normally occurs as part of setting up the DAI plugin. This traffic is necessary for proper plugin setup, and does not affect the Seek Without Ads functionality.

## Customizing Plugin Behavior

There are a couple of configuration points in BCOVDAI. You can combine BCOVDAI with another plugin for the Brightcove Player SDK for iOS, you can create a custom view strategy, and you can supply a custom ads request policy.

### Ads Request Policy for VOD and Live 

BCOVDAI gives you control over how ads requests are made, via the `BCOVDAIAdsRequestPolicy` class. The class provides factory methods for the supported policies. Once you obtain an instance of the correct policy, you need to provide it to the `BCOVPlayerSDKManager` to create a playback controller or a playback session provider. 

In Quick Start, an example using the SourceID is given. Here is a video properties.

```swift
    let imaSettings = IMASettings()
    imaSettings.ppid = "<publisher-id>"
    if let languageCode = NSLocale.current.languageCode {
        imaSettings.language = languageCode
    }

    let adsRenderingSettings = IMAAdsRenderingSettings()
    adsRenderingSettings.linkOpenerDelegate = self
    adsRenderingSettings.linkOpenerPresentingController = self

[1] let adsRequestPolicy = BCOVDAIAdsRequestPolicy.videoProperties()

    let sdkManager = BCOVPlayerSDKManager.sharedManager()
    let playbackController = sdkManager.createDAIPlaybackController(with: imaSettings,
                                                                    adsRenderingSettings: adsRenderingSettings,
                                                                    adsRequestPolicy: adsRequestPolicy,
                                                                    adContainer: playerView.contentOverlayView,
                                                                    viewController: self,
                                                                    companionSlots: nil,
                                                                    viewStrategy: nil)
```

Let's break this code down into steps, to make it a bit simpler to digest:

1. This example is the same as the one provided in the quick-start, except that we are now calling a different `BCOVDAIAdsRequestPolicy` policy method to specify that we want to use video properties.

BCOVDAIAdsRequestPolicy has two factory methods to generate ads request policy; one for VOD and one for Live. The factory method for VOD is described in more detail below:

* `BCOVDAIAdsRequestPolicy.videoProperties()`: This method returns an ads request policy which looks for the `kBCOVDAIVideoPropertiesKeySourceId` and `kBCOVDAIVideoPropertiesKeyVideoId` in each BCOVVideo's properties to determine the DAI Stream.

There is one factory method for Live. The Live policy is as follows:

* `BCOVDAIAdsRequestPolicy.videoPropertiesAssetKey()` This method returns an ads request policy that checks each BCOVVideo's properties for the key `kBCOVDAIVideoPropertiesKeyAssetKey` to determine the DAI Live Stream.

You can add properties to a video by using the `update:` method on the `BCOVVideo` object. The following example adds the properties needed for VOD:

```swift
func updateVideo(_ video: BCOVVideo) -> BCOVVideo {
    return video.update { (mutableVideo: BCOVMutableVideo?) in
        guard let mutableVideo else {
            return
        }

        var updatedProperties = mutableVideo.properties

        updatedProperties[kBCOVDAIVideoPropertiesKeySourceId] = "<source-id>"
        updatedProperties[kBCOVDAIVideoPropertiesKeyVideoId] = "<video-id>"

        mutableVideo.properties = updatedProperties
    }
}
```

### Modifying the IMAStreamRequest


The DAI Plugin passes an `IMAStreamRequest` object to a `BCOVDAIPlaybackSessionDelegate` immediately before calling `IMAAdsLoader -requestStreamWithRequest`, allowing the user to first modify the ads request. To receive the ads request callback, create an object that implements the `BCOVDAIPlaybackSessionDelegate` protocol.

```swift
import BrightcovePlayerSDK
import BrightcoveDAI
import GoogleInteractiveMediaAds

class ViewController1: UIView, BCOVDAIPlaybackSessionDelegate
```

Create a `BCOVDAISessionProvider` using either `createDAIPlaybackControllerWithSettings` or `createDAISessionProviderWithSettings`, and provide an NSDictionary of options with an entry having a key of `kBCOVDAIOptionDAIPlaybackSessionDelegateKey` and a value which is your delegate.

```swift
let daiSessionProviderOptions = [
    kBCOVDAIOptionDAIPlaybackSessionDelegateKey: self
]

let sdkManager = BCOVPlayerSDKManager.sharedManager()
let daiSessionProvider = sdkManager.createDAISessionProvider(with: imaSettings,
                                                             adsRenderingSettings: adsRenderingSettings,
                                                             adsRequestPolicy: adsRequestPolicy,
                                                             adContainer: playerView.contentOverlayView,
                                                             viewController: self,
                                                             companionSlots: nil,
                                                             upstreamSessionProvider: nil,
                                                             options: daiSessionProviderOptions)

```

Implement `willCallIMAAdsLoaderRequestAdsWithRequest:` in your `BCOVDAIPlaybackSessionDelegate`.

```swift
func willCallIMAAdsLoaderRequestAds(with adsRequest: IMAStreamRequest) {
    adsRequest.adTagParameters = [
        "rdp": "1",
        "myAdTargetingTest": "1"
    ]

    adsRequest.authToken = "<your-auth-token>"

    adsRequest.apiKey = "<your-api-key>"
}
```
    
### Composing Session Providers

If you are using more than one plugin to the Brightcove Player SDK for iOS that needs to create a customized playback controller, you must instead compose a chain of session providers and pass the final session provider to the `sdkManager.createPlaybackController(withSessionProvider:,viewStrategy:)` method.

When composing session providers, the session preloading can be enabled from [`BCOVBasicSessionProvider`][basicprovider]; however, preloading sessions with DAI plugin is **strongly discouraged** due to a bug in the Google IMA SDK when having multiple AVPlayers in memory.

[basicprovider]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/ios/BrightcovePlayerSDK.framework/Headers/BrightcovePlayerSDK-Swift.h#L407-L420

## Registering Ad Overlays

If you are placing any views over ads while they are playing, it is necceessary to register those views with the IMA SDK. Read the **Friendly obstructions** section of the [Open Measurement in the IMA SDK](https://developers.google.com/interactive-media-ads/docs/sdks/ios/omsdk) page for more information.

You can get the current IMAAdDisplayContainer object neccessary to register your overlays from the `playbackController:playbackSession:didEnterAdSequence:` delegate method of your BCOVPlaybackController instance. For example:

```swift
func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didEnter adSequence: BCOVAdSequence) {

    let props = session.video.properties
    if let adDisplayContainer = props[kBCOVDAIVideoPropertiesKeyAdDisplayContainer] as? IMAAdDisplayContainer{
        adDisplayContainer.register(adOverlayView)
    }

}
```

To unregister the obstructions when the ad sequence is finished, the `playbackController:playbackSession:didExitAdSequence:` delegate method of your BCOVPlaybackController instance can be used. For example:

```swift
func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didExitAdSequence adSequence: BCOVAdSequence) {
    let props = session.video.properties
    if let adDisplayContainer = props[kBCOVDAIVideoPropertiesKeyAdDisplayContainer] as? IMAAdDisplayContainer{
        adDisplayContainer.unregisterAllFriendlyObstructions()
    }
}
```

## AirPlay

**Brightcove does not offer support for using AirPlay with the DAI plugin.** Google’s IMA SDK does not fully support AirPlay, and the usage of AirPlay with the DAI plugin is not recommended at this time. There are likely to be unexpected behaviors and bugs for which no solution exists.

However, if you wish to use this functionality in your apps set `enableBackgroundPlayback` to `YES` on `IMASettings` along with enabling AirPlay on your `BCOVPlaybackController`. See the "_AirPlay_" section of the [Core SDK README](https://github.com/brightcove/brightcove-player-sdk-ios#airplay) for more information.

## Picture-in-Picture

The Brightcove DAI plugin can be used with Brightcove's Picture-in-Picture support.

Ads can not be started if Picture-in-Picture is active, however if an ad is playing when Picture-in-Picture begins it will continue playing in the Picture-in-Picture window. 

## AVPlayerViewController Support

### Displaying Ad UI

If you'd like to display your own Ad UI during ad playback you can use the `playbackController:playbackSession:didReceiveLifecycleEvent:` delegate method. Here is an example:

```swift
// MARK: BCOVPlaybackControllerDelegate
func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didReceive lifecycleEvent: BCOVPlaybackSessionLifecycleEvent) {

    if kBCOVDAILifecycleEventAdsManagerDidReceiveAdEvent == lifecycleEvent.eventType {
        if let adEvent = lifecycleEvent.properties["adEvent"] as? IMAAdEvent {
            switch adEvent.type {
                case .STARTED:
                    displayAdUI()
                case .COMPLETE:
                    hideAdUI()
                default:
                    break
            }
        }
    }
    
}
```

## Known Issues / Limitations

* The use of Brightcove VOD Streams are limited.
* DRM is not supported.

## Support

If you have questions, need help or want to provide feedback, please use the [Support Portal](https://supportportal.brightcove.com/s/login/) or contact your Account Manager.  To receive notification of new SDK software releases, subscribe to the Brightcove Native Player SDKs [Google Group](https://groups.google.com/g/brightcove-native-player-sdks).

