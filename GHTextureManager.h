//
//  GHTextureManager.h
//  Betelgeuse
//
//  Created by Gabriel Handford on 12/25/09.
//  Copyright 2009. All rights reserved.
//

#import "GHGLTexture.h"

@interface GHTextureManager : NSObject {
  NSMutableDictionary *_textures;
}

+ (GHTextureManager *)sharedManager;

- (void)addTexture:(id<GHGLTexture>)texture forKey:(id)key;

- (id<GHGLTexture>)textureForKey:(id)key;

- (id<GHGLTexture>)textureForResource:(NSString *)resource;

@end
