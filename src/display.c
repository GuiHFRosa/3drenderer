#include "display.h"

SDL_Window* window;
SDL_Renderer *renderer;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL. \n");
    return false;
  }

  // Fullscreen resolution
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);
  window_width = display_mode.w;
  window_height = display_mode.h;

  // Create a SDL window
  window =
    SDL_CreateWindow(
      NULL,
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED,
      window_width, 
      window_height, 
      SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "Error creating SDL window \n");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  // Create a SDL renderer
  if (!renderer) {
    fprintf(stderr, "Error creating SDL renderer.\n");
    return false;
  }

  // Real fullscreen
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  return true;
}

void draw_grid(uint32_t color) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      if (y % 10 == 0 || x % 10 == 0) {
        color_buffer[(window_width * y) + x] = color;
      }
    }
  }
}

void draw_pixel(int x, int y, uint32_t color) {
  if (x < window_width && y < window_height) {
    color_buffer[(window_width * y) + x] = color;
  }
}

//TODO: Improve implement, I don't need iterare the entire buffer
void draw_rectangle(int x, int y, int width, int height, uint32_t color) {
  for (int yAxis = 0; yAxis < window_height; yAxis++) {
    for (int xAxis = 0; xAxis < window_width; xAxis++) {
      if (xAxis >= x && xAxis < x + width + 1 && yAxis >= y && yAxis < y + height + 1) {
        color_buffer[(window_width * yAxis) + xAxis] = color;
      }
    }
  }
}

void render_color_buffer(void) {
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (int)(window_width * sizeof(uint32_t)));
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      color_buffer[(window_width * y) + x] = color;
    }
  }
}

void destroy_window(void) {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
