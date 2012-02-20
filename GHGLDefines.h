//
// Modified from Jeff Lamarche's OpenGL ES Template for XCode
// http://iphonedevelopment.blogspot.com/2009/05/opengl-es-from-ground-up-table-of.html
//

#if DEBUG
#define GHGLDebug(...) NSLog(__VA_ARGS__)
#else
#define GHGLDebug(...) do { } while (0)
#endif

#define GHGLError(...) NSLog(__VA_ARGS__)

#if !TARGET_OS_IPHONE
#define GL_POINT_SPRITE_OES GL_POINT_SPRITE_ARB
#define GL_COORD_REPLACE_OES GL_COORD_REPLACE_ARB
#define GL_POINT_SIZE_ARRAY_OES GL_POINT_SIZE_ARRAY_APPLE
#define glPointSizePointerOES glPointSizePointerAPPLE
#endif

// How many times a second to refresh the screen
#if TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR
#define kRenderingFrequency             15.0
#define kInactiveRenderingFrequency     5.0
#else
#define kRenderingFrequency             30.0
#define kInactiveRenderingFrequency     3.0
#endif
// For setting up perspective, define near, far, and angle of view
#define kZNear                          0.01
#define kZFar                           1000.0
#define kFieldOfView                    45.0
// Defines whether to setup and use a depth buffer
#define USE_DEPTH_BUFFER                0
// Set to 1 if you want it to attempt to create a 2.0 context
#define kAttemptToUseOpenGLES2          0
// Macros
#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) / 180.0 * M_PI)

#define RANDOM_MINUS_1_TO_1() ((random() / (GLfloat)0x3fffffff)-1.0f)

// Macro which returns a random number between 0 and 1
#define RANDOM_0_TO_1() ((random() / (GLfloat)0x7fffffff))

#define GHGL_RANDOM_MINUS_1_TO_1() ((random() / (GLfloat)0x3fffffff)-1.0f)

// Macro which returns a random number between 0 and 1
#define GHGL_RANDOM_0_TO_1() ((random() / (GLfloat)0x7fffffff))

#define GHGL_RANDOM_0_TO(__MAX__) ((GLfloat)(arc4random() % (GLint)__MAX__))
#define GHGL_RANDOM_PLUS_MINUS(__MAX__) ((GLfloat)((arc4random() % (GLint)(__MAX__ * 2)) - __MAX__))

#define GHGL_RANDOM_INT_0_TO(__MAX__) (arc4random() % (GLint)__MAX__)


