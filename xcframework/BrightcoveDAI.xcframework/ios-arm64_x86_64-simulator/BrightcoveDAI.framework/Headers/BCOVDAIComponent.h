//
// BCOVDAIComponent.h
// BrightcoveDAI
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

#import <BrightcovePlayerSDK/BrightcovePlayerSDK.h>

@class BCOVDAIAdsRequestPolicy;
@class IMAAdsRenderingSettings, IMASettings;


NS_ASSUME_NONNULL_BEGIN



/**
 * When DAI ads load successfully, the kBCOVIMALifecycleEventAdsLoaderLoaded
 * lifecycle event "properties" dictionary contains a reference to the IMAAdsLoader
 * which can be retrieved using the key kBCOVIMALifecycleEventPropertyKeyAdsManager.
 */
extern NSString * const kBCOVDAILifecycleEventAdsLoaderLoaded;
extern NSString * const kBCOVDAILifecycleEventAdsLoaderFailed;
extern NSString * const kBCOVDAILifecycleEventAdsManagerDidReceiveAdEvent;
extern NSString * const kBCOVDAILifecycleEventAdsManagerDidReceiveAdError;
extern NSString * const kBCOVDAILifecycleEventPropertyKeyAdsManager;
extern NSString * const kBCOVDAILifecycleEventPropertyKeyAdEvent;
extern NSString * const kBCOVDAILifecycleEventPropertyKeyAdError;

extern NSString * const kBCOVDAIAdPropertiesKeyIMAAdInstance;

/**
 * The user's option dictionary key to force non-personalized ads.
 */
extern NSString * const kBCOVDAIOptionDAINonPersonalizedAdsKey;

/**
 * The user's option dictionary key for  TFUA (`Tag For Users under the Age`)
 * parameter .
 */
extern NSString * const kBCOVDAIOptionDAITagForUsersKey;

/**
 * The user's option dictionary key to notify Google that RDP should be enabled
 * using Google's signal.
 */
extern NSString * const kBCOVDAIOptionDAIRDPGoogleKey;

/**
 * The user's option dictionary key to notify Google that RDP should be enabled
 * using IAB's signal.
 */
extern NSString * const kBCOVDAIOptionDAIRDPIABKey;

/**
 * The user's option dictionary key to serve limited ads.
 */
extern NSString * const kBCOVDAIOptionDAILimitedAdsKey;

/**
 * The dictionary key in the video properties for the VOD content source ID.
 */
extern NSString * const kBCOVDAIVideoPropertiesKeySourceId;

/**
 * The dictionary key in the video properties for the VOD video ID.
 */
extern NSString * const kBCOVDAIVideoPropertiesKeyVideoId;

/**
 * The dictionary key in the video properties for the LIVE stream asset key.
 */
extern NSString * const kBCOVDAIVideoPropertiesKeyAssetKey;

/**
 * The dictionary key in the video properties for the stream request API key.
 */
extern NSString * const kBCOVDAIVideoPropertiesKeyAPIKey;

/**
 * The dictionary key in the video properties for the stream request authorization token.
 */
extern NSString * const kBCOVDAIVideoPropertiesKeyAuthToken;

/**
 * The dictionary key in the video properties for the
 * IMA ad display container (IMAAdDisplayContainer *) associated with this ad.
 */
extern NSString * const kBCOVDAIVideoPropertiesKeyAdDisplayContainer;

/**
 * Category methods added to BCOVPlayerSDKManager to support DAI.
 */
@interface BCOVPlayerSDKManager (BCOVDAIAdditions)

/**
 * Creates and returns a new playback controller with the specified IMASettings
 * object, IMAAdsRenderingSettings object, view strategy, and ad container. The
 * returned playback controller will be configured with a DAI session provider.
 *
 * @param settings An IMASettings that will be used to configure any
 * IMAAdsLoader object used by the returned playback controller.
 * @param adsRenderingSettings An IMAAdsRenderingSettings that will be used to
 * configure any IMAAdsManager object used by the returned playback controller.
 * @param adsRequestPolicy BCOVDAIAdsRequestPolicy instance to generate
 * IMAStreamRequests for use by a given input playback session.
 * @param strategy A view strategy that determines the view for the returned
 * playback controller.
 * @param adContainer the view in which the ad will be displayed and the ad
 * information UI will be rendered.
 * @param adContainerViewController The view controller containing the ad container. If not provided
 * here, must be set on the IMAAdDisplayContainer before making an ads or stream request.
 * @param companionSlots the list of IMACompanionAdSlot instances. Can be nil
 * or empty.
 * @return A new playback controller with the specified parameters.
 */
- (id<BCOVPlaybackController>)createDAIPlaybackControllerWithSettings:(nullable IMASettings *)settings
                                                 adsRenderingSettings:(nullable IMAAdsRenderingSettings *)adsRenderingSettings
                                                     adsRequestPolicy:(nullable BCOVDAIAdsRequestPolicy *)adsRequestPolicy
                                                          adContainer:(UIView *)adContainer
                                                       viewController:(UIViewController *)adContainerViewController
                                                       companionSlots:(nullable NSArray *)companionSlots
                                                         viewStrategy:(nullable BCOVPlaybackControllerViewStrategy)strategy;

