#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Window* createWindow() {
    SDL_Window* window = SDL_CreateWindow("Raster Graphics Editor", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    return window;
}

int main(int argc, char* args[]) {
    if (!init()) {
        return -1;
    }

    SDL_Window* window = createWindow();
    if (window == NULL) {
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    // Initialize drawing color (default color)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Flag to track whether the mouse button is pressed
    bool isDrawing = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isDrawing = true;

                    // Get mouse coordinates
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    // Draw a point at the mouse position
                    SDL_RenderDrawPoint(renderer, mouseX, mouseY);
                }
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isDrawing = false;
                }
            } else if (e.type == SDL_MOUSEMOTION) {
                if (isDrawing) {
                    // Get mouse coordinates
                    int mouseX = e.motion.x;
                    int mouseY = e.motion.y;

                    // Draw a point at the mouse position
                    SDL_RenderDrawPoint(renderer, mouseX, mouseY);
                }
            }
        }

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
