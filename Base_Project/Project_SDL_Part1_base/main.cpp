#include "Project_SDL1.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

  std::cout << "Starting up the application" << std::endl;

  if (argc != 4)
    throw std::runtime_error("Need three arguments - "
                             "number of sheep, number of wolves, "
                             "simulation time in seconde\n");

  init();

  std::cout << "Done with initilization" << std::endl;

  application my_app(std::stoul(argv[1]), std::stoul(argv[2]));

  std::cout << "Created window" << std::endl;

  int retval = my_app.loop(std::stoul(argv[3]));

  std::cout << "Exiting application with code " << retval << std::endl;

  TTF_Quit();
  SDL_Quit();

  return retval;
}