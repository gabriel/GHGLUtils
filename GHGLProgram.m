//
//  GHGLProgram.m
//  Betelgeuse
//
//  Created by Gabriel Handford on 10/26/10.
//  Copyright 2010. All rights reserved.
//

#import "GHGLProgram.h"
#import "GHGLDefines.h"

@interface GHGLProgram ()
- (BOOL)_linkProgram:(GLuint)prog;
- (BOOL)_validateProgram:(GLuint)prog;
- (BOOL)_compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file includeFile:(NSString *)includeFile;
@end


@implementation GHGLProgram

@synthesize program=_program;

- (id)init {
  if ((self = [super init])) {
    _program = glCreateProgram();
  }
  return self;
}

- (id)initWithFragmentShader:(NSString *)fragmentShader vertexShader:(NSString *)vertexShader {
  if ((self = [self init])) {
    [self attachShadersWithFragmentShader:fragmentShader vertexShader:vertexShader fragmentShaderInclude:nil];
  }
  return self;
}

- (void)dealloc {
  if (_vertexShader) {
    glDeleteShader(_vertexShader);
    _vertexShader = 0;
  }
  if (_fragmentShader) {
    glDeleteShader(_fragmentShader);
    _fragmentShader = 0;
  }
  if (_program) {
    glDeleteProgram(_program);
    _program = 0;
  }
  [super dealloc];
}

+ (GHGLProgram *)compileAndLinkWithFragmentShader:(NSString *)fragmentShader vertexShader:(NSString *)vertexShader {
  GHGLProgram *program = [[GHGLProgram alloc] initWithFragmentShader:fragmentShader vertexShader:vertexShader];
  [program linkProgram];
  [program releaseShaders];
  return [program autorelease];
}

- (void)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file includeFile:(NSString *)includeFile {
  BOOL compiled = [self _compileShader:shader type:type file:file includeFile:includeFile];
  if (!compiled) [NSException raise:NSInternalInconsistencyException format:@"Failed to compile: %@", file];
}

- (BOOL)_compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file includeFile:(NSString *)includeFile {
  GLint status;
  
  NSString *source = [NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil];
  if (!source) {
    GHGLError(@"Failed to load shader at path: %@", file);
    return NO;
  }
  
  if (includeFile) {
    NSString *sourceInclude = [NSString stringWithContentsOfFile:includeFile encoding:NSUTF8StringEncoding error:nil];
    if (!sourceInclude) {
      GHGLError(@"Failed to load shader include at path: %@", includeFile);
      return NO;
    }
    source = [sourceInclude stringByAppendingString:source];
  }
  
  //GHGLDebug(@"%@:\n\n%@\n\n", file, source);
  
  *shader = glCreateShader(type);
  const GLchar *sourceChar = (GLchar *)[source UTF8String];
  glShaderSource(*shader, 1, &sourceChar, NULL);
  glCompileShader(*shader);
  
#if DEBUG
  GLint logLength;
  glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetShaderInfoLog(*shader, logLength, &logLength, log);
    GHGLDebug(@"%@:\n\n%@\n\n", file, source);
    GHGLError(@"Shader compile log:\n%s", log);
    free(log);
  }
#endif
  
  glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
  if (status == 0) {
    GHGLError(@"Shader compile error");
    glDeleteShader(*shader);
    return NO;
  }
  
  return YES;
}

- (void)linkProgram {
  if (!_program) [NSException raise:NSInternalInconsistencyException format:@"No program available"];
  BOOL linked = [self _linkProgram:_program];
  if (!linked) [NSException raise:NSInternalInconsistencyException format:@"Failed to link program"];
}

- (BOOL)_linkProgram:(GLuint)prog {
  GLint status;
  
  glLinkProgram(prog);
  
#if DEBUG
  GLint logLength;
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetProgramInfoLog(prog, logLength, &logLength, log);
    NSLog(@"Program link log:\n%s", log);
    free(log);
  }
#endif
  
  glGetProgramiv(prog, GL_LINK_STATUS, &status);
  if (status == 0)
    return NO;
  
  return YES;
}

- (void)validateProgram {
  if (!_program) [NSException raise:NSInternalInconsistencyException format:@"No program available"];
  BOOL validated = [self _validateProgram:_program];
  if (!validated) [NSException raise:NSInternalInconsistencyException format:@"Failed to validate program"];
}

- (BOOL)_validateProgram:(GLuint)program {
  GLint logLength, status;
  
  glValidateProgram(program);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetProgramInfoLog(program, logLength, &logLength, log);
    NSLog(@"Program validate log:\n%s", log);
    free(log);
  }
  
  glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
  if (status == 0)
    return NO;
  
  return YES;
}

- (void)attachShaders:(NSString *)name {
  return [self attachShadersWithFragmentShader:name vertexShader:name fragmentShaderInclude:nil];
}

- (void)attachShadersWithFragmentShader:(NSString *)fragmentShader vertexShader:(NSString *)vertexShader fragmentShaderInclude:(NSString *)fragmentShaderInclude {
  
  // Create and compile vertex shader.  
  NSString *vertexShaderPathname = [[NSBundle mainBundle] pathForResource:[vertexShader stringByDeletingPathExtension] ofType:[vertexShader pathExtension]];
  [self compileShader:&_vertexShader type:GL_VERTEX_SHADER file:vertexShaderPathname includeFile:nil];
  
  // Create and compile fragment shader.
  NSString *fragmentShaderPathname = [[NSBundle mainBundle] pathForResource:[fragmentShader stringByDeletingPathExtension] ofType:[fragmentShader pathExtension]];
  NSString *fragmentShaderIncludePathname = nil;
  if (fragmentShaderInclude) {
    fragmentShaderIncludePathname = [[NSBundle mainBundle] pathForResource:[fragmentShaderInclude stringByDeletingPathExtension] ofType:[fragmentShaderInclude pathExtension]];
  }
  [self compileShader:&_fragmentShader type:GL_FRAGMENT_SHADER file:fragmentShaderPathname includeFile:fragmentShaderIncludePathname];
  
  // Attach vertex shader to program.
  glAttachShader(_program, _vertexShader);
  
  // Attach fragment shader to program.
  glAttachShader(_program, _fragmentShader);  
}

- (void)releaseShaders {
  // Release vertex and fragment shaders.
  if (_vertexShader) {
    glDetachShader(_program, _vertexShader);
    glDeleteShader(_vertexShader);
    _vertexShader = 0;
  }
  if (_fragmentShader) {
    glDetachShader(_program, _fragmentShader);
    glDeleteShader(_fragmentShader);
    _fragmentShader = 0;
  }
}

@end
