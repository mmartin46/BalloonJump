
BOX2D = src/include/*.cpp 
CONFIGS = game/config.cpp
SOUNDS = sounds/sounds.cpp
ENTITIES = entities/*.cpp
ALL_ELSE = utils/*.cpp game/game.cpp
FLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main # -mwindows
run:
	g++ -I src/include -L src/lib -std=c++17 -o main.exe ${ENTITIES} ${BOX2D} ${CONFIGS}  ${SOUNDS} ${ALL_ELSE} main.cpp  ${FLAGS}
	./main
save:
	git add .
	git commit -m "$(msg)"
	git push -u origin
	