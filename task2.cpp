
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
int radius=4;
int Ycenter=300;int Xcenter=500;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool isRunning;
int red = 0;
Uint32 startTime;
Uint32 currentTime;


bool initializeWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error: SDL initialization failed\nSDL Error: " << SDL_GetError() << endl;
        isRunning = false;
        return false;
    }

    window = SDL_CreateWindow("Task2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Error: Failed to create window\nSDL Error: " << SDL_GetError() << endl;
        isRunning = false;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << endl;
        isRunning = false;
        return false;
    }

    return true;
}

void Events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

void setup() {}

void increment() {
    radius += 2; // Increase radius at a faster rate
    if (radius >= 300)radius = 2;
}

void update() {
    currentTime = SDL_GetTicks();
    Uint32 passedTime = currentTime - startTime;
    if (passedTime >= 15) { // Update approximately every 16 milliseconds (60 FPS)
        increment();
        startTime = currentTime;
    }
}

void draw() {
    for (int m = -radius; m <= radius; m++) {
        for (int n = -radius; n <= radius; n++) {
            if (m * m + n * n <= radius * radius) {
                SDL_RenderDrawPoint(renderer, Xcenter + m, Ycenter + n);
            }
        }
    }
}

void render() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw the ball
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    draw();

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char** argv) {
    isRunning = initializeWindow();
    setup();
    startTime = SDL_GetTicks();

    while (isRunning) {
        Events();
        update();
        render();
    }

    clear();

    return 0;
}
