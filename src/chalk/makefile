default:

gccflags= \
	-std=c99 \
	-Wpedantic \
	-Wall \
	-Wextra \
	-iquote . \
	-iquote ..

test: ./a.out
	./a.out $(args)

rpoints:
	gcc $(gccflags) \
		\
		$(args) \
		\
		tests/rpoints.c \
		random.c \
		\
		-lm \
		-lSDL2

sort:
	gcc $(gccflags) \
		$(args) \
		tests/sort.c \
		compare_point.c \

