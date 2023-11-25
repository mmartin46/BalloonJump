
BOX2D = src/include/*.cpp config.cpp
SOUNDS = sounds/sounds.cpp
ENTITIES = entities/player.cpp entities/enemy.cpp
DLLS_PATH = dlls
FLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main # -mwindows
run:
	g++ -I src/include -L src/lib -L $(DLLS_PATH) -std=c++17 -o main.exe main.cpp ${ENTITIES} ${BOX2D}  ${SOUNDS} ${FLAGS}
	cp $(DLLS_PATH)/*.dll .
	./main
	rm *.dll
save:
	git add .
	git commit -m "$(msg)"
	git push -u origin