
BOX2D = src/include/*.cpp config.cpp
SOUNDS = sounds/sounds.cpp
ENTITIES = entities/player.cpp entities/enemy.cpp entities/enemyhandler.cpp
ALL_ELSE = tile.cpp map.cpp utils/background.cpp header.cpp game.cpp
FLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main # -mwindows
run:
	g++ -I src/include -L src/lib -std=c++17 -o main.exe ${ENTITIES} ${BOX2D}  ${SOUNDS} ${ALL_ELSE} main.cpp  ${FLAGS}
	./main
save:
	git add .
	git commit -m "$(msg)"
	git push -u origin
	