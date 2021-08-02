CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
DoodleJump: main.o velocity.o  player.o spring.o acceleration.o enemy.o platform.o camera.o rsdl.o DoodleJump.o outerior_functions.o
	g++ main.o DoodleJump.o velocity.o  outerior_functions.o player.o spring.o acceleration.o enemy.o platform.o camera.o rsdl.o -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer -o DoodleJump
rsdl.o: rsdl.cpp rsdl.hpp
	g++ -c rsdl.cpp -o rsdl.o
outerior_functions.o : outerior_functions.cpp headers.hpp
	g++ -c outerior_functions.cpp -o outerior_functions.o
DoodleJump.o :DoodleJump.cpp headers.hpp player.hpp spring.hpp platform.hpp enemy.hpp
	g++ -c DoodleJump.cpp -o DoodleJump.o
velocity.o : velocity.cpp velocity.hpp
	g++ -c velocity.cpp -o velocity.o
acceleration.o : acceleration.cpp acceleration.hpp
	g++ -c acceleration.cpp -o acceleration.o
spring.o : spring.cpp spring.hpp
	g++ -c spring.cpp -o spring.o
platform.o: platform.cpp platform.hpp
	g++ -c platform.cpp platform.hpp
player.o : player.cpp player.hpp rsdl.hpp acceleration.hpp velocity.hpp camera.hpp
	g++ -c player.cpp -o player.o
camera.o :camera.cpp camera.hpp rsdl.hpp
	g++ -c camera.cpp -o camera.o
enemy.o :enemy.cpp enemy.hpp rsdl.hpp
	g++ -c enemy.cpp -o enemy.o
.PHONY: clean
clean:
	rm *.o