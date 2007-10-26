#ifndef UTILS_H_
#define UTILS_H_

typedef struct _pointF {
	float x;
	float y;
	_pointF(float nx, float ny):x(nx),y(ny){}
} PointF;

typedef struct _pointI {
	int x;
	int y;
	_pointI(int nx, int ny):x(nx),y(ny){}
} PointI;

typedef struct _rect {
	int x;
	int y;
	int w;
	int h;
	_rect(int nx, int ny, int nw, int nh):x(nx),y(ny),w(nw),h(nh){}
} Rect;

typedef struct _transformMatrix {
	int x;
	int y;
	float rotation;
	float scalex;
	float scaley;
	_transformMatrix(int nx, int ny, float nrotate=0.0, float nscalex=1.0, float nscaley=1.0)
		:x(nx),y(ny),rotation(nrotate),scalex(nscalex),scaley(nscaley){}
} TransformMatrix;

///This function gets the first power of 2 >= the
///int that we pass it.
inline int nextPowerOfTwo ( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

inline unsigned int bitMask( unsigned int numBits ){
	unsigned int result = 0;
	while(numBits--){
		result = (result << 1) | 1;
	}
	return result;
}

#endif /*UTILS_H_*/
