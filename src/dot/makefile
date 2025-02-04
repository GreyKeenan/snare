default:

guroot= ../../subs/gu/src

gccflags= \
	-std=c99 \
	-Wpedantic \
	-Wall \
	-Wextra \
	-iquote . \
	-iquote .. \
	-iquote $(guroot)

lgu= \
	-L $(guroot) \
	-l gu

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
		-lSDL2 \
		$(lgu)

sort:
	gcc $(gccflags) \
		$(args) \
		\
		tests/sort.c \
		sort.c \
		\
		$(lgu)
