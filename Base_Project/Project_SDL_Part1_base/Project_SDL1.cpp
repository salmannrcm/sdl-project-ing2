// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"
#include <math.h>
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

// ######################  animal class implementation #######################""

  int animal::getRandomSpawn(POSITION pos) {
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  if (pos == POSITION::HORIZONTAL) {
    std::uniform_int_distribution<int> distr(frame_boundary,
                                             frame_width - frame_boundary);
    return distr(generator);
  } else {
    std::uniform_int_distribution<int> distr(frame_boundary,
                                             frame_height - frame_boundary);
    return distr(generator);
  }
}

animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr) {
  image_ptr_ = IMG_Load(file_path.c_str());
  window_surface_ptr_ = window_surface_ptr;
  position_.x = 0;
  position_.y = 0;
  position_.w = image_ptr_->w;
  position_.h = image_ptr_->h;

  targetX = 0, targetY = 0;
};

animal::~animal() { SDL_FreeSurface(image_ptr_); };

void animal::draw() {
  SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &position_);
};

int animal::random_moove(int delimitation, POSITION targ) {
  int min, max;
  if (targ == POSITION::HORIZONTAL) {
    if (position_.x - delimitation <= frame_boundary) {
      min = frame_boundary;
    } else {
      min = position_.x - delimitation;
    }

    if (position_.x + delimitation >= frame_width - frame_boundary) {
      max = frame_width - frame_boundary;
    } else {
      max = position_.x + delimitation;
    }
  } else {
    if (position_.y - delimitation <= frame_boundary) {
      min = frame_boundary;
    } else {
      min = position_.y - delimitation;
    }

    if (position_.y + delimitation >= frame_height - frame_boundary) {
      max = frame_height - frame_boundary;
    } else {
      max = position_.y + delimitation;
    }
  }
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr(min, max);
  return distr(generator);
}

bool animal::isOnTarget() {
  return (targetX - speed <= position_.x && position_.x <= targetX + speed) &&
         (targetY - speed <= position_.y && position_.y <= targetY + speed);
}

bool animal::isOnCouple(const std::shared_ptr<animal>& secondeAni) {
  float distance =
      sqrt(pow(secondeAni->position_.x - this->position_.x, 2) +
           pow(secondeAni->position_.y - this->position_.y, 2) * 1.0);
  return distance <= (secondeAni->position_.w / 2);
}

void animal::setSpeed(int newSpeed) { this->speed = newSpeed; }

void animal::runAway(const std::shared_ptr<animal>& seconde) {
  auto degree = SDL_atan2(position_.y - seconde->position_.y,
                          position_.x - seconde->position_.x);
  targetX = abs(position_.x + 100 * cos(-degree * 180 / PI));
  targetY = abs(position_.y + 100 * sin(-degree * 180 / PI));
  if (targetX < 0) {
    targetX = frame_boundary;
  }

  if (targetX > frame_width - position_.w) {
    targetX = frame_width - frame_boundary;
  }

  if (targetY < 0) {
    targetY = frame_boundary;
  }

  if (targetY > frame_height - position_.h) {
    targetY = frame_height - frame_boundary;
  }
}


//#################" sheep class implementation #########################

sheep::sheep(SDL_Surface* window_surface_ptr)
    : animal("../media/sheep.png", window_surface_ptr) {
  this->position_.x = getRandomSpawn(POSITION::HORIZONTAL);
  this->position_.y = getRandomSpawn(POSITION::VERTICAL);
  this->targetX = random_moove(100, POSITION::HORIZONTAL);
  this->targetY = random_moove(100, POSITION::VERTICAL);

}
void sheep::move() {
  if (position_.x > targetX) {
    position_.x--;
  } else if (position_.x < targetX) {
    position_.x++;
  }
  if (position_.y > targetY) {
    position_.y--;
  } else if (position_.y < targetY) {
    position_.y++;
  }
  if (targetX == position_.x && targetY == position_.y) {
    this->targetX = random_moove(100, POSITION::HORIZONTAL);
    this->targetY = random_moove(100, POSITION::VERTICAL);
  }
}

//#################" wolf class implementation #########################
wolf::wolf(SDL_Surface* window_surface_ptr)
    : animal("../media/wolf.png", window_surface_ptr) {
  this->position_.x = getRandomSpawn(POSITION::HORIZONTAL);
  this->position_.y = getRandomSpawn(POSITION::VERTICAL);
  this->targetX = random_moove(100,POSITION::HORIZONTAL);

  this->targetY = random_moove(100,POSITION::VERTICAL);

}

void::wolf::move() {
if (position_.x > targetX) {
    position_.x--;
  } else if (position_.x < targetX) {
    position_.x++;
  }
  if (position_.y > targetY) {
    position_.y--;
  } else if (position_.y < targetY) {
    position_.y++;
  }
  if (targetX == position_.x && targetY == position_.y) {
    this->targetX = random_moove(100, POSITION::HORIZONTAL);
    this->targetY = random_moove(100, POSITION::VERTICAL);
  }
}

//#################" ground class implementation #########################

ground::ground(SDL_Surface* window_surface_ptr) {
  window_surface_ptr_ = window_surface_ptr;
  animals_ = std::vector<std::shared_ptr<animal>>();
}

ground::~ground(){};

unsigned ground::countSheep(unsigned nbSheep) {
  for (auto aniIT = animals_.begin(); aniIT != animals_.end(); ++aniIT) {
    animal& ani = *aniIT.base()->get();
    if (typeid(ani) == typeid(sheep)) {
      nbSheep++;
    }
  }
  return nbSheep;
}

void ground::add_animal(std::shared_ptr<animal> NewAnimal) {
  animals_.push_back(NewAnimal);
}

void ground::update() {
  for (std::shared_ptr<animal> ani : animals_) {
    ani-> move();
    ani->draw();
  }
}

//#################" application class implementation #########################


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

  Ground_ = std::make_unique<ground>(window_surface_ptr_);

  for (size_t i = 0; i < n_sheep; i++)
    Ground_->add_animal(std::make_shared<sheep>(window_surface_ptr_));
  for (size_t i = 0; i < n_wolf; i++)
    Ground_->add_animal(std::make_shared<wolf>(window_surface_ptr_));
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
    Ground_->update();
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
  return NULL;
}
} // namespace
