//
//  GHGLTexture.h
//  GHGLUtils
//

//
// Modified from Jeff Lamarche's OpenGL ES Template for XCode
// http://iphonedevelopment.blogspot.com/2009/05/opengl-es-from-ground-up-table-of.html
//

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

#if TARGET_OS_IPHONE
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#endif

// For lightweight texture struct use Texture from GHGLCommon.h

@protocol GHGLTexture <NSObject>
@property (readonly, nonatomic) GLuint textureId;
- (void)bind;
@end

@interface GHGLTexture : NSObject <GHGLTexture> {
	GLuint _texture[1];
  GLuint _width;
  GLuint _height;
}

@property (readonly, nonatomic) GLuint textureId;
@property (readonly, nonatomic) GLuint width;
@property (readonly, nonatomic) GLuint height;

- (id)initWithName:(NSString *)name;
- (id)initWithName:(NSString *)name width:(GLuint)width height:(GLuint)height;

+ (void)useDefaultTexture;

- (void)drawInRect:(CGRect)rect;

@end
