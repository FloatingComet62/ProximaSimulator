src = $(wildcard */*.cpp)
out = main.exe
cflags =  -I/deps/include/
all: $(src)
	make build
	make run
build: $(src)
	g++ $(src) $(cflags) -o $(out) -Ldeps/lib/ -lSDL2
run:
	$(out)