//
//  GHGLContext.h
//  Betelgeuse
//
//  Created by Gabriel Handford on 10/25/10.
//  Copyright 2010. All rights reserved.
//


#import "GHGLProgram.h"

@interface GHGLContext : NSObject {
  GHGLProgram *_GLProgram;
	EAGLContext *_GLContext;
}

@property (readonly, nonatomic) EAGLContext *GLContext;
@property (readonly, nonatomic) GHGLProgram *GLProgram;

- (id)initWithAPI:(EAGLRenderingAPI)API;

- (BOOL)setCurrentContext;

@end