/**
 * Creates and returns a new playback controller with the specified IMASettings
 * object, IMAAdsRenderingSettings object, view strategy, and ad container. The
 * returned playback controller will be configured with a DAI session provider.
 *
 * @param settings An IMASettings that will be used to configure any
 * IMAAdsLoader object used by the returned playback controller.
 * @param adsRenderingSettings An IMAAdsRenderingSettings that will be used to
 * configure any IMAAdsManager object used by the returned playback controller.
 * @param adsRequestPolicy BCOVDAIAdsRequestPolicy instance to generate
 * IMAStreamRequests for use by a given input playback session.
 * @param strategy A view strategy that determines the view for the returned
 * playback controller.
 * @param adContainer the view in which the ad will be displayed and the ad
 * information UI will be rendered.
 * @param adContainerViewController The view controller containing the ad container. If not provided
 * here, must be set on the IMAAdDisplayContainer before making an ads or stream request.
 * @param companionSlots the list of IMACompanionAdSlot instances. Can be nil
 * or empty.
 * @param options An NSDictionary of DAI options. Can be nil or empty. The only
 *  valid option keys are
 *      kBCOVDAIOptionDAINonPersonalizedAdsKey
 *      kBCOVDAIOptionDAITagForUsersKey
 *      kBCOVDAIOptionDAIRDPGoogleKey
 *      kBCOVDAIOptionDAIRDPIABKey
 *      kBCOVDAIOptionDAILimitedAdsKey
 * @return A new playback controller with the specified parameters.
 */
- (id<BCOVPlaybackController>)createDAIPlaybackControllerWithSettings:(nullable IMASettings *)settings
                                                 adsRenderingSettings:(nullable IMAAdsRenderingSettings *)adsRenderingSettings
                                                     adsRequestPolicy:(nullable BCOVDAIAdsRequestPolicy *)adsRequestPolicy
                                                          adContainer:(UIView *)adContainer
                                                       viewController:(UIViewController *)adContainerViewController
                                                       companionSlots:(nullable NSArray *)companionSlots
                                                         viewStrategy:(nullable BCOVPlaybackControllerViewStrategy)strategy
                                                              options:(nullable NSDictionary *)options;

/**
 * Creates and returns a new BCOVDAISessionProvider with the specified
 * parameters.
 *
 * @param settings An IMASettings that will be used to configure any
 * IMAAdsLoader object used by the returned session provider.
 * @param adsRenderingSettings An IMAAdsRenderingSettings that will be used to
 * configure any IMAAdsManager object used by the returned session provider.
 * @param adsRequestPolicy BCOVDAIAdsRequestPolicy instance to generate
 * IMAStreamRequests for use by a given input playback session.
 * @param adContainer the view in which the ad will be displayed and the ad
 * information UI will be rendered.
 * @param adContainerViewController The view controller containing the ad container. If not provided
 * here, must be set on the IMAAdDisplayContainer before making an ads or stream request.
 * @param companionSlots the list of IMACompanionAdSlot instances. Can be nil
 * or empty.
 * @param provider A session provider to attach upstream and deliver playback
 * sessions to the returned session provider.
 * @return A new BCOVDAISessionProvider with the specified parameters.
 */
- (id<BCOVPlaybackSessionProvider>)createDAISessionProviderWithSettings:(nullable IMASettings *)settings
                                                   adsRenderingSettings:(nullable IMAAdsRenderingSettings *)adsRenderingSettings
                                                       adsRequestPolicy:(nullable BCOVDAIAdsRequestPolicy *)adsRequestPolicy
                                                            adContainer:(UIView *)adContainer
                                                         viewController:(UIViewController *)adContainerViewController
                                                         companionSlots:(nullable NSArray *)companionSlots
                                                upstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider;

/**
 * Creates and returns a new BCOVDAISessionProvider with the specified
 * parameters.
 *
 * @param settings An IMASettings that will be used to configure any
 * IMAAdsLoader object used by the returned session provider.
 * @param adsRenderingSettings An IMAAdsRenderingSettings that will be used to
 * configure any IMAAdsManager object used by the returned session provider.
 * @param adsRequestPolicy BCOVDAIAdsRequestPolicy instance to generate
 * IMAStreamRequests for use by a given input playback session.
 * @param adContainer the view in which the ad will be displayed and the ad
 * information UI will be rendered.
 * @param adContainerViewController The view controller containing the ad container. If not provided
 * here, must be set on the IMAAdDisplayContainer before making an ads or stream request.
 * @param companionSlots the list of IMACompanionAdSlot instances. Can be nil
 * or empty.
 * @param provider A session provider to attach upstream and deliver playback
 * sessions to the returned session provider.
 * @param options An NSDictionary of DAI options. Can be nil or empty. The only
 *  valid option keys are
 *      kBCOVDAIOptionDAINonPersonalizedAdsKey
 *      kBCOVDAIOptionDAITagForUsersKey
 *      kBCOVDAIOptionDAIRDPGoogleKey
 *      kBCOVDAIOptionDAIRDPIABKey
 *      kBCOVDAIOptionDAILimitedAdsKey
 * @return A new BCOVDAISessionProvider with the specified parameters.
 */
- (id<BCOVPlaybackSessionProvider>)createDAISessionProviderWithSettings:(nullable IMASettings *)settings
                                                   adsRenderingSettings:(nullable IMAAdsRenderingSettings *)adsRenderingSettings
                                                       adsRequestPolicy:(nullable BCOVDAIAdsRequestPolicy *)adsRequestPolicy
                                                            adContainer:(UIView *)adContainer
                                                         viewController:(UIViewController *)adContainerViewController
                                                         companionSlots:(nullable NSArray *)companionSlots
                                                upstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider
                                                                options:(nullable NSDictionary *)options;

@end


@interface BCOVDAIComponent : NSObject <BCOVComponent, BCOVComponentIdentity>

+ (NSString *)versionIdentifier;

@end


@interface BCOVSessionProviderExtension (BCOVDAIAdditions)

/**
 * Plays the video.
 *
 * On first play, before playing content, the session will process all preroll ads before starting
 * the content.
 */
- (void)dai_play;

/**
 * Pauses the video.
 */
- (void)dai_pause;

@end

NS_ASSUME_NONNULL_END
