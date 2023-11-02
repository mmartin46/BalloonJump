
BOX2D = src/include/*.cpp
FLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main # -mwindows
run:
	g++ -I src/include -L src/lib -std=c++17 -o main.exe main.cpp ${BOX2D} ${FLAGS}
	./main
save:
	git add .
	git commit -m "$(msg)"
	git push -u origin