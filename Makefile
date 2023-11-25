
BOX2D = src/include/*.cpp config.cpp
SOUNDS = sounds/sounds.cpp
ENTITIES = entities/player.cpp entities/enemy.cpp
FLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main # -mwindows
run:
	g++ -I src/include -L src/lib -std=c++17 -o main.exe main.cpp ${ENTITIES} ${BOX2D}  ${SOUNDS} ${FLAGS}
	./main
save:
	git add .
	git commit -m "$(msg)"
	git push -u origin
	