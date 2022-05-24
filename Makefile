main: src/main.cpp src/game.cpp src/controls.cpp src/scenes.cpp src/utils.cpp
	g++ -I src src/*.cpp   -lGL -lglut -lGLU

# Danger: will delete the savefile as well as the executable.
clean:
	rm a.out savefile.save