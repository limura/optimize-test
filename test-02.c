#include <math.h>
#include <stdio.h>

struct GlobalData
{
	float x;
	float y;
	float p;
} global_data;

void stroke_add(float x, float y, float p)
{
	global_data.x += x;
	global_data.y += y;
	global_data.p += p;
}

void parent(
	float xp0, float xp1, float xp2, float xp3,
	float yp0, float yp1, float yp2, float yp3,
	float pp0, float pp1, float pp2, float pp3
	)
{
	float dx = xp1-xp2;
	float dy = yp1-yp2;
	float d =(float)sqrt(dx*dx+dy*dy); 
	int num = (int)ceil((double)(d*0.2d) + 0.5d);
	float x,y,p;
	float invertNum = 1.0f/num; // numの逆数を定義
	float deltaT = 0;
	float xv0 = (xp2-xp0)*0.5f;
	float xv1 = (xp3-xp1)*0.5f;
	float xfact1=((xp1 - xp2)*2.0f + xv0 + xv1);
	float xfact2=((xp2 - xp1)*3.0f - 2.0f * xv0 - xv1) ;
	float yv0 = (yp2-yp0)*0.5f;
	float yv1 = (yp3-yp1)*0.5f;
	float yfact1=((yp1 - yp2)*2.0f + yv0 + yv1);
	float yfact2=((yp2 - yp1)*3.0f - 2.0f * yv0 - yv1) ;
	float pv0 = (pp2-pp0)*0.5f;
	float pv1 = (pp3-pp1)*0.5f;
	float pfact1=((pp1 - pp2)*2.0f + pv0 + pv1);
	float pfact2=((pp2 - pp1)*3.0f - 2.0f * pv0 - pv1);
	float xfact1n =0;
	float yfact1n =0;
	float pfact1n =0;
	float xFact1step = xfact1 * invertNum;
	float yFact1step = yfact1 * invertNum;
	float pFact1step = pfact1 * invertNum;
	int i;
	for(i = 0; i < num; i++, deltaT+=invertNum){
		x =  ((xfact1n + xfact2) * deltaT + xv0) * deltaT + xp1;
		y =  ((yfact1n + yfact2) * deltaT + yv0) * deltaT + yp1;
		p =  ((pfact1n + pfact2) * deltaT + pv0) * deltaT + pp1;
		xfact1n += xFact1step;
		yfact1n += xFact1step;
		pfact1n += xFact1step;
		stroke_add(x,y,p);
	}
}

int main(int argc, char *argv[])
{
	int loop_count = atoi(argv[1]);
	int i;
	float lastX[4], lastY[4], lastP[4];
	for(i = 0; i < loop_count; ++i)
	{
		parent(
			lastX[0], lastX[1], lastX[2], lastX[3]
			, lastY[0], lastY[1], lastY[2], lastY[3]
			, lastP[0], lastP[1], lastP[2], lastP[3]
			);
	}
	return 0;
}
