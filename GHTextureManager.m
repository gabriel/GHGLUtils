//
//  GHTextureManager.m
//  GHGLUtils
//
//  Created by Gabriel Handford on 12/25/09.
//  Copyright 2009. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without
//  restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following
//  conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.
//

#import "GHTextureManager.h"


@implementation GHTextureManager

+ (GHTextureManager *)sharedManager {
  static GHTextureManager *SharedManager = NULL;
  if (SharedManager == NULL) {
    SharedManager = [[GHTextureManager alloc] init];
  }
  return SharedManager;
}

- (id)init {
  if ((self = [super init])) {
    _textures = [[NSMutableDictionary alloc] init];
  }
  return self;
}

- (void)dealloc {
  [_textures release];
  [super dealloc];
}

- (void)addTexture:(id<GHGLTexture>)texture forKey:(id)key {
  [_textures setObject:texture forKey:key];
}

- (id<GHGLTexture>)textureForKey:(id)key {
  return [_textures objectForKey:key];
}

- (id<GHGLTexture>)textureForResource:(NSString *)resource {
  id<GHGLTexture> texture = [_textures objectForKey:resource];
  if (texture) return texture;
  
  texture = [[GHGLTexture alloc] initWithName:resource];
  [self addTexture:texture forKey:resource];
  [texture release];
  return texture;
}

@end
