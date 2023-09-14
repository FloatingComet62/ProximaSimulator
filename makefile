src = $(wildcard */*.cpp)
out = main.exe
compiler_flags = -I/deps/include/
compiler = g++
lib_flags = -Ldeps/lib/ -lSDL2
all: $(src)
	make build
	make run
build: $(src)
	$(compiler) $(src) $(compiler_flags) -o $(out) $(lib_flags)
run:
	$(out)