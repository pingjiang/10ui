#ifndef UTILS_H_
#define UTILS_H_

typedef struct pointF {
	float x;
	float y;
	pointF(float nx, float ny):x(nx),y(ny){}
} PointF;

typedef struct pointI {
	int x;
	int y;
	pointI(int nx, int ny):x(nx),y(ny){}
} PointI;

typedef struct color4F {
	float r;
	float g;
	float b;
	float alpha;
	color4F(float nr, float ng, float nb, float nalpha):r(nr),g(ng),b(nb),alpha(nalpha){}
} Color4;

typedef struct transformF {
	PointF translate;
	float rotate;
	float scalex;
	float scaley;
	transformF(PointF &ntranslate, float nrotate=0.0, float nscalex=1.0, float nscaley=1.0)
		:translate(ntranslate),rotate(nrotate),scalex(nscalex),scaley(nscaley){}
} TransformF;

///This function gets the first power of 2 >= the
///int that we pass it.
inline int nextPowerOfTwo ( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

#endif /*UTILS_H_*/
