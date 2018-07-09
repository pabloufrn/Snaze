g++ src/* -std=c++11 -Iinclude -Isfml/include -o exec_game -Wl,-rpath='$ORIGIN/sfml/lib' -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lpthread
