//
//  GHGLContext.m
//  Betelgeuse
//
//  Created by Gabriel Handford on 10/25/10.
//  Copyright 2010. All rights reserved.
//

#import "GHGLContext.h"
#import "GHGLDefines.h"


@implementation GHGLContext

@synthesize GLContext=_GLContext, GLProgram=_GLProgram;

- (id)init {
  return [self initWithAPI:kEAGLRenderingAPIOpenGLES2];
}

- (id)initWithAPI:(EAGLRenderingAPI)API {
  if ((self = [super init])) {
    _GLContext = [[EAGLContext alloc] initWithAPI:API];
    
    if (!_GLContext || ![EAGLContext setCurrentContext:_GLContext]) {
      [_GLContext release];
      _GLContext = nil;
      [NSException raise:NSInternalInconsistencyException format:@"Unable to set current context"];
    }
  }
  return self;
}

- (void)dealloc {
  [_GLProgram release];
  if ([EAGLContext currentContext] == _GLContext) 
		[EAGLContext setCurrentContext:nil];
	
	[_GLContext release];
  [super dealloc];
}  

- (GHGLProgram *)GLProgram {
  if (!_GLProgram) _GLProgram = [[GHGLProgram alloc] init];
  return _GLProgram;
}

- (BOOL)setCurrentContext {
  if (_GLContext)
    return [EAGLContext setCurrentContext:_GLContext];
  return NO;
}

@end
