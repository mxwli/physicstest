#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"

//CONSTANTS
#define sWidth 1000
#define sHeight 500
#define targetFPS 60
#define radius 30

//STRUCTS
struct ball {
	double x, y, xv, yv;
} aball, bball;

//FUNCTIONS
void clamp(double* val, double min, double max) {
	if(*val < min) *val = min;
	if(*val > max) *val = max;
}

int main() {
	srand(time(0));
	aball.x = rand()%sWidth, aball.y = rand()%sHeight, aball.xv = rand()%50+50, aball.yv = rand()%50+50;
	bball.x = rand()%sWidth, bball.y = rand()%sHeight, bball.xv = rand()%50+50, bball.yv = rand()%50+50;
	
	InitWindow(sWidth, sHeight, "Physics Exercise");
	SetTargetFPS(targetFPS);
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		
		//UPDATE FRAME
		double ft = GetFrameTime();
		aball.x += aball.xv*ft; aball.y += aball.yv*ft;
		bball.x += bball.xv*ft; bball.y += bball.yv*ft;
		
		//COLLISIONS WITH BORDERS
		if(aball.x-radius < 0 || aball.x+radius > sWidth) aball.xv *= -1;
		if(aball.y-radius < 0 || aball.y+radius > sHeight) aball.yv *= -1;
		if(bball.x-radius < 0 || bball.x+radius > sWidth) bball.xv *= -1;
		if(bball.x-radius < 0 || bball.x+radius > sHeight) bball.yv *= -1;
		
		clamp(&(aball.x), radius, sWidth-radius); clamp(&(aball.y), radius, sHeight-radius);
		clamp(&(bball.x), radius, sWidth-radius); clamp(&(bball.y), radius, sHeight-radius);
		
		//COLLISIONS WITH EACH OTHER
		
		
		//DRAWING
		DrawCircle(aball.x, aball.y, radius, BLUE);
		DrawCircle(bball.x, bball.y, radius, RED);
		
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
