﻿// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once
#define PI 3.14159265
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>


// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

enum POSITION { HORIZONTAL, VERTICAL };

class animal {
private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
  // todo: Attribute(s) to define its position
protected:
  int speed;
  bool isOnTarget();
  int targetX, targetY;
  int getRandomSpawn(POSITION dir);
  int random_moove(int delimitation, POSITION targ);
public:
  SDL_Rect position_;
  animal(const std::string& file_path, SDL_Surface* window_surface_ptr);
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
  ~animal(); // todo: Use the destructor to release memory and "clean up
               // behind you"

  void draw(); // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

  virtual void move() = 0; // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
  bool isOnCouple(const std::shared_ptr<animal>&);
  void setSpeed(int newSpeed);
  void runAway(const std::shared_ptr<animal>&);

};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {
public:
  sheep(SDL_Surface* window_surface_ptr);
  ~sheep() {}
  void move();
  // Dtor
  // implement functions that are purely virtual in base class
};

class wolf : public animal {
public:
  wolf(SDL_Surface* window_surface_ptr);
  ~wolf() {}
  void move();
};
// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;

  // Some attribute to store all the wolves and sheep
  std::vector<std::shared_ptr<animal>> animals_;

public:
  ground(SDL_Surface* window_surface_ptr); // todo: Ctor
  ~ground(); //
  // Add an animal
  void add_animal(std::shared_ptr<animal> NewAnimal);
  unsigned countSheep(unsigned nbSheep);
  void update(); // todo: "refresh the screen": Move animals and draw them
  // Possibly other methods, depends on your implementation
};

// The application class, which is in charge of generating the window
class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;

  std::unique_ptr<ground> Ground_;

public:
  application(unsigned n_sheep, unsigned n_wolf); // Ctor
  ~application();                                 // dtor

  int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};
