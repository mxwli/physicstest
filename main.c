#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"
#include "complex.h"
#include "math.h"

#define sW 1000
#define sH 500
#define radius 90
#define sWP (sW-radius)
#define sHP (sH-radius)
#define velBase 300
#define velRang 100

struct ball {
	double complex pos, vel;
	//position, velocity
} ballA, ballB;

//returns the real with the smaller magnitude
double fabsmin(double a, double b) {
	return (fabs(a)<fabs(b))?a:b;
}

#define dtp(a, b) creal(a*conj(b))
#define csp(a, b) cimag(a*conj(b))
#define sqr(x) (x*x)
#define proj(a, b) (dtp(a, b)*b/sqr(cabs(b)))

int main() {
	srand(time(0));
	ballA.pos = rand()%sW + I * (rand()%sH);
	ballA.vel = cexp(I*rand())*(rand()%velRang+velBase);
	ballB.pos = rand()%sW + I * (rand()%sH);
	ballB.vel = cexp(I*rand())*(rand()%velRang+velBase);
	
	InitWindow(sW, sH, "physics test");
	SetTargetFPS(180);
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		
		DrawCircle(creal(ballA.pos), cimag(ballA.pos), radius, RED);
		DrawCircle(creal(ballB.pos), cimag(ballB.pos), radius, BLUE);
		
		ballA.pos += ballA.vel * GetFrameTime();
		ballB.pos += ballB.vel * GetFrameTime();
		
		if(creal(ballA.pos) < radius || creal(ballA.pos) > sWP) ballA.vel -= 2*creal(ballA.vel),  ballA.pos += fabsmin(radius-creal(ballA.pos), sWP-creal(ballA.pos));
		if(creal(ballB.pos) < radius || creal(ballB.pos) > sWP) ballB.vel -= 2*creal(ballB.vel),  ballB.pos += fabsmin(radius-creal(ballB.pos), sWP-creal(ballB.pos));
		if(cimag(ballA.pos) < radius || cimag(ballA.pos) > sHP) ballA.vel -= 2*I*cimag(ballA.vel),ballA.pos+=I*fabsmin(radius-cimag(ballA.pos), sHP-cimag(ballA.pos));
		if(cimag(ballB.pos) < radius || cimag(ballB.pos) > sHP) ballB.vel -= 2*I*cimag(ballB.vel),ballB.pos+=I*fabsmin(radius-cimag(ballB.pos), sHP-cimag(ballB.pos));
		
		if(cabs(ballA.pos-ballB.pos)<2*radius) {
			double complex interact = ballA.pos-ballB.pos;

			//here, we have two different ways to handle the interaction (neither of which are actually correct)
			
			//option one: handle the collision as if each object was bouncing off of an infinite mass wall
			double complex newVelA = ballA.vel - 2 * proj(ballA.vel, interact);
			double complex newVelB = ballB.vel - 2 * proj(ballB.vel, interact);
			
			//option two: handle the collision by exchanging velocity vectors
			newVelA = ballB.vel;
			newVelB = ballA.vel;
			
			ballA.vel = newVelA, ballB.vel = newVelB;
		}
		
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
