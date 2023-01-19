Step 1. Install SDL_ttf library which allows font rendering (sudo apt-get install libsdl2--tf-dev). Make sure to "sudo apt-get update" if error occurs
Step 2. Build a /build directory under /Base_Project (mkdir /Base_Build/build)
Step 3. From the /build directory execute "cmake .."
Step 4. From the /build directory execute "make"
Step 5. From the /build directory, execute "./Project_SDL_Part1_base/SDL_part1 <nb_sheep> <nb_wolf> <duration>"
