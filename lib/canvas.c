
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten.h>


#define NUM_CIRCLES 500

struct Circle {
    int x;
    int y;
    int r;
    int cr;
    int cg;
    int cb;
};

struct CircleAnimationData {
    int x;
    int y;
    int r;
    int xv;
    int yv;
    int xd;
    int yd;
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData circlesData[NUM_CIRCLES];
// init circle edata nad start render - JS

int getRand(max) {
    return (rand() % max);
}

int main() {
    int i;
    int radius;
    srand(time(NULL));
    printf("init circles\n");


    for ( int i = 0; i < NUM_CIRCLES; i++) {
        radius = getRand(50);
        int x = getRand(1000) + radius;
        int y = getRand(1000) + radius;

        // animation data
        circlesData[i].x = x;
        circlesData[i].y = y;
        circlesData[i].r = radius;
        circlesData[i].xv = getRand(10) + 1;
        circlesData[i].yv = getRand(10) + 1;
        circlesData[i].xd = 1;
        circlesData[i].yd = 1;

        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = radius;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255);
    }

    EM_ASM({ render($0, $1);}, NUM_CIRCLES * 6, 6);

}

// return circles to JS
struct Circle * getCircles( int canvasWidth, int canvasHeight ) {

    for ( int i = 0; i < NUM_CIRCLES; i++) {
        if (( circlesData[i].x + circlesData[i].r) >= canvasWidth) {
            circlesData[i].xd = 0;
        }

        if (( circlesData[i].x - circlesData[i].r) <= 0) {
            circlesData[i].xd = 1;
        }

        if (( circlesData[i].y - circlesData[i].r) <= 0) {
            circlesData[i].yd = 1;
        }

        if (( circlesData[i].y + circlesData[i].r) >= canvasHeight) {
            circlesData[i].yd = 0;
        }

        if (circlesData[i].xd == 1) {
            circlesData[i].x += circlesData[i].xv;
        } else {
            circlesData[i].x =  circlesData[i].x - circlesData[i].xv;
        }

        if (circlesData[i].yd == 1) {
            circlesData[i].y += circlesData[i].yv;
        } else {
            circlesData[i].y = circlesData[i].y - circlesData[i].yv;
        }

        circles[i].x = circlesData[i].x;
        circles[i].y = circlesData[i].y;
    }

    return circles;
}