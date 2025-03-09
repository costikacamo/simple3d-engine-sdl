#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAP_WIDTH = 8;
const int MAP_HEIGHT = 8;

// Adjusted game constants for better responsiveness
const float ROTATION_SPEED = 180.0f;  // 180 degrees per second
const float MOVE_SPEED = 2.5f;        // 2.5 units per second
const float COLLISION_BUFFER = 0.2f;   // Buffer distance from walls
const float MAX_DELTA_TIME = 0.05f;    // Cap delta time to prevent jumps

// Simple 2D map (1 = wall, 0 = empty space)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,1,0,0,1,0,1},
    {1,0,1,0,0,1,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

// Player variables
float playerX = 3.5f, playerY = 3.5f;
float playerAngle = 0.0f;

void castRays(SDL_Renderer* renderer) {
    const float FOV = 60.0f;
    const float RAY_STEP = 0.05f; // Increased for better performance

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        float rayAngle = (playerAngle - FOV/2.0f) + (i / (float)SCREEN_WIDTH) * FOV;
        float rayX = playerX, rayY = playerY;
        
        // Pre-calculate ray direction
        float rayDirX = cos(rayAngle * M_PI / 180.0f);
        float rayDirY = sin(rayAngle * M_PI / 180.0f);

        while (true) {
            rayX += rayDirX * RAY_STEP;
            rayY += rayDirY * RAY_STEP;
            
            // Bounds checking
            int mapX = (int)rayX;
            int mapY = (int)rayY;
            
            if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT || map[mapY][mapX] == 1) {
                break;
            }
        }

        float distance = sqrt((rayX - playerX) * (rayX - playerX) + 
                            (rayY - playerY) * (rayY - playerY));
        distance *= cos((rayAngle - playerAngle) * M_PI / 180.0f);
        
        int lineHeight = (int)(SCREEN_HEIGHT / distance);
        lineHeight = std::min(lineHeight, SCREEN_HEIGHT);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 
                          i, 
                          (SCREEN_HEIGHT / 2) - (lineHeight / 2),
                          i, 
                          (SCREEN_HEIGHT / 2) + (lineHeight / 2));
    }
}

void handleInput(bool& running, float deltaTime) {
    // Cap delta time to prevent large jumps
    deltaTime = std::min(deltaTime, MAX_DELTA_TIME);
    
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // Handle escape key
    if (keystate[SDL_SCANCODE_ESCAPE]) {
        running = false;
        return;
    }

    // Rotation with adjusted speed
    if (keystate[SDL_SCANCODE_LEFT]) playerAngle -= ROTATION_SPEED * deltaTime;
    if (keystate[SDL_SCANCODE_RIGHT]) playerAngle += ROTATION_SPEED * deltaTime;

    // Keep angle in [0, 360) range
    playerAngle = fmod(playerAngle + 360.0f, 360.0f);

    // Pre-calculate trigonometric values
    float cosAngle = cos(playerAngle * M_PI / 180.0f);
    float sinAngle = sin(playerAngle * M_PI / 180.0f);

    // Movement direction
    float moveX = 0, moveY = 0;
    if (keystate[SDL_SCANCODE_UP]) {
        moveX += cosAngle;
        moveY += sinAngle;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        moveX -= cosAngle;
        moveY -= sinAngle;
    }

    // Normalize diagonal movement
    if (moveX != 0 && moveY != 0) {
        float length = sqrt(moveX * moveX + moveY * moveY);
        moveX /= length;
        moveY /= length;
    }

    // Apply movement speed and delta time
    moveX *= MOVE_SPEED * deltaTime;
    moveY *= MOVE_SPEED * deltaTime;

    // Collision detection with buffer
    float newX = playerX + moveX;
    float newY = playerY + moveY;
    
    if (map[(int)(playerY)][(int)(newX + (moveX > 0 ? COLLISION_BUFFER : -COLLISION_BUFFER))] == 0) {
        playerX = newX;
    }
    if (map[(int)(newY + (moveY > 0 ? COLLISION_BUFFER : -COLLISION_BUFFER))][(int)(playerX)] == 0) {
        playerY = newY;
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raycasting Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    
    Uint32 lastTime = SDL_GetTicks();
    
    while (running) {
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        handleInput(running, deltaTime);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        castRays(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
