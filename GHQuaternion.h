//
//  GHQuaternion.h
//  GHGLUtils
//
//  Created by Gabriel Handford on 9/7/09.
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

/*!
 References:
 http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=Quaternion_Camera_Class
 */

#import "GHGLCommon.h"


typedef struct {
	GLfloat	w;
	GLfloat	x;
	GLfloat	y;
	GLfloat z;
} Quaternion;


static inline Quaternion QuaternionMakeFromAxisAngle(GLfloat degrees, GLfloat x, GLfloat y, GLfloat z) {
	// First we want to convert the degrees to radians
	// since the angle is assumed to be in radians
	GLfloat angle = (degrees / 180.0f) * M_PI;
	
	// Here we calculate the sin( theta / 2) once for optimization
	GLfloat result = sinf(angle / 2.0f);
	
	Quaternion m;
	
	// Calcualte the w value by cos( theta / 2 )
	m.w = cosf(angle / 2.0f);
	
	// Calculate the x, y and z of the quaternion
	m.x = x * result;
	m.y = y * result;
	m.z = z * result;
	
	return m;
}

static inline void QuaternionCreateMatrix(Quaternion m, Matrix3D matrix) {	
	// First row
	matrix[0] = 1.0f - 2.0f * (m.y * m.y + m.z * m.z);
	matrix[1] = 2.0f * (m.x * m.y + m.z * m.w);
	matrix[2] = 2.0f * (m.x * m.z - m.y * m.w);
	matrix[3] = 0.0f;
	
	// Second row
	matrix[4] = 2.0f * (m.x * m.y - m.z * m.w);
	matrix[5] = 1.0f - 2.0f * (m.x * m.x + m.z * m.z);
	matrix[6] = 2.0f * (m.z * m.y + m.x * m.w);
	matrix[7] = 0.0f;
	
	// Third row
	matrix[8] = 2.0f * (m.x * m.z + m.y * m.w);
	matrix[9] = 2.0f * (m.y * m.z - m.x * m.w);
	matrix[10] = 1.0f - 2.0f * (m.x * m.x + m.y * m.y);
	matrix[11] = 0.0f;
	
	// Fourth row
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1.0f;
}

static inline Quaternion QuaternionMultiply(Quaternion m, Quaternion q) { 
	Quaternion r;
	
	r.w = m.w*q.w - m.x*q.x - m.y*q.y - m.z*q.z;
	r.x = m.w*q.x + m.x*q.w + m.y*q.z - m.z*q.y;
	r.y = m.w*q.y + m.y*q.w + m.z*q.x - m.x*q.z;
	r.z = m.w*q.z + m.z*q.w + m.x*q.y - m.y*q.x;
	
	return r;
}