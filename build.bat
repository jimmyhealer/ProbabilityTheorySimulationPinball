g++ -c lib/SDL_FontCache.c -o lib/SDL_FontCache.o 
g++ main.cpp lib/SDL_FontCache.o -o main.exe -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2 
