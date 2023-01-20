# C++


[![Build passed](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

C++ SDL Project 

## Installation


Step 1. Install SDL_ttf library which allows font rendering 
(Make sure to "sudo apt-get update" if error occurs ) 

```sh
sudo apt-get install libsdl2--tf-dev
```

 Step 2. Build a /build directory under /Base_Project
 
```sh
cd Base_Prroject
$Base_Project : mkdir build
```

Step 3. From the /build directory execute "cmake .." 

```sh
$Base_Project : cd build
$Base_Project/build : cmake ..
```
Step 4. From the /build directory execute "make"

```sh
$Base_Project/build : make
```

Step 5. From the /build directory, execute the "SDL_part1" binary with the right parametres 

```sh
$Base_Project/build : ./Project_SDL_Part1_base/SDL_part1 <nb_sheep> <nb_wolf> <duration>"
```

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [markdown-it]: <https://github.com/markdown-it/markdown-it>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>

   [PlDb]: <https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md>
   [PlGh]: <https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md>
   [PlGd]: <https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md>
   [PlOd]: <https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md>
   [PlMe]: <https://github.com/joemccann/dillinger/tree/master/plugins/medium/README.md>
   [PlGa]: <https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md>
