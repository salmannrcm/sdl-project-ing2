// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}

application::application(unsigned n_sheep, unsigned n_wolf) {
  // Create an application window with the following settings:
  window_ptr_ = SDL_CreateWindow("An SDL2 window",        // window title
                                 SDL_WINDOWPOS_UNDEFINED, // initial x position
                                 SDL_WINDOWPOS_UNDEFINED, // initial y position
                                 frame_width,             // width, in pixels
                                 frame_height,            // height, in pixels
                                 SDL_WINDOW_SHOWN         // flags - see below
  );

  window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

}

application::~application() {
  // Close and destroy the window
  SDL_DestroyWindow(window_ptr_);
}

int application::loop(unsigned period) {
  SDL_Rect windRect = SDL_Rect{0, 0, frame_width, frame_height};
  
  while (period * 1000 >= SDL_GetTicks()) {

    SDL_FillRect(window_surface_ptr_, &windRect,
                 SDL_MapRGB(window_surface_ptr_->format, 0, 255, 0));

    SDL_PollEvent(&window_event_);

    if (window_event_.type == SDL_QUIT ||
        window_event_.type == SDL_WINDOWEVENT &&
            window_event_.window.event == SDL_WINDOWEVENT_CLOSE)
      break;

    SDL_UpdateWindowSurface(window_ptr_);
    
    SDL_Delay(frame_time * 1000); // Pause execution for framerate milliseconds
  }

  return 1;
}

namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Surface* load_surface_for(const std::string& path,
                              SDL_Surface* window_surface_ptr) {

  // Helper function to load a png for a specific surface
  // See SDL_ConvertSurface
}
} // namespace
