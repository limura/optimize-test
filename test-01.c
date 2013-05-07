#include <math.h>
#include <stdio.h>

struct GlobalData
{
	float x;
	float y;
	float p;
} global_data;

float catmullRom(float p0, float p1, float p2, float p3, float t)
{
	float v0 = (p2 - p0) / 2.0f ;
	float v1 = (p3 - p1) / 2.0f ;
	return
		((2.0f * p1 - 2.0f * p2) + v0 + v1) * t * t * t + 
		((-3.0f * p1 + 3.0f * p2) - 2.0F * v0 - v1) * t * t + v0 * t + p1;
}

float distance(float x1, float y1, float x2, float y2){
	return (float)sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void stroke_add(float x, float y, float p)
{
	global_data.x += x;
	global_data.y += y;
	global_data.p += p;
}

void parent(float* lastX, float* lastY, float* lastP)
{
	float d = distance(lastX[1], lastY[1], lastX[2], lastY[2]);
	int num = (int)ceil((double)(d / 5.0d) + 0.5d);
	float x,y,p;
	int i;
	for(i = 0; i < num; i++){
		x = catmullRom(lastX[0], lastX[1], lastX[2], lastX[3], (float)i / (float)num);
		y = catmullRom(lastY[0], lastY[1], lastY[2], lastY[3], (float)i / (float)num);
		p = catmullRom(lastP[0], lastP[1], lastP[2], lastP[3], (float)i / (float)num);
		stroke_add(x,y,p);
	}
}

int main(int argc, char *argv[])
{
	int loop_count = atoi(argv[1]);
	int i;
	global_data.x = global_data.y = global_data.z = 0.0f;
	float lastX[4] = { 0.1f, 0.2f, 0.3f, 0.4f };
	float lastY[4] = { 0.1f, 0.2f, 0.3f, 0.4f };
	float lastP[4] = { 0.1f, 0.2f, 0.3f, 0.4f };
	for(i = 0; i < loop_count; ++i)
	{
		parent(lastX, lastY, lastP);
	}
	printf("%f,%f,%f\n", global_data.x, global_data.y, global_data.p);
	return 0;
}

