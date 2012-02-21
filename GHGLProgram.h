//
//  GHGLProgram.h
//  GHGLUtils
//
//  Created by Gabriel Handford on 10/26/10.
//  Copyright 2010. All rights reserved.
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


@interface GHGLProgram : NSObject {
  GLuint _program;  
  GLuint _vertexShader;
  GLuint _fragmentShader;
}

@property (readonly, nonatomic) GLuint program;

/*!
 Create a shader program.
 @param fragmentShader Name of fragment shader file in main bundle, e.g. Shader.fs
 @param vertexShader Name of vertex shader file in main bundle, e.g. Shader.vs
 */
- (id)initWithFragmentShader:(NSString *)fragmentShader vertexShader:(NSString *)vertexShader;

/*!
 Compiles, attaches and links the shader program.
 @param fragmentShader Name of fragment shader file in main bundle, e.g. Shader.fs
 @param vertexShader Name of vertex shader file in main bundle, e.g. Shader.vs
 */
+ (GHGLProgram *)compileAndLinkWithFragmentShader:(NSString *)fragmentShader vertexShader:(NSString *)vertexShader;

/*!
 Compile shader.
 @param shader Shader
 @param type Shader type
 @param file Shader path (full)
 @param includeFile Include file to prepend, optional.
 */
- (void)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file includeFile:(NSString *)includeFile;

/*!
 Validate the program.
 */
- (void)validateProgram;

/*!
 Link the program.
 */
- (void)linkProgram;

/*!
 Compile and attach shaders.
 
 After linking program be sure to call releaseShaders.

 @param fragmentShader Name of fragment shader file in main bundle, e.g. Shader.fs
 @param vertexShader Name of vertex shader file in main bundle, e.g. Shader.vs
 */
- (void)attachShadersWithFragmentShader:(NSString *)fragmentShader vertexShader:(NSString *)vertexShader;

/*!
 Compile and attach shaders.
 
 After linking program be sure to call releaseShaders.
 
 @param fragmentShader Name of fragment shader file in main bundle, e.g. Shader.fs
 @param vertexShader Name of vertex shader file in main bundle, e.g. Shader.vs
 @param fragmentShaderInclude Optional. Name of fragment shader include file in main bundle. This file is prepended to the fragment shader file, e.g. Shader-Include.fs.
 */
- (void)attachShadersWithFragmentShader:(NSString *)fragmentShader vertexShader:(NSString *)vertexShader fragmentShaderInclude:(NSString *)fragmentShaderInclude;

/*!
 Release the shaders.
 */
- (void)releaseShaders;

@end
