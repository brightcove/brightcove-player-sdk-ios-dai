//
// BCOVDAIAdsRequestPolicy.h
// BrightcoveDAI
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@interface BCOVDAIAdsRequestPolicy : NSObject

#pragma mark VOD

/**
 * Returns an ads request policy that checks each `BCOVVideo`'s properties for
 * `kBCOVDAIVideoPropertiesKeySourceId` and
 * `kBCOVDAIVideoPropertiesKeyVideoId` keys.
 * The values from the keys will be used to construct an `IMAStreamRequest`
 * for that playback session.
 *
 * Use this policy when you want the ability to specify a different VOD content
 * source and video IDs.
 *
 * @return An ads request policy that generates an `IMAStreamRequest`.
 */
+ (instancetype)videoPropertiesAdsRequestPolicy;


#pragma mark LIVE

/**
 * Returns an ads request policy that checks each `BCOVVideo`'s properties for
 * `kBCOVDAIVideoPropertiesKeyAssetKey`  key.
 * The value from the key will be used to construct an `IMAStreamRequest`
 * for that playback session.
 *
 * Use this policy for LIVE streams.
 *
 * @return An ads request policy that generates an `IMAStreamRequest`.
 */
+ (instancetype)videoPropertiesAssetKeyAdsRequestPolicy;

@end

NS_ASSUME_NONNULL_END
